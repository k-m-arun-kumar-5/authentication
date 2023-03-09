/* ********************************************************************
FILE                   : sw_lib.c

PURPOSE                : 
                     									 	 
AUTHOR                : K.M. Arun Kumar alias Arunkumar Murugeswaran
	 
KNOWN BUGS            : 

NOTE                  : 
                       
CHANGE LOGS           : 

FILE ID               : 07 

*****************************************************************************/
#include "main.h"

#if defined(SW_MOD_ENABLE) || defined(KEYBOARD_MOD_ENABLE)

/* ------------------------------ macro defination ------------------------------ */

/* ----------------------------- global variable defination --------------------- */
uint8_t last_sw_ch_id = 0;
static uint16_t alloc_sw_ch_ids_bit_field = 0;

/* ----------------------------- global variable declaration -------------------- */


/* ----------------------------- global function declaration -------------------- */
static uint8_t SW_Ch_Validate(const uint8_t base_sw_ch_id, const uint8_t num_sw_chs);

/*------------------------------------------------------------*
FUNCTION NAME  : IO_Ch_To_SW_Ch

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 07.01  

BUGS           :              
-*------------------------------------------------------------*/
uint8_t IO_Ch_To_SW_Ch(const uint8_t io_ch, uint8_t *const sw_ch_id_ptr )
{
	    uint8_t ret_status = FAILURE, sw_ch_id;
	
	    if(sw_ch_id_ptr == NULL_PTR || ((ret_status = IO_Ch_Validate(io_ch, 1)) != SUCCESS))
      {
		    sys_error_or_warning_flag = ERR_IO_CH_TO_SW_CH;
			 Error_or_Warning_Proc("07.01.01", ERROR_OCCURED, sys_error_or_warning_flag);
		    return sys_error_or_warning_flag; 
	    }
	    for(sw_ch_id = 0; sw_ch_id <= last_sw_ch_id; ++sw_ch_id)
	    {
				  if(sw_para[sw_ch_id].io_ch == io_ch)
					{
						  *sw_ch_id_ptr = sw_ch_id;
						 	return SUCCESS;
					}
			}
		 	sys_error_or_warning_flag = ERR_SW_CH_NOT_MATCH_IO_CH ;
			Error_or_Warning_Proc("07.01.02", ERROR_OCCURED, sys_error_or_warning_flag);
		  return sys_error_or_warning_flag;
}

/*------------------------------------------------------------*
FUNCTION NAME  : SW_Ch_ID_Check_And_Alloc

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : for CH_ID_ALLOC_FIXED, alloc_base_sw_ch_id_ptr points to req_base_sw_ch_id data. 
                 for CH_ID_ALLOC_DYNAMIC, alloc_base_sw_ch_id_ptr points to start_free_base_sw_ch_id data. 

Func ID        : 07.02  

BUGS           :              
-*------------------------------------------------------------*/
uint8_t SW_Ch_ID_Check_And_Alloc(const uint8_t ch_id_alloc_type, uint8_t *const alloc_base_sw_ch_id_ptr, const uint8_t num_sw_chs)
{
	consucc_bit_t check_free_sw_ch ;
	uint8_t i, ret_status ;
  		
	if(alloc_base_sw_ch_id_ptr == NULL_PTR)
	{
		sys_error_or_warning_flag = ERR_NULL_PTR;
		Error_or_Warning_Proc("07.02.01", ERROR_OCCURED, sys_error_or_warning_flag);
		return sys_error_or_warning_flag;
	}
	switch(ch_id_alloc_type)
	{
		case CH_ID_ALLOC_DYNAMIC:
		  *alloc_base_sw_ch_id_ptr = CH_ID_INVALID;
	      check_free_sw_ch.bits_len = num_sw_chs;
	      check_free_sw_ch.read_or_test_consucc_val = alloc_sw_ch_ids_bit_field;
	      for(i = 0; i < sizeof(alloc_sw_ch_ids_bit_field) * 8; ++i)
	      {
	    	if(Test_Bit_Is_Clear_in_Data( &alloc_sw_ch_ids_bit_field, i) )
	    	{
			    check_free_sw_ch.start_bit_pos = i; 
			    ret_status = Test_Consucc_Bits(FLAG_CONSUCC_BITS_0, &check_free_sw_ch);
			    if(ret_status == TEST_OK_0_CONSUCC_BITS)
			    {
			    	*alloc_base_sw_ch_id_ptr = i;
			    	break;				
			    }
			    else
			    {
				   continue;
			    }
		    }
	     }
	     if(*alloc_base_sw_ch_id_ptr == CH_ID_INVALID)
	     {
	    	sys_error_or_warning_flag = ERR_SW_CONFIG_DYNAMIC_NOT_ALLOC;
			 Error_or_Warning_Proc("07.02.02", ERROR_OCCURED, sys_error_or_warning_flag);
		    return sys_error_or_warning_flag; 
	     }
		 if(*alloc_base_sw_ch_id_ptr + num_sw_chs  > NUM_INPUT_DEV_ID_SW_CHS)
	     {
		     sys_error_or_warning_flag = ERR_MAX_SW_CH_EXCEEDS;
		     Error_or_Warning_Proc("07.02.03", ERROR_OCCURED, sys_error_or_warning_flag);
		     return sys_error_or_warning_flag;
	     }
		break;
		case CH_ID_ALLOC_FIXED:
		  if(*alloc_base_sw_ch_id_ptr + num_sw_chs  >= NUM_INPUT_DEV_ID_SW_CHS)
	      {
		     sys_error_or_warning_flag = ERR_MAX_SW_CH_EXCEEDS;
		     Error_or_Warning_Proc("07.02.04", ERROR_OCCURED, sys_error_or_warning_flag);
		     return sys_error_or_warning_flag;
	      }
		   check_free_sw_ch.start_bit_pos = *alloc_base_sw_ch_id_ptr;
           check_free_sw_ch.bits_len = num_sw_chs;
  		   check_free_sw_ch.read_or_test_consucc_val = alloc_sw_ch_ids_bit_field;
		   ret_status = Test_Consucc_Bits(FLAG_CONSUCC_BITS_0, &check_free_sw_ch);
		   if(ret_status != TEST_OK_0_CONSUCC_BITS)
		   {
		       sys_error_or_warning_flag = ERR_SW_CONFIG_FIXED_NOT_ALLOC;
		       Error_or_Warning_Proc("07.02.05", ERROR_OCCURED, sys_error_or_warning_flag);
		       return sys_error_or_warning_flag; 			    				
		   }	
		break;
		default:
		   sys_error_or_warning_flag = ERR_FORMAT_INVALID;
		   Error_or_Warning_Proc("07.02.06", ERROR_OCCURED, sys_error_or_warning_flag);
		   return sys_error_or_warning_flag;
	}
	check_free_sw_ch.start_bit_pos = *alloc_base_sw_ch_id_ptr;
	check_free_sw_ch.bits_len = num_sw_chs;
	check_free_sw_ch.write_or_config_consucc_val = alloc_sw_ch_ids_bit_field;
    if((ret_status = Config_Consucc_Bits(FLAG_CONSUCC_BITS_1, &check_free_sw_ch )) != SUCCESS)
	{
		sys_error_or_warning_flag = ERR_SW_CONFIG;
		Error_or_Warning_Proc("07.02.07", ERROR_OCCURED, sys_error_or_warning_flag);
		return sys_error_or_warning_flag; 
	}
	alloc_sw_ch_ids_bit_field =  check_free_sw_ch.write_or_config_consucc_val;
	if( *alloc_base_sw_ch_id_ptr == last_sw_ch_id)
	{
		last_sw_ch_id += num_sw_chs;
	}
	return SUCCESS;
} 

/*------------------------------------------------------------*
FUNCTION NAME  : Reset_SW_Ch

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 07.03  

BUGS           :              
-*------------------------------------------------------------*/
uint8_t Reset_SW_Ch(const uint8_t sw_ch_id)
{
	 if(sw_ch_id >= NUM_INPUT_DEV_ID_SW_CHS) 
	 {
		   sys_error_or_warning_flag = ERR_MAX_SW_CH_EXCEEDS;
		   Error_or_Warning_Proc("07.03.01", ERROR_OCCURED, sys_error_or_warning_flag);
		   return sys_error_or_warning_flag;
	 }		 
    SW_No_Access(sw_ch_id);
    sw_para[sw_ch_id].sw_cur_state = STATE_KEY_RELEASED;
    Clear_Bit_in_Data(&alloc_sw_ch_ids_bit_field, sw_ch_id); 
    if((int8_t)sw_ch_id == (int8_t)last_sw_ch_id - 1)
    {
	    --last_sw_ch_id;
    }
   return SUCCESS;
}

/*------------------------------------------------------------*
FUNCTION NAME  : Reset_SW_Chs

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 07.04  

BUGS           :              
-*------------------------------------------------------------*/
void Reset_SW_Chs(void)
{
	uint8_t i;
	
	for (i = 0 ; i < NUM_INPUT_DEV_ID_SW_CHS; ++i)
	{
	  	Reset_SW_Ch(i);
	}
	last_sw_ch_id = 0;
	alloc_sw_ch_ids_bit_field = 0;
}

/*------------------------------------------------------------*
FUNCTION NAME  : SW_Read_By_IO_Ch

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 07.05  

BUGS           :              
-*------------------------------------------------------------*/
uint8_t SW_Read_By_IO_Ch(const uint8_t io_ch, uint8_t *const sw_ch_id_ptr )
{
	 uint8_t ret_status = SUCCESS;	
	
	 if((ret_status = IO_Ch_To_SW_Ch(io_ch, sw_ch_id_ptr )) != SUCCESS)
	 {
		 sys_error_or_warning_flag = ERR_IO_CH_TO_SW_CH;
		 Error_or_Warning_Proc("07.05.01", ERROR_OCCURED, sys_error_or_warning_flag);
		 return sys_error_or_warning_flag;
	 }
	 if((ret_status = SW_Ch_Validate(*sw_ch_id_ptr, 1)) != SUCCESS)
	 {
	       sys_error_or_warning_flag = ERR_SW_CH_INVALID;
	       Error_or_Warning_Proc("07.05.02", ERROR_OCCURED, sys_error_or_warning_flag);
	       return sys_error_or_warning_flag;
	 }
	 if((ret_status = SW_Read(*sw_ch_id_ptr)) != SUCCESS)
	 {
		 sys_error_or_warning_flag = ERR_SW_NO_READ;
		 Error_or_Warning_Proc("07.05.03", ERROR_OCCURED, sys_error_or_warning_flag);
		 return sys_error_or_warning_flag;
	 }
	 return SUCCESS; 
}

/*------------------------------------------------------------*
FUNCTION NAME  : SW_Read_By_IO_Ch_Proc

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 07.06  

BUGS           :              
-*------------------------------------------------------------*/
uint8_t SW_Read_By_IO_Ch_Proc(const uint8_t io_ch)
{
	uint8_t ret_status = SW_OR_KEY_NOT_PRESSED, sw_ch_id;
 
	if((ret_status = IO_Ch_To_SW_Ch(io_ch, &sw_ch_id)) != SUCCESS)
	{
		sys_error_or_warning_flag = ERR_IO_CH_TO_SW_CH;
		Error_or_Warning_Proc("07.06.01", ERROR_OCCURED, sys_error_or_warning_flag);
		return sys_error_or_warning_flag;		   
	}
	if((ret_status = SW_Ch_Validate(sw_ch_id, 1)) != SUCCESS)
	{
	       sys_error_or_warning_flag = ERR_SW_CH_INVALID;
	       Error_or_Warning_Proc("07.06.02", ERROR_OCCURED, sys_error_or_warning_flag);
	       return sys_error_or_warning_flag;
	}
	ret_status = SW_Press_Proc(sw_ch_id, NULL_PTR);
	return ret_status;
}

#ifdef SW_PRESS_HOLD_CPU
/*------------------------------------------------------------*
FUNCTION NAME  : SW_Press_Proc

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : When SW is pressed, then hold CPU by using While(read_sw_pressed_state);  

Func ID        : 07.07  

BUGS           :              
-*------------------------------------------------------------*/
uint8_t SW_Press_Proc(const uint8_t sw_ch_id, void *const dummy_ptr)
{
	sw_para_t *sw_para_ptr;
	uint8_t ret_status = SW_OR_KEY_NOT_PRESSED;
	
   	if((ret_status = SW_Ch_Validate(sw_ch_id, 1)) != SUCCESS)
	{
	       sys_error_or_warning_flag = ERR_SW_CH_INVALID;
	       Error_or_Warning_Proc("07.07.01", ERROR_OCCURED, sys_error_or_warning_flag);
	       return sys_error_or_warning_flag;
	}
	sw_para_ptr = sw_para + sw_ch_id;
	if( sw_para_ptr->access_flag == STATE_NO) 
	{  
          sys_error_or_warning_flag = WARN_CUR_DATA_ID_DEV_NO_ACCESS;
		 // Error_or_Warning_Proc("07.07.02", ERROR_OCCURED, sys_error_or_warning_flag);
          return  sys_error_or_warning_flag;
	}
		 
	if(sw_para_ptr->enable_flag == STATE_NO) 
	{  
          sys_error_or_warning_flag = WARN_CUR_DATA_ID_DEV_DISABLED;	
		 //Error_or_Warning_Proc("07.07.03", ERROR_OCCURED, sys_error_or_warning_flag);
         return  sys_error_or_warning_flag;
	}		 
			  if((ret_status = SW_Read(sw_ch_id )) != SUCCESS)
			   {
				     ret_status = ERR_SW_NO_READ; 
				      Error_or_Warning_Proc("07.07.04", ERROR_OCCURED, sys_error_or_warning_flag);
					 return ret_status;
			   }
		     if(sw_para_ptr->sw_cur_state == STATE_KEY_RELEASED  && (sw_para_ptr->sw_read_data == sw_para_ptr->sw_pressed_state))
			  {
				      SW_Time_Delay(MAX_ICOUNT_SW_DEBOUNCE_SW_DELAY, MAX_JCOUNT_SW_DEBOUNCE_SW_DELAY); 
			          if(((ret_status = SW_Read(sw_ch_id )) != SUCCESS))
					  {
						    ret_status = ERR_SW_NO_READ;
							 Error_or_Warning_Proc("07.07.05", ERROR_OCCURED, sys_error_or_warning_flag);
							return ret_status;		  
					  }
					  if( sw_para_ptr->sw_read_data == sw_para_ptr->sw_pressed_state)
		              { 
			               sw_para_ptr->sw_cur_state = STATE_KEY_PRESSED;
						   do
					       {
							  if((ret_status = SW_Read(sw_ch_id )) != SUCCESS)
							  {
								    ret_status = ERR_SW_NO_READ; 
									 Error_or_Warning_Proc("07.07.06", ERROR_OCCURED, sys_error_or_warning_flag);
									return ret_status;    
							  }												 
												 
						  } while( sw_para_ptr->sw_read_data == sw_para_ptr->sw_pressed_state); 
					  }  
					  SW_Time_Delay(MAX_ICOUNT_SW_DEBOUNCE_SW_DELAY, MAX_JCOUNT_SW_DEBOUNCE_SW_DELAY);
					  if((ret_status = SW_Read(sw_ch_id )) != SUCCESS)
					  {
					    	ret_status = ERR_SW_NO_READ; 	
							 Error_or_Warning_Proc("07.07.07", ERROR_OCCURED, sys_error_or_warning_flag);
							return ret_status; 
					  }
					  if(sw_para_ptr->sw_read_data != sw_para_ptr->sw_pressed_state)
					  {
						  sw_para_ptr->sw_cur_state = STATE_KEY_RELEASED;		
						  return SUCCESS;
			          }				 
			     } 	
		return SW_OR_KEY_NOT_PRESSED; 
}	
#else
/*------------------------------------------------------------*
FUNCTION NAME  : SW_Press_Proc

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : When SW is pressed, then dont hold CPU by using sw read level transition; 

Func ID        : 07.08  

BUGS           :              
-*------------------------------------------------------------*/
uint8_t SW_Press_Proc(const uint8_t sw_ch_id, void *const dummy_ptr )
{
	sw_para_t *sw_para_ptr;
	uint8_t ret_status = SW_OR_KEY_NOT_PRESSED;
	
    if((ret_status = SW_Ch_Validate(sw_ch_id, 1)) != SUCCESS)
	{
	       sys_error_or_warning_flag = ERR_SW_CH_INVALID;
	       Error_or_Warning_Proc("07.08.01", ERROR_OCCURED, sys_error_or_warning_flag);
	       return sys_error_or_warning_flag;
	}	
	sw_para_ptr = sw_para + sw_ch_id;
	if( sw_para_ptr->access_flag == STATE_NO) 
	{  
          sys_error_or_warning_flag = WARN_CUR_DATA_ID_DEV_NO_ACCESS;	
		   Error_or_Warning_Proc("07.08.02", ERROR_OCCURED, sys_error_or_warning_flag);
          return  sys_error_or_warning_flag;
	}
		 
	if(sw_para_ptr->enable_flag == STATE_NO) 
	{  
         sys_error_or_warning_flag = WARN_CUR_DATA_ID_DEV_DISABLED;
		  Error_or_Warning_Proc("07.08.03", ERROR_OCCURED, sys_error_or_warning_flag);
         return  sys_error_or_warning_flag;
	}
		   
			  if((ret_status = SW_Read(sw_ch_id )) != SUCCESS)
			   {
				     ret_status = ERR_SW_NO_READ;
 				      Error_or_Warning_Proc("07.08.04", ERROR_OCCURED, sys_error_or_warning_flag);
					 return ret_status;
			   }
		     if(sw_para_ptr->sw_cur_state == STATE_KEY_RELEASED  && sw_para_ptr->sw_read_data == sw_para_ptr->sw_pressed_state)
			  {
				      SW_Time_Delay(MAX_ICOUNT_SW_DEBOUNCE_SW_DELAY, MAX_JCOUNT_SW_DEBOUNCE_SW_DELAY); 
			          if(((ret_status = SW_Read(sw_ch_id )) != SUCCESS))
					  {
						    ret_status = ERR_SW_NO_READ; 
							 Error_or_Warning_Proc("07.08.05", ERROR_OCCURED, sys_error_or_warning_flag);
							return ret_status;		  
					  }
					  if( sw_para_ptr->sw_read_data == sw_para_ptr->sw_pressed_state)
		              { 
			              sw_para_ptr->sw_cur_state = STATE_KEY_PRESSED;
					  }
			  }
              else
			  {
                  if(sw_para_ptr->sw_cur_state == STATE_KEY_PRESSED && sw_para_ptr->sw_read_data != sw_para_ptr->sw_pressed_state)
				  {
					  SW_Time_Delay(MAX_ICOUNT_SW_DEBOUNCE_SW_DELAY, MAX_JCOUNT_SW_DEBOUNCE_SW_DELAY); 
			          if(((ret_status = SW_Read(sw_ch_id )) != SUCCESS))
					  {
						    ret_status = ERR_SW_NO_READ;
							 Error_or_Warning_Proc("07.08.06", ERROR_OCCURED, sys_error_or_warning_flag);
							return ret_status;		  
					  }
					  if( sw_para_ptr->sw_read_data != sw_para_ptr->sw_pressed_state)
		              { 
			              sw_para_ptr->sw_cur_state = STATE_KEY_RELEASED;
						  return SUCCESS;
					  }
				  }
			  }				  
	return SW_OR_KEY_NOT_PRESSED; 					   
 } 		  
#endif		

/*------------------------------------------------------------*
FUNCTION NAME  : SW_Read

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 07.09  

BUGS           :              
-*------------------------------------------------------------*/
uint8_t SW_Read(const uint8_t sw_ch_id)
{
	uint8_t ret_status = SUCCESS, read_data;
	sw_para_t *cur_sw_para_ptr = NULL_PTR;
	
	if((ret_status = SW_Ch_Validate(sw_ch_id, 1)) != SUCCESS)
	{
	    sys_error_or_warning_flag = ERR_SW_CH_INVALID;
	    Error_or_Warning_Proc("07.09.01", ERROR_OCCURED, sys_error_or_warning_flag);
	   return sys_error_or_warning_flag;
	} 
	 
	 cur_sw_para_ptr = sw_para + sw_ch_id;			
	if((ret_status = IO_Channel_Read(cur_sw_para_ptr->io_ch, &read_data )) != SUCCESS)
	{
		 sys_error_or_warning_flag = ERR_IO_CH_READ;
		 Error_or_Warning_Proc("07.09.02", ERROR_OCCURED, sys_error_or_warning_flag);
		 return sys_error_or_warning_flag;
	}
	cur_sw_para_ptr->sw_read_data = (read_data & 0x01);
	return SUCCESS;	
}

/*------------------------------------------------------------*
FUNCTION NAME  : SW_Ch_UnConfig_By_IO_Ch

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 07.10  

BUGS           :              
-*------------------------------------------------------------*/
uint8_t SW_Ch_UnConfig_By_IO_Ch(const uint8_t base_sw_io_ch, const uint8_t num_sw_chs)
{
	int16_t offset_sw_io_ch = 0;
	uint8_t  sw_ch_id, ret_status;	
		
	for(offset_sw_io_ch = num_sw_chs - 1; offset_sw_io_ch >=0 ; --offset_sw_io_ch)
	{		
	    if((ret_status = IO_Ch_To_SW_Ch(base_sw_io_ch + offset_sw_io_ch, &sw_ch_id)) != SUCCESS)
		{
			sys_error_or_warning_flag = ERR_IO_CH_TO_SW_CH;
			 Error_or_Warning_Proc("07.10.01", ERROR_OCCURED, sys_error_or_warning_flag);
		    return sys_error_or_warning_flag; 
		}
		Reset_SW_Ch(sw_ch_id);		
	}  	
	return SUCCESS;
} 

/*------------------------------------------------------------*
FUNCTION NAME  : SW_Ch_UnConfig

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 07.11  

BUGS           :              
-*------------------------------------------------------------*/
uint8_t SW_Ch_UnConfig(const uint8_t base_sw_ch_id, const uint8_t num_sw_chs)
{
	int16_t offset_sw_ch_id = 0;		
	uint8_t ret_status;
	
	for(offset_sw_ch_id = num_sw_chs - 1; offset_sw_ch_id >=0 ; --offset_sw_ch_id)
	{		
	   	Reset_SW_Ch(base_sw_ch_id + offset_sw_ch_id);		
	}  	
	return SUCCESS;
} 

/*------------------------------------------------------------*
FUNCTION NAME  : SW_Ch_Validate

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 07.12

Bugs           :  
-*------------------------------------------------------------*/
static uint8_t SW_Ch_Validate(const uint8_t base_sw_ch_id, const uint8_t num_sw_chs)
{
	consucc_bit_t check_alloc_sw_ch ;
	uint8_t ret_status;
	
	if(base_sw_ch_id + num_sw_chs  > NUM_INPUT_DEV_ID_SW_CHS )
	{
		sys_error_or_warning_flag = ERR_MAX_SW_CH_EXCEEDS;
		Error_or_Warning_Proc("07.12.01", ERROR_OCCURED, sys_error_or_warning_flag);
		return sys_error_or_warning_flag;
	}
	check_alloc_sw_ch.start_bit_pos = base_sw_ch_id;
    check_alloc_sw_ch.bits_len = num_sw_chs;
  	check_alloc_sw_ch.read_or_test_consucc_val = alloc_sw_ch_ids_bit_field;
	ret_status = Test_Consucc_Bits(FLAG_CONSUCC_BITS_1, &check_alloc_sw_ch);
	if(ret_status != TEST_OK_1_CONSUCC_BITS)
	{
	     sys_error_or_warning_flag = ERR_SW_NOT_ALLOC;
	     Error_or_Warning_Proc("07.12.02", ERROR_OCCURED, sys_error_or_warning_flag);
	     return sys_error_or_warning_flag; 			    				
	}	
	return SUCCESS;
}

/*------------------------------------------------------------*
FUNCTION NAME  : SW_Disable

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 07.13  

Bugs           :  
-*------------------------------------------------------------*/
uint8_t SW_Disable(const uint8_t sw_ch_id)
{
	 sw_para_t *cur_sw_para_ptr = NULL_PTR;
	
	  if(sw_ch_id >= last_sw_ch_id)
	{
		sys_error_or_warning_flag = ERR_MAX_SW_CH_EXCEEDS;
		return sys_error_or_warning_flag;
	}
	 cur_sw_para_ptr = sw_para + sw_ch_id ;  
     cur_sw_para_ptr->enable_flag = STATE_NO;
	 
   return SUCCESS;
}
/*------------------------------------------------------------*
FUNCTION NAME  : SW_Enable

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 07.14  

Bugs           :  
-*------------------------------------------------------------*/
uint8_t SW_Enable(const uint8_t sw_ch_id)
{
	  sw_para_t *cur_sw_para_ptr = NULL_PTR;
	
	  if(sw_ch_id >= last_sw_ch_id)
	{
		sys_error_or_warning_flag = ERR_MAX_SW_CH_EXCEEDS;
		return sys_error_or_warning_flag;
	}
	 cur_sw_para_ptr = sw_para + sw_ch_id ;  
     cur_sw_para_ptr->enable_flag = STATE_YES;
   return SUCCESS;
}

/*------------------------------------------------------------*
FUNCTION NAME  : Disable_All_SWs

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 07.15  

Bugs           :  
-*------------------------------------------------------------*/
uint8_t Disable_All_SWs(void)
{
	 uint8_t sw_ch_id =0;
	
	 for(sw_ch_id = 0; sw_ch_id < NUM_INPUT_DEV_ID_SW_CHS; ++sw_ch_id)
	 {
		   SW_Disable(sw_ch_id);
	 }
	 return SUCCESS;
}

/*------------------------------------------------------------*
FUNCTION NAME  : SW_Allow_Access

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 07.16 

Bugs           :  
-*------------------------------------------------------------*/
uint8_t SW_Allow_Access(const uint8_t sw_ch_id)
{
	  sw_para_t *cur_sw_para_ptr = NULL_PTR;
	
	 if(sw_ch_id >= last_sw_ch_id)
	{
		sys_error_or_warning_flag = ERR_MAX_SW_CH_EXCEEDS;
		return sys_error_or_warning_flag;
	}
	 cur_sw_para_ptr = sw_para + sw_ch_id ;  
     cur_sw_para_ptr->access_flag = STATE_YES;
	 return SUCCESS;
}

/*------------------------------------------------------------*
FUNCTION NAME  : SW_No_Access

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 07.17 

Bugs           :  
-*------------------------------------------------------------*/
uint8_t SW_No_Access(const uint8_t sw_ch_id)
{
	 sw_para_t *cur_sw_para_ptr = NULL_PTR;
	
	 if(sw_ch_id >= last_sw_ch_id)
	{
		sys_error_or_warning_flag = ERR_MAX_SW_CH_EXCEEDS;
		return sys_error_or_warning_flag;
	}
	cur_sw_para_ptr = sw_para + sw_ch_id ;  
    cur_sw_para_ptr->access_flag = STATE_NO;
    SW_Disable(sw_ch_id);
	return SUCCESS;
}

/*------------------------------------------------------------*
FUNCTION NAME  : SW_Init

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 07.18 

Bugs           :  
-*------------------------------------------------------------*/
uint8_t SW_Init(const uint8_t sw_ch_id)
{
	 sw_para_t *cur_sw_para_ptr = NULL_PTR;
	 io_config_t sw_config;	 
	 uint8_t ret_status = SUCCESS, alloc_base_sw_ch_id = sw_ch_id ;	
	 
	 if(sw_ch_id >= NUM_INPUT_DEV_ID_SW_CHS )
	 {
		  sys_error_or_warning_flag = ERR_DEV_CH_ID_EXCEEDS;
		  Error_or_Warning_Proc("07.18.01", ERROR_OCCURED, sys_error_or_warning_flag);
		  return sys_error_or_warning_flag;
	 }
	 cur_sw_para_ptr = sw_para + sw_ch_id;   
     sw_config.io_ch = cur_sw_para_ptr->io_ch;
	 sw_config.port_pin_len = 1;
	 sw_config.signal = PIN_SIG_DIGITAL;
	 sw_config.dir = IO_DIR_INPUT;
	 sw_config.func = IO_FUNC_GPIO;
	 sw_config.state = cur_sw_para_ptr->sw_pressed_state;
	 sw_config.func_type = IO_FUNC_TYPE_GPIO_SW;
	 sw_config.ch_id_alloc_type = CH_ID_ALLOC_FIXED;
	 if((ret_status = SW_Ch_ID_Check_And_Alloc(sw_config.ch_id_alloc_type, &alloc_base_sw_ch_id, sw_config.port_pin_len)) != SUCCESS)
	 {
		 sys_error_or_warning_flag = ERR_SW_CONFIG;
		 Error_or_Warning_Proc("07.18.02", ERROR_OCCURED, sys_error_or_warning_flag);
		return sys_error_or_warning_flag;
	 }
	 alloc_base_sw_ch_id = sw_ch_id;
	 if((ret_status = SW_Para_Init(alloc_base_sw_ch_id, cur_sw_para_ptr->io_ch, sw_config.port_pin_len, cur_sw_para_ptr->sw_pressed_state )) != SUCCESS)
	 {
		 sys_error_or_warning_flag = ERR_SW_CONFIG;
		 Error_or_Warning_Proc("07.18.03", ERROR_OCCURED, sys_error_or_warning_flag);
		 return sys_error_or_warning_flag;  
	 }
	 if((ret_status = IO_Channels_Func_Set(&sw_config)) != SUCCESS)
	 {
		sys_error_or_warning_flag = ERR_GPIO_FUNC_SET;
		Error_or_Warning_Proc("07.18.04", ERROR_OCCURED, sys_error_or_warning_flag);
		return sys_error_or_warning_flag;
	 }
	 return SUCCESS; 	
}

/*------------------------------------------------------------*
FUNCTION NAME  : SW_DeInit

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 07.19 

Bugs           :  
-*------------------------------------------------------------*/
uint8_t SW_DeInit(const uint8_t sw_ch_id)
{
	 sw_para_t *cur_sw_para_ptr = NULL_PTR;
	 io_config_t sw_unconfig;
	 uint8_t ret_status = SUCCESS ;	
	 
	 if((ret_status = SW_Ch_Validate(sw_ch_id, 1)) != SUCCESS)
	 {
	       sys_error_or_warning_flag = ERR_SW_CH_INVALID;
	       Error_or_Warning_Proc("07.19.01", ERROR_OCCURED, sys_error_or_warning_flag);
	       return sys_error_or_warning_flag;
	 }
	 cur_sw_para_ptr = sw_para + sw_ch_id;	 
	 SW_No_Access(sw_ch_id);
	 sw_unconfig.io_ch  = cur_sw_para_ptr->io_ch;
	 sw_unconfig.port_pin_len = 1;	 
	 sw_unconfig.func = IO_FUNC_GPIO;
	 sw_unconfig.dir = IO_DIR_INPUT;
	 sw_unconfig.func_type = IO_FUNC_TYPE_GPIO_SW;
	 sw_unconfig.ch_id_alloc_type = CH_ID_ALLOC_FIXED;
	 if((ret_status = IO_Ch_Func_Reset(&sw_unconfig)) != SUCCESS)
	 {
		sys_error_or_warning_flag = ERR_IO_CH_FUNC_RESET;
		 Error_or_Warning_Proc("07.19.02", ERROR_OCCURED, sys_error_or_warning_flag);
        return sys_error_or_warning_flag;		
	 }	 	 
	 return SUCCESS;
}

/*------------------------------------------------------------*
FUNCTION NAME  : SW_Oper

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 07.20 

Bugs           :  
-*------------------------------------------------------------*/
uint8_t SW_Oper(const uint8_t io_ch, const uint8_t sw_dev_oper)
{
	typedef uint8_t (*sw_oper_t)(const uint8_t sw_ch_id);
	sw_oper_t  SW_Oper_Func_Ptr;
	uint8_t ret_status, sw_ch_id;
 
	if((ret_status = IO_Ch_To_SW_Ch(io_ch, &sw_ch_id)) != SUCCESS)
	{
		sys_error_or_warning_flag = ERR_IO_CH_TO_SW_CH;
		Error_or_Warning_Proc("07.20.01", ERROR_OCCURED, sys_error_or_warning_flag);
		return sys_error_or_warning_flag;		   
	}
	if(sw_dev_oper != DEV_INIT_OPER )
	{
	   if((ret_status = SW_Ch_Validate(sw_ch_id, 1)) != SUCCESS)
	   {
	       sys_error_or_warning_flag = ERR_SW_CH_INVALID;
	       Error_or_Warning_Proc("07.20.02", ERROR_OCCURED, sys_error_or_warning_flag);
	       return sys_error_or_warning_flag;
	   }
	}
    switch(sw_dev_oper)
	{
		case DEV_INIT_OPER:
		  SW_Oper_Func_Ptr = SW_Init;
		break;
		case DEV_DEINIT_OPER:
		   SW_Oper_Func_Ptr = SW_DeInit;
		break;
		case DEV_DISABLE_OPER: 	           
		   SW_Oper_Func_Ptr = SW_Disable;
		   #ifdef SHOULD_REMOVE
				disp_trace_num_fmt.sign_flag = STATE_NO;
		        disp_trace_num_fmt.least_digits_flag = STATE_YES;
		        disp_trace_num_fmt.left_format_flag = STATE_YES;
		        disp_trace_num_fmt.num_digits = 2;
				UART_Transmit_Str(TRACE_UART_CH_ID, "\r Disable : SW ID - ");
				UART_Transmit_Num(TRACE_UART_CH_ID, DATA_TYPE_IN_DECIMAL, disp_trace_num_fmt, sw_ch_id);			         
				 #endif
		break;   
        case DEV_ENABLE_OPER:         
		   SW_Oper_Func_Ptr = SW_Enable;
		    #ifdef SHOULD_REMOVE
				disp_trace_num_fmt.sign_flag = STATE_NO;
		        disp_trace_num_fmt.least_digits_flag = STATE_YES;
		        disp_trace_num_fmt.left_format_flag = STATE_YES;
		        disp_trace_num_fmt.num_digits = 2;
				UART_Transmit_Str(TRACE_UART_CH_ID, "\r Enable : SW ID - ");
				UART_Transmit_Num(TRACE_UART_CH_ID, DATA_TYPE_IN_DECIMAL, disp_trace_num_fmt, sw_ch_id);			         
				 #endif
        break;  
        case DEV_NO_ACCESS_OPER:
           SW_Oper_Func_Ptr = SW_No_Access;
        break;
		case DEV_ALLOW_ACCESS_OPER:
     	    SW_Oper_Func_Ptr = SW_Allow_Access;
		break;
		case DEV_READ_OPER:		    
		  ret_status = SW_Press_Proc(sw_ch_id, NULL_PTR);
		  switch(ret_status)
	      {
		       case SUCCESS:
		       case SW_OR_KEY_NOT_PRESSED:
			   case WARN_CUR_DATA_ID_DEV_NO_ACCESS:
		       case WARN_CUR_DATA_ID_DEV_DISABLED:
		          return ret_status;
              //break; 
               default:
                  sys_error_or_warning_flag = ERR_SW_PRESS_PROC;
	              Error_or_Warning_Proc("07.20.03", ERROR_OCCURED, sys_error_or_warning_flag);
	              return sys_error_or_warning_flag;			   
	       }  
		//break;
		default:
		  sys_error_or_warning_flag = ERR_FORMAT_INVALID;
		  Error_or_Warning_Proc("07.20.04", ERROR_OCCURED, sys_error_or_warning_flag);
		  return sys_error_or_warning_flag;	
	}		
	if((ret_status = (*SW_Oper_Func_Ptr)(sw_ch_id)) != SUCCESS)
	{
		  sys_error_or_warning_flag = ERR_DEV_OPER_FUNC_PROC;
		  Error_or_Warning_Proc("07.20.05", ERROR_OCCURED, sys_error_or_warning_flag);
		  return sys_error_or_warning_flag;	
	}
	return SUCCESS;	
}

/*------------------------------------------------------------*
FUNCTION NAME  : SW_Para_Init

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        : 07.21 

Bugs           :  
-*------------------------------------------------------------*/
uint8_t SW_Para_Init(const uint8_t base_sw_ch_id, const uint8_t base_sw_io_ch, const uint8_t num_sw_chs, const uint8_t pressed_state)
{
	uint8_t offset_sw_ch_id, sw_ch_id, ret_status;
	
	if(pressed_state >= 2)
	{
		sys_error_or_warning_flag = ERR_INVALID_DATA;
		Error_or_Warning_Proc("07.21.01", ERROR_OCCURED, sys_error_or_warning_flag);
		return sys_error_or_warning_flag;
	}
	if((ret_status = SW_Ch_Validate(base_sw_ch_id, num_sw_chs)) != SUCCESS)
	 {
	       sys_error_or_warning_flag = ERR_SW_CH_INVALID;
	       Error_or_Warning_Proc("07.21.02", ERROR_OCCURED, sys_error_or_warning_flag);
	       return sys_error_or_warning_flag;
	 }	 
	for(offset_sw_ch_id = 0, sw_ch_id = base_sw_ch_id; offset_sw_ch_id < num_sw_chs; ++offset_sw_ch_id, ++sw_ch_id)
	{		
	    sw_para[sw_ch_id].io_ch = base_sw_io_ch + offset_sw_ch_id;
  	    sw_para[sw_ch_id].access_flag = STATE_NO;
	    sw_para[sw_ch_id].enable_flag = STATE_NO;
  	    sw_para[sw_ch_id].sw_cur_state = STATE_KEY_RELEASED; 
 	    sw_para[sw_ch_id].sw_pressed_state = pressed_state;
	}
	return SUCCESS;
}

#endif

/*------------------------------------------------------------------*-
  ------------------------ END OF FILE ------------------------------
-*------------------------------------------------------------------*/
