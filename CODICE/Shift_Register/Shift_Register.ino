//scketch Schift Register 74HC595 con ESP32

int clockPin = 27; // cavo arancione
int latchPin = 26;  // cavo giallo
int dataPin = 25;  // cavo verde
int input = 0;
byte leds = 0;
String inString = ""; 

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  while (Serial.available() > 0) {
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char and add it to the string:
      inString += (char)inChar;
    }
    // if you get a newline, print the string, then the string's value:
    if (inChar == '\n') {
      Serial.println(inString.toInt());
      setNumero(inString.toInt());
      // clear the string for new input:
      inString = "";
    }
  }
}

//Metodo per stampare sul display un numero tra 0 e 9
void setNumero(int numero){
  switch(numero){
    case 0:
      cleanByte();
      bitSet(leds, 7);
      bitSet(leds, 1);
      bitSet(leds, 2);
      bitSet(leds, 3);
      bitSet(leds, 4);
      bitSet(leds, 6);
      updateShiftRegister();
      break;
    case 1:
      cleanByte();
      bitSet(leds, 1);
      bitSet(leds, 2);
      updateShiftRegister();
      break;
    case 2:
      cleanByte();
      bitSet(leds, 7);
      bitSet(leds, 1);
      bitSet(leds, 5);
      bitSet(leds, 4);
      bitSet(leds, 3);
      updateShiftRegister();
      break;
    case 3:
      cleanByte();
      bitSet(leds, 7);
      bitSet(leds, 1);
      bitSet(leds, 2);
      bitSet(leds, 3);
      bitSet(leds, 5);
      updateShiftRegister();
      break;
    case 4:
      cleanByte();
      bitSet(leds, 5);
      bitSet(leds, 6);
      bitSet(leds, 1);
      bitSet(leds, 2);
      updateShiftRegister();
      break;
    case 5:
      cleanByte();
      bitSet(leds, 7);
      bitSet(leds, 5);
      bitSet(leds, 6);
      bitSet(leds, 2);
      bitSet(leds, 3);
      updateShiftRegister();
      break;
    case 6:
      cleanByte();
      bitSet(leds, 7);
      bitSet(leds, 5);
      bitSet(leds, 6);
      bitSet(leds, 2);
      bitSet(leds, 4);
      bitSet(leds, 3);
      updateShiftRegister();
      break;
    case 7:
      cleanByte();
      bitSet(leds, 7);
      bitSet(leds, 1);
      bitSet(leds, 2);
      updateShiftRegister();
      break;
    case 8:
      cleanByte();
      bitSet(leds, 7);
      bitSet(leds, 1);
      bitSet(leds, 2);
      bitSet(leds, 3);
      bitSet(leds, 4);
      bitSet(leds, 5);
      bitSet(leds, 6);
      updateShiftRegister();
      break;
    case 9:
      cleanByte();
      bitSet(leds, 7);
      bitSet(leds, 1);
      bitSet(leds, 2);
      bitSet(leds, 3);
      bitSet(leds, 6);
      bitSet(leds, 5);
      updateShiftRegister();
      break;
  }
}


void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}
void cleanByte(){
   leds = 0;
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}
