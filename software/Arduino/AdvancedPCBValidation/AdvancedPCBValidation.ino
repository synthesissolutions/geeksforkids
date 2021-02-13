/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  int sensorValue2 = analogRead(A1);
  int sensorValue3 = analogRead(A4);
  int sensorValue4 = analogRead(A5);
  // print out the value you read:
  
  Serial.print("RJ45: ");
  Serial.print(sensorValue);
  Serial.print(" ");
  Serial.print(sensorValue2);
  Serial.print("    RC: ");
  Serial.print(sensorValue3);
  Serial.print(" ");
  Serial.println(sensorValue4);

  delay(25);        // delay in between reads for stability
}
