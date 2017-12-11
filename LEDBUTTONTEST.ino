//Setting the variables for each of the GPIO pins for LEDs and Button
int redLED = 13;
int yellowLED = 12;
int greenLED = 8;
int button = 2;

//Creating integer variables so I can store button counter and values
int buttonCounter = 0;
int bState = 0;
int bRecent = 0;

//Sets up pins for input and output
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  
  pinMode(button, INPUT);
  
}


void loop() {
  //Reads if button is pressed or not
  bState = digitalRead(button);

  //If button is not the same value as before it will add 1 to counter
  if(bState != bRecent) {
    if (bState == HIGH) {
      buttonCounter++;
    
    }
    
    delay(50);
  }
  //Resetting the value of the variable
 bRecent = bState;

//Depending how many times the button has been pressed it will light up more lights
 if (buttonCounter == 1) {
   digitalWrite(redLED, HIGH);
 }
  else if (buttonCounter == 2) {
    digitalWrite(yellowLED, HIGH);
  }
  else if (buttonCounter == 3) {
  digitalWrite(greenLED, HIGH);
    
  }
  //If the button has been pressed 4 or more times then it will turn all LEDs off and reset the counter
  else if(buttonCounter >=4) {
  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, LOW);

  buttonCounter = 0;
  }

/*
  TEST CODE FOR TURNING RED, YELLOW AND GREEN LED ON AND OFF LIKE A TRAFFIC LIGHT WITH DELAYS
  digitalWrite(redLED, HIGH);   
  delay(3000);                  
  digitalWrite(redLED, LOW);    
  delay(3000);                     

  digitalWrite(yellowLED, HIGH);   
  delay(3000);                      
  digitalWrite(yellowLED, LOW);    
  delay(3000);

  digitalWrite(greenLED, HIGH);   
  delay(3000);                      
  digitalWrite(greenLED, LOW);    
  delay(3000); */
}
