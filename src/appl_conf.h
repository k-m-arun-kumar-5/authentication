/**************************************************************************
   FILE          :    appl_conf.h
 
   PURPOSE       :   main application configuration Header
 
   AUTHOR        :    K.M. Arun Kumar alias Arunkumar Murugeswaran
 
  KNOWN BUGS     :
	
  NOTE           :   
  
  CHANGE LOGS    :
	   
 **************************************************************************/
 
 #ifndef _APPL_CONF_H
 #define _APPL_CONF_H 
 
/* -------------------------------- Debug Conf -----------------------------------------*/
 //#define TRACE                                   (1U)
#define TRACE_ERROR                                 (2U)

#define TRACE_LCD_CH_ID                             (CH_ID_00)
#define TRACE_UART_CH_ID                            (CH_ID_00) 

/* -------------------------------  Macro Conf ------------------------------------------*/
//#define SHOULD_REMOVE                 (3)
#define SHOULD_CALL                     (4)
//#define TEST                          (5)                                                  
#define SW_PRESS_HOLD_CPU               (6)
//#define DMA_DATA_ID_STR               (7)
//#define STR_TO_NUM_FROM_RIGHT_TO_LEFT   (8)

/*------------------------------- LCD Disp Conf ------------------------------------------*/
#ifdef LCD_MOD_ENABLE

#define WELCOME_MSG_LINE_NUM          NUM_LINE1
#define WELCOME_MSG_START_COL_NUM     NUM_COL1
#define ACCOUNT_MSG_LINE_NUM          NUM_LINE1 
#define ACCOUNT_MSG_START_COL_NUM     NUM_COL1
#define PIN_MSG_LINE_NUM              NUM_LINE1
#define PIN_MSG_START_COL_NUM         NUM_COL1
#define FAILED_AUTH_REASON_LINE_NUM   NUM_LINE1
#define SUCCESS_AUTH_LINE_NUM         NUM_LINE1 
#define FAILED_SET_PIN_LINE_NUM          NUM_LINE1	
#define ERROR_LINE_NUM                   NUM_LINE4  
#define ACCOUNT_ENTRY_START_LINE_NUM     NUM_LINE2
#define ACCOUNT_ENTRY_START_COL_NUM      NUM_COL1
// ACCOUNT_ENTRY_START_LOC = loc of ACCOUNT_ENTRY_START_LINE_NUM and ACCOUNT_ENTRY_START_COL_NUM
#define ACCOUNT_ENTRY_START_LOC          BEGIN_LOC_LINE2 
   
// ACCOUNT_MSG_START_LOC = loc of ACCOUNT_MSG_LINE_NUM and ACCOUNT_MSG_START_COL_NUM
#define ACCOUNT_MSG_START_LOC            BEGIN_LOC_LINE1 
#define PIN_ENTRY_START_LINE_NUM         NUM_LINE2
#define PIN_ENTRY_START_COL_NUM          NUM_COL1 
#define FAILED_AUTH_LINE_NUM             NUM_LINE2
#define DISP_BLANK_LINE3_NUM             NUM_LINE3
#define DISP_BLANK_LINE4_NUM             NUM_LINE4
#define LONG_PRESSKEY_TIMEOUT_LINE_NUM   NUM_LINE3
//#define NO_KEYPRESS_TIMEOUT_LINE_NUM     NUM_LINE3
#define NO_KEYPRESS_TIMEOUT_LINE_NUM     NUM_LINE4
#define AUTH_TIMEOUT_LINE_NUM            NUM_LINE4
#define SET_PIN_TIMEOUT_LINE_NUM         NUM_LINE4

#endif
/* -------------------------------Timer State Conf ---------------------------------------*/


/* ------------------------------ ADC input signal val Conf ------------------------------*/


/* ------------------------------ Appl Data Types --------------------------------------- */
#define MAX_DATA_INPUT_DEVS                 (2)
#define MAX_DATA_OUTPUT_DEVS                (2)
#define MAX_DATA_RECEIVE_DEVS               (1) 
#define MAX_DATA_TRANSMIT_DEVS              (1)


typedef enum 
{
  DATA_ID_ACCOUNT, DATA_ID_PIN, DATA_ID_STATUS, NUM_DATA_IDS    	
} appl_data_id_t;

/* ------------------------------- Application Conf --------------------------------------*/

#define HIDDEN_KEY_DISP_CHAR                      ('X') 
#define DATA_MAX_NUM_ALLOCATED_CHARS              (11) 
#define HIDDEN_CHAR_LCD_DISP_TIME_IN_MS          (1000)
#define MAX_ICOUNT_HIDDEN_CHAR_DISP_1500MS       (1500)
#define MAX_JCOUNT_HIDDEN_CHAR_DISP_1500MS       (1500)

#define  NUM_CHARS_INPUTDATA        GIVEN_CHARS_MAX_CONFIG_LINES_AND_COLS

#define MAX_COUNT_LONG_PRESSKEY_TIMEOUT   (3U)  

#define MAX_TIMEOUT_NO_KEY_PRESS         (10)  
#define MAX_TIMEOUT_LONG_PRESS_KEY       (5)

#endif

/*------------------------------------------------------------------*-
  ------------------------ END OF FILE ------------------------------
-*------------------------------------------------------------------*/
