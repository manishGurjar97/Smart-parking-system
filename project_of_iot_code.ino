#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Manish";
const char* password = "12345678";

WebServer server(80);

// Pin connections for four sensors
const int sensor1Pin = 5;  // D5
const int sensor2Pin = 4;  // D4
const int sensor3Pin = 19; // D19
const int sensor4Pin = 23; // D23

int sensor1State = HIGH;
int sensor2State = HIGH;
int sensor3State = HIGH;
int sensor4State = HIGH;

// Function to handle the status of all sensors
void handleStatus() {
    sensor1State = digitalRead(sensor1Pin);
    sensor2State = digitalRead(sensor2Pin);
    sensor3State = digitalRead(sensor3Pin);
    sensor4State = digitalRead(sensor4Pin);

    // Constructing the response for all sensors
    String response = "Sensor 1: " + String(sensor1State == LOW ? "on" : "off") + "\n";
    response += "Sensor 2: " + String(sensor2State == LOW ? "on" : "off") + "\n";
    response += "Sensor 3: " + String(sensor3State == LOW ? "on" : "off") + "\n";
    response += "Sensor 4: " + String(sensor4State == LOW ? "on" : "off") + "\n";

    server.send(200, "text/plain", response);
}

void setup() {
    Serial.begin(115200);

    // Initialize sensor pins as input
    pinMode(sensor1Pin, INPUT);
    pinMode(sensor2Pin, INPUT);
    pinMode(sensor3Pin, INPUT);
    pinMode(sensor4Pin, INPUT);

    // Connect to WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");

    Serial.print("NodeMCU IP Address: ");
    Serial.println(WiFi.localIP());

    // Define server route to get the status of all sensors
    server.on("/status", handleStatus);
    server.begin();
    Serial.println("Server started");
}

void loop() {
    server.handleClient();
}

