
String inputString = "";
String commandString = "";
boolean stringComplete = false;
boolean isConnected = false;
const int stepsPerRevolution = 400;
float degree = 0;
int ENA = 3;

int speed = 0;
//int Step = 0;

//Include
#include <Stepper.h>
#include <ArduinoJson.h>

StaticJsonDocument<200> data;

Stepper myStepper(stepsPerRevolution, 7, 5);


void setup() {
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);           // set pin to input
  digitalWrite(ENA, HIGH);
}

void loop() {
  if (stringComplete)
  {
    stringComplete = false;
    getCommand();
    //float STEPS_PER_OUT_REV = stepsPerRevolution * (GEAR_RED / 4.444);
    if (commandString.equals("START"))
    {
      digitalWrite(ENA, LOW);
      Serial.println("START");
    }
    if (commandString.equals("STOP"))
    {
      digitalWrite(ENA, HIGH);
      Serial.println("STOP");
    }
    else if (commandString.equals("MOVE"))
    {
      myStepper.setSpeed(speed);
      myStepper.step(degree);
      Serial.println("done");
    }
    inputString = "";
  }

}

void getCommand()
{
  if (inputString.length() > 0)
  {
    //{"speed":500,"degree":64,"step":10,"command":"LED1"}
    DeserializationError error = deserializeJson(data, inputString);
    const char* temp = data["command"];

    commandString =  temp;
    speed = data["speed"];
    degree = (double)data["degree"];
    //Step = data["step"];

   /* Serial.print("speed: ");
    Serial.println(speed);
    
    Serial.print("command: ");
    Serial.println(commandString);*/
  }
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
