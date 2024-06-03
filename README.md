
## Batalla Naval

Este repositorio contiene implementaciones de clases para simular un juego de batalla naval.

## Autores

Leonel Cledon
Marcelo Nelson
Emanuel Boz

## Clases Principales

1. **AircraftCarrier**:
   - Atributos:
     - No se especifican atributos en el archivo proporcionado.
   - Métodos Públicos (firma):
     - `AircraftCarrier()`: Constructor.

2. **Battleship**:
   - Atributos:
     - No se especifican atributos en el archivo proporcionado.
   - Métodos Públicos (firma):
     - `Battleship()`: Constructor.

3. **Cruiser**:
   - Atributos:
     - No se especifican atributos en el archivo proporcionado.
   - Métodos Públicos (firma):
     - `Cruiser()`: Constructor.
4. **Player**:
   - Atributos:
     - No se especifican atributos en el archivo proporcionado.
   - Métodos Públicos (firma):
     - `Player()`: Constructor
5. **Game**:
   - Atributos:
     - No se especifican atributos en el archivo proporcionado.
   - Métodos Públicos (firma):
     - `Game()`: Constructor
6. **Destroyer**:
   - Atributos:
     - No se especifican atributos en el archivo proporcionado.
   - Métodos Públicos (firma):
     - `Destroyer()`: Constructor
7. **Board**:
   - Atributos:
     - No se especifican atributos en el archivo proporcionado.
   - Métodos Públicos (firma):
     - `Board()`: Constructor

## Estrategia de Uso de Archivos

### Cantidad de Archivos de Texto Utilizados

Se utilizarán al menos dos archivos de texto:
1. **Archivo de Configuración**: Para guardar la configuración del juego, como el tamaño del tablero y los tipos de barcos.
2. **Archivo de Estado del Juego**: Para guardar el estado actual del juego, incluyendo la posición de los barcos y los ataques realizados.

### Datos a Escribir en Cada Archivo

1. **Archivo de Configuración**:
   
     Tamaño del Tablero: 10x10
     Tipos de Barcos: Aircraft Carrier, Battleship, Cruiser

2. **Archivo de Estado del Juego**:

     Posición de los Barcos:
     - Aircraft Carrier: (A1, A2, A3, A4)
     - Battleship: (B1, B2, B3)
     - Cruiser: (C1, C2)
     Ataques Realizados:
     - A1: Hit
     - B2: Miss

### Asociación de Archivos

Los archivos estarán asociados de la siguiente manera:
- El archivo de configuración se leerá al inicio del juego para establecer la configuración adecuada.
- El archivo de estado del juego se actualizará durante el juego y se leerá para cargar el estado anterior.

### Formato para Guardar los Datos

Los datos se guardarán en formato de texto plano, separando cada atributo o valor por coma o línea nueva según corresponda.

### Serialización/Deserialización de Datos

Para serializar datos no basados en strings, se utilizarán las siguientes funciones:
- Para convertir un número a std::string: `std::to_string(numero)`
- Para convertir un std::string a un número: `std::stoi(string)`

Esto garantizará que los datos se guarden y carguen correctamente en los archivos de texto.

Recuerda que el uso de archivos es fundamental para persistir el estado del juego y administrar los datos entre sesiones de ejecución.
```
