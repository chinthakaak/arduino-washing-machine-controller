byte torque_motor_pin = 8 ;// pink - torque motor
byte main_motor_left_pin = 10 ;// red - motor left
byte main_motor_right_pin = 9 ;// yellow - motor right
byte water_valve_pin = 11; // orange - water valve
byte buzzer_pin = 12;
byte start_button_pin = 13;
byte default_wash_count = 2;

unsigned long WATER_DELAY = 180000L;
unsigned long WASH_DELAY = 5000L;
unsigned long RINSE_DELAY = 90000L;
unsigned long SPIN_DELAY =  240000L;
unsigned long SPIN_START1_DELAY=7000L;
unsigned long SPIN_START2_DELAY=5000L;
unsigned long SPIN_STOP_DELAY = 60000L;
unsigned long DELAY = 3000L;

void setup() {
  pinMode(torque_motor_pin,OUTPUT); 
  pinMode(main_motor_right_pin,OUTPUT); 
  pinMode(main_motor_left_pin,OUTPUT); 
  pinMode(water_valve_pin,OUTPUT); 
  pinMode(buzzer_pin,OUTPUT); 
  
  pinMode(start_button_pin, INPUT);
}

void loop() {
  byte wash_count = default_wash_count;
  if (digitalRead(start_button_pin) == HIGH) {
    beep(wash_count);
    while(digitalRead(start_button_pin) == HIGH) {
      beep(1);
      wash_count++;
    }
    
    for (int i = 0; i< wash_count; i++) {
      stopAll();
      water();
      wash(8);
      rinse();      
    }
    spin();
    beep(10);
  }
}

void water(){
  digitalWrite(water_valve_pin, HIGH);
  delay(WATER_DELAY); 
  digitalWrite(water_valve_pin,LOW);
}
  
void wash(int cycles) {
  for (int i = 0; i<cycles; i++) {
    delay(DELAY);
    digitalWrite(main_motor_left_pin,HIGH);    
    delay(WASH_DELAY);
    digitalWrite(main_motor_left_pin,LOW);    
    delay(DELAY);
    digitalWrite(main_motor_right_pin,HIGH);    
    delay(WASH_DELAY);
    digitalWrite(main_motor_right_pin,LOW);    
  }
}

  void rinse() {
    delay(DELAY);
    digitalWrite(torque_motor_pin,HIGH);
    delay(RINSE_DELAY);
    digitalWrite(torque_motor_pin,LOW);
  }

  void spin() {
    digitalWrite(torque_motor_pin,HIGH);
    digitalWrite(main_motor_left_pin,HIGH);    
    delay(SPIN_START1_DELAY);
    digitalWrite(main_motor_left_pin,LOW);    

    delay(SPIN_START2_DELAY);
    digitalWrite(torque_motor_pin,HIGH);
    digitalWrite(main_motor_left_pin,HIGH);    
    delay(SPIN_DELAY);
        
    digitalWrite(main_motor_left_pin,LOW);    
    delay(SPIN_STOP_DELAY);
    digitalWrite(torque_motor_pin,LOW);
  }
  
void stopAll() {
  digitalWrite(torque_motor_pin,LOW);
  digitalWrite(main_motor_left_pin,LOW);
  digitalWrite(main_motor_right_pin,LOW);
  digitalWrite(water_valve_pin,LOW);
}
void beep(int times) {
  for (int i = 0; i < times; i++){
    tone(buzzer_pin, 2000,500);
    delay(750);
  }
}
