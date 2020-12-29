// Gestione pulsanti per selezionare il numero

int stato = 0;
int nFaccie = 6;
int pinConferma = 33;
int pinAumenta = 32;

int clockPin = 27; // cavo arancione
int latchPin = 26;  // cavo giallo
int dataPin = 25;  // cavo verde
int input = 0;
byte leds = 0;
String inString = ""; 

void setup(){
    pinMode(pinConferma, INPUT_PULLUP);
    pinMode(pinAumenta, INPUT_PULLUP);

    pinMode(latchPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
  
    Serial.begin(115200);
}

void loop(){
    if(stato == 0){
        if(digitalRead(pinConferma) == LOW){
            while(digitalRead(pinConferma) == LOW){}
            delay(1);
            stato = 1;
        }
        delay(1);
        Serial.println("Pronto");
        caricamento();
    }
    
    else{
        Serial.print("Numero Faccie: ");
        Serial.println(nFaccie);
        cleanByte();
        setNumero(nFaccie);
        if(digitalRead(pinAumenta) == LOW){
            while(digitalRead(pinAumenta) == LOW){}
            if(nFaccie != 9){
                nFaccie++;
            }
            else{
                nFaccie = 1;
            }
            delay(1);
        }
        if(digitalRead(pinConferma) == LOW){
            while(digitalRead(pinConferma) == LOW){}
            stato = 0;
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
}
