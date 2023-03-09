/**************************************************************************
   FILE          :    led_matrix.h
 
   PURPOSE       :    
 
   AUTHOR        :   K.M. Arun Kumar alias Arunkumar Murugeswaran
 
  KNOWN BUGS     :
	
  NOTE           :   
  
  CHANGE LOGS    :
	   
 **************************************************************************/
 
 #ifndef _LED_MATRIX_H
 #define _LED_MATRIX_H
 
 /* ---------------------- macro defination ------------------------------------------------ */
 #define MAX_LED_MATRIX_NUM_CHARS         (10 + 26 + 7)
 #define NUM_DISP_MAP_EACH_CHAR           (5)
 
/* ---------------------- data type defination --------------------------------------------- */
typedef enum
{
	ROW_ANODE_TYPE, ROW_CATHODE_TYPE
} led_matrix_type_t;

typedef enum
{
	SEQ_WRITE_ROW, SEQ_WRITE_COL
} led_matrix_seq_write_t;

typedef enum
{
	FONT_SIZE_5_7, FONT_SIZE_8_8
} led_matrix_font_size_t;

typedef struct
{
	 uint8_t io_ch_rowa;
	 uint8_t io_ch_col1;
	 uint8_t access_flag              : 1; 
	 uint8_t enable_flag              : 1;
	 uint8_t row_type                 : 1; 
	 uint8_t font_size                : 1; 
	 uint8_t seq_write_type           : 1;
	 uint8_t                          : 3;
} led_matrix_ctrl_t;

typedef enum
{  
   DISP_LED_DOT_MATRIX_INC, DISP_LED_DOT_MATRIX_DCR, DISP_LED_DOT_MATRIX_NO_CHANGE 
} disp_data_ctrl_para_t;

/* -------------------- public variable declaration --------------------------------------- */
  extern const uint8_t led_dot_disp_map[(MAX_LED_MATRIX_NUM_CHARS )* NUM_DISP_MAP_EACH_CHAR];
  extern led_matrix_ctrl_t led_matrix_ctrl[NUM_OUTPUT_DEV_ID_LED_MATRIX_CHS];

 /* -------------------- public prototype declaration --------------------------------------- */
uint8_t LED_Matrix_Write(const uint8_t led_matrix_ch_id, const void *const led_matrix_data_code_ptr);
uint8_t LED_Matrix_Disable(const uint8_t led_matrix_ch_id);
uint8_t LED_Matrix_Enable(const uint8_t led_matrix_ch_id);
uint8_t Disable_All_LED_Matrixs(void);
uint8_t LED_Matrix_Allow_Access(const uint8_t led_matrix_ch_id);
uint8_t LED_Matrix_No_Access(const uint8_t led_matrix_ch_id);
uint8_t LED_Matrix_Init(const uint8_t led_matrix_ch_id);
uint8_t LED_Matrix_DeInit(const uint8_t led_matrix_ch_id);

#endif

/*------------------------------------------------------------------*-
  ------------------------ END OF FILE ------------------------------
-*------------------------------------------------------------------*/
