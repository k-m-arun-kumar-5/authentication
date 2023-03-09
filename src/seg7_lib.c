/* ********************************************************************
FILE                   : seg7_lib.c

PURPOSE                : 
                     									 	 
AUTHOR                : K.M. Arun Kumar alias Arunkumar Murugeswaran
	 
KNOWN BUGS            : 

NOTE                  : 
                       
CHANGE LOGS           : 

FILE ID               : 06 

*****************************************************************************/

#include "main.h"

#ifdef SEG7_MOD_ENABLE

/* ------------------------------ macro defination ------------------------------ */

/* ----------------------------- global variable defination --------------------- */

/* ----------------------------- global variable declaration -------------------- */

/* ----------------------------- global function declaration -------------------- */

/* ----------------------------- const function pointer defination -------------- */


/*------------------------------------------------------------*-
FUNCTION NAME  : Seg7_Write

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 06.01 

BUGS           :
-*------------------------------------------------------------*/
uint8_t Seg7_Write(const uint8_t seg7_ch_id, const void *const seg7_rcv_disp_num_ptr)
{
    int32_t seg7_num, cur_seg7_num;	
	uint32_t base_power_val;	
	data_value_ptr_with_type_t *seg7_data_write_ptr;		
    seg7_ctrl_t *cur_seg7_ctrl_ptr = NULL_PTR;
	char *seg7_str_ptr;
	char retrieved_seg7_data_str[DATA_MAX_NUM_ALLOCATED_CHARS];
	consucc_bit_t consucc_bit_data;
    int16_t place_val, repeat;
	uint8_t cc_digit[] = {0x3F, 0x06, 0x5B, 0x4F,0x66,0x6D, 0x7D, 0x07, 0x7F, 0x6F}, ret_status = SUCCESS, base;
    uint8_t place_digit[MAX_SEG7_DIGITS], i, output_data_type ;     
	
	
    if(seg7_rcv_disp_num_ptr == NULL_PTR)
	{
		sys_error_or_warning_flag = ERR_NULL_PTR;
		Error_or_Warning_Proc("06.01.01", ERROR_OCCURED, sys_error_or_warning_flag);
		return sys_error_or_warning_flag;
	}
    if(seg7_ch_id >= NUM_OUTPUT_DEV_ID_SEG7_CHS)
	{
		   sys_error_or_warning_flag = ERR_DEV_CH_ID_EXCEEDS;
		   Error_or_Warning_Proc("06.01.02", ERROR_OCCURED, sys_error_or_warning_flag);
		   return sys_error_or_warning_flag;
	}	
	cur_seg7_ctrl_ptr = seg7_ctrl + seg7_ch_id;     
	if(  cur_seg7_ctrl_ptr->access_flag != STATE_YES) 
	   {  
          sys_error_or_warning_flag = WARN_CUR_DATA_ID_DEV_NO_ACCESS;
		  Error_or_Warning_Proc("06.01.03", ERROR_OCCURED, sys_error_or_warning_flag);
          return  sys_error_or_warning_flag;
	   }
		 
	   if( cur_seg7_ctrl_ptr->enable_flag != STATE_YES) 
	   {  
          sys_error_or_warning_flag = WARN_CUR_DATA_ID_DEV_DISABLED;
		  Error_or_Warning_Proc("06.01.04", ERROR_OCCURED, sys_error_or_warning_flag);
          return  sys_error_or_warning_flag;
	   }
     
     seg7_data_write_ptr  = (data_value_ptr_with_type_t *)seg7_rcv_disp_num_ptr;
	if((ret_status = Appl_Data_Retrieve_Para(cur_data_id, DATA_RETRIEVE_CTRL_OUTPUT_DATA_TYPE, &output_data_type)) != SUCCESS)
	{
		sys_error_or_warning_flag = ERR_APPL_DATA_RETRIEVE;
		Error_or_Warning_Proc("06.01.05", ERROR_OCCURED, sys_error_or_warning_flag);
		return sys_error_or_warning_flag; 
	}	 
	 switch(output_data_type)
	 {
		case DATA_TYPE_IN_STR:
		   if((ret_status = Appl_Data_Retrieve_Para(cur_data_id, DATA_RETRIEVE_STATUS_DATA_STR, retrieved_seg7_data_str )) != SUCCESS)
		   {
				  sys_error_or_warning_flag = ERR_APPL_DATA_RETRIEVE;
				  Error_or_Warning_Proc("06.01.06", ERROR_OCCURED, sys_error_or_warning_flag);
				  return sys_error_or_warning_flag; 
		   }
		  if((ret_status = Str_to_Num_Conv(&seg7_num, retrieved_seg7_data_str)) != SUCCESS)
		  {
			  sys_error_or_warning_flag = ERR_FORMAT_INVALID;
			  Error_or_Warning_Proc("06.01.07", ERROR_OCCURED, sys_error_or_warning_flag);
              return sys_error_or_warning_flag;
		  }
		  base = 10;
		break;
		case DATA_TYPE_IN_CHAR:
		   if((ret_status = Appl_Data_Retrieve_Para(cur_data_id, DATA_RETRIEVE_STATUS_DATA_CHAR, retrieved_seg7_data_str )) != SUCCESS)
		   {
				  sys_error_or_warning_flag = ERR_APPL_DATA_RETRIEVE;
				  Error_or_Warning_Proc("06.01.08", ERROR_OCCURED, sys_error_or_warning_flag);
				  return sys_error_or_warning_flag; 
		   }	
		  seg7_num = retrieved_seg7_data_str[0] - NUM_0_CHAR;
		  if(seg7_num < 0 || seg7_num > 9 || cur_seg7_ctrl_ptr->num_digits != 1)
		  {
			  sys_error_or_warning_flag = ERR_FORMAT_INVALID;
			  Error_or_Warning_Proc("06.01.09", ERROR_OCCURED, sys_error_or_warning_flag);
              return sys_error_or_warning_flag; 
		  }
		   base = 10;		   
		break;
		case DATA_TYPE_IN_BINARY:
		     if(cur_seg7_ctrl_ptr->num_digits <= 0 || cur_seg7_ctrl_ptr->num_digits > MAX_SEG7_DIGITS)
		     {
		         sys_error_or_warning_flag = ERR_FORMAT_INVALID;
				 Error_or_Warning_Proc("06.01.10", ERROR_OCCURED, sys_error_or_warning_flag);
                 return sys_error_or_warning_flag;
		     }	 
      		base = 2;
			if((ret_status = Appl_Data_Retrieve_Para(cur_data_id, DATA_RETRIEVE_STATUS_DATA_INT32, &seg7_num )) != SUCCESS)
		   {
				  sys_error_or_warning_flag = ERR_APPL_DATA_RETRIEVE;
				  Error_or_Warning_Proc("06.01.11", ERROR_OCCURED, sys_error_or_warning_flag);
				  return sys_error_or_warning_flag; 
		   } 
			 
        break;			
		case DATA_TYPE_IN_HEXA:
		    if(cur_seg7_ctrl_ptr->num_digits <= 0 || cur_seg7_ctrl_ptr->num_digits > MAX_SEG7_DIGITS)
		     {
		         sys_error_or_warning_flag = ERR_FORMAT_INVALID;
				 Error_or_Warning_Proc("06.01.12", ERROR_OCCURED, sys_error_or_warning_flag);
                 return sys_error_or_warning_flag;
		     }
		    base = 16;
			if((ret_status = Appl_Data_Retrieve_Para(cur_data_id, DATA_RETRIEVE_STATUS_DATA_INT32, &seg7_num )) != SUCCESS)
		    {
				  sys_error_or_warning_flag = ERR_APPL_DATA_RETRIEVE;
				  Error_or_Warning_Proc("06.01.13", ERROR_OCCURED, sys_error_or_warning_flag);
				  return sys_error_or_warning_flag; 
		    } 	 			
	    break;		
		case DATA_TYPE_IN_DECIMAL:
		    if(cur_seg7_ctrl_ptr->num_digits <= 0 || cur_seg7_ctrl_ptr->num_digits > MAX_SEG7_DIGITS)
		    {
		         sys_error_or_warning_flag = ERR_FORMAT_INVALID;
				 Error_or_Warning_Proc("06.01.14", ERROR_OCCURED, sys_error_or_warning_flag);
                 return sys_error_or_warning_flag;
		    }  
		   base = 10;
		   if((ret_status = Appl_Data_Retrieve_Para(cur_data_id, DATA_RETRIEVE_STATUS_DATA_INT32, &seg7_num )) != SUCCESS)
		   {
				  sys_error_or_warning_flag = ERR_APPL_DATA_RETRIEVE;
				  Error_or_Warning_Proc("06.01.15", ERROR_OCCURED, sys_error_or_warning_flag);
				  return sys_error_or_warning_flag; 
		   }    
		break;  		
		default:
		   sys_error_or_warning_flag = ERR_DATA_TYPE_INVALID;
		   Error_or_Warning_Proc("06.01.16", ERROR_OCCURED, sys_error_or_warning_flag);
		   return sys_error_or_warning_flag;
	}
	for(i = 0; i < cur_seg7_ctrl_ptr->num_digits; ++i)
	{
		 if((ret_status = IO_Channel_Write(cur_seg7_ctrl_ptr->io_ch_unit_digit + i,  STATE_LOW)) != SUCCESS)
		 {						 
		      sys_error_or_warning_flag = ERR_SEG7_NO_WRITE;
			  Error_or_Warning_Proc("06.01.17", ERROR_OCCURED, sys_error_or_warning_flag);
		      return sys_error_or_warning_flag;  
		 } 
    }
  consucc_bit_data.start_bit_pos = cur_seg7_ctrl_ptr->io_ch_a_led % NUM_PINS_PER_PORT;
  consucc_bit_data.bits_len = 8;    
	for(repeat = 0; repeat < REQ_CNT_SEG7_REPEAT_NUM; ++repeat)
	{
          cur_seg7_num = seg7_num;
		  base_power_val =  Power_Of(base, cur_seg7_ctrl_ptr->num_digits);
		  for(place_val = cur_seg7_ctrl_ptr->num_digits - 1; place_val >= 0; --place_val)
		  {
		     cur_seg7_num %= base_power_val;
		     base_power_val /= base; 
		     place_digit[place_val] =  cur_seg7_num /base_power_val;		     
			 if(cur_seg7_ctrl_ptr->seg7_type == SEG7_COMMON_CATHODE)   
             {       
		        consucc_bit_data.write_or_config_consucc_val = 0;
             }
             else
             {
                 consucc_bit_data.write_or_config_consucc_val = 0xFF;
             }
		     if((ret_status = Port_Write(cur_seg7_ctrl_ptr->io_ch_a_led, &consucc_bit_data)) != SUCCESS)
		     {
			    sys_error_or_warning_flag = ERR_SEG7_NO_WRITE;
				Error_or_Warning_Proc("06.01.18", ERROR_OCCURED, sys_error_or_warning_flag);
			    return sys_error_or_warning_flag;
		     }				
		     if((ret_status = IO_Channel_Write(cur_seg7_ctrl_ptr->io_ch_unit_digit + place_val ,  STATE_HIGH)) != SUCCESS)
		     {						 
			     sys_error_or_warning_flag = ERR_SEG7_NO_WRITE;
				 Error_or_Warning_Proc("06.01.19", ERROR_OCCURED, sys_error_or_warning_flag);
			     return sys_error_or_warning_flag;  
		     } 
		     
             if(cur_seg7_ctrl_ptr->seg7_type == SEG7_COMMON_CATHODE)   
             {       
		        consucc_bit_data.write_or_config_consucc_val = cc_digit[place_digit[place_val]];
             }
             else
             {
                 consucc_bit_data.write_or_config_consucc_val = ~cc_digit[place_digit[place_val]] & 0xFF; ;
             }
		     if((ret_status = Port_Write(cur_seg7_ctrl_ptr->io_ch_a_led, &consucc_bit_data)) != SUCCESS)
		     {
			    sys_error_or_warning_flag = ERR_SEG7_NO_WRITE;
				Error_or_Warning_Proc("06.01.20", ERROR_OCCURED, sys_error_or_warning_flag);
			    return sys_error_or_warning_flag;
		     }			 
             SW_Time_Delay(MAX_ICOUNT_7SEG_SW_DELAY, MAX_JCOUNT_7SEG_SW_DELAY);	
		
		    if((ret_status = IO_Channel_Write(cur_seg7_ctrl_ptr->io_ch_unit_digit + place_val,  STATE_LOW)) != SUCCESS)
		    {						 
			   sys_error_or_warning_flag = ERR_SEG7_NO_WRITE;
			   Error_or_Warning_Proc("06.01.21", ERROR_OCCURED, sys_error_or_warning_flag);
			   return sys_error_or_warning_flag;  
		    }
		} 		
	}	
  return SUCCESS;
}

/*------------------------------------------------------------*
FUNCTION NAME  : Seg7_Disable

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 06.02  

Bugs           :  
-*------------------------------------------------------------*/
uint8_t Seg7_Disable(const uint8_t seg7_ch_id)
{
	 seg7_ctrl_t *cur_seg7_ctrl_ptr = NULL_PTR;
	
	 if(seg7_ch_id >= NUM_OUTPUT_DEV_ID_SEG7_CHS)
	 {
		  sys_error_or_warning_flag = ERR_DEV_CH_ID_EXCEEDS;
		  return sys_error_or_warning_flag;
	 }
	 cur_seg7_ctrl_ptr = seg7_ctrl + seg7_ch_id ;  
   cur_seg7_ctrl_ptr->enable_flag = STATE_NO;
	 
   return SUCCESS;
}
/*------------------------------------------------------------*
FUNCTION NAME  : Seg7_Enable

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 06.03  

Bugs           :  
-*------------------------------------------------------------*/
uint8_t Seg7_Enable(const uint8_t seg7_ch_id)
{
	 seg7_ctrl_t *cur_seg7_ctrl_ptr = NULL_PTR;
	
	 if(seg7_ch_id >= NUM_OUTPUT_DEV_ID_SEG7_CHS)
	 {
		  sys_error_or_warning_flag = ERR_DEV_CH_ID_EXCEEDS;
		  return sys_error_or_warning_flag;
	 }
	 cur_seg7_ctrl_ptr = seg7_ctrl + seg7_ch_id ;  
   cur_seg7_ctrl_ptr->enable_flag = STATE_YES;
   return SUCCESS;
}

/*------------------------------------------------------------*
FUNCTION NAME  : Disable_All_Seg7s

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 06.04  

Bugs           :  
-*------------------------------------------------------------*/
uint8_t Disable_All_Seg7s(void)
{
	 uint8_t seg7_ch_id =0;
	
	 for(seg7_ch_id = 0; seg7_ch_id < NUM_OUTPUT_DEV_ID_SEG7_CHS; ++seg7_ch_id)
	 {
		   Seg7_Disable(seg7_ch_id);
	 }
	 return SUCCESS;
}

/*------------------------------------------------------------*
FUNCTION NAME  : Seg7_Allow_Access

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 06.05 

Bugs           :  
-*------------------------------------------------------------*/
uint8_t Seg7_Allow_Access(const uint8_t seg7_ch_id)
{
	 seg7_ctrl_t *cur_seg7_ctrl_ptr = NULL_PTR;
	
	 if(seg7_ch_id >= NUM_OUTPUT_DEV_ID_SEG7_CHS)
	 {
		  sys_error_or_warning_flag = ERR_DEV_CH_ID_EXCEEDS;
		  return sys_error_or_warning_flag;
	 }
	  cur_seg7_ctrl_ptr = seg7_ctrl + seg7_ch_id ;  
    cur_seg7_ctrl_ptr->access_flag = STATE_YES;
	 return SUCCESS;
}

/*------------------------------------------------------------*
FUNCTION NAME  : Seg7_No_Access

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 06.06 

Bugs           :  
-*------------------------------------------------------------*/
uint8_t Seg7_No_Access(const uint8_t seg7_ch_id)
{
	 seg7_ctrl_t *cur_seg7_ctrl_ptr = NULL_PTR;
	
	 if(seg7_ch_id >= NUM_OUTPUT_DEV_ID_SEG7_CHS)
	 {
		  sys_error_or_warning_flag = ERR_DEV_CH_ID_EXCEEDS;
		  return sys_error_or_warning_flag;
	 }
	 cur_seg7_ctrl_ptr = seg7_ctrl + seg7_ch_id ;  
     cur_seg7_ctrl_ptr->access_flag = STATE_NO;
     Seg7_Disable(seg7_ch_id);
	 return SUCCESS;
}

/*------------------------------------------------------------*
FUNCTION NAME  : Seg7_Init

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 06.07 

Bugs           :  
-*------------------------------------------------------------*/
uint8_t Seg7_Init(const uint8_t seg7_ch_id)
{
	 seg7_ctrl_t *cur_seg7_ctrl_ptr = NULL_PTR;
	 io_config_t seg7_config;
	 
	 uint8_t ret_status = SUCCESS ;	
	 
	 if(seg7_ch_id >= NUM_OUTPUT_DEV_ID_SEG7_CHS)
	 {
		  sys_error_or_warning_flag = ERR_DEV_CH_ID_EXCEEDS;
		  Error_or_Warning_Proc("06.07.01", ERROR_OCCURED, sys_error_or_warning_flag);
		  return sys_error_or_warning_flag;
	 }
	 cur_seg7_ctrl_ptr = seg7_ctrl + seg7_ch_id ;
	 
	 seg7_config.io_ch = cur_seg7_ctrl_ptr->io_ch_a_led;
	 seg7_config.signal = PIN_SIG_DIGITAL;
	 seg7_config.func = IO_FUNC_GPIO;
	 seg7_config.dir = IO_DIR_OUTPUT;
	 if(cur_seg7_ctrl_ptr->seg7_type == SEG7_COMMON_CATHODE)
	 {
		 seg7_config.state = STATE_LOW;
	 }
	 else
	 {
		  seg7_config.state = STATE_HIGH;
	 }
	 seg7_config.func_type = IO_FUNC_TYPE_GPIO_NON_SW;
	 seg7_config.port_pin_len = 8;
		 
	 if((ret_status = IO_Channels_Func_Set(&seg7_config)) != SUCCESS)
	 {
		sys_error_or_warning_flag = ERR_GPIO_FUNC_SET;
		Error_or_Warning_Proc("06.07.02", ERROR_OCCURED, sys_error_or_warning_flag);
		return sys_error_or_warning_flag;
	 }
	 seg7_config.io_ch = cur_seg7_ctrl_ptr->io_ch_unit_digit;
	 seg7_config.port_pin_len = cur_seg7_ctrl_ptr->num_digits; 
	 seg7_config.state = STATE_LOW;
	 if((ret_status = IO_Channels_Func_Set(&seg7_config)) != SUCCESS)
	 {
		sys_error_or_warning_flag = ERR_GPIO_FUNC_SET;
		Error_or_Warning_Proc("06.07.03", ERROR_OCCURED, sys_error_or_warning_flag);
		return sys_error_or_warning_flag;
	 }
	 return SUCCESS; 	
}

/*------------------------------------------------------------*
FUNCTION NAME  : Seg7_DeInit

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 06.08 

Bugs           :  
-*------------------------------------------------------------*/
uint8_t Seg7_DeInit(const uint8_t seg7_ch_id)
{
	 io_config_t seg7_unconfig;
	 seg7_ctrl_t *cur_seg7_ctrl_ptr = NULL_PTR;
	 uint8_t ret_status = SUCCESS;
	 
	 if(seg7_ch_id >= NUM_OUTPUT_DEV_ID_SEG7_CHS)
	 {
		  sys_error_or_warning_flag = ERR_DEV_CH_ID_EXCEEDS;
		  Error_or_Warning_Proc("06.08.01", ERROR_OCCURED, sys_error_or_warning_flag);
		  return sys_error_or_warning_flag;
	 }
	 Seg7_No_Access(seg7_ch_id);
	 cur_seg7_ctrl_ptr = seg7_ctrl + seg7_ch_id ; 
	 seg7_unconfig.io_ch  = cur_seg7_ctrl_ptr->io_ch_a_led;	 
	 seg7_unconfig.port_pin_len = 8;
	 seg7_unconfig.func = IO_FUNC_GPIO;
	 seg7_unconfig.func_type = IO_FUNC_TYPE_GPIO_NON_SW;
	 if((ret_status = IO_Ch_Func_Reset(&seg7_unconfig)) != SUCCESS)
	 {
		sys_error_or_warning_flag = ERR_IO_CH_FUNC_RESET;
		 Error_or_Warning_Proc("06.08.02", ERROR_OCCURED, sys_error_or_warning_flag);
        return sys_error_or_warning_flag;		
	 }	 
	 seg7_unconfig.io_ch  = cur_seg7_ctrl_ptr->io_ch_unit_digit;
	 seg7_unconfig.port_pin_len = cur_seg7_ctrl_ptr->num_digits;
	 if((ret_status = IO_Ch_Func_Reset(&seg7_unconfig)) != SUCCESS)
	 {
		sys_error_or_warning_flag = ERR_IO_CH_FUNC_RESET;
		 Error_or_Warning_Proc("06.08.03", ERROR_OCCURED, sys_error_or_warning_flag);
        return sys_error_or_warning_flag;		
	 }
	 return SUCCESS;
}

#endif

/*------------------------------------------------------------------*-
  ------------------------ END OF FILE ------------------------------
-*------------------------------------------------------------------*/
