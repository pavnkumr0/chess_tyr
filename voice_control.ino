#include <Stepper.h>
#include <Servo.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int stepsPerRevolution = 200;  // Change this based on your stepper motor specifications
int prevrow= 1;
const float stepsPermove=3.22; 
int prevcolumn = 1; 
int condcheck=1;
Stepper columnStepper(stepsPerRevolution, 8, 9, 10, 11);
Stepper rowStepper(stepsPerRevolution, 4, 5, 6, 7);
// Function to move the stepper motors based on chess coordinates with a constant speed

// Declare the Servo pin 
int servoPin = 3; 
// Create a servo object 
Servo Servo1; 
void rowenable(int i){
  if(i==1){  
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);
  delay(100); }
  else if(i==0) {
    
    digitalWrite(A2, LOW);
    digitalWrite(A3, LOW);
    delay(100);
  }
  }
  //ENABLES.....
void colenable(int i){
  if(i==1){  

     digitalWrite(A0, HIGH);

      digitalWrite(A1, HIGH);
  delay(100); }
  else if(i==0) {
digitalWrite(A0, LOW);
 
      digitalWrite(A1, LOW);
    delay(100);
  }
  }
  
void moveToPosition(int column, int row) {

 lcd.setCursor(0,0);
  lcd.print("Attacking.......");
  lcd.setCursor(0,1);
  lcd.print("..");

  int rotationscol = column - prevcolumn; // Calculate the difference
  int rotationsrow = row - prevrow; 
  int forprintB= prevrow;
  Serial.print("Previous COLUMN Position: ");
  Serial.println(prevcolumn);
  Serial.print("Column Rotations: ");
  Serial.println(rotationscol);
    Serial.print("Previous ROW Position: ");
  Serial.println(forprintB);
  Serial.print(" Row Rotations: ");
  Serial.println( rotationsrow );
  prevrow = row;
  prevcolumn = column;
  // Set the speed for column stepper motor
  columnStepper.setSpeed(200);
  // Convert column character to a corresponding number (A=1, B=2, ..., H=8)
 delay(100);
  // Move the column stepper motor
  int columnSteps = (rotationscol ) * stepsPerRevolution;
colenable(1);
  columnStepper.step(columnSteps*stepsPermove);
  colenable(0);
  delay(100);
  // Set the speed for row stepper motor
  rowStepper.setSpeed(200);
  delay(100);
  // Move the row stepper motor
  int rowSteps = (rotationsrow ) * stepsPerRevolution;
   rowenable(1);
  rowStepper.step(rowSteps*stepsPermove);
     rowenable(0);

}
// pickup of piece
void pickup() {
 
  moveblock();
   lcd.setCursor(4,1);
  lcd.print("ready");
  delay(100);;
      Servo1.write(0); 
   delay(1000);
  //for servo code
  delay(100);
  exitblock();
}
// dropoff of piece
void dropoff() {
  moveblock();
  lcd.setCursor(4,1);
  lcd.print("charge");
  delay(100);
      Servo1.write(90); 
   delay(1000);
  //for servo code
  delay(100);
  exitblock();
}
// function to move to block
void moveblock() {
  Serial.println("in move");
  columnStepper.setSpeed(200);
  // Convert column character to a corresponding number (A=1, B=2, ..., H=8)
  // Move the column stepper motor
  int columnSteps = 100;
   colenable(1);
  columnStepper.step(columnSteps * stepsPermove);
colenable(0)  ;// Set the speed for row stepper motor
  rowStepper.setSpeed(200);
  delay(100);
  // Move the row stepper motor
  int rowSteps = 100;
rowenable(1);
  rowStepper.step(rowSteps *stepsPermove);
  rowenable(0);
  delay(1000);
}
// function exit the block
void exitblock() {
  Serial.println("in exit");
  columnStepper.setSpeed(200);
 
  // Convert column character to a corresponding number (A=1, B=2, ..., H=8)
  // Move the column stepper motor
  int columnSteps = -100;
 colenable(1);
  columnStepper.step(columnSteps * stepsPermove);
  colenable(0);
  // Set the speed for row stepper motor
  rowStepper.setSpeed(200);
  // Move the row stepper motor
  int rowSteps = -100;
  rowenable(1);
  rowStepper.step(rowSteps *stepsPermove);
   rowenable(0);
  delay(1000);
}

char toLowerCase(char letter) {
  if (letter >= 'A' && letter <= 'Z') {
    return letter + 32;
  }
  return letter;
}

int letterToNumber(char letter) {
  if (letter >= 'a' && letter <= 'h') {
    return letter - 'a' + 1;
  } else {
    return -1; // Invalid letter
  }
}
int infun()
{



  int column;
    int row;
  // Check if there's serial data available
    while (Serial.available() < 2) {
        
    // Wait for user input
  }
    lcd.clear();
  if (Serial.available() > 0) {
    // Read the input string until a newline character is received
    String input = Serial.readStringUntil('\n');
    input.trim();
     Serial.print(input + '\n');
    if(input == "END"|| input == "end"||input == "End"){
      Serial.println("Ending the process and\n moving to : 'A1'");
    moveToPosition(1, 1 );
    Servo1.write(0); 
   delay(1000);
   Servo1.write(180); 
   delay(1000);
   Servo1.write(0); 
   delay(1000);
      return 0;
    }
    if (input.length() == 2) {
      char letter = toLowerCase(input.charAt(0));  // Convert letter to lowercase
      char number = input.charAt(1);

       column = letterToNumber(letter);
     row = number - '0';

    // Parse the input string (assuming format like "55")
  
      
    // Move to the specified position
      Serial.print("Received Move: ");
  Serial.print(column);
  Serial.println(row);}
  if((column<=8)&&(column>=1)&&(row<=8)&&(row>=1)){
   moveToPosition(column,row  );
  }
  else
  {
      Serial.println("wrong input please check");
   return 0;
  }}
}
void setup() {
      pinMode(A0, OUTPUT);
      pinMode(A1, OUTPUT);
        pinMode(A2, OUTPUT);
      pinMode(A3, OUTPUT);
  pinMode(1, OUTPUT);
    pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);
 pinMode(3, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
      pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
   pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  // for lcd init
   lcd.init();
  lcd.backlight();
  //Setup Awal Ketika Running
  lcd.setCursor(0,0);
  lcd.print("Welcome to tyr");
  lcd.setCursor(0,1);
  lcd.print("future of chess....");
  delay(4000);
  lcd.clear();
  // for servo init
 Servo1.attach(servoPin);
    Servo1.write(0); 
   delay(1000);
   Servo1.write(180); 
   delay(1000);
   Servo1.write(0); 
   delay(1000);
      Servo1.write(90); 
   delay(1000);
  Serial.begin(9600);  // Initialize serial communication at 9600 bps
}
void loop() {
reve:

  Serial.println("to Pickup Enter chess move (e.g.,A5 or b6): or 'end' ");


 lcd.setCursor(0,0);
  lcd.print("To pickup enter");
  lcd.setCursor(0,1);
  lcd.print("move e.g.,A5/end");
condcheck=1;

condcheck=infun();
 //lcd.clear();
if(condcheck==0){
condcheck=1;
goto reve;
}
pickup();
    Serial.println(" to Dropoff Enter chess move (e.g.,A5 or b6): or 'end' ");
  lcd.setCursor(0,0);
  lcd.print("To dropoff enter");
  lcd.setCursor(0,1);
  lcd.print("move e.g.,A5/end"); 
condcheck=infun();
 //lcd.clear();
if(condcheck==0){
goto reve;
}
dropoff();
  
  
}

