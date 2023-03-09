/* ********************************************************************
FILE                   : appl.c

PURPOSE                :  Application 
	 
AUTHOR                : K.M. Arun Kumar alias Arunkumar Murugeswaran
	 
KNOWN BUGS            : 

NOTE                  : 
						
CAUTION               :  
                                    
CHANGE LOGS           :  

FILE ID               : 11

*****************************************************************************/
#include "main.h"
#include "appl.h"

/* ------------------------------ macro defination ------------------------------ */


/* ----------------------------- global variable defination --------------------- */
lcd_disp_status_t lcd_disp_status = {STATUS_DISP_ON, STATUS_DISP_ON, STATUS_DISP_ON, STATUS_DISP_OFF, STATUS_DISP_OFF, STATE_NO};

auth_fsm auth_fsm_state = INITIAL_FSM; 
auth_status_fsm status_disp_fsm = INITIAL;
 
uint8_t appl_error_or_warning_flag;
 
/* ----------------------------- global variable declaration -------------------- */


/* ----------------------------- global function declaration -------------------- */

/*------------------------------------------------------------*
FUNCTION NAME  : After_Switch_Stoke_Proc

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 11.01

BUGS           :    
-*------------------------------------------------------------*/ 
uint8_t After_Switch_Stoke_Proc(const unsigned char pressed_sw)
{
	const char enter_account_msg_disp_str[] =  "Enter Account"; 	
	lcd_point_config_t lcd_data_point_config;
	dev_id_t lcd_or_keyboard_dev_id, cur_data_devs_src_allow[1] = { CUR_DATA_ID_ALL_SRC_OF_SPEC_OPER};
	uint8_t ret_status, retrieve_data_str_len, keyboard_part_and_oper_data;
	
	switch(pressed_sw)
	{
	    case ACCOUNT_SW_CODE:
		     #ifdef SHOULD_REMOVE
				UART_Transmit_Str(TRACE_UART_CH_ID, "\r ACCOUNT_SW_CODE ");						         
		    #endif			
		     if((ret_status = Next_Data_Conf_Parameter(DATA_ID_ACCOUNT)) != SUCCESS)
			 {
				 appl_error_or_warning_flag = ERR_NEXT_DATA_CONF;
				 Error_or_Warning_Proc("11.01.01", ERROR_OCCURED, appl_error_or_warning_flag);
				 return appl_error_or_warning_flag; 
			 }
			 if((ret_status = SW_Oper(ACCOUNT_SW_IO_CH, DEV_DISABLE_OPER)) != SUCCESS)
             {
		         appl_error_or_warning_flag = ERR_DEV_OPER_DISABLE_FUNC;
	             Error_or_Warning_Proc("11.01.02", ERROR_OCCURED, appl_error_or_warning_flag);
	             return appl_error_or_warning_flag;
             }   
			 if((ret_status = SW_Oper(RESET_SW_IO_CH, DEV_ENABLE_OPER)) != SUCCESS)
             {
		         appl_error_or_warning_flag = ERR_DEV_OPER_ENABLE_FUNC;
	             Error_or_Warning_Proc("11.01.03", ERROR_OCCURED, appl_error_or_warning_flag);
	              return appl_error_or_warning_flag;
             }
			 Set_Data_Devs_Src_Allow(DEV_OUTPUT_TYPE, CUR_DATA_ID_ALL_SRC_OF_SPEC_OPER, cur_data_devs_src_allow);
		     if((ret_status = Cur_Data_ID_Devs_Src_Basic_Oper_Func(OUTPUT_DEV_ENABLE_OPER_FUNC, DEV_OUTPUT_TYPE, cur_data_devs_src_allow)) != SUCCESS)
		     {
		         appl_error_or_warning_flag = ERR_DEV_OPER_ENABLE_FUNC;
				 Error_or_Warning_Proc("11.01.04", ERROR_OCCURED, appl_error_or_warning_flag);
				 return appl_error_or_warning_flag; 
	         }
		        lcd_or_keyboard_dev_id.dev_id = OUTPUT_DEV_ID_LCD;
		         if((ret_status = Data_ID_Src_Spec_Dev_Find_Dev_Ch_ID(cur_data_id, &lcd_or_keyboard_dev_id, DEV_OUTPUT_TYPE))!= SUCCESS)
				 {
					 appl_error_or_warning_flag = ERR_LCD_NOT_DATA_SRC;
					 Error_or_Warning_Proc("11.01.05", ERROR_OCCURED, appl_error_or_warning_flag);
					 return appl_error_or_warning_flag;
				 }
				 if((ret_status = LCD_Clear_Screen(lcd_or_keyboard_dev_id.dev_ch_id)) != SUCCESS)
				 {
					 appl_error_or_warning_flag = ERR_LCD_WRITE_OPER;
					 Error_or_Warning_Proc("11.01.06", ERROR_OCCURED, appl_error_or_warning_flag);
					 return appl_error_or_warning_flag;
				 }			     
			     if((ret_status = LCD_Disp_Goto_XY(lcd_or_keyboard_dev_id.dev_ch_id, ACCOUNT_MSG_LINE_NUM, ACCOUNT_MSG_START_COL_NUM)) != SUCCESS)
				 {
					 appl_error_or_warning_flag = ERR_LCD_DISP_GOTO_XY;
					 Error_or_Warning_Proc("11.01.07", ERROR_OCCURED, appl_error_or_warning_flag);
					 return appl_error_or_warning_flag; 
				 }
                 if((ret_status = LCD_Disp_Str(lcd_or_keyboard_dev_id.dev_ch_id, enter_account_msg_disp_str)) != SUCCESS)
				 {
					 appl_error_or_warning_flag = ERR_LCD_WRITE_OPER;
					 Error_or_Warning_Proc("11.01.08", ERROR_OCCURED, appl_error_or_warning_flag);
					 return appl_error_or_warning_flag; 
				 }
				 lcd_data_point_config.cur_data_start_point_num.line_num_or_index = ACCOUNT_ENTRY_START_LINE_NUM;
				 lcd_data_point_config.cur_data_start_point_num.col_num_or_index = ACCOUNT_ENTRY_START_COL_NUM;
				 if((ret_status = Appl_Data_Retrieve_Para(cur_data_id, DATA_RETRIEVE_CTRL_REQ_MAX_DATA_CHARS, &lcd_data_point_config.max_num_chars_config)) != SUCCESS)
				 {
						 appl_error_or_warning_flag = ERR_APPL_DATA_RETRIEVE;
					     Error_or_Warning_Proc("11.01.09", ERROR_OCCURED, appl_error_or_warning_flag);
					     return appl_error_or_warning_flag; 
				 }
                 #if( NUM_CHARS_INPUTDATA == GIVEN_CHARS_MAX_CONFIG_LINES_AND_COLS)											
                    ret_status = LCD_Cur_Data_By_NumChars_Calc_Para(lcd_or_keyboard_dev_id.dev_ch_id, &lcd_data_point_config);
                 #elif(NUM_CHARS_INPUTDATA == GIVEN_XY_MAX_CONFIG_LINES_AND_COLS)
                  /* ACCOUNT INPUT DATA max num of input account chars = num of chars from start pos (entry start line, entry start col) till end of that line */ 
			         lcd_data_point_config.next_data_start_point_num.line_num_or_index = ACCOUNT_ENTRY_START_LINE_NUM + 1;
				     lcd_data_point_config.next_data_start_point_num.col_num_or_index = NUM_COL1;
                     ret_status = LCD_Cur_Data_By_XY_Calc_Para(lcd_or_keyboard_dev_id->dev_ch_id, &lcd_data_point_config );
                  #else 
                	  /*NUM_CHARS_INPUTDATA = GIVEN_CHARS_MAX_XY */
                  /* ACCOUNT INPUT DATA's max num of input account chars = min(num of chars from start pos (entry start line, entry start col) till end of that line, MAX_ACCOUNT_NUM_CHARS ) */
				    lcd_data_point_config.next_data_start_point_num.line_num_or_index = ACCOUNT_ENTRY_START_LINE_NUM + 1;
				    lcd_data_point_config.next_data_start_point_num.col_num_or_index = NUM_COL1;						
                 	ret_status = LCD_Cur_Data_By_NumChars_and_XY_Calc_Para(lcd_or_keyboard_dev_id->dev_ch_id, &lcd_data_point_config); 
                 #endif
				 #ifdef SHOULD_REMOVE
				     disp_trace_num_fmt.sign_flag = STATE_NO;
		             disp_trace_num_fmt.least_digits_flag = STATE_YES;
		             disp_trace_num_fmt.left_format_flag = STATE_YES;
		             disp_trace_num_fmt.num_digits = 3;
					 UART_Transmit_Str(TRACE_UART_CH_ID, "\r Account Alloc = ");
					 UART_Transmit_Num(TRACE_UART_CH_ID, DATA_TYPE_IN_DECIMAL, disp_trace_num_fmt, lcd_status[lcd_or_keyboard_dev_id.dev_ch_id].cur_data_lcd_para.max_num_chars_alloc);			         
				 #endif
				 switch(ret_status)
				 {
					 case WARN_LCD_ALLOC_LESS_THAN_CONFIG_CHARS:
					 case SUCCESS:
					      if((ret_status = Data_ID_Set_Para(cur_data_id, lcd_status[lcd_or_keyboard_dev_id.dev_ch_id].cur_data_lcd_para.max_num_chars_alloc + 1)) != SUCCESS)
						  {
							  appl_error_or_warning_flag = ERR_DATA_ID_CONF;
					          Error_or_Warning_Proc("11.01.11", ERROR_OCCURED, appl_error_or_warning_flag);
					          return appl_error_or_warning_flag; 
						  }
					 break;
                     default:
                  		appl_error_or_warning_flag = ERR_LCD_DATA_POINT_CONFIG;
					    Error_or_Warning_Proc("11.01.12", ERROR_OCCURED, appl_error_or_warning_flag);
					    return appl_error_or_warning_flag; 			 
				 }
				 if((ret_status = LCD_Input_Goto_XY(lcd_or_keyboard_dev_id.dev_ch_id, ACCOUNT_ENTRY_START_LINE_NUM, ACCOUNT_ENTRY_START_COL_NUM)) != SUCCESS)
				 {
					 appl_error_or_warning_flag = ERR_LCD_INPUT_GOTO_XY;
					 Error_or_Warning_Proc("11.01.13", ERROR_OCCURED, appl_error_or_warning_flag);
					 return appl_error_or_warning_flag;
				 }
                 if((ret_status = LCD_Write_Command(lcd_or_keyboard_dev_id.dev_ch_id, 0x0E)) != SUCCESS)
				 {
					 appl_error_or_warning_flag = ERR_LCD_WRITE_OPER;
					 Error_or_Warning_Proc("11.01.14", ERROR_OCCURED, appl_error_or_warning_flag);
					 return appl_error_or_warning_flag;
				 }
                 lcd_or_keyboard_dev_id.dev_id = INPUT_DEV_ID_KEYBOARD;
		         if((ret_status = Data_ID_Src_Spec_Dev_Find_Dev_Ch_ID(cur_data_id, &lcd_or_keyboard_dev_id, DEV_INPUT_TYPE))!= SUCCESS)
				 {
					 appl_error_or_warning_flag = ERR_LCD_NOT_DATA_SRC;
					 Error_or_Warning_Proc("11.01.16", ERROR_OCCURED, appl_error_or_warning_flag);
					 return appl_error_or_warning_flag;
				 }
				 if((ret_status = Keyboard_Keypad_Oper(lcd_or_keyboard_dev_id.dev_ch_id, DEV_ENABLE_OPER)) != SUCCESS)
				 {
					 appl_error_or_warning_flag = ERR_DEV_OPER_ENABLE_FUNC;
					 Error_or_Warning_Proc("11.01.17", ERROR_OCCURED, appl_error_or_warning_flag);
					 return appl_error_or_warning_flag;
				 }
				 Set_Data_Devs_Src_Allow(DEV_INPUT_TYPE, CUR_DATA_ID_ALL_SRC_OF_SPEC_OPER, cur_data_devs_src_allow);
		         if((ret_status = Cur_Data_ID_Devs_Src_Basic_Oper_Func(INPUT_DEV_ENABLE_OPER_FUNC, DEV_INPUT_TYPE, cur_data_devs_src_allow)) != SUCCESS)
		         {
		             appl_error_or_warning_flag = ERR_DEV_OPER_ENABLE_FUNC;
					 Error_or_Warning_Proc("11.01.18", ERROR_OCCURED, appl_error_or_warning_flag);
					 return appl_error_or_warning_flag;					 
	             }	
				 auth_fsm_state = ACCOUNT_FSM; 
         break;      					
		 case ENTER_SW_CODE:
		   /*  Process for valid Enter sw stroke */			     
         break;
         case BACKSPACE_SW_CODE:			  
            /* Process for valid Backspace */
			#ifdef SHOULD_REMOVE
				UART_Transmit_Str(TRACE_UART_CH_ID, "\r BS_SW_CODE ");						         
		    #endif
			     lcd_or_keyboard_dev_id.dev_id = OUTPUT_DEV_ID_LCD;
		         if((ret_status = Data_ID_Src_Spec_Dev_Find_Dev_Ch_ID(cur_data_id, &lcd_or_keyboard_dev_id, DEV_OUTPUT_TYPE))!= SUCCESS)
				 {
					 appl_error_or_warning_flag = ERR_LCD_NOT_DATA_SRC;
					 Error_or_Warning_Proc("11.01.19", ERROR_OCCURED, appl_error_or_warning_flag);
					 return appl_error_or_warning_flag;
				 }
				
			     if((ret_status = Appl_Data_Retrieve_Para(cur_data_id, DATA_RETRIEVE_STATUS_NUM_CHARS_READ, &retrieve_data_str_len)) != SUCCESS)
				 {
						 appl_error_or_warning_flag = ERR_APPL_DATA_RETRIEVE;
					     Error_or_Warning_Proc("11.01.20", ERROR_OCCURED, appl_error_or_warning_flag);
					     return appl_error_or_warning_flag; 
				 }
                 if(retrieve_data_str_len >= 0)
				 {
					 keyboard_part_and_oper_data = LCD_INPUT_LOC << LCD_CTRL_LOC_TYPE_DATA_POS; 
					 if((ret_status = LCD_Loc_Ctrl_Proc(lcd_or_keyboard_dev_id.dev_ch_id, keyboard_part_and_oper_data, BACKSPACE_CHAR)) != SUCCESS)
					 {
						 appl_error_or_warning_flag = ERR_LCD_LOC_CTRL;
					     Error_or_Warning_Proc("11.01.21", ERROR_OCCURED, appl_error_or_warning_flag);
					     return appl_error_or_warning_flag; 
					 }
				 } 
                			 
            break;
            case RESET_SW_CODE:
			   #ifdef SHOULD_REMOVE
				  UART_Transmit_Str(TRACE_UART_CH_ID, "\r RESET_SW_CODE ");						         
		       #endif
			   if((ret_status = Appl_Reset(RESET_APPL)) != SUCCESS)
			   {
				    appl_error_or_warning_flag = ERR_RESET_OPER;
				    Error_or_Warning_Proc("11.01.22", ERROR_OCCURED, appl_error_or_warning_flag);
					return appl_error_or_warning_flag;	
			   }	   
             break;
             default:
			     appl_error_or_warning_flag = ERR_FORMAT_INVALID;
				 Error_or_Warning_Proc("11.01.23", ERROR_OCCURED, appl_error_or_warning_flag);
				 return appl_error_or_warning_flag;	
	     }		 
		return SUCCESS;
}

/*------------------------------------------------------------*
FUNCTION NAME  : Auth_Fsm_Proc

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 11.02

BUGS           :    
-*------------------------------------------------------------*/ 
uint8_t Auth_Fsm_Proc(const uint8_t input_read_status)
{
	const char default_account_str[] = "56789", enter_pin_msg_disp_str[] = "Enter PIN", default_pin_str[] = "1234"; 
	const char reenter_acc_msg_disp_str[]= "Reenter Account", reenter_pin_msg_disp_str[] = "Reenter PIN";  
	char retrieved_read_data_str[DATA_MAX_NUM_ALLOCATED_CHARS];
	lcd_point_config_t lcd_data_point_config;
	dev_id_t lcd_or_keyboard_dev_id, cur_data_devs_src_allow[1] = { CUR_DATA_ID_ALL_SRC_OF_SPEC_OPER};	
	uint8_t ret_status;
	
    switch(auth_fsm_state)
    {
	   case INITIAL_FSM:
	      ret_status = SW_Oper(ACCOUNT_SW_IO_CH, DEV_READ_OPER);
	      switch(ret_status)
	      {	
              case SUCCESS:
		        if((ret_status =  After_Switch_Stoke_Proc(ACCOUNT_SW_CODE)) != SUCCESS)
		        {
		  	       appl_error_or_warning_flag = ERR_AFTER_SW_PRESS_STROKE;
			       Error_or_Warning_Proc("11.05.11", ERROR_OCCURED, appl_error_or_warning_flag);
			       return appl_error_or_warning_flag; 
		        }
	    	  break;  
		      case SW_OR_KEY_NOT_PRESSED:
		      case WARN_CUR_DATA_ID_DEV_NO_ACCESS:
		      case WARN_CUR_DATA_ID_DEV_DISABLED: 
              break;
              default:			   
		         appl_error_or_warning_flag = ERR_DEV_OPER_READ_FUNC;
		         Error_or_Warning_Proc("11.05.12", ERROR_OCCURED, appl_error_or_warning_flag);
		        return appl_error_or_warning_flag;                        
           }
	   break;	   
	   case ACCOUNT_FSM:
	     switch(input_read_status)
		 {
			 case CUR_DATA_ID_UNTIL_LAST_TRY_COMPLETE_READ_AND_READY_PROCESS:
             case CUR_DATA_ID_LAST_TRY_COMPLETE_READ_AND_READY_PROCESS:			 
  	           lcd_or_keyboard_dev_id.dev_id = OUTPUT_DEV_ID_LCD;
		       if((ret_status = Data_ID_Src_Spec_Dev_Find_Dev_Ch_ID(cur_data_id, &lcd_or_keyboard_dev_id, DEV_OUTPUT_TYPE))!= SUCCESS)
		       {
			     appl_error_or_warning_flag = ERR_LCD_NOT_DATA_SRC;
		         Error_or_Warning_Proc("11.02.01", ERROR_OCCURED, appl_error_or_warning_flag);
			     return appl_error_or_warning_flag;
	           }
		       if((ret_status = LCD_Clear_Screen(lcd_or_keyboard_dev_id.dev_ch_id)) != SUCCESS)
		       {
			      appl_error_or_warning_flag = ERR_LCD_WRITE_OPER;
			      Error_or_Warning_Proc("11.02.02", ERROR_OCCURED, appl_error_or_warning_flag);
			      return appl_error_or_warning_flag;
		       }	
			   if((ret_status = Appl_Data_Retrieve_Para(cur_data_id, DATA_RETRIEVE_STATUS_DATA_STR, retrieved_read_data_str )) != SUCCESS)
			   {
				  appl_error_or_warning_flag = ERR_APPL_DATA_RETRIEVE;
				  Error_or_Warning_Proc("11.02.03", ERROR_OCCURED, appl_error_or_warning_flag);
				  return appl_error_or_warning_flag; 
			   }	
               if(strcmp(retrieved_read_data_str, default_account_str)== 0)
               {	
                   Reset_Data_ID_Status(cur_data_id, DATA_ID_RESET_WHOLE_STATUS);	
				   auth_fsm_state = PIN_FSM; 
		           if((ret_status = Next_Data_Conf_Parameter(DATA_ID_PIN)) != SUCCESS)
			       {
				      appl_error_or_warning_flag = ERR_NEXT_DATA_CONF;
				      Error_or_Warning_Proc("11.02.04", ERROR_OCCURED, appl_error_or_warning_flag);
				      return appl_error_or_warning_flag; 
			       }				       
		           Set_Data_Devs_Src_Allow(DEV_OUTPUT_TYPE, CUR_DATA_ID_ALL_SRC_OF_SPEC_OPER, cur_data_devs_src_allow);
		           if((ret_status = Cur_Data_ID_Devs_Src_Basic_Oper_Func(OUTPUT_DEV_ENABLE_OPER_FUNC, DEV_OUTPUT_TYPE, cur_data_devs_src_allow)) != SUCCESS)
		           {
		               appl_error_or_warning_flag = ERR_DEV_OPER_ENABLE_FUNC;
				       Error_or_Warning_Proc("11.02.05", ERROR_OCCURED, appl_error_or_warning_flag);
				       return appl_error_or_warning_flag; 
	               }
				   lcd_or_keyboard_dev_id.dev_id = OUTPUT_DEV_ID_LCD;
		           if((ret_status = Data_ID_Src_Spec_Dev_Find_Dev_Ch_ID(cur_data_id, &lcd_or_keyboard_dev_id, DEV_OUTPUT_TYPE))!= SUCCESS)
		           {
			          appl_error_or_warning_flag = ERR_LCD_NOT_DATA_SRC;
		              Error_or_Warning_Proc("11.02.06", ERROR_OCCURED, appl_error_or_warning_flag);
			          return appl_error_or_warning_flag;
	               }				 		     
			       if((ret_status = LCD_Disp_Goto_XY(lcd_or_keyboard_dev_id.dev_ch_id, PIN_MSG_LINE_NUM, PIN_MSG_START_COL_NUM)) != SUCCESS)
				   {
				  	  appl_error_or_warning_flag = ERR_LCD_DISP_GOTO_XY;
					  Error_or_Warning_Proc("11.02.07", ERROR_OCCURED, appl_error_or_warning_flag);
					  return appl_error_or_warning_flag; 
				   }
                   if((ret_status = LCD_Disp_Str(lcd_or_keyboard_dev_id.dev_ch_id, enter_pin_msg_disp_str)) != SUCCESS)
				   {
				      appl_error_or_warning_flag = ERR_LCD_WRITE_OPER;
					  Error_or_Warning_Proc("11.02.08", ERROR_OCCURED, appl_error_or_warning_flag);
					  return appl_error_or_warning_flag; 
				   }				 
				   lcd_data_point_config.cur_data_start_point_num.line_num_or_index = PIN_ENTRY_START_LINE_NUM;
				   lcd_data_point_config.cur_data_start_point_num.col_num_or_index = PIN_ENTRY_START_COL_NUM;
				   if((ret_status = Appl_Data_Retrieve_Para(cur_data_id, DATA_RETRIEVE_CTRL_REQ_MAX_DATA_CHARS, &lcd_data_point_config.max_num_chars_config)) != SUCCESS)
				   {
						 appl_error_or_warning_flag = ERR_APPL_DATA_RETRIEVE;
					     Error_or_Warning_Proc("11.02.09", ERROR_OCCURED, appl_error_or_warning_flag);
					     return appl_error_or_warning_flag; 
				   }	
                   #if( NUM_CHARS_INPUTDATA == GIVEN_CHARS_MAX_CONFIG_LINES_AND_COLS)										
                    ret_status = LCD_Cur_Data_By_NumChars_Calc_Para(lcd_or_keyboard_dev_id.dev_ch_id, &lcd_data_point_config);
                  #elif(NUM_CHARS_INPUTDATA == GIVEN_XY_MAX_CONFIG_LINES_AND_COLS)
                  /* ACCOUNT INPUT DATA max num of input account chars = num of chars from start pos (entry start line, entry start col) till end of that line */ 
			         lcd_data_point_config.next_data_start_point_num.line_num_or_index = PIN_ENTRY_START_LINE_NUM + 1 ;
				     lcd_data_point_config.next_data_start_point_num.col_num_or_index = NUM_COL1;
                     ret_status = LCD_Cur_Data_By_XY_Calc_Para(lcd_or_keyboard_dev_id.dev_ch_id, &lcd_data_point_config );
                  #else 
                	  /*NUM_CHARS_INPUTDATA = GIVEN_CHARS_MAX_XY */
                  /* ACCOUNT INPUT DATA's max num of input account chars = min(num of chars from start pos (entry start line, entry start col) till end of that line, MAX_ACCOUNT_NUM_CHARS ) */
				    lcd_data_point_config.next_data_start_point_num.line_num_or_index = PIN_ENTRY_START_LINE_NUM + 1;
				    lcd_data_point_config.next_data_start_point_num.col_num_or_index = NUM_COL1;
					if((ret_status = Appl_Data_Retrieve_Para(cur_data_id, DATA_RETRIEVE_CTRL_REQ_MAX_DATA_CHARS, &lcd_data_point_config.max_num_chars_config) != SUCCESS)
					{
						 appl_error_or_warning_flag = ERR_APPL_DATA_RETRIEVE;
					     Error_or_Warning_Proc("11.02.10", ERROR_OCCURED, appl_error_or_warning_flag);
					     return appl_error_or_warning_flag; 
					}	
                 	ret_status = LCD_Cur_Data_By_NumChars_and_XY_Calc_Para(lcd_or_keyboard_dev_id.dev_ch_id, &lcd_data_point_config); 
                 #endif
				    switch(ret_status)
				    {
					   case WARN_LCD_ALLOC_LESS_THAN_CONFIG_CHARS:
					   case SUCCESS:
					      if((ret_status = Data_ID_Set_Para(cur_data_id, lcd_status[lcd_or_keyboard_dev_id.dev_ch_id].cur_data_lcd_para.max_num_chars_alloc + 1)) != SUCCESS)
						  {
							  appl_error_or_warning_flag = ERR_DATA_ID_CONF;
					          Error_or_Warning_Proc("11.02.11", ERROR_OCCURED, appl_error_or_warning_flag);
					          return appl_error_or_warning_flag; 
						  }
					   break;
                       default:
                  	     appl_error_or_warning_flag = ERR_LCD_DATA_POINT_CONFIG;
					     Error_or_Warning_Proc("11.02.12", ERROR_OCCURED, appl_error_or_warning_flag);
					     return appl_error_or_warning_flag; 			 
				    }
				    if((ret_status = LCD_Input_Goto_XY(lcd_or_keyboard_dev_id.dev_ch_id, PIN_ENTRY_START_LINE_NUM, PIN_ENTRY_START_COL_NUM)) != SUCCESS)
				    {
					   appl_error_or_warning_flag = ERR_LCD_INPUT_GOTO_XY;
					   Error_or_Warning_Proc("11.02.13", ERROR_OCCURED, appl_error_or_warning_flag);
					   return appl_error_or_warning_flag;
				    }
                    if((ret_status = LCD_Write_Command(lcd_or_keyboard_dev_id.dev_ch_id, 0x0E)) != SUCCESS)
				    {
					   appl_error_or_warning_flag = ERR_LCD_WRITE_OPER;
					   Error_or_Warning_Proc("11.02.14", ERROR_OCCURED, appl_error_or_warning_flag);
					   return appl_error_or_warning_flag;
				    }
					lcd_or_keyboard_dev_id.dev_id = INPUT_DEV_ID_KEYBOARD;
					if((ret_status = Data_ID_Src_Spec_Dev_Find_Dev_Ch_ID(cur_data_id, &lcd_or_keyboard_dev_id, DEV_INPUT_TYPE))!= SUCCESS)
				    {
				    	 appl_error_or_warning_flag = ERR_LCD_NOT_DATA_SRC;
					     Error_or_Warning_Proc("11.01.14", ERROR_OCCURED, appl_error_or_warning_flag);
					     return appl_error_or_warning_flag;
				    }
				    if((ret_status = Keyboard_Keypad_Oper(lcd_or_keyboard_dev_id.dev_ch_id, DEV_ENABLE_OPER)) != SUCCESS)
				    {
				    	 appl_error_or_warning_flag = ERR_DEV_OPER_ENABLE_FUNC;
				    	 Error_or_Warning_Proc("11.01.15", ERROR_OCCURED, appl_error_or_warning_flag);
					     return appl_error_or_warning_flag;
				    }
                    Set_Data_Devs_Src_Allow(DEV_INPUT_TYPE, CUR_DATA_ID_ALL_SRC_OF_SPEC_OPER, cur_data_devs_src_allow);
		            if((ret_status = Cur_Data_ID_Devs_Src_Basic_Oper_Func(INPUT_DEV_ENABLE_OPER_FUNC, DEV_INPUT_TYPE, cur_data_devs_src_allow)) != SUCCESS)
		            {
		               appl_error_or_warning_flag = ERR_DEV_OPER_ENABLE_FUNC;
					   Error_or_Warning_Proc("11.02.15", ERROR_OCCURED, appl_error_or_warning_flag);
					   return appl_error_or_warning_flag;					 
	                }                                  
			    }
			    else
			    {	
			       if(input_read_status == CUR_DATA_ID_UNTIL_LAST_TRY_COMPLETE_READ_AND_READY_PROCESS)
				   {
		               Reset_Data_ID_Status(cur_data_id, DATA_ID_RESET_RETRY_STATUS);
                       if((ret_status = LCD_Disp_Goto_XY(lcd_or_keyboard_dev_id.dev_ch_id, ACCOUNT_MSG_LINE_NUM, ACCOUNT_MSG_START_COL_NUM)) != SUCCESS)				
				       {
				        	appl_error_or_warning_flag = ERR_LCD_DISP_GOTO_XY;
				        	Error_or_Warning_Proc("11.02.16", ERROR_OCCURED, appl_error_or_warning_flag);
					        return appl_error_or_warning_flag;
				       }
				       if((ret_status = LCD_Disp_Str(lcd_or_keyboard_dev_id.dev_ch_id, reenter_acc_msg_disp_str)) != SUCCESS)
				       {
					      appl_error_or_warning_flag = ERR_LCD_WRITE_OPER;
					      Error_or_Warning_Proc("11.02.17", ERROR_OCCURED, appl_error_or_warning_flag);
					      return appl_error_or_warning_flag; 
				       }
                       if((ret_status = LCD_Input_Goto_XY(lcd_or_keyboard_dev_id.dev_ch_id, ACCOUNT_ENTRY_START_LINE_NUM, ACCOUNT_ENTRY_START_COL_NUM)) != SUCCESS)
			           {
					      appl_error_or_warning_flag = ERR_LCD_INPUT_GOTO_XY;
					      Error_or_Warning_Proc("11.02.18", ERROR_OCCURED, appl_error_or_warning_flag);
					      return appl_error_or_warning_flag;
				       }
				      // insert cursor on at cur_input_lcd_loc
                      if((ret_status = LCD_Write_Command(lcd_or_keyboard_dev_id.dev_ch_id, 0x0E)) != SUCCESS)
				      {
					     appl_error_or_warning_flag = ERR_LCD_WRITE_OPER;
					     Error_or_Warning_Proc("11.02.19", ERROR_OCCURED, appl_error_or_warning_flag);
					     return appl_error_or_warning_flag;
				      }
			       }
				   else
				   {
					  Set_Auth_Status_Disp_Fsm(INVALID_ACCOUNT);
				   }
			    }
             break;
	         case CUR_DATA_ID_INPUT_MAX_TRIED: 
                Set_Auth_Status_Disp_Fsm(INVALID_ACCOUNT);
             break;
		  }
	   break;
       case PIN_FSM:
	     switch(input_read_status)
		 {
			 case CUR_DATA_ID_UNTIL_LAST_TRY_COMPLETE_READ_AND_READY_PROCESS:
			 case CUR_DATA_ID_LAST_TRY_COMPLETE_READ_AND_READY_PROCESS:		              			 
  	           lcd_or_keyboard_dev_id.dev_id = OUTPUT_DEV_ID_LCD;
		       if((ret_status = Data_ID_Src_Spec_Dev_Find_Dev_Ch_ID(cur_data_id, &lcd_or_keyboard_dev_id, DEV_OUTPUT_TYPE))!= SUCCESS)
		       {
			     appl_error_or_warning_flag = ERR_LCD_NOT_DATA_SRC;
		         Error_or_Warning_Proc("11.02.20", ERROR_OCCURED, appl_error_or_warning_flag);
			     return appl_error_or_warning_flag;
	           }
		       if((ret_status = LCD_Clear_Screen(lcd_or_keyboard_dev_id.dev_ch_id)) != SUCCESS)
		       {
			      appl_error_or_warning_flag = ERR_LCD_WRITE_OPER;
			      Error_or_Warning_Proc("11.02.21", ERROR_OCCURED, appl_error_or_warning_flag);
			      return appl_error_or_warning_flag;
		       }	
			   if((ret_status = Appl_Data_Retrieve_Para(cur_data_id, DATA_RETRIEVE_STATUS_DATA_STR, retrieved_read_data_str )) != SUCCESS)
			   {
				  appl_error_or_warning_flag = ERR_APPL_DATA_RETRIEVE;
				  Error_or_Warning_Proc("11.02.22", ERROR_OCCURED, appl_error_or_warning_flag);
				  return appl_error_or_warning_flag; 
			   } 
			   if(strcmp(retrieved_read_data_str, default_pin_str)== 0)
               {
				   /* start up for AUTH_SUCCESS_FSM  */
				    Set_Auth_Status_Disp_Fsm(AUTH_SUCCESS);                  
				    auth_fsm_state = AUTH_SUCCESS_FSM; 
               } 
               else
               {
				   if(input_read_status == CUR_DATA_ID_UNTIL_LAST_TRY_COMPLETE_READ_AND_READY_PROCESS)
				   {
			    	   Reset_Data_ID_Status(cur_data_id, DATA_ID_RESET_RETRY_STATUS);					 
                       if((ret_status = LCD_Disp_Goto_XY(lcd_or_keyboard_dev_id.dev_ch_id, PIN_MSG_LINE_NUM, PIN_MSG_START_COL_NUM)) != SUCCESS)				
				       {
				        	appl_error_or_warning_flag = ERR_LCD_DISP_GOTO_XY;
				    	    Error_or_Warning_Proc("11.02.23", ERROR_OCCURED, appl_error_or_warning_flag);
					        return appl_error_or_warning_flag;
				       }
				       if((ret_status = LCD_Disp_Str(lcd_or_keyboard_dev_id.dev_ch_id, reenter_pin_msg_disp_str)) != SUCCESS)
				       {
					      appl_error_or_warning_flag = ERR_LCD_WRITE_OPER;
					      Error_or_Warning_Proc("11.02.24", ERROR_OCCURED, appl_error_or_warning_flag);
					      return appl_error_or_warning_flag; 
				       }
                       if((ret_status = LCD_Input_Goto_XY(lcd_or_keyboard_dev_id.dev_ch_id, PIN_ENTRY_START_LINE_NUM, PIN_ENTRY_START_COL_NUM)) != SUCCESS)
			           {
					      appl_error_or_warning_flag = ERR_LCD_INPUT_GOTO_XY;
					      Error_or_Warning_Proc("11.02.25", ERROR_OCCURED, appl_error_or_warning_flag);
					      return appl_error_or_warning_flag;
				       }  
				       // insert cursor on at lcd_cur_input_loc
                       if((ret_status = LCD_Write_Command(lcd_or_keyboard_dev_id.dev_ch_id, 0x0E)) != SUCCESS)
				       {
					      appl_error_or_warning_flag = ERR_LCD_WRITE_OPER;
					      Error_or_Warning_Proc("11.02.26", ERROR_OCCURED, appl_error_or_warning_flag);
					      return appl_error_or_warning_flag;
				       }
				       lcd_or_keyboard_dev_id.dev_id = INPUT_DEV_ID_KEYBOARD;
					   if((ret_status = Data_ID_Src_Spec_Dev_Find_Dev_Ch_ID(cur_data_id, &lcd_or_keyboard_dev_id, DEV_INPUT_TYPE))!= SUCCESS)
				       {
				        	 appl_error_or_warning_flag = ERR_LCD_NOT_DATA_SRC;
					         Error_or_Warning_Proc("11.02.27", ERROR_OCCURED, appl_error_or_warning_flag);
					         return appl_error_or_warning_flag;
				       }
				       if((ret_status = Keyboard_Keypad_Oper(lcd_or_keyboard_dev_id.dev_ch_id, DEV_ENABLE_OPER)) != SUCCESS)
				       {
				      	   appl_error_or_warning_flag = ERR_DEV_OPER_ENABLE_FUNC;
				    	   Error_or_Warning_Proc("11.02.28", ERROR_OCCURED, appl_error_or_warning_flag);
					       return appl_error_or_warning_flag;
				      }
                      Set_Data_Devs_Src_Allow(DEV_INPUT_TYPE, CUR_DATA_ID_ALL_SRC_OF_SPEC_OPER, cur_data_devs_src_allow);
		              if((ret_status = Cur_Data_ID_Devs_Src_Basic_Oper_Func(INPUT_DEV_ENABLE_OPER_FUNC, DEV_INPUT_TYPE, cur_data_devs_src_allow)) != SUCCESS)
		              {
		                 appl_error_or_warning_flag = ERR_DEV_OPER_ENABLE_FUNC;
					     Error_or_Warning_Proc("11.02.29", ERROR_OCCURED, appl_error_or_warning_flag);
					     return appl_error_or_warning_flag;					 
	                  }                              
			       }
				   else
				   {
					    Set_Auth_Status_Disp_Fsm(INVALID_PIN);
				   }
			   }
			 break;
             case CUR_DATA_ID_INPUT_MAX_TRIED: 
                Set_Auth_Status_Disp_Fsm(INVALID_PIN); 
             break; 			 
		 }       
       break; 
       case  AUTH_SUCCESS_FSM:	     
       break; 
       default:
	      /* error: invalid auth fsm state */
         appl_error_or_warning_flag = ERR_FORMAT_INVALID;
		 Error_or_Warning_Proc("11.02.30", ERROR_OCCURED, appl_error_or_warning_flag);
		 return appl_error_or_warning_flag;
    } 
    return SUCCESS;	
}

/*------------------------------------------------------------*
FUNCTION NAME  : Disp_Status_Fsm

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 11.03

BUGS           :    
-*------------------------------------------------------------*/ 
uint8_t Disp_Status_Fsm(void)
{
	const char auth_success_msg_disp_str[] = "Successful Auth", incorrect_auth_msg_disp_str[] = "Visit Bank";    
    const char max_acc_try_msg_disp_str[]=  "Max Acc Exceed", max_pin_try_msg_disp_str[] = "Max PIN Exceed";
	dev_id_t lcd_dev_id, cur_data_devs_src_allow[1] = { CUR_DATA_ID_ALL_SRC_OF_SPEC_OPER};	
	uint8_t ret_status;	
	 
	 if((ret_status = Next_Data_Conf_Parameter(DATA_ID_STATUS)) != SUCCESS)
	 {
	     appl_error_or_warning_flag = ERR_NEXT_DATA_CONF;
	     Error_or_Warning_Proc("11.03.01", ERROR_OCCURED, appl_error_or_warning_flag);
	     return appl_error_or_warning_flag; 
	 }				       
	 Set_Data_Devs_Src_Allow(DEV_OUTPUT_TYPE, CUR_DATA_ID_ALL_SRC_OF_SPEC_OPER, cur_data_devs_src_allow);
	 if((ret_status = Cur_Data_ID_Devs_Src_Basic_Oper_Func(OUTPUT_DEV_ENABLE_OPER_FUNC, DEV_OUTPUT_TYPE, cur_data_devs_src_allow)) != SUCCESS)
	 {
	      appl_error_or_warning_flag = ERR_DEV_OPER_ENABLE_FUNC;
	      Error_or_Warning_Proc("11.03.02", ERROR_OCCURED, appl_error_or_warning_flag);
	      return appl_error_or_warning_flag; 
	 }
	 lcd_dev_id.dev_id = OUTPUT_DEV_ID_LCD;
	 if((ret_status = Data_ID_Src_Spec_Dev_Find_Dev_Ch_ID(cur_data_id, &lcd_dev_id, DEV_OUTPUT_TYPE))!= SUCCESS)
	 {
	      appl_error_or_warning_flag = ERR_LCD_NOT_DATA_SRC;
	      Error_or_Warning_Proc("11.03.03", ERROR_OCCURED, appl_error_or_warning_flag);
	      return appl_error_or_warning_flag;
	 }	
     if((ret_status = LCD_Clear_Screen(lcd_dev_id.dev_ch_id)) != SUCCESS)
	 {
	     appl_error_or_warning_flag = ERR_LCD_WRITE_OPER;
	     Error_or_Warning_Proc("11.03.04", ERROR_OCCURED, appl_error_or_warning_flag);
	     return appl_error_or_warning_flag;
	 }	
	  #ifdef SHOULD_REMOVE
	    if((ret_status = LCD_Write_Command(lcd_dev_id.dev_ch_id, 0x0E)) != SUCCESS)
	    {
	       appl_error_or_warning_flag = ERR_LCD_WRITE_OPER;
	       Error_or_Warning_Proc("11.03.05", ERROR_OCCURED, appl_error_or_warning_flag);
	       return appl_error_or_warning_flag;
	   }
	  #endif
       #ifdef SHOULD_CALL	
       if((ret_status = LCD_Write_Command(lcd_dev_id.dev_ch_id, 0x0C)) != SUCCESS)
	   {
	       appl_error_or_warning_flag = ERR_LCD_WRITE_OPER;
	       Error_or_Warning_Proc("11.03.06", ERROR_OCCURED, appl_error_or_warning_flag);
	       return appl_error_or_warning_flag;
	   }	     
	   #endif
	   
	   switch(status_disp_fsm)
       {
          case INVALID_ACCOUNT:
		     if((ret_status = LCD_Disp_Goto_XY(lcd_dev_id.dev_ch_id, FAILED_AUTH_REASON_LINE_NUM, NUM_COL1 )) != SUCCESS)
			 {
				 appl_error_or_warning_flag = ERR_LCD_DISP_GOTO_XY;
				 Error_or_Warning_Proc("11.03.07", ERROR_OCCURED, appl_error_or_warning_flag);
				 return appl_error_or_warning_flag;
			 }
			 if((ret_status = LCD_Disp_Str(lcd_dev_id.dev_ch_id, max_acc_try_msg_disp_str)) != SUCCESS)
			 {
			     appl_error_or_warning_flag = ERR_LCD_WRITE_OPER;
			     Error_or_Warning_Proc("11.03.08", ERROR_OCCURED, appl_error_or_warning_flag);
			     return appl_error_or_warning_flag; 
			 }
			 if((ret_status = LCD_Disp_Goto_XY(lcd_dev_id.dev_ch_id, FAILED_AUTH_LINE_NUM, NUM_COL1)) != SUCCESS)
			 {
				  appl_error_or_warning_flag = ERR_LCD_DISP_GOTO_XY;
				  Error_or_Warning_Proc("11.03.09", ERROR_OCCURED, appl_error_or_warning_flag);
				  return appl_error_or_warning_flag;
			 }				 
			 if((ret_status = LCD_Disp_Str(lcd_dev_id.dev_ch_id, incorrect_auth_msg_disp_str)) != SUCCESS)
			 {
				 appl_error_or_warning_flag = ERR_LCD_WRITE_OPER;
			     Error_or_Warning_Proc("11.03.10", ERROR_OCCURED, appl_error_or_warning_flag);
			     return appl_error_or_warning_flag;
			 }
             break;
         case INVALID_PIN:
		     if((ret_status = LCD_Disp_Goto_XY(lcd_dev_id.dev_ch_id, FAILED_AUTH_REASON_LINE_NUM, NUM_COL1 )) != SUCCESS)
			 {
				 appl_error_or_warning_flag = ERR_LCD_DISP_GOTO_XY;
				 Error_or_Warning_Proc("11.03.11", ERROR_OCCURED, appl_error_or_warning_flag);
				 return appl_error_or_warning_flag;
			 }
             if((ret_status = LCD_Disp_Str(lcd_dev_id.dev_ch_id, max_pin_try_msg_disp_str)) != SUCCESS)
			 {
			     appl_error_or_warning_flag = ERR_LCD_WRITE_OPER;
			     Error_or_Warning_Proc("11.03.12", ERROR_OCCURED, appl_error_or_warning_flag);
			     return appl_error_or_warning_flag; 
			 }
			 if((ret_status = LCD_Disp_Goto_XY(lcd_dev_id.dev_ch_id, FAILED_AUTH_LINE_NUM, NUM_COL1)) != SUCCESS)
			 {
				  appl_error_or_warning_flag = ERR_LCD_DISP_GOTO_XY;
				  Error_or_Warning_Proc("11.03.13", ERROR_OCCURED, appl_error_or_warning_flag);
				  return appl_error_or_warning_flag;
			 }				 
			 if((ret_status = LCD_Disp_Str(lcd_dev_id.dev_ch_id, incorrect_auth_msg_disp_str)) != SUCCESS)
			 {
				 appl_error_or_warning_flag = ERR_LCD_WRITE_OPER;
			     Error_or_Warning_Proc("11.03.14", ERROR_OCCURED, appl_error_or_warning_flag);
			     return appl_error_or_warning_flag;
			 }
             break;
		#ifdef UNUSED	 
	     case TIMEOUT_LONG_KEY_PRESS:
		    if((ret_status = LCD_Disp_Goto_XY(lcd_dev_id.dev_ch_id, FAILED_AUTH_REASON_LINE_NUM, NUM_COL1 )) != SUCCESS)
			{
				 appl_error_or_warning_flag = ERR_LCD_DISP_GOTO_XY;
				 Error_or_Warning_Proc("11.03.15", ERROR_OCCURED, appl_error_or_warning_flag);
				 return appl_error_or_warning_flag;
			}
			if((ret_status = LCD_Disp_Str(lcd_dev_id.dev_ch_id, auth_timeout_msg_disp)) != SUCCESS)
			 {
			     appl_error_or_warning_flag = ERR_LCD_WRITE_OPER;
			     Error_or_Warning_Proc("11.03.16", ERROR_OCCURED, appl_error_or_warning_flag);
			     return appl_error_or_warning_flag; 
			 }
			 if((ret_status = LCD_Disp_Goto_XY(lcd_dev_id.dev_ch_id, FAILED_AUTH_REASON_LINE_NUM, start_col_reason_timeout_msg_disp )) != SUCCESS)
			{
				 appl_error_or_warning_flag = ERR_LCD_DISP_GOTO_XY;
				 Error_or_Warning_Proc("11.03.17", ERROR_OCCURED, appl_error_or_warning_flag);
				 return appl_error_or_warning_flag;
			}
			if((ret_status = LCD_Disp_Str(lcd_dev_id.dev_ch_id, error_long_key_press_msg_disp)) != SUCCESS)
			{
			     appl_error_or_warning_flag = ERR_LCD_WRITE_OPER;
			     Error_or_Warning_Proc("11.03.18", ERROR_OCCURED, appl_error_or_warning_flag);
			     return appl_error_or_warning_flag; 
			}
			 if((ret_status = LCD_Disp_Goto_XY(lcd_dev_id.dev_ch_id, FAILED_AUTH_LINE_NUM, NUM_COL1)) != SUCCESS)
			 {
				  appl_error_or_warning_flag = ERR_LCD_DISP_GOTO_XY;
				  Error_or_Warning_Proc("11.03.19", ERROR_OCCURED, appl_error_or_warning_flag);
				  return appl_error_or_warning_flag;
			 }				 
			 if((ret_status = LCD_Disp_Str(lcd_dev_id.dev_ch_id, incorrect_auth_msg_disp_str)) != SUCCESS)
			 {
				 appl_error_or_warning_flag = ERR_LCD_WRITE_OPER;
			     Error_or_Warning_Proc("11.03.20", ERROR_OCCURED, appl_error_or_warning_flag);
			     return appl_error_or_warning_flag;
			 }				 	
             break;
	     case TIMEOUT_NO_KEY_PRESS:	
           	if((ret_status = LCD_Disp_Goto_XY(lcd_dev_id.dev_ch_id, FAILED_AUTH_REASON_LINE_NUM, NUM_COL1 )) != SUCCESS)
			{
				 appl_error_or_warning_flag = ERR_LCD_DISP_GOTO_XY;
				 Error_or_Warning_Proc("11.03.21", ERROR_OCCURED, appl_error_or_warning_flag);
				 return appl_error_or_warning_flag;
			}
			if((ret_status = LCD_Disp_Str(lcd_dev_id.dev_ch_id, auth_timeout_msg_disp)) != SUCCESS)
			 {
			     appl_error_or_warning_flag = ERR_LCD_WRITE_OPER;
			     Error_or_Warning_Proc("11.03.22", ERROR_OCCURED, appl_error_or_warning_flag);
			     return appl_error_or_warning_flag; 
			 }
			 if((ret_status = LCD_Disp_Goto_XY(lcd_dev_id.dev_ch_id, FAILED_AUTH_REASON_LINE_NUM, start_col_reason_timeout_msg_disp )) != SUCCESS)
			{
				 appl_error_or_warning_flag = ERR_LCD_DISP_GOTO_XY;
				 Error_or_Warning_Proc("11.03.23", ERROR_OCCURED, appl_error_or_warning_flag);
				 return appl_error_or_warning_flag;
			}
			if((ret_status = LCD_Disp_Str(lcd_dev_id.dev_ch_id, error_no_key_press_msg_disp)) != SUCCESS)
			{
			     appl_error_or_warning_flag = ERR_LCD_WRITE_OPER;
			     Error_or_Warning_Proc("11.03.24", ERROR_OCCURED, appl_error_or_warning_flag);
			     return appl_error_or_warning_flag; 
			}
			 if((ret_status = LCD_Disp_Goto_XY(lcd_dev_id.dev_ch_id, FAILED_AUTH_LINE_NUM, NUM_COL1)) != SUCCESS)
			 {
				  appl_error_or_warning_flag = ERR_LCD_DISP_GOTO_XY;
				  Error_or_Warning_Proc("11.03.25", ERROR_OCCURED, appl_error_or_warning_flag);
				  return appl_error_or_warning_flag;
			 }				 
			 if((ret_status = LCD_Disp_Str(lcd_dev_id.dev_ch_id, incorrect_auth_msg_disp_str)) != SUCCESS)
			 {
				 appl_error_or_warning_flag = ERR_LCD_WRITE_OPER;
			     Error_or_Warning_Proc("11.03.26", ERROR_OCCURED, appl_error_or_warning_flag);
			     return appl_error_or_warning_flag;
			 }				
			break;
		#endif	
         case AUTH_SUCCESS:
		    if((ret_status = LCD_Disp_Goto_XY(lcd_dev_id.dev_ch_id, SUCCESS_AUTH_LINE_NUM, NUM_COL1 )) != SUCCESS)
			{
				 appl_error_or_warning_flag = ERR_LCD_DISP_GOTO_XY;
				 Error_or_Warning_Proc("11.03.27", ERROR_OCCURED, appl_error_or_warning_flag);
				 return appl_error_or_warning_flag;
			}
			if((ret_status = LCD_Disp_Str(lcd_dev_id.dev_ch_id, auth_success_msg_disp_str )) != SUCCESS)
			{
			     appl_error_or_warning_flag = ERR_LCD_WRITE_OPER;
			     Error_or_Warning_Proc("11.03.28", ERROR_OCCURED, appl_error_or_warning_flag);
			     return appl_error_or_warning_flag; 
			}		    
			break;
		 default:
            /* error: invalid auth disp status */   
            appl_error_or_warning_flag = ERR_FORMAT_INVALID;
	       Error_or_Warning_Proc("11.03.29", ERROR_OCCURED, appl_error_or_warning_flag);
	       return appl_error_or_warning_flag;
      }	   
   Set_Data_Devs_Src_Allow(DEV_OUTPUT_TYPE, CUR_DATA_ID_ALL_SRC_OF_SPEC_OPER, cur_data_devs_src_allow);
   if((ret_status = Cur_Data_ID_Devs_Src_Basic_Oper_Func(OUTPUT_DEV_DISABLE_OPER_FUNC, DEV_OUTPUT_TYPE, cur_data_devs_src_allow)) != SUCCESS)
   {
	      appl_error_or_warning_flag = ERR_DEV_OPER_DISABLE_FUNC;
	      Error_or_Warning_Proc("11.03.30", ERROR_OCCURED, appl_error_or_warning_flag);
	      return appl_error_or_warning_flag; 
   }
   if((ret_status = SW_Oper(RESET_SW_IO_CH, DEV_ENABLE_OPER)) != SUCCESS)
   {
		 appl_error_or_warning_flag = ERR_DEV_OPER_ENABLE_FUNC;
	     Error_or_Warning_Proc("11.03.31", ERROR_OCCURED, appl_error_or_warning_flag);
	     return appl_error_or_warning_flag;
   }   
   return SUCCESS;   
} 

/*------------------------------------------------------------*
FUNCTION NAME  : Appl_Reset

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 11.04

BUGS           :    
-*------------------------------------------------------------*/
 uint8_t Appl_Reset(const uint8_t reset_type)
{
	const char welcome_msg_disp_str[] = "Welcome"; 
	lcd_status_t *cur_lcd_status_ptr;
	dev_id_t lcd_dev_id, cur_data_devs_src_allow[1] = { CUR_DATA_ID_ALL_SRC_OF_SPEC_OPER};	
	uint8_t ret_status;
	
	switch(reset_type)
	{
		case RESET_APPL:
		  if((ret_status = Next_Data_Conf_Parameter(DATA_ID_STATUS)) != SUCCESS)
	      {
	         appl_error_or_warning_flag = ERR_NEXT_DATA_CONF;
	         Error_or_Warning_Proc("11.04.01", ERROR_OCCURED, appl_error_or_warning_flag);
	         return appl_error_or_warning_flag; 
	      }				       
	      Set_Data_Devs_Src_Allow(DEV_OUTPUT_TYPE, CUR_DATA_ID_ALL_SRC_OF_SPEC_OPER, cur_data_devs_src_allow);
	      if((ret_status = Cur_Data_ID_Devs_Src_Basic_Oper_Func(OUTPUT_DEV_ENABLE_OPER_FUNC, DEV_OUTPUT_TYPE, cur_data_devs_src_allow)) != SUCCESS)
	      {
	        appl_error_or_warning_flag = ERR_DEV_OPER_ENABLE_FUNC;
	        Error_or_Warning_Proc("11.04.02", ERROR_OCCURED, appl_error_or_warning_flag);
	        return appl_error_or_warning_flag; 
	      }
	      lcd_dev_id.dev_id = OUTPUT_DEV_ID_LCD;
	      if((ret_status = Data_ID_Src_Spec_Dev_Find_Dev_Ch_ID(cur_data_id, &lcd_dev_id, DEV_OUTPUT_TYPE))!= SUCCESS)
	      {
	         appl_error_or_warning_flag = ERR_LCD_NOT_DATA_SRC;
	         Error_or_Warning_Proc("11.04.03", ERROR_OCCURED, appl_error_or_warning_flag);
	         return appl_error_or_warning_flag;
	      }	
		  cur_lcd_status_ptr = lcd_status + lcd_dev_id.dev_ch_id; 
          Set_Status_Reset_Data_IDs(DATA_ID_RESET_INIT_STATUS);
          auth_fsm_state = INITIAL_FSM;
          status_disp_fsm =INITIAL;  
          lcd_disp_status.disp_status_flag = STATE_NO;        
         if((ret_status = SW_Oper(RESET_SW_IO_CH, DEV_DISABLE_OPER)) != SUCCESS)
         {
		    appl_error_or_warning_flag = ERR_DEV_OPER_DISABLE_FUNC;
	        Error_or_Warning_Proc("11.04.04", ERROR_OCCURED, appl_error_or_warning_flag);
	        return appl_error_or_warning_flag;
         }  
        if((ret_status = SW_Oper(ACCOUNT_SW_IO_CH, DEV_ENABLE_OPER)) != SUCCESS)
        {
		   appl_error_or_warning_flag = ERR_DEV_OPER_ENABLE_FUNC;
	       Error_or_Warning_Proc("11.04.05", ERROR_OCCURED, appl_error_or_warning_flag);
	       return appl_error_or_warning_flag;
        }   
          Set_Cur_Loc_LCD(lcd_dev_id.dev_ch_id, STATE_YES, ACCOUNT_ENTRY_START_LOC, STATE_YES, ACCOUNT_MSG_START_LOC );    
          cur_lcd_status_ptr->cur_line_disp_data[LONG_PRESSKEY_TIMEOUT_LINE_NUM] = BLANK_LINE_DISP;
          cur_lcd_status_ptr->cur_line_disp_data[NO_KEYPRESS_TIMEOUT_LINE_NUM] = BLANK_LINE_DISP;
          //cur_line_disp_data[AUTH_TIMEOUT_LINE_NUM] = BLANK_LINE_DISP; 
          cur_lcd_status_ptr->cur_line_disp_data[ALL_LINES] = ANY_DATA_DISP;
		  if((ret_status = LCD_Clear_Screen(lcd_dev_id.dev_ch_id)) != SUCCESS)
	      {
	         appl_error_or_warning_flag = ERR_LCD_WRITE_OPER;
	         Error_or_Warning_Proc("11.04.06", ERROR_OCCURED, appl_error_or_warning_flag);
	         return appl_error_or_warning_flag;
	      }	
		  #ifdef SHOULD_REMOVE
		  // display and cursor on and blinking OFF
	       if((ret_status = LCD_Write_Command(lcd_dev_id.dev_ch_id, 0x0E)) != SUCCESS)
	       {
	          appl_error_or_warning_flag = ERR_LCD_WRITE_OPER;
	          Error_or_Warning_Proc("11.04.07", ERROR_OCCURED, appl_error_or_warning_flag);
	          return appl_error_or_warning_flag;
	       }
	      #endif
           #ifdef SHOULD_CALL
		   // display on , cursor and blinking OFF
           if((ret_status = LCD_Write_Command(lcd_dev_id.dev_ch_id, 0x0C)) != SUCCESS)
	       {
	          appl_error_or_warning_flag = ERR_LCD_WRITE_OPER;
	          Error_or_Warning_Proc("11.04.08", ERROR_OCCURED, appl_error_or_warning_flag);
	          return appl_error_or_warning_flag;
	       }	     
	       #endif 
           if((ret_status = LCD_Disp_Goto_XY(lcd_dev_id.dev_ch_id, WELCOME_MSG_LINE_NUM, WELCOME_MSG_START_COL_NUM)) != SUCCESS)
		   {
				  appl_error_or_warning_flag = ERR_LCD_DISP_GOTO_XY;
				  Error_or_Warning_Proc("11.04.09", ERROR_OCCURED, appl_error_or_warning_flag);
				  return appl_error_or_warning_flag;
		   }				 
		   if((ret_status = LCD_Disp_Str(lcd_dev_id.dev_ch_id, welcome_msg_disp_str)) != SUCCESS)
		   {
				 appl_error_or_warning_flag = ERR_LCD_WRITE_OPER;
			     Error_or_Warning_Proc("11.04.10", ERROR_OCCURED, appl_error_or_warning_flag);
			     return appl_error_or_warning_flag;
		   }	
		break;
		default:
		   appl_error_or_warning_flag = ERR_FORMAT_INVALID;
		   Error_or_Warning_Proc("11.04.11", ERROR_OCCURED, appl_error_or_warning_flag);
		   return appl_error_or_warning_flag;
	}
	return SUCCESS;
} 

/*------------------------------------------------------------*
FUNCTION NAME  : Appl_Proc

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 11.05

BUGS           :    
-*------------------------------------------------------------*/
uint8_t Appl_Proc(void)
{
	lcd_status_t *cur_lcd_status_ptr;
	dev_id_t lcd_or_keyboard_dev_id;
	uint8_t ret_status, lcd_rcvd_char_disp_format, lcd_ctrl_format;
	unsigned char last_read_char;
	uint8_t  retrieve_data_str_len;        //SHOULD_REMOVE
	
	if(cur_data_id < NUM_DATA_IDS)
	{	
        if(auth_fsm_state == INITIAL_FSM)
		{
           if((ret_status = Auth_Fsm_Proc(ret_status)) != SUCCESS)
	       {
		       appl_error_or_warning_flag = ERR_AUTH_FSM_PROC;
		       Error_or_Warning_Proc("11.05.01", ERROR_OCCURED, appl_error_or_warning_flag);
		       return appl_error_or_warning_flag;
		   }
		}
	    ret_status = Cur_Data_ID_Input_Devs_Read_Oper_Func(&last_read_char);				
		switch(ret_status)
	    {
		     case CUR_DATA_ID_UNTIL_LAST_TRY_COMPLETE_READ_AND_READY_PROCESS:
             case CUR_DATA_ID_LAST_TRY_COMPLETE_READ_AND_READY_PROCESS:			 
			 case CUR_DATA_ID_INPUT_MAX_TRIED:			 
               if((ret_status = Auth_Fsm_Proc(ret_status)) != SUCCESS)
			   {
				   appl_error_or_warning_flag = ERR_AUTH_FSM_PROC;
		           Error_or_Warning_Proc("11.05.01", ERROR_OCCURED, appl_error_or_warning_flag);
		           return appl_error_or_warning_flag;
			   }
			 break;	
			 case CUR_DATA_ID_VALID_CHAR_READ:
			  #ifdef SHOULD_REMOVE	
		  	ret_status = Appl_Data_Retrieve_Para(cur_data_id, DATA_RETRIEVE_STATUS_NUM_CHARS_READ, &retrieve_data_str_len);		 
			            			
		     disp_trace_num_fmt.sign_flag = STATE_NO;
		     disp_trace_num_fmt.least_digits_flag = STATE_YES;
		    disp_trace_num_fmt.left_format_flag = STATE_YES;
		    disp_trace_num_fmt.num_digits = 3;
			UART_Transmit_Str(TRACE_UART_CH_ID, "\r APPL DATA: ");
			UART_Transmit_Num(TRACE_UART_CH_ID, DATA_TYPE_IN_DECIMAL, disp_trace_num_fmt, retrieve_data_str_len );
			
			 #endif
			   lcd_or_keyboard_dev_id.dev_id = OUTPUT_DEV_ID_LCD;
	           if((ret_status = Data_ID_Src_Spec_Dev_Find_Dev_Ch_ID(cur_data_id, &lcd_or_keyboard_dev_id, DEV_OUTPUT_TYPE))!= SUCCESS)
	           {
	              appl_error_or_warning_flag = ERR_LCD_NOT_DATA_SRC;
	              Error_or_Warning_Proc("11.05.02", ERROR_OCCURED, appl_error_or_warning_flag);
	              return appl_error_or_warning_flag;
	           }
			   if((ret_status = Appl_Data_Retrieve_Para(cur_data_id, DATA_RETRIEVE_CTRL_DISP_FORMAT, &lcd_rcvd_char_disp_format)) != SUCCESS)
			   {
					appl_error_or_warning_flag = ERR_APPL_DATA_RETRIEVE;
					Error_or_Warning_Proc("11.05.03", ERROR_OCCURED, appl_error_or_warning_flag);
					return appl_error_or_warning_flag; 
			   }
			   lcd_ctrl_format = lcd_rcvd_char_disp_format;
			   lcd_ctrl_format |= (LCD_INPUT_LOC << LCD_CTRL_LOC_TYPE_DATA_POS);
			   if((ret_status = LCD_Loc_Ctrl_Proc(lcd_or_keyboard_dev_id.dev_ch_id, lcd_ctrl_format, last_read_char)) != SUCCESS)
			   {
				    appl_error_or_warning_flag = ERR_LCD_LOC_CTRL;
					Error_or_Warning_Proc("11.05.04", ERROR_OCCURED, appl_error_or_warning_flag);
					return appl_error_or_warning_flag;
			   }
			 break;
			 case CUR_DATA_ID_REACH_MAX_CHARS_READ_WAIT_TERMINATOR_CHAR:			   
			 break;
             case CUR_DATA_ID_NO_INPUT_DEV:			 
		     case WARN_CUR_DATA_ID_DEV_DISABLED:
		     case WARN_CUR_DATA_ID_DEV_NO_ACCESS:		         
		     case SW_OR_KEY_NOT_PRESSED:
		     case WARN_CUR_DATA_ID_SPECIAL_CHAR_READ_BUT_DISABLED:
		     case WARN_CUR_DATA_ID_NUM_CHAR_READ_BUT_DISABLED:
		     case WARN_CUR_DATA_ID_SMALL_ENGLISH_ALPHA_CHAR_READ_BUT_DISABLED:
		     case WARN_CUR_DATA_ID_BIG_ENGLISH_ALPHA_CHAR_READ_BUT_DISABLED:
		     case WARN_CUR_DATA_ID_CTRL_CHAR_READ_BUT_DISABLED:
             break;		      			 
             case VALID_CTRL_CHAR_READ:
			   #ifdef SHOULD_REMOVE	
		  	Appl_Data_Retrieve_Para(cur_data_id, DATA_RETRIEVE_STATUS_NUM_CHARS_READ, &retrieve_data_str_len);
			  			              			
		     disp_trace_num_fmt.sign_flag = STATE_NO;
		     disp_trace_num_fmt.least_digits_flag = STATE_YES;
		    disp_trace_num_fmt.left_format_flag = STATE_YES;
		    disp_trace_num_fmt.num_digits = 3;
			UART_Transmit_Str(TRACE_UART_CH_ID, "\r APPL CTRL: ");
			UART_Transmit_Num(TRACE_UART_CH_ID, DATA_TYPE_IN_DECIMAL, disp_trace_num_fmt, retrieve_data_str_len );
			
			 #endif
			  
			    switch(last_read_char)
				{
					case BACKSPACE_CHAR:
					  if((ret_status =  After_Switch_Stoke_Proc(BACKSPACE_SW_CODE)) != SUCCESS)
					  {
						  appl_error_or_warning_flag = ERR_AFTER_SW_PRESS_STROKE;
						  Error_or_Warning_Proc("11.05.05", ERROR_OCCURED, appl_error_or_warning_flag);
				          return appl_error_or_warning_flag; 
					  }
                    break;
                    case ENTER_CHAR:
					  if((ret_status =  After_Switch_Stoke_Proc(ENTER_SW_CODE)) != SUCCESS)
					  {
						  appl_error_or_warning_flag = ERR_AFTER_SW_PRESS_STROKE;
						  Error_or_Warning_Proc("11.05.06", ERROR_OCCURED, appl_error_or_warning_flag);
				          return appl_error_or_warning_flag; 
					  }
                    break;
                    default:
                       appl_error_or_warning_flag = ERR_FORMAT_INVALID;
					   Error_or_Warning_Proc("11.05.07", ERROR_OCCURED, appl_error_or_warning_flag);
				       return appl_error_or_warning_flag;  					
				}					
		    break;
        default:
               appl_error_or_warning_flag = ERR_DEV_OPER_READ_FUNC;
			   Error_or_Warning_Proc("11.05.08", ERROR_OCCURED, appl_error_or_warning_flag);
			   return appl_error_or_warning_flag;  		  
	    }
		lcd_or_keyboard_dev_id.dev_id = OUTPUT_DEV_ID_LCD;
	    if((ret_status = Data_ID_Src_Spec_Dev_Find_Dev_Ch_ID(cur_data_id, &lcd_or_keyboard_dev_id, DEV_OUTPUT_TYPE))!= SUCCESS)
	    {
	       appl_error_or_warning_flag = ERR_LCD_NOT_DATA_SRC;
	       Error_or_Warning_Proc("11.05.09", ERROR_OCCURED, appl_error_or_warning_flag);
	       return appl_error_or_warning_flag;
	    }	
		cur_lcd_status_ptr = lcd_status + lcd_or_keyboard_dev_id.dev_ch_id; 
		if(status_disp_fsm != INITIAL && cur_lcd_status_ptr->cur_line_disp_data[ALL_LINES] == ANY_DATA_DISP )
        { 
	        if((ret_status = Disp_Status_Fsm()) != SUCCESS)
			{
				appl_error_or_warning_flag = ERR_DISP_STATUS;
				Error_or_Warning_Proc("11.05.10", ERROR_OCCURED, appl_error_or_warning_flag);
				return appl_error_or_warning_flag;
			}				
	        cur_lcd_status_ptr->cur_line_disp_data[ALL_LINES] = AUTH_STATUS_DISP;     
        }
    }	
	ret_status = SW_Oper(RESET_SW_IO_CH, DEV_READ_OPER);
	switch(ret_status)
	{	
        case SUCCESS:
		   if((ret_status =  After_Switch_Stoke_Proc(RESET_SW_CODE)) != SUCCESS)
		   {
		  	  appl_error_or_warning_flag = ERR_AFTER_SW_PRESS_STROKE;
			  Error_or_Warning_Proc("11.05.13", ERROR_OCCURED, appl_error_or_warning_flag);
			  return appl_error_or_warning_flag; 
		   }
		break;  
		case SW_OR_KEY_NOT_PRESSED:
		case WARN_CUR_DATA_ID_DEV_NO_ACCESS:
		case WARN_CUR_DATA_ID_DEV_DISABLED: 
        break;
        default:			   
		   appl_error_or_warning_flag = ERR_DEV_OPER_READ_FUNC;
		   Error_or_Warning_Proc("11.05.14", ERROR_OCCURED, appl_error_or_warning_flag);
		   return appl_error_or_warning_flag;                        
    }
	return SUCCESS;
}

/*------------------------------------------------------------*
FUNCTION NAME  : Appl_Init

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 11.06  

BUGS           :              
-*------------------------------------------------------------*/
uint8_t Appl_Init(const void *const data_ptr)
{	
    uint8_t ret_status;
	
    if((ret_status = SW_Oper(ACCOUNT_SW_IO_CH, DEV_ALLOW_ACCESS_OPER)) != SUCCESS)
	{
		return FAILURE;
	}
	if((ret_status = SW_Oper(RESET_SW_IO_CH, DEV_ALLOW_ACCESS_OPER)) != SUCCESS)
	{
		return FAILURE;
	}	   
	return SUCCESS; 
}

/*------------------------------------------------------------*
FUNCTION NAME  : Appl_HW_Init

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : First initialise independent SW in order from SW_CH_ID from 0 if any, then initialize Keyboard, if any.

Func ID        : 11.07  

BUGS           :              
-*------------------------------------------------------------*/
uint8_t Appl_HW_Init(void)
{
    uint8_t ret_status ;
	
	if((ret_status = UART_Init(TRACE_UART_CH_ID)) != SUCCESS)
	{
		return FAILURE;
	}
	if((ret_status = LCD_Init(CH_ID_00)) != SUCCESS)
	{
		return FAILURE;
	}
	if((ret_status = Output_Dev_Init(INTERNAL_ERROR_LED_IO_CH, 1)) != SUCCESS)
	{
		return FAILURE;
	}
	if((ret_status = SW_Oper(RESET_SW_IO_CH, DEV_INIT_OPER)) != SUCCESS)
	{
		return FAILURE;
	}
	if((ret_status = SW_Oper(ACCOUNT_SW_IO_CH, DEV_INIT_OPER)) != SUCCESS)
	{
		return FAILURE;
	}		
	if((ret_status = Keyboard_Init(CH_ID_00)) != SUCCESS)
	{
		return FAILURE;
	}
	
	return SUCCESS; 
}

/*------------------------------------------------------------*
FUNCTION NAME  : Set_Auth_Status_Disp_Fsm

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 11.08  

BUGS           :              
-*------------------------------------------------------------*/
uint8_t Set_Auth_Status_Disp_Fsm(const auth_status_fsm set_status_disp_fsm )
{
	Reset_Data_ID_Status(cur_data_id, DATA_ID_RESET_WHOLE_STATUS);			
	status_disp_fsm = set_status_disp_fsm;
	lcd_disp_status.disp_status_flag = STATE_YES; 
	return SUCCESS;
}
/*------------------------------------------------------------------*-
  ------------------------ END OF FILE ------------------------------
-*------------------------------------------------------------------*/
