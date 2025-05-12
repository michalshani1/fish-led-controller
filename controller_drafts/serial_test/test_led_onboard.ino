const int triggerPin = LED_BUILTIN;
bool startAction = false;
char incomingChar;
int ledState = LOW;
int step = 15;

void setup() {
  pinMode(triggerPin, OUTPUT);
  Serial.begin(9600);
  //while(!Serial){}
  delay(2000); // Give time for Bonsai to stabilize
  //Serial.println("Arduino Ready");
  for(int i=0;i<5;i++)
  {
    digitalWrite(triggerPin, HIGH);
    delay(100);
    digitalWrite(triggerPin, LOW);
    delay(100);
  }

}


void loop() {
  if (Serial.available() > 0) {
    incomingChar = Serial.read();
    //Serial.print("Received: ");
    //Serial.println(incomingChar);
    if (incomingChar == 'O') {
      startAction = true;
    //  Serial.println("LED Start Command Received");
    } else if (incomingChar == 'C') {
      startAction = false;
    //  Serial.println("LED Stop Command Received");
    }
  }

  if (startAction && ledState == LOW) {
    digitalWrite(triggerPin, HIGH);
    ledState = HIGH;
   // Serial.println("LED ON");
    delay(step * 10);
  } else if (!startAction && ledState == HIGH) {
    digitalWrite(triggerPin, LOW);
    ledState = LOW;
  //  Serial.println("LED OFF");
    delay(step * 10);
  }
}
