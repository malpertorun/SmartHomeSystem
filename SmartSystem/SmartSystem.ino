
#include <avr/wdt.h>
#include <Servo.h>
Servo servo;


short coIki = A0;
short gaz = A3;
short yangin = A5;
//LEDLER
short yanginLed = 3;
short led = 13;         
short gazLed = 2; 
short coikiLed = 9;
//BUZZER
short buzzer1 = 8;
short buzzer2 = 7;
short buzzerTepe = 4;
// MANTIKSAL
boolean servoDonguKontrol;
boolean alarmDurumu;
boolean durum;
boolean ledDurum;
// TIME
unsigned long time;
unsigned long zaman2;
unsigned long zamanLed=0;
unsigned long motorZaman = 200000;
unsigned long freeMotorZaman;
// DEGISKENLER
short ldrBanyo = A4;
short ldrMutfak = A1;

short servoDeger = 4;
short motorHizi = 180;
short motorhizDongusu;
short a;
short b;
short O;
 

void setup() {


  Serial.begin(9600);
  servo.attach(6);
  servo.write(70);
  pinMode(led, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(gaz, INPUT);
  pinMode(gazLed, OUTPUT);
  pinMode(yangin, INPUT);
  pinMode(ldrBanyo, INPUT);
  pinMode(ldrMutfak, INPUT);
  pinMode(coIki, INPUT);
  pinMode(coikiLed, OUTPUT);
  pinMode(yanginLed, OUTPUT);
 pinMode(buzzer1, OUTPUT);
  pinMode(buzzer2, OUTPUT);
  pinMode(buzzerTepe, OUTPUT);

}

void loop() {


  // GAZ&YANGIN ALGILAMA*******************************************************************

  //      Serial.print("       Ana sistem sayaci..  ");
  //      Serial.print(millis());
  //      Serial.print("        time:     ");
  //      Serial.print(time );
  //
  //      Serial.print("    ");
  //      Serial.println("  **********  ");
  //      delay(400);


short   degerBanyo = analogRead(ldrBanyo);
  short degerMutfak = analogRead(ldrMutfak);
   short degerGaz = analogRead(gaz);
  short degerYangin = analogRead(yangin);
  short karbondioksit = analogRead(coIki);
  
  if( alarmDurumu==false)
  {
    
              if(karbondioksit > 344 || degerGaz > 821 )
              { 
                   delay(1000); 
                 degerBanyo = analogRead(ldrBanyo);
                 degerGaz = analogRead(gaz);
                 degerYangin = analogRead(yangin);
                 karbondioksit = analogRead(coIki);
   
              }
  }
  //****************************** Gaz& Yangın çıktıları..
  //
    Serial.print("Ldr: --> ");
    Serial.print(degerBanyo);
   Serial.print("   LdrMutfak: --> ");
   Serial.print(degerMutfak);
   Serial.print("  &&  ");
    Serial.print("yangn: --> ");
    Serial.print(degerYangin);
    Serial.print("  &&  ");
    Serial.print("GAZ: --> ");
    Serial.print(degerGaz);
    Serial.print("  &&  ");
    Serial.print("Karbondioksit: --> ");
    Serial.print(karbondioksit);
    Serial.println(" ** <<<<<>>>>>** ");
   // delay(1000);

  //**********************************  değer KARŞILAŞTIRMA -----------------------

  //************************************************* HERZMAN YAPILACAKLAR *************************************************
  boolean banyoDurumu = lambaDurumu();


  if (O == 0)
  {

    //pinMode(6,INPUT);
    //     Serial.println("Zaman Led Sartini Sagladi..");
    //Serial.println(millis()); Serial.println("-******************..");
    //Serial.println(zamanLed);
    if (millis() - zamanLed > 2250 ) {
      //       Serial.println("Zaman Saglandi ve Ledler Yakildi");
      ledleriAc();

    }
     if (millis() - zamanLed > 2250 ) {
      zamanLed = millis();
      isikKapat();
      pinMode(buzzer2, OUTPUT);
      delay(20);
      digitalWrite(buzzer2, LOW);
      delay(250);
      tone(buzzer2, 195);
      delay(50);
      noTone(buzzer2);
      digitalWrite(buzzer2, HIGH);
      delay(45);

      //        Serial.print("*************KAPATILDI*************");
    }
  } 
  //**************************************************************************************************************************

  if ( degerGaz < 820 && degerYangin > 400 && karbondioksit <  344 ) {

    digitalWrite(buzzer1, LOW);
    digitalWrite(buzzerTepe, LOW);
    if (banyoDurumu == true) {
      pinMode(buzzer2, INPUT);
    }
    alarmDurumu=false;


  }

  else if (karbondioksit > 345) {
    digitalWrite(coikiLed, HIGH);
    alarm(9);
     alarm(9);
      alarm(9);
    
  } 

  else if (degerGaz > 821 ) {
    digitalWrite(gazLed, HIGH);
 alarm(2);
   alarm(2);
   alarm(2);

  }

 else  if (degerYangin < 140 )
  {
    digitalWrite(yanginLed, HIGH);
   // alarm(3);
   //alarm(3);
   //alarm(3);
  }

  //***********************TRUEEEEE*************************  LDDDDDDDRRRRRRR

  if (banyoDurumu == true)
  {
    Serial.print(" <<<< LAMBA YAKILDI! ---> ");  O++;

   if(motorZaman>=820000)
      {
  
         cildir(); alarm(3);

      }
  else{
         servo.attach(6);
    if (servoDeger < 179 && servoDonguKontrol == false)
    {
    
      servo.write(servoDeger );
      delay(50);
      servo.write(servoDeger-2 );
      delay(20);
       servo.write(servoDeger-4 );
      servoDeger += 5;
      if (servoDeger > 140) {
        servoDonguKontrol = true;
      }
    }
    if (servoDeger < 179 && servoDonguKontrol == true)
    {
      servo.write(servoDeger);
      delay(50);
//        servo.write(servoDeger+2);
//        delay(20);
//          servo.write(servoDeger+4);
     
      servoDeger -= 5;

      if (servoDeger < 15) {
        servoDonguKontrol = false;
      }
    }
          
    }

    if (O == 1 && 1 >= 1) {
      time = millis();
      motorhizDongusu = motorHizi;
    }
    if (millis() - time > 680000 &&  millis() - time < 1360000) {           
      motorZaman = 450000;
    }
      else if (millis() - time > 1850000) {   
      motorZaman =820000;
    }
  else  if (millis() - time > 1370000) {
      motorZaman = 750000;
    }
    

    //1370000     750000    680000   1360000   450000  150000
    iceriVerr();


    if (millis() - time > 150000 && durum == false  )  {
      a = 1;
      b = 0;

    }

    durum = false;

    if (banyoDurumu == false) {
      delay(600);
    }
  }

  if (a == 1 && banyoDurumu == false && durum == false) {
    motorHizi = motorhizDongusu;
    time = 0;
  }

  //********************FALSEEEEEEEEEEE**********************

  if (banyoDurumu == false)
  {

servo.attach(6);
      servo.write(70);
 
    if (a == 1)
    {
      durum = true;



      Serial.print("**************"); Serial.print("  Isik kapandi, calismaya devam ediyor..., -->>> "); b++;

      if (b == 1 && 1 >= 1) {

        time = millis();
        zaman2 = time;

      }

      Serial.print("  Zaman sayimi basladi,     ");



      if (millis() - zaman2 > motorZaman  ) {                   
        Serial.print("   artik motorZaman dongusunde!.., ");

        Serial.println("  MOTORLAR DURDURULDU! ");
        a = 0; O = 0;



      }
    }
    
  else  if (a == 0) {

      time = 0;  O = 0; durum = true;
      servo.attach(6);
      servo.write(70);
      pinMode(buzzer2, INPUT);
      Serial.print("*********");     Serial.print("  Lamba kapali - Motorlar durduruldu! "); Serial.println("************");


//BOSTA
      if (degerMutfak < 900)
      {

      //  Serial.println(" MUTFAK KAPALI VE MOTORLAR KAPATILDI!! ");

        digitalWrite(11, LOW);
        digitalWrite(12, LOW);
        analogWrite(10, 00);

      }
      else {
       // Serial.println(" MUTFAK ACIK CALISMAYA DEVAM EDIYOR ");
        if (millis() - freeMotorZaman > 2250 ) {

          digitalWrite(11, LOW );
          digitalWrite(12, HIGH);
          analogWrite(10, 255);

        }
        if (millis() - freeMotorZaman > 3670) {
          freeMotorZaman = millis();

          digitalWrite(11, LOW);
          digitalWrite(12, LOW);
          analogWrite(10, 00);
        }



      }

    }

  }
}


boolean lambaDurumu() 
{ 
 
       short  degerBanyo = analogRead(ldrBanyo);
 
if(degerBanyo>600 && alarmDurumu==false)
  { 
       ledleriAc();
       delay(45);
       return true;
  }
  else
  {

    return false;

  }

}
 short alarm(short kimden)
{

  isikKapat();
digitalWrite(kimden,HIGH);
 digitalWrite(led, HIGH);
    cildir();
      cildir();
      
  digitalWrite(buzzer1, HIGH);
  digitalWrite(buzzer2, HIGH);
  tone(buzzer2, 262);
  digitalWrite(buzzerTepe, HIGH);
  delay(1000);
  digitalWrite(kimden,LOW);
 digitalWrite(led, LOW);
  digitalWrite(buzzer1, LOW);
  digitalWrite(buzzer2, LOW);
  digitalWrite(buzzerTepe, LOW);
    delay(600);
    digitalWrite(kimden,HIGH);
 digitalWrite(led, HIGH);
    digitalWrite(buzzer1, HIGH);
  digitalWrite(buzzer2, HIGH);
  tone(buzzer2, 262);
  digitalWrite(buzzerTepe, HIGH);
  delay(1000);
  digitalWrite(kimden,LOW);
 digitalWrite(led, LOW);
  digitalWrite(buzzer1, LOW);
  digitalWrite(buzzer2, LOW);
  digitalWrite(buzzerTepe, LOW);
  delay(600);
  
     cildir();
    cildir();
    
      alarmDurumu=true;

}

void ledleriAc()
{
  digitalWrite(led, HIGH);
  digitalWrite(gazLed, HIGH);
  digitalWrite(yanginLed, HIGH);
  digitalWrite(coikiLed, HIGH);
  delay(50);
  digitalWrite(led, LOW);
  digitalWrite(gazLed, LOW);
  digitalWrite(yanginLed, LOW);
  digitalWrite(coikiLed, LOW);
  delay(45);
  digitalWrite(led, HIGH);
  digitalWrite(gazLed, HIGH);
  digitalWrite(yanginLed, HIGH);
  digitalWrite(coikiLed, HIGH);
 
}
void isikKapat()
{                   

  digitalWrite(led, LOW);
  digitalWrite(gazLed, LOW);
  digitalWrite(yanginLed, LOW);
  digitalWrite(coikiLed, LOW);

}
void iceriVerr() {
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
  analogWrite(10, motorHizi + 75);

}
void cildir()
{    
       servo.attach(6);
    servo.write(90);
  delay(100);
  servo.write(30);
  delay(100);
  servo.write(60);
   delay(150);
  servo.write(100);
  
  }

