//scketch Schift Register 74HC595 con ESP32

int clockPin = 27; // cavo arancione STCP
int latchPin = 26;  // cavo giallo SHCP
int dataPin = 25;  // cavo verde DS
int input = 0;
byte leds = 0;
String inString = ""; 

int digits [10][8]{
  {0,1,1,1,1,0,1,1}, // digit 0
  {0,1,1,0,0,0,0,0}, // digit 1
  {0,1,0,1,1,1,0,1}, // digit 2
  {0,1,1,1,0,1,0,1}, // digit 3
  {0,1,1,0,0,1,1,0}, // digit 4
  {0,0,1,1,0,1,1,1}, // digit 5
  {0,0,1,1,1,1,1,1}, // digit 6
  {0,1,1,0,0,0,0,1}, // digit 7
  {0,1,1,1,1,1,1,1}, // digit 8
  {0,1,1,1,0,1,1,1}  // digit 9
};

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  //Inserimento valori da monitor seriale
  // while (Serial.available() > 0) {
  //   int inChar = Serial.read();
  //   if (isDigit(inChar)) {
  //     // convert the incoming byte to a char and add it to the string:
  //     inString += (char)inChar;
  //   }
  //   // if you get a newline, print the string, then the string's value:
  //   if (inChar == '\n') {
  //     Serial.println(inString.toInt());
  //     displayDigit(inString.toInt());
  //     // clear the string for new input:
  //     inString = "";
  //   }
  // }


  //caricamento di 3 secondi (il tempo che ci impiega il giroscopio per calibrarsi)
  for(int i = 0; i<5; i++){
    caricamento();
  }
  displayDigit(random(0, 9));
  delay(1000);
  cleanByte();
  delay(1000);
}

void displayDigit (int digit) {
  cleanByte();
  for (int i=7; i>=0; i--){
    if (digits[digit][i] == 1) bitSet(leds, i);
  }
  updateShiftRegister();
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
//medoto CARICAMENTO
void caricamento(){
  for(int i = 0; i<7; i++){
    cleanByte();
    if(i == 0){
      bitSet(leds, 7);
      updateShiftRegister(); 
      delay(100); 
    }
    if(i==5){}
    else{
      bitSet(leds, i);
      updateShiftRegister();
      delay(100);
    }
  }
  cleanByte();
}
