
// PIN SETUP

//Piezo buzzer pin
const int SpeakerPin = 5;  

//Set up relay pins for each component
const int MotorPin = 7;
const int DrainPin = 8;
const int PumpPin = 12;
const int ValvePin = 11;

//Set up on/off switch pin
const int OnOffPin = 2;

//Set the variable to a string type
String CycleType;

//create variables for time to run components
long FillTime;
long SpinTime;
long DrainTime;
long ValveTime;


//FILL FUNCTION
void fill(){

  //Make sure other components are off
  digitalWrite(MotorPin, LOW);
  digitalWrite(ValvePin, LOW);
  digitalWrite(DrainPin, LOW);

  //Turn on pump
  digitalWrite(PumpPin, HIGH); 

  //Keep the pump on for x seconds 
  delay(FillTime);

  //Turn off pump
  digitalWrite(PumpPin, LOW);
}


//DRAIN FUNCTION
void drain(){

  //Make sure other components are off
  digitalWrite(MotorPin, LOW);
  digitalWrite(PumpPin, LOW);

  //Open valve so water can flow through
  digitalWrite(ValvePin, HIGH);

  //Turn on drain pump
  digitalWrite(DrainPin, HIGH); 

  //Keep the drain on for X seconds 
  delay(DrainTime);

  //Turn off drain and close valve
  digitalWrite(DrainPin, LOW);
  digitalWrite(ValvePin, LOW);
}


//SPIN FUNCTION
void spin(){
  
  //Make sure other components are off
  digitalWrite(PumpPin, LOW);
  digitalWrite(ValvePin, LOW);
  digitalWrite(DrainPin, LOW);

  //Turn on motor
      digitalWrite(MotorPin, HIGH);

      //Keep motor on for X seconds
      delay(SpinTime);

      //Turn off motor
      digitalWrite(MotorPin, LOW);
}


//END FUNCTION
void StopBeep() {

  //Set all pins to LOW
  digitalWrite(MotorPin, LOW);
  digitalWrite(ValvePin, LOW);
  digitalWrite(DrainPin, LOW);
  digitalWrite(PumpPin, LOW);

  //Have buzzer play tone to signify end of cycle
  tone(SpeakerPin, 500, 1000);
}

//SET PIN MODES 
void setup() {

//Set pizeo speaker pin to output
pinMode(SpeakerPin, OUTPUT);

//Set the relay pins to output
pinMode(MotorPin, OUTPUT);
pinMode(DrainPin, OUTPUT);
pinMode(PumpPin, OUTPUT);
pinMode(ValvePin, OUTPUT);

//Switch the on/off button to input pullup and set to input pullup, when switch is pushed away from resistor it reads LOW
  pinMode(OnOffPin, INPUT_PULLUP);

//connect with computer
Serial.begin(9600); 

//Prompt the user to input a cycle type, instruct user on how to use switch
Serial.println("Push switch towards resistor side before inputing cycle type if ready to start cycle. During the cycle push the switch away from the resistor if you would like the cycle to end.");
Serial.println("Choose cycle: Light, Normal, Heavy");
Serial.println("L = Light, N = Normal, H = Heavy");
}



//BEGIN 
void loop() 
{
  
  //If user types something
  if (Serial.available() > 0) 
  { 
    

    //Read string input until enter is pressed
    CycleType = Serial.readStringUntil('\n'); 

    //If user types L for light, this runs
    if (CycleType == "L")
    {
      //Print user's choice on serial monitor
      Serial.print("You have chosen LIGHT.");
      
      //Set the fill and draintime to 30 and 29 seconds, set spin time to 30 seconds
      FillTime = 15000;
      DrainTime = 30000;
      SpinTime = 5000;

    

      //Actual cycle: fills, spins, then drains twice, if the switch reads low at anytime, the current function finishes and then the whole cycle ends.
      if (digitalRead(OnOffPin)==LOW) fill();
      if (digitalRead(OnOffPin)==LOW) spin();
      if (digitalRead(OnOffPin)==LOW) drain();
      if (digitalRead(OnOffPin)==LOW) fill();
      if (digitalRead(OnOffPin)==LOW) spin();
      if (digitalRead(OnOffPin)==LOW) drain();

      //cycle is done so it beeps
      StopBeep();
      

    }

    //If user types N for normal, this runs
    else if (CycleType == "N")
    {
      //Print user's choice
      Serial.print("You have chosen MEDIUM.");

      //Set the fill and draintime to 30 and 29 seconds, set spin time to 45 seconds
      FillTime = 15000;
      DrainTime = 30000;
      SpinTime = 10000;

    

      //Actual cycle: fills, spins, then drains twice, if the switch reads low at anytime, the current function finishes and then the whole cycle ends.
      if (digitalRead(OnOffPin)==LOW) fill();
      if (digitalRead(OnOffPin)==LOW) spin();
      if (digitalRead(OnOffPin)==LOW) drain();
      if (digitalRead(OnOffPin)==LOW) fill();
      if (digitalRead(OnOffPin)==LOW) spin();
      if (digitalRead(OnOffPin)==LOW) drain();

      //cycle is done so it beeps
      StopBeep();
      
    }
    
    //If user types H for Heavy, this runs.
    else if (CycleType == "H")
    {
      //Print user's choice
      Serial.print("You have chosen HEAVY.");

      //Set the fill and draintime to 30 and 29 seconds, set spin time to 60 seconds
      FillTime = 15000;
      DrainTime = 30000;
      SpinTime = 15000;


      //Actual cycle: fills, spins, then drains twice
      if (digitalRead(OnOffPin)==LOW) fill();
      if (digitalRead(OnOffPin)==LOW) spin();
      if (digitalRead(OnOffPin)==LOW) drain();
      if (digitalRead(OnOffPin)==LOW) fill();
      if (digitalRead(OnOffPin)==LOW) spin();
      if (digitalRead(OnOffPin)==LOW) drain();

      //cycle is done so it beeps
      StopBeep();
           
    }
  }

}






