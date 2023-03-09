/**************************************************************************
   FILE          :    io_conf.h
 
   PURPOSE       :   main peripherial configuration Header
 
   AUTHOR        :   K.M. Arun Kumar alias Arunkumar Murugeswaran
 
  KNOWN BUGS     :
	
  NOTE           :   
  
  CHANGE LOGS    :
	   
 **************************************************************************/
 
 #ifndef _IO_CONF_H
 #define _IO_CONF_H
 

/* -------------------------------- OSC Freq conf -------------------------------------*/
 #define _XTAL_FREQ                              (12000000)
 
 /* ------------------------------ Number of Device Channels ----------------------------- */
#define NUM_COMM_DEV_ID_UART_CHS                  (2)
#define NUM_COMM_DEV_ID_I2C_CHS                   (1)
#define NUM_COMM_DEV_ID_SPI_CHS                   (1)
#define NUM_COMM_DEV_ID_MISC_CHS                  (1)  
#define NUM_INPUT_DEV_ID_MISC_CHS            (1)          
#define NUM_INPUT_DEV_ID_ADC_CHS             (1) 
#define NUM_INPUT_DEV_ID_KEYBOARD_CHS        (1)
#define NUM_INPUT_DEV_ID_SW_CHS              (7)
#define NUM_OUTPUT_DEV_ID_LED_MATRIX_CHS     (1)
#define NUM_OUTPUT_DEV_ID_DAC_CHS            (1)
#define NUM_OUTPUT_DEV_ID_PWM_CHS            (1)
#define NUM_OUTPUT_DEV_ID_LCD_CHS            (1)
#define NUM_OUTPUT_DEV_ID_SEG7_CHS           (1)

/* --------------------------------- module enable conf ---------------------------------*/ 
// #define TIMER1_MOD_ENABLE                      (01)
// #define TIMER2_MOD_ENABLE                      (02) 
// #define TIMER0_MOD_ENABLE                      (03)
 #define LCD_MOD_ENABLE                           (04)
 #define KEYBOARD_MOD_ENABLE                      (05)
// #define CAPTURE_MOD_ENABLE                     (06)
// #define COMPARE_MOD_ENABLE                     (07)
// #define PWM_MOD_ENABLE                         (08)
 #define USART_MOD_ENABLE                       (09)
// #define ADC_MOD_ENABLE                         (10)
// #define GSM_MOD_ENABLE                         (11)
// #define COMPARATOR1_MOD_ENABLE                 (12)
// #define COMPARATOR2_MOD_ENABLE                 (13)
// #define SPI_MOD_ENABLE                         (14)
// #define I2C_MOD_ENABLE                         (15) 
// #define WATCHDOG_TIMER_MOD_ENABLE              (16)
// #define SW_MOD_ENABLE                          (17)
// #define SEG7_MOD_ENABLE                        (18)
// #define DAC_MOD_ENABLE                         (19)
// #define OUTPUT_MISC_MOD_ENABLE                 (20)
// #define INPUT_MISC_MOD_ENABLE                  (21)
// #define MISC_MOD_ENABLE                        (22)
// #define LED_MATRIX_MOD_ENABLE                  (23)

#ifdef SW_MOD_ENABLE 
   #include "sw_lib.h"
#endif

#ifdef KEYBOARD_MOD_ENABLE 
  #ifndef SW_MOD_ENABLE
    #define SW_MOD_ENABLE                          (17) 
    #include "sw_lib.h"
  #endif
  #include "keyboard.h"    
#endif

#ifdef SEG7_MOD_ENABLE
  #include "seg7_lib.h"
#endif
 
#ifdef LED_MATRIX_MOD_ENABLE
  #include "led_matrix.h"
#endif

#ifdef LCD_MOD_ENABLE
   #include "lcd.h"
#endif
 
#ifdef USART_MOD_ENABLE
  #include "uart.h"
#endif
  
/* ------------------------------- LCD oper conf ---------------------------------------*/ 
#ifdef LCD_MOD_ENABLE

 #define MAX_LCD_DIGITS                    (10) 
 
#define MAX_ICOUNT_LCD_1500MS              (2000)
#define MAX_JCOUNT_LCD_1500MS              (2000)
 
#define MAX_ICOUNT_LCD_10MS              (400)
#define MAX_JCOUNT_LCD_10MS              (400)

#define MAX_ICOUNT_LCD_1MS               (100) 
#define MAX_JCOUNT_LCD_1MS               (100)

// for JHD162A series LCD parameters
#define LCD_WRITE_ENABLE_PULSE_IN_USEC       (1)
#define LCD_ADDR_SETUP_IN_USEC               (1)
#define LCD_ENABLE_PULSE_BEFORE_WRITE_IN_USEC (1)
#define LCD_DATA_SETUP_IN_USEC               (1)
#define LCD_WRITE_ENABLE_PULSE_DELAY_IN_USEC (1)
#define LCD_CLEAR_EXEC_IN_USEC             (1650)
#define LCD_CURSOR_RETURN_EXEC_IN_USEC     (1650)
#define LCD_OTHER_INST_EXEC_IN_USEC          (40) 

#endif
/* -------------------------------- timer oper conf ------------------------------------*/

#define TIMER1_PRESET_TIME_DELAY_IN_MULTIPLE                    (1U)
#define TIMER1_POSTSET_TIME_DELAY_IN_MULTIPLE                   (2U) 
#define TIMER1_SET_TIME_DELAY_IN_MULTIPLE                       TIMER1_PRESET_TIME_DELAY_IN_MULTIPLE

#define TIMER1_TICK_IN_MILLI_SEC                                (50U)  
#define TIMER1_REQ_TIME_1_UPDATE_REACHED_IN_MILLI_SEC           TIME_UNIT_1_SEC_IN_MILLI_SEC
 //in Timer1_Load_Init_Val_Calc() in timer.c, change variable inc_timer1, which (directly loads initial TMR1 values ), depends on Osc freq
 
 
#define TIMER2_PRESET_TIME_DELAY_IN_MULTIPLE                    (1U)
#define TIMER2_POSTSET_TIME_DELAY_IN_MULTIPLE                   (2U) 
#define TIMER2_SET_TIME_DELAY_IN_MULTIPLE                       TIMER2_PRESET_TIME_DELAY_IN_MULTIPLE
 
#define TIMER2_TICK_IN_MILLI_SEC                               (50U)  
#define TIMER2_REQ_TIME_1_UPDATE_REACHED_IN_MILLI_SEC          TIME_UNIT_1_SEC_IN_MILLI_SEC 
//in Timer2_Load_Init_Val_Calc() in timer.c, change variable inc_timer2, which (directly loads initial TMR2 values ), depends on Osc freq
  
/* ------------------------------- uart oper conf -------------------------------------- */
#ifdef USART_MOD_ENABLE

#define MAX_UART_DIGITS                      (31) 
#define LCD_BEGIN_LOC_ECHO_UART_RCVD_STR      BEGIN_LOC_LINE2

#endif

/* ------------------------------- 7 segment LED oper conf ------------------------------*/
#ifdef  SEG7_MOD_ENABLE

#define MAX_SEG7_DIGITS                   SEG7_6_DIGIT 
#define REQ_CNT_SEG7_REPEAT_NUM                  (20)
#define MAX_ICOUNT_7SEG_SW_DELAY                 (12)
#define MAX_JCOUNT_7SEG_SW_DELAY                 (12)

#endif

/* ------------------------------- LED DOT MATRIX oper conf -----------------------------*/
#ifdef LED_MATRIX_MOD_ENABLE

#define REG_CNT_LED_MATRIX_CHAR                   (10) 
#define REQ_SCAN_DELAY_IN_MS                      (1)
#define MAX_ICOUNT_LED_MATRIX_SCAN_DELAY          (12) 
#define MAX_JCOUNT_LED_MATRIX_SCAN_DELAY          (12)

#endif

/* ------------------------------------ SW oper conf ------------------------------------*/
#ifdef SW_MOD_ENABLE

#define MAX_ICOUNT_SW_DEBOUNCE_SW_DELAY           (100) 
#define MAX_JCOUNT_SW_DEBOUNCE_SW_DELAY           (100)

#endif

#endif

/*------------------------------------------------------------------*-
  ------------------------ END OF FILE ------------------------------
-*------------------------------------------------------------------*/
