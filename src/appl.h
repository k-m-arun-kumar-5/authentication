/**************************************************************************
   FILE          :    appl.h
 
   PURPOSE       :    application header.  
 
   AUTHOR        :   K.M. Arun Kumar alias Arunkumar Murugeswaran
 
  KNOWN BUGS     :
	
  NOTE           :   
	
  CHANGE LOGS     :
	   
 **************************************************************************/
 
 /* to avoid this header file to be included more than once, conditional directive is used  */
#ifndef _APPL_H
#define _APPL_H

 
/* ---------------------- macro defination ------------------------------------------------ */
#define ACCOUNT_SW_CODE               ('A')
#define RESET_SW_CODE                 ('R')

/* lcd_disp_status[] index ie lcd_disp_status[LONG_PRESS_TIME_STATUS_DISP_INDEX] = STATUS_DISP_ON, \
   then long press time status is displayed */
#define ERROR_STATUS_DISP_INDEX             (0)
#define LONG_PRESS_TIME_STATUS_DISP_INDEX   (1)
#define NO_KEY_PRESS_TIME_STATUS_DISP_INDEX (2)
#define AUTH_TIME_STATUS_DISP_INDEX         (3)
#define SET_PIN_TIME_STATUS_DISP_INDEX      (4)

/* ---------------------- data type defination -------------------------------------------- */
typedef enum 
{ 
   NO_KEY_PRESS_TIMEOUT_DISP = NUM_LCD_GNRL_DISP_DATAS, LONG_PRESS_TIMEOUT_DISP, AUTH_PROCESS_TIMEOUT_DISP, SET_PIN_TIMEOUT_DISP, AUTH_STATUS_DISP   
 } lcd_disp_data_t;
 
 typedef struct
 {
	uint8_t error_flag          : 1;
   	uint8_t long_press_key_flag : 1;
	uint8_t no_press_key_flag   : 1;
	uint8_t auth_time_flag      : 1;
    uint8_t set_pin_time_flag   : 1;
    uint8_t disp_status_flag    : 1;
    uint8_t                     : 2;	
 } lcd_disp_status_t;
 
typedef enum 
 {
	INITIAL_FSM, ACCOUNT_FSM ,PIN_FSM, AUTH_SUCCESS_FSM
 } auth_fsm;

typedef enum 
 {
	 INITIAL, INVALID_ACCOUNT, INVALID_PIN, AUTH_SUCCESS, TIMEOUT_LONG_KEY_PRESS, TIMEOUT_NO_KEY_PRESS
 } auth_status_fsm;

 typedef enum
 {
	ERR_LCD_NOT_DATA_SRC = NUM_SYS_STATUS, ERR_AUTH_FSM_PROC, ERR_LCD_LOC_CTRL, ERR_AFTER_SW_PRESS_STROKE, ERR_DISP_STATUS,
	ERR_UART_TRANSMIT_OPER, NUM_APPL_STATUS
 } appl_status_t;
 
/* -------------------- public variable declaration --------------------------------------- */
extern lcd_disp_status_t lcd_disp_status;
extern uint8_t appl_error_or_warning_flag;

/* -------------------- public function declaration --------------------------------------- */
uint8_t Auth_Fsm_Proc(const uint8_t input_read_status);
uint8_t After_Switch_Stoke_Proc(const unsigned char pressed_sw);
uint8_t Disp_Status_Fsm(void);
uint8_t Appl_Reset(const uint8_t reset_type);
uint8_t Set_Auth_Status_Disp_Fsm(const auth_status_fsm set_status_disp_fsm );

#endif

/*------------------------------------------------------------------*-
  ------------------------ END OF FILE ------------------------------
-*------------------------------------------------------------------*/
