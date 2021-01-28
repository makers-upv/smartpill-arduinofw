void prePill(){
    //Serial.println("Pre");
  if(State2 == LOW){
    if(rep == 0){
       mp3_set_volume (25);
    mp3_play (1);
    rep =1;}
  page1.show();   
  if(preGlass != Glass)
delay(1000);
   preGlass = Glass;              
State2 = HIGH;
State3 = LOW;
  }} 




  
 void glass(){
 // Serial.println("vaso");
  if(State3 == LOW){
    if(rep == 0){
    mp3_play (1);
    rep = 1;
    }
  page7.show();
  if(preGlass != Glass)
delay(1000);
   preGlass = Glass;
 // mp3_play (1);                   
State3 = HIGH;
State2 = LOW;

  }}


  //Ni lo explico, no hay nada todavía xD
