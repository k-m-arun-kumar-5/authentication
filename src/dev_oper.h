/**************************************************************************
   FILE          :    dev_oper.h
 
   PURPOSE       :    Device Operation
 
   AUTHOR        :   K.M. Arun Kumar alias Arunkumar Murugeswaran
 
  KNOWN BUGS     :
	
  NOTE           :    
	
  CHANGE LOGS     :  
	   
 **************************************************************************/
#ifndef _DEV_OPER_H
#define _DEV_OPER_H

/* ---------------------- macro defination ------------------------------------------------ */
#define CUR_DATA_ID_ALL_SRC_OF_SPEC_OPER      NUM_DEVS 
#define DATA_READ_STATUS_INPUT_MODE_DATA_POS          (0)
#define DATA_READ_STATUS_MAX_CHARS_REACH_DATA_POS     (1)
#define DATA_READ_STATUS_TERMINATOR_READ_DATA_POS     (2)

#define DATA_READ_STATUS_MAX_CHARS_NOT_REACHED        (0)
#define DATA_READ_STATUS_MAX_CHARS_REACHED            (1)
#define DATA_READ_STATUS_TERMINATOR_NOT_READ          (0)
#define DATA_READ_STATUS_TERMINATOR_READ              (1)    

/* ---------------------- data type defination -------------------------------------------- */
typedef struct
{
	uint8_t  dev_id    : DEV_ID_BIT_SIZE;
	uint8_t  dev_ch_id : DEV_CH_ID_BIT_SIZE;
} dev_id_t;

typedef enum
{
	DEV_INPUT_TYPE, DEV_OUTPUT_TYPE, DEV_RECEIVE_TYPE, DEV_TRANSMIT_TYPE, NUM_DEV_TYPES
} dev_type_t;

typedef struct
{
   uint8_t data_id;
   dev_id_t data_input_dev_ids[MAX_DATA_INPUT_DEVS];
   dev_id_t data_output_dev_ids[MAX_DATA_OUTPUT_DEVS];
   dev_id_t data_receive_dev_ids[MAX_DATA_RECEIVE_DEVS];
   dev_id_t data_transmit_dev_ids[MAX_DATA_TRANSMIT_DEVS];
} data_id_dev_src_t;

 typedef enum
{
  OUTPUT_DEV_ID_DAC, OUTPUT_DEV_ID_PWM, OUTPUT_DEV_ID_SEG7, OUTPUT_DEV_ID_LCD, OUTPUT_DEV_ID_LED_MATRIX, COMM_DEV_ID_UART, COMM_DEV_ID_I2C,
  COMM_DEV_ID_SPI, COMM_DEV_ID_MISC, INPUT_DEV_ID_KEYBOARD, INPUT_DEV_ID_ADC, INPUT_DEV_ID_SW, INPUT_DEV_ID_MISC, NUM_DEVS, DEV_ID_INVALID 	
} dev_src_id_t;
 
 #define    BEGIN_OUTPUT_DEV_ID            OUTPUT_DEV_ID_DAC
 #define    END_OUTPUT_DEV_ID              OUTPUT_DEV_ID_LED_MATRIX
 #define    BEGIN_COMM_DEV_ID             COMM_DEV_ID_UART
 #define    END_COMM_DEV_ID               COMM_DEV_ID_MISC
 #define    BEGIN_INPUT_DEV_ID             INPUT_DEV_ID_KEYBOARD
 #define    END_INPUT_DEV_ID               INPUT_DEV_ID_SW 
 
typedef enum
 { 
   INPUT_DEV_DEINIT_OPER_FUNC,  INPUT_DEV_INIT_OPER_FUNC, INPUT_DEV_NO_ACCESS_OPER_FUNC, INPUT_DEV_ALLOW_ACCESS_OPER_FUNC, 
   INPUT_DEV_DISABLE_OPER_FUNC, INPUT_DEV_ENABLE_OPER_FUNC,  INPUT_DEV_OPEN_OPER_FUNC, INPUT_DEV_CLOSE_OPER_FUNC,
   INPUT_DEV_INPUT_OPER_FUNC, OUTPUT_DEV_DEINIT_OPER_FUNC,  OUTPUT_DEV_INIT_OPER_FUNC, OUTPUT_DEV_NO_ACCESS_OPER_FUNC, 
   OUTPUT_DEV_ALLOW_ACCESS_OPER_FUNC, OUTPUT_DEV_DISABLE_OPER_FUNC, OUTPUT_DEV_ENABLE_OPER_FUNC, OUTPUT_DEV_OPEN_OPER_FUNC, 
   OUTPUT_DEV_CLOSE_OPER_FUNC, OUTPUT_DEV_OUTPUT_OPER_FUNC, COMM_DEV_DEINIT_OPER_FUNC,  COMM_DEV_INIT_OPER_FUNC, 
   COMM_DEV_NO_ACCESS_OPER_FUNC, COMM_DEV_ALLOW_ACCESS_OPER_FUNC, COMM_DEV_DISABLE_OPER_FUNC, COMM_DEV_ENABLE_OPER_FUNC,
   COMM_DEV_OPEN_OPER_FUNC, COMM_DEV_CLOSE_OPER_FUNC, COMM_DEV_RECEIVE_OPER_FUNC, COMM_DEV_TRANSMIT_OPER_FUNC
 } dev_oper_func_t; 

#define START_INPUT_DEV_OPER_FUNC              INPUT_DEV_DEINIT_OPER_FUNC
#define END_INPUT_DEV_OPER_FUNC                INPUT_DEV_INPUT_OPER_FUNC
#define START_OUTPUT_DEV_OPER_FUNC             OUTPUT_DEV_DEINIT_OPER_FUNC
#define END_OUTPUT_DEV_OPER_FUNC               OUTPUT_DEV_OUTPUT_OPER_FUNC
#define START_COMM_DEV_OPER_FUNC               COMM_DEV_DEINIT_OPER_FUNC
#define END_COMM_DEV_OPER_FUNC                 COMM_DEV_TRANSMIT_OPER_FUNC

#define START_INPUT_DEV_BASIC_OPER_FUNC        INPUT_DEV_DEINIT_OPER_FUNC
#define END_INPUT_DEV_BASIC_OPER_FUNC          INPUT_DEV_ENABLE_OPER_FUNC
#define START_OUTPUT_DEV_BASIC_OPER_FUNC       OUTPUT_DEV_DEINIT_OPER_FUNC
#define END_OUTPUT_DEV_BASIC_OPER_FUNC         OUTPUT_DEV_ENABLE_OPER_FUNC
#define START_COMM_DEV_BASIC_OPER_FUNC        COMM_DEV_DEINIT_OPER_FUNC
#define END_COMM_DEV_BASIC_OPER_FUNC          COMM_DEV_ENABLE_OPER_FUNC
 
typedef uint8_t (*dev_deinit_t)(const uint8_t dev_ch_id);
typedef uint8_t (*dev_init_t)(const uint8_t dev_ch_id);
typedef uint8_t (*dev_no_access_t)(const uint8_t dev_ch_id);
typedef uint8_t (*dev_allow_access_t)(const uint8_t dev_ch_id);
typedef uint8_t (*dev_disable_t)(const uint8_t dev_ch_id);
typedef uint8_t (*dev_enable_t)(const uint8_t dev_ch_id);
typedef uint8_t (*dev_receive_t)(const uint8_t dev_ch_id, void *const receive_data_ptr);
typedef uint8_t (*dev_transmit_t)(const uint8_t dev_ch_id, const void *const transmit_data_ptr);
typedef uint8_t (*dev_read_t)(const uint8_t dev_ch_id, void *const input_devs_ptr);
typedef uint8_t (*dev_write_t)(const uint8_t dev_ch_id, const void *const output_devs_ptr);
typedef uint8_t (*dev_open_t)(const uint8_t dev_ch_id, const void *const open_option_ptr );
typedef uint8_t (*dev_close_t)(const uint8_t dev_ch_id, const void *const close_option_ptr );

typedef struct 
{
	dev_deinit_t Dev_DeInit_Func_Ptr;
	dev_init_t   Dev_Init_Func_Ptr;
	dev_no_access_t Dev_No_Access_Func_Ptr;
	dev_allow_access_t Dev_Allow_Access_Func_Ptr;
	dev_disable_t Dev_Disable_Func_Ptr;
	dev_enable_t Dev_Enable_Func_Ptr;
	dev_receive_t Dev_Receive_Func_Ptr;
	dev_transmit_t Dev_Transmit_Func_Ptr;
	dev_read_t  Dev_Read_Func_Ptr;
	dev_write_t Dev_Write_Func_Ptr;	
	/*dev_open_t  Dev_Open_Func_Ptr;
	dev_close_t Dev_Close_Func_Ptr; */
}  Dev_Oper_Func_t;

typedef struct
{
	unsigned char rcvd_data_char;
	data_input_status_t cur_data_input_status;
} dev_input_ctrl_para_t;

typedef struct
{
	uint8_t led_matrix_scroll_fmt;
	#ifdef LCD_MOD_ENABLE
	  lcd_disp_ctrl_t lcd_disp_para;
	#endif
} dev_output_ctrl_para_t;

 /* -------------------- public variable declaration --------------------------------------- */
 extern Dev_Oper_Func_t Dev_Oper_Func_Table[];
 extern const data_id_dev_src_t  data_ids_dev_srcs[NUM_DATA_IDS];
 
/* -------------------- public function declaration --------------------------------------- */
uint8_t Data_Dev_Src_Access_Oper_Func(const uint8_t prev_data_id);
uint8_t Data_ID_Devs_Src_Set(const data_id_dev_src_t *const data_id_dev_src_conf_ptr, const uint8_t num_conf_size);
uint8_t Cur_Data_ID_Input_Devs_Read_Oper_Func(unsigned char *const last_read_data_char_ptr);
uint8_t Cur_Data_ID_Output_Devs_Write_Oper_Func(const dev_output_ctrl_para_t *const dev_output_ctrl_para_ptr);
uint8_t Cur_Data_ID_Devs_Src_Basic_Oper_Func(const uint8_t dev_src_basic_oper_func, const uint8_t dev_type, const dev_id_t *const cur_data_devs_src_allow_ptr );
uint8_t Set_Data_Devs_Src_Allow(const uint8_t dev_type, const uint8_t data_dev_allow_type, dev_id_t *const cur_data_devs_src_allow_ptr);
uint8_t Reset_Data_Devs_Src_Allow(dev_id_t *const cur_data_devs_src_allow_ptr);
uint8_t Cur_Data_ID_Comm_Devs_Receive_Oper_Func(unsigned char *const last_rcvd_data_char_ptr);
uint8_t Data_ID_Src_Spec_Dev_Find_Dev_Ch_ID(const uint8_t data_id, dev_id_t *const dev_data_ptr, const uint8_t dev_type);
uint8_t Dev_ID_Validate(dev_id_t *const dev_data_ptr, const uint8_t dev_type);

#endif

/*------------------------------------------------------------------*-
  ------------------------ END OF FILE ------------------------------
-*------------------------------------------------------------------*/
