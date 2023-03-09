/**************************************************************************
   FILE          :    uart.h
 
   PURPOSE       :      
 
   AUTHOR        :    K.M. Arun Kumar alias Arunkumar Murugeswaran
 
  KNOWN BUGS     :
	
  NOTE           :   
	
  CHANGE LOGS     :
	   
 **************************************************************************/
 
 /* to avoid this header file to be included more than once, conditional directive is used  */
#ifndef _UART_H
#define _UART_H

/* ---------------------- macro defination ------------------------------------------------ */


/* ---------------------- data type defination -------------------------------------------- */

 
/* -------------------- public variable declaration --------------------------------------- */
uint8_t UART_Init(const uint8_t uart_ch_id);
uint8_t UART_Transmit_Char(const uint8_t uart_ch_id, const unsigned char uart_tx_char);
uint8_t UART_Receive_Char(const uint8_t uart_ch_id,  unsigned char  *const uart_rcvd_char_ptr);
uint8_t UART_Transmit_Num(const uint8_t uart_ch_id, const uint8_t num_data_type, const disp_num_fmt_t disp_num_fmt, const int32_t uart_num);
uint8_t UART_Transmit_Str(const uint8_t uart_ch_id, const char *const transmit_str);

/* -------------------- public function declaration --------------------------------------- */

#endif

/*------------------------------------------------------------------*-
  ------------------------ END OF FILE ------------------------------
-*------------------------------------------------------------------*/
