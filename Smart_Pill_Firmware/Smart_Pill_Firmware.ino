
#include <NewPing.h>
#include <Nextion.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <PCF85063TP.h>
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
#include <FeedBackServo.h>

#define SERVOMIN  70                            // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  500                           // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50                           // Analog servos run at ~50 Hz updates

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

NexText t0 = NexText(0, 16, "t0");                            //Text to store the  date

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




NexTouch *nex_listen_list[]={                                   //It defines what  objects send a response when touched
  &button,                                                      //Now only the button can be pressed
  &RD1,
  &RD2,
  &RD3,
  &RD4,
  NULL
  };

 


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();      //Stuff to operate servos, idk how it works


const int SP0 = A0;                                            //Some constants in order to store analog pins
const int SP1 = A1;                                            //They will be used in Pill tab
const int SP2 = A2;
const int SP3 = A3;

const int restP = 310;                                          //Some postions 
const int D1P = 0;
const int D2P = 90;
const int D3P = 180;
const int D4P = 270;

 
const int UltrasonicPin = 5;
const int MaxDistance = 200;

const int ServoRelay = 4;
const int dAngle= 15;

int Dispensador = 0;                                          //A variable in order to change the dispenser used
int PillSensor; 
int n;                                                        //Variable to store n pills
int pos;                                                      // Variable to store the servo position
int i = 0;                                                    //Variable to count pills

          
int periodo = 10;                                           
int umbral = 0;                                               //Variable to calibrate each sensor before it uses

                           
int UM = 0;                                                   // This two variables are used to control the amount of times
int prevUM = -1;                                              //that  is being refreshed the display        

int temp;


bool trend1;                                                   //It defines the rotation sense of servos 
bool tamanyo = 0;
bool VS1 = 0;                                                  //It used to detect pills  --> 0 no pill, 1 pill

bool State = 0;                                                //Just some states in order to make stuff work.
bool State2 = 0;

NewPing sonar(UltrasonicPin, UltrasonicPin, MaxDistance);

void setup() {
   getRTC();

  Serial.begin(9600);
  
  mySerial.begin (9600);
  mp3_set_serial (mySerial);  //set softwareSerial for DFPlayer-mini mp3 module 
  mp3_set_volume (25);

  
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
dbSerialPrintln("setup done");

 servo.setServoControl(SERVO_PIN);
 servo.setKp(1.0);
    
pinMode(ServoRelay,OUTPUT);
digitalWrite(ServoRelay ,LOW);

if(servo.Angle()< restP-dAngle || servo.Angle() > restP+dAngle){
     servo.rotate(restP,1);
     }
     digitalWrite(ServoRelay,HIGH);
     delay(1000);

}

void loop() {
  
 if (State == LOW){                                           //This if makes able to change between pages
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {           //Some stuff in order to call getClock every second 
    // save the last time you blinked the LED
    previousMillis = currentMillis;
  getRTC();
  temp++;
  if(temp == 5)
  State = HIGH;
  }}
  else
    prePill();           
  

nexLoop(nex_listen_list);
 
}

 
  
