#include <MPU6050_tockn.h>
#include <Wire.h>

// Giroscopio
MPU6050 mpu6050(Wire);
double GyX, GyY, GyZ;

// Display
int clockPin = 27; // cavo arancione STCP
int latchPin = 26; // cavo giallo SHCP
int dataPin = 25;  // cavo verde DS
byte leds = 0;

// Stati
enum State { IDLE, MOVING, STOPPED }; // Stati del sistema
State currentState = IDLE;           // Stato iniziale

int currentDigit = -1;                // Numero attualmente visualizzato
unsigned long lastMotionTime = 0;     // Timer per il movimento
const unsigned long timeoutDuration = 10000; // 10 secondi di inattività

// Matrice per i numeri sul display
int digits[10][8] = {
    {0, 1, 1, 1, 1, 0, 1, 1}, // digit 0
    {0, 1, 1, 0, 0, 0, 0, 0}, // digit 1
    {0, 1, 0, 1, 1, 1, 0, 1}, // digit 2
    {0, 1, 1, 1, 0, 1, 0, 1}, // digit 3
    {0, 1, 1, 0, 0, 1, 1, 0}, // digit 4
    {0, 0, 1, 1, 0, 1, 1, 1}, // digit 5
    {0, 0, 1, 1, 1, 1, 1, 1}, // digit 6
    {0, 1, 1, 0, 0, 0, 0, 1}, // digit 7
    {0, 1, 1, 1, 1, 1, 1, 1}, // digit 8
    {0, 1, 1, 1, 0, 1, 1, 1}  // digit 9
};

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));

  // Giroscopio
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  // Display
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
}

void loop() {
  mpu6050.update();

  // Lettura dei valori del giroscopio
  GyX = mpu6050.getGyroX();
  GyY = mpu6050.getGyroY();
  GyZ = mpu6050.getGyroZ();

  // Calcola il movimento totale
  float motion = abs(GyX) + abs(GyY) + abs(GyZ);

  // Gestione degli stati
  switch (currentState) {
    case IDLE:
      blinkAllLeds(); // Animazione iniziale
      if (motion > 200) {
        currentState = MOVING; // Passa allo stato di movimento
        lastMotionTime = millis(); // Registra il tempo dell'ultimo movimento
        caricamento();             // Esegui l'animazione di caricamento
      }
      break;

    case MOVING:
      if (motion > 200) {
        // Movimento continuo, aggiorna il timer
        lastMotionTime = millis();
        caricamento();
      } else if (motion < 1) {
        // Movimento fermato, passa allo stato STOPPED
        currentState = STOPPED;
        lastMotionTime = millis(); // Aggiorna il tempo dell'ultimo stato
        int randomDigit = random(0, 10); // Genera il numero casuale
        currentDigit = randomDigit;
        displayDigit(randomDigit);
      }
      break;

    case STOPPED:
      if (motion > 300) {
        // Rilevato nuovo movimento, passa a MOVING
        currentState = MOVING;
        lastMotionTime = millis();
        caricamento();
      } else if (millis() - lastMotionTime > timeoutDuration) {
        // Se sono passati 10 secondi senza movimento, torna allo stato IDLE
        currentState = IDLE;
        currentDigit = -1; // Resetta il numero visualizzato
      } else if (currentDigit != -1) {
        // Mantieni il numero visualizzato
        displayDigit(currentDigit);
      }
      break;
  }
}

void displayDigit(int digit) {
  cleanByte();
  for (int i = 7; i >= 0; i--) {
    if (digits[digit][i] == 1) bitSet(leds, i);
  }
  updateShiftRegister();
}

void updateShiftRegister() {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, leds);
  digitalWrite(latchPin, HIGH);
}

void cleanByte() {
  leds = 0;
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, leds);
  digitalWrite(latchPin, HIGH);
}

void caricamento() {
  for (int i = 0; i < 7; i++) {
    cleanByte();
    if (i == 0) {
      bitSet(leds, 7);
      updateShiftRegister();
      delay(100);
    }
    if (i != 5) {
      bitSet(leds, i);
      updateShiftRegister();
      delay(100);
    }
  }
  cleanByte();
}

void blinkAllLeds() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 8; j++) {
      bitSet(leds, j);
    }
    updateShiftRegister();
    delay(300);
    cleanByte();
    delay(300);
  }
}
