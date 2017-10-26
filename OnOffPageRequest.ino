#include <ESP8266WiFi.h>
 
const char* ssid = "Wifi_SSID";
const char* password = "Wifi_Password";
 
int led1 = 05; // GPIO0 
int led2 = 04; // GPIO4
int led3 = 00; // GPIO5
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(led1, OUTPUT);
  digitalWrite(led1, LOW);
  pinMode(led2, OUTPUT);
  digitalWrite(led2, LOW);
  pinMode(led3, OUTPUT);
  digitalWrite(led3, LOW);
 
  // Connect to WiFi network
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
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value1 = LOW, value2 = LOW, value3 = LOW;
  if (request.indexOf("/LED1=ON") != -1)  {
    digitalWrite(led1, HIGH);
    value1 = HIGH;
  }
  if (request.indexOf("/LED1=OFF") != -1)  {
    digitalWrite(led1, LOW);
    value1 = LOW;
  }
  if (request.indexOf("/LED2=ON") != -1)  {
    digitalWrite(led2, HIGH);
    value2 = HIGH;
  }
  if (request.indexOf("/LED2=OFF") != -1)  {
    digitalWrite(led2, LOW);
    value2 = LOW;
  }
  if (request.indexOf("/LED3=ON") != -1)  {
    digitalWrite(led3, HIGH);
    value3 = HIGH;
  }
  if (request.indexOf("/LED3=OFF") != -1)  {
    digitalWrite(led3, LOW);
    value3 = LOW;
  }
 
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Led pin is now: ");
 
  if(value1 == HIGH) {
    client.print("LED1 On");
  } else {
    client.print("LED1 Off");
  }
  if(value2 == HIGH) {
    client.print("LED2 On");
  } else {
    client.print("LED2 Off");
  }
  if(value3 == HIGH) {
    client.print("LED3 On");
  } else {
    client.print("LED3 Off");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED1=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/LED1=OFF\"\"><button>Turn Off </button></a><br />");  
  client.println("<br><br>");
  client.println("<a href=\"/LED2=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/LED2=OFF\"\"><button>Turn Off </button></a><br />");  
  client.println("<br><br>");
  client.println("<a href=\"/LED3=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/LED3=OFF\"\"><button>Turn Off </button></a><br />");  
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
 
