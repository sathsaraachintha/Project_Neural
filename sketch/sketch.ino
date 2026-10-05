void setup() {
  Serial.begin(115200);
  
  delay(2000); 
  
  Serial.println("ESP32-S3 is ready!");
}

void loop() {
  Serial.println("Hello");
  
  delay(1000);
}