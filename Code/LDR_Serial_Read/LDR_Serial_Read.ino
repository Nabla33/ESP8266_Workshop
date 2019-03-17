const int LDR_IN = A0;

void setup() {
  Serial.begin(115200);
}

void loop() {
  int LDR_value = analogRead(LDR_IN);

  Serial.println(LDR_value);

  delay(500);

}
