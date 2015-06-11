/*
 * Sparkfun wrapper by JVK75
 */

#include <ESP8266WiFi.h>

#define readyPin 2 //ready for next command when pin HIGH

const char* host = "data.sparkfun.com";
String publickey;
String privatekey;

bool isConnected = false;
bool dataReady = false;
bool gotSsid = false;
bool gotPass = false;

String ssid;
String password;

void setup() {
  pinMode(readyPin, OUTPUT);
  digitalWrite(readyPin,LOW);
  Serial.begin(115200);
  delay(100);
  Serial.println("");
  Serial.println("ESP8266Wifi wrapper for data.sparkfun.com starting");
}

void loop() {
  delay(100);
  digitalWrite(readyPin,HIGH);
  readSerial();
}

void readSerial() {
  if (Serial.available()) {
    digitalWrite(readyPin,LOW);
    
    String readData = "";
    while (Serial.available()) {
      char c = Serial.read();
      if (c == ' ') {
        Serial.println(readData);
        if (readData == "connect") {
          Serial.print("connect: ");
          ssid = readNextUntil(':');
          Serial.print(ssid);
          Serial.print(" ");
          password = readNext();
          Serial.println(password);
          connectWifi(ssid.c_str(),password.c_str());
        } else if (readData == "publickey") {
          Serial.print("publickey: ");
          publickey = readNext().c_str();
          Serial.println(publickey);
        } else if (readData == "privatekey") {
          Serial.print("privatekey: ");
          privatekey = readNext().c_str();
          Serial.println(privatekey);
        } else if (readData == "data") {
          if (isConnected) {
            sendDataToServer(parseInput());
          }
        }
      } else {
        readData += c;
      }
    }
    Serial.print("readData -> ");
    Serial.println(readData);
    
    //digitalWrite(readyPin,HIGH);
  }
}

String readNext()
{
  String readWord = "";
  while (Serial.available()) {
    char c = Serial.read();
    if (!(c == '\r' || c == '\n')) {
      readWord += c;
    }
  }
  return readWord;
}

String readNextUntil(char until)
{
  String readWord = "";
  while (Serial.available()) {
    char c = Serial.read();
    if (!(c == '\r' || c == '\n' || c == until)) {
      readWord += c;
    } else {
      return readWord;
    }
  }
  return readWord;
}

void connectWifi(const char* ssid, const char* password)
{
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  isConnected = true;
}

void sendDataToServer(String dataToSend)
{
  Serial.print("sendDataToServer: ");
  Serial.println(dataToSend);
      
  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  // We now create a URI for the request
  String url = "/input/";
  url += publickey;
  url += "?private_key=";
  url += privatekey;
  url += "&";
  url += dataToSend;
  
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(100);
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
  Serial.println();
}


String parseInput()
{
  String data;
  while (Serial.available()){
    char c = Serial.read();
    if (c == '"') {
      data += readNextUntil('"');
    } else if (c == ':'){
      data += "=";
    } else if (c == ','){
      data += "&";
    }
  }
  return data;
}


