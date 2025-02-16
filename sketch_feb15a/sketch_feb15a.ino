#include <DHT11.h>
#include <ArduinoJson.h>

// Sensor DHT11 conectado ao pino digital 2
DHT11 dht11(2);

// Sensor de luminosidade no pino analógico A0
const int analogInPin = A0;

// Objeto JSON para armazenar os dados dos sensores
JsonDocument sensor;

void setup() {
  // Inicia a comunicação serial com taxa de 9600 bps
  Serial.begin(9600);

  // Define um intervalo de 4000ms entre leituras do DHT11 (o padrão é 500ms)
  dht11.setDelay(4000);
}

void loop() {
  int temperatura = 0;
  int umidade = 0;

  // Realiza a leitura da temperatura e umidade do DHT11 a cada 4000ms
  int result = dht11.readTemperatureHumidity(temperatura, umidade);

  // Lê o valor do sensor de luminosidade em ohms
  int luminosidade = map(analogRead(analogInPin), 0, 1023, 0, 10000);

  // Verifica se a leitura foi bem-sucedida
  if (result == 0) {
    sensor["temperatura"] = temperatura;
    sensor["umidade"] = umidade;
    sensor["luminosidade"] = luminosidade;

    // Generate the minified JSON and send it to the Serial port.
    serializeJson(sensor, Serial);

     // Start a new line
    Serial.println();

  } else {
    // Exibe mensagem de erro caso a leitura do DHT11 falhe
    Serial.print("Erro na leitura do DHT11: ");
    Serial.println(DHT11::getErrorString(result));
  }
}





