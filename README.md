# fishTank
This project is to be uploaded into Arduino microcontroller and the goal is to control two relays, the first one is for control a DC geared motor
and the second is to control the LED light of the fisher tank.

1) The motor moves a little jar which contains the food for the fishes. In the code is possible to modify the times that the jar turns and feeds the fishes
and also it pauses between feeds.

2) The light is provided by a LED lamp and currently is configured to keep turning on the light between 7:00 am and 2:00 pm. As you may know, a lot of
light is bad because microalgae could appear in the glasses of the aquarium. But is necessary to keep alive the plants inside the aquarium.

3) When the light is turned in on or the motor is working, a sound is played through a buzzer connected to the Arduino. 

4) Initially, the motor will feed the fishes two times each day, when it's 7:00 pm the light is turned off so the program will turn on the light while
feeding in order to help the fishes to see the food and can eat easily

5) Internally the Arduino is connected to an RTC (Real Time Clock) powered by a small battery. The first time you load the program it's necessary to 
configure the initial hour, minute, second, and date. After that, if the Arduino is turned in off or energy cut occur, then the next time the Arduino 
start the previous configured date and time will keep intact.
