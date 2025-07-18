/*
 *
 * Copyright (c) [2020] by InvenSense, Inc.
 * 
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */
 
#include "ICM45686.h"

// Instantiate an ICM456XX with LSB address set to 0
ICM456xx IMU(Wire,0);

void setup() {
  int ret;
  Serial.begin(115200);
  while(!Serial) {}

  // Initializing the ICM456XX
  ret = IMU.begin();
  if (ret != 0) {
    Serial.print("ICM456xx initialization failed: ");
    Serial.println(ret);
    while(1);
  }
  // Accel ODR = 100 Hz and Full Scale Range = 16G
  IMU.startAccel(100,16);
  // Gyro ODR = 100 Hz and Full Scale Range = 2000 dps
  IMU.startGyro(100,2000);
  // Wait IMU to start
  delay(100);
}

void loop() {

  inv_imu_sensor_data_t imu_data;

  // Read registers
  IMU.getDataFromRegisters(imu_data);

  // Format data for Serial Plotter
  Serial.print("AccelX:");
  Serial.println(imu_data.accel_data[0]);
  Serial.print("AccelY:");
  Serial.println(imu_data.accel_data[1]);
  Serial.print("AccelZ:");
  Serial.println(imu_data.accel_data[2]);
  Serial.print("GyroX:");
  Serial.println(imu_data.gyro_data[0]);
  Serial.print("GyroY:");
  Serial.println(imu_data.gyro_data[1]);
  Serial.print("GyroZ:");
  Serial.println(imu_data.gyro_data[2]);
  Serial.print("Temperature:");
  Serial.println((imu_data.temp_data/128.0)+25.0);

  delay(1000);
}
