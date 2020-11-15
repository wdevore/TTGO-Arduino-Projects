/*
  Simple Rotary Encoder test.
  Pin A and Pin B on rotary are the inputs to GPIO 15 and 2.
  Pin C is the middle pin and is connected to ground.
  
  This example code is in the public domain.

  At terminal:
  minicom -D /dev/ttyUSB0 -b 9600
*/

// ----------------------------------------------------------
// Approach #1 environment -- Doesn't work
// ----------------------------------------------------------
//// Setting up the counter
//int reading = 0;
//int lowest = -24;
//int highest = 24;
//int changeamnt = 1;
//
//// Timing for polling the encoder
//unsigned long currentTime;
//unsigned long lastTime;
//
//
//// Pin definitions
//const int pinA = 21;
//const int pinB = 22;
//
//// Storing the readings
//
//boolean encA;
//boolean encB;
//boolean lastA = false;

// ----------------------------------------------------------
// Approach #2 environment - Works
// Note: pin assignment is important. If pins A/B are assigned
// backwards it doesn't detect rotation.
// ----------------------------------------------------------
int brightness = 0;    // how bright the LED is, start at half brightness
const int maxValue = 10;
const int fadeAmount = 1;    // how many points to fade the LED by
unsigned long currentTime;
unsigned long loopTime;
const int pin_A = 15;  // The chosen "lead" pin based on the loop code.
const int pin_B = 2;
unsigned char encoder_A;
unsigned char encoder_B;
unsigned char encoder_A_prev=0;

void setup() {
  approach2_setup();
}

void loop() {
  approach2_loop();
}

void approach2_setup() {
  pinMode(pin_A, INPUT_PULLUP);
  pinMode(pin_B, INPUT_PULLUP);
  currentTime = millis();
  loopTime = currentTime; 
  // Start the serial monitor for debugging
  Serial.begin(9600);
}

//void approach1_setup() {
//  // set the two pins as inputs with internal pullups
//  pinMode(pinA, INPUT_PULLUP);
//  pinMode(pinB, INPUT_PULLUP);
//  
//  // Set up the timing of the polling
//  currentTime = millis();
//  lastTime = currentTime; 
//  
//  // Start the serial monitor for debugging
//  Serial.begin(9600);
//}

void approach2_loop() {
// get the current elapsed time
  currentTime = millis();
  if(currentTime >= (loopTime + 5)){
    // 5ms since last check of encoder = 200Hz  
    encoder_A = digitalRead(pin_A);    // Read encoder pins
    encoder_B = digitalRead(pin_B);   
    if((!encoder_A) && (encoder_A_prev)){
      // A has gone from high to low 
      if(!encoder_B) {
        // B is high so clockwise
        // increase the brightness, dont go over maxValue
        if(brightness + fadeAmount <= maxValue) brightness += fadeAmount;               
      }   
      else {
        // B is low so counter-clockwise      
        // decrease the brightness, dont go below 0
        if(brightness - fadeAmount >= 0) brightness -= fadeAmount;               
      }   

    }   
    encoder_A_prev = encoder_A;     // Store value of A for next time    
    
    Serial.println(brightness);
   
    loopTime = currentTime;  // Updates loopTime
  }
  // Other processing can be done here
}

//void approach1_loop() {
//  // Read elapsed time
//  currentTime = millis();
//  
//  // Check if it's time to read
//  if(currentTime >= (lastTime + 5))
//  {
//    // read the two pins
//    encA = digitalRead(pinA);
//    encB = digitalRead(pinB);
//    
//    // check if A has gone from high to low
//    if ((!encA) && (lastA))
//    {
//      // check if B is high
//      if (encB)
//      {
//        // clockwise
//        if (reading + changeamnt <= highest)
//        {
//          reading = reading + changeamnt; 
//        }
//      }
//      else
//      {
//        // anti-clockwise
//        if (reading - changeamnt >= lowest)
//        {
//          reading = reading - changeamnt; 
//        }
//      }
//      // Output reading for debugging
//      Serial.println(reading);
//    }
//    
//    // store reading of A and millis for next loop
//    lastA = encA;
//    lastTime = currentTime;
//  }
//}
