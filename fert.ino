//Fert!!

#include <unistd.h>
#include <LiquidCrystal.h>
//LCD pin to Arduino
const int pin_RS = 8; 
const int pin_EN = 9; 
const int pin_d4 = 4; 
const int pin_d5 = 5; 
const int pin_d6 = 6; 
const int pin_d7 = 7; 
const int pin_BL = 10; 
LiquidCrystal lcd( pin_RS,  pin_EN,  pin_d4,  pin_d5,  pin_d6,  pin_d7);

class Menu {
    public:
    int one;
    int two;
    int three;
    int four;
};

  int menuNum;
  long IR;
  float liter;
  bool sensorOn;
  int key; // 409 = left, 0023 = right, 972 = up, 254 = down, 639 = select

  int keyPress(){
    key = analogRead (0);
    if (key < 450 && key > 400){ // move left
      menuNum--;
      delay(250);
    }
    if (key < 50 && key >=0){ // move right
      menuNum++;
      delay(250);
    }
  }



void setup() {
  pinMode(A0, INPUT);
  menuNum = 0;
  int key; // 409 = left, 0023 = right, 972 = up, 254 = down, 6393 = select.
  key = analogRead (0);
  IR = 0;
  sensorOn = false;

  Menu Menu1;
    Menu1.one = 25;
    Menu1.two = 20;
    Menu1.three = 25;
    Menu1.four = 0;
  
 lcd.begin(16, 2);
 lcd.setCursor(0,0);
 lcd.print("a+b rhiz zym bst");
 lcd.setCursor(0,1);
 lcd.print(Menu1.one);
 lcd.print(" ");
 lcd.print(Menu1.two);
 lcd.print(" ");
 lcd.print(Menu1.three);
 lcd.print(" ");
 lcd.print(Menu1.four);
}


void loop() {

  int pk = 15;
  bool pause = false;

  if (key < 150 && key > 50){  //   Switches sensor readings to constantly update, or only update when 'down' is pressed
    if(sensorOn==false){
      sensorOn = true;
    }
    else{
      sensorOn = false;
    }
    delay(500);
  }

  if(sensorOn == true){
    for(int i = 0; i < 25; i++){ // Get average reading of IR
      IR = IR + analogRead(A1);
      delay(10);
    }
    IR = IR / 25;
  }

 //Convert IR value to liters
  float x = IR;
  int liters;

  if(IR < 276){
    liter = 0.304878 * x-46.6463;
  }
  if(IR > 276 && IR < 352){
    liter = 0.164474*x-7.89474;
  }
  if(IR > 352 && IR < 432){
    liter = 0.15625*x-5;
  }
  if(IR > 432){
    liter = 0.142045*x+1.13636;
  }
  if( IR == 0){
    liter = 0;
  }
  liters = 100 - liter;


  // Define objects
  // VALUES ARE FOR MY SPECIFIC FERTILISING SCHEDULE, MODIFY TO SUIT YOUR OWN NEEDS
  Menu Menu1;
  Menu1.one = 25;
  Menu1.two = 20;
  Menu1.three = 25;
  Menu1.four = 0;

  Menu Menu2;
  Menu2.one = 30;
  Menu2.two = 20;
  Menu2.three = 25;
  Menu2.four = 20;

  Menu Menu3;
  Menu3.one = 35;
  Menu3.two = 5;
  Menu3.three = 25;
  Menu3.four = 20;

  Menu Menu4;
  Menu4.one = 35;
  Menu4.two = 5;
  Menu4.three = 25;
  Menu4.four = 20;

  Menu Menu5;
  Menu5.one = 25;
  Menu5.two = 5;
  Menu5.three = 25;
  Menu5.four = 20;


  Menu array[5]{
    Menu1,
    Menu2,
    Menu3,
    Menu4,
    Menu5
  };
  Menu arraytwo[5]{
    Menu1,
    Menu2,
    Menu3,
    Menu4,
    Menu5
  };

  arraytwo[menuNum].one = arraytwo[menuNum].one * liters / 10;      //Calculate values, in Mls, of each fertiliser and additive
  arraytwo[menuNum].two = arraytwo[menuNum].two * liters / 10;
  arraytwo[menuNum].three = arraytwo[menuNum].three * liters / 10;
  arraytwo[menuNum].four = arraytwo[menuNum].four * liters / 10;    //Calculate values, in Mls, of each fertiliser and additive


  lcd.setCursor(0,0);
  if (menuNum != 3){
    lcd.print(menuNum + 1); //growth phase number
    lcd.print(" ab rhi zym bst");

  }
  else{
    lcd.print(" !!pk!!  ");
    lcd.print(pk * liters / 10);
    lcd.print("      ");
  }
  lcd.setCursor(0,1);
  
  keyPress();
  
  if (key < 700 && key > 600){ // Display IR sensor value and number of liters needed to fill on SELECT press
    lcd.print(IR);
    lcd.print(" ");
    lcd.print(liters);
    lcd.print("               ");
    delay(500);
  }
  if (key < 350 && key > 150){ // Pressing down key pauses screen
    while(pause == false){
      pause = true;
      delay(100);
    }
  }
  //unpause when down is pressed again
  //and define what happens while pause is true
  while(pause == true){
    key = analogRead(0);

    for(int i = 0; i < 25; i++){ // Get average reading of IR
      IR = IR + analogRead(A1);
      delay(10);
    }
    IR = IR / 25;

    delay(100);

    //if (key < 350 && key > 200){ //unpause
      pause = false;
    //}
  }


  //Loop menu if user attempts to go past either end of the menu.
  if (menuNum > 4){
    menuNum = 0;
  }
  if (menuNum < 0){
    menuNum = 4;
  }
  

  lcd.print(arraytwo[menuNum].one); //Display, in Mls, how much A+B to add
  lcd.print(" ");
  lcd.print(arraytwo[menuNum].two); //Display, in Mls, how much Rhiz to add
  lcd.print(" ");
  lcd.print(arraytwo[menuNum].three); //Display, in Mls, how much Zym to add
  lcd.print(" ");
  lcd.print(arraytwo[menuNum].four); //Display, in Mls, how much Bst to add
  lcd.print("          "); //Replaces previous values, after end of new print statement, with blank space
}
