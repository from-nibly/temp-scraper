#define MCP9808_I2CADDR_DEFAULT		0X18
#define MCP9808_REG_AMBIENT_TEMP	0x05

class Adafruit_MCP9808 {
 public:
  Adafruit_MCP9808();
  bool begin(unsigned int8_t a = MCP9808_I2CADDR_DEFAULT);
  float readTempF( void );
  float readTempC( void );

  void write16(unsigned int8_t reg, unsigned int16_t val);
  unsigned int16_t read16(unsigned int8_t reg);

 private:
  unsigned int8_t _i2caddr;
};

Adafruit_MCP9808::Adafruit_MCP9808(){
}

bool Adafruit_MCP9808::begin(unsigned int8_t addr) {
  _i2caddr = addr;
  //Wire.begin here

  //if the manuf ID and device ID are incorrect, then return false here

  return true;
}

float Adafruit_MCP9808::readTempC( void ) {
  unsigned int16_t t = read16(MCP9808_REG_AMBIENT_TEMP);
  
  float temp = t & 0x0FFF;
  temp /= 16.0;
  if (t & 0x1000) temp -= 256;

  return temp;
}

void Adafruit_MCP9808::write16(unsigned int8_t reg, unsigned int16_t value) {
  //use wiringPi to write to the thing
}

uint16_t Adafruit_MCP9808::read16(uint8_t reg) {
  uint16_t val;

  //read in value using wiringPi library

  val =  //read in value;
  val <<= 8;
  val |= //read in value again
  return val;
}

Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();

void setup() {
  printf("MCP9808 demo \n");
  
  if (!tempsensor.begin()) {
    printf("Couldn't find MCP9808!\n");
  while(1);
  }
}

void loop() {
  float c = tempsensor.readTempC();
  float f = c * 9.0 / 5.0 + 32;
  printf("temp: %dC || %dF\n");
  delay(250);
}

int main(void) {
  loop();
}
