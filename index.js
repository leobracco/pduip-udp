const dgram = require('dgram');
const mqtt = require('mqtt');
const server = dgram.createSocket('udp4');
const mqttClient = mqtt.connect('mqtt://127.0.0.1'); // Utiliza cualquier broker MQTT público o tu propio broker

const MQTT_TOPIC = '/servidor'; // El tópico al que te suscribes para recibir comandos
const UDP_PORT = 5000; // Puerto para clientes UDP

server.on('error', (err) => {
  console.log(`Server error:\n${err.stack}`);
  server.close();
});

server.on('message', (msg, rinfo) => {
  console.log(`Server got: ${msg} from ${rinfo.address}:${rinfo.port}`);
  // Aquí puedes responder al cliente UDP si es necesario
});

server.on('listening', () => {
  const address = server.address();
  console.log(`Server listening ${address.address}:${address.port}`);
});

// Inicia la escucha de mensajes UDP
server.bind(UDP_PORT);

// MQTT Client
mqttClient.on('connect', () => {
  console.log('Conectado al broker MQTT');
  mqttClient.subscribe(MQTT_TOPIC, (err) => {
    if (!err) {
      console.log(`Suscrito al tópico '${MQTT_TOPIC}'`);
    }
  });
});

mqttClient.on('message', (topic, message) => {
  console.log(`Mensaje recibido en el tópico '${topic}': ${message}`);

  // Aquí debes extraer la dirección IP y el puerto del mensaje o utilizar valores predeterminados
  const udpMessage = message; // Asume que el mensaje es adecuado para reenviar directamente
  const targetIp = '10.176.100.242'; // La IP del cliente UDP objetivo
  const targetPort = 8888; // El puerto del cliente UDP objetivo

  // Reenvía el mensaje MQTT como un mensaje UDP
  server.send(udpMessage, 0, udpMessage.length, targetPort, targetIp, (err) => {
    if (err) {
      console.error('Error al enviar el mensaje UDP:', err);
    } else {
      console.log(`Mensaje UDP enviado a ${targetIp}:${targetPort}`);
    }
  });
});
