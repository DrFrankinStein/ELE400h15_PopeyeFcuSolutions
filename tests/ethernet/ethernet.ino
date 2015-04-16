#include <Keypad.h>


#include <SPI.h>
#include <Ethernet.h>
#include "ethernet_pop.h"


byte mac[] = {
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02
};
IPAddress ip(192, 168, 1, 102);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);


// telnet defaults to port 23
EthernetServer server(60000);
boolean gotAMessage = false; // whether or not you got a message from the client yet




void setup() {
  Serial.begin(9600);
  
 if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // initialize the ethernet device not using DHCP:
    Ethernet.begin(mac, ip, gateway, subnet);
  }
 
 Serial.print("My IP address: ");
  ip = Ethernet.localIP();
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(ip[thisByte], DEC);
    Serial.print(".");
  }
 server.begin();
}



void loop() {
  EthernetClient client = server.available();
 
  if (client) {
  char thisChar = client.read();
  Serial.print(thisChar);
  }
  
  

}
