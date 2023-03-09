
/**************************************************************************
   FILE          :    port.h
 
   PURPOSE       :    port header - define port and its pin assignment.
 
   AUTHOR        :    K.M. Arun Kumar alias Arunkumar Murugeswaran
 
  KNOWN BUGS     :
	
  NOTE           :    port header - user interface to external device, such as LED, Switch,
 	connection to other microcontroller via RS232, USB, etc. 
 To avoid this header file to be included more than once, conditional directive is used  
	
  CHANGE LOGS     :  
	   
 **************************************************************************/
#ifndef _PORT_H
#define _PORT_H

/* ---------------------- macro defination ------------------------------------------------ */
	

/* ---------------------- data type defination -------------------------------------------- */
typedef enum 
{
 	IO_CH_LCD_CH_00_CMD = (IO_CH_55), IO_CH_LCD_CH_00_DATA =  (IO_CH_58), IO_CH_KEYPAD_CH_00_ROWA = (IO_CH_48),
	INTERNAL_ERROR_LED_IO_CH = (IO_CH_08)
} io_ch_map_op_ch_t;
 
typedef enum
{
	IO_CH_SW_CH_00 = (IO_CH_04), RESET_SW_IO_CH = IO_CH_SW_CH_00, IO_CH_SW_CH_01 = (IO_CH_06),  ACCOUNT_SW_IO_CH = IO_CH_SW_CH_01,
	IO_CH_KEYPAD_CH_00_COL1 = (IO_CH_52), IO_CH_KEYPAD_CH_00_ENTER = (IO_CH_62), IO_CH_KEYPAD_CH_00_BS = (IO_CH_63) 
} io_ch_map_ip_ch_t;

/* -------------------- public variable declaration --------------------------------------- */
 
/* -------------------- public function declaration --------------------------------------- */

 
#endif 

/*------------------------------------------------------------------*-
  ------------------------ END OF FILE ------------------------------
-*------------------------------------------------------------------*/
