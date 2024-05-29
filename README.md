# Sistema de Monitoreo de Cargador de Baterías

Este repositorio contiene el código para un sistema de monitoreo de cargador de baterías utilizando un Arduino. El sistema monitorea la temperatura, corriente, voltaje, potencia, porcentaje de batería y tiempo restante de carga/descarga, mostrando la información en una pantalla OLED. También incluye alertas sonoras para diversas condiciones como sobrecarga, carga completa, batería baja, sobrecarga y alta temperatura.

## Características

- **Monitoreo de Temperatura**: Lee y muestra la temperatura utilizando un sensor LM35.
- **Monitoreo de Corriente**: Lee y muestra la corriente utilizando un sensor ACS712.
- **Monitoreo de Voltaje**: Lee y muestra el voltaje del sensor ACS712.
- **Cálculo de Potencia**: Calcula y muestra la potencia (P = V * I).
- **Cálculo del Porcentaje de Batería**: Calcula y muestra el porcentaje de batería basado en el voltaje.
- **Cálculo del Tiempo Restante**: Estima y muestra el tiempo restante de carga/descarga.
- **Alertas Sonoras**: Reproduce alertas sonoras para sobrecarga, carga completa, batería baja, sobrecarga y alta temperatura.
- **Pantalla OLED**: Muestra todos los parámetros monitoreados en una pantalla OLED de 128x64 píxeles.
- **Carga USB**: Utiliza la batería monitoreada para cargar dispositivos mediante un puerto USB.

## Componentes Utilizados

- Arduino (cualquier modelo con entradas analógicas suficientes y soporte I2C)
- Sensor de Temperatura LM35
- Sensor de Corriente ACS712
- Pantalla OLED Adafruit SSD1306 (128x64 píxeles)
- Módulo de Tarjeta SD
- Altavoz
- Resistencias y capacitores varios
- Módulo de Carga USB

## Configuración de Pines

- **Sensor de Temperatura LM35**: Conectado a A0
- **Sensor de Corriente ACS712**: Conectado a A1
- **Pantalla OLED**: 
  - SDA: A4 (en Arduino UNO, puede variar en otros modelos)
  - SCL: A5 (en Arduino UNO, puede variar en otros modelos)
- **Módulo de Tarjeta SD**: 
  - CS: Pin 4
  - Otros pines conectados según las especificaciones del módulo SD (MISO, MOSI, SCK)
- **Altavoz**: Conectado al Pin 9

## Consideraciones

- Asegúrate de que la tarjeta SD contenga los archivos de audio necesarios (`complete.wav`, `low_batt.wav`, `overload.wav`, `high_temp.wav`).
- Calibra adecuadamente los sensores según tu hardware y requerimientos específicos.
- El cálculo del tiempo restante es una estimación y debe ajustarse según las especificaciones y patrones de uso reales de la batería.
- Asegúrate de que la fuente de alimentación para el Arduino y los módulos conectados sea estable para evitar lecturas erróneas.

## Configuración e Instalación

1. **Clonar el Repositorio**:
    ```bash
    git clone https://github.com/tuusuario/BatteryChargerMonitor.git
    ```
2. **Abrir el Proyecto**:
    Abre el archivo `BatteryChargerMonitor.ino` en el Arduino IDE.
3. **Instalar Bibliotecas Requeridas**:
    - Adafruit GFX Library
    - Adafruit SSD1306 Library
    - TMRpcm Library
4. **Conectar el Hardware**:
    Conecta todos los componentes según la configuración de pines mencionada arriba.
5. **Subir el Código**:
    Sube el código a tu Arduino utilizando el Arduino IDE.

## Uso

Una vez completada la configuración y subido el código, el sistema comenzará a monitorear y mostrar los parámetros de la batería en la pantalla OLED. Las alertas sonoras se activarán basadas en las condiciones especificadas. La batería monitoreada puede utilizarse para cargar dispositivos mediante el puerto USB.

## Ejemplo de Salida

Temp: 25.0 C
Current: 0.5 A
Voltage: 3.7 V
Power: 1.85 W
Battery: 75 %
Time: 3.75 h


## Contribuciones

¡Las contribuciones son bienvenidas! Por favor, haz un fork del repositorio y crea una pull request con tus cambios. Asegúrate de que tu código siga el estilo existente e incluye mensajes de commit detallados.


## Agradecimientos

- [Adafruit](https://www.adafruit.com/) por la pantalla OLED y las bibliotecas
- [Arduino](https://www.arduino.cc/) por la plataforma y el apoyo de la comunidad
- [TMRpcm Library](https://github.com/TMRh20/TMRpcm) por las capacidades de reproducción de audio
