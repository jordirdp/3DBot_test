# 3DBot_test
🔗Creado por [Jordi Rodriguez](https://github.com/jordirdp)  

👨🏻‍💻Práctica de **programación básica con bloques** en Steamakersblock sobre Arduino 

<img src="/Images/3dbot.jpg" width="300"/>   
    
### Software  
- Programado con [ArduinoBlocks](http://www.arduinoblocks.com/web/)
- Este código simplemente realiza un test del hardware instalado:
    - Buzzer reacciona a sensores de línea, iluminación ambiental y distancia de obstáculos
    - Movimiento delante/atrás/izquierda/derecha con el mando a distancia
    - Temperatura mostrada en la Consola  


### Hardware  
- Arduino UNO  
- Shield Imagina V3 con Bluetooth  
- HC-SR04 = Sensor ultrasonido de distancia  
- TCRT5000 = Sensor infrarrojo de proximidad (3x)  
- Motores Arduino (2x)  
- Mando para control remoto  

### Montaje    
🔧 Conexiones a pines Arduino UNO:  
- A00 = Zumbador  
- A01 = Sensor   
- A02 = Sensor lumínico LDR  
- A03 = Sensor de temperatura (NTC)  
- A04 = I2C LCD (SDA)  
- A05 = I2C LCD (SCL)  
- D00 = (RX) Bluetooth  
- D01 = (TX) Bluetooth  
- D02 = Sensor ultrasonidos / Pulsador  
- D03-= Led verde / Emisor infrarrojo
- D04 = Sensor ultrasonidos  
- D05-= Led amarillo / Sensor de línea izquierdo  
- D06-= Led rojo / Sensor de línea derecho  
- D07 = Motor A  
- D08 = Motor A  
- D09-= Motor A  
- D10-= Motor B  
- D11-= Receptor infrarrojo  
- D12 = Motor B   
- D13 = Motor B  

### Licencia  
⚖️Todo el contenido distribuido bajo [licencia GPL-3.0](https://www.gnu.org/licenses/gpl-3.0), salvo indicación expresa.  
Las referencias y librerías empleadas, estarán sujetas a sus propia licencia, y no se incluyen en este repositorio.  
