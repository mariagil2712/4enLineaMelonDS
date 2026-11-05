/*---------------------------------------------------------------------------------

ndsl.h -- Basic template code for NDSlite I/O

  Author: Tek <tek@javerianacali.edu.co>

---------------------------------------------------------------------------------*/

/* console structure used to store the state of a console render context. */
extern PrintConsole  topScreen;
extern PrintConsole  bottomScreen;

/* Minimal NDSlite initialisation */
void DSliteInit ( void );

/* Pause the execution until the next vertical blanking interval
   to synchronise program execution with the display refresh rate
   Then, check if user wants to finish the program */
void SyncCheck ( void );

/* Print system time */
void sysTime ( void );

/* Exit game and return to Menu */
void ExitGame ( void );
