# PortableWashingMachine_BAE305-Project
The following report contains the documentaion of the construction of a portable washing machine for the class BAE 305. The  following people contributed to the project: Tiffany Coogle, Maggie Barnes, Elyssa Roberts, and Hunter Walters.

## Summary
The goal of our project was to create a portable washing machine. The portable washing machine is applicable for situations in which the user has only a few small items of clothing to wash, and does not want to use a full size washing machine for them. Because of this, the portable washing machine that was created is most suitable for items such as socks, underwear, etc. The portable washing machine body is made from a 2 gallon bucket, and contains two pumps, a valve, a motor, and a 3D printed agitator. A RedBoard was used to control the operation of each component of the washing machine, and was mounted to the ________ of the system. The washing machine has three cycles: 1, 2, and 3 minutes, which each fill and drain twice to wash the clothes, remove the dirty water, then rinse. The user can select the desired cycle by inputing their selection into the serial monitor of the computer connected to the RedBoard. Then, when the user is ready, a button can be used to start the cycle. At the end of the cycle, a buzzer beeps to notify the user to remove their clothes from the washing machine. Should the user need to stop the cyle before the specified duration, the button can be pressed again to stop the cycle midway. This project was initiated in January 2023 and progess was tracked using the SCUM method. The projected reached complettion on _____ and the following results were found _____ .

## Design Description 

### Materials
* 4 ___ relays
* 4 ___ relay bases
* __ wires
* 3 TIP 31C Transistors
* 3 ___ ohm resistors
* RedBoard
* Computer with Arduino IDE downloaded
* 1 Piezo Buzzer
* 1 Button
* 2 B07X9L5RNS HiLetgo DC Brushless Water Pumps (240L/min)
* 1 B08KS6FMC7 Gredia N/C DC Solenoid Valve
* 3/8" od. tubing
* LS-00086 OSEPP Electronics LTD DC Motor
* ___ Power Supply
* ___ Connectors
* Crimper
* 2 Gallon Bucket with Lid
* 3D Printed Impeller
* 3D Printed Shaft Connector
* ___ od. PVC Pipe
*

### Design

#### Physical Design
When first creating the design for the washing machine a five gallon bucket was the selected size for the unit. However, after calcuating the torque needed to move that much water plus clothing and considering the voltage requirements and prices, a size reevaluation occured. A five gallon bucket half full of water was estimated at about 8 pounds without the weight of clothing. With a half foot of diameter estimated, around 4 lb-ft of torque would be needed at the minimum. The motors rated at this torque were very expensive and often required higher voltages. In the end, a 2 gallon bucket was decided on, with the intention to not fill it completely. Based on the size adjustment, a motor was chosen. The LS-00086 DC motor was chosen due to its low price, low voltage, and decent torque rating of 2.18 lb.-ft. The B07X9L5RNS brushless DC water pumps were chosen for their pumping capacity (240 L/min), low price, and low voltage/power consumption. Two were purchased: one to pump water in and one to empty the reservoir. In addition to these pumps, a B08KS6FMC7 Gredia normally closed DC solenoid valve was chosen to keep the unprimed outlet pump from continuing to send water into the drain.

#### Circuit Design
When designing the washing machine, an important factor was being able to control the operation of the pumps, motor, and valve, which all operated at 12 volts DC. This voltage could not be supplied from the RedBoard alone, so relays were used to switch them on and off. The components of the washing machine were connected to the switch connected terminals on the relay. A 12 volt supply was connected to these terminals as well. When the relay was turned on, the switch would close, allowing the 12 volts to flow to ground, and subsequently turning on the desired component. 

To turn the relay on and off, a controllable signal was needed on the non-switch connectted terminals. However, the current needed to turn on the relay was calculated to be _ mA, which was too high for the RedBoard to produce. To acheive the desired current, tranistors were used. The TIP31C models were used in the circuit. Four digital output pins (7, 8,12, and 13) from the RedBoard were connected to the bases of the tranisotrs. A 12 volt supply was connected to the collector on the transistor. The emitter was connected to the relay. When the redBoard sent out a 5 volt signal to the transitor, the 12 volts attched to the tranistor would be allowed to flow through the relay to ground. This higher voltage was able to produce enough current to trigger the relay.

The design of the circuit also inlcuded a piezo buzzer and a button. They were connected to the RedBoard via pins 5 and 2 respectively. When pin 5 sent out a signal, the buzzer would play a tone. Pin 2, whcih was connectted to the button was set to input pullup mode. This meant that the the pin would read high until the button was pressed, then it would read low. The input pullup resistor mode was used to prevent floating values.  

To help make the schematic easier to read, the wires leading to ground are highlighted in red, the wires connected to power are highlighted in green, and the wires connected to a pin are various colors of blue.

![image](https://user-images.githubusercontent.com/128632699/232825480-48f45489-9004-4147-b99f-dab62197959b.png)


#### Code
The code that operated the circuit was composed of if and else if statements. First, the pins were set as constant integer variables. The variable "CycleType" was also initialized as a string so it could hold other strings. In the void setup loop, the all pinmodes except the pin for the button were set to output. The button pin was set to input pullup. In this loop, serial connection was aslo created by using the Serial.begin command and setting the baud rate to 9600. Finally, the setup loop was concluded by displaying a message to prompt user input to choose a cycle type.

The main loop was comprised of many if and else statements. The blanketing if statemnt told the program to start if the user input something into the serial monitor. The string variable "CycleType" stored the input unitl "\n" was found, which equated to the user pressing the enter key. Depending on the user input, three different if or else if statements could be trigered. These three loops had varying messages and times to correspond with the cycle type. 

To easily adjust and call upon the major actions of the washing machine, functions were created. Fill, drain, valve, and motor fucntions were comprised of turning the corresponding pin to high, waiting a set time, and then turning the pin to low. By setting the time in each function to a variable, the times for each cycle type could be easily adjusted. A function for the beep at the end of the cycle was also created which included the tone command so the pin, frequency, and duration could be selected.


#### 3D Printing Design
For the inner workings of the machine, we researched actual appliances. Commercially available washing machines most often employ one of two washing methods: agitation or impeller washing. In an agitation washing machine, a central shaft with vanes rotates to spin clothes in water and wash them. An impeller is a low disc with fins that sits at the bottom of the basket, and impeller washing uses this structure to wash clothes. The design takes advantage of the friction generated between the articles of clothing to wash them and uses less water than an agitation machine does. For our small scale machine, we wanted to optimize our water use, so the impeller design was the ideal choice. When we took into consideration the materials we would be using, we realized it would be far easier to 3D print an impeller than a central agitator.

Our impeller design is simple: it's a flat disc that rises in the center to form a low cone. This center is hollow to allow our central shaft, a PVC pipe with an outer diameter of approximately 1 in, to be inserted. From the center cone, eight identical vanes protrude, lofting down to meet the edge of the disc. Commercial impellers tend to have six of these vanes, but we chose to use either for a more sturdy impeller, as, at the time of designing this part, we were unsure how much stress the impeller would be under. Future iterations of this project should test different impeller designs. The eight-vaned impeller part file is shown below.

<img src="Impeller Drawing.png">

To create this part, we used the 3D printers available at the Innovation Center at the University of Kentucky. The printer used was the Prusa Mini+, printing with Inland 1.75mm PLA filament. This printer's print bed is a 7 in square, which is just smaller than the impeller's diameter of 7.5 in. To use the Prusa Mini+, we cut our impeller file into four identical parts, as in the drawing file below. These four parts each had a mass of 40.01 grams, resulting in a total combined mass of 164.04 grams. 

<img src="Impeller Quarter Drawing.png">

Once these were printed, the triangular faces were glued together using E6000 industrial adhesive to form the full impeller, as shown in this photograph.

<img src="Impeller Photo.png">
<img src="Impeller Photo(2).png">

Another key component of the physical washing system is the motor mount. As mentioned previously, we chose to use a section of PVC pipe as a central shaft that would connect our impeller to the motor. To rotate this shaft from the motor key, we designed a fitting for the end of the pipe that has a hole to insert the motor shaft. This part was printed using the Prusa Mini+, with Inland 1.75mm PLA. The total mass of the print was 13.18 grams. The images show our drawing file and photos of the final print.

<img src="Motor Mount Drawing.png">
<img src="Motor Mount Photo.png">
<img src="Motor Mount Photo(2).png">
<img src="Motor Mount Photo(3).png">
=======
#### Laser Cut Design

The initial plan for the stand that would hold the bucket up was to 3D print. With the design having a diameter right above 9 inches, an industrial size printer would have been needed to preform the print. Then considering a new way to print smaller peices and glue them together, the cost and time to do so was still not reasonable. The final solution was to laser cut 4 (dimensions) peices, 1 base peice that was (dimensions) with a circle cut out in the middle, and 8 (dimensions) to create legs so that the bucket would be lifted. The circle cut out of the bottom and the legs being added so the bucket was 4 inches off the surface, was to supply room for the motor to be mounted. These components were laser cut from a 11.5 x 23.5 x .25 inch thick peice of wood. When laser cut, divets were added to the edges of the components to help them be glued together with more ease and stability. Gorilla wood glue was used to hold the peices together.
 
!!!!!PICTURE OF PEICES LASER CUT WITH LABELED DIMENSIONS!!!!!


!!!!!PICTURE OF FINAL PRODUCT!!!!!

!!!!!3D DRAWING????!!!!!

## Testing

#### Construction


During the construction of the inital circuit, the position of the relay relative to the tranistor was adjusted. At first, the relay was positioned directly after the voltage suplly and before the emitter. However, the relay caused a voltage drop before the transitor which was so low, that the voltage differnce did not allow current to flow from the power supply to ground. To fix this, the relay was repositioned after the emmiter and before the ground. 
#### Pump Flow Rate Testing

#### Motor Speed Testing

#### Cycle Testing

## Design Results Discussion

## Test Results Discussion
