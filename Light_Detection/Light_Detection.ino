/* 
 *  Created by Jivan RamjiSingh
 *  
 *  Testing the viability of a photoresistor to detect a hot wheels car moving down the track
 *  
 */

int startVal;
int trigVal; 

void setup() {
  Serial.begin(9600);
  startVal = analogRead(A0);
  Serial.println("Clear Output");
  delay(1000);
  Serial.println("3");
  delay(1000);
  Serial.println("2");
  delay(1000);
  Serial.println("1");
  delay(1000);
  
  Serial.println(startVal);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);

  trigVal = (0.75 * startVal);
  Serial.println(trigVal);
}


void loop() {
  int value = analogRead(A0);
  if (value <= trigVal) {
    digitalWrite(2, HIGH);
    Serial.println(value);
  }
  //Serial.println(value);
}
