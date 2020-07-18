int sensorCount = 5;
int threshold = 600;
int Position;

static const uint8_t analogPins[] = {0, 1, 2, 3, 4};
static const int pwmPin = 6;

void setup() {
  pinMode(pwmPin, OUTPUT);
}

void loop() {
  int valueSum = 0;
  int sensorData[sensorCount] = {0};
  
  for (int i = 0; i < sensorCount; i++){
    int sensorReading = analogRead(analogPins[i]);
    
    if (sensorReading > threshold)
      sensorData[i] = sensorReading;
    
    valueSum += sensorData[i];
  }
  
  if (valueSum == 0)
    valueSum = 1;
    
  Position = 0;
  for (int j = 0; j < sensorCount; j++){
    Position += (j*((float(sensorData[j])/float(valueSum))/4.0)*1024);
  }

  analogWrite(pwmPin, Position / 4);
}
