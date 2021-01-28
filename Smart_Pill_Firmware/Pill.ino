void pill( int n,  int DN) {
     // dbSerialPrint("DN:");
      //  dbSerialPrintln(DN);

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
  
for(int i=0;i<200;i++){                                       //Toma 200 valores del sensor en vacío y hace la media
// dbSerialPrintln(i);
  int x = analogRead(PillSensor);
  if(umbral < x  )                        ///De esta manera calibramos el sensor antes de cada uso.
  umbral = x;
 delayMicroseconds(1);
  }
  umbral = umbral+ 10;
  
while(analogRead(PillSensor)< umbral){          //Mientras no detecte ninguna pastilla gira el servo


    analogRead(PillSensor);                    //Lee la entrada analógica
    if(pos >= SERVOMAX )                     //Cambio de sentido
    trend1 = -1;
    
 /* if(tamanyo == 1){             //Agitar o no en función de la pastilla
    if(pos <= SERVOMIN + 150 && pos > SERVOMIN && trend1 < 0 ) {                    //Cambio de sentido pos >= SERVOMAX- 100 && pos < SERVOMAX || 
    periodo = 50;
     if(pos <= SERVOMIN + 10 && pos > SERVOMIN && trend1 < 0 )
     periodo=100;
     else
    periodo = 10;
  if(pos == SERVOMIN + 200  && trend1 < 0 ) {
    for(int k= 0; k < 10; k++){
      for (pos = pos; pos < SERVOMAX-180; pos++) {
    pwm.setPWM(Dispensador, 0, pos);
    delay(1);
  } 
  for (pos = pos; pos > SERVOMIN+170;pos--) {
    pwm.setPWM(Dispensador, 0, pos);
    delay(1);
  }
    }}}
    
    }*/
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
  // pwm.setPWM(Dispensador, 0, pos);                //Mueve el servo a posicion pos
  // for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
   // pwm.setPWM(Dispensador, 0, pulselen);
 // }

 // delay(500);
  //for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
   // pwm.setPWM(Dispensador, 0, pulselen);
  //}
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
   
