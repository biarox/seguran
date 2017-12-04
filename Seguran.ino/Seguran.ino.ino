#include "ESP8266WiFi.h"


// WiFi parameters to be configured
const char* ssid = "bea";
const char* password = "adminadmin";
const int led = 15;
const int buzzerPin = 14;
const int motorHorario = 4;
const int motorAnti = 5;
int onOff = 1;
int buzzerOnOff = 0;
int motorHorarioOnOff = 0;
int motorAntiOnOff = 0;

WiFiServer server(80);
 
void setup() {

  Serial.begin(115200);
  delay(10);
 
  // prepare 
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
 
  pinMode(motorHorario, OUTPUT);
  digitalWrite(motorHorario, 0);
  
  pinMode(motorAnti, OUTPUT);
  digitalWrite(motorAnti, 0);
    
  pinMode (buzzerPin, OUTPUT);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
}
 
void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

 // Mudança de status do buzzer 
  if (req.indexOf("buzzer_on") != -1){
    buzzerOnOff = 2000;
    tone(buzzerPin, buzzerOnOff);
  }
  
  if (req.indexOf("buzzer_off") != -1){
    buzzerOnOff = 0;
    noTone(buzzerPin);
  }
  
   
  // Mudança de status do led 
  if (req.indexOf("led_on") != -1){
    onOff = 1;
  }
  
  if (req.indexOf("led_off") != -1){
    onOff = 0;
  }
  
  digitalWrite(led, onOff);
  
  String ledStatus = "";
  if(onOff == 0){
    ledStatus = "on";
  }else{
    ledStatus = "off";
  }

  String buzzerStatus = "";
  if(buzzerOnOff == 0){
    buzzerStatus = "off";
  }else{
    buzzerStatus = "on";
  }

// Mudança de status do motor de passo ON 
  if (req.indexOf("motor_horario_on") != -1){
    motorHorarioOnOff = 1;
    Serial.println("Motor horário ON");

  }
  
  if (req.indexOf("motor_horario_off") != -1){
    motorHorarioOnOff = 0;
    Serial.println("Motor horário OFF");
  }
  
  digitalWrite(motorHorario, motorHorarioOnOff);


  String motorHorarioStatus = "";
  
  if(onOff == 0){
    motorHorarioStatus = "on";
     
     }else{
    motorHorarioStatus = "off";
     
  }

// Mudança de status do motor de passo OFF 
  if (req.indexOf("motor_anti_on") != -1){
    motorAntiOnOff = 1;
    Serial.println("Motor ANTI horário ON");
   
  }
  
  if (req.indexOf("motor_anti_off") != -1){
    motorAntiOnOff = 0;
  }
  
  digitalWrite(motorAnti, motorAntiOnOff);

    
  String motorAntiStatus = "";
  if(motorAntiOnOff == 0){
    motorAntiStatus = "on";
  }else{
    motorAntiStatus = "off";
  }

  
  String buf = "{ buzzer: '" + buzzerStatus + "',led: '"+ ledStatus + "',motor: '" + 0 +" }";
  client.print(buf);
  client.flush();
  
  Serial.println("Client disonnected");
}
