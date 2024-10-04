
#include <ESP8266WiFi.h>
#include <ThingESP.h>
#include <DHT.h>

#define DHTPIN 2 
#define DHTTYPE DHT11     // DHT 11
DHT dht(DHTPIN, DHTTYPE);

ThingESP8266 thing("nithinmv", "TempratureHumid1", "nithinmv");


unsigned long previousMillis = 0;
const long INTERVAL = 6000;  
int moisture=A0;
void setup()
{
  Serial.begin(115200);
  pinMode(moisture, INPUT);

  thing.SetWiFi("Nithin-hp15s", "12345678");

  thing.initDevice();
}


String HandleResponse(String query)
{

 float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  Serial.println("Temperature :");
  Serial.print(t);
  Serial.println("Humidity");
  Serial.print(h);
  String humid = "Humidity: " + String(h) + " % \n";
  String temp = "Temperature: " + String(t) + "°C, " + String(f) + "°F \n";
  int sd=analogRead(moisture);
  String mo= "Moisture Value: " + String(sd) + "\n";
  String dry= "The Soil is dry:" + String(sd) + "\n";
  String humidsoil= "The Soil is humid:" + String(sd) + "\n";
  String notin= "The Sensor is not in soil" + String(sd) + "\n";
  if (query == "temperature") {
   
    return temp;
  }

  else if (query == "humidity") {
  
    return humid;
  }
  else if(query == "moisture"){
    // return mo;
    if(sd>600 && sd<1000){
      return dry;
    }
    else if(sd>=370 && sd<=600){
      return humidsoil;
    }
    else{
      return notin;
    }
  }
 
  else return "Your query was invalid..";

}


void loop()
{ 

  thing.Handle();

}
 
 