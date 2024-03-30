/* Universal Genset Autostart Controller MK1
 * 
 * 
 * 
 */

// Initialize pins
const int RUN_EN = 13; // Start/Run Input
const int RUN_PIN = 12; // Run on IGN SW
const int START = 11; // Start pin on IGN SW
const int FAULT = 10; // Fault/Fail Light
const int POWER = 9; // Contactor close request
const int SHUTDOWN = 8; // Shutdown Input
const int ENGINE = 7; // Engine running input



void setup() {
// initialize builtin LED for heartbeat
 pinMode(LED_BUILTIN, OUTPUT);
// initialize pins
 pinMode(RUN_EN, INPUT);
 pinMode(SHUTDOWN, INPUT);
 pinMode(ENGINE, INPUT);

 pinMode(RUN_PIN, OUTPUT);
 pinMode(START, OUTPUT);
 pinMode(FAULT, OUTPUT);
 pinMode(POWER, OUTPUT);
 

}

void loop() {
  // put your main code here, to run repeatedly:
  heartbeat();
  while (RUN_EN == HIGH, ENGINE == LOW) {
    WU();
    CLOSE();
  }

  while (RUN_EN == HIGH, ENGINE == HIGH){
    RUNNING();
  } 

  while (RUN_EN == LOW, ENGINE == HIGH){  // IF no work, (RUN_EN == LOW && SHUTDOWN == HIGH) for 2 pin solution
    COOL();
  }
  
  while (RUN_EN == LOW){
      SR();
  }
}

// LED heartbeat
void heartbeat(){
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}

// Stopped Ready State
void SR(){
  digitalWrite(RUN_PIN, LOW);
}

// Stopped Alarmed State
void SA(){
  digitalWrite(RUN_PIN, LOW);
  digitalWrite(FAULT, HIGH);
}

// Warmup State
void WU(){
  digitalWrite(RUN_PIN, HIGH); // Run & Prime 
  delay(15000);                 // Wait for prime 15sec
  digitalWrite(START, HIGH); // Start Engine
  delay(3000);
  digitalWrite(START, LOW);
}

void CLOSE(){
  while (RUN_EN == HIGH, ENGINE == LOW){
    delay (500);
  }
  digitalWrite(POWER, HIGH); // Close contator
  delay(1000);
  digitalWrite(POWER, LOW); 
}

// Running State
void RUNNING(){
  digitalWrite(RUN_PIN, HIGH);  //Keep RUN relay engaged
}

// Cooldown State
void COOL(){
  digitalWrite(POWER, HIGH); // Open Contactor
  delay(1000);
  digitalWrite(POWER, LOW);
  delay(300000);            // wait 5min for engine cooldown
  digitalWrite(RUN_PIN, LOW); // Shutdown Engine
}
