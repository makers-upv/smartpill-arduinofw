void buttonPushCallBack(void *ptr){                          //Function with routines  to execute  when the button is pressed
  //dbSerialPrintln("HOLA MUNDO");
  
    page0.show();                                             //It shows page 0
    prevUM = -1;
    getRTC();

    rep = 0;
    State2=LOW;                                               //And basically restart states
    State=LOW; 
    
    
  }                                                           //It should call "Pill()" too, but it's not implementede yet.

void RD1PushCallBack(void *ptr){                          //Function with routines  to execute  when the button is pressed
  mp3_set_volume (15);
  mp3_play (5); 
  digitalWrite(ServoRelay,LOW);
  
for(int k=0;k < 60;k = k+2){
     j0.setValue(k);
    delay(1);
    
}
servo.rotate((D1P,1));
delay(1);
digitalWrite(ServoRelay,HIGH);

for(int k=60;k < 100;k=k+2 ){
     j0.setValue(k);
    delay(1);
}
      page5.show();
 }      

void RD2PushCallBack(void *ptr){                          //Function with routines  to execute  when the button is pressed
   mp3_set_volume (15);
   mp3_play (5); 
   digitalWrite(ServoRelay,LOW);

  int posA = servo.Angle();
  int distance = posA - D2P;
  for(int k = posA; k > D2P;k=k-15 ){
    servo.rotate(k,1);
    delay(1);
    int j = map(k-D2P,0,distance,100,0);
    j0.setValue(j);
    }
digitalWrite(ServoRelay,HIGH);
    page5.show();
  }

  void RD3PushCallBack(void *ptr){                          //Function with routines  to execute  when the button is pressed
    mp3_set_volume (15);
   mp3_play (5); 
   digitalWrite(ServoRelay,LOW);

  int posA = servo.Angle();
  int distance = posA - D3P;
  for(int k = posA; k > D3P;k=k-15 ){
    servo.rotate(k,1);
    delay(1);
    int j = map(k-D3P,0,distance,100,0);
    j0.setValue(j);
    
    }
digitalWrite(ServoRelay,HIGH);
    page5.show();
  }       

  void RD4PushCallBack(void *ptr){                          //Function with routines  to execute  when the button is pressed
    mp3_set_volume (15);
   mp3_play (5); 
   digitalWrite(ServoRelay,LOW);

  int posA = servo.Angle();
  int distance = posA - D4P;
  for(int k = posA; k > D4P;k=k -(k-D4P)*0.3 ){
    servo.rotate(k,1);
    delay(1);
    int j = map(k-D4P,0,distance,100,0);
    j0.setValue(j);
    }
digitalWrite(ServoRelay,HIGH);
    page5.show();
  }

 void extitRPushCallBack(void *ptr){                          //Function with routines  to execute  when the button is pressed
    digitalWrite(ServoRelay ,LOW);
     servo.rotate(restP,1);
     delay(1);
     digitalWrite(ServoRelay,HIGH); 
     
  mp3_stop (); 
  getRTC();
  page0.show();
  prevUM=-1;
  getRTC();

     
}
   void settingsPush(void *ptr) {
    
   // TRD1.setText("Refill");
    
    
    }    
