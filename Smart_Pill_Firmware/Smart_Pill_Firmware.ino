#include "stdint.h"
#include "string.h"
#include <NewPing.h>
#include <Nextion.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <PCF85063TP.h>
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
#include <FeedBackServo.h>

#define SERVOMIN  70                             // This is the 'minimum' pulse length count (out of 4096) 150 defualt 70
#define SERVOMAX   600                       // This is the 'maximum' pulse length count (out of 4096) 600       500
#define SERVO_FREQ 50                           // Analog servos run at ~50 Hz updates

//#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
//#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600

#define FEEDBACK_PIN 2
#define SERVO_PIN 3

FeedBackServo servo = FeedBackServo(FEEDBACK_PIN);

SoftwareSerial mySerial(10, 11); // RX, TX




unsigned long tiempoAnterior = 0;                //Store reference time to compare
unsigned long previousMillis = 0;                // will store last time "getClock" was updated


const long interval = 1000;                       


PCD85063TP RTclock;                     //define a object of PCD85063TP class

//////////////////////////////////////
//////////Nextion Stuff///////////////
//////////////////////////////////////

NexButton button = NexButton(1,1,"b0");                       //Button to confirm pill dispense
NexButton RD1 = NexButton(3,1,"b0");                       //Button to confirm pill dispense
NexButton RD2 = NexButton(3,2,"b1");                       //Button to confirm pill dispense
NexButton RD3 = NexButton(3,3,"b2");                       //Button to confirm pill dispense
NexButton RD4 = NexButton(3,4,"b3");                       //Button to confirm pill dispense
NexButton extitR = NexButton(5,1,"b0");                       //Button to confirm pill dispense
NexButton settings = NexButton(0,13,"b0");                       //Button to confirm pill dispense

NexText t0 = NexText(0, 16, "t0");                            //Text to store the  date
NexText TRD1 = NexText(3, 6, "t1");
NexText TRD2 = NexText(3, 7, "t2");
NexText TRD3 = NexText(3, 8, "t3");
NexText TRD4 = NexText(3, 9, "t4");


NexNumber  DecenaH = NexNumber (0, 11, "n0");                  //Some numerical variables in order
NexNumber  UnidadH= NexNumber (0, 12, "n1");                   //to display a clock
NexNumber  DecenaM = NexNumber (0, 13, "n2");
NexNumber  UnidadM = NexNumber (0, 14, "n3");

  
NexPage page0 = NexPage(0,0 , "page0");                         
NexPage page1 = NexPage(1,0 , "page1");
NexPage page2 = NexPage(2,0 , "page2");
NexPage page3 = NexPage(3,0 , "page3");
NexPage page4 = NexPage(4,0 , "page4");
NexPage page5 = NexPage(5,0 , "page5");
NexPage page6 = NexPage(6,0 , "page6");
NexPage page7 = NexPage(7,0 , "page7");

NexProgressBar  j0 = NexProgressBar (4, 1, "j0");


NexTouch *nex_listen_list[]={                                   //It defines what  objects send a response when touched
  &button,                                                      //Now only the button can be pressed
  &RD1,
  &RD2,
  &RD3,
  &RD4,
  &extitR,
  &TRD1,
  &TRD2,
  &TRD3,
  &TRD4,
  &settings,
  NULL
  };

 


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();      //Stuff to operate servos, idk how it works


const int SP0 = A1;                                            //Some constants in order to store analog pins
const int SP1 = A2;                                            //They will be used in Pill tab
const int SP2 = A3;
const int SP3 = A0;

const int restP = 310;                                          //Some postions 
const int D1P = 0;
const int D2P = 90;
const int D3P = 180;
const int D4P = 270;

 
const int UltrasonicPin = 5;
const int MaxDistance = 200;

const int ServoRelay = 4;
const int dAngle= 5;


int Dispensador = 0;                                          //A variable in order to change the dispenser used
int PillSensor; 
int n;                                                        //Variable to store n pills
int pos;                                                      // Variable to store the servo position
int i = 0;                                                    //Variable to count pills

          
int periodo = 10;                                           
int umbral = 0;                                               //Variable to calibrate each sensor before it uses

                           
int UM = 0;                                                   // This two variables are used to control the amount of times
int prevUM = -1;                                              //that  is being refreshed the display        

int  trend1;                                                   //It defines the rotation sense of servos 

bool tamanyo = 0;
bool VS1 = 0;                                                  //It used to detect pills  --> 0 no pill, 1 pill

bool State = 0;                                                //Just some states in order to make stuff work.
bool State2 = 0;
bool State3 = 0;
bool rep = 0;
bool Glass = 1;
bool preGlass = 1;
NewPing sonar(UltrasonicPin, UltrasonicPin, MaxDistance);

void setup() {
   getRTC();
  

  Serial.begin(9600);
  Serial3.begin(9600);
  
  mySerial.begin (9600);
  mp3_set_serial (mySerial);  //set softwareSerial for DFPlayer-mini mp3 module 
  mp3_set_volume (25);
  mp3_stop (); 
  
  pos = SERVOMAX;                                             
  pwm.begin();                                                  //It start an configurate servo stuf, frecuency, etc...
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
  delay(10);

  

nexInit();                                                      //Iniziate nextion display 
button.attachPush(buttonPushCallBack,&button);                  //Declare a button interrupotion?? IDK
RD1.attachPush(RD1PushCallBack,&RD1);                
RD2.attachPush(RD2PushCallBack,&RD2);                  
RD3.attachPush(RD3PushCallBack,&RD3);                  
RD4.attachPush(RD4PushCallBack,&RD4);  
extitR.attachPush(extitRPushCallBack,&extitR);  
TRD1.attachPush(RD1PushCallBack,&TRD1);                
TRD2.attachPush(RD2PushCallBack,&TRD2);                  
TRD3.attachPush(RD3PushCallBack,&TRD3);                  
TRD4.attachPush(RD4PushCallBack,&TRD4);  
settings.attachPush(settingsPush,&settings);

dbSerialPrintln("setup done");

 servo.setServoControl(SERVO_PIN);
 servo.setKp(0.2);
    
pinMode(ServoRelay,OUTPUT);
//digitalWrite(ServoRelay ,LOW);

    //servo.rotate(restP,1);
     
    digitalWrite(ServoRelay,HIGH);
     delay(1000);

}

void loop() {
  if(Serial3.available()> 0){
  parser();
  }

    
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {           //Some stuff in order to call getClock every second 
    // save the last time you blinked the LED
    previousMillis = currentMillis;
  getRTC();
 

  }
 
nexLoop(nex_listen_list);
 dbSerialPrintln("h");
}

 
  
