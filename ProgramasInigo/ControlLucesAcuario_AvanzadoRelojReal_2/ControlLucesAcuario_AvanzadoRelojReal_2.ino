#include <LiquidCrystal.h>
#include <MyRealTimeClock.h>
#include <TimeLib.h>

MyRealTimeClock myRTC(3, 4, 5);
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
  
const int blancoSuave = 0;
const int blancoFuerte = 1;
const int azul = 2;
const int iluminaciondisplay = 13;
long HoraAmanecer = 7, MinutoAmanecer = 0, SegundoAmanecer = 0;
long HoraManana = 8, MinutoManana = 0, SegundoManana = 0;
long HoraMediaManana = 10, MinutoMediaManana = 0, SegundoMediaManana = 0;
long HoraMediodia = 11, MinutoMediodia = 0, SegundoMediodia = 0;
long HoraTarde = 13, MinutoTarde = 0, SegundoTarde = 0;
long HoraMediaTarde = 14, MinutoMediaTarde = 0, SegundoMediaTarde = 0;
long HoraAtardecer = 17, MinutoAtardecer = 30, SegundoAtardecer = 0;
long HoraNoche = 19, MinutoNoche = 0, SegundoNoche = 0;

int ProgramaSeleccionado=1;
int value, opcion;
int horaajustada;
int minutoajustado;
int segundoajustado;
int programaajustado;

void setHoraFecha(int, int, int, int, int, int, int);

void initProgram();

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

void enterMenu();
void changeTime();
void setProgram();
void setManual();

String message_hour;

boolean displayapagado;

void setup() {
  Serial.begin(9600);
  pinMode(blancoSuave,OUTPUT);
  pinMode(blancoFuerte,OUTPUT);
  pinMode(azul,OUTPUT);
  pinMode(iluminaciondisplay,OUTPUT);
  digitalWrite(blancoSuave,HIGH);
  digitalWrite(blancoFuerte,HIGH);
  digitalWrite(azul,HIGH);
  digitalWrite(iluminaciondisplay,HIGH);
  pinMode(A0, INPUT_PULLUP);   //Menu
  pinMode(A1, INPUT_PULLUP);   //Back
  pinMode(A2, INPUT_PULLUP);   //Set
  pinMode(A3, INPUT_PULLUP);   //Up
  pinMode(A4, INPUT_PULLUP);   //Dw
  
  initProgram();
  lcd.begin(16,2);
  lcd.home();
  lcd.setCursor(0,0);
  // IMPRIMIR "Hola Mundo" EN LA PRIMERA LINEA
  lcd.print("SeaLampControl");
  lcd.setCursor(0,1);
  lcd.print(String(myRTC.hours)+":"+String(myRTC.minutes)+":"+String(myRTC.seconds)+"             ");
  Serial.println(String(myRTC.hours)+":"+String(myRTC.minutes)+":"+String(myRTC.seconds)+"             ");
  delay(1000);
  digitalWrite(iluminaciondisplay, LOW);
  displayapagado=true;
}

void loop() {
  lcd.setCursor(0,1);
  value = digitalRead(A0);  //lectura digital de pin 
  if (value == LOW) {
      delay(500);
      if (displayapagado==false) {
        lcd.print("Menu        ");
        enterMenu();
      }       
  }
  value = digitalRead(A2);  //lectura digital de pin 
  if (value == LOW) {
      if (displayapagado==true) {
        Serial.println("Oh");
        delay(500);
        digitalWrite(iluminaciondisplay, HIGH); 
        displayapagado=false;
      } else {
        Serial.println("Ah");
        delay(500);
        digitalWrite(iluminaciondisplay, LOW);
        displayapagado=true;   
      }
  }
  myRTC.updateTime();
  lcd.setCursor(0,0);
  lcd.print("SeaLampControl                    ");
  lcd.setCursor(0,1);
  //lcd.print(String(myRTC.hours)+":"+String(myRTC.minutes)+":"+String(myRTC.seconds)+"           ");
  Serial.println(String(myRTC.hours)+":"+String(myRTC.minutes)+":"+String(myRTC.seconds)+"           ");
  //Serial.println(String(myRTC.dayofmonth)+"/"+String(myRTC.month)+"/"+String(myRTC.year)+"   "+String(myRTC.hours)+":"+String(myRTC.minutes)+":"+String(myRTC.seconds)+"            ");
  if (esHoraAmanecer()){
    lcd.print(" Amanecer");
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
    lcd.print(" Manana1");
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
    lcd.print("  Manana2");
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
    lcd.print("  Mediodia");
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
    lcd.print("  Tarde1");
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
    lcd.print("  Tarde2");
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
    lcd.print("  Atardecer");
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
      lcd.print("  Noche");
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

void initProgram(){
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

void enterMenu(){
  opcion = 1;
  while (opcion > 0){
     delay(500);
     lcd.setCursor(0,0);
     switch (opcion) {
            case 1:
              lcd.print("[ ] Set Time    ");
              break;
            case 2:
              lcd.print("[ ] Set Program ");
              break;
            case 3:
              lcd.print("[ ] Set Manual  ");
              break;
            case 4:
              lcd.print("[ ] Exit        ");
              break;
      }
      lcd.setCursor(0,1);
      lcd.print("[OK] [+/-] [BK] ");
      unsigned long finish = millis()+60000UL; // cargo a start con el valor +10mil milisegundos
      while (millis() < finish) {
         // lo que este aqui dentro tiene 10 segundos para ejecutarse
         // o puedes salir con break*/
        value = digitalRead(A1);  //back
        if (value == LOW) {
            opcion = 0;
            break;
        }
        value = digitalRead(A2);  //set 
        if (value == LOW) {
            switch (opcion) {
              case 1:
                lcd.setCursor(0,0);
                lcd.print("[*] Set Time    ");
                delay(1000);
                changeTime();
                opcion = 4;
                break;
              case 2:
                lcd.setCursor(0,0);
                lcd.print("[*] Set Program ");
                delay(1000);
                setProgram();
                opcion = 4;
                break;
              case 3:
                lcd.setCursor(0,0);
                lcd.print("[*] Set Manual   ");
                delay(1000);
                setManual();
                opcion = 4;
                break;
              case 4:
                lcd.setCursor(0,0);
                lcd.print("[*] Exit         ");
                delay(1000);
                opcion = 0;
                break;
            }
           break;
        }
        value = digitalRead(A3);  //up 
        if (value == LOW) {
            opcion++;
            if (opcion == 5){
              opcion = 1;
            }
            //delay(1000);
            break;
        }
        value = digitalRead(A4);  //dw 
        if (value == LOW) {
            opcion--;
            if (opcion == 0){
              opcion = 4;
            }
            //delay(1000);
            break;
        }
      }
    }
}

void changeTime(){
    lcd.setCursor(0,0);
    horaajustada = myRTC.hours;
    minutoajustado = myRTC.minutes;
    segundoajustado = myRTC.seconds;
    lcd.print("Set time:       ");
    int opcionhora = 1;
    //unsigned long finishhora = millis()+120000UL; // cargo a start con el valor +10mil milisegundos
    //while (millis() < finishhora || opcionhora != 0) {
    while (opcionhora != 0) {
          delay(200);
          lcd.setCursor(0,1);
          if (second()%2==0){
            lcd.print(String(horaajustada)+":"+String(minutoajustado)+":"+String(segundoajustado)+"           ");
          } else {
            switch (opcionhora) {
                case 1: //set hora
                  lcd.print("__:"+String(minutoajustado)+":"+String(segundoajustado)+"           ");
                  break;
                case 2: //set minuto
                  lcd.print(String(horaajustada)+":__:"+String(segundoajustado)+"           ");
                  break;
                case 3:
                  lcd.print(String(horaajustada)+":"+String(minutoajustado)+":__           ");
                  break;
              }
            
          }
           // lo que este aqui dentro tiene 10 segundos para ejecutarse
           // o puedes salir con break
          value = digitalRead(A1);  //back
          if (value == LOW) {
              horaajustada = myRTC.hours;
              minutoajustado = myRTC.minutes;
              segundoajustado = myRTC.seconds;
              opcionhora = 0;
          }
          value = digitalRead(A2);  //set 
          if (value == LOW) {
              switch (opcionhora) {
                case 1: //set hora
                  opcionhora = 2;
                  break;
                case 2: //set minuto
                  opcionhora = 3;
                  break;
                case 3:
                  opcionhora = 0;
                  break;
              }
          }
          value = digitalRead(A3);  //up 
          if (value == LOW) {
              switch (opcionhora) {
                case 1: //set hora
                  horaajustada++;
                  if (horaajustada>=24){
                    horaajustada=0;
                  }
                  break;
                case 2: //set minuto
                  minutoajustado++;
                  if (minutoajustado>=60){
                    minutoajustado=0;
                  }
                  break;
                case 3:
                  segundoajustado++;
                  if (segundoajustado>=60){
                    segundoajustado=0;
                  }
                  break;
              }
          }
          value = digitalRead(A4);  //dw 
          if (value == LOW) {
              switch (opcionhora) {
                case 1: //set hora
                  horaajustada--;
                  if (horaajustada<0){
                    horaajustada=23;
                  }
                  break;
                case 2: //set minuto
                  minutoajustado--;
                  if (minutoajustado<0){
                    minutoajustado=59;
                  }
                  break;
                case 3:
                  segundoajustado--;
                  if (segundoajustado<0){
                    segundoajustado=59;
                  }
                  break;
              }
          }
    }
    setHoraFecha(segundoajustado, minutoajustado, horaajustada, 6, 6, 9, 2019);
    initProgram();
}

void setHoraFecha(int segundo, int minuto, int hora24, int diasemana, int diames, int mes, int ano){
  myRTC.setDS1302Time(segundo, minuto, hora24, diasemana, diames, mes, ano);
}

void setProgram(){
    lcd.setCursor(0,0);
    lcd.print("Select Pr: 1-2");
    programaajustado=ProgramaSeleccionado;
    int opcionprog = 1;
    //unsigned long finishhora = millis()+120000UL; // cargo a start con el valor +10mil milisegundos
    //while (millis() < finishhora || opcionhora != 0) {
    while (opcionprog != 0) {
          delay(200);
          lcd.setCursor(0,1);
          if (second()%2==0){
            lcd.print("Program: "+String(programaajustado)+"      ");
          } else {
            lcd.print("Program: _      ");            
          }
          value = digitalRead(A1);  //back
          if (value == LOW) {
              programaajustado = ProgramaSeleccionado;
              opcionprog = 0;
          }
          value = digitalRead(A2);  //set 
          if (value == LOW) {
              opcionprog = 0;
          }
          value = digitalRead(A3);  //up 
          if (value == LOW) {
              programaajustado++;
              if (programaajustado>=3){
                    programaajustado=1;
              }
          }
          value = digitalRead(A4);  //dw 
          if (value == LOW) {
              programaajustado--;
              if (programaajustado<1){
                    programaajustado=2;
              }
          }
    }
    ProgramaSeleccionado=programaajustado;
    initProgram();
}

void setManual(){
    lcd.setCursor(0,0);
    lcd.print("No implementado ");
    lcd.setCursor(0,1);
    lcd.print("No implementado ");
    delay(3000);
}

void Programa1(int hora){
  lcd.setCursor(0,0);
  lcd.print("Pr01 Updated");
  delay(3000);
  lcd.setCursor(0,1);
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
  lcd.setCursor(0,0);
  lcd.print("Pr02 Updated");
  delay(2000);
  lcd.setCursor(0,1);
  switch (hora) {
      case 1: //Amanecer
        lcd.print("Es amanecer    ");
        delay(2000);
        digitalWrite(blancoSuave,HIGH);
        digitalWrite(blancoFuerte,HIGH);
        digitalWrite(azul,LOW);
        break;    
      case 2: //Mañana
        lcd.print("Es manana    ");
        delay(2000);
        digitalWrite(blancoSuave,LOW);
        digitalWrite(blancoFuerte,HIGH);
        digitalWrite(azul,LOW);
        break;      
      case 3: //Media Mañana
      lcd.print("Es manana2    ");
        delay(2000);
        digitalWrite(blancoSuave,HIGH);
        digitalWrite(blancoFuerte,LOW);
        digitalWrite(azul,LOW);
        break;    
      case 4: //Mediodia
      lcd.print("Es mediodia    ");
        delay(2000);
        digitalWrite(blancoSuave,LOW);
        digitalWrite(blancoFuerte,LOW);
        digitalWrite(azul,LOW);
        break;      
      case 5: //Tarde
      lcd.print("Es tarde      ");
        delay(2000);
        digitalWrite(blancoSuave,HIGH);
        digitalWrite(blancoFuerte,LOW);
        digitalWrite(azul,LOW);
        break;    
      case 6: //Media tarde
      lcd.print("Es tarde1    ");
        delay(2000);
        digitalWrite(blancoSuave,LOW);
        digitalWrite(blancoFuerte,HIGH);
        digitalWrite(azul,LOW);
        break;  
      case 7: //Atardecer
      lcd.print("Es atardecer      ");
        delay(2000);
        digitalWrite(blancoSuave,HIGH);
        digitalWrite(blancoFuerte,HIGH);
        digitalWrite(azul,LOW);
        break;      
      case 8: //Noche
      lcd.print("Es noche      ");
        delay(2000);
        digitalWrite(blancoSuave,HIGH);
        digitalWrite(blancoFuerte,HIGH);
        digitalWrite(azul,HIGH);
        break;      
  }
}

void Programa3(int hora){
  lcd.setCursor(0,0);
  lcd.write("SeaLampControl Pr03");
  lcd.setCursor(0,1);
  
}

void Programa4(int hora){
  lcd.setCursor(0,0);
  lcd.write("SeaLampControl Pr04");
  lcd.setCursor(0,1);
  
}

void Programa5(int hora){
  lcd.setCursor(0,0);
  lcd.write("SeaLampControl Pr05");
  lcd.setCursor(0,1);
}

boolean esAmanecer(){
  myRTC.updateTime();
  long hora_actual = long(myRTC.hours)*3600 + long(myRTC.minutes)*60 + long(myRTC.seconds);
  long hora_amanecer = HoraAmanecer*3600+MinutoAmanecer*60+SegundoAmanecer;
  long hora_manana = HoraManana*3600+MinutoManana*60+SegundoManana;
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
  Serial.println("HoraActual: "+String(myRTC.hours)+" HoraMediaManana "+String(hora_mediamanana)+" HoraManana "+String(hora_manana));
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
