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



void loop() {
  if (hasCard()) {
    Serial.println("Co the trong vung doc");
    delay(1000);
  } else {
    delay (500);
    if (!hasCard()){

    
    Serial.println("Khong co the");
    delay(1000);
    return;
    }
  }

  delay(500);
mfrc522.PICC_ReadCardSerial();

 Serial.print("UID Thẻ: ");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    Serial.print(" ");
  }
   digitalWrite(OUT4RELAY, HIGH);
  delay (1000);





}