# README

## Control de Relés con Arduino y Ethernet

Este proyecto permite el control remoto de relés utilizando un módulo Arduino con capacidad Ethernet. Utiliza el protocolo UDP para la comunicación entre el Arduino y un servidor remoto, permitiendo cambiar el estado de los relés (encendido/apagado) de manera remota y reportar el estado actual de los mismos al servidor.

### Requisitos de Hardware

- Placa Arduino compatible (por ejemplo, Arduino Uno, Mega, etc.)
- Módulo Ethernet (UIPEthernet) compatible con Arduino
- Relés conectados a los pines digitales del Arduino

### Configuración del Proyecto

El código fuente proporcionado necesita configurarse adecuadamente antes de cargarlo al Arduino. Esto incluye la configuración de la dirección IP, máscara de subred, puerta de enlace, servidor DNS, y la dirección MAC del módulo Ethernet.

```cpp
uint8_t mac[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
IPAddress serverIp(192, 168, 1, 17); // IP del servidor que recibirá los datos
IPAddress subnet(255, 255, 255, 0); // Depende de tu red
IPAddress ip(192, 168, 1, 200); // Depende de tu red
IPAddress gateway(192, 168, 1, 1); // Depende de tu red
IPAddress dnsserver(192, 168, 1, 1); // Depende de tu red
```

### Uso

Una vez configurado y cargado el código en el Arduino, el sistema está listo para recibir comandos UDP del servidor remoto para controlar los relés. El Arduino reportará el estado de los relés (encendido/apagado) al servidor cada 5 segundos o después de cambiar el estado de algún relé.

### Funciones Principales

- `void setup()`: Configura el módulo Ethernet, inicia la comunicación UDP y configura los pines de los relés como salidas.
- `void sendRelayStates()`: Envía el estado actual de los relés al servidor.
- `void controlRelays(String command)`: Procesa los comandos recibidos para controlar los relés.
- `void loop()`: Se encarga de la recepción de mensajes UDP y del envío periódico del estado de los relés.

### Personalización

- Cambia las direcciones IP y MAC según la configuración de tu red.
- Ajusta los pines de los relés según cómo estén conectados a tu placa Arduino.

### Contribuciones

Este proyecto es abierto y cualquier contribución para mejorar su funcionalidad o documentación es bienvenida. 

---

Este README proporciona una visión general básica del proyecto. Para una implementación exitosa, asegúrate de adaptar la configuración a tu entorno de red específico y realizar las pruebas necesarias.
