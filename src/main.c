/* ********************************************************************
FILE                   : main.c

PROGRAM DESCRIPTION    :  A preset PIN and account number is set by default in code.
                          Entered PIN in keypad is displayed in  LCD. Use RESET_SW to reset Process, if any problem arises and start afresh. 
                          Use Enter SW to end input and entered data is at end.
                          At first Welcome message to be displayed, when ACCOUNT_SW is pressed, account number is entered.
                          If entered account number is correct, then ask for PIN  and if entered PIN is correct,
                          then display Next stage. If account number is incorrect and ask to reenter account number.
                          After 3 failed iteration on entered account number, stop reenter of account number and display visit bank. 
                          If no key is pressed for longer duration or key has been pressed for long duration, display timeout and display visit bank.
                          After 3 failed iteration on entered PIN number,stop reenter of PIN number and display visit bank.
                          After displayed auth status, wait for predetermined time,and then display welcome message and wait for ACCOUNT_SW to be pressed to enter account number.
                          After that RESET_SW is pressed to restart the process, if any problem arises.                          

	 
AUTHOR                : K.M. Arun Kumar alias Arunkumar Murugeswaran
	 
KNOWN BUGS            : 

NOTE                  : FOR reusable firmware development and data can be inputed by multi input source and outputed to multi output source.                        
                        		
	           
		
		 APPL TIMEOUT : YET TO IMPLEMENT. Use 2 TIMERs, one timer for (executes  Key Press) and other timer for (executes Long_Key_Press_Proc and No_Key_Press_Proc) with status check. 
                         Cannot do when both timer uses status check for timer expiry as processor loops for timer to expiry,
                        when expired for predefined time executes Appl(auth fsm) proc, which does waiting for key stroke,
                        without timer for no key stroke you can do decrement count, when count ends timeout for no key press has happened.
                        You can do when 2 timers are used and 1 timer or no timer uses status check for timer expiry and rest uses interrupt. 
						
						YET TO IMPLEMENT just after displayed visit bank wait for predetermined time, display welcome message 
                        and wait for ACCOUNT_SW to be pressed to enter account number
						
						Base from PIC16F887-repo->00_assignment->Single Account auth
						
CAUTION               :  

               LCD    :  only display least numeric digits and from left to right display is implemented.
			   UART   :  only display least numeric digits and from left to right display is implemented.
	     LED MATRIX   :  Does not support data type in str. 
                      :  Disp map ie led_dot_disp_map[] is coded for only seq write type = SEQ_WRITE_COL. 	                      					  
		        SW    :  if only sw is used, then no need to hold CPU by using sw read level transition by not defining SW_PRESS_HOLD_CPU. 
           	 KEYPAD   :  If keypad is used, then u must hold CPU by using While(read_sw_pressed_state) by defining SW_PRESS_HOLD_CPU.
			          :  If enter or backspace SW is not a part of keypad, then set IO ch of that enter or backspace SW = IO_CH_INVALID.
	SW & KEYPAD INIT  :  First initialise independent SW if any, then initialize Keyboard, if any.
	
    	ERROR PROC    :  Process to do when a error or warning has occured is not implemented, but communicates with error status in LCD(ch: 0) or/and UART(ch: 0).
		  CTRL CHARS  :  Only Backspace ctrl char is supported and enter ctrl char can be used as terminator char. 
                                    
CHANGE LOGS           :  

FILE ID               : 01

*****************************************************************************/
#include "main.h"
#include "dev_chs_map.h"
#include "data_ids_map.h"

/* ------------------------------ macro defination ------------------------------ */


/* ----------------------------- global variable defination --------------------- */
num_value_t disp_trace_num;
disp_num_fmt_t disp_trace_num_fmt;
uint32_t sys_error_or_warning_flag = NO_ERROR;
data_id_status_para_t data_id_status_para[NUM_DATA_IDS];
uint8_t cur_data_id = DATA_ID_INVALID;

/* ----------------------------- global variable declaration -------------------- */


/* ----------------------------- global function declaration -------------------- */
static uint8_t System_Init(void); 
static uint8_t HW_Init(const void *const get_init_ptr);
static uint8_t PLL_Init(void);
extern uint8_t Appl_Proc(void);
extern uint8_t Appl_Init(const void *const data_ptr);
extern uint8_t Appl_HW_Init(void);
extern uint8_t Appl_Reset(const uint8_t reset_type);

/*------------------------------------------------------------*
FUNCTION NAME  : main

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 01.01  

BUGS           :              
-*------------------------------------------------------------*/
int main(void)
{
	uint8_t ret_status;
	  	
	if((ret_status = System_Init()) != SUCCESS)
	{
       return ret_status;
	}	
    if((ret_status = Appl_Init(NULL_PTR)) != SUCCESS)
	{
		  return ret_status;
    }
	while(1)
	{
		if((ret_status = Appl_Proc()) != SUCCESS)
		{
			return FAILURE;
		}
	}
   return FAILURE;
}

/*------------------------------------------------------------*
FUNCTION NAME  : Reset_Process

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 01.02

BUGS           :    
-*------------------------------------------------------------*/
uint8_t Reset_Process(const uint8_t reset_type)
{
	uint8_t ret_status;
  
	switch(reset_type)
	{
		case RESET_WHOLE:		 
		  #ifdef SW_MOD_ENABLE
	         Disable_All_SWs();
	      #endif   
          #ifdef KEYBOARD_MOD_ENABLE	
            Disable_All_Keyboards();
	      #endif
	      #ifdef SEG7_MOD_ENABLE
	        Disable_All_Seg7s();
	      #endif
	      #ifdef LED_MATRIX_MOD_ENABLE
	         Disable_All_LED_Matrixs();
	      #endif
	      #ifdef LCD_MOD_ENABLE
	         Disable_All_LCDs();
	      #endif 
		  //Reset_UART_Parameters();
	      //memset(lcd_const_disp_flag, STATE_NO_IN_CHAR, sizeof(lcd_const_disp_flag)/ sizeof(char));
		case RESET_DATA_IDS_AND_APPL: 
		   Reset_Data_IDs_Status();
		case RESET_APPL:
           if((ret_status = Appl_Reset(RESET_APPL)) != SUCCESS)
		  {
			  sys_error_or_warning_flag = ERR_RESET_OPER;
		      Error_or_Warning_Proc("11.01.12", ERROR_OCCURED, sys_error_or_warning_flag);
		     return sys_error_or_warning_flag;
		  }
        break;
        default:
           sys_error_or_warning_flag = ERR_FORMAT_INVALID;
		   Error_or_Warning_Proc("11.01.12", ERROR_OCCURED, sys_error_or_warning_flag);
		   return sys_error_or_warning_flag;		
	}
	 return SUCCESS;
}

/*------------------------------------------------------------*
FUNCTION NAME  : System_Init

DESCRIPTION    : 
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 01.03  

BUGS           :              
-*------------------------------------------------------------*/
static uint8_t System_Init(void)
{
	 uint8_t ret_status; 
	 
	 if((ret_status = HW_Init(NULL_PTR)) != SUCCESS)
	 {
		 sys_error_or_warning_flag = ERR_HW_INIT;
		 Error_or_Warning_Proc("01.03.01", ERROR_OCCURED, sys_error_or_warning_flag);
		 return sys_error_or_warning_flag; 
	 }
	 if((ret_status = Reset_Process(RESET_WHOLE)) != SUCCESS)
	 {
		 sys_error_or_warning_flag = ERR_RESET_OPER;
		 Error_or_Warning_Proc("01.03.02", ERROR_OCCURED, sys_error_or_warning_flag);
		 return sys_error_or_warning_flag;
	 }	 
	 if((ret_status = Data_IDs_Set_Para()) != SUCCESS)
	 {
         sys_error_or_warning_flag = ERR_DATA_ID_CONF;
		 Error_or_Warning_Proc("01.03.03", ERROR_OCCURED, sys_error_or_warning_flag);
		 return sys_error_or_warning_flag; 
	 }
     return SUCCESS;	 
}

/*------------------------------------------------------------*
FUNCTION NAME  : HW_Init

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : First initialise independent SW if any, then initialize Keyboard, if any.

Func ID        : 01.04  

BUGS           :              
-*------------------------------------------------------------*/
static uint8_t HW_Init(const void *const get_init_ptr)
{
	uint8_t ret_status = SUCCESS ;
	
	PLL_Init();
	Reset_IO_Chs();	
    if((ret_status = Appl_HW_Init()) != SUCCESS)
	{
		 sys_error_or_warning_flag = ERR_HW_INIT;
		 Error_or_Warning_Proc("01.05.01", ERROR_OCCURED, sys_error_or_warning_flag);
		 return sys_error_or_warning_flag;
	}    
    return SUCCESS;	
}

/*------------------------------------------------------------*
FUNCTION NAME  : PLL_Init

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : calculated for crystal oscillitor of 12MHz  

Func ID        : 01.05  

BUGS           :              
-*------------------------------------------------------------*/
static uint8_t PLL_Init(void)
{
    PLLCON = 0x01; //Enable PLL
    PLLCFG = 0x24; //Multiplier and divider setup
    PLLFEED = 0xAA; //Feed sequence
    PLLFEED = 0x55;
 
    while(!(PLLSTAT & 0x00000400)); //is locked?
 
    PLLCON = 0x03; //Connect PLL after PLL is locked
    PLLFEED = 0xAA; //Feed sequence
    PLLFEED = 0x55;
    VPBDIV = 0x00; // or APBDIV, PCLK = CCLK / 4 
   	return SUCCESS;
}

/*------------------------------------------------------------------*-
  ------------------------ END OF FILE ------------------------------
-*------------------------------------------------------------------*/
