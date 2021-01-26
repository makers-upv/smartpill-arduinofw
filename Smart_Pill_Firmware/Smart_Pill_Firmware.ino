
#include <Nextion.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <PCF85063TP.h>

#define SERVOMIN  70                            // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  500                           // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50                           // Analog servos run at ~50 Hz updates


unsigned long tiempoAnterior = 0;                //Store reference time to compare
unsigned long previousMillis = 0;                // will store last time "getClock" was updated


const long interval = 1000;                       


PCD85063TP RTclock;                     //define a object of PCD85063TP class

//////////////////////////////////////
//////////Nextion Stuff///////////////
//////////////////////////////////////

NexButton button = NexButton(1,1,"b0");                       //Button to confirm pill dispense

NexText t0 = NexText(0, 16, "t0");                            //Text to store the  date

NexNumber  DecenaH = NexNumber (0, 11, "n0");                  //Some numerical variables in order
NexNumber  UnidadH= NexNumber (0, 12, "n1");                   //to display a clock
NexNumber  DecenaM = NexNumber (0, 13, "n2");
NexNumber  UnidadM = NexNumber (0, 14, "n3");

  
NexPage page0 = NexPage(0,0 , "page0");                         
NexPage page1 = NexPage(1,0 , "page1");

void t0PopCallback(void*ptr);


NexTouch *nex_listen_list[]={                                   //It defines what  objects send a response when touched
  &button,                                                      //Now only the button can be pressed
  NULL
  };

 

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();      //Stuff to operate servos, idk how it works


const int SP0 = A0;                                            //Some constants in order to store analog pins
const int SP1 = A1;                                            //They will be used in Pill tab
const int SP2 = A2;
const int SP3 = A3;

int Dispensador = 0;                                          //A variable in order to change the dispenser used
int PillSensor; 
int n;                                                        //Variable to store n pills
int pos;                                                      // Variable to store the servo position
int i = 0;                                                    //Variable to count pills

          
int periodo = 10;                                           
int umbral = 0;                                               //Variable to calibrate each sensor before it uses

                           
int UM = 0;                                                   // This two variables are used to control the amount of times
int prevUM = -1;                                              //that  is being refreshed the display        

bool trend1;                                                   //It defines the rotation sense of servos 
bool tamanyo = 0;
bool VS1 = 0;                                                  //It used to detect pills  --> 0 no pill, 1 pill

bool State = 1;                                                //Just some states in order to make stuff work.
bool State2 = 0;


void setup() {
  pos = SERVOMAX;                                             
  Serial.begin(9600);
  pwm.begin();                                                  //It start an configurate servo stuf, frecuency, etc...
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
  delay(10);


nexInit();                                                      //Iniziate nextion display 
button.attachPush(buttonPushCallBack,&button);                  //Declare a button interrupotion?? IDK
dbSerialPrintln("setup done");

}

void loop() {
      if(Serial.available() > 0)                              //Detecta si hay alguna entrada por serial
   {
      n = Serial.parseInt();                                  //Guardar la entrada como entero
   if (n >=1){                                                //Si es mayor de cero 
    
 }}
 
 if (State == LOW){                                           //This if makes able to change between pages
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {           //Some stuff in order to call getClock every second 
    // save the last time you blinked the LED
    previousMillis = currentMillis;
  getRTC();
  }}
  else{
    prePill();                                            
    }

nexLoop(nex_listen_list);
 }


 void buttonPushCallBack(void *ptr){                          //Function with routines  to execute  when the button is pressed
 // dbSerialPrintln("HOLA MUNDO");
    page0.show();                                             //It shows page 0
    State2=LOW;                                               //And basically restart states
    State=LOW;  
  }                                                           //It should call "Pill()" too, but it's not implementede yet.


  
