#include <MPU6050_tockn.h>
#include<Wire.h>

//giroscopio
MPU6050 mpu6050(Wire);
int AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;


int numberRandom;

void setup(){
  Serial.begin(115200);
  //randomSeed(???);
  //giroscopio
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

}
void loop(){
  mpu6050.update();
  
  AcX=mpu6050.getAccX();  //    
  AcY=mpu6050.getAccY();  //
  AcZ=mpu6050.getAccZ();  //
  //Tmp=mpu6050.getTemp();  //
  GyX=mpu6050.getGyroX();  //
  GyY=mpu6050.getGyroY();  //
  GyZ=mpu6050.getGyroZ();  //

  Serial.print("X: "); Serial.println(mpu6050.getGyroX());
  Serial.print("GyX:"); Serial.println(GyX);
  
  
  //numberRandom = random(10);
  delay(1000);
  
}
