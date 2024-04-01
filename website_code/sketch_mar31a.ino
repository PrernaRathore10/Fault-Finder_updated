/*
  this example will show
  1. how to use and ESP 32 for reading pins
  2. building a web page for a client (web browser, smartphone, smartTV) to connect to
  3. sending data from the ESP to the client to update JUST changed data
  4. sending data from the web page (like a slider or button press) to the ESP to tell the ESP to do something
  If you are not familiar with HTML, CSS page styling, and javascript, be patient, these code platforms are
  not intuitive and syntax is very inconsitent between platforms
  I know of 4 ways to update a web page
  1. send the whole page--very slow updates, causes ugly page redraws and is what you see in most examples
  2. send XML data to the web page that will update just the changed data--fast updates but older method
  3. JSON strings which are similar to XML but newer method
  4. web sockets very very fast updates, but not sure all the library support is available for ESP's
  I use XML here...
  compile options
  1. esp32 dev module
  2. upload speed 921600
  3. cpu speed 240 mhz
  flash speed 80 mhz
  flash mode qio
  flash size 4mb
  partition scheme default
  NOTE if your ESP fails to program press the BOOT button during programm when the IDE is "looking for the ESP"
  The MIT License (MIT)
  code writen by Kris Kasprzak
  
  Permission is hereby granted, free of charge, to any person obtaining a copy of
  this software and associated documentation files (the "Software"), to deal in
  the Software without restriction, including without limitation the rights to
  use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
  the Software, and to permit persons to whom the Software is furnished to do so,
  subject to the following conditions:
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
  FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
  COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
  IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
  On a personal note, if you develop an application or product using this code 
  and make millions of dollars, I'm happy for you!
*/

// #include <WiFi.h>       // standard library
// #include <WebServer.h>  // standard library
#include "SuperMon.h"   // .h file that stores your html page code

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// here you post web pages to your homes intranet which will make page debugging easier
// as you just need to refresh the browser as opposed to reconnection to the web server
#define USE_INTRANET

// replace this with your homes intranet connect parameters
#define LOCAL_SSID ":"
#define LOCAL_PASS "9424025594"

// once  you are read to go live these settings are what you client will connect to
#define AP_SSID "TestWebSite"
#define AP_PASS "023456789"

// start your defines for pins for sensors, outputs etc.
#define PIN_OUTPUT 26 // connected to nothing but an example of a digital write from the web page
#define PIN_FAN 27    // pin 27 and is a PWM signal to control a fan speed
#define PIN_LED 2     //On board LED
// #define PIN_A0 34     // some analog input sensor
#define PIN_A1 35     // some analog input sensor
/*
-----> OLD CODE - END
// variables to store measure data and sensor states
int BitsA0 = 0, BitsA1 = 0;
float VoltsA0 = 0, VoltsA1 = 0;
int FanSpeed = 0;
bool LED0 = false, SomeOutput = false;
int FanRPM = 0;
------> OLD CODE - START
*/
uint32_t SensorUpdate = 0;

// the XML array size needs to be bigger that your maximum expected size. 2048 is way too big for this example
char XML[2048];

// just some buffer holder for char operations
char buf[32];

// variable for the IP reported when you connect to your homes intranet (during debug mode)
IPAddress Actual_IP;

// definitions of your desired intranet created by the ESP32
IPAddress PageIP(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress ip;

// gotta create a server
ESP8266WebServer server(80);


// -----> Variable declaration for ldr and current sensor - start ;

// Auxiliar variables to store the current output state of LDR's

String ldr0_state = "ON";
String ldr1_state = "ON";
String ldr2_state = "ON";
String ldr3_state = "ON";
String ldr4_state = "ON";
String ldr5_state = "ON";
String ldr6_state = "ON";
String ldr7_state = "ON";

int ldr0_value = 0;
int ldr1_value = 0;
int ldr2_value = 0;
int ldr3_value = 0;
int ldr4_value = 0;
int ldr5_value = 0;
int ldr6_value = 0;
int ldr7_value = 0;

// VCC Pin for Current Sensor and Multiplexer Control for Analog Pin
int Pin_D5_current_sensor = 14;

// int Pin_D6_multiplexer = 12;

//Pin declaration for Multiplexing pins
const int pin_Out_S0 = D3;
const int pin_Out_S1 = D2;
const int pin_Out_S2 = D1;
// const int pin_In_Mux1 = A0;  Commentted because we are using A0 for both Current Sensing and Multiplexing

// Mux1_State is the Array to store values of LDR(1-8)
int Mux1_State[8][2] = {0};

//Pin declaration for Current Sensor pins
const int sensorIn = A0;
int mVperAmp = 100; // use 185 for 5A, 100 for 20A Module and 66 for 30A Module

double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;
double Wattage=0;

//-----> Variable declaration for ldr and current sensor - end ;

void setup() {

  // standard stuff here
  Serial.begin(115200);

  // pinMode(PIN_FAN, OUTPUT);
  // pinMode(PIN_LED, OUTPUT);

  // // turn off led
  // LED0 = false;
  // digitalWrite(PIN_LED, LED0);

  // ------> PinMode declaration for led and current sensor - Start
  // Initialize the output variables as outputs
  pinMode(pin_Out_S0, OUTPUT);
  pinMode(pin_Out_S1, OUTPUT);
  pinMode(pin_Out_S2, OUTPUT);
  //pinMode(pin_In_Mux1, INPUT);
  pinMode(Pin_D5_current_sensor, OUTPUT);

  //setting pins as low
  digitalWrite(pin_Out_S0, LOW);
  digitalWrite(pin_Out_S1, LOW);
  digitalWrite(pin_Out_S2, LOW);
  digitalWrite(Pin_D5_current_sensor, LOW);

  // Defining A0 as Input pin
  pinMode(sensorIn, INPUT);
  // -----> PinMode declaration for led and current sensor - End

  // if your web page or XML are large, you may not get a call back from the web page
  // and the ESP will think something has locked up and reboot the ESP
  // not sure I like this feature, actually I kinda hate it
  // disable watch dog timer 0
  // disableCore0WDT();

  // maybe disable watch dog timer 1 if needed
  //  disableCore1WDT();

  // just an update to progress
  Serial.println("starting server");

  // if you have this #define USE_INTRANET,  you will connect to your home intranet, again makes debugging easier
#ifdef USE_INTRANET
  WiFi.begin(LOCAL_SSID, LOCAL_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("IP address: "); Serial.println(WiFi.localIP());
  Actual_IP = WiFi.localIP();
#endif

  // if you don't have #define USE_INTRANET, here's where you will creat and access point
  // an intranet with no internet connection. But Clients can connect to your intranet and see
  // the web page you are about to serve up
#ifndef USE_INTRANET
  WiFi.softAP(AP_SSID, AP_PASS);
  delay(100);
  WiFi.softAPConfig(PageIP, gateway, subnet);
  delay(100);
  Actual_IP = WiFi.softAPIP();
  Serial.print("IP address: "); Serial.println(Actual_IP);
#endif

  printWifiStatus();


  // these calls will handle data coming back from your web page
  // this one is a page request, upon ESP getting / string the web page will be sent
  server.on("/", SendWebsite);

  // upon esp getting /XML string, ESP will build and send the XML, this is how we refresh
  // just parts of the web page
  server.on("/xml", SendXML);

  // upon ESP getting /UPDATE_SLIDER string, ESP will execute the UpdateSlider function
  // same notion for the following .on calls
  // add as many as you need to process incoming strings from your web page
  // as you can imagine you will need to code some javascript in your web page to send such strings
  // this process will be documented in the SuperMon.h web page code
  // server.on("/UPDATE_SLIDER", UpdateSlider);
  // server.on("/BUTTON_0", ProcessButton_0);
  // server.on("/BUTTON_1", ProcessButton_1);

  // finally begin the server
  server.begin();

}

void loop() {

  // you main loop that measures, processes, runs code, etc.
  // note that handling the "on" strings from the web page are NOT in the loop
  // that processing is in individual functions all managed by the wifi lib

  // in my example here every 50 ms, i measure some analog sensor data (my finger dragging over the pins
  // and process accordingly
  // analog input can be from temperature sensors, light sensors, digital pin sensors, etc.
  if ((millis() - SensorUpdate) >= 50) {
    //Serial.println("Reading Sensors");
    SensorUpdate = millis();
    // BitsA0 = analogRead(PIN_A0);
    // BitsA1 = analogRead(PIN_A1);

    //----> Funtion Call - Start
    analogRead1(); // Read Analog value of Current Sensor
    analogRead2(); // Read Analog value of Multiplexer (LDR's)
    //----> Funtion Call - End

    // standard converion to go from 12 bit resolution reads to volts on an ESP
    // VoltsA0 = BitsA0 * 3.3 / 4096;
    // VoltsA1 = BitsA1 * 3.3 / 4096;

  }

  // no matter what you must call this handleClient repeatidly--otherwise the web page
  // will not get instructions to do something
  server.handleClient();

}

/* 
-------> OLD CODE - START
// function managed by an .on method to handle slider actions on the web page
// this example will get the passed string called VALUE and conver to a pwm value
// and control the fan speed
void UpdateSlider() {
  // many I hate strings, but wifi lib uses them...
  String t_state = server.arg("VALUE");
  // conver the string sent from the web page to an int
  FanSpeed = t_state.toInt();
  Serial.print("UpdateSlider"); Serial.println(FanSpeed);
  // now set the PWM duty cycle
  // YOU MUST SEND SOMETHING BACK TO THE WEB PAGE--BASICALLY TO KEEP IT LIVE
  // option 1: send no information back, but at least keep the page live
  // just send nothing back
  // server.send(200, "text/plain", ""); //Send web page
  // option 2: send something back immediately, maybe a pass/fail indication, maybe a measured value
  // here is how you send data back immediately and NOT through the general XML page update code
  // my simple example guesses at fan speed--ideally measure it and send back real data
  // i avoid strings at all caost, hence all the code to start with "" in the buffer and build a
  // simple piece of data
  FanRPM = map(FanSpeed, 0, 255, 0, 2400);
  strcpy(buf, "");
  sprintf(buf, "%d", FanRPM);
  sprintf(buf, buf);
  // now send it back
  server.send(200, "text/plain", buf); //Send web page
}
// now process button_0 press from the web site. Typical applications are the used on the web client can
// turn on / off a light, a fan, disable something etc
void ProcessButton_0() {
  //
  LED0 = !LED0;
  digitalWrite(PIN_LED, LED0);
  Serial.print("Button 0 "); Serial.println(LED0);
  // regardless if you want to send stuff back to client or not
  // you must have the send line--as it keeps the page running
  // if you don't want feedback from the MCU--or let the XML manage
  // sending feeback
  // option 1 -- keep page live but dont send any thing
  // here i don't need to send and immediate status, any status
  // like the illumination status will be send in the main XML page update
  // code
  server.send(200, "text/plain", ""); //Send web page
  // option 2 -- keep page live AND send a status
  // if you want to send feed back immediataly
  // note you must have reading code in the java script
  /*
    if (LED0) {
    server.send(200, "text/plain", "1"); //Send web page
    }
    else {
    server.send(200, "text/plain", "0"); //Send web page
    }
  */
/*
}
// same notion for processing button_1
void ProcessButton_1() {
  // just a simple way to toggle a LED on/off. Much better ways to do this
  Serial.println("Button 1 press");
  SomeOutput = !SomeOutput;
  digitalWrite(PIN_OUTPUT, SomeOutput);
Serial.print("Button 1 "); Serial.println(LED0);
  // regardless if you want to send stuff back to client or not
  // you must have the send line--as it keeps the page running
  // if you don't want feedback from the MCU--or send all data via XML use this method
  // sending feeback
  server.send(200, "text/plain", ""); //Send web page
  // if you want to send feed back immediataly
  // note you must have proper code in the java script to read this data stream
  /*
    if (some_process) {
    server.send(200, "text/plain", "SUCCESS"); //Send web page
    }
    else {
    server.send(200, "text/plain", "FAIL"); //Send web page
    }
  */
  /*
}
// ----> OLD CODE - END
*/

// code to send the main web page
// PAGE_MAIN is a large char defined in SuperMon.h
void SendWebsite() {

  Serial.println("sending web page");
  // you may have to play with this value, big pages need more porcessing time, and hence
  // a longer timeout that 200 ms
  server.send(200, "text/html", PAGE_MAIN);

}

// code to send the main web page
// I avoid string data types at all cost hence all the char mainipulation code
void SendXML() {

  // Serial.println("sending xml");

  strcpy(XML, "<?xml version = '1.0'?>\n<Data>\n");

  // send bitsA0
  sprintf(buf, "<B0>%s</B0>\n", ldr0_state);
  strcat(XML, buf);
  // send Volts0
  sprintf(buf, "<V0>%d.%d</V0>\n", (int) (ldr0_value));
  // sprintf(buf, "<V0>%d.%d</V0>\n", (int) (VoltsA0), abs((int) (VoltsA0 * 10)  - ((int) (VoltsA0) * 10)));
  strcat(XML, buf);


  // send bitsA1
  sprintf(buf, "<B1>%s</B1>\n", ldr1_state);
  strcat(XML, buf);
  // send Volts1
  sprintf(buf, "<V1>%d.%d</V1>\n", (int) (ldr1_value));
  strcat(XML, buf);

  // send bitsA2
  sprintf(buf, "<B2>%s</B2>\n", ldr2_state);
  strcat(XML, buf);
  // send Volts2
  sprintf(buf, "<V2>%d.%d</V2>\n", (int) (ldr2_value));
  strcat(XML, buf);

  // send bitsA3
  sprintf(buf, "<B3>%s</B3>\n", ldr3_state);
  strcat(XML, buf);
  // send Volts3
  sprintf(buf, "<V3>%d.%d</V3>\n", (int) (ldr3_value));
  strcat(XML, buf);

  // send bitsA4
  sprintf(buf, "<B4>%s</B4>\n", ldr4_state);
  strcat(XML, buf);
  // send Volts4
  sprintf(buf, "<V4>%d.%d</V4>\n", (int) (ldr4_value));
  strcat(XML, buf);

  // send bitsA5
  sprintf(buf, "<B5>%s</B5>\n", ldr5_state);
  strcat(XML, buf);
  // send Volts5
  sprintf(buf, "<V5>%d.%d</V5>\n", (int) (ldr5_value));
  strcat(XML, buf);

  // send bitsA6
  sprintf(buf, "<B6>%s</B6>\n", ldr6_state);
  strcat(XML, buf);
  // send Volts7
  sprintf(buf, "<V6>%d.%d</V6>\n", (int) (ldr6_value));
  strcat(XML, buf);

  // send bitsA7
  sprintf(buf, "<B7>%s</B7>\n", ldr7_state);
  strcat(XML, buf);
  // send Volts7
  sprintf(buf, "<V7>%d.%d</V7>\n", (int) (ldr7_value));
  strcat(XML, buf);

  // send bits1
  sprintf(buf, "<B8>%d</B8>\n", (int)AmpsRMS);
  strcat(XML, buf);
  // send Volts1
  sprintf(buf, "<V8>%d.%d</V8>\n", (int) (VRMS), abs((int) (VRMS * 10)  - ((int) (VRMS) * 10)));
  strcat(XML, buf);
/*
---> OLD CODE - START
  // show led0 status
  if (LED0) {
    strcat(XML, "<LED>1</LED>\n");
  }
  else {
    strcat(XML, "<LED>0</LED>\n");
  }
  if (SomeOutput) {
    strcat(XML, "<SWITCH>1</SWITCH>\n");
  }
  else {
    strcat(XML, "<SWITCH>0</SWITCH>\n");
  }
  -----> OLD CODE - ENDS
  */

  strcat(XML, "</Data>\n");
  // wanna see what the XML code looks like?
  // actually print it to the serial monitor and use some text editor to get the size
  // then pad and adjust char XML[2048]; above
  Serial.println(XML);

  // you may have to play with this value, big pages need more porcessing time, and hence
  // a longer timeout that 200 ms
  server.send(200, "text/xml", XML);


}

// I think I got this code from the wifi example
void printWifiStatus() {

  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("Open http://");
  Serial.println(ip);
}


// -----> Functions for led and current sensors - Start 

float getVPP()
{
  float result;

  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here

   uint32_t start_time = millis();

   while((millis()-start_time) < 1000) //sample for 1 Sec
    {
      readValue = analogRead(sensorIn);
      // see if you have a new maxValue
      if (readValue > maxValue) {
        //record the maximum sensor value/
        maxValue = readValue;
      }
      if (readValue < minValue) 
      {
        //record the maximum sensor value/
        minValue = readValue;
      }
      // Serial.print(readValue);
      // Serial.println(" readValue ");
      // Serial.print(maxValue);
      // Serial.println(" maxValue ");
      // Serial.print(minValue);
      // Serial.println(" minValue ");
      delay(100);
    }

   // Subtract min from max
   result = (minValue * 5)/1024.0;

   return result;
 }


 void analogRead1() {
    digitalWrite(Pin_D5_current_sensor, HIGH); // Turn D5 Current Sensor ON
    digitalWrite(pin_Out_S0, LOW); //Turn Multiplexer OFF
    digitalWrite(pin_Out_S1, LOW); //Turn Multiplexer OFF
    digitalWrite(pin_Out_S2, LOW); //Turn Multiplexer OFF

    //CODE FOR CURRENT SENSOR VALUES
    Voltage = getVPP();
    VRMS = (Voltage/2.0) *0.707; // sq root
    AmpsRMS = (VRMS * 1000)/mVperAmp;
    Wattage = (220*AmpsRMS)-18; //Observed 18-20 Watt when no load was connected, so substracting offset value to get real consumption.
    // Serial.print("\n");
    // Serial.println(" Amps RMS : "+ (String)AmpsRMS);
    // Serial.println(" Watt : "+ (String) Wattage);
    // Serial.print("\n\n");

    digitalWrite(Pin_D5_current_sensor, LOW); // Turn D5 Current Sensor OFF
}

int analogRead2() {
    digitalWrite(Pin_D5_current_sensor, LOW); //  Turn D5 Current Sensor OFF
    digitalWrite(pin_Out_S0, HIGH); //Turn Multiplexer ON
    digitalWrite(pin_Out_S1, HIGH); //Turn Multiplexer ON
    digitalWrite(pin_Out_S2, HIGH); //Turn Multiplexer ON

    for (int i = 0; i < 8; i++){
      //Loops has 8 iterations for 0-7 pins of 8 ldr's
      digitalWrite(pin_Out_S0, HIGH && (i & B00000001)); //Set value for S0
      digitalWrite(pin_Out_S1, HIGH && (i & B00000010)); //Set value for S1
      digitalWrite(pin_Out_S2, HIGH && (i & B00000100)); //Set value for S2
      Mux1_State[i][1] = analogRead(sensorIn);  //Input values of LDR from analog pin A0 i.e. defined as pin_In_Mux1
    } 

    for(int i=0; i<8; i++){
      if( Mux1_State[i][1] < 900 ){ //if value >900 means Light is off i.e. there is darkness and if value < 900 means light is on i.e. there is light
        if(i == 0){
          ldr0_state = "ON";
        } else if(i == 1){
          ldr1_state = "ON";
        } else if(i == 2){
          ldr2_state = "ON";
        } else if(i == 3){
          ldr3_state = "ON";
        } else if(i == 4){
          ldr4_state = "ON";
        } else if(i == 5){
          ldr5_state = "ON";
        } else if(i == 6){
          ldr6_state = "ON";
        } else if(i == 7){
          ldr7_state = "ON";
        }
      }
      else{
        if(i == 0){
          ldr0_state = "OFF";
        } else if(i == 1){
          ldr1_state = "OFF";
        } else if(i == 2){
          ldr2_state = "OFF";
        } else if(i == 3){
          ldr3_state = "OFF";
        } else if(i == 4){
          ldr4_state = "OFF";
        } else if(i == 5){
          ldr5_state = "OFF";
        } else if(i == 6){
          ldr6_state = "OFF";
        } else if(i == 7){
          ldr7_state = "OFF";
        }
      }
      ldr0_value = Mux1_State[0][1];
      ldr1_value = Mux1_State[1][1];
      ldr2_value = Mux1_State[2][1];
      ldr3_value = Mux1_State[3][1];
      ldr4_value = Mux1_State[4][1];
      ldr5_value = Mux1_State[5][1];
      ldr6_value = Mux1_State[6][1];
      ldr7_value = Mux1_State[7][1];

    }
    digitalWrite(pin_Out_S0, LOW); //Turn Multiplexer OFF
    digitalWrite(pin_Out_S1, LOW); //Turn Multiplexer OFF
    digitalWrite(pin_Out_S2, LOW); //Turn Multiplexer OFF
    return analogRead(0);
}
// //CODE FOR MULTIPLEXER VALUES (i.e. LED is ON/OFF)
// updateMux1();
// for(int i = 0; i < 8; i ++) {
//   // In this for loop we've to read LDR values from Mux1_State Array
//   if(i == 7) {
//     Serial.println(Mux1_State[i]);
//   } else {
//     Serial.print(Mux1_State[i]);
//     Serial.print(",");
//   }
// }

// -----> Functions for led and current sensors - End 

// end of code
 717 changes: 717 additions & 0 deletions717  
savino/super