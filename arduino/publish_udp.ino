//Arduino_UDP.ino
#include <WiFi.h>
#include <WiFiUDP.h>
#include <WiFiClient.h>
#include <M5Core2.h>

const char* ssid = "SSID"; // SSID名を入れる
const char* password = "pass word of router"; // PASSWORDを入れる

static WiFiUDP wifiUdp; 
static const char *kRemoteIpadr = "192.168.11.60"; //JetbotのIPです
static const int kRmoteUdpPort = 5000; //送信先のポート

float acc[3];

char s0[16];
char s1[16];
char s2[16];
char t[16];
char test_message[16] = "Hello M5Stack!!";

static void WiFi_setup()
{
  static const int kLocalPort = 7000;  //自身のポート

  WiFi.begin(ssid, password);
  while( WiFi.status() != WL_CONNECTED) {
    delay(500);  
  }  
  wifiUdp.begin(kLocalPort);
}

static void Serial_setup()
{
  Serial.begin(115200);
  Serial.println(""); // to separate line  
}

void setup() {
  M5.begin();
  M5.IMU.Init();
  WiFi_setup();
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(40, 0);
  M5.Lcd.println("IMU TEST");
  M5.Lcd.println("IP: ");
  M5.Lcd.println(WiFi.localIP());
}

void loop() 
{
  M5.IMU.getAccelData(&acc[0],&acc[1],&acc[2]);
  M5.Lcd.setCursor(0, 50);
  M5.Lcd.print("G");
  M5.Lcd.printf(" %5.2f   %5.2f   %5.2f   ", acc[0], acc[1], acc[2]);

  dtostrf(acc[0], 5, 5, s0);
  dtostrf(acc[1], 5, 5, s1);
  dtostrf(acc[2], 5, 5, s2);

  wifiUdp.beginPacket(kRemoteIpadr, kRmoteUdpPort);

  /*
  for(int i=0; i < 7; i++){
    wifiUdp.write(s0[i]);
  }

  wifiUdp.write(',');

  for(int i=0; i < 7; i++){
    wifiUdp.write(s1[i]);
  }

  wifiUdp.write(',');

  for(int i=0; i < 7; i++){
    wifiUdp.write(s2[i]);
  }
  */

  for(int i=0; i < 16; i++)
  {
    wifiUdp.write(test_message[i]);
  }
  wifiUdp.endPacket();  

  delay(50);
}
