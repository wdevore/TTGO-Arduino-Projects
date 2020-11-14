/*
  DetectButton

  Reads a digital input on pin 0, prints the result to the Serial Monitor.
  When the button is pushed a "0" is sent to the monitor else a "1".

  This example code is in the public domain.

  At terminal:
  minicom -D /dev/ttyUSB0 -b 9600
*/

// digital pin 0 has a pushbutton attached to it. Give it a name:
int pushButton = 0;
int count = 0;
int buttonState = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  Serial.print("Button: ");
  buttonState = digitalRead(pushButton);
  // print out the state of the button:
  if (buttonState == 1) {
    Serial.print("Off");
    count -= 1;
    if (count < 0)
      count = 0;
  }
  else {
    Serial.print("On");
    count += 1;
  }
  Serial.print(", Count: ");
  Serial.println(count);
  buttonState = 1;
  delay(10);        // delay in between reads for stability
}
