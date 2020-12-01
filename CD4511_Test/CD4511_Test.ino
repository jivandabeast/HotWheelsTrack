/*
 * Created by Jivan RamjiSingh
 * 
 * Testing the usability of a CD4511BE with an Arduino
 */



void setup() {
  for (int i = 9; i <= 12; i += 1) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  digitalWrite(10, HIGH);
  digitalWrite(12, HIGH);
}

void loop() {
  

}
