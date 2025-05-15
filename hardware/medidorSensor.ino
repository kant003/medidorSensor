#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h> // Para el sensor de temperatura y humedad
#include <Wire.h> 
#include <Adafruit_Sensor.h>
#include <Adafruit_SI1145.h> // Para el sensor de radiación UV

// Configuración WiFi
const char* ssid = "Cebem_21"; 
const char* password = "Cebem2010";

// Configuración del sensor DHT
#define DHTPIN 4 // Pin donde está conectado el sensor DHT
#define DHTTYPE DHT11 // Tipo de sensor de temperatura y humedad
DHT dht(DHTPIN, DHTTYPE);

// Configuración del sensor UV
Adafruit_SI1145 uv = Adafruit_SI1145();

// URL del endpoint
String serverUrl = "https://medidorsensor.onrender.com/saveMeasure";

// Dirección MAC del ESP32
String macAddress = WiFi.macAddress();

void setup() {
  // Inicia la comunicación serie
  Serial.begin(115200);

  // Inicia la conexión WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando al WiFi...");
  }
  Serial.println("Conectado al WiFi!");

  // Inicializa los sensores
  dht.begin();
  if (!uv.begin()) {
    Serial.println("No se pudo inicializar el sensor UV.");
    //while (1);
  }
}

void loop() {
  // Obtiene los datos de los sensores
  float temperature = dht.readTemperature(); // Temperatura en grados Celsius
  float humidity = dht.readHumidity(); // Humedad relativa
  float solarRadiation = uv.readUV(); // Radiación solar medida por el sensor UV

  // Verifica si los valores de los sensores son válidos
  if (isnan(temperature) || isnan(humidity) || isnan(solarRadiation)) {
    Serial.println("Error al leer los sensores, poniendolos a 0");
    temperature=0;
    humidity=0;
    solarRadiation=0;
   // return;
  }

  // Crea el JSON para enviar
  String json = "{\"mac\":\"" + macAddress + "\",\"temperature\":" + String(temperature) + ",\"humidity\":" + String(humidity) + ",\"solarRadiation\":" + String(solarRadiation) + "}";

  // Enviar datos al servidor
  HTTPClient http;
  http.begin(serverUrl); // Especifica la URL del servidor
  http.addHeader("Content-Type", "application/json"); // Tipo de contenido

  // Realiza la solicitud POST
  int httpResponseCode = http.POST(json);

  if (httpResponseCode > 0) {
    Serial.println("Datos enviados correctamente");
    Serial.println("Código de respuesta HTTP: " + String(httpResponseCode));
  } else {
    Serial.println("Error al enviar los datos");
  }

  http.end(); // Cierra la conexión

  // Espera 1 segundo antes de la siguiente medición
  delay(1000);
}
