#define BLYNK_TEMPLATE_ID "TMPL6CIJ1LyOG"
#define BLYNK_TEMPLATE_NAME "SmartLight"
#define BLYNK_AUTH_TOKEN "RcqfFIvkuutAMKF3sD3NamBTTjOhx8uE"

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define RELAY_PIN_1 D7
#define RELAY_PIN_2 D5
#define PIR_PIN D4
#define BUTTON_PIN D6
#define LIGHT_SENSOR_PIN D2

/* Fill-in information from Blynk Device Info here */

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Hang_2.4G";
char pass[] = "0948315735";

int flag_mode = 0;
int state_manu = 1;
int button_manu = 0;
bool toggle = 0;

void Mode_Chong_Trom();
void Mode_Anh_Sang();
void Mode_Thu_Cong();
void Mode_Chuyen_Dong();
void Physic_Button();

void setup()
{
  // Debug console
  Serial.begin(115200);

  pinMode(RELAY_PIN_1, OUTPUT);
  pinMode(RELAY_PIN_2, OUTPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LIGHT_SENSOR_PIN, INPUT);

  digitalWrite(RELAY_PIN_1, HIGH);
  digitalWrite(RELAY_PIN_2, HIGH);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  
}
void loop()
{
  Blynk.run();
  Physic_Button();
 
  if (state_manu == 1)
  {
    Mode_Thu_Cong();
    Serial.print("Che do 0");
  }else if (state_manu == 2){
    Mode_Anh_Sang();
    Serial.print("Che do 1");
  } else if (state_manu == 3)
  {
   Mode_Chuyen_Dong();
   Serial.print("Che do 2");
  }else if (state_manu == 4)
  {
    Mode_Chong_Trom();
    Serial.print("Che do 3");
  }
}

void Physic_Button(){
    
    if(digitalRead(BUTTON_PIN)== 0){
      toggle = !toggle;
      state_manu = 1;
      button_manu = !toggle;
      Serial.println("Button Pressed");
      Serial.println(toggle);
      Serial.printf(" %d",button_manu);
      digitalWrite(RELAY_PIN_1,toggle);
      Blynk.virtualWrite(V5,!toggle);
    }
}

void Mode_Chong_Trom()
{
  Blynk.virtualWrite(V6, LOW);
  Blynk.virtualWrite(V7, LOW);
  Blynk.virtualWrite(V4, LOW);
  Blynk.virtualWrite(V8, HIGH);
  int state = digitalRead(PIR_PIN);
  if (state)
  {
    digitalWrite(RELAY_PIN_1, LOW);
    digitalWrite(RELAY_PIN_2, LOW);
  }
  else
  {
    digitalWrite(RELAY_PIN_1, HIGH);
    digitalWrite(RELAY_PIN_2, HIGH);
  }
}

void Mode_Thu_Cong()
{
  Blynk.virtualWrite(V6, LOW);
  Blynk.virtualWrite(V7, LOW);
  Blynk.virtualWrite(V4, HIGH);
  Blynk.virtualWrite(V8, LOW);
  digitalWrite(RELAY_PIN_2, HIGH);
  if (button_manu == 1 && state_manu == 1)
  {
    digitalWrite(RELAY_PIN_1, LOW);
    //low la bat - high la tat
  }
  else
    digitalWrite(RELAY_PIN_1, HIGH);
}

void Mode_Anh_Sang()
{
  Blynk.virtualWrite(V6, HIGH);
  Blynk.virtualWrite(V7, LOW);
  Blynk.virtualWrite(V4, LOW);
  Blynk.virtualWrite(V8, LOW);
  digitalWrite(RELAY_PIN_2,HIGH);
  int state = digitalRead(LIGHT_SENSOR_PIN);
  if (state)
  {
    digitalWrite(RELAY_PIN_1, LOW);
  }
  else
  {

    digitalWrite(RELAY_PIN_1, HIGH);
  }
}

void Mode_Chuyen_Dong()
{
  Blynk.virtualWrite(V6, LOW);
  Blynk.virtualWrite(V7, HIGH);
  Blynk.virtualWrite(V4, LOW);
  Blynk.virtualWrite(V8, LOW);
  digitalWrite(RELAY_PIN_2,HIGH); 
  int state = digitalRead(PIR_PIN);
  if (state)
  {
    digitalWrite(RELAY_PIN_1, LOW);
  }
  else
  {
    digitalWrite(RELAY_PIN_1, HIGH);
  }
}

BLYNK_CONNECTED()
{
  Serial.print("BLYNK SERVER CONNECTED !!!");
  // Blynk.syncAll();
  Blynk.syncVirtual(V0);
  Blynk.syncVirtual(V1);
  Blynk.syncVirtual(V2);
  Blynk.syncVirtual(V3);
}

BLYNK_WRITE(V0)
{
  int stt = param.asInt();
  if (stt)
  {
    state_manu = 1;
    //Mode_Thu_Cong();
  }
}

BLYNK_WRITE(V1)
{
  int stt = param.asInt();
  if (stt)
  {
    state_manu = 2;
   // Mode_Anh_Sang();
  }
}

BLYNK_WRITE(V2)
{
  int stt = param.asInt();
  if (stt)
  {
    state_manu = 3;
   // Mode_Chuyen_Dong();
  }
}
BLYNK_WRITE(V3)
{
  int stt = param.asInt();
  if (stt)
  {
    state_manu = 4;
   // Mode_Chong_Trom();
  }
}

BLYNK_WRITE(V5)
{
  int stt = param.asInt();
  if (stt)
  {
    button_manu = 1;
  }
  else
    button_manu = 0;
}
