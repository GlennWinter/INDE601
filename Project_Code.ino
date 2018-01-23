
#include <WiFi.h>
#include <PubSubClient.h>

// Setting up hot spot and broker settings
const char* ssid = "HTC Portable Hotspot 329F"; //variable for hotspot name
const char* password = "51EE58D052AA2";//variable for hotpass password //
const char* mqtt_server = "broker.i-dat.org"; //variable for mqtt broker name

WiFiClient espClient;
PubSubClient client(espClient); //connects these together

//setting up the GPIO ports on the arduino
int redLED = 13;
int yellowLED = 12;
int greenLED = 8;
int button;

//button variables
int buttonCounter =0;
int state = 0;
int recent = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize the digital pins so that they can be used for inputs and outputs
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(button, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
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
  //prints the IP of the board and "Wifi connected"
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
//connects to the MQTT server and retrieves data being sent to the GlennWorld MQTT topic
void callback(char* GlennWorld, byte* payload, unsigned int length) {  //function that runs everytime something is recieved
  Serial.print("Message arrived [");
  Serial.print(GlennWorld);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switches on the LED if the value from the sensor is above 0
 
  if ((char)payload[0] <= 0); {
     digitalWrite(redLED, HIGH);
    Serial.println("RED LED ENABLED");// Turn the red LED on if value is less than 0 
   
  }
   
   else ((char)payload[0] == 0); {
     digitalWrite(yellowLED, HIGH);
    Serial.println("ORANGE LED ENABLED");// Turn the orange LED on if value is 0
   
  } 
  else ((char)payload[0] >= 0); {
     digitalWrite(greenLED, HIGH);
    Serial.println("GREEN LED ENABLED");// Turn the green LED on if value is above 0
  }
}



void reconnect() {
  // Loops until board is reconnected to the WiFi
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempts connection MQTT server
    if (client.connect("15808cd41a854a03911b8a0b30dc30ceCAT")) { //Client ID in mqtt
      Serial.println("connected");
      //Posts if connection is successful
      client.publish("outTopic", "Connection Made"); //outopic of first variable
      // Resubscribes to MQTT channel
      client.subscribe("GlennWorld");
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


}
