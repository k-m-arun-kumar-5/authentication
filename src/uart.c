/* ********************************************************************
FILE                  : uart.c

PURPOSE               :  
	 
AUTHOR                : K.M. Arun Kumar alias Arunkumar Murugeswaran
	 
KNOWN BUGS            : 

NOTE                  : only display least numeric digits and from left to right display is implemented.
         
CHANGE LOGS           :  

FILE ID               : 10

*****************************************************************************/
#include "main.h"

#ifdef USART_MOD_ENABLE

/* ------------------------------ macro defination ------------------------------ */


/* ----------------------------- global variable defination --------------------- */
static uint8_t volatile *const uart_lcr_ptr[NUM_COMM_DEV_ID_UART_CHS] = {(uint8_t *) &U0LCR, (uint8_t *) &U1LCR };
static uint8_t volatile *const uart_dll_ptr[NUM_COMM_DEV_ID_UART_CHS] = {(uint8_t *) &U0DLL, (uint8_t *) &U1DLL };
static uint8_t volatile *const uart_dlm_ptr[NUM_COMM_DEV_ID_UART_CHS] = {(uint8_t *) &U0DLM, (uint8_t *) &U1DLM };
static uint8_t volatile *const uart_fcr_ptr[NUM_COMM_DEV_ID_UART_CHS] = {(uint8_t *) &U0FCR, (uint8_t *) &U1FCR };
static uint8_t volatile *const uart_lsr_ptr[NUM_COMM_DEV_ID_UART_CHS] = {(uint8_t *) &U0LSR, (uint8_t *) &U1LSR };
static uint8_t volatile *const uart_rbr_ptr[NUM_COMM_DEV_ID_UART_CHS] = {(uint8_t *) &U0RBR, (uint8_t *) &U1RBR };
static uint8_t volatile *const uart_thr_ptr[NUM_COMM_DEV_ID_UART_CHS] = {(uint8_t *) &U0THR, (uint8_t *) &U1THR };

/* ----------------------------- global variable declaration -------------------- */


/* ----------------------------- global function declaration -------------------- */


/*------------------------------------------------------------*
FUNCTION NAME  : UART_Init

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 10.01  

BUGS           :              
-*------------------------------------------------------------*/
uint8_t UART_Init(const uint8_t uart_ch_id)
{
	uint8_t uart_io_ch, ret_status;
	
	if(uart_ch_id >= NUM_COMM_DEV_ID_UART_CHS)
	{
		sys_error_or_warning_flag = ERR_DEV_CH_ID_EXCEEDS;
		 Error_or_Warning_Proc("10.01.01", ERROR_OCCURED, sys_error_or_warning_flag);
		return sys_error_or_warning_flag;
	}
	switch(uart_ch_id)
	{
		case CH_ID_00:
	       uart_io_ch = IO_CH_00;
		break;
        case CH_ID_01:
		   uart_io_ch = IO_CH_08;
        break;		
	}
	//UART TX FUNC
	if((ret_status = Non_GPIO_Func_Set(uart_io_ch, IO_FUNC_MODE_01 )) != SUCCESS)
	{
		sys_error_or_warning_flag = ERR_UART_INIT;
		 Error_or_Warning_Proc("10.01.02", ERROR_OCCURED, sys_error_or_warning_flag);
		return sys_error_or_warning_flag;
	}
	
	//UART RCV FUNC
	if((ret_status = Non_GPIO_Func_Set(uart_io_ch + 1, IO_FUNC_MODE_01 )) != SUCCESS)
	{
		sys_error_or_warning_flag = ERR_UART_INIT;
		 Error_or_Warning_Proc("10.01.03", ERROR_OCCURED, sys_error_or_warning_flag);
		return sys_error_or_warning_flag;
	}
	*uart_lcr_ptr[uart_ch_id] = 0x83;  //Line control Register for Lenght,Parity
	*uart_dll_ptr[uart_ch_id] = 98;   //Baud Rate 9600	
	*uart_dlm_ptr[uart_ch_id] = 0;     //Baud Rate 9600   
    *uart_lcr_ptr[uart_ch_id] = 0x03;  //Set Length and clear DLE
    *uart_fcr_ptr[uart_ch_id] = 0x03;  //FIFO Enable 	
	return SUCCESS;
}

/*------------------------------------------------------------*
FUNCTION NAME  : UART_Transmit_Char

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 10.02  

BUGS           :              
-*------------------------------------------------------------*/
uint8_t UART_Transmit_Char(const uint8_t uart_ch_id, const unsigned char uart_tx_char)
{
	if(uart_ch_id >= NUM_COMM_DEV_ID_UART_CHS)
	{
		sys_error_or_warning_flag = ERR_DEV_CH_ID_EXCEEDS;
		 Error_or_Warning_Proc("10.02.01", ERROR_OCCURED, sys_error_or_warning_flag);
		return sys_error_or_warning_flag;
	}
	*uart_thr_ptr[uart_ch_id] = uart_tx_char;   //Transmitting Data
    while(!(*uart_lsr_ptr[uart_ch_id] & 0X40)); //Waiting for Transmission End  
	return SUCCESS;
}

/*------------------------------------------------------------*
FUNCTION NAME  : UART_Transmit_Str

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 10.03  

BUGS           :              
-*------------------------------------------------------------*/
uint8_t UART_Transmit_Str(const uint8_t uart_ch_id, const char *const transmit_str)
{
	uint8_t ret_status, tx_num_chars = 0;
	
	if(transmit_str == NULL_PTR)
	{
		sys_error_or_warning_flag = ERR_NULL_PTR;
		Error_or_Warning_Proc("10.03.01", ERROR_OCCURED, sys_error_or_warning_flag);
		return sys_error_or_warning_flag;
	}
	if(uart_ch_id >= NUM_COMM_DEV_ID_UART_CHS)
	{
		sys_error_or_warning_flag = ERR_DEV_CH_ID_EXCEEDS;
		Error_or_Warning_Proc("10.03.02", ERROR_OCCURED, sys_error_or_warning_flag);
		return sys_error_or_warning_flag;
	}	
	while(*(transmit_str + tx_num_chars))
	{
		 if((ret_status = UART_Transmit_Char(uart_ch_id, *(transmit_str + tx_num_chars))) != SUCCESS)
		 {
			 sys_error_or_warning_flag = ERR_UART_TX_PROC;
			 Error_or_Warning_Proc("10.03.03", ERROR_OCCURED, sys_error_or_warning_flag);
			 return sys_error_or_warning_flag; 
		 }			 
		 ++tx_num_chars;
	}
    return SUCCESS;	
}

/*------------------------------------------------------------*
FUNCTION NAME  : UART_Transmit_Num

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : only display least numeric digits and from left to right display is implemented

Func ID        : 10.04  

BUGS           :              
-*------------------------------------------------------------*/
uint8_t UART_Transmit_Num(const uint8_t uart_ch_id, const uint8_t num_data_type, const disp_num_fmt_t disp_num_fmt, const int32_t uart_num)
{
    uint32_t base_power_val, uart_disp_num;
    int16_t place_val;
    uint8_t base, place_digit[MAX_UART_DIGITS], ret_status;    
	char hex_data[] ={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'}; 
	 
	if(uart_ch_id >= NUM_COMM_DEV_ID_UART_CHS)
	{
		   sys_error_or_warning_flag = ERR_DEV_CH_ID_EXCEEDS;
		   Error_or_Warning_Proc("10.04.01", ERROR_OCCURED, sys_error_or_warning_flag);
		   return sys_error_or_warning_flag;
	}
	if(disp_num_fmt.num_digits <= 0 || disp_num_fmt.num_digits > MAX_UART_DIGITS )
	{
		sys_error_or_warning_flag = ERR_UART_DISP_FORMAT;
		Error_or_Warning_Proc("10.04.02", ERROR_OCCURED, sys_error_or_warning_flag);
		return sys_error_or_warning_flag;
	}
     switch(num_data_type)
	 {
		case DATA_TYPE_IN_BINARY:
           base = 2;
	       if(uart_num < 0)
		   {
				 if(disp_num_fmt.sign_flag == STATE_YES)
		         {
			    	if((ret_status = UART_Transmit_Char(uart_ch_id, '-')) != SUCCESS)
					{
						sys_error_or_warning_flag = ERR_UART_TX_PROC;
		                Error_or_Warning_Proc("10.04.03", ERROR_OCCURED, sys_error_or_warning_flag);
						return sys_error_or_warning_flag;
					}
				 }			    
			}
			else
			{
			   if(disp_num_fmt.sign_flag == STATE_YES)
		       {
			    	if((ret_status = UART_Transmit_Char(uart_ch_id, '+')) != SUCCESS)
					{
						sys_error_or_warning_flag = ERR_UART_TX_PROC;
		                Error_or_Warning_Proc("10.04.04", ERROR_OCCURED, sys_error_or_warning_flag);
						return sys_error_or_warning_flag;
					}
			   }
		    }		
           uart_disp_num = uart_num;   		   
		   if((ret_status = UART_Transmit_Str(uart_ch_id, "0b")) != SUCCESS)
		   {
			   sys_error_or_warning_flag = ERR_UART_TX_PROC;
		       Error_or_Warning_Proc("10.04.05", ERROR_OCCURED, sys_error_or_warning_flag);
			   return sys_error_or_warning_flag;
		   }
       break;			
	   case DATA_TYPE_IN_HEXA:
		   base = 16;
	       if(uart_num < 0)
			 {
				 if(disp_num_fmt.sign_flag == STATE_YES)
		         {
			    	if((ret_status = UART_Transmit_Char(uart_ch_id, '-')) != SUCCESS)
					{
						sys_error_or_warning_flag = ERR_UART_TX_PROC;
		                Error_or_Warning_Proc("10.04.06", ERROR_OCCURED, sys_error_or_warning_flag);
						return sys_error_or_warning_flag;
					}			
				 }
         	uart_disp_num = -uart_num; 
			 }
			 else
			 {
				 if(disp_num_fmt.sign_flag == STATE_YES)
		        {
			    	if((ret_status = UART_Transmit_Char(uart_ch_id, '+')) != SUCCESS)
					{
						sys_error_or_warning_flag = ERR_UART_TX_PROC;
		                Error_or_Warning_Proc("10.04.07", ERROR_OCCURED, sys_error_or_warning_flag);
						return sys_error_or_warning_flag;
					}			
				 }
         uart_disp_num = uart_num; 
			 }           			
			if((ret_status = UART_Transmit_Str(uart_ch_id, "0x")) != SUCCESS)
			{
				sys_error_or_warning_flag = ERR_UART_TX_PROC;
		                Error_or_Warning_Proc("10.04.08", ERROR_OCCURED, sys_error_or_warning_flag);
						return sys_error_or_warning_flag;
			}
        break;			
		case DATA_TYPE_IN_DECIMAL:
		    base = 10;
		    if(uart_num < 0)
			 {
				 if(disp_num_fmt.sign_flag == STATE_YES)
		         {
			    	if((ret_status = UART_Transmit_Char(uart_ch_id, '-')) != SUCCESS)
					{
						sys_error_or_warning_flag = ERR_UART_TX_PROC;
		                Error_or_Warning_Proc("10.04.09", ERROR_OCCURED, sys_error_or_warning_flag);
						return sys_error_or_warning_flag;
					}
				 }
			    uart_disp_num = -uart_num; 
			 }
			 else
			 {
				 if(disp_num_fmt.sign_flag == STATE_YES)
		         {
			    	if((ret_status = UART_Transmit_Char(uart_ch_id, '+')) != SUCCESS)
					{
						sys_error_or_warning_flag = ERR_UART_TX_PROC;
		                Error_or_Warning_Proc("10.04.10", ERROR_OCCURED, sys_error_or_warning_flag);
						return sys_error_or_warning_flag;
					}
				 }
			  	 uart_disp_num = uart_num;  
			 }	
		break;
		default:
		  sys_error_or_warning_flag = ERR_UART_DISP_FORMAT;
		  Error_or_Warning_Proc("10.04.11", ERROR_OCCURED, sys_error_or_warning_flag);
		  return sys_error_or_warning_flag;
	}
	if(disp_num_fmt.least_digits_flag == STATE_YES && disp_num_fmt.left_format_flag == STATE_YES)
	{			
	       base_power_val =  Power_Of(base, disp_num_fmt.num_digits);
		   for(place_val = disp_num_fmt.num_digits - 1; place_val >= 0; --place_val)
		   {
		      uart_disp_num %= base_power_val;
		      base_power_val /= base; 
		      place_digit[place_val] = uart_disp_num /base_power_val;
		      if((ret_status = UART_Transmit_Char(uart_ch_id, hex_data[place_digit[place_val]])) != SUCCESS)
			  {
				  sys_error_or_warning_flag = ERR_UART_TX_PROC;
		          Error_or_Warning_Proc("10.04.12", ERROR_OCCURED, sys_error_or_warning_flag);
				  return sys_error_or_warning_flag;
			  }				  
		  } 
	}
    else
	{
		//only display least numeric digits and from left to right display is implemented
		sys_error_or_warning_flag = ERR_UART_DISP_FORMAT;
		Error_or_Warning_Proc("10.04.13", ERROR_OCCURED, sys_error_or_warning_flag);
		return sys_error_or_warning_flag;
	}		
    return SUCCESS;	
}

/*------------------------------------------------------------*
FUNCTION NAME  : UART_Receive_Char

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 10.05  

BUGS           :              
-*------------------------------------------------------------*/
uint8_t UART_Receive_Char(const uint8_t uart_ch_id,  unsigned char *const uart_rcvd_char_ptr)
{
	const char framing_error_msg_disp[] = "FERR", overrun_error_msg_disp[] = "OERR";
	uint8_t uart_status, ret_status;
	
	if(uart_rcvd_char_ptr == NULL_PTR)
	{
		sys_error_or_warning_flag = ERR_NULL_PTR;
		Error_or_Warning_Proc("10.05.01", ERROR_OCCURED, sys_error_or_warning_flag);
		return sys_error_or_warning_flag;
	}
	if(uart_ch_id >= NUM_COMM_DEV_ID_UART_CHS)
	{
		sys_error_or_warning_flag = ERR_DEV_CH_ID_EXCEEDS;
		Error_or_Warning_Proc("10.05.02", ERROR_OCCURED, sys_error_or_warning_flag);
		return sys_error_or_warning_flag;
	}
	uart_status = *uart_lsr_ptr[uart_ch_id];
	if(!(uart_status & (1 << 0)))
	{
		return COMM_NO_RCV_CHAR;
	}
	do
	{
		if(uart_status & (1 << 7))
		{
		   if(uart_status & (1 << 1))
		   {
			   //overflow run error has occured
			  #ifdef LCD_MOD_ENABLE
		           LCD_Disp_Goto_XY(TRACE_LCD_CH_ID, ERROR_LINE_NUM, NUM_COL1);
	               LCD_Disp_Str(TRACE_LCD_CH_ID, overrun_error_msg_disp);
			  #endif 
			     
			   Error_or_Warning_Proc("10.05.03", ERROR_OCCURED, ERR_UART_OVERFLOW_RUN );			              		
		   }
		   if(uart_status & (1 << 3))
		   {
			 // framing error has occured
			   #ifdef LCD_MOD_ENABLE
	             LCD_Disp_Goto_XY(TRACE_LCD_CH_ID, ERROR_LINE_NUM, NUM_COL1);
	             LCD_Disp_Str(TRACE_LCD_CH_ID, framing_error_msg_disp);
			   #endif 
		   		Error_or_Warning_Proc("10.05.04", ERROR_OCCURED, ERR_UART_FRAMING );		
		   }
		   sys_error_or_warning_flag = ERR_COMM_RCV_PROC;
		   Error_or_Warning_Proc("10.05.05", ERROR_OCCURED, sys_error_or_warning_flag );
		   return sys_error_or_warning_flag;	
		}
		uart_status = *uart_lsr_ptr[uart_ch_id];		
	} while(!(uart_status & (1 << 0)));      //Waiting for Data Receiving
    *uart_rcvd_char_ptr = *uart_rbr_ptr[uart_ch_id];  //Receive the Data 			
	if((ret_status = UART_Transmit_Char(uart_ch_id, *uart_rcvd_char_ptr)) != SUCCESS)
	{
		sys_error_or_warning_flag = ERR_UART_TX_PROC;
		Error_or_Warning_Proc("10.05.06", ERROR_OCCURED, sys_error_or_warning_flag );
		return sys_error_or_warning_flag;
	}
  	return COMM_RCVD_CHAR;
}

#endif

/*------------------------------------------------------------------*-
  ------------------------ END OF FILE ------------------------------
-*------------------------------------------------------------------*/
