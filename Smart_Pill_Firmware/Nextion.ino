void buttonPushCallBack(void *ptr){                          //Function with routines  to execute  when the button is pressed
  //dbSerialPrintln("HOLA MUNDO");
  
    page0.show();                                             //It shows page 0
    prevUM = -1;
    getRTC();
    
    State2=LOW;                                               //And basically restart states
    State=LOW; 
    
    
  }                                                           //It should call "Pill()" too, but it's not implementede yet.

void RD1PushCallBack(void *ptr){                          //Function with routines  to execute  when the button is pressed
  dbSerialPrintln("HOLA MUNDO 1");
  digitalWrite(ServoRelay,LOW);
  delay(200);

  if(servo.Angle()< D1P-dAngle || servo.Angle() >D1P+dAngle){
     servo.rotate(D1P,1);
     }
     digitalWrite(ServoRelay,HIGH);
     delay(200);
  }      

void RD2PushCallBack(void *ptr){                          //Function with routines  to execute  when the button is pressed
  dbSerialPrintln("HOLA MUNDO 2");
   digitalWrite(ServoRelay,LOW);
  delay(200);

  if(servo.Angle()< D2P-dAngle || servo.Angle() >D2P+dAngle){
     servo.rotate(D2P,1);
     }
     digitalWrite(ServoRelay,HIGH);
     delay(200);
  }      

  void RD3PushCallBack(void *ptr){                          //Function with routines  to execute  when the button is pressed
  dbSerialPrintln("HOLA MUNDO 3");
   digitalWrite(ServoRelay,LOW);
  delay(200);

  if(servo.Angle()< D3P-dAngle || servo.Angle() >D3P+dAngle){
     servo.rotate(D3P,1);
     }
     digitalWrite(ServoRelay,HIGH);
     delay(200);
  }       

  void RD4PushCallBack(void *ptr){                          //Function with routines  to execute  when the button is pressed
  dbSerialPrintln("HOLA MUNDO 4");
   digitalWrite(ServoRelay,LOW);
  delay(200);

  if(servo.Angle()< D4P-dAngle || servo.Angle() >D4P+dAngle){
     servo.rotate(D4P,1);
     }
     digitalWrite(ServoRelay,HIGH);
     delay(200);
  }       
       
