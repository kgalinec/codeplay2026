#include <math.h>

#define I2C_SDA 8
#define I2C_SCL 9

Soldered_LSM6DS3 lsm6ds3;

int16_t global_tilt_x = 0;
int16_t global_tilt_y = 0;
int16_t global_tilt_z = 0;

void akcelerometar_setup() {
  Wire.setPins(I2C_SDA, I2C_SCL);
  Wire.begin();

  if (lsm6ds3.begin() != 0) {
    while(1) delay(10);
  }
  
  lsm6ds3.enableAccelerator();
}

void akcelerometar_loop() {
  int32_t acc[3];
  lsm6ds3.getAcceleratorAxes(acc);

  float kut_x = atan2(acc[0], acc[2]) * 57.295;
  float kut_y = atan2(acc[1], acc[2]) * 57.295;
  float kut_z = atan2(sqrt(acc[0]*acc[0] + acc[1]*acc[1]), acc[2]) * 57.295;

  int limit_stupnjeva = 35; 

  global_tilt_x = map(constrain((int)kut_x, -limit_stupnjeva, limit_stupnjeva), -limit_stupnjeva, limit_stupnjeva, -100, 100);
  global_tilt_y = map(constrain((int)kut_y, -limit_stupnjeva, limit_stupnjeva), -limit_stupnjeva, limit_stupnjeva, -100, 100);
  global_tilt_z = map(constrain((int)kut_z, -limit_stupnjeva, limit_stupnjeva), -limit_stupnjeva, limit_stupnjeva, -100, 100);
}
