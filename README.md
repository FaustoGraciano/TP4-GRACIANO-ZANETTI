# TP4-GRACIANO-ZANETTI

# Control de LED RGB con PWM

Este programa permite controlar la intensidad y el color de un LED RGB utilizando la técnica de Modulación por Ancho de Pulso (PWM). El LED RGB está conectado a los terminales PB5, PB2 y PB1 del microcontrolador en configuración de ánodo común.

## Configuración del Hardware

El LED RGB está conectado a través de resistencias limitadoras de 220 ohms a los siguientes pines del microcontrolador:
- PB5 (Rojo)
- PB2 (Verde)
- PB1 (Azul)

Para la simulación en Proteus, se puede utilizar el modelo RGBLED-CA.

## Funcionalidades del Programa

1. **Generación de Señales PWM:**
   Se generan tres señales PWM en los pines mencionados, con una frecuencia mayor o igual a 50Hz y una resolución de 8 bits cada una.

2. **Selección de la Proporción de Color:**
   Se puede seleccionar la proporción de color de cada LED (de 0 a 255) para obtener un color resultante deseado.

3. **Interfaz Serie UART0:**
   Mediante un comando enviado por la interfaz serie UART0, se activa la modificación de la proporción de color deseada:
   - Envíe `R` para modificar el color rojo.
   - Envíe `G` para modificar el color verde.
   - Envíe `B` para modificar el color azul.

4. **Control de Brillo:**
   Utilice el potenciómetro (resistencia variable) conectado al terminal ADC3 para ajustar el brillo del color seleccionado. El ADC3 se encarga de convertir la señal analógica del potenciómetro a un valor digital que controla la intensidad del color.

## Implementación y Ejecución

Para ejecutar el programa:
- Configure su entorno de desarrollo según el microcontrolador y el compilador utilizado.
- Cargue el programa en el microcontrolador y asegúrese de que esté correctamente conectado al LED RGB y al potenciómetro.
- Utilice una terminal serial (como PuTTY o minicom) para enviar los comandos `R`, `G` o `B` y ajustar el brillo según sea necesario.

## Ejemplo de Uso

1. Enviar `R` por la interfaz UART0.
2. Ajustar el potenciómetro para cambiar la intensidad del color rojo, para finalizar el ajuste, presionar `E`.
3. Enviar `G` por la interfaz UART0.
4. Ajustar el potenciómetro para cambiar la intensidad del color verde, para finalizar el ajuste, presionar `E`.
5. Enviar `B` por la interfaz UART0.
6. Ajustar el potenciómetro para cambiar la intensidad del color azul, para finalizar el ajuste, presionar `E`.
