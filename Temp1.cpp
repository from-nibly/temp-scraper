#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define MCP9808_I2CADDR			0x18
#define MCP9808_REG_AMBIENT_TEMP	0x05

signed int fd;

class Adafruit_MCP9808 {
 public:
  Adafruit_MCP9808();
  bool begin();
  float readTempC();
};

Adafruit_MCP9808::Adafruit_MCP9808(){
}

bool Adafruit_MCP9808::begin() {
  fd = wiringPiI2CSetup(MCP9808_I2CADDR);
  if (fd < 0) return false; 
  return true;
}

float Adafruit_MCP9808::readTempC() {
  float Temperature;
  int lower;
  int upper;

  lower = wiringPiI2CReadReg16(fd, MCP9808_REG_AMBIENT_TEMP);
  upper = lower >> 8;
  lower = lower & 0x001F; 
  //swaparoo
  Temperature = (lower << 8) + upper;
  Temperature /= 16.0;

  if (lower & 0x1000) Temperature -= 256;

  return Temperature;
}

Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();

int setup() {
  printf("MCP9808 demo....\n");
  if (!tempsensor.begin()) {
    printf("Could not find MCP9808!!!\n");
    while(1);
    return 0;
  }

  //read in registers
  int val = 0;
  for(int i = 0; i < 9; i++) {
    val = wiringPiI2CReadReg16(fd,i);
    printf("Reg %d : %.2X\n", i, val);
    val = 0;
  }

  if (wiringPiI2CReadReg16(fd, 6) != 0x5400) return 0;
  if (wiringPiI2CReadReg16(fd, 7) != 0x04)return 0;

  return 1; 
}

void loop() {
  float c = tempsensor.readTempC();
  float f = c * (9.0 / 5.0) + 32;
  printf("%.2fC || %.2fF\n", c, f);
  delay(15000);
}

int main(void) {
  if (setup() != 1) {
        printf("Could not start application.\n");
	exit(0);
  }
  while (1) {
    loop();
  }
  return 1;
}
