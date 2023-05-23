#include <SPI.h>
#include <MFRC522.h>
 
#define RST_PIN 9
#define SS_PIN 10
#define RELAY 6
MFRC522 mfrc522(SS_PIN, RST_PIN);

static int access = 5000;
static int denied = 1000;

void setup() 
{
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW);
  Serial.println("Put your card");
  Serial.println();
}
void loop() 
{
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  
  Serial.print("UID: ");
  String content= "";
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println();
  if (content.substring(1) == "9F 11 CB 28")
  {
    Serial.println("Access");
    Serial.println();
    digitalWrite(RELAY, HIGH);
    delay(access);
    digitalWrite(RELAY, LOW);
  }
 else   {
    Serial.println("Denied");
    delay(denied);
  }
}
