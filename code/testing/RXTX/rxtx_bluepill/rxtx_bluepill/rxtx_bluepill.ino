void setup() {
   Serial2.begin(9600);
}

void loop() {
   Serial2.write("1");
   delay(3000);
   Serial2.write("0");
   delay(3000);
   Serial2.write("1");
   delay(3000);
   Serial2.write("0");
   delay(3000);
}
