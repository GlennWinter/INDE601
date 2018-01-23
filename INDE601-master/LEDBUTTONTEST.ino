
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Setting up hot spot and broker settings
const char* ssid = "Android HTC"; //variable for hotspot name
const char* password = "password12345";//variable for hotpass password
const char* mqtt_server = "broker.i-dat.org"; //variable for mqtt broker name

WiFiClient espClient;
PubSubClient client(espClient); //connects these together

long lastMsg = 0; //facevalues
char msg[50];
int value = 0;

int redLED = 13;
int yellowLED = 12;
int greenLED = 8;

int buttonCounter =0;
int state = 0;
int recent = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(button, INPUT);
  Serial.begin(9600);
  setup_wifi(); //Enables the wifi on the board
  client.setServer(mqtt_server, 80); //IDAT BROKER
  client.setCallback(callback); //Calls a function everytime a message is recieved
  
}

void setup_wifi() {

  delay(10);
  // Connects to the network set in the global variables and gives status
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  //sets user know wifi is connected and what the IP of the board is
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void callback(char* topic, byte* payload, unsigned int length) {  //function that runs everytime something is recieved
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switches on the LED if the value from the sensor is above 0
 
  if ((char)payload[0] != '0') {
    digitalWrite(BUILTIN_LED, LOW); 
    Serial.println("LDR WORKING");// Turn the LED on if value from sensor is above 0 meaning data is recorded
   
  }
   
   else { //LED stays off if 0 is recorded on the sensor
    digitalWrite(BUILTIN_LED, HIGH);  
      Serial.println("No data detected on LDR"); 
  }
}


void reconnect() {
  // Loops until board is reconnected to the network
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempts connection
    if (client.connect("ESP8266Client12345kk")) { //Client ID in mqtt
      Serial.println("connected");
      // Once connection is successful, posts announcement
      client.publish("123456", "hello world"); //outopic of first variable
      // ... resubscribes
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before trying to connect again
      delay(5000);
    }
  }
}
void loop() {
  //If client isn't connected then called reconnect function
  if (!client.connected()) {
    reconnect();
  }
 
  client.loop();
  delay (500);
  //Reads sensor value
  sensorValue = analogRead(sensorPin);
  digitalWrite(ledPin, HIGH);
  delay(sensorValue);
  digitalWrite(ledPin, LOW);
  delay(sensorValue);
  
  Serial.println(sensorValue, DEC);
  char buf [4];
  sprintf (buf, "%03i", sensorValue); //converting integer to char
    client.publish("123456", buf);

}

// the loop function runs over and over again forever
void loop() {
 
  digitalWrite(redLED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(3000);                       // wait for a second
  digitalWrite(redLED, LOW);    // turn the LED off by making the voltage LOW
  delay(3000);                       // wait for a second

  digitalWrite(yellowLED, HIGH);   
  delay(3000);                      
  digitalWrite(yellowLED, LOW);    
  delay(3000);

  digitalWrite(greenLED, HIGH);   
  delay(3000);                      
  digitalWrite(greenLED, LOW);    
  delay(3000); 
}
