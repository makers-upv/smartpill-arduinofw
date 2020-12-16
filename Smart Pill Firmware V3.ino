
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVOMIN  70 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  500 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates


unsigned long tiempoAnterior = 0;  //guarda tiempo de referencia para comparar

uint8_t Dispensador = 0;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();


const int SP1 = A0; //Constante donde guardar el sensor 1


int n;           //Variable para guardar n pastillas.
int pos;     // variable to store the servo position
int i =0;       //Variable para contar pastillas.
int trend1;
int periodo; 

bool VS1 = 0;         //Variable para la deteccion de pastillas --> 0 no pasti, 1 pasti
void setup() {
  pos = SERVOMAX;
  Serial.begin(9600);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
  delay(10);

}

void loop() {

      if(Serial.available() > 0) //Detecta si hay alguna entrada por serial
   {
      n = Serial.parseInt();    //Guardar la entrada como entero
   if (n >=1){                  //Si es mayor de cero 
    while( i < n ){             //Bucle hasta que dispensemos, n pastillas.

 ////////////////////////////////////////////////////////////////////
 ////////////////////////////////////////////////////////////////////
 ////////////////////////////////////////////////////////////////////

 
         
  while(analogRead(SP1)< 650){          //Mientras no detecte ninguna pastilla gira el servo
    
    analogRead(SP1);                    //Lee la entrada analógica
    if(pos >= SERVOMAX )                     //Cambio de sentido
    trend1 = -1;
    if(pos <= SERVOMIN + 150 && pos > SERVOMIN && trend1 < 0 ) {                    //Cambio de sentido pos >= SERVOMAX- 100 && pos < SERVOMAX || 
    periodo = 50;
     if(pos <= SERVOMIN + 10 && pos > SERVOMIN && trend1 < 0 )
     periodo=100;
    } else
    periodo = 10;
  if(pos == SERVOMIN + 200  && trend1 < 0 ) {
    for(int k= 0; k < 51; k++){
      for (pos = pos; pos < SERVOMAX-150; pos++) {
    pwm.setPWM(Dispensador, 0, pos);
    delay(1);
  } 
  for (pos = pos; pos > SERVOMIN+150;pos--) {
    pwm.setPWM(Dispensador, 0, pos);
    delay(1);
  }
    }
    
    }
    analogRead(SP1);                     //Lee la entrada analógica
    if(pos <= SERVOMIN)                        //Cambio de sentido
    trend1 = 1;
    analogRead(SP1);                      //Lee la entrada analógica
    
    if(millis()-tiempoAnterior>=periodo){  //si ha transcurrido el periodo programado
    pos = pos + trend1;                           //No se como explicarlo pero se entiende
    tiempoAnterior=millis();  //guarda el tiempo actual como referencia
     analogRead(SP1);                       //Lee la entrada analógica
    pwm.setPWM(Dispensador, 0, pos);                //Mueve el servo a posicion pos
    analogRead(SP1);                       //Lee la entrada analógica
    }}

while(analogRead(SP1) > 600){
//do nothing
  }
i++;                                       //Añade una pastilla a la cuenta
Serial.println(i);
analogRead(SP1);                          //Si el valor sigue siendo uno, por que se ha atascado o algo, no entra en el bucle anterior. Además ¿reinicia el valor? IDK pero funciona
    }
// Serial.println("HIIIIII");               
   i=0;                                   //Reinicia el contador a cero
   for (pos = pos; pos < SERVOMAX-100; pos= pos +10) {
    pwm.setPWM(Dispensador, 0, pos);
    delay(5);
  }
    for (pos = pos; pos < SERVOMAX; pos= pos +5) {
    pwm.setPWM(Dispensador, 0, pos);
    delay(20);
  }
   }
   
  
}
 }   
