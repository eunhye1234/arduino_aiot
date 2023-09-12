#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
int L1 = A2;
int L2 = 2;
int L3 = 3;
int Mpu;

Adafruit_MPU6050 mpu;

void setup(void) {
  Serial.begin(115200);
  pinMode(L1, OUTPUT);
  if (!mpu.begin()){
    Serial.println("Failed to find MPU6050 chip");
    while(1){
      digitalWrite(L1,HIGH);
      delay(500);
      digitalWrite(L1,LOW);
      delay(500);
    }
  }
  Serial.println("MPU6050 Found!");

  // set accelerometer range to +-8G
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

  // set gyro range to +- 500 deg/s
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);

  // set filter bandwidth to 21 Hz
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(100);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);

}

void loop() {
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  Serial.print("x: ");
  Serial.print(a.acceleration.x);
  Serial.print("\ty: ");
  Serial.print(a.acceleration.y);
  Serial.print("\tz: ");
  Serial.print(a.acceleration.z);

  if(a.acceleration.y<=0.00&&a.acceleration.y>-7.00 ){
    Serial.println("불 껴짐");
    digitalWrite(L3,HIGH);
    digitalWrite(L2,HIGH);
    digitalWrite(L1,HIGH);
  }
  else {
    Serial.println("불 꺼짐");
    digitalWrite(L3,LOW);
    digitalWrite(L2,LOW);
    digitalWrite(L1,LOW);
  }
 delay(1000);
}


  
  
