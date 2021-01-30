void pill( int n,  int DN) {
     // dbSerialPrint("DN:");
      //  dbSerialPrintln(DN);
      if(i2 == 0){
mp3_set_volume (20);
    mp3_play (5);
      }
counter2++;

i = 0;
while( i < n ){             //Bucle hasta que dispensemos, n pastillas.
       //     dbSerialPrintln("estoy dentro");
switch(DN) {                //En función del número del dispensador, asigna un servo y un sensor al algoritmo de abajo. 
  case 1:                   //De esta manera se supone que simplifca el codigo.
Dispensador = 0;
PillSensor = SP0;
break;
   case 2:
    //dbSerialPrintln("Dsi 7");
   Dispensador = 7;
PillSensor = SP1;
break;
 case 3:
 Dispensador = 9;
PillSensor = SP2;
break;
 case 4:
 Dispensador = 16;
PillSensor = SP3;
break;
  }
  
for(int i=0;i<400;i++){                                       //Toma 200 valores del sensor en vacío y hace la media
// dbSerialPrintln(i);
  int x = analogRead(PillSensor);
  if(umbral < x  )                        ///De esta manera calibramos el sensor antes de cada uso.
  umbral = x;
 delayMicroseconds(1);
  }
  umbral = umbral+5;
  
while(analogRead(PillSensor)< umbral){          //Mientras no detecte ninguna pastilla gira el servo


    analogRead(PillSensor);                    //Lee la entrada analógica
    if(pos >= SERVOMAX )                     //Cambio de sentido
    trend1 = -1;
    
    analogRead(PillSensor);    
     if(pos <= SERVOMIN + 100 && pos > SERVOMIN && trend1 < 0 )
     periodo=100;
     else
    periodo = 10;
analogRead(PillSensor);    
    
    
    
    analogRead(PillSensor);                     //Lee la entrada analógica
    if(pos <= SERVOMIN)                        //Cambio de sentido
    trend1 = 1;
   // dbSerialPrintln(trend1);
    analogRead(PillSensor);                      //Lee la entrada analógica
    
    if(millis()-tiempoAnterior>=periodo){  //si ha transcurrido el periodo programado
    pos = pos + trend1;                           //No se como explicarlo pero se entiende
    tiempoAnterior=millis();                        //guarda el tiempo actual como referencia
   
     analogRead(PillSensor);                       //Lee la entrada analógica
     dbSerialPrint(umbral);
     dbSerialPrint(" ");
     dbSerialPrintln(analogRead(PillSensor));
  pwm.setPWM(Dispensador,0, pos);
 
    analogRead(PillSensor);                       //Lee la entrada analógica
  //  dbSerialPrintln(PillSensor);
  
    }}

while(analogRead(PillSensor) > umbral){
//do nothing
  }
i++;                                       //Añade una pastilla a la cuenta
   // dbSerialPrintln(i);

analogRead(PillSensor);                          //Si el valor sigue siendo uno, por que se ha atascado o algo, no entra en el bucle anterior. Además ¿reinicia el valor? IDK pero funciona
}

progress = map(counter2,0,counter,0,100);
progressPill.setValue(progress);
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



 void endPill(){
  State2 = LOW;  
State3 = LOW;
State = LOW;
Serial.println("Salí");
counter = 0;
counter2 = 0;
page0.show();
  mp3_set_volume (25);
  mp3_play (2);
while(sonar.ping_cm() < 6 ){
  prevUM = -1;
  getRTC();
  int cero = 0;
  DecenaTH.setValue(cero);                  //In order to express the time in this format --> 01:00
  UnidadTH.setValue(cero);                  //It's needed to descompoose number into tens, and unities
                                              //Decena = tens, Unidad = Unities
  DecenaTM.setValue(cero);
  UnidadTM.setValue(cero);
  delay(10);
  nexLoop(nex_listen_list);
delay(100);
  }
  DecenaTH.setValue('0');                  //In order to express the time in this format --> 01:00
  UnidadTH.setValue('0');                  //It's needed to descompoose number into tens, and unities
                                              //Decena = tens, Unidad = Unities
  DecenaTM.setValue('0');
  UnidadTM.setValue('0');
  mp3_set_volume (25);
  Serial3.println("pill 1");
  mp3_play (3);
  delay(2500);
  mp3_play (4);
  i2 = 0;
  
  prevUM = -1;
  StateTemp = 1;
  getRTC();
  
  
  }
   
