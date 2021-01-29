void prePill(){
  mp3_stop ();
    //Serial.println("Pre");
     
  if(State2 == LOW){
    page1.show();
    if(rep == 0){   
       mp3_set_volume (25);
    mp3_play (1);
    delay(3500);
    rep =1;}
  if(preGlass != Glass)
delay(1000);
   preGlass = Glass;              
State2 = HIGH;
State3 = LOW;
  }} 




  
 void glass(){
 //Serial.println("vaso");
  unsigned long currentMillis = millis();

 if (currentMillis - previousMillis >= intervalAmong) {           //Some stuff in order to call getClock every second 
    // save the last time you blinked the LED
    previousMillis = currentMillis;
  mp3_set_volume (10);
 mp3_play (6);
  }

 
 
  if(State3 == LOW){
    page7.show();
    if(rep == 0){
       mp3_set_volume (20);
    mp3_play (1);
        delay(3500);
        mp3_set_volume (10);
 mp3_play (6);
    rep = 1;
    }
  
  if(preGlass != Glass)
delay(1000);
   preGlass = Glass;
 // mp3_play (1);                   
State3 = HIGH;
State2 = LOW;

  }}


  //Ni lo explico, no hay nada todavía xD
