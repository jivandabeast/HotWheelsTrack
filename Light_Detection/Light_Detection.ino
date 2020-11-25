/* 
 *  Created by Jivan RamjiSingh
 *  
 *  Testing the viability of a photoresistor to detect a hot wheels car moving down the track
 *  
 */

int startBotVal;
int trigBotVal; 

int startTopVal;
int trigTopVal;

unsigned long startTime;
unsigned long endTime;
unsigned long elapsedTime;

void setup() {
  Serial.begin(9600);
  startTopVal = analogRead(A1);
  startBotVal = analogRead(A0);
  Serial.println("Clear Output");
  delay(1000);
  Serial.println("3");
  delay(1000);
  Serial.println("2");
  delay(1000);
  Serial.println("1");
  delay(1000);
  
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  digitalWrite(6, LOW);

  trigTopVal = (0.75 * startTopVal);
  trigBotVal = (0.75 * startBotVal);

  digitalWrite(6, HIGH);
}


void loop() {
  int botValue = analogRead(A0);
  int topValue = analogRead(A1);
  if (botValue <= trigBotVal) {
    digitalWrite(2, HIGH);
    endTime = millis();

    elapsedTime = (endTime - startTime);
    elapsedTime = (elapsedTime / 1000);
    Serial.println(elapsedTime);
  }
  if (topValue <= trigTopVal) {
    digitalWrite(4, HIGH);
    startTime = millis();
  }
}
