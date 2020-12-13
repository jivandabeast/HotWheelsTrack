# HotWheelsTrack

Sure there's an [official Hot Wheels 6 Lane Race Track](https://www.amazon.com/Hot-Wheels-Super-6-Lane-Raceway/dp/B004U5C392), but that's so boring! 

This right here is that, but *better* and made by you!

The featureset is simple: you race the cars down the track, and it will tell you the winner (as well as who placed where). Unlike the official track, which will only tell you the lane to cross the finish first, this will tell you the placement for *every* track. Tracks can be enabled/disabled depending on how many cars you're racing. Additionally if you connect the Arduino to a PC so you can monitor serial, you can get calculated velocity for each car -- cool, huh?

# Hardware Requirements

The program doesn't really rely on too much, but here is what I used:

* 7 LEDs
* 12 Photoresistors 
* 12 11k Ohm Resistors
* 6 Switches
* 2 Push Buttons
* 6 Seven Segment Displays (Common Cathode)
* 6 CD4511BE IC Chips 
* Arduino Mega

Aside from the basic needs for the code to work, if you plan on building the track you're going to want:

* 2 Ethernet Cables, plus an additional 2 for internal wiring
* RJ-45 Keystones, Face Plates, and Breakout Boards
    * You will need 4 keystones & breakout boards, and 3-4 face plates depening on how you configure it.
* Wires to hook everything up
* You may find it beneficial to use pin headers to keep things a bit more modular


# Software Requirements

The software isn't reliant on much, however there are two things to note:

1. I wrote this using PlatformIO & VSCode
2. The program relies on the KickSort library, which can be found through PlatformIO
