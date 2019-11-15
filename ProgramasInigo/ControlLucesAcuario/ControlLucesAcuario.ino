#include <TimeLib.h>

const int blancoSuave = 2;
const int blancoFuerte = 3;
const int azul = 4;
const int HoraAmanecer = 10, MinutoAmanecer = 50, SegundoAmanecer = 10;
const int HoraManana = 10, MinutoManana = 50, SegundoManana = 20;
const int HoraMediodia = 10, MinutoMediodia = 50, SegundoMediodia = 30;
const int HoraTarde = 10, MinutoTarde = 50, SegundoTarde = 40;
const int HoraAtardecer = 10, MinutoAtardecer = 50, SegundoAtardecer = 50;
const int HoraNoche = 10, MinutoNoche = 51, SegundoNoche = 0;

//Al arrancar arduino ayudan a dar la franja horaria en la que nos encontramos
boolean esAmanecer(time_t);
boolean esManana(time_t);
boolean esMediodia(time_t);
boolean esTarde(time_t);
boolean esAtardecer(time_t);
boolean esNoche(time_t);

boolean esHoraAmanecer(time_t);
boolean esHoraManana(time_t);
boolean esHoraMediodia(time_t);
boolean esHoraTarde(time_t);
boolean esHoraAtardecer(time_t);
boolean esHoraNoche(time_t);

void setup() {
  Serial.begin(9600);
  setTime(10, 50, 0, 8, 9, 2019);
  // put your setup code here, to run once:
  pinMode(blancoSuave,OUTPUT);
  pinMode(blancoFuerte,OUTPUT);
  pinMode(azul,OUTPUT);
  digitalWrite(blancoSuave,HIGH);
  digitalWrite(blancoFuerte,HIGH);
  digitalWrite(azul,HIGH);
  time_t t = now();
  if (esAmanecer(t)){
        digitalWrite(blancoSuave,HIGH);
        digitalWrite(blancoFuerte,HIGH);
        digitalWrite(azul,LOW);    
  } else if (esManana(t)) {
        digitalWrite(blancoSuave,LOW);
        digitalWrite(blancoFuerte,HIGH);
        digitalWrite(azul,LOW);      
  } else if (esMediodia(t)) {
        digitalWrite(blancoSuave,HIGH);
        digitalWrite(blancoFuerte,LOW);
        digitalWrite(azul,LOW);      
  } else if (esTarde(t)) {
        digitalWrite(blancoSuave,LOW);
        digitalWrite(blancoFuerte,HIGH);
        digitalWrite(azul,LOW);  
  } else if (esAtardecer(t)) {
        digitalWrite(blancoSuave,HIGH);
        digitalWrite(blancoFuerte,HIGH);
        digitalWrite(azul,LOW);      
  } else if (esNoche(t)) {
        digitalWrite(blancoSuave,HIGH);
        digitalWrite(blancoFuerte,HIGH);
        digitalWrite(azul,HIGH);      
  }
}

void loop() {
  time_t t = now();
  if (esHoraAmanecer(t)){
        digitalWrite(blancoSuave,HIGH);
        digitalWrite(blancoFuerte,HIGH);
        digitalWrite(azul,LOW);    
  } else if (esHoraManana(t)) {
        digitalWrite(blancoSuave,LOW);
        digitalWrite(blancoFuerte,HIGH);
        digitalWrite(azul,LOW);      
  } else if (esHoraMediodia(t)) {
        digitalWrite(blancoSuave,HIGH);
        digitalWrite(blancoFuerte,LOW);
        digitalWrite(azul,LOW);      
  } else if (esHoraTarde(t)) {
        digitalWrite(blancoSuave,LOW);
        digitalWrite(blancoFuerte,HIGH);
        digitalWrite(azul,LOW);  
  } else if (esHoraAtardecer(t)) {
        digitalWrite(blancoSuave,HIGH);
        digitalWrite(blancoFuerte,HIGH);
        digitalWrite(azul,LOW);      
  } else if (esHoraNoche(t)) {
        digitalWrite(blancoSuave,HIGH);
        digitalWrite(blancoFuerte,HIGH);
        digitalWrite(azul,HIGH);      
  }
  //Serial.print("Son las:  ");
  //Serial.println(String(hour(t))+":"+String(minute(t))+":"+String(second(t)));
  // put your main code here, to run repeatedly:
  //digitalWrite(rele3,HIGH);
  //digitalWrite(rele1,LOW);
  //digitalWrite(LED_BUILTIN,HIGH);
  //delay(3000);
  //digitalWrite(rele1,HIGH);
  //digitalWrite(rele2,LOW);
  //digitalWrite(LED_BUILTIN,LOW);
  //delay(3000);
  //digitalWrite(rele2,HIGH);
  //digitalWrite(rele3,LOW);
  //digitalWrite(LED_BUILTIN,LOW);
  //delay(3000);
}

boolean esAmanecer(time_t amanecer){
  int hora_actual = hour(amanecer)*3600 + minute(amanecer)*60 + second(amanecer);
  int hora_amanecer = HoraAmanecer*3600+MinutoAmanecer*60+SegundoAmanecer;
  int hora_manana = HoraManana*3600+MinutoManana*60+SegundoManana;
  if ((hora_actual >= hora_amanecer) && (hora_actual < hora_manana)){
    return true;
  } else {
    return false;
  }
}

boolean esManana(time_t manana){
  int hora_actual = hour(manana)*3600 + minute(manana)*60 + second(manana);
  int hora_mediodia = HoraMediodia*3600+MinutoMediodia*60+SegundoMediodia;
  int hora_manana = HoraManana*3600+MinutoManana*60+SegundoManana;
  if ((hora_actual >= hora_manana) && (hora_actual < hora_mediodia)){
    return true;
  } else {
    return false;
  }
}

boolean esMediodia(time_t mediodia){
  int hora_actual = hour(mediodia)*3600 + minute(mediodia)*60 + second(mediodia);
  int hora_mediodia = HoraMediodia*3600+MinutoMediodia*60+SegundoMediodia;
  int hora_tarde = HoraTarde*3600+MinutoTarde*60+SegundoTarde;
  if ((hora_actual >= hora_mediodia) && (hora_actual < hora_tarde)){
    return true;
  } else {
    return false;
  }
}

boolean esTarde(time_t tarde){
  int hora_actual = hour(tarde)*3600 + minute(tarde)*60 + second(tarde);
  int hora_atardecer = HoraAtardecer*3600+MinutoAtardecer*60+SegundoAtardecer;
  int hora_tarde = HoraTarde*3600+MinutoTarde*60+SegundoTarde;
  if ((hora_actual >= hora_tarde) && (hora_actual < hora_atardecer)){
    return true;
  } else {
    return false;
  }
}

boolean esAtardecer(time_t atardecer){
  int hora_actual = hour(atardecer)*3600 + minute(atardecer)*60 + second(atardecer);
  int hora_atardecer = HoraAtardecer*3600+MinutoAtardecer*60+SegundoAtardecer;
  int hora_noche = HoraNoche*3600+MinutoNoche*60+SegundoNoche;
  if ((hora_actual >= hora_atardecer) && (hora_actual < hora_noche)){
    return true;
  } else {
    return false;
  }
}

boolean esNoche(time_t noche){
  int hora_actual = hour(noche)*3600 + minute(noche)*60 + second(noche);
  int hora_amanecer = HoraAmanecer*3600+MinutoAmanecer*60+SegundoAmanecer;
  int hora_noche = HoraNoche*3600+MinutoNoche*60+SegundoNoche;
  if ((hora_actual >= hora_noche) || (hora_actual < hora_amanecer)){
    return true;
  } else {
    return false;
  }
}

boolean esHoraAmanecer(time_t amanecer){
  if ((hour(amanecer)==HoraAmanecer) && (minute(amanecer)==MinutoAmanecer) && (second(amanecer)==SegundoAmanecer)){
    return true;
  } else {
    return false;
  }
}

boolean esHoraManana(time_t manana){
  if ((hour(manana)==HoraManana) && (minute(manana)==MinutoManana) && (second(manana)==SegundoManana)){
    return true;
  } else {
    return false;
  }
}

boolean esHoraMediodia(time_t mediodia){
  if ((hour(mediodia)==HoraMediodia) && (minute(mediodia)==MinutoMediodia) && (second(mediodia)==SegundoMediodia)){
    return true;
  } else {
    return false;
  }
}

boolean esHoraTarde(time_t tarde){
  if ((hour(tarde)==HoraTarde) && (minute(tarde)==MinutoTarde) && (second(tarde)==SegundoTarde)){
    return true;
  } else {
    return false;
  }
}

boolean esHoraAtardecer(time_t atardecer){
  if ((hour(atardecer)==HoraAtardecer) && (minute(atardecer)==MinutoAtardecer) && (second(atardecer)==SegundoAtardecer)){
    return true;
  } else {
    return false;
  }
}

boolean esHoraNoche(time_t noche){
  if ((hour(noche)==HoraNoche) && (minute(noche)==MinutoNoche) && (second(noche)==SegundoNoche)){
    return true;
  } else {
    return false;
  }
}
