#include<LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);
int analogPin = 0;
int UPBUTTON = 13;
int DOWNBUTTON = 6;
int latchPin=10;
int clockPin=9;
int dataPin=8;
int compare=7;

int count = 20;
int val = 0;
float temp = 0;
int temp_trans = 0;
int count_trans= 0;

void tmep_setup()
{
    boolean cut1 = digitalRead(UPBUTTON);
    boolean cut2 = digitalRead(DOWNBUTTON);

    if(cut1 == HIGH)count++;

    if(cut2 == HIGH)count++
}

void temp_LED_output()
{
    val = analogRead(analogPin);
    val = map(val,0,1023,0,950);
    temp=(float)val/10;
    lcd.print("Temperture:");
    lcd.print(temp,1);
    lcd.setCursor(0,1);
    lcd.print("Set Temp:");
    lcd.print(count);
    lcd.setCursor(0,0);
}

void trans_BCD()
{
    temp_trans=(int)temp;
    for(int i = 0; i<10 ; i++)
    {
      if(temp > (9+(10*i)))
      temp_trans = temp+(6*(i+1));
      
      if(count > (9+(10*i)))
      count_trans = count+(6*(i+1));  
    }
  
}

void pin_divide()
{
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin,clockPin,MSBFIRST,temp_trans);
    shiftOut(dataPin,clockPin,MSBFIRST,count_trans);
    digitalWrite(latchPin, HIGH);
}


void reset()
{
    int temp_trans = 0;
    int count_trans= 0;
}

void setup()
{
    pinMode(UPBUTTON,INPUT);
    pinMode(DOWNBUTTON,INPUT);
    Serial.begin(9600); 
    analogReference(INTERNAL);
    lcd.begin(16,2);
    
    pinMode(latchPin,OUTPUT);
    pinMode(clockPin,OUTPUT);
    pinMode(dataPin,OUTPUT);
    
    pinMode(compare,INPUT);
}

void loop()
{
    tmep_setup();
    
    temp_LED_output();
    
    trans_BCD();
    
    pin_divide();   
    
    reset();
    
delay(400);
}
