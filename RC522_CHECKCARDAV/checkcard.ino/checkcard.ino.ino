#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 21   // SDA
#define RST_PIN 22  // RST
MFRC522 mfrc522(SS_PIN, RST_PIN);
#define OUT4RELAY 33 // output 
void setup()
{
  Serial.begin(115200);
  SPI.begin(18,19,23,21);  // SPI.begin(SCK, MISO, MOSI, SS_optional)
  mfrc522.PCD_Init();// Khởi tạo RC522
  delay(300);
  Serial.println("da san sang doc the");
  pinMode(OUT4RELAY,OUTPUT);
}



bool hasCard() {
  byte atqa[2];
  byte atqaLen = 2;
  // Gửi lệnh REQA và xem phản hồi
  MFRC522::StatusCode status = mfrc522.PICC_RequestA(atqa, &atqaLen);
  return (status == MFRC522::STATUS_OK);  // true nếu có thẻ
}


void loop()
{
  bool a = 0;
 a = hasCard();
 Serial.println(a);
  vedau:
  delay(50);
  if (a==true)  
  {
    start:                     
    digitalWrite(OUT4RELAY,1);  //relay on
    Serial.println("bat relay");
  	while(1)
    {
       a = hasCard();
      if (a==true)
      {
        digitalWrite(OUT4RELAY,1);
        Serial.println("bat relay");
      }
      else 
        for(int i=0;i<16;i++)
      {
        a=hasCard();
        delay(1000);
        Serial.print("time remaining: ");
        Serial.print(16-i);
        Serial.println("s");
          if (a==true){
          goto start;}
      }
      
      goto vedau;
    }
  }
  else
    digitalWrite(OUT4RELAY,0); // relay off
    Serial.println("tat relay");
    delay(500);
}