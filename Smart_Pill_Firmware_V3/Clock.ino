void getRTC(){
int Hour;
int Mins;

String str1 = "Monday";
String str2 = "1";
String str3 = "";
String str4 = "th";
String str5 = "January";
String str6 = "2021";

  RTclock.getTime();

  Hour = RTclock.hour;
  Mins = RTclock.minute;

  UM = Mins%10;

  if(UM != prevUM){
prevUM = UM;

  DecenaH.setValue(Hour/10);
  UnidadH.setValue(Hour%10);

  DecenaM.setValue(Mins/10);
  UnidadM.setValue(UM);


switch (RTclock.dayOfWeek) { // Friendly printout the weekday
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
str2 = RTclock.dayOfMonth;

switch (RTclock.month) { // Friendly printout the weekday
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

    str6 = RTclock.year+2001;
    
str3 += str1;
str3 += " ";
str3 += str2;
str3 += str4;
str3 += " ";
str3 += str5;
str3 += ",";
str3 += " ";
str3 += str6;

int str_len = str3.length() + 1; 
char char_array[str_len];

str3.toCharArray(char_array,str_len);



  t0.setText(char_array);
  }
}
