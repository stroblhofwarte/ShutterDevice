
#include <Servo.h>

int serialDataReady = 0;
String serialData;
String serBuf;

#define SERVO_PORT 0 // D3

Servo BlueServo;

#define OPEN_POS 10
#define CLOSE_POS 90

void setup() {
  // initialize serial:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SERVO_PORT, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  serBuf = "";
  serialData = "";

  BlueServo.attach(SERVO_PORT); 
  BlueServo.write(CLOSE_POS);
  delay(800);
  digitalWrite(SERVO_PORT, LOW);
}

void Greeting()
{
  Serial.print("ArduinoShutter#");
  Serial.flush();
}

void openShutter()
{
  BlueServo.write(OPEN_POS);
  delay(800);
  digitalWrite(SERVO_PORT, LOW);
  Serial.print("open#");
  Serial.flush();
}

void closeShutter()
{
  BlueServo.write(CLOSE_POS);
  delay(800);
  digitalWrite(SERVO_PORT, LOW);
  Serial.print("close#");
  Serial.flush();
}

void process(String data)
{
  if(data == "G:")
    Greeting();
  if(data == "O:")
    openShutter();
  if(data == "C:")
    closeShutter();
    
}

void VisualAck()
{
  digitalWrite(LED_BUILTIN, LOW);
  delay(100); 
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  // if there's any serial available, read it:
  if(Serial.available() > 0 && serialDataReady == 0) 
  {
    char c = Serial.read();
    if(c != '\n')
    {
      if(c == ':')
      {
        // Data line is complete
        serBuf += String(c);
        serialData = serBuf;
        serBuf = "";
        serialDataReady = 1;
      }
      else
        serBuf += String(c);
    }
  }
  if(serialDataReady == 1)
  {
    serialDataReady = 0;
    VisualAck();
    process(serialData);
  }
}
