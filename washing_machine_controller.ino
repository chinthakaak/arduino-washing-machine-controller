#include <Wire.h>

#define SLAVE_ADDR 0x20

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  Serial.println("\nStart I2C");

  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(0x00); //selects the IODIRA register
  Wire.write(0x00); //this sets all port A pins to outputs
  Wire.endTransmission(); //stops talking to device
}

byte RL1 = 129;
byte RL2 = 65;
byte RL3 = 33;
byte RL4 = 17;
unsigned long WATER_DELAY = 180000L;
unsigned long WASH_DELAY = 5000L;
unsigned long RINSE_DELAY = 90000L;
unsigned long SPIN_DELAY =  120000L;
unsigned long SPIN_START1_DELAY=7000L;
unsigned long SPIN_START2_DELAY=5000L;
unsigned long SPIN_STOP_DELAY = 60000L;
unsigned long DELAY = 3000L;
void loop() {
  stopAll();
  water();
  wash(5);
  rinse();
  water();
  wash(5);
  rinse();
  stopAll();
  spin();
  stopAll();
  exit(0);
}
  void water(){
      delay(WASH_DELAY); 
      Wire.beginTransmission(SLAVE_ADDR); //starts talking to slave device
      Wire.write(0x09); //selects the GPIO pins
      Wire.write(RL4); // turns on pins 0 and 1 of GPIOA
      Wire.endTransmission(); //ends communication with the device   
      delay(WATER_DELAY); 
  }
  
void wash(int cycles) {
  for (int i = 0; i<cycles; i++) {
    delay(DELAY);
    Wire.beginTransmission(SLAVE_ADDR); //starts talking to slave device
    Wire.write(0x09); //selects the GPIO pins
    Wire.write(RL1); // turns on pins 0 and 1 of GPIOA
    Wire.endTransmission(); //ends communication with the device
    
    delay(WASH_DELAY);
    stopAll();
    delay(DELAY);

    Wire.beginTransmission(SLAVE_ADDR); //starts talking to slave device
    Wire.write(0x09); //selects the GPIO pins
    Wire.write(RL2); // turns on pins 0 and 1 of GPIOA
    Wire.endTransmission(); //ends communication with the device
    
    delay(WASH_DELAY);
    stopAll();
  }
}

  void rinse() {
    delay(DELAY);
    Wire.beginTransmission(SLAVE_ADDR); //starts talking to slave device
    Wire.write(0x09); //selects the GPIO pins
    Wire.write(RL3); // turns on pins 0 and 1 of GPIOA
    Wire.endTransmission(); //ends communication with the device    
    delay(RINSE_DELAY); 
  }

  void spin() {
    Wire.beginTransmission(SLAVE_ADDR); //starts talking to slave device
    Wire.write(0x09); //selects the GPIO pins
    Wire.write(RL2+RL3); // turns on pins 0 and 1 of GPIOA
    Wire.endTransmission(); //ends communication with the device  
    delay(SPIN_START1_DELAY);

    Wire.beginTransmission(SLAVE_ADDR); //starts talking to slave device
    Wire.write(0x09); //selects the GPIO pins
    Wire.write(RL3); // turns on pins 0 and 1 of GPIOA
    Wire.endTransmission(); //ends communication with the device  
    delay(SPIN_START2_DELAY);

    Wire.beginTransmission(SLAVE_ADDR); //starts talking to slave device
    Wire.write(0x09); //selects the GPIO pins
    Wire.write(RL2+RL3); // turns on pins 0 and 1 of GPIOA
    Wire.endTransmission(); //ends communication with the device  
    delay(SPIN_DELAY);
    
//    stopAll();
    
    Wire.beginTransmission(SLAVE_ADDR); //starts talking to slave device
    Wire.write(0x09); //selects the GPIO pins
    Wire.write(RL3); // turns on pins 0 and 1 of GPIOA
    Wire.endTransmission(); //ends communication with the device  
    delay(SPIN_STOP_DELAY);
    
  }

  void stopAll() {
    Wire.beginTransmission(SLAVE_ADDR); //starts talking to slave device
    Wire.write(0x09); //selects the GPIO pins
    Wire.write(0); // turns on pins 0 and 1 of GPIOA
    Wire.endTransmission(); //ends communication with the device 
  }
