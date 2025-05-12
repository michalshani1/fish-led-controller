void setup() {
  Serial.begin(9600); // Match default expected baudrate
}

void loop() {
  Serial.println("Hello from Arduino");
  delay(1000);
}
