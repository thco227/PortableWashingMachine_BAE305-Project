# PortableWashingMachine_BAE305-Project
The following report contains the documentation of the construction of a portable washing machine for the class BAE 305. The members of this team were Maggie Barnes, Tiffany Coogle, Elyssa Roberts, and Hunter Walters.

## Summary
The goal of our project was to create a portable washing machine. The portable washing machine is applicable for situations in which the user has only a few small items of clothing to wash, and does not want to use a full size washing machine for them. Because of this, the portable washing machine that was created is most suitable for items such as socks, underwear, etc. The portable washing machine body is made from a 2 gallon bucket, and contains two pumps, a valve, a motor, and a 3D printed impeller. An Arduino RedBoard was used to control the operation of each component of the washing machine. The washing machine has three cycles: 1, 2, and 3 minutes, which each fill and drain twice to wash the clothes, remove the dirty water, then rinse. The user can select the desired cycle by inputting their selection into the serial monitor of the computer connected to the RedBoard. Then, when the user is ready, a switch can be used to start the cycle. At the end of the cycle, a buzzer beeps to notify the user to remove their clothes from the washing machine. Should the user need to stop the cycle before the specified duration, the switch can be used to stop the cycle midway. This project was initiated in January 2023 and progress was tracked using the Scrum project development method. The complete project was presented for assessment on April 20th, 2023, and all features on our project backlog were demonstrated successfully.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=BKz9ElXcXlw" target="_blank"><img src="http://img.youtube.com/vi/BKz9ElXcXlw/0.jpg" height="300" /></a>

## Design Description 

### Materials
* 4 V23234-B1001-X004 Plug-in Mini ISO Relays
* 4 relay bases
* Jumper wires
* 3 TIP 31C Transistors
* 3 10k ohm resistors
* Arduino RedBoard
* Computer with Arduino IDE downloaded
* 1 Piezo Buzzer
* 1 Button
* 2 B07X9L5RNS HiLetgo DC Brushless Water Pumps (240L/min)
* 1 B08KS6FMC7 Gredia N/C DC Solenoid Valve
* 3/8" od. tubing
* LS-00086 OSEPP Electronics LTD DC Motor
* Global Specialties 100W Triple Output Switching DC Power Supply
* Female and Male Spade Connectors
* Crimper/wire stripper
* 2 Gallon Bucket with Lid
* 3D Printed Impeller
* 3D Printed Shaft Connector
* 1" od. PVC Pipe
* Hand Saw
* Kroger 1 Gallon Chocolate Icecream Bucket
* 1 set of Alligator Probes

### Design

#### Physical Design
When first creating the design for the washing machine, a five gallon bucket was the selected size for the unit. However, after calculating the torque needed to move that much water plus clothing and considering the voltage requirements and prices, a size reevaluation was necessary. A five gallon bucket half full of water was estimated at about 8 pounds without the weight of clothing. With a half foot of diameter estimated, around 4 lb-ft of torque would be needed at the minimum. The motors rated at this torque were very expensive and often required higher voltages. In the end, a 2 gallon bucket was decided on, with the intention to not fill it completely. Based on the size adjustment, a motor was chosen. The LS-00086 DC motor was chosen due to its low price, low voltage, and torque rating of 2.18 lb.-ft. The B07X9L5RNS brushless DC water pumps were chosen for their pumping capacity (240 L/min), low price, and low voltage/power consumption. Two were purchased: one to pump water in and one to empty the reservoir. In addition to these pumps, a B08KS6FMC7 Gredia normally closed DC solenoid valve was chosen to keep the unprimed outlet pump from continuing to send water into the drain.

Based on the size adjustment, a motor was chosen. The LS-00086 DC motor was chosen due to its low price, low voltage, and torque rating of 2.18 lb.-ft. The B07X9L5RNS brushless DC water pumps were chosen for their pumping capacity (240 L/min), low price, and low voltage/power consumption. Two were purchased: one to pump water in and one to empty the reservoir. In addition to these pumps, a B08KS6FMC7 Gredia normally closed DC solenoid valve was chosen to keep the unprimed outlet pump from continuing to send water into the drain.


#### Circuit Design
When designing the washing machine, an important factor was being able to control the operation of the pumps, motor, and valve, which all operated at 12 volts DC. This voltage could not be supplied from the RedBoard alone, so relays were used to switch them on and off. The components of the washing machine were connected to the switch connected terminals on the relay. A 12 volt supply was connected to these terminals as well. When the relay was turned on, the switch would close, allowing the 12 volts to flow to ground, and subsequently turning on the desired component. 

To turn the relay on and off, a controllable signal was needed on the non-switch connected terminals. However, the current needed to turn on the relay was calculated to be _ mA, which was too high for the RedBoard to produce. To achieve the desired current, transistors were used. The TIP31C models were used in the circuit. Four digital output pins (7, 8,12, and 13) from the RedBoard were connected to the bases of the transistors. A 12 volt supply was connected to the collector on the transistor. The emitter was connected to the relay. When the RedBoard sent out a 5 volt signal to the transistor, the 12 volts attached to the transistor would be allowed to flow through the relay to ground. This higher voltage was able to produce enough current to trigger the relay.

The design of the circuit also included a piezo buzzer and a switch. They were connected to the RedBoard via pins 5 and 2 respectively. When pin 5 sent out a signal, the buzzer would play a tone. Pin 2, which was connected to the switch, was set to input pullup mode. This meant that the pin would read zero until the switch was moved, then it would read low. The input pullup resistor mode was used to prevent floating values.  

To help make the schematic easier to read, the wires leading to ground are highlighted in red, the wires connected to power are highlighted in green, and the wires connected to a pin are various colors of blue.

![image](https://user-images.githubusercontent.com/128632699/232825480-48f45489-9004-4147-b99f-dab62197959b.png)


#### Code

The code that operated the circuit was created in Arduino IDE and is explained below. First, the pins were set as constant integer variables as shown below.
```c
const int SpeakerPin = 5;

const int MotorPin = 7;

const int DrainPin = 8;

const int PumpPin = 12;

const int ValvePin = 11;

const int OnOffPin = 2;
```
The variable "CycleType" was initialized as a string so it could hold other strings. This was essential to allow the user's input to be read correctly.
```c
String CycleType;
```
The following variables set the time to run each component of the washing machine. A "long" variable type, which allows numbers from -2,147,483,648 to 2,147,483,647 to be assigned to it, was used. This allowed for a higher level of variablilty in the cycles. The times could be set to larger numbers than was possible with an integer variable, which only went from -32,768 to 32,767.
```c
long FillTime;

long SpinTime;

long DrainTime;

long ValveTime;
```
In the setup loop, the all pinmodes except the switch pin were set to output. These pins needed to output HIGH to activate the transistors.
```c
void setup() {

pinMode(SpeakerPin, OUTPUT);

pinMode(MotorPin, OUTPUT);

pinMode(DrainPin, OUTPUT);

pinMode(PumpPin, OUTPUT);

pinMode(ValvePin, OUTPUT);
```
The switch pin was set to input pullup. This allowed the switch to ground a signal when connected.
```c
pinMode(OnOffPin, INPUT_PULLUP);
```
In this loop, serial connection was created by using the Serial.begin command and setting the baud rate to 9600.
```c
Serial.begin(9600);
```
Finally, the setup loop was concluded by displaying a message to prompt user input to choose a cycle type and instructing the user how to use the switch.
```c
Serial.println("Push switch towards resistor side before inputing cycle type if ready to start cycle. 
During the cycle push the switch away from the resistor if you would like the cycle to end.");

Serial.println("Choose cycle: Light, Normal, Heavy");

Serial.println("L = Light, N = Normal, H = Heavy");
}
```
The main loop was comprised of many if and else statements. The blanketing if statement told the program to start if the user input something into the serial monitor. 
```c
void loop() 
{
if (Serial.available() > 0)
```
The string variable "CycleType" stored the input until "\n" was found, which equated to the user pressing the enter key. Depending on the user input, three different if or else if statements could be trigered. These three loops had varying messages and times to correspond with the cycle type. The light cycle is shown below, howver the normal and heavy cycles have the exact same code, except with the time variables set to different times and the messages displaying the corresponding cycle. Note that the times are given in milliseconds.
```c
CycleType = Serial.readStringUntil('\n');

if (CycleType == "L")

Serial.print("You have chosen LIGHT.");

FillTime = 15000;

DrainTime = 30000;

SpinTime = 5000;
```
To easily adjust and call upon the major actions of the washing machine, functions were created. Fill, drain, valve, and motor fucntions were comprised of turning the corresponding pin to high, delaying for a set time, and then turning the pin to low. By setting the time in each function to a variable, the times for each cycle type could be easily adjusted. Each cycle type redefined the times for each function to allow to customize the intensity. The fill function is shown below, however the other functions follow a similar outline, with different pins being set to HIGH.

```c
void fill(){

  digitalWrite(MotorPin, LOW);
  
  digitalWrite(ValvePin, LOW);
  
  digitalWrite(DrainPin, LOW);

  digitalWrite(PumpPin, HIGH);
  
  delay(FillTime);

  digitalWrite(PumpPin, LOW); }
  ```

In each cycle, after the times were defined, the same sequence code would run. The sequece called on various functions created to fill, spin, drain, and turn the valve on and off. Before inputing a cycle type into the serial monitor, the user would be prompted to turn the switch toward the resistor on the breadboard if they were ready to start the cycle. With the switch toward the resistor, the pin would read LOW. When the switch was pressed away from the resistor, the pin would read zero. The code used this to create a system in which the cycle could be stopped in the middle. This was accomplished by putting an if statement before each step of the cycle. When the switch was pushed toward the resistor, it would read LOW, and would allow the code to run. If pressed away, the pin would read zero, and the code would stop because the conditions would not be fufilled.
```c
if (digitalRead(OnOffPin)==LOW) fill();

if (digitalRead(OnOffPin)==LOW) spin();

if (digitalRead(OnOffPin)==LOW) drain();

if (digitalRead(OnOffPin)==LOW) fill();
```
A function for the beep at the end of the cycle was also created, which included the tone command so the pin, frequency, and duration could be selected. This function was not put within an if statement on the conditon of the switch, so the user would know if their cycle had ended had they decided to end it midway.

```c
void StopBeep() {
  digitalWrite(MotorPin, LOW);
  
  digitalWrite(ValvePin, LOW);
  
  digitalWrite(DrainPin, LOW);
  
  digitalWrite(PumpPin, LOW);

  
  tone(SpeakerPin, 500, 1000);
}
```


#### 3D Printing Design
For the inner workings of the machine, we researched actual appliances. Commercially available washing machines most often employ one of two washing methods: agitation or impeller washing. In an agitation washing machine, a central shaft with vanes rotates to spin clothes in water and wash them. An impeller is a low disc with fins that sits at the bottom of the basket, and impeller washing uses this structure to wash clothes. The design takes advantage of the friction generated between the articles of clothing to wash them and uses less water than an agitation machine does. For our small scale machine, we wanted to optimize our water use, so the impeller design was the ideal choice. When we took into consideration the materials we would be using, we realized it would be far easier to 3D print an impeller than a central agitator.

Our impeller design is simple: it's a flat disc that rises in the center to form a low cone. This center is hollow to allow our central shaft, a PVC pipe with an outer diameter of approximately 1 in, to be inserted. From the center cone, eight identical vanes protrude, lofting down to meet the edge of the disc. Commercial impellers tend to have six of these vanes, but we chose to use either for a more sturdy impeller, as, at the time of designing this part, we were unsure how much stress the impeller would be under. Future iterations of this project should test different impeller designs. The eight-vaned impeller part file is shown below.

<img src="Impeller Drawing.png" height="300">

To create this part, we used the 3D printers available at the Innovation Center at the University of Kentucky. The printer used was the Prusa Mini+, printing with Inland 1.75mm PLA filament. This printer's print bed is a 7 in square, which is just smaller than the impeller's diameter of 7.5 in. To use the Prusa Mini+, we cut our impeller file into four identical parts, as in the drawing file below. These four parts each had a mass of 40.01 grams, resulting in a total combined mass of 164.04 grams. 

<img src="Impeller Quarter Drawing.png" height="300">

Once these were printed, the triangular faces were glued together using E6000 industrial adhesive to form the full impeller, as shown in this photograph.

<img src="Impeller Photo.jpg" height="300"> <img src="Impeller Photo(2) (1).jpg" height="300">

Another key component of the physical washing system is the motor mount. As mentioned previously, we chose to use a section of PVC pipe as a central shaft that would connect our impeller to the motor. To rotate this shaft from the motor key, we designed a fitting for the end of the pipe that has a hole to insert the motor shaft. This part was printed using the Prusa Mini+, with Inland 1.75mm PLA. The total mass of the print was 13.18 grams. The images show our drawing file and photos of the final print.

<img src="Motor Mount Drawing.png" height="300">

<img src="Motor Mount Photo.jpg" height="300"> <img src="Motor Mount Photo(2).jpg" height="300"> <img src="Motor Mount Photo(3).jpg" height="300">

#### Laser Cut Design

The initial plan for the stand that would hold the bucket up was to 3D print. With the design having a diameter right above 9 inches, an industrial size printer would have been needed to perform the print. Then considering a new way to print smaller pieces and glue them together, the cost and time to do so was still not reasonable. The final solution was to laser cut 4 (dimensions) pieces, 1 base piece that was (dimensions) with a circle cut out in the middle, and 8 (dimensions) to create legs so that the bucket would be lifted. The circle cut out of the bottom and the legs being added so the bucket was 4 inches off the surface, was to supply room for the motor to be mounted. These components were laser cut from a 11.5 x 23.5 x .25 inch thick piece of wood. When laser cut, divots were added to the edges of the components to help them be glued together with more ease and stability. Gorilla wood glue was used to hold the pieces together.
 
!!!!!PICTURE OF PEICES LASER CUT WITH LABELED DIMENSIONS!!!!!

!!!!!3D DRAWING????!!!!!

![image](https://user-images.githubusercontent.com/128632699/234920913-ea3b110e-f991-494c-a286-65586017bc9c.png)

## Testing

#### Construction


During the construction of the initial circuit, the position of the relay relative to the transistor was adjusted. At first, the relay was positioned directly after the voltage supply and before the emitter. However, the relay caused a voltage drop before the transistor which was so low, that the voltage difference did not allow current to flow from the power supply to ground. To fix this, the relay was repositioned after the emitter and before the ground. 

#### Pump Flow Rate Testing
The timing of the drain and pump were important in ensuing the washing machine completed a full cycle. The pumps were advertised as having a flow rate of 240L/hr. To test the flow rate, the pumps were set to run for a given amount of time, and the water was collected in a graduated cylinder. The testing resulted in a flow rate of about 140 L/hr. This reduction in flow rate was most likely due to the tubing attached to the pump, causing the water to slow. 

#### Cycle Testing
To run the entire cycle, the water needed to end at the same level that it started at.


## Design Results Discussion

## Test Results Discussion

#### Motor
To test the motor that controlled the agitator we ran just that part of the code to confirm the motor would spin the agitator correctly. After running the code we could confirm the motor was indeed working correctly at an efficient speed.

![image](https://user-images.githubusercontent.com/128632699/234919649-f80057c6-9721-4500-9f46-039b59b15715.png)

#### Pumping System
To test the pumping system we connected tubing to the pumps and filled one bucket with water. The tubes ran from the bucket with water to the main system, and back to the bucket of water. When testing we ran our code and were able to confirm that the pumps and tubing system were indeed able to takewater from the water bucket, fill the main system, then empty the main system back to the water bucket.

![Pump Testing Data](https://user-images.githubusercontent.com/128632699/234917565-806b4ccf-d7b0-422a-b616-40089b56d7a7.JPG)
![image](https://user-images.githubusercontent.com/128632699/234919778-104a27f8-9f4c-4bef-b895-76b67d5eeef0.png)
![image](https://user-images.githubusercontent.com/128632699/234919844-d281b1d7-34fd-42bf-85ed-b04b940daa87.png)

#### Buzzer
To test the buzzer system that goes off at the end of each cycle, we ran all three types of cycles and made sure the buzzer successfully went off at the end of each one.
![image](https://user-images.githubusercontent.com/128632699/234920975-a211e361-7099-472d-bd06-70036be99d4c.png)

#### Physical Components 
To test to make sure all of our physical components worked together, we had to bring all of the parts of the project into the lab and put it together. After assembling we were able to confirm all the peices fit together. Once getting all the peices fitted together properly we ran a full cycle to make sure everything ran smoothly. The cycle was ran and completed successfully.
![image](https://user-images.githubusercontent.com/128632699/234920149-0c92d2e3-cc3c-47da-b917-77c790f5594f.png)

