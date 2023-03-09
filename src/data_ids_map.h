/**************************************************************************
   FILE          :    data_ids_map.h
 
   PURPOSE       :   
 
   AUTHOR        :    K.M. Arun Kumar alias Arunkumar Murugeswaran
 
  KNOWN BUGS     :
	
  NOTE           :   If data terminator char = NULL_CHAR, then newly read chars are taken till max nums of chars is reached.
                 :   If data terminator char != NULL_CHAR, then if data's max data allocated char < num entered chars, then new entered chars are taken, till terminator char is read.
			            else, then newly read chars are discarded, till terminator char is read. 
  
  CHANGE LOGS    :
	   
 **************************************************************************/
 
 #ifndef _DATA_IDS_MAP_H
 #define _DATA_IDS_MAP_H 

 //                                            DATA_ID,     NUM_CHAR, SMALL_ALPHA, BIG_ALPHA, SPECIAL_CHAR, CTRL_CHAR, I/P_STREAM,             DISP_FORMAT,               
 const data_id_ctrl_para_t data_id_ctrl_para[]  = {  
	                                         { DATA_ID_ACCOUNT, STATE_YES,  STATE_YES, STATE_YES, STATE_NO,  STATE_NO, DATA_NO_STREAM, RCVD_CHAR_PLAIN_DISP_FORMAT,
											 
//											  O/P_DATA_TYPE,         I/P_DATA_TYPE,     O/P_STREAM,  TX_STREAM,         RCV_STREAM,  TERMINATOR, RETRY, REQ_MAX_CHARS
											 DATA_TYPE_IN_STR, 	DATA_TYPE_IN_STR, DATA_NO_STREAM, DATA_NO_STREAM,   DATA_NO_STREAM,  ENTER_CHAR,  3,       5 },

//                                           DATA_ID,     NUM_CHAR, SMALL_ALPHA, BIG_ALPHA, SPECIAL_CHAR, CTRL_CHAR, I/P_STREAM,             DISP_FORMAT,               
 	                                         { DATA_ID_PIN, STATE_YES,  STATE_YES, STATE_YES, STATE_NO,  STATE_NO, DATA_NO_STREAM, RCVD_CHAR_HIDDEN_DISP_FORMAT,
											 
//											  O/P_DATA_TYPE,        I/P_DATA_TYPE,       O/P_STREAM,        TX_STREAM,        RCV_STREAM,   TERMINATOR, RETRY, REQ_MAX_CHARS
											  DATA_TYPE_IN_STR,  DATA_TYPE_IN_STR, DATA_NO_STREAM,  DATA_NO_STREAM,   DATA_NO_STREAM,         NULL_CHAR,  3,    4 }, 
											  
 //                                           DATA_ID,       NUM_CHAR, SMALL_ALPHA, BIG_ALPHA, SPECIAL_CHAR, CTRL_CHAR, I/P_STREAM,             DISP_FORMAT,               
 	                                         { DATA_ID_STATUS, STATE_YES,  STATE_YES, STATE_YES, STATE_NO,  STATE_NO, DATA_NO_STREAM,   RCVD_CHAR_PLAIN_DISP_FORMAT,
											 
//											  O/P_DATA_TYPE,        I/P_DATA_TYPE,       O/P_STREAM,        TX_STREAM,        RCV_STREAM,       TERMINATOR, RETRY, REQ_MAX_CHARS
											  DATA_TYPE_IN_STR,  DATA_TYPE_NO_DATA,   DATA_NO_STREAM,  DATA_NO_STREAM,      DATA_NO_STREAM,     NULL_CHAR,  0,        0 }                                     
										 
                                           };

//                                                 DATA_ID,          INPUT_DEV,                 OUTPUT_DEV,         	RECEIVE_DEV,      TRANSMIT_DEV        									   
 const data_id_dev_src_t  data_ids_dev_srcs[] = {
	                                             {DATA_ID_ACCOUNT, {INPUT_DEV_ID_KEYBOARD, CH_ID_00, DEV_ID_INVALID}, {OUTPUT_DEV_ID_LCD, CH_ID_00, DEV_ID_INVALID},  {DEV_ID_INVALID}, {DEV_ID_INVALID}},
												 {DATA_ID_PIN, {INPUT_DEV_ID_KEYBOARD, CH_ID_00, DEV_ID_INVALID}, {OUTPUT_DEV_ID_LCD, CH_ID_00, DEV_ID_INVALID},  {DEV_ID_INVALID}, {DEV_ID_INVALID}},
												 {DATA_ID_STATUS, {DEV_ID_INVALID}, {OUTPUT_DEV_ID_LCD, CH_ID_00, DEV_ID_INVALID}, {DEV_ID_INVALID}, {DEV_ID_INVALID}}
		                                       };												 

#endif
																						 
/*------------------------------------------------------------------*-
  ------------------------ END OF FILE ------------------------------
-*------------------------------------------------------------------*/
																						 
