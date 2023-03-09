/**************************************************************************
   FILE          :    dev_chs_map.h
 
   PURPOSE       :   
 
   AUTHOR        :    K.M. Arun Kumar alias Arunkumar Murugeswaran
 
  KNOWN BUGS     :
	
  NOTE           :   If enter or backspace SW is not a part of keypad, then set IO ch of that enter or backspace SW = IO_CH_INVALID.
  
  CHANGE LOGS    :
	   
 **************************************************************************/
 
 #ifndef _DEV_CHS_MAP_H
 #define _DEV_CHS_MAP_H
 
 #ifdef KEYBOARD_MOD_ENABLE
 //                                                 IO_CH_ROWA,             IO_CH_COL1,       IO_CH_ENTER,               IO_CH_BS,            ACCESS,   ENABLE,                                           
keyboard_ctrl_t keyboard_ctrl[]  = {  
	                                     { IO_CH_KEYPAD_CH_00_ROWA, IO_CH_KEYPAD_CH_00_COL1, IO_CH_KEYPAD_CH_00_ENTER, IO_CH_KEYPAD_CH_00_BS, STATE_NO, STATE_NO,	
										 
//                                KEYS_ENABLE,   , KEYPAD_PRESSED, ENTER_PRESSED, BS_PRESSED 										 
									 STATE_NO,	    STATE_LOW,         STATE_LOW,  STATE_LOW}											 
                                   };
#endif

#ifdef SEG7_MOD_ENABLE
//                            IO_CH_A_LED,           IO_CH_UNIT_DIGIT,             ACCESS, ENABLE,       TYPE      ,      NUM_DIGITS            											 
seg7_ctrl_t seg7_ctrl[] = {
                            { IO_CH_SEG7_CH_00_A_LED, IO_CH_SEG7_CH_00_UNIT_DIGIT, STATE_NO, STATE_NO, SEG7_COMMON_ANODE, SEG7_4_DIGIT }
                          };
#endif
						  
#ifdef LED_MATRIX_MOD_ENABLE
//                                         IO_CH_ROWA,                       IO_CH_COL1,   LED_MATRIX_ACCESS, LED_MATRIX_ENABLE,  TYPE         , FONT_TYPE,      SCAN_TYPE
 led_matrix_ctrl_t led_matrix_ctrl[] = {
	                                       {IO_CH_LED_MATRIX_CH_00_ROWA, IO_CH_LED_MATRIX_CH_00_COL1, STATE_NO, STATE_NO,  ROW_CATHODE_TYPE, FONT_SIZE_5_7, SEQ_WRITE_COL }
                                       };
#endif
 
#ifdef  SW_MOD_ENABLE
//                                          IO_CH,      SW_ACCESS, SW_ENABLE,  PRESSED_STATE
  sw_para_t sw_para[ NUM_INPUT_DEV_ID_SW_CHS] =                            
                                       {
										   {IO_CH_SW_CH_00, STATE_NO, STATE_NO, STATE_LOW},
                                           {IO_CH_SW_CH_01, STATE_NO, STATE_NO, STATE_LOW} 										   
                                       };	  
#endif

#ifdef LCD_MOD_ENABLE
//                                  IO_CH_CMD,           IO_CH_DATA,      LCD_ACCESS,  LCD_ENABLE,   INTERFACE,               FONT,         BUSY_FLAG
   lcd_ctrl_t lcd_ctrl[] = 
                              { 
                                  {IO_CH_LCD_CH_00_CMD, IO_CH_LCD_CH_00_DATA, STATE_NO, STATE_NO, DATA_INTERFACE_4_BITS, CHAR_FONT_5_8_DOTS, NO_CHECK_BUSY_FLAG,
								  
//                                MAX_AVAIL_LINES + 1, MAX_CONFIG_LINES + 1,    MAX_AVAIL_COLS + 1,     MAX_CONFIG_COLS + 1 
                                     (4 - 1) ,                 (4 - 1),          (20 - 1),           (20 - 1)                                                                                      
	                              }
                              };    										 
#endif


#endif
																					
/*------------------------------------------------------------------*-
  ------------------------ END OF FILE ------------------------------
-*------------------------------------------------------------------*/
																		
