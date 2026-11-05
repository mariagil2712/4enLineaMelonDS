/*---------------------------------------------------------------------------------

  init.c -- Basic template code for NDSlite initialisation and I/O support

  Author: Tek <tek@javerianacali.edu.co>

---------------------------------------------------------------------------------*/

#include <nds.h>
#include <stdio.h>

/* Callback function to be called on key press */
void OnKeyPressed ( int key );

/* User function to be called on A key press */
extern void about ( void );

/* console structure used to store the state of a console render context. */
PrintConsole  topScreen;
PrintConsole  bottomScreen;

/* Minimal NDSlite initialisation */
void DSliteInit ( void )
{
  /* keyboard structure used to describe a keyboard. */
  Keyboard      *kbd;
  /* variable to store keys status and enable using the console */
  int           keys,
                done;
  /*  Set the text video mode on the main screen. */
  videoSetMode ( MODE_0_2D );
  /*  Set the text video mode on the sub screen. */
  videoSetModeSub ( MODE_0_2D );

  /* Map bank A to main screen background memory. */
  vramSetBankA ( VRAM_A_MAIN_BG );
  /* Map bank C to sub screen background memory. */
  vramSetBankC ( VRAM_C_SUB_BG );

  /* Initialise the consoles. */
  consoleInit ( &topScreen, 3, BgType_Text4bpp, BgSize_T_256x256, 31, 0, true, true );
  // consoleInit ( &bottomScreen, 3, BgType_Text4bpp, BgSize_T_256x256, 31, 0, false, true );
  consoleInit ( &bottomScreen, 0, BgType_Text4bpp, BgSize_T_256x256, 22, 3, false, true );

  /* Initialise the keyboard with default options  */
  kbd = keyboardInit ( NULL, 3, BgType_Text4bpp, BgSize_T_256x512, 20, 0, false, true );
  /* Set callback function to be called on key press */
  kbd->OnKeyPressed = OnKeyPressed;
  /* Show keyboard on sub screen */
  keyboardShow ();

  /* Switch the ARM9 to a 'low power' mode
     in order to extend the battery life of the DS */
  swiWaitForVBlank ();

  /* Update the keys registers with current values. */
  done = 0;
  consoleSelect ( &topScreen );
  consoleClear ();
  printf ( "Sistemas de Procesamiento\n" );
  printf ( "\n" );
  printf ( "Universidad Javeriana - Cali\n\n" );
  printf ( "Por Maria Antonia Gil\n\n" );
  printf ( "Presiona START para imprimir el tablero..." );
  while ( !done )
  {
    /* Obtains the current keypad pressed state */
    scanKeys ();
    keys = keysDown ();
    if ( keys & KEY_START )
      done = 1;
    swiWaitForVBlank ();
  }
}

/* Callback function to be called on key press */
void OnKeyPressed ( int key )
{
  if ( key > 0 )
  {
    consoleSelect ( &bottomScreen );
    printf ( "%c", key );
  }
}

/* Return to Menu */
void ExitGame ( void )
{
  consoleSelect ( &bottomScreen );
  consoleClear ();
  consoleSelect ( &topScreen );
  consoleClear ();
  keyboardHide ();
  swiWaitForVBlank ();
  exit ( 0 );
}

/* Pause the execution until the next vertical blanking interval
   to synchronise program execution with the display refresh rate
   Then, check if user wants to finish the program */
void SyncCheck ( void )
{
    /* Switch the ARM9 to a 'low power' mode
       in order to extend the battery life of the DS */
    swiWaitForVBlank ();

    scanKeys();
    int pressed = keysDown();
    if ( pressed & KEY_START )
      ExitGame ();
}
