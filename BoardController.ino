// Import required libraries
#include "ESP8266WiFi.h"
#include <aREST.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
 
// And connect 2 DC motors to port M3 & M4 !
Adafruit_DCMotor *L_MOTOR = AFMS.getMotor(1);
Adafruit_DCMotor *R_MOTOR = AFMS.getMotor(2);

// Create aREST instance
aREST rest = aREST();

// WiFi parameters
const char* ssid = "wincity_boyz";
const char* password = "114941mr";

// The port to listen for incoming TCP connections 
#define LISTEN_PORT           80

// Create an instance of the server
WiFiServer server(LISTEN_PORT);

// Function
int stop(String message);
int forward(String message);
int right(String message);
int left(String message);
int backward(String message);
int honk(String message);

// Defines pins used
int speakerPin = 13;
int trigPin = 12;
int echoPin = 14;

// Defines variables
long duration;
int distance;

void setup(void)
{
  // Start Serial
  Serial.begin(115200);

  // Init proximity sensor
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  // Init motor shield
  AFMS.begin();

  // Functions
  rest.function("stop", stop);
  rest.function("forward", forward);
  rest.function("left", left);
  rest.function("right", right);
  rest.function("backward", backward);
  rest.function("honk", honk);

  // Give name and ID to device
  rest.set_id("1");
  rest.set_name("robot");

  // Connect to WiFi
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
  Serial.println(WiFi.localIP());

}

void loop() {
  //Handle Proximity Sensor

  digitalWrite(trigPin, LOW);// Clears the trigPin
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);// Sets the trigPin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);  // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;   // Calculating the distance
  Serial.print("Distance: ");   // Prints the distance on the Serial Monitor
  Serial.println(distance);
  if(distance < 5){
    Serial.print("STOPPPP");
    honk("");
    stop("");
    delay(500);
  }

  // Handle REST calls
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while(!client.available()){
    delay(1);
  }
  rest.handle(client);
}

int stop(String command) {
  // Stop
  L_MOTOR->setSpeed(0);
  L_MOTOR->run( RELEASE );

  R_MOTOR->setSpeed(0);
  R_MOTOR->run( RELEASE );
}

int forward(String command) {
  // Stop
  L_MOTOR->setSpeed(50);
  L_MOTOR->run( FORWARD );

  R_MOTOR->setSpeed(50);
  R_MOTOR->run( FORWARD );
}

int left(String command) {
  // Stop
  L_MOTOR->setSpeed(50);
  L_MOTOR->run( BACKWARD );

  R_MOTOR->setSpeed(50);
  R_MOTOR->run( FORWARD );
}

int right(String command) {
  // Stop
  L_MOTOR->setSpeed(50);
  L_MOTOR->run( FORWARD );

  R_MOTOR->setSpeed(50);
  R_MOTOR->run( BACKWARD );
}

int backward(String command) {
  // Stop
  L_MOTOR->setSpeed(50);
  L_MOTOR->run( BACKWARD );

  R_MOTOR->setSpeed(50);
  R_MOTOR->run( BACKWARD );
}

int honk(String command){
  tone(speakerPin,311);
  delay(500);
  noTone(speakerPin);
}