#include <MyRealTimeClock.h>
#include <TimeLib.h>

MyRealTimeClock myRTC(6, 7, 8);

const int blancoSuave = 2;
const int blancoFuerte = 3;
const int azul = 4;
const int entradaManual = 12;
const int led = 13;
long HoraAmanecer = 8, MinutoAmanecer = 0, SegundoAmanecer = 0;
long HoraManana = 8, MinutoManana = 30, SegundoManana = 0;
long HoraMediaManana = 11, MinutoMediaManana = 0, SegundoMediaManana = 0;
long HoraMediodia = 12, MinutoMediodia = 30, SegundoMediodia = 0;
long HoraTarde = 13, MinutoTarde = 30, SegundoTarde = 0;
long HoraMediaTarde = 15, MinutoMediaTarde = 0, SegundoMediaTarde = 0;
long HoraAtardecer = 19, MinutoAtardecer = 30, SegundoAtardecer = 0;
long HoraNoche = 20, MinutoNoche = 0, SegundoNoche = 0;

boolean manual = false;

int ProgramaSeleccionado=1;
int value;

//Al arrancar arduino ayudan a dar la franja horaria en la que nos encontramos
boolean esAmanecer();
boolean esManana();
boolean esMediaManana();
boolean esMediodia();
boolean esTarde();
boolean esMediaTarde();
boolean esAtardecer();
boolean esNoche();

boolean esHoraAmanecer();
boolean esHoraManana();
boolean esHoraMediaManana();
boolean esHoraMediodia();
boolean esHoraMediaTarde();
boolean esHoraTarde();
boolean esHoraAtardecer();
boolean esHoraNoche();

void Programa1(int);
void Programa2(int);
void Programa3(int);
void Programa4(int);
void Programa5(int);

void setup() {
  Serial.begin(9600);
  //delay(10000);
  uint8_t segundos = 0;
  uint8_t minutos = 44;
  uint8_t horas = 10;
  uint8_t diasemana = 5;
  uint8_t diames = 7;
  uint8_t mes = 12;
  int ano = 2019;
  //myRTC.setDS1302Time(segundos, minutos, horas, diasemana, diames, mes, ano);
  pinMode(blancoSuave,OUTPUT);
  pinMode(blancoFuerte,OUTPUT);
  pinMode(azul,OUTPUT);
  pinMode(entradaManual,INPUT_PULLUP);
  digitalWrite(blancoSuave,HIGH);
  digitalWrite(blancoFuerte,HIGH);
  digitalWrite(azul,HIGH);
  digitalWrite(led,LOW);
  delay(1000);
  if (manual){
      digitalWrite(blancoSuave,LOW);
      digitalWrite(blancoFuerte,LOW);
      digitalWrite(azul,LOW);
      digitalWrite(led,HIGH);
  } else {
    if (esAmanecer()){
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
    } else if (esManana()) {
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
    } else if (esMediaManana()) {
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
    } else if (esMediodia()) {
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
    } else if (esTarde()) {
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
    } else if (esMediaTarde()) {
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
    } else if (esAtardecer()) {
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
    } else if (esNoche()) {
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
  delay(1000);
}

void loop() {
  delay(500);
  myRTC.updateTime();
  Serial.println("HoraActual: "+String(myRTC.hours)+":"+String(myRTC.minutes)+":"+String(myRTC.seconds));
  value = digitalRead(entradaManual);  //lectura digital de pin 
  if (value == LOW) {
    if (manual == true){
       Serial.println("Salgo de manual");
       manual = false;
          if (esAmanecer()){
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
            } else if (esManana()) {
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
            } else if (esMediaManana()) {
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
            } else if (esMediodia()) {
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
            } else if (esTarde()) {
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
            } else if (esMediaTarde()) {
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
            } else if (esAtardecer()) {
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
            } else if (esNoche()) {
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
            digitalWrite(led,LOW);
    } else {
      Serial.println("Entro en manual");
      manual = true;
      digitalWrite(blancoSuave,LOW);
      digitalWrite(blancoFuerte,LOW);
      digitalWrite(azul,LOW);
      digitalWrite(led,HIGH);
    }
  }
  if (!manual) {
    if (esHoraAmanecer()){
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
    } else if (esHoraManana()) {
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
    } else if (esHoraMediaManana()) {
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
    } else if (esHoraMediodia()) {
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
    } else if (esHoraTarde()) {
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
    } else if (esHoraMediaTarde()) {
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
    } else if (esHoraAtardecer()) {
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
    } else if (esHoraNoche()) {
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

boolean esAmanecer(){
  myRTC.updateTime();
  long hora_actual = long(myRTC.hours)*3600 + long(myRTC.minutes)*60 + long(myRTC.seconds);
  long hora_amanecer = HoraAmanecer*3600+MinutoAmanecer*60+SegundoAmanecer;
  long hora_manana = HoraManana*3600+MinutoManana*60+SegundoManana;
  //Serial.println("Es "+hora_actual+" Hora_manana"+hora_manana+" Hora_amanecer "+hora_amanecer);
  if ((hora_actual >= hora_amanecer) && (hora_actual < hora_manana)){
    return true;
  } else {
    return false;
  }
}

boolean esManana(){
  myRTC.updateTime();
  long hora_actual = long(myRTC.hours)*3600 + long(myRTC.minutes)*60 + long(myRTC.seconds);
  long hora_mediamanana = HoraMediaManana*3600+MinutoMediaManana*60+SegundoMediaManana;
  long hora_manana = HoraManana*3600+MinutoManana*60+SegundoManana;
  //Serial.println("Es "+hora_actual+" Hora_manana"+hora_manana+" Hora_mediamanana "+hora_mediamanana);
  if ((hora_actual >= hora_manana) && (hora_actual < hora_mediamanana)){
    return true;
  } else {
    return false;
  }
}

boolean esMediaManana(){
  myRTC.updateTime();
  long hora_actual = long(myRTC.hours)*3600 + long(myRTC.minutes)*60 + long(myRTC.seconds);
  long hora_mediamanana = HoraMediaManana*3600+MinutoMediaManana*60+SegundoMediaManana;
  long hora_mediodia = HoraMediodia*3600+MinutoMediodia*60+SegundoMediodia;
  //Serial.println("Es "+hora_actual+" Hora_mediodia"+hora_mediodia+" Hora_mediamanana "+hora_mediamanana);
  if ((hora_actual >= hora_mediamanana) && (hora_actual < hora_mediodia)){
    return true;
  } else {
    return false;
  }
}

boolean esMediodia(){
  myRTC.updateTime();
  long hora_actual = long(myRTC.hours)*3600 + long(myRTC.minutes)*60 + long(myRTC.seconds);
  long hora_mediodia = HoraMediodia*3600+MinutoMediodia*60+SegundoMediodia;
  long hora_tarde = HoraTarde*3600+MinutoTarde*60+SegundoTarde;
  //Serial.println("Es "+hora_actual+" Hora_mediodia"+hora_mediodia+" Hora_tarde "+hora_tarde);
  if ((hora_actual >= hora_mediodia) && (hora_actual < hora_tarde)){
    return true;
  } else {
    return false;
  }
}

boolean esTarde(){
  myRTC.updateTime();
  long hora_actual = long(myRTC.hours)*3600 + long(myRTC.minutes)*60 + long(myRTC.seconds);
  long hora_mediatarde = HoraMediaTarde*3600+MinutoMediaTarde*60+SegundoMediaTarde;
  long hora_tarde = HoraTarde*3600+MinutoTarde*60+SegundoTarde;
  //Serial.println("Es "+hora_actual+" Hora_tarde"+hora_tarde+" Hora_mediatarde "+hora_mediatarde);
  if ((hora_actual >= hora_tarde) && (hora_actual < hora_mediatarde)){
    return true;
  } else {
    return false;
  }
}

boolean esMediaTarde(){
  myRTC.updateTime();
  long hora_actual = long(myRTC.hours)*3600 + long(myRTC.minutes)*60 + long(myRTC.seconds);
  long hora_atardecer = HoraAtardecer*3600+MinutoAtardecer*60+SegundoAtardecer;
  long hora_mediatarde = HoraMediaTarde*3600+MinutoMediaTarde*60+SegundoMediaTarde;
  //Serial.println("Es "+String(hora_actual)+" Hora_atardecer"+String(hora_atardecer)+" Hora_mediatarde "+String(hora_mediatarde));
  if ((hora_actual >= hora_mediatarde) && (hora_actual < hora_atardecer)){
    return true;
  } else {
    return false;
  }
}
boolean esAtardecer(){
  myRTC.updateTime();
  long hora_actual = long(myRTC.hours)*3600 + long(myRTC.minutes)*60 + long(myRTC.seconds);
  long hora_atardecer = HoraAtardecer*3600+MinutoAtardecer*60+SegundoAtardecer;
  long hora_noche = HoraNoche*3600+MinutoNoche*60+SegundoNoche;
  //Serial.println("Es "+String(hora_actual)+" Hora_noche "+String(hora_noche)+" Hora_amanecer "+String(hora_atardecer));
  if ((hora_actual >= hora_atardecer) && (hora_actual < hora_noche)){
    return true;
  } else {
    return false;
  }
}

boolean esNoche(){
  myRTC.updateTime();
  long hora_actual = long(myRTC.hours)*3600 + long(myRTC.minutes)*60 + long(myRTC.seconds);
  long hora_amanecer = HoraAmanecer*3600+MinutoAmanecer*60+SegundoAmanecer;
  long hora_noche = HoraNoche*3600+MinutoNoche*60+SegundoNoche;
  if ((hora_actual >= hora_noche) || (hora_actual < hora_amanecer)){
    return true;
  } else {
    return false;
  }
}

boolean esHoraAmanecer(){
  myRTC.updateTime();
  if ((myRTC.hours==HoraAmanecer) && (myRTC.minutes==MinutoAmanecer) && (myRTC.seconds==SegundoAmanecer)){
    return true;
  } else {
    return false;
  }
}

boolean esHoraManana(){
  myRTC.updateTime();
  if ((myRTC.hours==HoraManana) && (myRTC.minutes==MinutoManana) && (myRTC.seconds==SegundoManana)){
    return true;
  } else {
    return false;
  }
}

boolean esHoraMediaManana(){
  myRTC.updateTime();
  if ((myRTC.hours==HoraMediaManana) && (myRTC.minutes==MinutoMediaManana) && (myRTC.seconds==SegundoMediaManana)){
    return true;
  } else {
    return false;
  }
}

boolean esHoraMediodia(){
  myRTC.updateTime();
  if ((myRTC.hours==HoraMediodia) && (myRTC.minutes==MinutoMediodia) && (myRTC.seconds==SegundoMediodia)){
    return true;
  } else {
    return false;
  }
}

boolean esHoraTarde(){
  myRTC.updateTime();
  if ((myRTC.hours==HoraTarde) && (myRTC.minutes==MinutoTarde) && (myRTC.seconds==SegundoTarde)){
    return true;
  } else {
    return false;
  }
}

boolean esHoraMediaTarde(){
  myRTC.updateTime();
  if ((myRTC.hours==HoraMediaTarde) && (myRTC.minutes==MinutoMediaTarde) && (myRTC.seconds==SegundoMediaTarde)){
    return true;
  } else {
    return false;
  }
}

boolean esHoraAtardecer(){
  myRTC.updateTime();
  if ((myRTC.hours==HoraAtardecer) && (myRTC.minutes==MinutoAtardecer) && (myRTC.seconds==SegundoAtardecer)){
    return true;
  } else {
    return false;
  }
}

boolean esHoraNoche(){
  myRTC.updateTime();
  if ((myRTC.hours==HoraNoche) && (myRTC.minutes==MinutoNoche) && (myRTC.seconds==SegundoNoche)){
    return true;
  } else {
    return false;
  }
}
