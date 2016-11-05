/* hallo.c 
   turns franzboard LEDs sequentially on and off
*/ 
#include <stdio.h>
#include <wiringPi.h>

#define	LED1 18	
#define	LED2 23
#define	LED3 24 	
#define	LED4 25 	

int main (void)
{
  int leds[4] = {LED1, LED2, LED3, LED4};
  int i;
  printf ("Raspberry Pi blink\n") ;

  wiringPiSetupGpio() ;
  for (i = 0; i < 4; i++)
  	pinMode (leds[i], OUTPUT);

  for (i = 0;; i++)
  {
    if (i == 4)
	i = 0;
    digitalWrite (leds[i], HIGH);
    delay (500) ;		// mS
    digitalWrite (leds[i], LOW);
    delay (500) ;
  }
  return 0 ;
}
