//Pin numbers for each of the components
int wireController = 11;
int wireController1 = 10;
int wireController2 = 9;

int ledPinHigher = 13;
int ledPinLower = 12;
int ledPinHigher1 = 6;
int ledPinLower1 = 5;
int ledPinHigher2 = 4;
int ledPinLower2 = 3;

int buttonReceiver = 2;
int buttonReceiver1 = 7;
int buttonReceiver2 = 8;

int temperatureSensor = A0;
int temperatureSensor1 = A1;
int temperatureSensor2 = A2;

//Flags for the states of the components and time related variables
int wireState = 0
int timeFirstPress = 0;
int isPressedButton = 1;
int wireState1 = 0;
int timeFirstPress1 = 0;
int isPressedButton1 = 1;
int wireState2 = 0;
int timeFirstPress2 = 0;
int isPressedButton2 = 1;

void checkTempState(int temperatureSensor){
  if(analogRead(temperatureSensor)){
  }
  return;
}

void togglePower(int timeFirstPress, int * isPressedButton, int * wireState, int buttonReadPin, int basePin, int ledPinHigher, int ledPinLower){
  int currentTime = millis();

  if(digitalRead(buttonReadPin) == HIGH)
  { 
    if (*isPressedButton == 1){
      if (*wireState == 2){
        *wireState = 0;
        analogWrite(basePin, 0);
        digitalWrite(ledPinLower, LOW);
        digitalWrite(ledPinHigher, LOW);
      }
      else if(*wireState == 0)
      {
        *wireState = 1;
        analogWrite(basePin, 127);
        digitalWrite(ledPinHigher, LOW);
        digitalWrite(ledPinLower, HIGH);
      }
      else if(*wireState == 1)
      {
        *wireState = 2;
        analogWrite(basePin, 160);
        digitalWrite(ledPinLower, LOW);
        digitalWrite(ledPinHigher, HIGH);
      }
      
      *isPressedButton = 0;
      timeFirstPress = millis();
    }
  }

  if (currentTime - timeFirstPress >= 100){
    *isPressedButton=1;
  }
}

void setup()
{
  Serial.begin(9600);
  
  pinMode(wireController, OUTPUT);
  pinMode(wireController1, OUTPUT);
  pinMode(wireController2, OUTPUT);
  
  pinMode(temperatureSensor, INPUT);
  pinMode(temperatureSensor1, INPUT);
  pinMode(temperatureSensor2, INPUT);
  
  pinMode(buttonReceiver, INPUT);
  pinMode(buttonReceiver1, INPUT);
  pinMode(buttonReceiver2, INPUT);
  
  digitalWrite(wireController, LOW);
  digitalWrite(wireController1, LOW);
  digitalWrite(wireController2, LOW);
  
  wireState = 0;
  timeFirstPress = 0;
  isPressedButton = 1;
  wireState1 = 0;
  timeFirstPress1 = 0;
  isPressedButton1 = 1;
  wireState2 = 0;
  timeFirstPress2 = 0;
  isPressedButton2 = 1;
}

void loop()
{  
    int reading = analogRead(temperatureSensor);
    float voltage = reading * 5.0;
    voltage /= 1024.0;

    int temp = (voltage - 0.5) * 100;

  togglePower(timeFirstPress, &isPressedButton, &wireState, buttonReceiver, wireController, ledPinHigher, ledPinLower);
  togglePower(timeFirstPress1, &isPressedButton1, &wireState1, buttonReceiver1, wireController1, ledPinHigher1, ledPinLower1);
  togglePower(timeFirstPress2, &isPressedButton2, &wireState2, buttonReceiver2, wireController2, ledPinHigher2, ledPinLower2);
}