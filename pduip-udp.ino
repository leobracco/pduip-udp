#include <UIPEthernet.h>

EthernetUDP udp;
unsigned long next;
uint8_t mac[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};

IPAddress serverIp(192, 168, 1, 17);//The Server who will get the data
IPAddress subnet(255, 255, 255, 0);//This depends on your network
IPAddress ip(192, 168, 1, 200);//Depends on your network
IPAddress gateway(192, 168, 1, 1);//depends on your network
IPAddress dnsserver(192, 168, 1, 1);//depends on your network

unsigned int localPort = 8888; 
unsigned int serverPort = 5000; 
const String deviceId = "LB-PDU4-000173";
const int relayPins[] = {4, 5, 6, 7};

void setup() {
  

   Ethernet.begin(mac, ip, dnsserver, gateway, subnet);
  udp.begin(localPort);
  for (int relayPin : relayPins) {
    pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin, LOW);
   
  }
  next = millis() + 5000;
  
  sendRelayStates();
}

void sendRelayStates() {
  String message = deviceId + ",RELAYS,";
  for (int relayPin : relayPins) {
    bool state = digitalRead(relayPin) == HIGH;
    message += state ? "ON," : "OFF,";
  }
  message.remove(message.length() - 1);
  udp.beginPacket(serverIp, serverPort);
  udp.write(message.c_str());
  udp.endPacket();
 
  
}

void controlRelays(String command) {
 
  if (!command.startsWith(deviceId)) {
    
    return;
  }

  int separatorIndex = command.indexOf(',', deviceId.length() + 1);
  if (separatorIndex == -1) {
   
    return;
  }

  int relayNumber = command.substring(deviceId.length() + 1, separatorIndex).toInt() - 1;
  String relayCommand = command.substring(separatorIndex + 1);

  if (relayNumber >= 0 && relayNumber < 4) {
    digitalWrite(relayPins[relayNumber], relayCommand.equals("ON") ? HIGH : LOW);
   
    sendRelayStates();
  }
}

void loop() {
  // Comprueba si ha llegado un nuevo paquete
  int packetSize = udp.parsePacket();
  if (packetSize) {
    
    String message = "";
    // Lee el mensaje
    while (udp.available()) {
      char c = udp.read();
      message += c;
    }
   
    controlRelays(message); // Procesa el mensaje
  }

  // Envía el estado de los relés cada 5 segundos
  if (millis() - next >= 5000) {
    sendRelayStates();
    next = millis(); // Actualiza el tiempo para el próximo envío
  }
}
