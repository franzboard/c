/*  Pushing one of the buttons makes LEDs display a
    random binary pattern 
    Edgar Neukirchner 2016
*/
   
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <errno.h>
#include <string.h>
#include <time.h>

#define LED1 18    
#define LED2 23
#define LED3 24     
#define LED4 25     

#define BUTTON1 22
#define BUTTON2 27
#define BUTTON3 17

#define TBOUNCE 1000

unsigned int* int2hex(unsigned int x);
void writeDisplay(unsigned int val);
void clearDisplay(void);
void generate_pattern(void);
unsigned int* int2hex(unsigned int x);
void myInterrupt (void); 

unsigned long last_ir = 0;

void myInterrupt (void) 
{
        unsigned long ir_time = millis();
        if (ir_time - last_ir > TBOUNCE) {
                generate_pattern();
        }
        last_ir = ir_time;

}

void generate_pattern(void)
{
    int t = 100;
    while(t > 0) {
        writeDisplay(rand());
        delay(t);
        t -= 10;
    }
}

unsigned int* int2hex(unsigned int x)
{
    static unsigned int buf[5];
    int i;

    for(i = 0; i < 4; i++) {
        buf[i] = (x & 0x01);         
        x >>= 1;
    }
    return buf;
}

void writeDisplay(unsigned int val)
{
    unsigned int* hex = int2hex(val % 15 + 1);
    int leds[4] = {LED1, LED2, LED3, LED4};
    int i;

    for (i = 0; i < 4; i++) {
        pinMode (leds[i], OUTPUT);
        if (hex[i] == 1)
            digitalWrite(leds[i], HIGH);
        else
            digitalWrite(leds[i], LOW);
    }
}
    
void clearDisplay(void)
{
    int leds[4] = {LED1, LED2, LED3, LED4};
    int i;

    for (i = 0; i < 4; i++) {
        pinMode (leds[i], OUTPUT);
        digitalWrite(leds[i], LOW);
    }
}

int main(void)
{
    wiringPiSetupGpio() ;
    wiringPiISR (BUTTON1, INT_EDGE_FALLING, &myInterrupt);
    wiringPiISR (BUTTON2, INT_EDGE_FALLING, &myInterrupt);
    wiringPiISR (BUTTON3, INT_EDGE_FALLING, &myInterrupt);
    srand(time(NULL));
    clearDisplay();
    for(;;);
    return 0;
}



