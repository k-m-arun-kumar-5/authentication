/**************************************************************************
   FILE          :    io_lib.h
 
   PURPOSE       :    IO Library header 
 
   AUTHOR        :    K.M. Arun Kumar alias Arunkumar Murugeswaran
 
  KNOWN BUGS     :
	
  NOTE           :    
	
  CHANGE LOGS     :  
	   
 **************************************************************************/
#ifndef _IO_LIB_H
#define _IO_LIB_H

 /* ---------------------- macro defination ------------------------------------------------ */
#define PIN_SIG_DIGITAL       (0)
#define PIN_SIG_ANALOG        (1)

#define IO_DIR_INPUT           (0)                  
#define IO_DIR_OUTPUT          (1)

#define IO_FUNC_MODE_00       (0)
#define IO_FUNC_MODE_01       (1)
#define IO_FUNC_MODE_02       (2)
#define IO_FUNC_MODE_03       (3) 

#define IO_FUNC_TYPE_GPIO_NON_SW           (0)
#define IO_FUNC_TYPE_GPIO_SW               (1)

#define CH_ID_ALLOC_DYNAMIC    (0)
#define CH_ID_ALLOC_FIXED      (1)
 
/* ---------------------- data type defination -------------------------------------------- */
typedef enum 
{
	 CH_ID_00, CH_ID_01, CH_ID_02, CH_ID_03, CH_ID_04, CH_ID_05, CH_ID_06, CH_ID_07, 
	 CH_ID_08, CH_ID_09, CH_ID_10, CH_ID_11, CH_ID_12, CH_ID_13, NUM_CHS, CH_ID_INVALID
} ch_id_t; 
 
typedef enum
 {  IO_FUNC_GPIO, IO_FUNC_SPI, IO_FUNC_I2C , IO_FUNC_UART, IO_FUNC_ADC, IO_FUNC_DAC, IO_FUNC_PWM, IO_FUNC_TIMER, 
    IO_FUNC_EXTR_INTP, IO_FUNC_CAPTURE,IO_FUNC_COMP,IO_FUNC_DEBUG, IO_FUNC_TRACE, IO_FUNC_RESERVE, IO_FUNC_UNUSED,
    IO_FUNC_INVALID 
 } io_func_t; 
 
typedef struct
{
	uint8_t io_ch         : 6;        // IO ch [0:63]
	uint8_t signal        : 1;        // analog, digital
	uint8_t dir           : 1;        // input or output 
	uint8_t func          : 4;        // pin function type ie GPIO, ADC, DAC, Timer, SPI, or I2C, etc	
	uint8_t state         : 1;        // in output, initial state or in input, if func_type == IO_FUNC_TYPE_GPIO_SW,  then sw pressed state
    uint8_t ch_id_alloc_type   : 1;        // ch id alloc fixed or dynamic    	
	uint8_t func_type     : 1;        /* for a specific pin function, its type eg for func = IO_FUNC_GPIO ,dir = IO_DIR_INPUT, and 
	                                     if func_type == IO_FUNC_TYPE_GPIO_SW, then SW is connected at io_ch, else non sw eg LCD with its data port as input */
	uint8_t port_pin_len;									 
										 
} io_config_t;

typedef enum
{
    PORT_CH_00, PORT_CH_01, NUM_PORT_CHS	
} port_ch_t;

typedef struct
{
	  uint8_t port;
	  uint8_t port_pin;
} io_port_t;

typedef enum 
{ 
  PIN_00, PIN_01, PIN_02, PIN_03, PIN_04, PIN_05, PIN_06, PIN_07, 
  PIN_08, PIN_09, PIN_10, PIN_11, PIN_12, PIN_13, PIN_14, PIN_15,
  PIN_16, PIN_17, PIN_18, PIN_19, PIN_20, PIN_21, PIN_22, PIN_23,
  PIN_24, PIN_25, PIN_26, PIN_27, PIN_28, PIN_29, PIN_30, PIN_31,
  NUM_PINS_PER_PORT   
} io_pin_t;

typedef enum 
{
  IO_CH_00, IO_CH_01, IO_CH_02, IO_CH_03, IO_CH_04, IO_CH_05, IO_CH_06, IO_CH_07, 
  IO_CH_08, IO_CH_09, IO_CH_10, IO_CH_11, IO_CH_12, IO_CH_13, IO_CH_14, IO_CH_15,
  IO_CH_16, IO_CH_17, IO_CH_18, IO_CH_19, IO_CH_20, IO_CH_21, IO_CH_22, IO_CH_23,
  IO_CH_24, IO_CH_25, IO_CH_26, IO_CH_27, IO_CH_28, IO_CH_29, IO_CH_30, IO_CH_31,
	IO_CH_48 = 48, IO_CH_49, IO_CH_50, IO_CH_51, IO_CH_52, IO_CH_53, IO_CH_54, IO_CH_55, 
  IO_CH_56, IO_CH_57, IO_CH_58, IO_CH_59, IO_CH_60, IO_CH_61, IO_CH_62, IO_CH_63,
	NUM_IO_CHS = 48, IO_CH_INVALID
} io_ch_t;

/* -------------------- public variable declaration --------------------------------------- */
   extern uint32_t default_port_mask[NUM_PORT_CHS]; 
   
/* -------------------- public function declaration --------------------------------------- */
uint8_t IO_Channels_Func_Set(const io_config_t *const io_config_ptr);
uint8_t IO_Channel_Read(const uint8_t io_ch, uint8_t *const cur_data_devs_src_allow_ptr);
void Reset_Ports(void);
uint8_t Port_Write(const uint8_t io_channel, const void *const data_ptr);
uint8_t IO_Channel_Write(const uint8_t io_channel, const uint8_t data);
void Reset_IO_Chs(void);
uint8_t Config_Port_Pin_Range_Validate(const io_config_t *const io_config_ptr );
uint8_t Port_Read(const uint8_t io_channel, void *const data_ptr);
uint8_t IO_Ch_Func_Reset(const io_config_t *const io_unconfig_ptr);
uint8_t Check_GPIO_Func(const uint8_t io_channel, const void *const data_ptr);
uint8_t Non_GPIO_Func_Set(uint8_t io_ch, uint8_t func_mode); 
uint8_t IO_Ch_Validate(const uint8_t base_io_ch, const uint8_t num_io_chs);
uint8_t Output_Dev_Init(uint8_t base_io_ch, const uint8_t num_io_chs);
uint8_t Output_Dev_DeInit(uint8_t base_io_ch, const uint8_t num_io_chs);

#endif

/*------------------------------------------------------------------*-
  ------------------------ END OF FILE ------------------------------
-*------------------------------------------------------------------*/
