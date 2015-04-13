
#include "ethernet_pop.h"

void initEthernet(void)
{

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


void serverEthernet()
{

 EthernetClient client = server.available();
 
  if (client) {
  char thisChar = client.read();
  Serial.print(thisChar);
  }
  


}