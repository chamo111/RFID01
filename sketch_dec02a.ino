#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
#define PIR_PIN 2

int led_red = 6; //RED
int led_green = 5; //GREEN
int led_blue = 3; //BLUE

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

void setup() {
  pinMode(led_red, OUTPUT);
  pinMode(led_green, OUTPUT);
  pinMode(led_blue, OUTPUT);
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
}

void loop() {
  digitalWrite (led_red, HIGH);
  digitalWrite (led_blue, HIGH);
  digitalWrite (led_green, HIGH);
  
  // Look for new cards
  Serial.println("Put your card to the reader...");
  Serial.println();
delay(500);
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "D3 87 2E 1D" || content.substring(1) == "43 EC 61 AC" || content.substring(1) == "F3 33 5E AC")
  {
    Serial.println("Authorized access");
    Serial.println();
    digitalWrite (led_red, HIGH);
    digitalWrite (led_blue, HIGH);
    digitalWrite (led_green, LOW);
    delay(2000);
    digitalWrite (led_green, HIGH);

  }

  else   {
    Serial.println(" Access denied");
    digitalWrite (led_red, LOW);
    digitalWrite (led_blue, HIGH);
    digitalWrite (led_green, HIGH);
    delay(2000);
    digitalWrite (led_red, HIGH);

  }

  delay(5000);
}
