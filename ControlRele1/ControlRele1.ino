const int rele1 = 2;
const int rele2 = 3;
const int rele3 = 4;


void setup() {
  // put your setup code here, to run once:
  pinMode(rele1,OUTPUT);
  pinMode(rele2,OUTPUT);
  pinMode(rele3,OUTPUT);
  //pinMode(LED_BUILTIN,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(rele3,LOW);
  digitalWrite(rele1,HIGH);
  //digitalWrite(LED_BUILTIN,HIGH);
  delay(3000);
  digitalWrite(rele1,LOW);
  digitalWrite(rele2,HIGH);
  //digitalWrite(LED_BUILTIN,LOW);
  delay(3000);
  digitalWrite(rele2,LOW);
  digitalWrite(rele3,HIGH);
  //digitalWrite(LED_BUILTIN,LOW);
  delay(3000);
}
