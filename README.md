# PicoSerial v1.0

Ultra lightweight serial support for Arduino, properly supporting incoming interrupts

## SYNOPSIS


```C
  #include <PicoSerial.h>

    #define BAUD 250000
    uint32_t setup() {
      gotBAUD=PicoSerial.begin(BAUD,myIn);                // myIn is your code which gets called when bytes arrive
      PicoSerial.print("The BAUD I really got was:");
      PicoSerial.println(gotBAUD);                        // If you ask for 115200 on an 8mhz CPU, you really get 111111 baud...
    }

    void loop() {
      // do stuff - usually checking your read buffer here...
    }

    void myIn(int c) {                            // this is an ISR - it gets called when new data comes in. buffer and exit this as fast as you can; do not do anything else in here.
      myBuffer[bufferIndex++]=c;
    }

\`\`\`

## FUNCTIONS

    =for markdown
    ```C

      uint32_t begin(BAUD,rxCallBackFunction);            // Sets baud rate, and lets you tell PicoSerial which of your functions you want to call when data is ready. Returns baudrate

    int read()    // Unbuffered read.  returns -1 if no character is available or an available character.

    size_t write(uint8_t b)       // Unbuffered write; param[in] b byte to write. return 1

    boolean canWrite();           // true if we can do a nonblocking write next

## Thanks

This code was adapted from PetitSerial.h, which is a small Serial class in the spirit of Petit FatFs.

## HOW TO INSTALL

### (Method 1)


1. Open a terminal (commandline, bash shell, whatever)
2. Change into your Arduino folder
```bash
   cd /Applications/Arduino.app/Contents/Java/libraries/
   (or)
   cd ~/Arduino/libraries/
```
3. grab and install this code
```bash
   git clone https://github.com/gitcnd/PicoSerial.git
```
4. restart your arduino IDE
5. Choose File => Examples => PicoSerial => PicoSerial_example
6. Hit the "build" button and enjoy!

### (Method 2) - see https://www.arduino.cc/en/Guide/Libraries


1. Download the ZIP of this repo: https://github.com/gitcnd/PicoSerial/archive/master.zip
2. In your IDE, select Sketch -> Include Library -> Add .ZIP Library
3. Choose File => Examples => PicoSerial => PicoSerial_example
4. Hit the "build" button and enjoy!
