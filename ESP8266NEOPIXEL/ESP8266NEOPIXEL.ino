//CREATED BY EDWARD C. DEAVER, IV
//DESCRIPTION: THIS IS USED TO RMTLY CONTROL NEOPIXEL TO RECREATE A MUZZEL FLASH. 
//TO DO:
// NEED TO CREATE COLOR PALLET FOR MUZZEL FLASH
// THEN CREATE THE A FLASH
// WANT EVENTUALLY:
// CONTROL THE PARAMETERS VIA WEBPAGE
//BASED ON TUTORIAL BY Nuno Santos on techtutorialsx.com


#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Adafruit_NeoPixel.h>

#define NUMPIXELS    144
//Set to Number of LEDS to 144

#define BRIGHTNESS 255
//Set to MAX 255

ESP8266WebServer server(80);
//Set web server to port 80

int ledPin = 4;
char ssid[] = "SSID";
char pass[] = "PASS";

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, ledPin, NEO_RGBW + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass); //Connect to the WiFi network
   
  strip.begin(); // This initializes the NeoPixel library.
  strip.setBrightness(BRIGHTNESS);
  setLEDrsOFF();
  
  while (WiFi.status() != WL_CONNECTED) { //Wait for connection

    delay(500);
    Serial.println("Waiting to connect…");

    }

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); //Print the local IP
  server.on("/", setLEDrsOFF);
  server.on("/on", setLEDs);         //Associate the handler function to the path
  server.on("/off", setLEDrsOFF);        //Associate the handler function to the path

  server.begin(); //Start the server
  Serial.println("Server listening");

  }
void loop() {

server.handleClient();

}


void setLEDs(){
    for(int i = 0; i<NUMPIXELS; i = i+1){

    //MAX BRIGHTNESS
    strip.setPixelColor(i, 255, 255, 255, 255);
    //HOLD TILL COLOR IS CHOSEN
       //   if(i%2 == 0){
   //     strip.setPixelColor(i, 0, 255, 0, 0);
   //   }
     // if(i%2 == 1){
    //    strip.setPixelColor(i, 100, 255, 0, 0);
    //  }
  }
  strip.show();
  server.send(200, "text/plain", "LED on");

}

void setLEDrsOFF(){
    for(int i = 0; i<NUMPIXELS; i = i+1){
      strip.setPixelColor(i, 0, 0, 0, 0);
  }
 strip.show();
  server.send(200, "text/plain", "LED OFF");

}

