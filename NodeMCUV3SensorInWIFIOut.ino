
#include "max6675.h"
#include <ESP8266WiFi.h>
//#include <Wire.h>
 
int ktcSO = 12;
int ktcCS = 13;
int ktcCLK = 14;

const char* ssid = "INFINITUM119D_2.4";
const char* password = "JuanitoPerez2";
int ledPin = 15; // GPIO13 D07

WiFiServer server(80); 
MAX6675 ktc(ktcCLK, ktcCS, ktcSO);
  
void setup() {
  Serial.begin(9600); //use the same on Tools, Upload Speed
  delay(50);

    // Connect to WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  // Start the server
    server.begin();
  Serial.println("Server started");
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
  return;
  }
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
  delay(1);
  }
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  //Sensor variables assignation
  float DC = ktc.readCelsius();
  // Read temperature as Celsius
  float DF = ktc.readFahrenheit();

  // Return the response
  client.println("HTTP/1.1 200 OK");
  while (client.available()){
    client.println("Content-Type: text/html");
    client.println(""); // do not forget this one
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.print("C = ");
    client.print(ktc.readCelsius());
    //client.print("F = ");
    //client.print(ktc.readFahrenheit());
    delay(1000);
    client.flush();
    //client.clear();
    }
  //displayData();
}
 
