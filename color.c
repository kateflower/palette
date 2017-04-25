#include <stdlib.h>
#include <6502.h>
#include <lynx.h>
#include <tgi.h>
// enable Mikeys interrupt response
//#define CLI asm("\tcli")

// These header files are related to the processor family, the Lynx and the TGI libraries.


// The code will first clear the screen, display a header, then print the hex values twice: once against 
// a black background and another time against a white background.

//  this array will contain a string “tgi” that indicates that the loading of the driver was successful.
extern char lynxtgi[]; 




void initialize()
{
	// driver for the Tiny Graphics Interface (TGI)
	// allows for 2D graphics primitives like drawing and text 
  	// Lynx file is called lynx-160-102-16.tgi and is part of the Lynx specific CC65 files
	// function call to tgi_install will install the Lynx specific TGI driver
	// Lynx does not have the ability to load a driver dynamically it needs to be linked statically when the game is built.   
	tgi_install(&lynxtgi);

	// performs the initialization of the loaded drivers of which the TGI graphics driver is just one
	// There are two additional drivers (joystick and comlynx) that you can load as well. 
  	tgi_init();

	// represents the CLI assembly instruction for the 65SC02 processor
	// allows you to clear the Interrupt Disable flag of the processor,   
  	CLI();
	
  	while (tgi_busy())  {  };
 
  	tgi_setpalette(tgi_getdefpalette());
  	tgi_setcolor(COLOR_WHITE);
  	tgi_setbgcolor(COLOR_BLACK);
  	tgi_clear();
}

// The code will first clear the screen, display a header, 
// then print the hex values twice: once against a black background and another 
// time against a white background.
void show_palette(const char* header)
{
  char index = 0;
  char text[5];
 
  tgi_clear();
	
  tgi_setbgcolor(COLOR_BLACK);
  tgi_setcolor(COLOR_WHITE);
  tgi_outtextxy(10, 0, header);
 
  tgi_gotoxy(10, 10);
  for (index = 0; index < 16; index++)
  {
    itoa(index, text, 16);
    tgi_setcolor(index);
    tgi_outtext(text);
  }
 
  tgi_setbgcolor(COLOR_WHITE);
  tgi_gotoxy(10, 20);
  for (index = 0; index < 16; index++)
  {
    itoa(index, text, 16);
    tgi_setcolor(index);
    tgi_outtext(text);
  }
 
  tgi_updatedisplay();
  while (tgi_busy());
}



// The entry point is the main function
void main(void)  {	
  	initialize();
	  
	// An infinite loop where we remain forever  
  while (1)
  {
    tgi_setpalette(tgi_getdefpalette());
    // The call to show_palette is made from the main loop.
    show_palette("Default palette");
  };
}