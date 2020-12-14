
#include <Servo.h>

Servo Dispenser1;  // create servo object to control a servo
const int SP1 = A0; //Constante donde guardar el sensor 1
const int Servo1 = 9;   //Constante donde guardar el pin del servo 1

int n;           //Variable para guardar n pastillas.
int pos = 180;     // variable to store the servo position
int i =0;       //Variable para contar pastillas.
int trend1;

bool VS1 = 0;         //Variable para la deteccion de pastillas --> 0 no pasti, 1 pasti
void setup() {
  Serial.begin(9600);
 Dispenser1.attach(Servo1);   // attaches the servo on pin 9 to the servo object
 //pinMode(SP1,INPUT);
 Dispenser1.write(pos);
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
 
 
     
  while(analogRead(SP1)< 200){          //Mientras no detecte ninguna pastilla gira el servo
    analogRead(SP1);                    //Lee la entrada analógica
    if(pos == 180 )                     //Cambio de sentido
    trend1 = -1;
    analogRead(SP1);                     //Lee la entrada analógica
    if(pos == 0)                        //Cambio de sentido
    trend1 = 1;
    analogRead(SP1);                      //Lee la entrada analógica
   pos = pos + trend1;                    //No se como explicarlo pero se entiende
    analogRead(SP1);                       //Lee la entrada analógica
    Dispenser1.write(pos);                //Mueve el servo a posicion pos
    analogRead(SP1);                       //Lee la entrada analógica
   delay(10); 
   analogRead(SP1);                        //Lee la entrada analógica
}
delay(1000);
i++;                                       //Añade una pastilla a la cuenta
//Serial.println(i);
analogRead(SP1);                          //Si el valor sigue siendo uno, por que se ha atascado o algo, no entra en el bucle anterior. Además ¿reinicia el valor? IDK pero funciona
    }
 //Serial.println("HIIIIII");               
   i=0;                                   //Reinicia el contador a cero
   }
   
  
}
 }   
