#define piezo_PIN PA1

void piezo_init(){
   pinMode(piezo_PIN, OUTPUT);
}

void piezo_ON(int ON_time, int frequency){
   analogWrite(piezo_PIN, frequency);
   delay(ON_time);
   analogWrite(piezo_PIN, 0);
}

void setup() {
   piezo_init();
}

void loop() {
   piezo_ON(2000, 1000);
   delay(1000);
}
