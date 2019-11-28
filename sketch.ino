#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "./config.h"

WiFiClient wifi;
ESP8266WebServer server(80);

void handleIndex()
{
  server.send(200, "text/html", "Hello world");
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  while (!Serial)
  { // Wait for the serial port to connect
    Serial.println();
  }

  setupWiFi();

  server.on("/", handleIndex);
  server.begin();

  blink(2);
}

void setupWiFi()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  Serial.print(" ");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(250);
    Serial.print(".");
  }

  Serial.println(" done!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void blink(int count)
{
  for (int i = 0; i < count; i++)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(150);
    digitalWrite(LED_BUILTIN, LOW);
    delay(150);
    digitalWrite(LED_BUILTIN, HIGH);
  }
}

void loop()
{
  server.handleClient();
}
