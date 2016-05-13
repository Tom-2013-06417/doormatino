/*
 * UIPEthernet TcpClient example.
 *
 * UIPEthernet is a TCP/IP stack that can be used with a enc28j60 based
 * Ethernet-shield.
 *
 * UIPEthernet uses the fine uIP stack by Adam Dunkels <adam@sics.se>
 *
 *	 -----------------
 *
 * This TcpClient example gets its local ip-address via dhcp and sets
 * up a tcp socket-connection to 192.168.0.1 port 5000 every 5 Seconds.
 * After sending a message it waits for a response. After receiving the
 * response the client disconnects and tries to reconnect after 5 seconds.
 *
 * Copyright (C) 2013 by Norbert Truchsess <norbert.truchsess@t-online.de>
 */

#include <UIPEthernet.h>


EthernetClient client;

int threshold = 512;

int counter = 1;

int sensorReading;


void setup() {

	Serial.begin(9600);

	uint8_t mac[6] = {0x00,0x01,0x02,0x03,0x04,0x05};
	Ethernet.begin(mac);

  //pinMode(knockSensor, INPUT);

	// Serial.print("localIP: ");
	// Serial.println(Ethernet.localIP());
	// Serial.print("subnetMask: ");
	// Serial.println(Ethernet.subnetMask());
	// Serial.print("gatewayIP: ");
	// Serial.println(Ethernet.gatewayIP());
	// Serial.print("dnsServerIP: ");
	// Serial.println(Ethernet.dnsServerIP());

  Serial.println("Client connecting...");

  if (client.connect(IPAddress(192,168,1,35),3000)) Serial.println("Client connected!");
  
  else Serial.println("Client connect failed");
  
}


void loop() {

  sensorReading = analogRead(A0);
  //Serial.println(sensorReading);

  if (sensorReading >= threshold){
    sendData(counter);
    delay(500);          
  }

  while (client.available()){
    client.read();
  } 
  
  delay(500);             // delay to avoid overloading the serial port buffer

  Ethernet.maintain();    //Added just to make sure it doesn't prolly tears the connection

}


void sendData(int thisData){

	String JsonData = "{\"steps\": {\"value\": ";	
	JsonData = JsonData + thisData;
	JsonData = JsonData + "}}";		

	client.println("PATCH / HTTP/1.1");
  client.println("User-Agent: Arduino/1.0");
	client.println("Host: 192.168.1.33:3000");	
	client.println("Accept: application/json");
  client.println("Content-Type: application/json");
	client.print("Content-Length: ");
	client.println(JsonData.length());
	
	client.println("Connection: Keep-Alive");
	client.println();
	client.print(JsonData);
	
	Serial.print("DATA from Client: ");
  Serial.println(JsonData);

//  if (client.available()) {
//    char c = client.read();
//    Serial.print(c);
//  }
	
//	close:
//		Serial.println("Client disconnect");
//		client.stop();  

}


