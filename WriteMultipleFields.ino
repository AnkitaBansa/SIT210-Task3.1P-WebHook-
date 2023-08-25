#include <WiFiNINA.h> //This library for WiFi functionality
#include <DHT.h>  //This library for DHT sensor
#include <ThingSpeak.h>  // Include the ThingSpeak library for data sending to ThingSpeak directly

#define DHTPIN 7 //Set the pin to 7 where DHT senser is connected.
#define DHTTYPE DHT11 

char ssid[] = "Get lost"; //Your own WiFi Name
char pass[] = "bansalankita27"; // Write WiFi Network Password

const char *thingSpeakApiKey = "36OCHK7GZH371H3Y"; //Replace with your writeAPIKey which is in your channel on ThingSpeak
unsigned long channelNumber = 2249954; // Replace with your ChannelId that is on ThingSpeak

DHT dht(DHTPIN, DHTTYPE); //This is the constructor to create DHT

WiFiClient client; // Create a WiFi client object

void setup() {
  Serial.begin(9600); //Initialize serial communication
  connectWiFi(); //This is a call function to connect to WiFi Network
  ThingSpeak.begin(client);  
  dht.begin(); //Initialize the DHT sensor
}

void loop() {
  float temperature = dht.readTemperature(); //Read the temperature from DHT11 sensor

  if (!isnan(temperature)) {
    Serial.print("Temperature: "); //print on serial monitor to show temperature readings
    Serial.println(temperature);

    // Send data to ThingSpeak
    ThingSpeak.writeField(channelNumber, 1, temperature, thingSpeakApiKey);

    delay(30000); // To get the next redaing, wait for 30 seconds
  }
}

void connectWiFi() {
  Serial.print("Connecting to WiFi..."); //print on serial monitor when it is in processing to connect to wifi

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) { //Wait until WiFi is connected 
    delay(1000); // For one second the application will pause every 1000 milliseconds
    Serial.print(".");
  }
  //For the time of trying to connect to WiFi, the loop above repeats.
  Serial.println("\nConnected to WiFi"); //Gaves a new line on serial monitor when it is connected to WiFi
}