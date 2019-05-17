// example showing PicoSerial input buffering etc

#include <PicoSerial.h>

#define BAUD 250000	// 8mhz CPU gives you exactly 250000 baud
//#define BAUD 115200 	// 8mhz CPUs closest they can do is 111111

#define BUFFSIZE 100
volatile byte buf[BUFFSIZE];
volatile byte rxptr,rxsize=0; // pointer into our buffer, and sizes of things in it

void setup() {
  for(int i=0;i<BUFFSIZE;i++) { buf[i]=i; } 
  uint32_t realbaud=PicoSerial.begin(BAUD,myIn);// myIn/myOut is your code which gets called when bytes arrive, or when a previous send-byte has complete
  PicoSerial.print(F("Good to go!!  Send me stome stuff now... btw - real baud="));
  PicoSerial.println(realbaud);
  pinMode(13,OUTPUT);
} // setup

byte ledtoggle=0;

volatile byte printfrom,printme,nextprint=0;	// When data is ready, where does it start, and how long is it?

void loop() {
  digitalWrite(13, (ledtoggle++&1)); 		// Blink the LED
  delay(1000);	// Deliberate example to show impending data loss that would occur if not using PicoSerial

  if(printme) { // Something arrived!
    if(printme<255) {
      while(printme--) {			// Echo it back out
	PicoSerial.print((char)buf[printfrom++]);
	if(printfrom>=BUFFSIZE)printfrom=0;
      }
    } else {
      PicoSerial.println("Buffer overflowed :-)"); 
      rxsize=0;
    }
    printme=0;
  } // printme

} // loop


void myIn(int c) {				// this is an ISR - it gets called when new data comes in. buffer and exit this as fast as you can; do not do anything else in here.
  if(++rxsize<=BUFFSIZE) {
    buf[rxptr++]=c;				// Store the char
    if(rxptr>=BUFFSIZE)rxptr=0;			// use a circular buffer
    if(c==10){					// newline
      printme=rxsize;				// tell caller that we have assembled a packet into our buffer now
      printfrom=nextprint;			// and where it begins from
      rxsize=0; nextprint=rxptr;		// clear pointers ready to get the next packet now
    }
  } else {
    printme=255;				// Handle buffer overflow 
  }
  // Do not do anything else in here - this is an interrupt service routine only.
}
