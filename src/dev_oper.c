/**************************************************************************
   FILE          :    dev_oper.c
 
   PURPOSE       :     
 
   AUTHOR        :    K.M. Arun Kumar alias Arunkumar Murugeswaran
 
  KNOWN BUGS     :
	
	CAUTION        :
	
  NOTE           :   
  
  CHANGE LOGS    :
  
  FILE ID        : 08  
	   
 **************************************************************************/ 
 #include "main.h"

/* ------------------------------ macro defination ------------------------------ */

/* ----------------------------- global variable defination --------------------- */

/* ----------------------------- global variable declaration -------------------- */

/* ----------------------------- global function declaration -------------------- */
 static uint8_t Dev_Oper_Read_Status_Proc( const uint8_t rcvd_read_status, unsigned char last_read_char);
 static uint8_t Cur_Data_ID_Dev_Src_Basic_Oper_Func(const uint8_t dev_src_basic_oper_func, const dev_id_t *const dev_basic_oper_func_ptr);
 static uint8_t Data_ID_Input_Try_Complete_Proc(const uint8_t data_id);
 
/* ---------------------------- function pointer defination ---------------------- */
Dev_Oper_Func_t Dev_Oper_Func_Table[] = { 
                        #ifdef DAC_MOD_ENABLE
                        { NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR},
                        #else
                         { NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR},
                        #endif
                        #ifdef PWM_MOD_ENABLE
                         { NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR},
                        #else
                         { NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR},
                        #endif
						#ifdef SEG7_MOD_ENABLE
						{ Seg7_DeInit, Seg7_Init, Seg7_No_Access, Seg7_Allow_Access, Seg7_Disable, Seg7_Enable, NULL_PTR, NULL_PTR, NULL_PTR, Seg7_Write },
						#else
						 { NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR},
					    #endif
						#ifdef LCD_MOD_ENABLE
						 { LCD_DeInit ,LCD_Init, LCD_No_Access, LCD_Allow_Access, LCD_Disable, LCD_Enable, NULL_PTR, NULL_PTR, NULL_PTR, LCD_Write},
						#else
						 { NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR},
					    #endif
						#ifdef LED_MATRIX_MOD_ENABLE
                         { LED_Matrix_DeInit, LED_Matrix_Init, LED_Matrix_No_Access, LED_Matrix_Allow_Access, LED_Matrix_Disable, LED_Matrix_Enable, NULL_PTR, NULL_PTR, NULL_PTR, LED_Matrix_Write},
                        #else
                         { NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR},
                        #endif
                      	#ifdef USART_MOD_ENABLE
                         { NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR},
                        #else
                         { NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR},
                        #endif
						#ifdef I2C_MOD_ENABLE
                        { NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR},
                        #else
                         { NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR},
                        #endif
                        #ifdef SPI_MOD_ENABLE
                         { NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR},
                        #else
                         { NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR},
                        #endif
              			#ifdef MISC_MOD_ENABLE
                         { NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR},
                        #else
                         { NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR},
                        #endif	
                        #ifdef KEYBOARD_MOD_ENABLE
 						 { Keyboard_DeInit, Keyboard_Init, Keyboard_No_Access, Keyboard_Allow_Access, Keyboard_Disable, Keyboard_Enable, NULL_PTR, NULL_PTR, Keyboard_Read, NULL_PTR},
                        #else
                         { NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR},
                        #endif
						#ifdef ADC_MOD_ENABLE
						 { NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR},
                        #else
                        { NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR},
                        #endif
						#ifdef SW_MOD_ENABLE
						 { SW_DeInit, SW_Init, SW_No_Access, SW_Allow_Access, SW_Disable, SW_Enable, NULL_PTR, NULL_PTR, SW_Press_Proc, NULL_PTR},
                        #else
                        { NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR},
                        #endif
						#ifdef INPUT_MISC_MOD_ENABLE
						 { NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR},
                        #else
                         { NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR},
                        #endif
						 { NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR}
                      }; 
					  
/*------------------------------------------------------------*
FUNCTION NAME  : Cur_Data_ID_Input_Devs_Read_Oper_Func

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 08.01

BUGS           :    
-*------------------------------------------------------------*/
uint8_t Cur_Data_ID_Input_Devs_Read_Oper_Func(unsigned char *const last_read_data_char_ptr )
{
 	data_id_status_para_t *cur_data_id_status_para_ptr;
	const data_id_ctrl_para_t *cur_data_id_ctrl_para_ptr;
  const dev_id_t *data_dev_read_oper_func;
  dev_input_ctrl_para_t dev_input_ctrl_para;
	uint8_t ret_status = CUR_DATA_ID_NO_INPUT_DEV, i = 0; 	
	
	if(cur_data_id >= NUM_DATA_IDS)
	{
	   sys_error_or_warning_flag = ERR_DATA_ID_EXCEED;
	   Error_or_Warning_Proc("08.01.01", ERROR_OCCURED, sys_error_or_warning_flag);
	   return sys_error_or_warning_flag;
	}
	if(last_read_data_char_ptr == NULL_PTR)
	{
		sys_error_or_warning_flag = ERR_NULL_PTR;
	    Error_or_Warning_Proc("08.01.02", ERROR_OCCURED, sys_error_or_warning_flag);
	    return sys_error_or_warning_flag;
	}
	*last_read_data_char_ptr = NULL_CHAR;
	cur_data_id_status_para_ptr = data_id_status_para + cur_data_id;
	cur_data_id_ctrl_para_ptr = data_id_ctrl_para + cur_data_id;
	if(cur_data_id_status_para_ptr->data_input_status.max_try_reached_flag == STATE_YES)
	{
		return CUR_DATA_ID_INPUT_MAX_TRIED;
	}
	if(cur_data_id_status_para_ptr->data_input_status.last_try_read_and_ready_to_process_flag == STATE_YES)
	{
		return CUR_DATA_ID_LAST_TRY_COMPLETE_READ_AND_READY_PROCESS;
	}
	if(cur_data_id_status_para_ptr->data_input_status.read_and_ready_to_process_flag == STATE_YES)
	{
		  return CUR_DATA_ID_UNTIL_LAST_TRY_COMPLETE_READ_AND_READY_PROCESS;
	}
	i = 0;	
    data_dev_read_oper_func =  data_ids_dev_srcs[cur_data_id].data_input_dev_ids;
	while(i < MAX_DATA_INPUT_DEVS && (data_dev_read_oper_func + i)->dev_id >= BEGIN_INPUT_DEV_ID && (data_dev_read_oper_func + i)->dev_id <= END_INPUT_DEV_ID  )
	{
		if(cur_data_id_status_para_ptr->data_input_status.max_try_reached_flag == STATE_YES)
	    {
	    	return CUR_DATA_ID_INPUT_MAX_TRIED;
	    }
		if(cur_data_id_status_para_ptr->data_input_status.last_try_read_and_ready_to_process_flag == STATE_YES)
	    {
		    return CUR_DATA_ID_LAST_TRY_COMPLETE_READ_AND_READY_PROCESS;
	    }
	    if(cur_data_id_status_para_ptr->data_input_status.read_and_ready_to_process_flag == STATE_YES)
	    {
		    return CUR_DATA_ID_UNTIL_LAST_TRY_COMPLETE_READ_AND_READY_PROCESS;
	    }
	   if(Dev_Oper_Func_Table[(data_dev_read_oper_func + i)->dev_id].Dev_Read_Func_Ptr == NULL_PTR)
	   {
		  sys_error_or_warning_flag = ERR_NULL_PTR;
		   Error_or_Warning_Proc("08.01.03", ERROR_OCCURED, sys_error_or_warning_flag);
          return sys_error_or_warning_flag; 
	   }
	   // num chars read with an appended NULL_CHAR
	   if(cur_data_id_status_para_ptr->data_value.data_str_len_or_pos + 1 >= cur_data_id_status_para_ptr->max_allocated_data_len)
	   {
		   cur_data_id_status_para_ptr->data_input_status.reach_max_alloc_input_chars_flag = STATE_YES;
		   switch( cur_data_id_status_para_ptr->data_input_status.data_input_mode) 
	       {
			 /* if data's max data allocated char < num entered chars, then new entered chars are taken, till terminator char is read.
			   if data's max data allocated char >= num entered chars, then newly read chars are discarded, till terminator char is read */
		     case DATA_ID_INPUT_MODE_TILL_TERMINATOR:			    					
		     break;
			 case DATA_ID_INPUT_MODE_TILL_ALLOC:
                cur_data_id_status_para_ptr->data_input_status.read_and_ready_to_process_flag = STATE_YES;
                ret_status = Data_ID_Input_Try_Complete_Proc(cur_data_id);
                return ret_status;				
             //break;			
	       }
	   }
	   else
	   {
		  cur_data_id_status_para_ptr->data_input_status.reach_max_alloc_input_chars_flag = STATE_NO; 
	   }
	    dev_input_ctrl_para.cur_data_input_status = cur_data_id_status_para_ptr->data_input_status;
	    ret_status = (*Dev_Oper_Func_Table[(data_dev_read_oper_func + i)->dev_id].Dev_Read_Func_Ptr)((data_dev_read_oper_func + i)->dev_ch_id, &dev_input_ctrl_para);
	      switch(ret_status)
          {
           case DATA_CHAR_READ:
		          *last_read_data_char_ptr = dev_input_ctrl_para.rcvd_data_char;
                  ret_status = Dev_Oper_Read_Status_Proc(ret_status, dev_input_ctrl_para.rcvd_data_char);    
		          switch(ret_status)
		          {
			           case ERR_DEV_OPER_READ_FUNC:
					      *last_read_data_char_ptr = NULL_CHAR;
			              sys_error_or_warning_flag = ret_status;
						  Error_or_Warning_Proc("08.01.02", ERROR_OCCURED, sys_error_or_warning_flag);
                          return sys_error_or_warning_flag;
                   //break;
                    case CUR_DATA_ID_COMPLETE_READ_AND_READY_PROCESS:
					    ret_status = Data_ID_Input_Try_Complete_Proc(cur_data_id);
                        return ret_status;	
			           //break;	
					case CUR_DATA_ID_LAST_TRY_COMPLETE_READ_AND_READY_PROCESS:					  
					break;
		          }
           break;              
           case SW_OR_KEY_NOT_PRESSED:
           case WARN_CUR_DATA_ID_DEV_DISABLED: 
           case WARN_CUR_DATA_ID_DEV_NO_ACCESS: 		    
           break;           
           default: 
             sys_error_or_warning_flag = ERR_DEV_OPER_READ_FUNC;
			 Error_or_Warning_Proc("08.01.04", ERROR_OCCURED, sys_error_or_warning_flag);
			 return sys_error_or_warning_flag;
         }	
      ++i;    
	   }
	return ret_status;	
}

/*------------------------------------------------------------*
FUNCTION NAME  : Dev_Oper_Read_Status_Proc

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           :   

Func ID        : 08.02  

BUGS           :              
-*------------------------------------------------------------*/
static uint8_t Dev_Oper_Read_Status_Proc( const uint8_t rcvd_read_status, unsigned char last_read_char)
{
	data_id_status_para_t *cur_data_id_status_para_ptr = NULL_PTR;
	const data_id_ctrl_para_t *cur_data_id_ctrl_para_ptr;	
	uint8_t data_valid_read_char_flag = STATE_NO, ret_status = rcvd_read_status ;
	
	if(cur_data_id >= NUM_DATA_IDS)
	{
	   sys_error_or_warning_flag = ERR_DATA_ID_EXCEED;
	   	Error_or_Warning_Proc("08.02.01", ERROR_OCCURED, sys_error_or_warning_flag);
	   return ERR_DEV_OPER_READ_FUNC;
	}
	cur_data_id_status_para_ptr = data_id_status_para + cur_data_id;
	cur_data_id_ctrl_para_ptr  = data_id_ctrl_para + cur_data_id;
	if(cur_data_id_status_para_ptr->data_input_status.last_try_read_and_ready_to_process_flag == STATE_YES)
	{
		return CUR_DATA_ID_LAST_TRY_COMPLETE_READ_AND_READY_PROCESS;
	}
	if(cur_data_id_status_para_ptr->data_input_status.read_and_ready_to_process_flag == STATE_YES)
	{
	    return CUR_DATA_ID_COMPLETE_READ_AND_READY_PROCESS;
	}
	switch(rcvd_read_status)
	{ 
	    case  DATA_CHAR_READ:
		case  COMM_RCVD_CHAR:
		   if(last_read_char > ASCII_MAX_CHAR_CODE)
		   {
			   sys_error_or_warning_flag = ERR_INVALID_DATA_CHAR_READ;
			   	Error_or_Warning_Proc("08.02.02", ERROR_OCCURED, sys_error_or_warning_flag);
			   return ERR_DEV_OPER_READ_FUNC;
		   }
		   switch( cur_data_id_status_para_ptr->data_input_status.data_input_mode) 
	       {
			 /* if data's max data allocated char < num entered chars, then new entered chars are taken, till terminator char is read.
			   if data's max data allocated char >= num entered chars, then newly read chars are discarded, till terminator char is read */
		      case DATA_ID_INPUT_MODE_TILL_TERMINATOR:
			    if(cur_data_id_ctrl_para_ptr->data_input_terminator_char == last_read_char )
		        {
			       cur_data_id_status_para_ptr->data_value.data_str[cur_data_id_status_para_ptr->data_value.data_str_len_or_pos]= NULL_CHAR;
			       cur_data_id_status_para_ptr->data_input_status.input_valid_terminator_char_flag = STATE_YES; 
			       cur_data_id_status_para_ptr->data_input_status.read_and_ready_to_process_flag = STATE_YES;
			       return CUR_DATA_ID_COMPLETE_READ_AND_READY_PROCESS;	
		        }	
			    if(cur_data_id_status_para_ptr->data_input_status.reach_max_alloc_input_chars_flag == STATE_YES && last_read_char != BACKSPACE_CHAR && cur_data_id_status_para_ptr->data_input_status.input_valid_terminator_char_flag == STATE_NO )
				{					   
					return CUR_DATA_ID_REACH_MAX_CHARS_READ_WAIT_TERMINATOR_CHAR;
				}					
		      break;
			  case DATA_ID_INPUT_MODE_TILL_ALLOC:                 				
              break;			
	       }
		   		 
		  if(last_read_char >= NUM_0_CHAR && last_read_char <= NUM_9_CHAR)
		  {  
		     if(cur_data_id_ctrl_para_ptr->data_proc_num_char_enable_flag  ==  STATE_NO)		
		     {
				 sys_error_or_warning_flag = WARN_CUR_DATA_ID_NUM_CHAR_READ_BUT_DISABLED;
				 Error_or_Warning_Proc("08.02.03", WARNING_OCCURED, sys_error_or_warning_flag);
		         return sys_error_or_warning_flag;
		     }
			 
		     data_valid_read_char_flag = STATE_YES;
			 break;
		  }
		  if(last_read_char >= ENGLISH_SMALL_ALPHA_a_CHAR && last_read_char <= ENGLISH_SMALL_ALPHA_z_CHAR)
		  {
		      if(cur_data_id_ctrl_para_ptr->data_proc_small_english_alpha_char_enable_flag  ==  STATE_NO)		
		      {
			   	 sys_error_or_warning_flag = WARN_CUR_DATA_ID_SMALL_ENGLISH_ALPHA_CHAR_READ_BUT_DISABLED; 	
				 Error_or_Warning_Proc("08.02.04", WARNING_OCCURED, sys_error_or_warning_flag);
		         return sys_error_or_warning_flag;
		      }
		      data_valid_read_char_flag = STATE_YES;
			  break; 
		  }
		  if(last_read_char >= ENGLISH_BIG_ALPHA_A_CHAR && last_read_char <= ENGLISH_BIG_ALPHA_Z_CHAR)
		  {
			   if(cur_data_id_ctrl_para_ptr->data_proc_big_english_alpha_char_enable_flag  ==  STATE_NO)		
		       {
			  	   sys_error_or_warning_flag = WARN_CUR_DATA_ID_BIG_ENGLISH_ALPHA_CHAR_READ_BUT_DISABLED;
				    Error_or_Warning_Proc("08.02.05", WARNING_OCCURED, sys_error_or_warning_flag);
		           return sys_error_or_warning_flag;
		       }
		       data_valid_read_char_flag = STATE_YES;
			   break;
		  }
		  if(last_read_char >= BEGIN_CTRL_CHARS_ASCII_CODE && last_read_char <= END_CTRL_CHARS_ASCII_CODE)
		  {
			  switch(last_read_char)
			   {
			       case BACKSPACE_CHAR:
			      	  // rcvd char is backspace 
					  switch(cur_data_id_ctrl_para_ptr->input_data_type)
		              {
		                 case DATA_TYPE_IN_CHAR:
			                cur_data_id_status_para_ptr->data_value.data_str[cur_data_id_status_para_ptr->data_value.data_str_len_or_pos] = NULL_CHAR; 
			             break;
			             case DATA_TYPE_IN_STR:
			                if(cur_data_id_status_para_ptr->data_value.data_str_len_or_pos > 0)
				            {
						      cur_data_id_status_para_ptr->data_value.data_str[cur_data_id_status_para_ptr->data_value.data_str_len_or_pos] = NULL_CHAR;
						      --cur_data_id_status_para_ptr->data_value.data_str_len_or_pos;	
							   #ifdef SHOULD_REMOVE			 
			  
			                      disp_trace_num_fmt.sign_flag = STATE_NO;
		                          disp_trace_num_fmt.least_digits_flag = STATE_YES;
		                           disp_trace_num_fmt.left_format_flag = STATE_YES;
		    disp_trace_num_fmt.num_digits = 3;
			UART_Transmit_Str(TRACE_UART_CH_ID, "\r dev - : ");
			UART_Transmit_Num(TRACE_UART_CH_ID, DATA_TYPE_IN_DECIMAL, disp_trace_num_fmt, cur_data_id_status_para_ptr->data_value.data_str_len_or_pos );
			 #endif
				            }
                            else
				            {
				              cur_data_id_status_para_ptr->data_value.data_str[0] = NULL_CHAR;							
			                }
                         break;
                         default:
         		           sys_error_or_warning_flag = ERR_CUR_DATA_ID_INVALID_DATA_TYPE;
			               Error_or_Warning_Proc("08.02.06", ERROR_OCCURED, sys_error_or_warning_flag);
			               	return ERR_DEV_OPER_READ_FUNC;  
		             }
					//break;
                   case ENTER_CHAR:				    
                   break;
                   default:	
                      sys_error_or_warning_flag = ERR_INVALID_DATA;
			          Error_or_Warning_Proc("08.02.07", ERROR_OCCURED, sys_error_or_warning_flag);
			          	return ERR_DEV_OPER_READ_FUNC;  				   
			   } 
			  /* if(cur_data_id_ctrl_para_ptr->data_proc_ctrl_char_enable_flag  ==  STATE_NO)		
		       {
			  	   sys_error_or_warning_flag = WARN_CUR_DATA_ID_CTRL_CHAR_READ_BUT_DISABLED;
				   Error_or_Warning_Proc("08.02.08", WARNING_OCCURED, sys_error_or_warning_flag);
		           return sys_error_or_warning_flag;
		       } */			   
		       return VALID_CTRL_CHAR_READ;
			   //break;
		  }
		  else
		  {
		     if(cur_data_id_ctrl_para_ptr->data_proc_special_char_enable_flag  ==  STATE_NO)		
		     {
				 sys_error_or_warning_flag = WARN_CUR_DATA_ID_SPECIAL_CHAR_READ_BUT_DISABLED; 	
				 Error_or_Warning_Proc("08.02.09", WARNING_OCCURED, sys_error_or_warning_flag);
		         return sys_error_or_warning_flag;
		      }
		     data_valid_read_char_flag = STATE_YES;
		    // break;	  
		  }
		  break;
          case WARN_CUR_DATA_ID_DEV_DISABLED:
		  case WARN_CUR_DATA_ID_DEV_NO_ACCESS:
		  case SW_OR_KEY_NOT_PRESSED:	
	      case COMM_NO_RCV_CHAR:
          break;
		  default:
		    sys_error_or_warning_flag = ERR_DEV_OPER_READ_FUNC; 	
			Error_or_Warning_Proc("08.02.10", ERROR_OCCURED, sys_error_or_warning_flag);
            return sys_error_or_warning_flag; 
	} 
	if(data_valid_read_char_flag == STATE_YES)
	{
		  ret_status = CUR_DATA_ID_VALID_CHAR_READ;		  
		  switch(cur_data_id_ctrl_para_ptr->input_data_type)
		  {
		     case DATA_TYPE_IN_CHAR:
			      cur_data_id_status_para_ptr->data_value.data_str[cur_data_id_status_para_ptr->data_value.data_str_len_or_pos] = last_read_char; 
			 break;
			 case DATA_TYPE_IN_STR:
			      cur_data_id_status_para_ptr->data_value.data_str[cur_data_id_status_para_ptr->data_value.data_str_len_or_pos] = last_read_char;   
                  ++cur_data_id_status_para_ptr->data_value.data_str_len_or_pos;				 
                  cur_data_id_status_para_ptr->data_value.data_str[cur_data_id_status_para_ptr->data_value.data_str_len_or_pos] = NULL_CHAR;
				  #ifdef SHOULD_REMOVE			 
			  
			   disp_trace_num_fmt.sign_flag = STATE_NO;
		    disp_trace_num_fmt.least_digits_flag = STATE_YES;
		    disp_trace_num_fmt.left_format_flag = STATE_YES;
		    disp_trace_num_fmt.num_digits = 3;
			UART_Transmit_Str(TRACE_UART_CH_ID, "\r dev + : ");
			UART_Transmit_Num(TRACE_UART_CH_ID, DATA_TYPE_IN_DECIMAL, disp_trace_num_fmt, cur_data_id_status_para_ptr->data_value.data_str_len_or_pos );
			 #endif
             break;
             default:
         		 sys_error_or_warning_flag = ERR_CUR_DATA_ID_INVALID_DATA_TYPE;
			     Error_or_Warning_Proc("08.02.11", ERROR_OCCURED, sys_error_or_warning_flag);
			     return ERR_DEV_OPER_READ_FUNC;	   
		  }
	}  
	return ret_status;		
}

/*------------------------------------------------------------*
FUNCTION NAME  : Data_Dev_Src_Access_Oper_Func

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 08.03

Bugs           :   
-*------------------------------------------------------------*/
uint8_t Data_Dev_Src_Access_Oper_Func(const uint8_t prev_data_id)
{
  const dev_id_t *data_dev_access_oper; 
	dev_id_t cur_data_devs_src_allow[1] = { CUR_DATA_ID_ALL_SRC_OF_SPEC_OPER};
    uint8_t i = 0, ret_status = SUCCESS, data_dev_type, min_dev_id, max_dev_id, max_data_dev_type_srcs;
	
	 if(cur_data_id == prev_data_id)
	 {
		  return SUCCESS;
	 }
	 
	 if(prev_data_id < NUM_DATA_IDS)
	 {
		 for(data_dev_type = DEV_INPUT_TYPE; data_dev_type < NUM_DEV_TYPES; ++data_dev_type)
		 {
			 switch(data_dev_type)
			 {
			    case DEV_INPUT_TYPE:
     	           data_dev_access_oper =  data_ids_dev_srcs[prev_data_id].data_input_dev_ids;
				   min_dev_id = BEGIN_INPUT_DEV_ID;
				   max_dev_id = END_INPUT_DEV_ID;
				   max_data_dev_type_srcs = MAX_DATA_INPUT_DEVS;
			    break;
			    case DEV_OUTPUT_TYPE:
			       data_dev_access_oper =  data_ids_dev_srcs[prev_data_id].data_output_dev_ids;
				   min_dev_id = BEGIN_OUTPUT_DEV_ID;
				   max_dev_id = END_OUTPUT_DEV_ID;
				   max_data_dev_type_srcs = MAX_DATA_OUTPUT_DEVS;
			    break;
			    case DEV_RECEIVE_TYPE:
			       data_dev_access_oper =  data_ids_dev_srcs[prev_data_id].data_receive_dev_ids;
				   min_dev_id = BEGIN_COMM_DEV_ID;
				   max_dev_id = END_COMM_DEV_ID;
				   max_data_dev_type_srcs = MAX_DATA_RECEIVE_DEVS;
			    break;
			    case DEV_TRANSMIT_TYPE:
			       data_dev_access_oper =  data_ids_dev_srcs[prev_data_id].data_transmit_dev_ids;
				   min_dev_id = BEGIN_COMM_DEV_ID;
				   max_dev_id = END_COMM_DEV_ID;
				   max_data_dev_type_srcs = MAX_DATA_TRANSMIT_DEVS;
			    break;
          default:
			      sys_error_or_warning_flag = ERR_FORMAT_INVALID;
			      Error_or_Warning_Proc("08.02.11", ERROR_OCCURED, sys_error_or_warning_flag);
			      return ERR_DEV_OPER_READ_FUNC;
		     }
            i = 0;		 
		    while(i < max_data_dev_type_srcs && (data_dev_access_oper + i)->dev_id >= min_dev_id && (data_dev_access_oper + i)->dev_id <= max_dev_id )
		    {
				  if(Dev_Oper_Func_Table[(data_dev_access_oper + i)->dev_id].Dev_No_Access_Func_Ptr == NULL_PTR)
				   {
					   sys_error_or_warning_flag = ERR_NULL_PTR;
					   Error_or_Warning_Proc("08.03.04", ERROR_OCCURED, sys_error_or_warning_flag);
                       return sys_error_or_warning_flag;  
				   } 
				   if((ret_status = (*Dev_Oper_Func_Table[(data_dev_access_oper + i)->dev_id].Dev_No_Access_Func_Ptr)((data_dev_access_oper + i)->dev_ch_id)) != SUCCESS)
				   {
					  sys_error_or_warning_flag = ERR_DEV_OPER_NO_ACCESS_FUNC;
					  Error_or_Warning_Proc("08.03.03", ERROR_OCCURED, sys_error_or_warning_flag);
					  return sys_error_or_warning_flag;
				   }
				   ++i;			   
			 }
	     }
	 }		 
	 if(cur_data_id < NUM_DATA_IDS)
	 {
	    if((ret_status = Cur_Data_ID_Devs_Src_Basic_Oper_Func(INPUT_DEV_ALLOW_ACCESS_OPER_FUNC, DEV_INPUT_TYPE, cur_data_devs_src_allow )) != SUCCESS)
		{
			sys_error_or_warning_flag = ERR_DEV_OPER_ALLOW_ACCESS_FUNC;
			Error_or_Warning_Proc("08.03.09", ERROR_OCCURED, sys_error_or_warning_flag);
			return sys_error_or_warning_flag;
		}
        if((ret_status = Cur_Data_ID_Devs_Src_Basic_Oper_Func(OUTPUT_DEV_ALLOW_ACCESS_OPER_FUNC, DEV_OUTPUT_TYPE, cur_data_devs_src_allow )) != SUCCESS)
		{
			sys_error_or_warning_flag = ERR_DEV_OPER_ALLOW_ACCESS_FUNC;
			Error_or_Warning_Proc("08.03.10", ERROR_OCCURED, sys_error_or_warning_flag);
			return sys_error_or_warning_flag;
		}
		if((ret_status = Cur_Data_ID_Devs_Src_Basic_Oper_Func(COMM_DEV_ALLOW_ACCESS_OPER_FUNC, DEV_RECEIVE_TYPE, cur_data_devs_src_allow )) != SUCCESS)
		{
			sys_error_or_warning_flag = ERR_DEV_OPER_ALLOW_ACCESS_FUNC;
			Error_or_Warning_Proc("08.03.11", ERROR_OCCURED, sys_error_or_warning_flag);
			return sys_error_or_warning_flag;
		}
		if((ret_status = Cur_Data_ID_Devs_Src_Basic_Oper_Func(COMM_DEV_ALLOW_ACCESS_OPER_FUNC, DEV_TRANSMIT_TYPE, cur_data_devs_src_allow )) != SUCCESS)
		{
			sys_error_or_warning_flag = ERR_DEV_OPER_ALLOW_ACCESS_FUNC;
			Error_or_Warning_Proc("08.03.12", ERROR_OCCURED, sys_error_or_warning_flag);
			return sys_error_or_warning_flag;
		}
	 }
      return SUCCESS;    
}

/*------------------------------------------------------------*
FUNCTION NAME  : Cur_Data_ID_Devs_Src_Basic_Oper_Func

DESCRIPTION    :
								
INPUT          :

OUTPUT         : 

NOTE           : 

Func ID        : 08.04 

Bugs           :   
-*------------------------------------------------------------*/
uint8_t Cur_Data_ID_Devs_Src_Basic_Oper_Func(const uint8_t dev_src_basic_oper_func, const uint8_t dev_type, const dev_id_t *const cur_data_devs_src_allow_ptr )
{
	  const dev_id_t *data_dev_basic_oper_func_ptr;
      uint8_t i = 0, ret_status, j = 0, min_dev_id, max_dev_id, max_data_dev_type_srcs, dev_src_allow_match_flag = STATE_NO;
	  
	  if(cur_data_devs_src_allow_ptr == NULL_PTR ||
      !((dev_src_basic_oper_func >= START_INPUT_DEV_BASIC_OPER_FUNC && dev_src_basic_oper_func <= END_INPUT_DEV_BASIC_OPER_FUNC) || 
		 (dev_src_basic_oper_func >= START_OUTPUT_DEV_BASIC_OPER_FUNC && dev_src_basic_oper_func <= END_OUTPUT_DEV_BASIC_OPER_FUNC) ||
	     (dev_src_basic_oper_func >= START_COMM_DEV_BASIC_OPER_FUNC && dev_src_basic_oper_func <= END_COMM_DEV_BASIC_OPER_FUNC)))
	  {
		  sys_error_or_warning_flag = ERR_DEV_SRC_BASIC_OPER_FUNC_INVALID;
		  Error_or_Warning_Proc("08.04.01", ERROR_OCCURED, sys_error_or_warning_flag);
		  return sys_error_or_warning_flag;
	  }
	  
	  if(dev_src_basic_oper_func >= START_INPUT_DEV_BASIC_OPER_FUNC && dev_src_basic_oper_func <= END_INPUT_DEV_BASIC_OPER_FUNC )
	  {
		  if(dev_type != DEV_INPUT_TYPE)
		  {
			    sys_error_or_warning_flag = ERR_INPUT_DEV_ID_OPER_FUNC;
		        Error_or_Warning_Proc("08.11.03", ERROR_OCCURED, sys_error_or_warning_flag);
                return sys_error_or_warning_flag; 
		  }
          data_dev_basic_oper_func_ptr =  data_ids_dev_srcs[cur_data_id].data_input_dev_ids;
		  if((data_dev_basic_oper_func_ptr->dev_id < BEGIN_INPUT_DEV_ID || data_dev_basic_oper_func_ptr->dev_id > END_INPUT_DEV_ID) )
	      {
			  return SUCCESS;
	      }
	      min_dev_id = BEGIN_INPUT_DEV_ID;
		  max_dev_id = END_INPUT_DEV_ID;
		  max_data_dev_type_srcs = MAX_DATA_INPUT_DEVS;		 
	  }
	  else
	  {
	      if(dev_src_basic_oper_func >= START_OUTPUT_DEV_BASIC_OPER_FUNC && dev_src_basic_oper_func <= END_OUTPUT_DEV_BASIC_OPER_FUNC )
	      {
			 if(dev_type != DEV_OUTPUT_TYPE)
		     {
			    sys_error_or_warning_flag = ERR_OUTPUT_DEV_ID_OPER_FUNC;
		        Error_or_Warning_Proc("08.11.03", ERROR_OCCURED, sys_error_or_warning_flag);
                return sys_error_or_warning_flag; 
		    } 
             data_dev_basic_oper_func_ptr =  data_ids_dev_srcs[cur_data_id].data_output_dev_ids;
	         if((data_dev_basic_oper_func_ptr->dev_id < BEGIN_OUTPUT_DEV_ID || data_dev_basic_oper_func_ptr->dev_id > END_OUTPUT_DEV_ID) )
	         {
		         return SUCCESS;
	         }
		     min_dev_id = BEGIN_OUTPUT_DEV_ID;
		     max_dev_id = END_OUTPUT_DEV_ID;
		     max_data_dev_type_srcs = MAX_DATA_OUTPUT_DEVS;		 
	      }
		  else
		  {
			  switch(dev_type)
			  {
				  case DEV_RECEIVE_TYPE:      			    
				    data_dev_basic_oper_func_ptr = data_ids_dev_srcs[cur_data_id].data_receive_dev_ids;
					max_data_dev_type_srcs = MAX_DATA_RECEIVE_DEVS;
			      break;
				  case DEV_TRANSMIT_TYPE:
				     data_dev_basic_oper_func_ptr = data_ids_dev_srcs[cur_data_id].data_transmit_dev_ids; 
				     max_data_dev_type_srcs = MAX_DATA_TRANSMIT_DEVS;
				  break;	 
				  default: 	     
			        sys_error_or_warning_flag = ERR_COMM_DEV_ID_OPER_FUNC;
		            Error_or_Warning_Proc("08.11.03", ERROR_OCCURED, sys_error_or_warning_flag);
                    return sys_error_or_warning_flag; 
		      }			 
	         if((data_dev_basic_oper_func_ptr->dev_id < BEGIN_COMM_DEV_ID || data_dev_basic_oper_func_ptr->dev_id > END_COMM_DEV_ID))
	         {
		         return SUCCESS;  
	         }
		     min_dev_id = BEGIN_COMM_DEV_ID;
		     max_dev_id = END_COMM_DEV_ID;		    	  
		  }
	  }
	  i = 0; 
      if((cur_data_devs_src_allow_ptr + 0)->dev_id != CUR_DATA_ID_ALL_SRC_OF_SPEC_OPER)
	  {		  
	      for(j = 0; j < max_data_dev_type_srcs; ++j)
		  {
			 dev_src_allow_match_flag = STATE_NO;
		     if((cur_data_devs_src_allow_ptr + j )->dev_id == DEV_ID_INVALID)
			 {				
				 return SUCCESS;
			 }		 
	         while(i < max_data_dev_type_srcs && (data_dev_basic_oper_func_ptr + i)->dev_id >= min_dev_id && (data_dev_basic_oper_func_ptr + i)->dev_id <= max_dev_id )
	         {
                 if((cur_data_devs_src_allow_ptr + j )->dev_id == (data_dev_basic_oper_func_ptr + i)->dev_id )
			     {
				      if((cur_data_devs_src_allow_ptr + j )->dev_ch_id == (data_dev_basic_oper_func_ptr + i)->dev_ch_id)
				      {
					      if((ret_status = Cur_Data_ID_Dev_Src_Basic_Oper_Func(dev_src_basic_oper_func, data_dev_basic_oper_func_ptr + i)) != SUCCESS)
						  {
							  sys_error_or_warning_flag = ERR_DEV_SRC_BASIC_OPER_FUNC_INVALID;
							  Error_or_Warning_Proc("08.04.02", ERROR_OCCURED, sys_error_or_warning_flag);
							  return sys_error_or_warning_flag;
						  }
						  dev_src_allow_match_flag = STATE_YES;
				      }
				 }
				 if(dev_src_allow_match_flag == STATE_YES)
				 {
				     break; 		              		 
		         }
                 ++i; 
             }
			 if(dev_src_allow_match_flag == STATE_NO && (data_dev_basic_oper_func_ptr + i)->dev_id != DEV_ID_INVALID)
			 {
				 sys_error_or_warning_flag = ERR_CUR_DATA_DEV_SRC_ALLOW_NOT_SRC_LIST;
				 Error_or_Warning_Proc("08.04.03", ERROR_OCCURED, sys_error_or_warning_flag);
				 return sys_error_or_warning_flag;
			 }			       
		  }  
	  }
      else
      {
          i = 0;
		  while(i < max_data_dev_type_srcs && (data_dev_basic_oper_func_ptr + i)->dev_id >= min_dev_id && (data_dev_basic_oper_func_ptr + i)->dev_id <= max_dev_id )
	      {
              if((ret_status = Cur_Data_ID_Dev_Src_Basic_Oper_Func(dev_src_basic_oper_func, data_dev_basic_oper_func_ptr + i)) != SUCCESS)
			  {
				  sys_error_or_warning_flag = ERR_DEV_SRC_BASIC_OPER_FUNC_INVALID;
				  Error_or_Warning_Proc("08.04.04", ERROR_OCCURED, sys_error_or_warning_flag);
			      return sys_error_or_warning_flag;
		      } 
			  ++i;		      
		  } 
	  }	
	return SUCCESS;
}

/*------------------------------------------------------------*
FUNCTION NAME  : Cur_Data_ID_Output_Devs_Write_Oper_Func

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 08.05

BUGS           :    
-*------------------------------------------------------------*/
uint8_t Cur_Data_ID_Output_Devs_Write_Oper_Func(const dev_output_ctrl_para_t *const dev_output_ctrl_para_ptr)
{
	data_id_status_para_t *cur_data_id_status_para_ptr = NULL_PTR;
	data_value_ptr_with_type_t data_output_value;
  const dev_id_t *data_dev_write_oper;
	uint8_t ret_status = SUCCESS, i = 0;
	
    if(dev_output_ctrl_para_ptr == NULL_PTR)
	{
		sys_error_or_warning_flag = ERR_NULL_PTR;
		 Error_or_Warning_Proc("08.05.01", ERROR_OCCURED, sys_error_or_warning_flag);
		return sys_error_or_warning_flag;
	}		
	if(cur_data_id >= NUM_DATA_IDS)
	{
	   sys_error_or_warning_flag = ERR_DATA_ID_EXCEED;
	   Error_or_Warning_Proc("08.05.02", ERROR_OCCURED, sys_error_or_warning_flag);
	   return sys_error_or_warning_flag;
	}		   
	if(data_id_ctrl_para[cur_data_id].output_data_type == DATA_TYPE_IN_INVALID)
	{
		sys_error_or_warning_flag = ERR_DATA_TYPE_INVALID;
		Error_or_Warning_Proc("08.05.03", ERROR_OCCURED, sys_error_or_warning_flag);
	    return sys_error_or_warning_flag;
	}
	cur_data_id_status_para_ptr = data_id_status_para + cur_data_id;
	data_output_value.dev_output_ctrl_para_ptr = dev_output_ctrl_para_ptr;
	i = 0;	
    data_dev_write_oper =  data_ids_dev_srcs[cur_data_id].data_output_dev_ids;
	while(i < MAX_DATA_OUTPUT_DEVS && (data_dev_write_oper + i)->dev_id >= BEGIN_OUTPUT_DEV_ID && (data_dev_write_oper + i)->dev_id <= END_OUTPUT_DEV_ID )
	{
	    if(Dev_Oper_Func_Table[(data_dev_write_oper + i)->dev_id].Dev_Write_Func_Ptr == NULL_PTR)
	   {
		  sys_error_or_warning_flag = ERR_NULL_PTR;
		  Error_or_Warning_Proc("08.05.05", ERROR_OCCURED, sys_error_or_warning_flag);
          return sys_error_or_warning_flag; 
	   }
	   ret_status = (*Dev_Oper_Func_Table[(data_dev_write_oper + i)->dev_id].Dev_Write_Func_Ptr)((data_dev_write_oper + i)->dev_ch_id, &data_output_value);
	   switch(ret_status)
       {
           case SUCCESS:
           case WARN_CUR_DATA_ID_DEV_DISABLED: 
           case WARN_CUR_DATA_ID_DEV_NO_ACCESS: 
           break;           
           default: 
             sys_error_or_warning_flag = ERR_DEV_OPER_WRITE_FUNC;
             Error_or_Warning_Proc("08.05.04", ERROR_OCCURED, sys_error_or_warning_flag);
		     return sys_error_or_warning_flag;
       } 		
	   ++i;	  
	}
	return ret_status;	
}

/*------------------------------------------------------------*
FUNCTION NAME  : Set_Data_Devs_Src_Allow

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 08.06

BUGS           :    
-*------------------------------------------------------------*/
uint8_t Set_Data_Devs_Src_Allow(const uint8_t dev_type, const uint8_t data_dev_allow_type, dev_id_t *const cur_data_devs_src_allow_ptr)
{
  dev_id_t data_dev;
	uint8_t ret_status, i;
	
	if((ret_status = Reset_Data_Devs_Src_Allow(cur_data_devs_src_allow_ptr)) != SUCCESS)
	{
		sys_error_or_warning_flag = ERR_NULL_PTR;
		Error_or_Warning_Proc("08.06.01", ERROR_OCCURED, sys_error_or_warning_flag);
		return sys_error_or_warning_flag;
	}
	if(data_dev_allow_type == CUR_DATA_ID_ALL_SRC_OF_SPEC_OPER)
	{
		(cur_data_devs_src_allow_ptr + 0)->dev_id = CUR_DATA_ID_ALL_SRC_OF_SPEC_OPER;
		return SUCCESS;
	}
	switch(dev_type)
	{
		case DEV_INPUT_TYPE:
		   for(i = 0; i < MAX_DATA_INPUT_DEVS; ++i)
		   {
			  data_dev = data_ids_dev_srcs[cur_data_id].data_input_dev_ids[i];
              if(data_dev.dev_id == DEV_ID_INVALID)
              {
                   break;
			  }
			  *(cur_data_devs_src_allow_ptr + i) = data_dev;			   
		   }
        break;
        case DEV_OUTPUT_TYPE:
           for(i = 0; i < MAX_DATA_OUTPUT_DEVS; ++i)
		   {
			  data_dev = data_ids_dev_srcs[cur_data_id].data_output_dev_ids[i];
              if(data_dev.dev_id == DEV_ID_INVALID)
              {
                   break;
			  }
			  *(cur_data_devs_src_allow_ptr + i) = data_dev;	
		   }
        break;	
        case DEV_RECEIVE_TYPE:
		   for(i = 0; i < MAX_DATA_RECEIVE_DEVS; ++i)
		   {
			  data_dev = data_ids_dev_srcs[cur_data_id].data_receive_dev_ids[i];
              if(data_dev.dev_id == DEV_ID_INVALID)
              {
                   break;
			  }
			  *(cur_data_devs_src_allow_ptr + i) = data_dev;
		   }
        break;
		case DEV_TRANSMIT_TYPE:
		   for(i = 0; i < MAX_DATA_TRANSMIT_DEVS; ++i)
		   {
			  data_dev = data_ids_dev_srcs[cur_data_id].data_transmit_dev_ids[i];
              if(data_dev.dev_id == DEV_ID_INVALID)
              {
                   break;
			  }
			  *(cur_data_devs_src_allow_ptr + i) = data_dev;
		   }
        break;
        default:
		  sys_error_or_warning_flag = ERR_FORMAT_INVALID;
		  Error_or_Warning_Proc("08.06.02", ERROR_OCCURED, sys_error_or_warning_flag);
		  return sys_error_or_warning_flag;		
	}
	return SUCCESS;
}

/*------------------------------------------------------------*
FUNCTION NAME  :  Reset_Data_Devs_Src_Allow

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 08.07

BUGS           :    
-*------------------------------------------------------------*/
uint8_t Reset_Data_Devs_Src_Allow(dev_id_t *const cur_data_devs_src_allow_ptr)
{
	uint8_t i, cur_data_devs_allow_size =  MAX_NUM(MAX_NUM(MAX_DATA_INPUT_DEVS, MAX_DATA_OUTPUT_DEVS), MAX_NUM(MAX_DATA_RECEIVE_DEVS, MAX_DATA_TRANSMIT_DEVS) );
	
	if(cur_data_devs_src_allow_ptr == NULL_PTR)
	{
		 sys_error_or_warning_flag = ERR_NULL_PTR;
		 Error_or_Warning_Proc("08.07.01", ERROR_OCCURED, sys_error_or_warning_flag);
         return sys_error_or_warning_flag;
	}
	for(i = 0; i < cur_data_devs_allow_size; ++i)
	{
		(cur_data_devs_src_allow_ptr + i)->dev_id = DEV_ID_INVALID;
	}
	return SUCCESS;
}	

/*------------------------------------------------------------*
FUNCTION NAME  :  Cur_Data_ID_Dev_Src_Basic_Oper_Func

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 08.08

BUGS           :    
-*------------------------------------------------------------*/
static uint8_t Cur_Data_ID_Dev_Src_Basic_Oper_Func(const uint8_t dev_src_basic_oper_func, const dev_id_t *const dev_basic_oper_func_ptr)
{
	uint8_t ret_status;
	
	if(dev_basic_oper_func_ptr == NULL_PTR)
	{
		sys_error_or_warning_flag = ERR_NULL_PTR;
		Error_or_Warning_Proc("08.08.01", ERROR_OCCURED, sys_error_or_warning_flag);
		return sys_error_or_warning_flag;
	}
    switch(dev_src_basic_oper_func)
	{
         case INPUT_DEV_DEINIT_OPER_FUNC:
	     case OUTPUT_DEV_DEINIT_OPER_FUNC:
		 case COMM_DEV_DEINIT_OPER_FUNC:
             if(Dev_Oper_Func_Table[dev_basic_oper_func_ptr->dev_id].Dev_DeInit_Func_Ptr == NULL_PTR)
		     {
				sys_error_or_warning_flag = ERR_NULL_PTR;
				Error_or_Warning_Proc("08.08.03", ERROR_OCCURED, sys_error_or_warning_flag);
                return sys_error_or_warning_flag; 		        	
	        }
		    if((ret_status = (*Dev_Oper_Func_Table[dev_basic_oper_func_ptr->dev_id].Dev_DeInit_Func_Ptr)(dev_basic_oper_func_ptr->dev_ch_id)) != SUCCESS)
		    {
		    	sys_error_or_warning_flag = ERR_DEV_OPER_DEINIT_FUNC;
				Error_or_Warning_Proc("08.08.02", ERROR_OCCURED, sys_error_or_warning_flag);
				return sys_error_or_warning_flag;
		    } 	
    	 break;
	     case INPUT_DEV_INIT_OPER_FUNC:
		 case OUTPUT_DEV_INIT_OPER_FUNC:
		 case COMM_DEV_INIT_OPER_FUNC:
		     if(Dev_Oper_Func_Table[dev_basic_oper_func_ptr->dev_id].Dev_Init_Func_Ptr == NULL_PTR)
		     {
		        sys_error_or_warning_flag = ERR_NULL_PTR;
				Error_or_Warning_Proc("08.08.05", ERROR_OCCURED, sys_error_or_warning_flag);
                return sys_error_or_warning_flag;
					
	         }
		     if((ret_status = (*Dev_Oper_Func_Table[dev_basic_oper_func_ptr->dev_id].Dev_Init_Func_Ptr)(dev_basic_oper_func_ptr->dev_ch_id)) != SUCCESS)
			 {
			        sys_error_or_warning_flag = ERR_DEV_OPER_INIT_FUNC;
					Error_or_Warning_Proc("08.08.04", ERROR_OCCURED, sys_error_or_warning_flag);
				    return sys_error_or_warning_flag;
		     } 	
		 break;
		 case INPUT_DEV_NO_ACCESS_OPER_FUNC:
		 case OUTPUT_DEV_NO_ACCESS_OPER_FUNC:
		 case COMM_DEV_NO_ACCESS_OPER_FUNC:
		    if(Dev_Oper_Func_Table[dev_basic_oper_func_ptr->dev_id].Dev_No_Access_Func_Ptr == NULL_PTR)
		    {
				sys_error_or_warning_flag = ERR_NULL_PTR;
				Error_or_Warning_Proc("08.08.07", ERROR_OCCURED, sys_error_or_warning_flag);
                return sys_error_or_warning_flag;
		        		
	        }
		    if((ret_status = (*Dev_Oper_Func_Table[dev_basic_oper_func_ptr->dev_id].Dev_No_Access_Func_Ptr)(dev_basic_oper_func_ptr->dev_ch_id)) != SUCCESS)
		        {
		    	      sys_error_or_warning_flag = ERR_DEV_OPER_NO_ACCESS_FUNC;
					  Error_or_Warning_Proc("08.08.06", ERROR_OCCURED, sys_error_or_warning_flag);
			          return sys_error_or_warning_flag;
		        } 
        break;
        case INPUT_DEV_ALLOW_ACCESS_OPER_FUNC:
		case OUTPUT_DEV_ALLOW_ACCESS_OPER_FUNC:
		case COMM_DEV_ALLOW_ACCESS_OPER_FUNC:
		    if(Dev_Oper_Func_Table[dev_basic_oper_func_ptr->dev_id].Dev_Allow_Access_Func_Ptr == NULL_PTR)
		    {
				sys_error_or_warning_flag = ERR_NULL_PTR;
				Error_or_Warning_Proc("08.08.09", ERROR_OCCURED, sys_error_or_warning_flag);
                return sys_error_or_warning_flag;		        		
	        }
		    if((ret_status = (*Dev_Oper_Func_Table[dev_basic_oper_func_ptr->dev_id].Dev_Allow_Access_Func_Ptr)(dev_basic_oper_func_ptr->dev_ch_id)) != SUCCESS)
		        {
				      sys_error_or_warning_flag = ERR_DEV_OPER_ALLOW_ACCESS_FUNC;
					  Error_or_Warning_Proc("08.08.08", ERROR_OCCURED, sys_error_or_warning_flag);
				      return sys_error_or_warning_flag;
		        } 
        break;
        case	INPUT_DEV_DISABLE_OPER_FUNC:
		case	OUTPUT_DEV_DISABLE_OPER_FUNC:
		case	COMM_DEV_DISABLE_OPER_FUNC:
		   if(Dev_Oper_Func_Table[dev_basic_oper_func_ptr->dev_id].Dev_Disable_Func_Ptr == NULL_PTR)
		   {
			   sys_error_or_warning_flag = ERR_NULL_PTR;
				 Error_or_Warning_Proc("08.08.11", ERROR_OCCURED, sys_error_or_warning_flag);
                return sys_error_or_warning_flag;
		       		
	      }
		  if((ret_status = (*Dev_Oper_Func_Table[dev_basic_oper_func_ptr->dev_id].Dev_Disable_Func_Ptr)(dev_basic_oper_func_ptr->dev_ch_id)) != SUCCESS)
		       {
			      sys_error_or_warning_flag = ERR_DEV_OPER_DISABLE_FUNC;
				  Error_or_Warning_Proc("08.08.10", ERROR_OCCURED, sys_error_or_warning_flag);
			      return sys_error_or_warning_flag;
		       } 
        break;
        case  INPUT_DEV_ENABLE_OPER_FUNC:
        case  OUTPUT_DEV_ENABLE_OPER_FUNC: 
        case  COMM_DEV_ENABLE_OPER_FUNC: 
		   if(Dev_Oper_Func_Table[dev_basic_oper_func_ptr->dev_id].Dev_Enable_Func_Ptr == NULL_PTR)
		   {
			   sys_error_or_warning_flag = ERR_NULL_PTR;
				Error_or_Warning_Proc("08.08.13", ERROR_OCCURED, sys_error_or_warning_flag);
                return sys_error_or_warning_flag;		      		
	       }
		   if((ret_status = (*Dev_Oper_Func_Table[dev_basic_oper_func_ptr->dev_id].Dev_Enable_Func_Ptr)(dev_basic_oper_func_ptr->dev_ch_id)) != SUCCESS)
		      {
			      sys_error_or_warning_flag = ERR_DEV_OPER_ENABLE_FUNC;
				  Error_or_Warning_Proc("08.08.12", ERROR_OCCURED, sys_error_or_warning_flag);
			      return sys_error_or_warning_flag;
		      } 
        break;
        default:
		    sys_error_or_warning_flag = ERR_DEV_SRC_BASIC_OPER_FUNC_INVALID;
			Error_or_Warning_Proc("08.08.14", ERROR_OCCURED, sys_error_or_warning_flag);
		    return sys_error_or_warning_flag;
    }
	return SUCCESS;
}

/*------------------------------------------------------------*
FUNCTION NAME  : Cur_Data_ID_Comm_Devs_Receive_Oper_Func

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 08.09

BUGS           :    
-*------------------------------------------------------------*/
uint8_t Cur_Data_ID_Comm_Devs_Receive_Oper_Func(unsigned char *const last_rcvd_data_char_ptr)
{
 	data_id_status_para_t *cur_data_id_status_para_ptr = NULL_PTR;
  const dev_id_t *data_dev_receive_oper_func;
	uint8_t ret_status = SUCCESS, i = 0; 
		
	if(cur_data_id >= NUM_DATA_IDS)
	{
	   sys_error_or_warning_flag = ERR_DATA_ID_EXCEED;
	   Error_or_Warning_Proc("08.09.01", ERROR_OCCURED, sys_error_or_warning_flag);
	   return sys_error_or_warning_flag;
	}
	cur_data_id_status_para_ptr = data_id_status_para + cur_data_id;
	if(cur_data_id_status_para_ptr->data_input_status.max_try_reached_flag == STATE_YES)
	{
	    	return CUR_DATA_ID_INPUT_MAX_TRIED;
	}
	if(cur_data_id_status_para_ptr->data_input_status.last_try_read_and_ready_to_process_flag == STATE_YES)
	{
		    return CUR_DATA_ID_LAST_TRY_COMPLETE_READ_AND_READY_PROCESS;
	}
	if(cur_data_id_status_para_ptr->data_input_status.read_and_ready_to_process_flag == STATE_YES)
	{
		    return CUR_DATA_ID_UNTIL_LAST_TRY_COMPLETE_READ_AND_READY_PROCESS;
	}
		
	i = 0;
    data_dev_receive_oper_func =  data_ids_dev_srcs[cur_data_id].data_receive_dev_ids;
	while(i < MAX_DATA_RECEIVE_DEVS && (data_dev_receive_oper_func + i)->dev_id >= BEGIN_COMM_DEV_ID && (data_dev_receive_oper_func + i)->dev_id <= END_COMM_DEV_ID )
	{
	   if(Dev_Oper_Func_Table[(data_dev_receive_oper_func + i)->dev_id].Dev_Receive_Func_Ptr == NULL_PTR)
	   {
	 	  sys_error_or_warning_flag = ERR_NULL_PTR;
		  Error_or_Warning_Proc("08.09.04", ERROR_OCCURED, sys_error_or_warning_flag);
          return sys_error_or_warning_flag;
	   }
	   ret_status = (*Dev_Oper_Func_Table[(data_dev_receive_oper_func + i)->dev_id].Dev_Receive_Func_Ptr)((data_dev_receive_oper_func + i)->dev_ch_id, last_rcvd_data_char_ptr);
	   switch(ret_status)
       {
           case COMM_RCVD_CHAR:
           case COMM_NO_RCV_CHAR:
           case WARN_CUR_DATA_ID_DEV_DISABLED: 
           case WARN_CUR_DATA_ID_DEV_NO_ACCESS: 
           break;           
           default: 
               sys_error_or_warning_flag = ERR_DEV_OPER_RECEIVE_FUNC;
			   Error_or_Warning_Proc("08.09.02", ERROR_OCCURED, sys_error_or_warning_flag);
			   return sys_error_or_warning_flag;
         }	      
          ret_status = Dev_Oper_Read_Status_Proc(ret_status, *last_rcvd_data_char_ptr);    
		  switch(ret_status)
		  {
			  case ERR_DEV_OPER_READ_FUNC:
			    sys_error_or_warning_flag = ret_status;
				Error_or_Warning_Proc("08.09.03", ERROR_OCCURED, sys_error_or_warning_flag);
              case CUR_DATA_ID_LAST_TRY_COMPLETE_READ_AND_READY_PROCESS:
			  case CUR_DATA_ID_COMPLETE_READ_AND_READY_PROCESS:
			     return ret_status;
			  //break;	
		  } 
	   ++i;	   
	}
	return ret_status;	
}

/*------------------------------------------------------------*
FUNCTION NAME  : Data_ID_Src_Spec_Dev_Find_Dev_Ch_ID

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : Specified Device should be unique, if specified Device is present in the corresponding data_ids_dev_srcs[cur_data_id] list, 
                  then Specified Device's dev ch id is returned.
                 If specified Device is not unique, then from the index 0, if specified device is present in the corresponding data_ids_dev_srcs[cur_data_id] list, 
				 then first specified Device's dev ch id is returned.

Func ID        : 08.10

BUGS           :    
-*------------------------------------------------------------*/
uint8_t Data_ID_Src_Spec_Dev_Find_Dev_Ch_ID(const uint8_t data_id, dev_id_t *const dev_data_ptr, const uint8_t dev_type)
{
	const dev_id_t *cur_search_dev_ptr;
	uint8_t i = 0, max_data_dev_type_srcs, ret_status;
	
	if(data_id >= NUM_DATA_IDS)
	{
		sys_error_or_warning_flag = ERR_DATA_ID_EXCEED;
	    Error_or_Warning_Proc("08.10.02", ERROR_OCCURED, sys_error_or_warning_flag);
	    return sys_error_or_warning_flag;
	}
	if((ret_status = Dev_ID_Validate(dev_data_ptr, dev_type)) != SUCCESS)
	{
		sys_error_or_warning_flag = ERR_DEV_ID_INVALID;
	    Error_or_Warning_Proc("08.10.02", ERROR_OCCURED, sys_error_or_warning_flag);
	    return sys_error_or_warning_flag;
	}
    switch(dev_type)
	{
       case DEV_INPUT_TYPE:
           cur_search_dev_ptr =  data_ids_dev_srcs[data_id].data_input_dev_ids;		
	       max_data_dev_type_srcs = MAX_DATA_INPUT_DEVS;	
	   break;
       case DEV_OUTPUT_TYPE:
      	cur_search_dev_ptr =  data_ids_dev_srcs[data_id].data_output_dev_ids;
	  	max_data_dev_type_srcs = MAX_DATA_OUTPUT_DEVS;
	   break;
	   case DEV_RECEIVE_TYPE:
	     cur_search_dev_ptr =  data_ids_dev_srcs[data_id].data_receive_dev_ids;
		 max_data_dev_type_srcs = MAX_DATA_RECEIVE_DEVS;
	   break;
	   case DEV_TRANSMIT_TYPE:
	     cur_search_dev_ptr =  data_ids_dev_srcs[data_id].data_transmit_dev_ids;
		 max_data_dev_type_srcs = MAX_DATA_TRANSMIT_DEVS;
	   break;	 
	}
	i = 0;  
  while( i < max_data_dev_type_srcs && ((cur_search_dev_ptr + i)->dev_id != dev_data_ptr->dev_id) )
	{
		++i;
	}
  if(i >= max_data_dev_type_srcs)
	{
	  	sys_error_or_warning_flag = ERR_DEV_ID_NOT_MATCH;
 	    Error_or_Warning_Proc("08.10.04", ERROR_OCCURED, sys_error_or_warning_flag);
      return sys_error_or_warning_flag;
	}
    dev_data_ptr->dev_ch_id = (cur_search_dev_ptr + i)->dev_ch_id;
	return SUCCESS;  
}

/*------------------------------------------------------------*
FUNCTION NAME  : Dev_ID_Validate

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 08.11

BUGS           :    
-*------------------------------------------------------------*/
uint8_t Dev_ID_Validate(dev_id_t *const dev_data_ptr, const uint8_t dev_type)
{
	if(dev_data_ptr == NULL_PTR)
	{
		 sys_error_or_warning_flag = ERR_NULL_PTR;
		 Error_or_Warning_Proc("08.11.01", ERROR_OCCURED, sys_error_or_warning_flag);
         return sys_error_or_warning_flag;
	}	
	
	 if(!((dev_data_ptr->dev_id >= BEGIN_COMM_DEV_ID && dev_data_ptr->dev_id <= END_COMM_DEV_ID) || 
	  (dev_data_ptr->dev_id >= BEGIN_OUTPUT_DEV_ID && dev_data_ptr->dev_id <= END_OUTPUT_DEV_ID) ||
      (dev_data_ptr->dev_id >= BEGIN_INPUT_DEV_ID && dev_data_ptr->dev_id <= END_INPUT_DEV_ID)))
	{
		 sys_error_or_warning_flag = ERR_DEV_ID_INVALID;
		 Error_or_Warning_Proc("08.11.02", ERROR_OCCURED, sys_error_or_warning_flag);
         return sys_error_or_warning_flag;
	}	
	switch(dev_type)
	{
		case DEV_INPUT_TYPE:
		   if(!(dev_data_ptr->dev_id >= BEGIN_INPUT_DEV_ID && dev_data_ptr->dev_id <= END_INPUT_DEV_ID))
		   {
			    sys_error_or_warning_flag = ERR_INPUT_DEV_ID_OPER_FUNC;
		        Error_or_Warning_Proc("08.11.03", ERROR_OCCURED, sys_error_or_warning_flag);
                return sys_error_or_warning_flag;
		   }
		break;
		case DEV_OUTPUT_TYPE:
		   if(!(dev_data_ptr->dev_id >= BEGIN_OUTPUT_DEV_ID && dev_data_ptr->dev_id <= END_OUTPUT_DEV_ID))
		   {
			    sys_error_or_warning_flag = ERR_OUTPUT_DEV_ID_OPER_FUNC;
		        Error_or_Warning_Proc("08.11.04", ERROR_OCCURED, sys_error_or_warning_flag);
                return sys_error_or_warning_flag;
		   }
		break;
		case DEV_TRANSMIT_TYPE:
		case DEV_RECEIVE_TYPE:
		  if(!(dev_data_ptr->dev_id >= BEGIN_COMM_DEV_ID && dev_data_ptr->dev_id <= END_COMM_DEV_ID))
		  {
			    sys_error_or_warning_flag = ERR_COMM_DEV_ID_OPER_FUNC;
		        Error_or_Warning_Proc("08.11.05", ERROR_OCCURED, sys_error_or_warning_flag);
                return sys_error_or_warning_flag; 
		  }
		break;
		default:
		  sys_error_or_warning_flag = ERR_FORMAT_INVALID;
		  Error_or_Warning_Proc("08.11.06", ERROR_OCCURED, sys_error_or_warning_flag);
         return sys_error_or_warning_flag;
	}
	return SUCCESS;
}

/*------------------------------------------------------------*
FUNCTION NAME  : Data_ID_Input_Try_Complete_Proc

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 08.12

BUGS           :    
-*------------------------------------------------------------*/
static uint8_t Data_ID_Input_Try_Complete_Proc(const uint8_t data_id)
{
	data_id_status_para_t *cur_data_id_status_para_ptr = NULL_PTR;
	const data_id_ctrl_para_t *cur_data_id_ctrl_para_ptr;
	
	if(data_id >= NUM_DATA_IDS)
	{
	   sys_error_or_warning_flag = ERR_DATA_ID_EXCEED;
	   Error_or_Warning_Proc("08.12.01", ERROR_OCCURED, sys_error_or_warning_flag);
	   return sys_error_or_warning_flag;
	}
	cur_data_id_status_para_ptr = data_id_status_para + data_id;
	cur_data_id_ctrl_para_ptr = data_id_ctrl_para + data_id;
	
	++cur_data_id_status_para_ptr->data_input_num_try;
	#ifdef SHOULD_REMOVE
	    disp_trace_num_fmt.sign_flag = STATE_NO;
	    disp_trace_num_fmt.least_digits_flag = STATE_YES;
	    disp_trace_num_fmt.left_format_flag = STATE_YES;
	    disp_trace_num_fmt.num_digits = 3;
		UART_Transmit_Str(TRACE_UART_CH_ID, "\r Retry: data_id : ");
		UART_Transmit_Num(TRACE_UART_CH_ID, DATA_TYPE_IN_DECIMAL, disp_trace_num_fmt, data_id );
		UART_Transmit_Str(TRACE_UART_CH_ID, ", times : ");
		UART_Transmit_Num(TRACE_UART_CH_ID, DATA_TYPE_IN_DECIMAL, disp_trace_num_fmt, cur_data_id_status_para_ptr->data_input_num_try );
	#endif
    if(cur_data_id_status_para_ptr->data_input_num_try < cur_data_id_ctrl_para_ptr->max_num_data_input_try)
	{
		 cur_data_id_status_para_ptr->data_input_status.read_and_ready_to_process_flag = STATE_YES;
	     return CUR_DATA_ID_UNTIL_LAST_TRY_COMPLETE_READ_AND_READY_PROCESS;
	}
	else if(cur_data_id_status_para_ptr->data_input_num_try == cur_data_id_ctrl_para_ptr->max_num_data_input_try)
	{
		 cur_data_id_status_para_ptr->data_input_status.read_and_ready_to_process_flag = STATE_YES;
	     cur_data_id_status_para_ptr->data_input_status.last_try_read_and_ready_to_process_flag = STATE_YES;
		return CUR_DATA_ID_LAST_TRY_COMPLETE_READ_AND_READY_PROCESS;
    }					 
	cur_data_id_status_para_ptr->data_input_status.max_try_reached_flag = STATE_YES;
	cur_data_id_status_para_ptr->data_input_status.read_and_ready_to_process_flag = STATE_NO;
	cur_data_id_status_para_ptr->data_input_status.last_try_read_and_ready_to_process_flag = STATE_NO;
	return CUR_DATA_ID_INPUT_MAX_TRIED;
}

/*------------------------------------------------------------------*-
  ------------------------ END OF FILE ------------------------------
-*------------------------------------------------------------------*/
