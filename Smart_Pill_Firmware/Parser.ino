

#define MAX_BUFFER_SIZE 400
#define MAX_DEPOSIT_NUM 4

char buffer_example[MAX_BUFFER_SIZE];
char msg[MAX_BUFFER_SIZE]={0};
char *search_start;
char *search_aux;
char *search_tok;

char token[2] = " ";

uint8_t counter = 0;

typedef struct {
  char pillname[20];
  char quantity[5];
  char deposit[5];
  char weight[10];
} pilltype;

pilltype pills[MAX_DEPOSIT_NUM] = {0, 0, 0, 0};

void parser(){
  
  
  String a = Serial3.readStringUntil("\n");
  a.toCharArray(buffer_example,MAX_BUFFER_SIZE);
   //Counter pills
  search_aux = buffer_example;
  search_start = strchr(search_aux, 'D');
  while (search_start != NULL)
  {
    search_aux = (char *)(search_start + 1);
    search_start = strchr(search_aux, 'D');
    counter++;
  }

  //Parser 
  search_tok = strtok(buffer_example, token);

  for (uint8_t i = 0; i < counter; i++)
  {
    search_tok = strtok(NULL, token); // Name
    strcpy(pills[i].pillname, search_tok);
    search_tok = strtok(NULL, token); // Quantity
    strcpy(pills[i].quantity, search_tok);
    search_tok = strtok(NULL, token); // Deposit
    strcpy(pills[i].deposit, search_tok);
    search_tok = strtok(NULL, token); // Weight
    strcpy(pills[i].weight, search_tok);
    search_tok = strtok(NULL, token); // "D"
  }
  
  for (uint8_t i = 0; i < counter; i++)
  {
    n = atoi(pills[i].quantity);
   Dispensador = atoi(pills[i].deposit);
//dbSerialPrintln(i);
 if(n > 0 && Dispensador >= 0){
        while(State == LOW){
          
          dbSerialPrintln("Bucle");
          nexLoop(nex_listen_list);
           delay(200);
  //  int  a = sonar.ping_cm();
  // dbSerialPrintln(a);
   if(sonar.ping_cm() <=  dGlass)
   Glass = 1;
   else
   Glass = 0;


   
  if(Glass == 1)
    prePill();           
    else
    glass();
  }
  if(State == HIGH){
  pill(n,Dispensador);
    //dbSerialPrintln("Dispenso: ");
   //dbSerialPrintln(i);
  
  }}
   i2++; 
  }
  endPill();
  }
