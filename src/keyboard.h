/**************************************************************************
   FILE          :    keyboard.h
 
   PURPOSE       :    keyboard Header
 
   AUTHOR        :    K.M. Arun Kumar alias Arunkumar Murugeswaran
 
  KNOWN BUGS     :
	
  NOTE           :   
  
  CHANGE LOGS    :
	   
 **************************************************************************/
 
 #ifndef _KEYBOARD_H
 #define _KEYBOARD_H
 
 /* ---------------------- macro defination ------------------------------------------------ */
 
#define ENTER_SW_CODE                           ('E')
#define BACKSPACE_SW_CODE                       ('B')

#define KEYBOARD_PART_DATA_POS                   (4)

/* ---------------------- data type defination --------------------------------------------- */
typedef struct 
{
	uint8_t io_ch_rowa;
	uint8_t io_ch_col1;
	uint8_t io_ch_enter_sw;
	uint8_t io_ch_bs_sw;
    uint8_t access_flag               : 1; 
	uint8_t enable_flag               : 1;
	uint8_t keypad_keys_enable_flag   : 1; 
   	uint8_t keypad_pressed_state      : 1;
	uint8_t enter_sw_pressed_state    : 1;
	uint8_t bs_sw_pressed_state       : 1;
    uint8_t                           : 2;	
    uint8_t base_sw_ch_id             :	(DEV_CH_ID_BIT_SIZE + 1);    //col1's key as base sw
	uint8_t                           : (8 - (DEV_CH_ID_BIT_SIZE + 1));
} keyboard_ctrl_t;

typedef struct
{
	  uint8_t data_id;          	  
} keyboard_status_t;		
	
typedef enum
{ 
  WHOLE_KEYBOARD, PART_KEYPAD, PART_ENTER_SW, PART_BS_SW
} keyboard_part_t;
  
/* -------------------- public variable declaration --------------------------------------- */
extern keyboard_ctrl_t keyboard_ctrl[];

 /* -------------------- public prototype declaration --------------------------------------- */
uint8_t Keyboard_Read(const uint8_t keyboard_ch_id, void *const pressed_key_ptr);
uint8_t Entered_Key_No_Long_Press_Proc(keyboard_ctrl_t *const cur_keyboard_ctrl_ptr);
uint8_t Keyboard_Disable(const uint8_t keyboard_ch_id);
uint8_t Disable_All_Keyboards(void);
uint8_t Keyboard_Enable(const uint8_t keyboard_ch_id);
uint8_t Keyboard_Allow_Access(const uint8_t keyboard_ch_id);
uint8_t Keyboard_No_Access(const uint8_t keyboard_ch_id);
uint8_t Get_Data_By_Keyboard(const uint8_t keyboard_ch_id, const uint8_t data_id );
uint8_t Keyboard_Init(const uint8_t keyboard_ch_id);
uint8_t Keyboard_DeInit(const uint8_t keyboard_ch_id);
uint8_t Keyboard_Part_Oper_Proc(const uint8_t keyboard_ch_id, const uint8_t keyboard_part_and_oper_data);
uint8_t Keyboard_Keypad_Oper(const uint8_t keyboard_ch_id, const uint8_t dev_oper);
uint8_t Keyboard_Enter_SW_Oper(const uint8_t keyboard_ch_id, const uint8_t dev_oper);
uint8_t Keyboard_BS_SW_Oper(const uint8_t keyboard_ch_id, const uint8_t dev_oper);
uint8_t Keyboard_Enter_SW_Read_Proc(const uint8_t keyboard_ch_id);
uint8_t Keyboard_BS_SW_Read_Proc(const uint8_t keyboard_ch_id);

#endif

/*------------------------------------------------------------------*-
  ------------------------ END OF FILE ------------------------------
-*------------------------------------------------------------------*/
