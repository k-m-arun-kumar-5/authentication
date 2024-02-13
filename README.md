Description :
============
 Single user account authentication process. 

Design
=======
A preset PIN and account number is set by default in code. Entered PIN in keypad is displayed in LCD. Use RESET_SW to reset Process, if any problem arises and start afresh. Use Enter SW to end input and entered data is at end. At first Welcome message to be displayed, when ACCOUNT_SW is pressed, account number is entered. If entered account number is correct, then ask for PIN and if entered PIN is correct, then display Next stage. If account number is incorrect and ask to reenter account
number. After 3 failed iteration on entered account number, stop reenter of account number and display visit bank. If no key is pressed for longer duration or key has been pressed for long duration, display timeout and display visit bank. After 3 failed iteration on entered PIN number, stop reenter of PIN number and display visit bank. After displayed auth status, wait for predetermined time, and then display welcome message and wait for ACCOUNT_SW to be pressed to enter account number. RESET_SW is pressed to restart the process, if any problem arises.

CAUTION:
========
Schematics and simulation is done by Proteus CAD. NOT EXPERIMENTED IN REAL TIME ENVIRONMENT.

Purpose :
=========
In all my respective repositories, I just shared my works that I worked as the learning path and practiced, with designed, developed, implemented, simulated and tested, including some projects, assignments, documentations and all other related files and some programming that might not being implement, not being completed, lacks some features or have some bugs. Purpose of all my repositories, if used, can be used for EDUCATIONAL PURPOSE ONLY. It can be used as the open source and freeware. Kindly read the LICENSE.txt for license, terms and conditions about the use of source codes, binaries, documentation and all other files, located in all my repositories. 
       
