#include <LiquidCrystal_I2C.h>
#include <MyRealTimeClock.h>
#include <TimeLib.h>

MyRealTimeClock myRTC(3, 1, 2);
LiquidCrystal_I2C lcd(0x3F, 16, 2);
  
const int Channel1 = 11;
const int Channel2 = 10;
const int Channel3 = 9;
const int Channel4 = 6;
const int Channel5 = 5;
// Joystick pin numbers
const int SW_pin = 0; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output
int x_value = 500;
int y_value = 500;
//const int Menu = 0;
//const int Back = 4;
//const int Set = 7;
//const int Up = 8;
//const int Dw = 12;
//No ajustar ningun periodo a menos de 5 minutos
long HoraAmanecer = 7, MinutoAmanecer = 0, SegundoAmanecer = 0;
long HoraManana = 7, MinutoManana = 30, SegundoManana = 0;
long HoraMediaManana = 10, MinutoMediaManana = 0, SegundoMediaManana = 0;
long HoraMediodia = 11, MinutoMediodia = 30, SegundoMediodia = 0;
long HoraTarde = 12, MinutoTarde = 30, SegundoTarde = 0;
long HoraMediaTarde = 14, MinutoMediaTarde = 0, SegundoMediaTarde = 0;
long HoraAtardecer = 18, MinutoAtardecer = 30, SegundoAtardecer = 0;
long HoraNoche = 19, MinutoNoche = 0, SegundoNoche = 0;

int IntensityChannel1 = 0;
int IntensityChannel2 = 0;
int IntensityChannel3 = 0;
int IntensityChannel4 = 0;
int IntensityChannel5 = 0;

int AimIntensityChannel1 = 0;
int AimIntensityChannel2 = 0;
int AimIntensityChannel3 = 0;
int AimIntensityChannel4 = 0;
int AimIntensityChannel5 = 0;

int manual = 1;
boolean demoOn = false;

int ManualIntensityChannel1 = 9;
int ManualIntensityChannel2 = 9;
int ManualIntensityChannel3 = 9;
int ManualIntensityChannel4 = 9;
int ManualIntensityChannel5 = 9;

int ProgramaSeleccionado=1;
int value, opcion;
int horaajustada;
int minutoajustado;
int segundoajustado;
int programaajustado;
int counterDisplay;

void setHoraFecha(int, int, int, int, int, int, int);

void printDate(String, String, String);

void initProgram();
void initProgram1();
void initProgram2();
void initProgram3();
void initProgram4();
void initProgram5();

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

void initPrograma1();
void initPrograma2();
void initPrograma3();
void initPrograma4();
void initPrograma5();

void Programa1(int, boolean);
void Programa2(int, boolean);
void Programa3(int, boolean);
void Programa4(int, boolean);
void Programa5(int, boolean);

void enterMenu();
void changeTime();
void setProgram();
void setManual();
void setValueManual();
void setDemo();

void adjustIntensity(int, int, int, int, int, boolean);

String message_hour;

boolean displayapagado;

int interrupt_timer = 0;

void setup() {
  //Serial.begin(9600);
  pinMode(Channel1,OUTPUT);
  pinMode(Channel2,OUTPUT);
  pinMode(Channel3,OUTPUT);
  pinMode(Channel4,OUTPUT);
  pinMode(Channel5,OUTPUT);
  digitalWrite(Channel1,0);
  digitalWrite(Channel2,0);
  digitalWrite(Channel3,0);
  digitalWrite(Channel4,0);
  digitalWrite(Channel5,0);
  pinMode(SW_pin, INPUT_PULLUP);

  //Configuro el timer 2 para generar la señal pwm para los led que tendrá una frecuencia de 12Hz aproximadamente. Configuro el timer a frecuencia 244Hz 
  //y con un contador de 20 (interrupt_timer) genero la frecuencia de 12Hz.
  cli();//stop interrupts
  
  //set timer1 interrupt at 244Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 16000;// = (16*10^6) / (1000) - 1 (must be <65536)
  //OCR1A = 65535;// = (16*10^6) / (244) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1 prescaler
  TCCR1B |= (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);


  sei();//allow interrupts

  
  initProgram();
  lcd.init();
  lcd.backlight();
  lcd.home();
  lcd.setCursor(0,0);
  lcd.print("SeaLampControl  ");
  lcd.setCursor(0,1);
  printDate(String(myRTC.hours),String(myRTC.minutes),String(myRTC.seconds));
  //Serial.println(String(myRTC.hours)+":"+String(myRTC.minutes)+":"+String(myRTC.seconds)+"             ");
  delay(1000);
  displayapagado=true;
  counterDisplay=1;
  lcd.noBacklight();
    
}

void loop() {
  delay(100);
  counterDisplay--;
  if (counterDisplay == 0){
    counterDisplay = 1;
    lcd.noBacklight();
    displayapagado=true;   
  }
  lcd.setCursor(0,1);
  value = digitalRead(SW_pin);  //lectura digital de pin 
  if (value == LOW) {
    delay(1000);
      if (displayapagado==false) {
      //  lcd.print("Menu        ");
        enterMenu();
      } else {
        lcd.backlight();
        counterDisplay = 100;
        displayapagado=false;        
      }
  }
  myRTC.updateTime();
  lcd.setCursor(0,0);
  lcd.print("SeaLampControl                    ");
  lcd.setCursor(0,1);
  printDate(String(myRTC.hours),String(myRTC.minutes),String(myRTC.seconds));
  //Serial.println(String(myRTC.hours)+":"+String(myRTC.minutes)+":"+String(myRTC.seconds));
  //Serial.println(String(myRTC.dayofmonth)+"/"+String(myRTC.month)+"/"+String(myRTC.year)+"   "+String(myRTC.hours)+":"+String(myRTC.minutes)+":"+String(myRTC.seconds)+"            ");
  if (manual != 2){ //SI estamos en modo manual no hacemos nada, la intensidad ya se fijó al configurar el modo manual.
   if (esHoraAmanecer()){
      lcd.print(" Amanecer");
      switch (ProgramaSeleccionado) {
        case 1:
          Programa1(1, true);
          break;
        case 2:
          Programa2(1, true);
          break;
        case 3:
          Programa3(1, true);
          break;
        case 4:
          Programa4(1, true);
          break;
        case 5:
          Programa5(1, true);
          break;  
      }   
    } else if (esHoraManana()) {
      lcd.print(" Manana1");
      switch (ProgramaSeleccionado) {
        case 1:
          Programa1(2, true);
          break;
        case 2:
          Programa2(2, true);
          break;
        case 3:
          Programa3(2, true);
          break;
        case 4:
          Programa4(2, true);
          break;
        case 5:
          Programa5(2, true);
          break;  
      }      
    } else if (esHoraMediaManana()) {
      lcd.print("  Manana2");
      switch (ProgramaSeleccionado) {
            case 1:
              Programa1(3, true);
              break;
            case 2:
              Programa2(3, true);
              break;
            case 3:
              Programa3(3, true);
              break;
            case 4:
              Programa4(3, true);
              break;
            case 5:
              Programa5(3, true);
              break;  
          }      
    } else if (esHoraMediodia()) {
      lcd.print("  Mediodia");
      switch (ProgramaSeleccionado) {
            case 1:
              Programa1(4, true);
              break;
            case 2:
              Programa2(4, true);
              break;
            case 3:
              Programa3(4, true);
              break;
            case 4:
              Programa4(4, true);
              break;
            case 5:
              Programa5(4, true);
              break;  
          }  
    } else if (esHoraTarde()) {
      lcd.print("  Tarde1");
      switch (ProgramaSeleccionado) {
            case 1:
              Programa1(5, true);
              break;
            case 2:
              Programa2(5, true);
              break;
            case 3:
              Programa3(5, true);
              break;
            case 4:
              Programa4(5, true);
              break;
            case 5:
              Programa5(5, true);
              break;  
          }     
    } else if (esHoraMediaTarde()) {
      lcd.print("  Tarde2");
      switch (ProgramaSeleccionado) {
            case 1:
              Programa1(6, true);
              break;
            case 2:
              Programa2(6, true);
              break;
            case 3:
              Programa3(6, true);
              break;
            case 4:
              Programa4(6, true);
              break;
            case 5:
              Programa5(6, true);
              break;  
          }      
    } else if (esHoraAtardecer()) {
      lcd.print("  Atardecer");
      switch (ProgramaSeleccionado) {
            case 1:
              Programa1(7, true);
              break;
            case 2:
              Programa2(7, true);
              break;
            case 3:
              Programa3(7, true);
              break;
            case 4:
              Programa4(7, true);
              break;
            case 5:
              Programa5(7, true);
              break;  
          }      
    } else if (esHoraNoche()) {
        lcd.print("  Noche");
        switch (ProgramaSeleccionado) {
            case 1:
              Programa1(8, true);
              break;
            case 2:
              Programa2(8, true);
              break;
            case 3:
              Programa3(8, true);
              break;
            case 4:
              Programa4(8, true);
              break;
            case 5:
              Programa5(8, true);
              break;  
          }      
    }
  }      
}

void printDate(String horaprint, String minutoprint, String segundoprint){
  if (horaprint.length() < 2){
    horaprint = "0"+horaprint;
  }
  if (minutoprint.length() < 2){
    minutoprint = "0"+minutoprint;
  }
  if (segundoprint.length() < 2){
    segundoprint = "0"+segundoprint;
  }
  if (manual == 2) {
    lcd.print(horaprint+":"+minutoprint+":"+segundoprint+"  Manual"); 
  } else {
    lcd.print(horaprint+":"+minutoprint+":"+segundoprint+"  Pr0"+ProgramaSeleccionado+"  "); 
  } 
}

void initProgram(){
  switch (ProgramaSeleccionado) {
      case 1:
        initProgram1();
        break;
      case 2:
        initProgram2();
        break;
      case 3:
        initProgram3();
        break; 
      case 4:
        initProgram4();
        break;
      case 5:
        initProgram5();  
        break;
  } 
  if (esAmanecer()){
    switch (ProgramaSeleccionado) {
      case 1:
        Programa1(1, false);
        break;
      case 2:
        Programa2(1, false);
        break;
      case 3:
        Programa3(1, false);
        break; 
      case 4:
        Programa4(1, false);
        break;
      case 5:
        Programa5(1, false);  
        break;
    } 
  } else if (esManana()) {
    switch (ProgramaSeleccionado) {
      case 1:
        Programa1(2, false);
        break;
      case 2:
        Programa2(2, false);
        break;
      case 3:
        Programa3(2, false);
        break;
      case 4:
        Programa4(2, false);
        break;
      case 5:
        Programa5(2, false);
        break;  
    }      
  } else if (esMediaManana()) {
    switch (ProgramaSeleccionado) {
      case 1:
        Programa1(3, false);
        break;
      case 2:
        Programa2(3, false);
        break;
      case 3:
        Programa3(3, false);
        break;
      case 4:
        Programa4(3, false);
        break;
      case 5:
        Programa5(3, false);
        break;  
    } 
  } else if (esMediodia()) {
    switch (ProgramaSeleccionado) {
      case 1:
        Programa1(4, false);
        break;
      case 2:
        Programa2(4, false);
        break;
      case 3:
        Programa3(4, false);
        break;
      case 4:
        Programa4(4, false);
        break;
      case 5:
        Programa5(4, false);
        break;  
    }      
  } else if (esTarde()) {
    switch (ProgramaSeleccionado) {
      case 1:
        Programa1(5, false);
        break;
      case 2:
        Programa2(5, false);
        break;
      case 3:
        Programa3(5, false);
        break;
      case 4:
        Programa4(5, false);
        break;
      case 5:
        Programa5(5, false);
        break;  
    }  
  } else if (esMediaTarde()) {
    switch (ProgramaSeleccionado) {
      case 1:
        Programa1(6, false);
        break;
      case 2:
        Programa2(6, false);
        break;
      case 3:
        Programa3(6, false);
        break;
      case 4:
        Programa4(6, false);
        break;
      case 5:
        Programa5(6, false);
        break;  
    } 
  } else if (esAtardecer()) {
    switch (ProgramaSeleccionado) {
      case 1:
        Programa1(7, false);
        break;
      case 2:
        Programa2(7, false);
        break;
      case 3:
        Programa3(7, false);
        break;
      case 4:
        Programa4(7, false);
        break;
      case 5:
        Programa5(7, false);
        break;  
    }   
  } else if (esNoche()) {
    switch (ProgramaSeleccionado) {
      case 1:
        Programa1(8, false);
        break;
      case 2:
        Programa2(8, false);
        break;
      case 3:
        Programa3(8, false);
        break;
      case 4:
        Programa4(8, false);
        break;
      case 5:
        Programa5(8, false);
        break;  
    }       
  }
}

void initProgram1(){
  long HoraAmanecer = 7, MinutoAmanecer = 0, SegundoAmanecer = 0;
  long HoraManana = 7, MinutoManana = 30, SegundoManana = 0;
  long HoraMediaManana = 10, MinutoMediaManana = 0, SegundoMediaManana = 0;
  long HoraMediodia = 11, MinutoMediodia = 30, SegundoMediodia = 0;
  long HoraTarde = 12, MinutoTarde = 30, SegundoTarde = 0;
  long HoraMediaTarde = 14, MinutoMediaTarde = 0, SegundoMediaTarde = 0;
  long HoraAtardecer = 18, MinutoAtardecer = 30, SegundoAtardecer = 0;
  long HoraNoche = 19, MinutoNoche = 0, SegundoNoche = 0;  
}

void initProgram2(){
  long HoraAmanecer = 7, MinutoAmanecer = 0, SegundoAmanecer = 0;
  long HoraManana = 7, MinutoManana = 30, SegundoManana = 0;
  long HoraMediaManana = 10, MinutoMediaManana = 0, SegundoMediaManana = 0;
  long HoraMediodia = 11, MinutoMediodia = 30, SegundoMediodia = 0;
  long HoraTarde = 12, MinutoTarde = 30, SegundoTarde = 0;
  long HoraMediaTarde = 14, MinutoMediaTarde = 0, SegundoMediaTarde = 0;
  long HoraAtardecer = 18, MinutoAtardecer = 30, SegundoAtardecer = 0;
  long HoraNoche = 19, MinutoNoche = 0, SegundoNoche = 0;  
}

void initProgram3(){
  long HoraAmanecer = 8, MinutoAmanecer = 0, SegundoAmanecer = 0;
  long HoraManana = 8, MinutoManana = 30, SegundoManana = 0;
  long HoraMediaManana = 11, MinutoMediaManana = 0, SegundoMediaManana = 0;
  long HoraMediodia = 12, MinutoMediodia = 30, SegundoMediodia = 0;
  long HoraTarde = 13, MinutoTarde = 30, SegundoTarde = 0;
  long HoraMediaTarde = 15, MinutoMediaTarde = 0, SegundoMediaTarde = 0;
  long HoraAtardecer = 19, MinutoAtardecer = 30, SegundoAtardecer = 0;
  long HoraNoche = 20, MinutoNoche = 0, SegundoNoche = 0;  
}

void initProgram4(){
  long HoraAmanecer = 8, MinutoAmanecer = 0, SegundoAmanecer = 0;
  long HoraManana = 8, MinutoManana = 30, SegundoManana = 0;
  long HoraMediaManana = 11, MinutoMediaManana = 0, SegundoMediaManana = 0;
  long HoraMediodia = 12, MinutoMediodia = 30, SegundoMediodia = 0;
  long HoraTarde = 13, MinutoTarde = 30, SegundoTarde = 0;
  long HoraMediaTarde = 15, MinutoMediaTarde = 0, SegundoMediaTarde = 0;
  long HoraAtardecer = 19, MinutoAtardecer = 30, SegundoAtardecer = 0;
  long HoraNoche = 20, MinutoNoche = 0, SegundoNoche = 0;
}

void initProgram5(){
  long HoraAmanecer = 9, MinutoAmanecer = 0, SegundoAmanecer = 0;
  long HoraManana = 9, MinutoManana = 30, SegundoManana = 0;
  long HoraMediaManana = 12, MinutoMediaManana = 0, SegundoMediaManana = 0;
  long HoraMediodia = 13, MinutoMediodia = 15, SegundoMediodia = 0;
  long HoraTarde = 13, MinutoTarde = 45, SegundoTarde = 0;
  long HoraMediaTarde = 15, MinutoMediaTarde = 0, SegundoMediaTarde = 0;
  long HoraAtardecer = 18, MinutoAtardecer = 30, SegundoAtardecer = 0;
  long HoraNoche = 19, MinutoNoche = 0, SegundoNoche = 0;  
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
              lcd.print("[ ] Demo         ");
              break;
            case 5:
              lcd.print("[ ] Exit        ");
              break;
      }
      lcd.setCursor(0,1);
      lcd.print("[OK] [+/-] [BK] ");
      unsigned long finish = millis()+60000UL; // cargo a start con el valor +10mil milisegundos
      while (millis() < finish) {
         // lo que este aqui dentro tiene 10 segundos para ejecutarse
         // o puedes salir con break*/
        x_value = analogRead(X_pin);
        y_value = analogRead(Y_pin);
        //if (y_value > 900) {
        //    opcion = 0;
        //    break;
        //}
        value = digitalRead(SW_pin);  //set 
        if (value == LOW) {
            switch (opcion) {
              case 1:
                lcd.setCursor(0,0);
                lcd.print("[*] Set Time    ");
                delay(1000);
                changeTime();
                opcion = 5;
                break;
              case 2:
                lcd.setCursor(0,0);
                lcd.print("[*] Set Program ");
                delay(1000);
                setProgram();
                opcion = 5;
                break;
              case 3:
                lcd.setCursor(0,0);
                lcd.print("[*] Set Manual   ");
                delay(1000);
                setManual();
                opcion = 5;
                break;
              case 4:
                lcd.setCursor(0,0);
                lcd.print("[*] Demo          ");
                delay(1000);
                setDemo();
                opcion = 5;
                break;
              case 5:
                lcd.setCursor(0,0);
                lcd.print("[*] Exit         ");
                delay(1000);
                opcion = 0;
                break;
            }
           break;
        }
        //up 
        if (x_value > 900) {
            opcion++;
            if (opcion == 6){
              opcion = 1;
            }
            //delay(1000);
            break;
        }
        //dw 
        if (x_value < 100) {
            opcion--;
            if (opcion == 0){
              opcion = 5;
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
            printDate(String(horaajustada),String(minutoajustado),String(segundoajustado));
          } else {
            switch (opcionhora) {
                case 1: //set hora
                  printDate("__",String(minutoajustado),String(segundoajustado));
                  break;
                case 2: //set minuto
                  printDate(String(horaajustada),"__",String(segundoajustado));
                  break;
                case 3:
                  printDate(String(horaajustada),String(minutoajustado),"__");
                  break;
              }
            
          }
           // lo que este aqui dentro tiene 10 segundos para ejecutarse
           // o puedes salir con break
          x_value = analogRead(X_pin);
          y_value = analogRead(Y_pin);
          if (y_value > 900) { //BACK
              horaajustada = myRTC.hours;
              minutoajustado = myRTC.minutes;
              segundoajustado = myRTC.seconds;
              opcionhora = 0;
          }
          value = digitalRead(SW_pin);  //set 
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
          //up 
          if (x_value > 900) {
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
          //dw 
          if (x_value < 100) {
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
    lcd.print("Select Pr: 1-2-3-4-5  ");
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
          x_value = analogRead(X_pin);
          y_value = analogRead(Y_pin);
           //back
          if (y_value > 900) {
              programaajustado = ProgramaSeleccionado;
              opcionprog = 0;
          }
          value = digitalRead(SW_pin);  //set 
          if (value == LOW) {
              opcionprog = 0;
          }
          //up 
          if (x_value > 900) {
              programaajustado++;
              if (programaajustado>=6){
                    programaajustado=1;
              }
          }
          //dw 
          if (x_value < 100) {
              programaajustado--;
              if (programaajustado<1){
                    programaajustado=5;
              }
          }
    }
    ProgramaSeleccionado=programaajustado;
    initProgram();
}

void setManual(){
    int opcionmanual = 1;
    int valuemanual;
    //unsigned long finishhora = millis()+120000UL; // cargo a start con el valor +10mil milisegundos
    //while (millis() < finishhora || opcionhora != 0) {
    while (opcionmanual != 0) {
          delay(200);
          lcd.setCursor(0,0);
          lcd.print("Manual Mode     ");
          lcd.setCursor(0,1);
          if (manual == 2){
              lcd.print("[ON] Manual     ");
          } else {
              lcd.print("[OFF] Manual    ");
          }
          x_value = analogRead(X_pin);
          y_value = analogRead(Y_pin);
          //back
          if (y_value > 900) {
              delay(1000);
              opcionmanual = 0;
          }
          valuemanual = digitalRead(SW_pin);  //set 
          if (valuemanual == LOW) {
              delay(1000);
              if (manual == 2){
                lcd.setCursor(0,1);
                lcd.print("[OFF] Manual     ");
                delay(1500);
                manual = 1;
                //ManualIntensityChannel1 = 10;
                //ManualIntensityChannel2 = 10;
                //ManualIntensityChannel3 = 10;
                //ManualIntensityChannel4 = 10;
                //ManualIntensityChannel5 = 10;
                //opcionmanual = 0; 
              } else {
                lcd.setCursor(0,1);
                lcd.print("[ON] Manual     ");
                delay(1500);
                manual = 2;
                setValueManual();
                //opcionmanual = 0;
              }
          }        
    }
}

void setValueManual(){
      lcd.setCursor(0,1);
      boolean exit = false;
      int index=0;
      while (index < 5){
          while (!exit){
            delay(200);
            x_value = analogRead(X_pin);
            y_value = analogRead(Y_pin);
            switch (index){
              case 0:
                if (ManualIntensityChannel1 == 0){
                  lcd.setCursor(0,1);
                  lcd.print("CH1 Level "+String(ManualIntensityChannel1*100/20)+"%   ");
                } else {
                  lcd.setCursor(0,1);
                  lcd.print("CH1 Level "+String((ManualIntensityChannel1+1)*100/20)+"%   ");
                }
                //up 
                if (x_value > 900) {
                  ManualIntensityChannel1 = ManualIntensityChannel1 + 1;
                  if (ManualIntensityChannel1 > 19){
                    ManualIntensityChannel1 = 19;
                  } 
                }
                //dw 
                if (x_value < 100) {
                  ManualIntensityChannel1 = ManualIntensityChannel1 - 1;
                  if (ManualIntensityChannel1 < 0){
                    ManualIntensityChannel1 = 0;
                  }
                }
                //next 
                if (y_value > 900) {
                  delay(500);
                  index++;
                  if(index == 5) {
                    index = 0;
                  }
                }
                //previous 
                if (y_value < 100) {
                    delay(500);
                    index--;
                    if(index < 0 ) {
                      index = 4;
                    }
                }
                value = digitalRead(SW_pin);  //up 
                if (value == LOW) {
                  delay(1000);
                  lcd.setCursor(0,1);
                  lcd.print("Exit?  [OK]     ");
                  int confirm = 0;
                  unsigned long finish = millis()+3000UL; // cargo a start con el valor +10mil milisegundos
                  while (millis() < finish && confirm == 0) {
                    value = digitalRead(SW_pin);  //up 
                    if (value == LOW) {
                      confirm = 1;
                      index = 5;
                      exit = true;
                    }
                  }
                }   
                break;
              case 1:
                lcd.setCursor(0,1);
                if (ManualIntensityChannel2 == 0){
                  lcd.print("CH2 Level "+String(ManualIntensityChannel2*100/20)+"%   ");
                } else {
                  lcd.print("CH2 Level "+String((ManualIntensityChannel2+1)*100/20)+"%   ");
                }
                //up 
                if (x_value > 900) {
                  ManualIntensityChannel2 = ManualIntensityChannel2 + 1;
                  if (ManualIntensityChannel2 > 19){
                    ManualIntensityChannel2 = 19;
                  } 
                }
                //dw 
                if (x_value < 100) {
                  ManualIntensityChannel2 = ManualIntensityChannel2 - 1;
                  if (ManualIntensityChannel2 < 0){
                    ManualIntensityChannel2 = 0;
                  }
                }
                //next 
                if (y_value > 900) {
                  delay(500);
                  index++;
                  if(index == 5) {
                    index = 0;
                  }
                }
                //previous 
                if (y_value < 100) {
                    delay(500);
                    index--;
                    if(index < 0 ) {
                      index = 4;
                    }
                }
                value = digitalRead(SW_pin);  //up 
                if (value == LOW) {
                  delay(1000);
                  lcd.setCursor(0,1);
                  lcd.print("Exit?  [OK]     ");
                  int confirm = 0;
                  unsigned long finish = millis()+3000UL; // cargo a start con el valor +10mil milisegundos
                  while (millis() < finish && confirm == 0) {
                    value = digitalRead(SW_pin);  //up 
                    if (value == LOW) {
                      confirm = 1;
                      index = 5;
                      exit = true;
                    }
                  }
                }    
                break;
              case 2:
                lcd.setCursor(0,1);
                if (ManualIntensityChannel3 == 0){
                  lcd.print("CH3 Level "+String(ManualIntensityChannel3*100/20)+"%   ");
                } else {
                  lcd.print("CH3 Level "+String((ManualIntensityChannel3+1)*100/20)+"%   ");
                }
                //up 
                if (x_value > 900) {
                  ManualIntensityChannel3 = ManualIntensityChannel3 + 1;
                  if (ManualIntensityChannel3 > 19){
                    ManualIntensityChannel3 = 19;
                  } 
                }
                //dw 
                if (x_value < 100) {
                  ManualIntensityChannel3 = ManualIntensityChannel3 - 1;
                  if (ManualIntensityChannel3 < 0){
                    ManualIntensityChannel3 = 0;
                  }
                }
                //next 
                if (y_value > 900) {
                  delay(500);
                  index++;
                  if(index == 5) {
                    index = 0;
                  }
                }
                //previous 
                if (y_value < 100) {
                    delay(500);
                    index--;
                    if(index < 0 ) {
                      index = 4;
                    }
                }
                value = digitalRead(SW_pin);  //up 
                if (value == LOW) {
                  delay(1000);
                  lcd.setCursor(0,1);
                  lcd.print("Exit?  [OK]     ");
                  int confirm = 0;
                  unsigned long finish = millis()+3000UL; // cargo a start con el valor +10mil milisegundos
                  while (millis() < finish && confirm == 0) {
                    value = digitalRead(SW_pin);  //up 
                    if (value == LOW) {
                      confirm = 1;
                      index = 5;
                      exit = true;
                    }
                  }
                }  
                break;
              case 3:            
                lcd.setCursor(0,1);
                if (ManualIntensityChannel4 == 0){
                  lcd.print("CH4 Level "+String(ManualIntensityChannel4*100/20)+"%   ");
                } else {
                  lcd.print("CH4 Level "+String((ManualIntensityChannel4+1)*100/20)+"%   ");
                }
                //up 
                if (x_value > 900) {
                  ManualIntensityChannel4 = ManualIntensityChannel4 + 1;
                  if (ManualIntensityChannel4 > 19){
                    ManualIntensityChannel4 = 19;
                  } 
                }
                //dw 
                if (x_value < 100) {
                  ManualIntensityChannel4 = ManualIntensityChannel4 - 1;
                  if (ManualIntensityChannel4 < 0){
                    ManualIntensityChannel4 = 0;
                  }
                }
                //next 
                if (y_value > 900) {
                  delay(500);
                  index++;
                  if(index == 5) {
                    index = 0;
                  }
                }
                //previous 
                if (y_value < 100) {
                    delay(500);
                    index--;
                    if(index < 0 ) {
                      index = 4;
                    }
                }
                value = digitalRead(SW_pin);  //up 
                if (value == LOW) {
                  delay(1000);
                  lcd.setCursor(0,1);
                  lcd.print("Exit?  [OK]     ");
                  int confirm = 0;
                  unsigned long finish = millis()+3000UL; // cargo a start con el valor +10mil milisegundos
                  while (millis() < finish && confirm == 0) {
                    value = digitalRead(SW_pin);  //up 
                    if (value == LOW) {
                      confirm = 1;
                      index = 5;
                      exit = true;
                    }
                  }
                }  
                break;
              case 4:              
                lcd.setCursor(0,1);
                if (ManualIntensityChannel5 == 0) {
                  lcd.print("CH5 Level "+String(ManualIntensityChannel5*100/20)+"%   ");
                } else {
                  lcd.print("CH5 Level "+String((ManualIntensityChannel5+1)*100/20)+"%   ");
                }
                //up 
                if (x_value > 900) {
                  ManualIntensityChannel5 = ManualIntensityChannel5 + 1;
                  if (ManualIntensityChannel5 > 19){
                    ManualIntensityChannel5 = 19;
                  } 
                }
                //dw 
                if (x_value < 100) {
                  ManualIntensityChannel5 = ManualIntensityChannel5 - 1;
                  if (ManualIntensityChannel5 < 0){
                    ManualIntensityChannel5 = 0;
                  }
                }
                //next 
                if (y_value > 900) {
                  delay(500);
                  index++;
                  if(index == 5) {
                    index = 0;
                  }
                }
                //previous 
                if (y_value < 100) {
                    delay(500);
                    index--;
                    if(index < 0 ) {
                      index = 4;
                    }
                }
                value = digitalRead(SW_pin);  //up 
                if (value == LOW) {
                  delay(1000);
                  lcd.setCursor(0,1);
                  lcd.print("Exit?  [OK]     ");
                  int confirm = 0;
                  unsigned long finish = millis()+3000UL; // cargo a start con el valor +10mil milisegundos
                  while (millis() < finish && confirm == 0) {
                    value = digitalRead(SW_pin);  //up 
                    if (value == LOW) {
                      confirm = 1;
                      index = 5;
                      exit = true;
                    }
                  }
                }    
                break;            
            }
          }
          exit = false;
          
      }
      adjustIntensity(ManualIntensityChannel1, ManualIntensityChannel2, ManualIntensityChannel3, ManualIntensityChannel4, ManualIntensityChannel5, false);
}

void setDemo(){
   boolean exitDemo = false;
   demoOn = true;
   //Los tiempos deben ser mayores de 90s para permitir el ciclo completo de cambio gradual
   unsigned long amanecer = millis();
   unsigned long manana1 = millis()+120000UL;
   unsigned long manana2 = millis()+240000UL;
   unsigned long mediodia = millis()+360000UL;
   unsigned long tarde1 = millis()+480000UL;
   unsigned long tarde2 = millis()+600000UL;
   unsigned long atardecer = millis()+720000UL;
   unsigned long noche = millis()+840000UL;
   unsigned long finish = millis()+960000UL; // cargo a start con el valor +10mil milisegundos
   lcd.setCursor(0,0);
   lcd.print("DEMO Cancel [OK]");
   lcd.setCursor(0,1);
   lcd.print(" Amanecer       ");
   switch (ProgramaSeleccionado) {
     case 1:
       Programa1(1, true);
       break;
     case 2:
       Programa2(1, true);
       break;
     case 3:
       Programa3(1, true);
       break;
     case 4:
       Programa4(1, true);
       break;
     case 5:
       Programa5(1, true);
       break;  
   }   
   while (millis() < finish && exitDemo == false) {
      value = digitalRead(SW_pin);  //up 
      if (value == LOW) {
        delay(1000);
        exitDemo = true;
      }
      if (millis() == manana1 ){
          lcd.setCursor(0,1);
          lcd.print(" Manana1        ");
          switch (ProgramaSeleccionado) {
            case 1:
              Programa1(2, true);
              break;
            case 2:
              Programa2(2, true);
              break;
            case 3:
              Programa3(2, true);
              break;
            case 4:
              Programa4(2, true);
              break;
            case 5:
              Programa5(2, true);
              break;  
          }      
        } else if (millis() == manana2 ){
          lcd.setCursor(0,1);
          lcd.print(" Manana2        ");
          switch (ProgramaSeleccionado) {
                case 1:
                  Programa1(3, true);
                  break;
                case 2:
                  Programa2(3, true);
                  break;
                case 3:
                  Programa3(3, true);
                  break;
                case 4:
                  Programa4(3, true);
                  break;
                case 5:
                  Programa5(3, true);
                  break;  
              }      
        } else if (millis() == mediodia ){
          lcd.setCursor(0,1);
          lcd.print(" Mediodia        ");
          switch (ProgramaSeleccionado) {
                case 1:
                  Programa1(4, true);
                  break;
                case 2:
                  Programa2(4, true);
                  break;
                case 3:
                  Programa3(4, true);
                  break;
                case 4:
                  Programa4(4, true);
                  break;
                case 5:
                  Programa5(4, true);
                  break;  
              }  
        } else if (millis() == tarde1 ){
          lcd.setCursor(0,1);
          lcd.print(" Tarde1         ");
          switch (ProgramaSeleccionado) {
                case 1:
                  Programa1(5, true);
                  break;
                case 2:
                  Programa2(5, true);
                  break;
                case 3:
                  Programa3(5, true);
                  break;
                case 4:
                  Programa4(5, true);
                  break;
                case 5:
                  Programa5(5, true);
                  break;  
              }     
        } else if (millis() == tarde2 ){
          lcd.setCursor(0,1);
          lcd.print(" Tarde2         ");
          switch (ProgramaSeleccionado) {
                case 1:
                  Programa1(6, true);
                  break;
                case 2:
                  Programa2(6, true);
                  break;
                case 3:
                  Programa3(6, true);
                  break;
                case 4:
                  Programa4(6, true);
                  break;
                case 5:
                  Programa5(6, true);
                  break;  
              }      
        } else if (millis() == atardecer ){
          lcd.setCursor(0,1);
          lcd.print(" Atardecer      ");
          switch (ProgramaSeleccionado) {
                case 1:
                  Programa1(7, true);
                  break;
                case 2:
                  Programa2(7, true);
                  break;
                case 3:
                  Programa3(7, true);
                  break;
                case 4:
                  Programa4(7, true);
                  break;
                case 5:
                  Programa5(7, true);
                  break;  
              }      
        } else if (millis() == noche ){
            lcd.setCursor(0,1);
            lcd.print(" Noche          ");
            switch (ProgramaSeleccionado) {
                case 1:
                  Programa1(8, true);
                  break;
                case 2:
                  Programa2(8, true);
                  break;
                case 3:
                  Programa3(8, true);
                  break;
                case 4:
                  Programa4(8, true);
                  break;
                case 5:
                  Programa5(8, true);
                  break;  
              }      
        }
   }
   demoOn = false;
   if (manual == 2) {
      adjustIntensity(ManualIntensityChannel1, ManualIntensityChannel2, ManualIntensityChannel3, ManualIntensityChannel4, ManualIntensityChannel5, false);
   } else {
      initProgram();
   }
}

void adjustIntensity(int Aim1,int Aim2,int Aim3,int Aim4,int Aim5, boolean gradually){
  if (gradually){
    while(Aim1 != IntensityChannel1 || Aim2 != IntensityChannel2 || Aim3 != IntensityChannel3 || Aim4 != IntensityChannel4 || Aim5 != IntensityChannel5){
        if (Aim1 != IntensityChannel1) {
           if(IntensityChannel1 > Aim1){
                IntensityChannel1--;
           } else {
                IntensityChannel1++;
           }
        }
        if (Aim2 != IntensityChannel2) {
           if(IntensityChannel2 > Aim2){
                IntensityChannel2--;
           } else {
                IntensityChannel2++;
           }     
        }
        if (Aim3 != IntensityChannel3) {
           if(IntensityChannel3 > Aim3){
                IntensityChannel3--;
           } else {
                IntensityChannel3++;
           }     
        }
        if (Aim4 != IntensityChannel4) {
           if(IntensityChannel4 > Aim4){
                IntensityChannel4--;
           } else {
                IntensityChannel4++;
           }     
        }
        if (Aim5 != IntensityChannel5) {
           if(IntensityChannel5 > Aim5){
                IntensityChannel5--;
           } else {
                IntensityChannel5++;
           }
        }
        if (demoOn == true){
          delay(4500);
        } else {
          delay(30000);
        }
    }
  } else {
    IntensityChannel1=Aim1;
    IntensityChannel2=Aim2;
    IntensityChannel3=Aim3;
    IntensityChannel4=Aim4;
    IntensityChannel5=Aim5;
  }
}

void Programa1(int hora, boolean gradually){
  lcd.setCursor(0,1);
  switch (hora) {
      case 1: //Amanecer
        AimIntensityChannel1 = 9;
        AimIntensityChannel2 = 4;
        AimIntensityChannel3 = 4;
        AimIntensityChannel4 = 0;
        AimIntensityChannel5 = 9;
        break; 
      case 2: //Mañana
        AimIntensityChannel1 = 9;
        AimIntensityChannel2 = 9;
        AimIntensityChannel3 = 9;
        AimIntensityChannel4 = 0;
        AimIntensityChannel5 = 0;
        break;      
      case 3: //Media Mañana
        AimIntensityChannel1 = 9;
        AimIntensityChannel2 = 19;
        AimIntensityChannel3 = 19;
        AimIntensityChannel4 = 0;
        AimIntensityChannel5 = 0; 
        break;    
      case 4: //Mediodia
        AimIntensityChannel1 = 9;
        AimIntensityChannel2 = 19;
        AimIntensityChannel3 = 19;
        AimIntensityChannel4 = 9;
        AimIntensityChannel5 = 9;
        break;      
      case 5: //Tarde
        AimIntensityChannel1 = 9;
        AimIntensityChannel2 = 19;
        AimIntensityChannel3 = 19;
        AimIntensityChannel4 = 0;
        AimIntensityChannel5 = 0;
        break;
      case 6: //Media tarde
        AimIntensityChannel1 = 9;
        AimIntensityChannel2 = 9;
        AimIntensityChannel3 = 9;
        AimIntensityChannel4 = 0;
        AimIntensityChannel5 = 0;
        break;  
      case 7: //Atardecer
        AimIntensityChannel1 = 9;
        AimIntensityChannel2 = 4;
        AimIntensityChannel3 = 4;
        AimIntensityChannel4 = 0;
        AimIntensityChannel5 = 9;
        break;      
      case 8: //Noche
        AimIntensityChannel1 = 0;
        AimIntensityChannel2 = 0;
        AimIntensityChannel3 = 0;
        AimIntensityChannel4 = 0;
        AimIntensityChannel5 = 0;
        break;
  }
  adjustIntensity(AimIntensityChannel1, AimIntensityChannel2, AimIntensityChannel3, AimIntensityChannel4, AimIntensityChannel5, gradually);  
}

void Programa2(int hora, boolean gradually){
  lcd.setCursor(0,1);
  switch (hora) {
      case 1: //Amanecer
        AimIntensityChannel1 = 0;
        AimIntensityChannel2 = 4;
        AimIntensityChannel3 = 9;
        AimIntensityChannel4 = 0;
        AimIntensityChannel5 = 9;
        break; 
      case 2: //Mañana
        AimIntensityChannel1 = 0;
        AimIntensityChannel2 = 9;
        AimIntensityChannel3 = 14;
        AimIntensityChannel4 = 0;
        AimIntensityChannel5 = 0;
        break;      
      case 3: //Media Mañana
        AimIntensityChannel1 = 9;
        AimIntensityChannel2 = 19;
        AimIntensityChannel3 = 19;
        AimIntensityChannel4 = 0;
        AimIntensityChannel5 = 0; 
        break;    
      case 4: //Mediodia
        AimIntensityChannel1 = 9;
        AimIntensityChannel2 = 19;
        AimIntensityChannel3 = 19;
        AimIntensityChannel4 = 9;
        AimIntensityChannel5 = 9;
        break;      
      case 5: //Tarde
        AimIntensityChannel1 = 9;
        AimIntensityChannel2 = 19;
        AimIntensityChannel3 = 19;
        AimIntensityChannel4 = 0;
        AimIntensityChannel5 = 0;
        break;
      case 6: //Media tarde
        AimIntensityChannel1 = 0;
        AimIntensityChannel2 = 9;
        AimIntensityChannel3 = 14;
        AimIntensityChannel4 = 0;
        AimIntensityChannel5 = 0;
        break;  
      case 7: //Atardecer
        AimIntensityChannel1 = 0;
        AimIntensityChannel2 = 4;
        AimIntensityChannel3 = 9;
        AimIntensityChannel4 = 0;
        AimIntensityChannel5 = 9;
        break;      
      case 8: //Noche
        AimIntensityChannel1 = 0;
        AimIntensityChannel2 = 0;
        AimIntensityChannel3 = 0;
        AimIntensityChannel4 = 0;
        AimIntensityChannel5 = 0;
        break;
  }
  adjustIntensity(AimIntensityChannel1, AimIntensityChannel2, AimIntensityChannel3, AimIntensityChannel4, AimIntensityChannel5, gradually); 
}

void Programa3(int hora, boolean gradually){
  lcd.setCursor(0,0);
  lcd.print("SeaLampControl Pr03");
  lcd.setCursor(0,1);
  switch (hora) {
      case 1: //Amanecer
        AimIntensityChannel1 = 19;
        AimIntensityChannel2 = 0;
        AimIntensityChannel3 = 0;
        AimIntensityChannel4 = 0;
        AimIntensityChannel5 = 19;
        break; 
      case 2: //Mañana
        AimIntensityChannel1 = 9;
        AimIntensityChannel2 = 9;
        AimIntensityChannel3 = 9;
        AimIntensityChannel4 = 0;
        AimIntensityChannel5 = 0;
        break;      
      case 3: //Media Mañana
        AimIntensityChannel1 = 9;
        AimIntensityChannel2 = 19;
        AimIntensityChannel3 = 19;
        AimIntensityChannel4 = 0;
        AimIntensityChannel5 = 0; 
        break;    
      case 4: //Mediodia
        AimIntensityChannel1 = 9;
        AimIntensityChannel2 = 19;
        AimIntensityChannel3 = 19;
        AimIntensityChannel4 = 9;
        AimIntensityChannel5 = 9;
        break;      
      case 5: //Tarde
        AimIntensityChannel1 = 9;
        AimIntensityChannel2 = 19;
        AimIntensityChannel3 = 19;
        AimIntensityChannel4 = 0;
        AimIntensityChannel5 = 0;
        break;
      case 6: //Media tarde
        AimIntensityChannel1 = 9;
        AimIntensityChannel2 = 9;
        AimIntensityChannel3 = 9;
        AimIntensityChannel4 = 0;
        AimIntensityChannel5 = 9;
        break;  
      case 7: //Atardecer
        AimIntensityChannel1 = 19;
        AimIntensityChannel2 = 0;
        AimIntensityChannel3 = 0;
        AimIntensityChannel4 = 0;
        AimIntensityChannel5 = 19;
        break;      
      case 8: //Noche
        AimIntensityChannel1 = 0;
        AimIntensityChannel2 = 0;
        AimIntensityChannel3 = 0;
        AimIntensityChannel4 = 0;
        AimIntensityChannel5 = 0;
        break;
  }
  adjustIntensity(AimIntensityChannel1, AimIntensityChannel2, AimIntensityChannel3, AimIntensityChannel4, AimIntensityChannel5, gradually);
  
}

void Programa4(int hora, boolean gradually){
  lcd.setCursor(0,0);
  lcd.print("SeaLampControl Pr04");
  lcd.setCursor(0,1);
  switch (hora) {
      case 1: //Amanecer
        AimIntensityChannel1 = 0;
        AimIntensityChannel2 = 4;
        AimIntensityChannel3 = 9;
        AimIntensityChannel4 = 0;
        AimIntensityChannel5 = 9;
        break; 
      case 2: //Mañana
        AimIntensityChannel1 = 0;
        AimIntensityChannel2 = 9;
        AimIntensityChannel3 = 14;
        AimIntensityChannel4 = 0;
        AimIntensityChannel5 = 0;
        break;      
      case 3: //Media Mañana
        AimIntensityChannel1 = 9;
        AimIntensityChannel2 = 19;
        AimIntensityChannel3 = 19;
        AimIntensityChannel4 = 0;
        AimIntensityChannel5 = 0; 
        break;    
      case 4: //Mediodia
        AimIntensityChannel1 = 9;
        AimIntensityChannel2 = 19;
        AimIntensityChannel3 = 19;
        AimIntensityChannel4 = 9;
        AimIntensityChannel5 = 9;
        break;      
      case 5: //Tarde
        AimIntensityChannel1 = 9;
        AimIntensityChannel2 = 19;
        AimIntensityChannel3 = 19;
        AimIntensityChannel4 = 0;
        AimIntensityChannel5 = 0;
        break;
      case 6: //Media tarde
        AimIntensityChannel1 = 0;
        AimIntensityChannel2 = 9;
        AimIntensityChannel3 = 14;
        AimIntensityChannel4 = 0;
        AimIntensityChannel5 = 0;
        break;  
      case 7: //Atardecer
        AimIntensityChannel1 = 0;
        AimIntensityChannel2 = 4;
        AimIntensityChannel3 = 9;
        AimIntensityChannel4 = 0;
        AimIntensityChannel5 = 9;
        break;      
      case 8: //Noche
        AimIntensityChannel1 = 0;
        AimIntensityChannel2 = 0;
        AimIntensityChannel3 = 0;
        AimIntensityChannel4 = 0;
        AimIntensityChannel5 = 0;
        break;
  }
  adjustIntensity(AimIntensityChannel1, AimIntensityChannel2, AimIntensityChannel3, AimIntensityChannel4, AimIntensityChannel5, gradually);
  
}

void Programa5(int hora, boolean gradually){
  lcd.setCursor(0,0);
  lcd.print("SeaLampControl Pr05");
  lcd.setCursor(0,1);
  switch (hora) {
      case 1: //Amanecer
        AimIntensityChannel1 = 0;
        AimIntensityChannel2 = 4;
        AimIntensityChannel3 = 9;
        AimIntensityChannel4 = 0;
        AimIntensityChannel5 = 9;
        break; 
      case 2: //Mañana
        AimIntensityChannel1 = 0;
        AimIntensityChannel2 = 9;
        AimIntensityChannel3 = 14;
        AimIntensityChannel4 = 0;
        AimIntensityChannel5 = 0;
        break;      
      case 3: //Media Mañana
        AimIntensityChannel1 = 9;
        AimIntensityChannel2 = 19;
        AimIntensityChannel3 = 19;
        AimIntensityChannel4 = 0;
        AimIntensityChannel5 = 0; 
        break;    
      case 4: //Mediodia
        AimIntensityChannel1 = 9;
        AimIntensityChannel2 = 19;
        AimIntensityChannel3 = 19;
        AimIntensityChannel4 = 9;
        AimIntensityChannel5 = 9;
        break;      
      case 5: //Tarde
        AimIntensityChannel1 = 9;
        AimIntensityChannel2 = 19;
        AimIntensityChannel3 = 19;
        AimIntensityChannel4 = 0;
        AimIntensityChannel5 = 0;
        break;
      case 6: //Media tarde
        AimIntensityChannel1 = 0;
        AimIntensityChannel2 = 9;
        AimIntensityChannel3 = 14;
        AimIntensityChannel4 = 0;
        AimIntensityChannel5 = 0;
        break;  
      case 7: //Atardecer
        AimIntensityChannel1 = 0;
        AimIntensityChannel2 = 4;
        AimIntensityChannel3 = 9;
        AimIntensityChannel4 = 0;
        AimIntensityChannel5 = 9;
        break;      
      case 8: //Noche
        AimIntensityChannel1 = 0;
        AimIntensityChannel2 = 0;
        AimIntensityChannel3 = 0;
        AimIntensityChannel4 = 0;
        AimIntensityChannel5 = 0;
        break;
  }
  adjustIntensity(AimIntensityChannel1, AimIntensityChannel2, AimIntensityChannel3, AimIntensityChannel4, AimIntensityChannel5, gradually);
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
  //Serial.println("HoraActual: "+String(myRTC.hours)+" HoraMediaManana "+String(hora_mediamanana)+" HoraManana "+String(hora_manana));
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

ISR(TIMER1_COMPA_vect){  //change the 0 to 1 for timer1 and 2 for timer2
   //interrupt commands here
   interrupt_timer++;
   if(interrupt_timer > 19){
      interrupt_timer = 0;
      if (IntensityChannel1 != interrupt_timer){
        digitalWrite(Channel1,HIGH);
      }
      if (IntensityChannel2 != interrupt_timer){
        digitalWrite(Channel2,HIGH);
      }
      if (IntensityChannel3 != interrupt_timer){
        digitalWrite(Channel3,HIGH);
      }
      if (IntensityChannel4 != interrupt_timer){
        digitalWrite(Channel4,HIGH);
      }
      if (IntensityChannel5 != interrupt_timer){
        digitalWrite(Channel5,HIGH);
      }
   } 
   if (IntensityChannel1 == interrupt_timer){
      digitalWrite(Channel1,LOW);
   }
   if (IntensityChannel2 == interrupt_timer){
      digitalWrite(Channel2,LOW);
   }
   if (IntensityChannel3 == interrupt_timer){
      digitalWrite(Channel3,LOW);
   }
   if (IntensityChannel4 == interrupt_timer){
      digitalWrite(Channel4,LOW);
   }
   if (IntensityChannel5 == interrupt_timer){
      digitalWrite(Channel5,LOW);
   }
}
