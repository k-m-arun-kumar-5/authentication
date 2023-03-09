/**************************************************************************
   FILE          :    sw_lib.h
 
   PURPOSE       :    Switch Library header 
 
   AUTHOR        :    K.M. Arun Kumar alias Arunkumar Murugeswaran
 
  KNOWN BUGS     :
	
  NOTE           :    
	
  CHANGE LOGS     :  
	   
 **************************************************************************/
#ifndef _SW_LIB_H
#define _SW_LIB_H

 /* ---------------------- macro defination ------------------------------------------------ */

 
/* ---------------------- data type defination -------------------------------------------- */
 typedef struct 
 {
	 uint8_t io_ch;
	 uint8_t access_flag        : 1;
     uint8_t enable_flag        : 1;      	 
	 uint8_t sw_pressed_state   : 1;
	 uint8_t sw_cur_state       : 2; 
	 uint8_t sw_read_data       : 1;
     uint8_t                    : 2;	 
 } sw_para_t;
 
 /* -------------------- public variable declaration --------------------------------------- */
  extern sw_para_t sw_para[]; 
    
/* -------------------- public function declaration --------------------------------------- */
uint8_t IO_Ch_To_SW_Ch( const uint8_t io_ch, uint8_t *const sw_ch_id_ptr);
uint8_t Reset_SW_Ch(const uint8_t sw_ch_id);
void Reset_SW_Chs(void);
uint8_t SW_Read_By_IO_Ch( const uint8_t io_ch, uint8_t *const sw_ch_id_ptr); 
uint8_t SW_Read(const uint8_t sw_ch_id);
uint8_t SW_Press_By_IO_Ch_Proc(const uint8_t sw_io_ch);
uint8_t SW_Press_Proc(const uint8_t sw_ch_id, void *const dummy_ptr);
uint8_t SW_Disable(const uint8_t sw_ch_id);
uint8_t SW_Enable(const uint8_t sw_ch_id);
uint8_t Disable_All_SWs(void);
uint8_t SW_Allow_Access(const uint8_t sw_ch_id);
uint8_t SW_No_Access(const uint8_t sw_ch_id);
uint8_t SW_Init(const uint8_t sw_ch_id);
uint8_t SW_DeInit(const uint8_t sw_ch_id);
uint8_t SW_Ch_ID_Check_And_Alloc(const uint8_t ch_id_alloc_type, uint8_t *const base_sw_ch_id_ptr, const uint8_t num_sw_chs);
uint8_t SW_Ch_UnConfig(const uint8_t base_sw_ch_id, const uint8_t num_sw_chs);
uint8_t SW_Oper(const uint8_t sw_io_ch, const uint8_t sw_dev_oper);
uint8_t SW_Para_Init(const uint8_t base_sw_ch_id, const uint8_t base_sw_io_ch, const uint8_t num_sw_chs, const uint8_t pressed_state);

#endif

/*------------------------------------------------------------------*-
  ------------------------ END OF FILE ------------------------------
-*------------------------------------------------------------------*/
