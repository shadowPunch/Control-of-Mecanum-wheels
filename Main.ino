#include <Wire.h>

const int MPU_addr = 0x68; 

float accel_x_g, accel_y_g, accel_z_g;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B); 
  Wire.write(0);   
  Wire.endTransmission(true);
}

void loop() {
  // Read accelerometer data
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B); 
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true); 
  int16_t accel_x_raw = Wire.read() << 8 | Wire.read();
  int16_t accel_y_raw = Wire.read() << 8 | Wire.read(); 
  int16_t accel_z_raw = Wire.read() << 8 | Wire.read();

  // Convert accelerometer data to acceleration in g
  const float sensitivity = 16384.0; 
  // Sensitivity scale factor for ±2g full scale
  accel_x_g = accel_x_raw / sensitivity;
  accel_y_g = accel_y_raw / sensitivity;
  accel_z_g = accel_z_raw / sensitivity;

  Serial.print("Accel X (g): "); Serial.print(accel_x_g);
  Serial.print(", Y (g): "); Serial.print(accel_y_g);
  Serial.print(", Z (g): "); Serial.println(accel_z_g);

  delay(1000);
}