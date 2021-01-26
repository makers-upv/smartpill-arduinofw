void getRTC(){
int Hour;                                       //Defining some variables in order to make the clock work
int Mins;

String str1 = "Monday";                         //Here is being defined some strings in orer to compund a setence later.
String str2 = "1";
String str3 = "";
String str4 = "th";
String str5 = "January";
String str6 = "2021";

  RTclock.getTime();                          //Get's data from RTC

  Hour = RTclock.hour;                       
  Mins = RTclock.minute;

  UM = Mins%10;                               //Mechanism in order to refresh only when it's needed
                                              //Otherwise the screen would start blinking
  if(UM != prevUM){
prevUM = UM;

  DecenaH.setValue(Hour/10);                  //In order to express the time in this format --> 01:00
  UnidadH.setValue(Hour%10);                  //It's needed to descompoose number into tens, and unities
                                              //Decena = tens, Unidad = Unities
  DecenaM.setValue(Mins/10);
  UnidadM.setValue(UM);


switch (RTclock.dayOfWeek) { // It stores the day into string1 (week)
        case MON:
            str1 = "Monday";
            break;
        case TUE:
            str1 = "Tuesday";
            break;
        case WED:
            str1 = "Wednsday";
            break;
        case THU:
           str1 = "Thursday";
            break;
        case FRI:
            str1 = "Friday";
            break;
        case SAT:
            str1 = "Saturday";
            break;
        case SUN:
            str1 = "Sunday";
            break;
    }
str2 = RTclock.dayOfMonth;        //It stores the numerical day in string2

switch (RTclock.month) { // It stores the month in strin 5
        case 1:
            str5 = "January";
            break;
        case 2:
            str5 = "February";
            break;
        case 3:
            str5 = "March";
            break;
        case 4:
           str5 = "April";
            break;
        case 5:
            str5 = "May";
            break;
        case 6:
           str5 = "June";
            break;
        case 7:
            str5 = "July";
            break;
        case 8:
            str5 = "August";
            break;
        case 9:
            str5 = "September";
            break;
        case 10:
            str5 = "October";
            break;
        case 11:
            str5 = "November";
            break;
        case 12:
            str5 = "December";
            break;
    }

    str6 = RTclock.year+2001;     //And finally stores year in other string

    //Now all the strings are added in one string in order to write a "sentence"
    
str3 += str1;
str3 += " ";
str3 += str2;
str3 += str4;
str3 += " ";
str3 += str5;
str3 += ",";
str3 += " ";
str3 += str6;

//The string sentence is transofrmed into a char due to compatibily reasons

int str_len = str3.length() + 1;  
char char_array[str_len];

str3.toCharArray(char_array,str_len);


//With the char, the sentence can be showed in nextion display.
  t0.setText(char_array);
  }
}
