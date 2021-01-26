
#include "Nextion.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "PCF85063TP.h"

#define SERVOMIN  70 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  500 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates


unsigned long tiempoAnterior = 0;  //guarda tiempo de referencia para comparar
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 1000; 


PCD85063TP RTclock;//define a object of PCD85063TP class
NexButton button = NexButton(1,1,"b0");
NexText t0 = NexText(0, 16, "t0");

NexNumber  DecenaH = NexNumber (0, 11, "n0");
NexNumber  UnidadH= NexNumber (0, 12, "n1");
NexNumber  DecenaM = NexNumber (0, 13, "n2");
NexNumber  UnidadM = NexNumber (0, 14, "n3");


NexPage page0 = NexPage(0,0 , "page0");
NexPage page1 = NexPage(1,0 , "page1");

void t0PopCallback(void*ptr);


NexTouch *nex_listen_list[]={
  &button,
  NULL
  };

 




Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
const int SP0 = A0;
const int SP1 = A1;
const int SP2 = A2;
const int SP3 = A3;

int Dispensador = 0;
int PillSensor;
int n;           //Variable para guardar n pastillas.
int pos;     // variable to store the servo position
int i =0;       //Variable para contar pastillas.
int trend1;
int periodo = 10; 
int umbral = 0;

int prevUM = -1;
int UM = 0;

bool tamanyo = 0;
bool VS1 = 0;         //Variable para la deteccion de pastillas --> 0 no pasti, 1 pasti

bool State = 1;
bool State2 = 0;


void setup() {
  pos = SERVOMAX;
  Serial.begin(9600);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
  delay(10);


nexInit();
button.attachPush(buttonPushCallBack,&button);
dbSerialPrintln("setup done");

}

void loop() {
      if(Serial.available() > 0) //Detecta si hay alguna entrada por serial
   {
      n = Serial.parseInt();    //Guardar la entrada como entero
   if (n >=1){                  //Si es mayor de cero 
    
 }}
 
 if (State == LOW){
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
  getRTC();
  }}
  else{
    prePill();   
    }

nexLoop(nex_listen_list);
 }


 void buttonPushCallBack(void *ptr){
 // dbSerialPrintln("HOLA MUNDO");
    page0.show();
    State2=LOW;
    State=LOW;
  }


  
