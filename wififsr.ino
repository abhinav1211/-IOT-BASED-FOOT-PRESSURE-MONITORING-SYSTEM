#include <ESP8266WiFi.h>
const char* ssid     = "Bablu@nayak"; // Your ssid
const char* password = "balu@!123"; // Your Password
WiFiServer server(80);
#define LED D0            // Led in NodeMCU at pin GPIO16 (D0).
#define LED1 D1            // Led in NodeMCU at pin GPIO16 (D0).
#define LED2 D2            // Led in NodeMCU at pin GPIO16 (D0).
void setup() 
{
 Serial.begin(115200);
 pinMode(A0, INPUT); 
 pinMode(LED, OUTPUT);  
 pinMode(LED1, OUTPUT); 
 pinMode(LED2, OUTPUT);  
Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi is connected");
server.begin();
Serial.println("Server started");
Serial.println(WiFi.localIP());
}
void loop() 
{
int fsr_val = analogRead(A0); // To convert analog values to Celsius We have 3.3 V on our board and we know that output voltage of LM35 varies by 10 mV to every degree Celsius rise/fall. So , (A0*3300/10)/1023 = celsius
Serial.print(" pressure ");
Serial.print(fsr_val);
if(fsr_val < 10)
{
  digitalWrite(D0,1);
  digitalWrite(D1,0);
  digitalWrite(D2,0);
}
else if(fsr_val < 200)
  {
    Serial.println(" - Light touch");
    digitalWrite(D0,1);
    digitalWrite(D1,0);
    digitalWrite(D2,0);
  } 
  else if (fsr_val < 500) 
  {
    Serial.println(" - Light squeeze");
    digitalWrite(D0,1);
    digitalWrite(D1,0);
    digitalWrite(D2,0);
  } 
  else if(fsr_val < 800) 
  {
    Serial.println(" - Medium squeeze");
    digitalWrite(D0,0);
    digitalWrite(D1,0);
    digitalWrite(D2,1);
  }
  else 
  {
    Serial.println(" - Big squeeze");
    digitalWrite(D0,1);
    digitalWrite(D1,0);
    digitalWrite(D2,0);
  }
  
WiFiClient client = server.available();
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println("Connection: close");  // the connection will be closed after completion of the response
client.println("Refresh: 10");  // update the page after 10 sec
client.println();
client.println("<!DOCTYPE HTML>");
client.println("<html>");
client.print("<p style='text-align: center;'><span style='font-size: x-large;'><strong>Digital Thermometer</strong></span></p>");
client.print("<p style='text-align: center;'><span style='color: #0000ff;'><strong style='font-size: large;'>fsr_val= ");
client.println(fsr_val);
//client.print("<p style='text-align: center;'><span style='color: #0000ff;'><strong style='font-size: large;'>Temperature (F) = ");
//client.println(temp_fahrenheit);
client.print("</p>");
client.println("</html>");
delay(5000);
}
