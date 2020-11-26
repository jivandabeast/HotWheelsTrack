/* 
 *  Created by Jivan RamjiSingh
 *  
 *  Code for a semi-full scale 6 lane track setup 
 *  12 Photoresistors, 2 per lane
 *  7 LEDs, 1 per lane + 1 "ready"
 *  
 */

const char lightPin[] = {3, 4, 5, 6, 7, 8, 2};
const char topPho[] = {A0, A1, A2, A3, A4, A5};
const char botPho[] = {A6, A7, A8, A9, A10, A11};

int topVal[6] = {};
int botVal[6] = {};

int trigTopVal[6] = {};
int trigBotVal[6] = {};

unsigned long startTime = 0;
unsigned long endTime = 0;
unsigned long elapsedTime = 0;

boolean topTrig = true;
boolean botTrig = true;

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing");

  Serial.println();
  Serial.print("Configuring LED pin outputs: ");
  for (int n = 0; n < 7; n += 1) {
    Serial.print(n);
    Serial.print(" ");
    pinMode(lightPin[n], OUTPUT);
    digitalWrite(lightPin[n], LOW);
  }
  Serial.println();

  Serial.println();
  Serial.print("Setting up lane: ");
  for (int i = 0; i < 6; i += 1) {
    Serial.print(i);
    Serial.print(" ");
    topVal[i] = analogRead(topPho[i]);
    botVal[i] = analogRead(botPho[i]);

    trigTopVal[i] = (0.75 * topVal[i]);
    trigBotVal[i] = (0.75 * botVal[i]);
  }
  Serial.println();
  digitalWrite(lightPin[6], HIGH);
}


void loop() {
  int botValue = analogRead(A6);
  int topValue = analogRead(A0);
  if ((botValue <= trigBotVal[0]) && (botTrig)) {
    digitalWrite(3, HIGH);
    botTrig = false;
    endTime = millis();

    elapsedTime = (endTime - startTime);
    elapsedTime = (elapsedTime / 1000);
    Serial.println(elapsedTime);

    Serial.println("Triggered bottom photoresistor");
  }
  if ((topValue <= trigTopVal[0]) && (topTrig)) {
    digitalWrite(4, HIGH);
    topTrig = false;
    startTime = millis();
    Serial.println("Triggered top photoresistor");
  }
}
