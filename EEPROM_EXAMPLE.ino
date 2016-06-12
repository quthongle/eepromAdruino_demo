/*-------------------------------------------------------------------------
read and write EEPROM basic example.
This example will read a char from terminal and write it to EEPROM,
it also allows user to read EEPROM accroding to address.
----------------------------------------------------------------------------*/

#include <EEPROM.h>

// start reading from the first byte (address 0) of the EEPROM
int addressWrite = 0;
int addressRead = 0;
byte value;

void setup() {
  // initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
   ;
   }
  pinMode(13, OUTPUT);
  }

/*----------------------------------------------------------------------------
readEEPROM
----------------------------------------------------------------------------*/
void readEEPROM() {
  Serial.println("EEPROM READ");
  // read a byte from the current address of the EEPROM
  value = EEPROM.read(addressRead);

  Serial.print(value);
  Serial.print("\t @ ");
  Serial.print(addressRead);
  Serial.println();

  /***
  Advance to the next address, when at the end restart at the beginning.

  Larger AVR processors have larger EEPROM sizes, E.g:
  - Arduno Duemilanove: 512b EEPROM storage.
  - Arduino Uno:        1kb EEPROM storage.
  - Arduino Mega:       4kb EEPROM storage.

  Rather than hard-coding the length, you should use the pre-provided length 
  function.
  This will make your code portable to all AVR processors.
   ***/
  addressRead = addressRead + 1;
  if (addressRead == EEPROM.length()) {
   addressRead = 0;
   }

  blink(value);
  delay(500);
  }


/*----------------------------------------------------------------------------
writeEEPROM
----------------------------------------------------------------------------*/
void writeEEPROM() {
/***
  Each byte of the EEPROM can only hold a value from 0 to 255.
 ***/

  /***
  Write the value to the appropriate byte of the EEPROM.
  these values will remain there when the board is
  turned off.
   ***/
  byte writeValue;
  Serial.println("EEPROM WRITE");
  // get the next character from the serial port
  Serial.print( "Value to be written?" );
  while( !Serial.available() )
  ;
  writeValue = Serial.read();
  EEPROM.write(addressWrite, writeValue);
  Serial.println();
  Serial.println("WRITE");
  Serial.print( "-----------EEPROM has been written receiveValue :" );
  Serial.write(writeValue);
    Serial.print(" = (char) ");
  Serial.print(writeValue);
  Serial.print( " @ " );
  Serial.print(addressWrite);


  /***
  Advance to the next address, when at the end restart at the beginning.

  Larger AVR processors have larger EEPROM sizes, E.g:
  - Arduno Duemilanove: 512b EEPROM storage.
  - Arduino Uno:        1kb EEPROM storage.
  - Arduino Mega:       4kb EEPROM storage.

  Rather than hard-coding the length, you should use the pre-provided length 
  function.
  This will make your code portable to all AVR processors.
   ***/
  addressWrite = addressWrite + 1;
  if (addressWrite == EEPROM.length()) {
   addressWrite = 0;
   }
  delay(500);
  }

/*----------------------------------------------------------------------------
blink 10 times, each delay 10xval
----------------------------------------------------------------------------*/
void blink(byte time) {
  Serial.println(".BLINK FUNCTION");
  for(int i = 0;i<10;i++){
   Serial.print( "-----------loop :" );
   Serial.println(i);

   Serial.println (time);
   digitalWrite(13, HIGH);
   delay(time*10);
   digitalWrite(13, LOW);
   delay(time*10);
   }
  }

/*----------------------------------------------------------------------------
loop
----------------------------------------------------------------------------*/
void loop()
{
  boolean isValidInput;
  // draw a menu on the serial port
  Serial.println( "-----------------------------" );
  Serial.println( "MENU:" );
  Serial.println( "1) Read a value" );
  Serial.println( "2) Wire a value" );
  Serial.println( "-----------------------------" );

  do {
   byte c;
   // get the next character from the serial port
   Serial.print( "?" );
   while( !Serial.available() )
   ;                                                         // LOOP...
   c = Serial.read();
   // execute the menu option based on the character recieved
   switch( c )
   {
    case '1':
    Serial.println( "1) Read a value" );
    readEEPROM();
     break;

    case '2':
    Serial.println( "2) Wire a value" );
    writeEEPROM();
     break;     

    default:
    // wrong character! display the menu again!
    isValidInput = false;
     break;
  }
   } while( isValidInput == true );

// repeat the main loop and redraw the menu...

  }
