#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
int L1 = A2;
int L2 = 2;
int L3 = 3;
int Mpu;
unsigned long timePrev;   //지난시간
  
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

  bool checkTimePrev = false;
  while (a.acceleration.y <= -8.00 ){
    if (checkTimePrev == false) {
      timePrev = millis();
      checkTimePrev = true;
    }
    unsigned long timeCurr = millis();    //현재 시간을 지정
    if (timeCurr - timePrev > 5000){       //10초 동안 기울기 y<-8.00일 때
      Serial.println("불 껴짐");
      Serial.print("x: ");
      Serial.print(a.acceleration.x);
      Serial.print("\ty: ");
      Serial.print(a.acceleration.y);
      Serial.print("\tz: ");
      Serial.print(a.acceleration.z);
      Serial.print("\n");
      digitalWrite(L3,HIGH);
      digitalWrite(L2,HIGH);
      digitalWrite(L1,HIGH);
//  }
    }
    else {
      Serial.println("불 안 켜짐");
      Serial.print("x: ");
      Serial.print(a.acceleration.x);
      Serial.print("\ty: ");
      Serial.print(a.acceleration.y);
      Serial.print("\tz: ");
      Serial.print(a.acceleration.z);
      Serial.print("\n");
      digitalWrite(L3,LOW);
      digitalWrite(L2,LOW);
      digitalWrite(L1,LOW);
    }
    delay(500);
  }
}

  
  
