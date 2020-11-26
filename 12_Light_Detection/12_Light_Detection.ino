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

unsigned long startTime[6] = {};
unsigned long endTime[6] = {};
unsigned long elapsedTime[6] = {};

boolean topTrig[6] = {true, true, true, true, true, true};
boolean botTrig[6] = {true, true, true, true, true, true};

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
  for (int i = 0; i < 6; i += 1) {
    int topValue = analogRead(topPho[i]);
    int botValue = analogRead(botPho[i]);

    if ((topValue <= trigTopVal[i]) && (topTrig[i])) {
      startTime[i] = millis();
      topTrig[i] = false;
    }
    if ((botValue <= trigBotVal[i]) && (botTrig[i])) {
      digitalWrite(lightPin[i], HIGH);
      endTime[i] = millis();
      elapsedTime[i] = (endTime[i] - startTime[i]);
      elapsedTime[i] = (elapsedTime[i] / 1000);
      Serial.println();
      Serial.print("Lane ");
      Serial.print(i);
      Serial.print(" finished with a time of ");
      Serial.print(elapsedTime[i]);
      Serial.println(" !");
      botTrig[i] = false;
    }
  }
}
