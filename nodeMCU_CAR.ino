#include <ESP8266WiFi.h>
 
const char* ssid = ""; //give yours
const char* password = "";
 
WiFiServer server(80);
 
void setup() {
  pinMode(12,OUTPUT);
pinMode(14,OUTPUT);
pinMode(2,OUTPUT);
pinMode(0,OUTPUT);
  Serial.begin(115200);
  delay(10);
 

 
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
 
  String value="";
  if (request.indexOf("/RIGHT") != -1)  {
     digitalWrite(12,LOW );
      digitalWrite(14,HIGH);
      digitalWrite(2,LOW );
      digitalWrite(0,HIGH);
    value = "RIGHT";
  }
  if (request.indexOf("/LEFT") != -1)  {
     digitalWrite(12,HIGH );
      digitalWrite(14,LOW);
      digitalWrite(2,HIGH );
      digitalWrite(0,LOW); 
    value ="LEFT";
  }
  if (request.indexOf("/FORWARD") != -1)  {
    digitalWrite(12,HIGH);
      digitalWrite(14,LOW );
      digitalWrite(2,LOW );
      digitalWrite(0,HIGH ); 
    value ="FORWARD";
  }
   if (request.indexOf("/BACKWARD") != -1)  {
    digitalWrite(12,LOW);
      digitalWrite(14,HIGH );
      digitalWrite(2,HIGH );
      digitalWrite(0,LOW ); 
    value ="BACKWARD";
  }
  if (request.indexOf("/STOP") != -1)  {
   digitalWrite(12,LOW );
      digitalWrite(14,LOW);
      digitalWrite(2,LOW );
      digitalWrite(0,LOW);
    value ="STOP";
  }
  
 
 
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
/*
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Your car is moving ");
 
  if(value == "RIGHT") {
    client.print("RIGHT");
  } else if(value="LEFT"){
    client.print("LEFT");
  }
  else if(value=="FORWARD")
  {
    client.print("FORWARD");
  }
  else if(value=="BACKWARD")
  {
    client.print("BACKWARD");
  }
  else if(value=="STOP")
  {
    client.print("STOP");
  }
  */
  //client.println("<br><br>");
  client.print("<body style='align-items:center;display:flex;flex-direction:column;margin-top: 50vh;'>");
  client.println("<a href=\"/FORWARD\"\" ><button  style='padding-top:20px;padding-bottom:20px;margin-bottom: 20px;background-image:linear-gradient(to bottom right,#673AB7,#3F51B5);color:white;border-radius: 12px;width: 22vh;font-size: 4em;height: 14vh;'>FORWARD </button></a>"); 
  client.println("<a href=\"/RIGHT\"\" ><button style='padding-top:20px;padding-bottom:20px;margin-right: 124px;background-image: linear-gradient(to bottom right,#8BC34A,#4CAF50);color:white;border-radius: 12px;width: 22vh;font-size: 4em;height: 14vh;'>RIGHT </button>");
  client.println("<a href=\"/LEFT\"\"><button style='padding-top:20px;padding-bottom:20px;color:white;border-radius: 12px;width: 22vh;font-size: 4em;height: 14vh;;background-image: linear-gradient(to bottom right,#FFEB3B,#9ba117)'>LEFT </button></a>");  
  client.println("<a href=\"/BACKWARD\"\"><button   style='padding-top:20px;padding-bottom:20px;margin-top: 22px;background-image:linear-gradient(to bottom right,#a51647,#ba1da9);color:white;border-radius: 12px;width: 23vh;font-size: 4em;height: 14vh;'>BACKWARD </button></a>"); 
  client.println("<a href=\"/STOP\"\"><button  style='padding-top:20px;padding-bottom:20px;margin-top: 80px;padding-left: 149px;padding-right:149px;background-color:#F44336;color:white;border-radius: 12px;width: 100vw;font-size: 4em;height: 14vh;'>STOP </button></a>"); 
  client.println("</body>");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
 
