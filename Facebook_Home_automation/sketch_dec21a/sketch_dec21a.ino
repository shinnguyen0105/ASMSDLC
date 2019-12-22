#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
//#include <SimpleTimer.h>

#include <Keypad.h>
#include <Servo.h>


#define BLYNK_PRINT Serial

char auth[] = "eaOdRCrgqTth4XUyRUTYL5Q_14YmMl-T";

char ssid[] = "Greenwich-Student";
char pass[] = "12345678";

Servo myServo;
//SimpleTimer timer;
 
const byte n_rows = 4;
const byte n_cols = 4;

bool check=false;

int count =0;

int ledOpen,ledClose;

String passwordSetup = "1111"; 
String passwordInput = "";

//String textIn;
//
//bool checkBlynk = false;
 
char keys[n_rows][n_cols] = {
  {'1','2','3','4'},
  {'5','6','7','8'},
  {'9','0','A','B'},
  {'C','D','E','F'}
};
 
byte colPins[n_rows] = {D5, D4, D3, D2};
byte rowPins[n_cols] = {D9, D8, D7, D6};
 
Keypad myKeypad = Keypad( makeKeymap(keys), rowPins, colPins, n_rows, n_cols); 

WidgetLCD lcd(V4);

 
void setup(){
  Blynk.begin(auth, ssid, pass);
//  timer.setInterval(1000L, checkPassBlynk);
  
  Serial.begin(115200);
  myServo.attach(D10);
  myServo.write(180);

}

//BLYNK_WRITE(V5)
//{
//  textIn = param.asStr();
//}

BLYNK_WRITE(V1)
{
  
  int pinValueV = param.asInt();

  if(pinValueV == 1)
  {
    Blynk.virtualWrite(V2, 255);
    Blynk.virtualWrite(V3, 0);
    lcd.clear();
    lcd.print(0,0,"Correct password");
    myServo.write(120);
  }
  else
  { 
    Blynk.virtualWrite(V2, 0);
    Blynk.virtualWrite(V3, 255);
    lcd.clear();
    lcd.print(0,0,"Close");
    lcd.print(0,1,"Made by Shin");
    myServo.write(0);
  }
}
 
void loop(){
  Blynk.run();
  
  keySelect();
  delay(200);
}

//void checkPassBlynk()
//{
//  if (textIn == passwordSetup)
//  {
//    checkBlynk = true;
//  }else
//    checkBlynk = false;
//}


void keySelect()
{
  char myKey = myKeypad.getKey();
 
  if (myKey != NULL){
    Serial.print("Key pressed: ");
    Serial.println(myKey);
    switch(myKey)
      {
        case '1':
        if(check == true)
        {
          passwordSetup += '1';
        }else
          passwordInput += '1';
          break;
        
        case '2':
        if(check == true)
        {
          passwordSetup += '2';
        }else
          passwordInput += '2';
          break;
      
      case '3':
        if(check == true)
        {
          passwordSetup += '3';
        }else
          passwordInput += '3';
          break;
      
      case '4':
        if(check == true)
        {
          passwordSetup += '4';
        }else
          passwordInput += '4';
          break;
      
      case '5':
        if(check == true){
          passwordSetup += '5';
        }else
          passwordInput += '5';
          break;
      
      case '6':
        if(check == true)
        {
          passwordSetup += '6';
        }else
          passwordInput += '6';
          break;
          
      case '7':
      if(check == true)
      {
        passwordSetup += '7';
      }else
        passwordInput += '7';
        break;
        
      case '8':
        if(check == true)
        {
          passwordSetup += '8';
        }else
          passwordInput += '8';
          break;
          
      case '9':
        if(check == true)
        {
          passwordSetup += '9';
        }else
          passwordInput += '9';
          break;
          
      case '0':
      if(check == true)
      {
        passwordSetup += '0';
      }else
        passwordInput += '0';
        break;
        
      case 'A':
      if(check == true)
      {
        passwordSetup += 'A';
      }else
        passwordInput += 'A';
        break;
        
      case 'B':
      if(check == true)
      {
        passwordSetup += 'B';
      }else
        passwordInput += 'B';
        break;
      
      case 'C':
        check = !check;
        Serial.print("Input password: ");
        Serial.println(passwordInput);
        Serial.print("Password setup: ");
        Serial.println(passwordSetup);
        break;
        
      case 'D':
        Serial.println("Resert Password");
        Serial.println("S14");
        lcd.clear();
        lcd.print(0,0,"Resert PW");
        passwordSetup = "";
        Serial.print("Input password: ");
        Serial.println(passwordInput);
        Serial.print("Password setup: ");
        Serial.println(passwordSetup);
        break;
        
      case 'E':
        Serial.println("Close");
        lcd.clear();
        lcd.print(0,0,"Close");
        Blynk.virtualWrite(V2, 0);
        Blynk.virtualWrite(V3, 255);
        Blynk.virtualWrite(V1, 0);
        myServo.write(0);
        passwordInput = "";
        Serial.print("Input password: ");
        Serial.println(passwordInput);
        Serial.print("Password setup: ");
        Serial.println(passwordSetup);
        break;
        
      case 'F':
      if (passwordInput == passwordSetup)
      {
        Serial.println("Open");
        lcd.clear();
        lcd.print(0,0,"Correct password");
        Blynk.virtualWrite(V2, 255);
        Blynk.virtualWrite(V3, 0);
        Blynk.virtualWrite(V1, 1);
        myServo.write(120);
        Serial.print("Input password: ");
        Serial.println(passwordInput);
        Serial.print("Password setup: ");
        Serial.println(passwordSetup);
        count=0;
      }else
      {
        Serial.println("Wrong password");
        lcd.clear();
        lcd.print(0,0,"Wrong password");
        passwordInput ="";
        count++;
        if(count >3)
        {
          //buzzer
          delay(300);
          // ...for 1sec
        }
      }
        break;
        
      default:
      break;
      }
    }
}
