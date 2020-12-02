/* 
 *  Created by Jivan RamjiSingh
 *  
 *  Arduino assisted Hot Wheels race track
 *  12 photoresistors, 7 LEDs, 6 segmented displays
 *  Lots of room for expansion and other things to add to it, feel free to hack away!
 *  
 */

#include <Arduino.h>
#include "KickSort.h"

// Pins that the photoresistors are connected to
const char lightPin[] = {3, 4, 5, 6, 7, 8, 2};
const char topPho[] = {A0, A1, A2, A3, A4, A5};
const char botPho[] = {A6, A7, A8, A9, A10, A11};

// Pins that the 7 segment displays are connected to
const char dispPin[] = {};

const int lanes = 6;

// Arrays to save the initial and threshold values from the photoresistors
int topVal[6] = {};
int botVal[6] = {};

int trigTopVal[6] = {};
int trigBotVal[6] = {};

// Variables for keeping track of the track times
int finTrack = 0; 

unsigned long startTime[6] = {};
unsigned long endTime[6] = {};
unsigned long elapsedTime[6] = {};

int milliSeconds[6] = {};

// Booleans for keeping track of which lanes have been started/finished
boolean topTrig[6] = {true, true, true, true, true, true};
boolean botTrig[6] = {false, false, false, false, false, false};

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing");

  Serial.println();
  Serial.print("Configuring LED pin outputs: ");
  // Configuring LED pin outputs
  for (int n = 0; n < 7; n += 1) {
    Serial.print(n);
    Serial.print(" ");
    pinMode(lightPin[n], OUTPUT);
    digitalWrite(lightPin[n], LOW);
  }
  Serial.println();

  Serial.println();
  Serial.print("Setting up lane: ");
  // Setting up lanes
  for (int i = 0; i < 6; i += 1) {
    Serial.print(i);
    Serial.print(" ");
    topVal[i] = analogRead(topPho[i]);
    botVal[i] = analogRead(botPho[i]);

    trigTopVal[i] = (0.75 * topVal[i]);
    trigBotVal[i] = (0.75 * botVal[i]);
  }

  // Activate ready signal
  Serial.println();
  digitalWrite(lightPin[6], HIGH);

}

void loop() {
  for (int i = 0; i < 6; i += 1) {
    // Read the values from the two resistors in each lane
    int topValue = analogRead(topPho[i]);
    int botValue = analogRead(botPho[i]);
    
    // If the top resistor value is below the trigger threshold
    // record the time and set the booleans appropriately
    if ((topValue <= trigTopVal[i]) && (topTrig[i])) {
      startTime[i] = millis();
      topTrig[i] = false;
      botTrig[i] = true;
    }

    // If the bottom resistor value is below the trigger threshold
    // and the top resistor has already been called
    // record the time, calculate elapsed time, and adjust variables
    if ((botValue <= trigBotVal[i]) && (botTrig[i])) {
      digitalWrite(lightPin[i], HIGH);
      endTime[i] = millis();
      elapsedTime[i] = (endTime[i] - startTime[i]);
      // elapsedTime[i] = (elapsedTime[i] / 1000);
      Serial.println();
      Serial.print("Lane ");
      Serial.print(i);
      Serial.print(" finished with a time of ");
      Serial.print(elapsedTime[i]);
      Serial.println(" !");
      botTrig[i] = false;
      finTrack += 1;
      milliSeconds[i] = elapsedTime[i];

      // If all six lanes have been called, calculate results
      if (finTrack == 6) {
        Serial.println();
        KickSort<int>::quickSort(milliSeconds, lanes, KickSort_Dir::ASCENDING);
        for (int i = 0; i < lanes; i += 1) {
          int t = milliSeconds[i];
          for (int n = 0; n < lanes; n += 1) {
            if (t == elapsedTime[n]) {
              Serial.print("Lane ");
              Serial.print(n);
              Serial.print(" finished in ");
              int p = (i + 1);
              Serial.print(p);
              Serial.print(" Place, with a time of ");
              Serial.print(t);
              Serial.print(" !");
              Serial.println();
            }
          }
        }
      }
    }
  }
}