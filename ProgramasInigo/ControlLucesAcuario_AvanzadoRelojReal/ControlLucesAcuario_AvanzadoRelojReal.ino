#include <MyRealTimeClock.h>
#include <TimeLib.h>

MyRealTimeClock myRTC(3, 4, 5);
  
const int blancoSuave = 0;
const int blancoFuerte = 1;
const int azul = 2;
long HoraAmanecer = 7, MinutoAmanecer = 0, SegundoAmanecer = 0;
long HoraManana = 8, MinutoManana = 0, SegundoManana = 0;
long HoraMediaManana = 10, MinutoMediaManana = 0, SegundoMediaManana = 0;
long HoraMediodia = 11, MinutoMediodia = 0, SegundoMediodia = 0;
long HoraTarde = 13, MinutoTarde = 0, SegundoTarde = 0;
long HoraMediaTarde = 14, MinutoMediaTarde = 0, SegundoMediaTarde = 0;
long HoraAtardecer = 17, MinutoAtardecer = 30, SegundoAtardecer = 0;
long HoraNoche = 19, MinutoNoche = 0, SegundoNoche = 0;

int ProgramaSeleccionado=2;

//Al arrancar arduino ayudan a dar la franja horaria en la que nos encontramos
boolean esAmanecer(time_t);
boolean esManana(time_t);
boolean esMediaManana(time_t);
boolean esMediodia(time_t);
boolean esTarde(time_t);
boolean esMediaTarde(time_t);
boolean esAtardecer(time_t);
boolean esNoche(time_t);

boolean esHoraAmanecer(time_t);
boolean esHoraManana(time_t);
boolean esHoraMediaManana(time_t);
boolean esHoraMediodia(time_t);
boolean esHoraMediaTarde(time_t);
boolean esHoraTarde(time_t);
boolean esHoraAtardecer(time_t);
boolean esHoraNoche(time_t);

void Programa1(int);
void Programa2(int);
void Programa3(int);
void Programa4(int);
void Programa5(int);

void setup() {
  Serial.begin(9600);
  pinMode(blancoSuave,OUTPUT);
  pinMode(blancoFuerte,OUTPUT);
  pinMode(azul,OUTPUT);
  digitalWrite(blancoSuave,HIGH);
  digitalWrite(blancoFuerte,HIGH);
  digitalWrite(azul,HIGH);
  myRTC.setDS1302Time(00, 59, 10, 12 , 10, 07, 2015);
  myRTC.updateTime();
  if (esAmanecer(t)){
    switch (ProgramaSeleccionado) {
      case 1:
        Programa1(1);
        break;
      case 2:
        Programa2(1);
        break;
      case 3:
        Programa3(1);
        break; 
      case 4:
        Programa4(1);
        break;
      case 5:
        Programa5(1);  
        break;
    } 
  } else if (esManana(t)) {
    switch (ProgramaSeleccionado) {
      case 1:
        Programa1(2);
        break;
      case 2:
        Programa2(2);
        break;
      case 3:
        Programa3(2);
        break;
      case 4:
        Programa4(2);
        break;
      case 5:
        Programa5(2);
        break;  
    }      
  } else if (esMediaManana(t)) {
    switch (ProgramaSeleccionado) {
      case 1:
        Programa1(3);
        break;
      case 2:
        Programa2(3);
        break;
      case 3:
        Programa3(3);
        break;
      case 4:
        Programa4(3);
        break;
      case 5:
        Programa5(3);
        break;  
    } 
  } else if (esMediodia(t)) {
    switch (ProgramaSeleccionado) {
      case 1:
        Programa1(4);
        break;
      case 2:
        Programa2(4);
        break;
      case 3:
        Programa3(4);
        break;
      case 4:
        Programa4(4);
        break;
      case 5:
        Programa5(4);
        break;  
    }      
  } else if (esTarde(t)) {
    switch (ProgramaSeleccionado) {
      case 1:
        Programa1(5);
        break;
      case 2:
        Programa2(5);
        break;
      case 3:
        Programa3(5);
        break;
      case 4:
        Programa4(5);
        break;
      case 5:
        Programa5(5);
        break;  
    }  
  } else if (esMediaTarde(t)) {
    switch (ProgramaSeleccionado) {
      case 1:
        Programa1(6);
        break;
      case 2:
        Programa2(6);
        break;
      case 3:
        Programa3(6);
        break;
      case 4:
        Programa4(6);
        break;
      case 5:
        Programa5(6);
        break;  
    } 
  } else if (esAtardecer(t)) {
    switch (ProgramaSeleccionado) {
      case 1:
        Programa1(7);
        break;
      case 2:
        Programa2(7);
        break;
      case 3:
        Programa3(7);
        break;
      case 4:
        Programa4(7);
        break;
      case 5:
        Programa5(7);
        break;  
    }   
  } else if (esNoche(t)) {
    switch (ProgramaSeleccionado) {
      case 1:
        Programa1(8);
        break;
      case 2:
        Programa2(8);
        break;
      case 3:
        Programa3(8);
        break;
      case 4:
        Programa4(8);
        break;
      case 5:
        Programa5(8);
        break;  
    }       
  }

  //delay(5000);
}

void loop() {
  myRTC.updateTime();
  time_t t = now();
  Serial.println(String(myRTC.day)+"/"+String(myRTC.month)+"/"+String(myRTC.year)+"   "+String(myRTC.hour)+":"+String(myRTC.minute)+":"+String(myRTC.second));
    if (esHoraAmanecer(t)){
    switch (ProgramaSeleccionado) {
      case 1:
        Programa1(1);
        break;
      case 2:
        Programa2(1);
        break;
      case 3:
        Programa3(1);
        break;
      case 4:
        Programa4(1);
        break;
      case 5:
        Programa5(1);
        break;  
    }   
  } else if (esHoraManana(t)) {
    switch (ProgramaSeleccionado) {
      case 1:
        Programa1(2);
        break;
      case 2:
        Programa2(2);
        break;
      case 3:
        Programa3(2);
        break;
      case 4:
        Programa4(2);
        break;
      case 5:
        Programa5(2);
        break;  
    }      
  } else if (esHoraMediaManana(t)) {
      switch (ProgramaSeleccionado) {
          case 1:
            Programa1(3);
            break;
          case 2:
            Programa2(3);
            break;
          case 3:
            Programa3(3);
            break;
          case 4:
            Programa4(3);
            break;
          case 5:
            Programa5(3);
            break;  
        }      
  } else if (esHoraMediodia(t)) {
      switch (ProgramaSeleccionado) {
          case 1:
            Programa1(4);
            break;
          case 2:
            Programa2(4);
            break;
          case 3:
            Programa3(4);
            break;
          case 4:
            Programa4(4);
            break;
          case 5:
            Programa5(4);
            break;  
        }  
  } else if (esHoraTarde(t)) {
      switch (ProgramaSeleccionado) {
          case 1:
            Programa1(5);
            break;
          case 2:
            Programa2(5);
            break;
          case 3:
            Programa3(5);
            break;
          case 4:
            Programa4(5);
            break;
          case 5:
            Programa5(5);
            break;  
        }     
  } else if (esHoraMediaTarde(t)) {
      switch (ProgramaSeleccionado) {
          case 1:
            Programa1(6);
            break;
          case 2:
            Programa2(6);
            break;
          case 3:
            Programa3(6);
            break;
          case 4:
            Programa4(6);
            break;
          case 5:
            Programa5(6);
            break;  
        }      
  } else if (esHoraAtardecer(t)) {
      switch (ProgramaSeleccionado) {
          case 1:
            Programa1(7);
            break;
          case 2:
            Programa2(7);
            break;
          case 3:
            Programa3(7);
            break;
          case 4:
            Programa4(7);
            break;
          case 5:
            Programa5(7);
            break;  
        }      
  } else if (esHoraNoche(t)) {
      switch (ProgramaSeleccionado) {
          case 1:
            Programa1(8);
            break;
          case 2:
            Programa2(8);
            break;
          case 3:
            Programa3(8);
            break;
          case 4:
            Programa4(8);
            break;
          case 5:
            Programa5(8);
            break;  
        }      
  }      
}

void Programa1(int hora){
  switch (hora) {
      case 1: //Amanecer
        digitalWrite(blancoSuave,HIGH);
        digitalWrite(blancoFuerte,HIGH);
        digitalWrite(azul,LOW);   
        break; 
      case 2: //Mañana
        digitalWrite(blancoSuave,LOW);
        digitalWrite(blancoFuerte,HIGH);
        digitalWrite(azul,LOW);
        break;      
      case 3: //Media Mañana
        digitalWrite(blancoSuave,LOW);
        digitalWrite(blancoFuerte,HIGH);
        digitalWrite(azul,LOW);
        break;    
      case 4: //Mediodia
        digitalWrite(blancoSuave,HIGH);
        digitalWrite(blancoFuerte,LOW);
        digitalWrite(azul,LOW);
        break;      
      case 5: //Tarde
        digitalWrite(blancoSuave,LOW);
        digitalWrite(blancoFuerte,HIGH);
        digitalWrite(azul,LOW);
        break;
      case 6: //Media tarde
        digitalWrite(blancoSuave,LOW);
        digitalWrite(blancoFuerte,HIGH);
        digitalWrite(azul,LOW);
        break;  
      case 7: //Atardecer
        digitalWrite(blancoSuave,HIGH);
        digitalWrite(blancoFuerte,HIGH);
        digitalWrite(azul,LOW);
        break;      
      case 8: //Noche
        digitalWrite(blancoSuave,HIGH);
        digitalWrite(blancoFuerte,HIGH);
        digitalWrite(azul,HIGH);
        break;
  }
}

void Programa2(int hora){
  switch (hora) {
      case 1: //Amanecer
        digitalWrite(blancoSuave,HIGH);
        digitalWrite(blancoFuerte,HIGH);
        digitalWrite(azul,LOW);
        break;    
      case 2: //Mañana
        digitalWrite(blancoSuave,LOW);
        digitalWrite(blancoFuerte,HIGH);
        digitalWrite(azul,LOW);
        break;      
      case 3: //Media Mañana
        digitalWrite(blancoSuave,HIGH);
        digitalWrite(blancoFuerte,LOW);
        digitalWrite(azul,LOW);
        break;    
      case 4: //Mediodia
        digitalWrite(blancoSuave,LOW);
        digitalWrite(blancoFuerte,LOW);
        digitalWrite(azul,LOW);
        break;      
      case 5: //Tarde
        digitalWrite(blancoSuave,HIGH);
        digitalWrite(blancoFuerte,LOW);
        digitalWrite(azul,LOW);
        break;    
      case 6: //Media tarde
        digitalWrite(blancoSuave,LOW);
        digitalWrite(blancoFuerte,HIGH);
        digitalWrite(azul,LOW);
        break;  
      case 7: //Atardecer
        digitalWrite(blancoSuave,HIGH);
        digitalWrite(blancoFuerte,HIGH);
        digitalWrite(azul,LOW);
        break;      
      case 8: //Noche
        digitalWrite(blancoSuave,HIGH);
        digitalWrite(blancoFuerte,HIGH);
        digitalWrite(azul,HIGH);
        break;      
  }
}

void Programa3(int hora){
  
}

void Programa4(int hora){
  
}

void Programa5(int hora){
  
}

boolean esAmanecer(time_t actual){
  long hora_actual = long(hour(actual))*3600 + long(minute(actual))*60 + long(second(actual));
  long hora_amanecer = HoraAmanecer*3600+MinutoAmanecer*60+SegundoAmanecer;
  long hora_manana = HoraManana*3600+MinutoManana*60+SegundoManana;
  if ((hora_actual >= hora_amanecer) && (hora_actual < hora_manana)){
    return true;
  } else {
    return false;
  }
}

boolean esManana(time_t actual){
  long hora_actual = long(hour(actual))*3600 + long(minute(actual))*60 + long(second(actual));
  long hora_mediamanana = HoraMediaManana*3600+MinutoMediaManana*60+SegundoMediaManana;
  long hora_manana = HoraManana*3600+MinutoManana*60+SegundoManana;
  if ((hora_actual >= hora_manana) && (hora_actual < hora_mediamanana)){
    return true;
  } else {
    return false;
  }
}

boolean esMediaManana(time_t actual){
  long hora_actual = long(hour(actual))*3600 + long(minute(actual))*60 + long(second(actual));
  long hora_mediamanana = HoraMediaManana*3600+MinutoMediaManana*60+SegundoMediaManana;
  long hora_mediodia = HoraMediodia*3600+MinutoMediodia*60+SegundoMediodia;
  if ((hora_actual >= hora_mediamanana) && (hora_actual < hora_mediodia)){
    return true;
  } else {
    return false;
  }
}

boolean esMediodia(time_t actual){
  long hora_actual = long(hour(actual))*3600 + long(minute(actual))*60 + long(second(actual));
  long hora_mediodia = HoraMediodia*3600+MinutoMediodia*60+SegundoMediodia;
  long hora_tarde = HoraTarde*3600+MinutoTarde*60+SegundoTarde;
  if ((hora_actual >= hora_mediodia) && (hora_actual < hora_tarde)){
    return true;
  } else {
    return false;
  }
}

boolean esTarde(time_t actual){
  long hora_actual = long(hour(actual))*3600 + long(minute(actual))*60 + long(second(actual));
  long hora_mediatarde = HoraMediaTarde*3600+MinutoMediaTarde*60+SegundoMediaTarde;
  long hora_tarde = HoraTarde*3600+MinutoTarde*60+SegundoTarde;
  if ((hora_actual >= hora_tarde) && (hora_actual < hora_mediatarde)){
    return true;
  } else {
    return false;
  }
}

boolean esMediaTarde(time_t actual){
  long hora_actual = long(hour(actual))*3600 + long(minute(actual))*60 + long(second(actual));
  long hora_atardecer = HoraAtardecer*3600+MinutoAtardecer*60+SegundoAtardecer;
  long hora_mediatarde = HoraMediaTarde*3600+MinutoMediaTarde*60+SegundoMediaTarde;
  if ((hora_actual >= hora_mediatarde) && (hora_actual < hora_atardecer)){
    return true;
  } else {
    return false;
  }
}
boolean esAtardecer(time_t actual){
  long hora_actual = long(hour(actual))*3600 + long(minute(actual))*60 + long(second(actual));
  long hora_atardecer = HoraAtardecer*3600+MinutoAtardecer*60+SegundoAtardecer;
  long hora_noche = HoraNoche*3600+MinutoNoche*60+SegundoNoche;
  if ((hora_actual >= hora_atardecer) && (hora_actual < hora_noche)){
    return true;
  } else {
    return false;
  }
}

boolean esNoche(time_t actual){
  long hora_actual = long(hour(actual))*3600 + long(minute(actual))*60 + long(second(actual));
  long hora_amanecer = HoraAmanecer*3600+MinutoAmanecer*60+SegundoAmanecer;
  long hora_noche = HoraNoche*3600+MinutoNoche*60+SegundoNoche;
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

boolean esHoraMediaManana(time_t mediamanana){
  if ((hour(mediamanana)==HoraMediaManana) && (minute(mediamanana)==MinutoMediaManana) && (second(mediamanana)==SegundoMediaManana)){
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

boolean esHoraMediaTarde(time_t mediatarde){
  if ((hour(mediatarde)==HoraMediaTarde) && (minute(mediatarde)==MinutoMediaTarde) && (second(mediatarde)==SegundoMediaTarde)){
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
