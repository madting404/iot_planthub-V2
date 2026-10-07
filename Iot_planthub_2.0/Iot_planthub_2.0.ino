#include <DHT.h>
#include <Servo.h>

#define DHTPIN 2
#define DHTTYPE DHT22
#define SOIL_SENSOR A1
#define servoPin 9
#define FAN 6
#define PUMP 7
#define HEATER 8

int soil_moisture = 0;

// Calibrate these with your real readings
constexpr int air_value = 650;   // driest reading
constexpr int wet_value = 0;     // wettest reading
constexpr int intervals = (air_value - wet_value) / 3;

Servo seansServo;
int posHome = 0;
int posOpen = 70;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();

  pinMode(FAN, OUTPUT);
  pinMode(PUMP, OUTPUT);
  pinMode(HEATER, OUTPUT);

  seansServo.attach(9);
  seansServo.write(posHome);

delay(5000);
  Serial.println("Setup complete");
}

void loop() {
  float temperature = dht.readTemperature();
  if (isnan(temperature)) {
    Serial.println("DHT read failed");
  } else {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");
  }

  soil_moisture = analogRead(SOIL_SENSOR);

  Serial.print("Soil moisture raw: ");
  Serial.println(soil_moisture);

  // Soil classification (includes boundaries)
  if (soil_moisture <= wet_value + intervals) {
    Serial.println("The soil is too wet");
    digitalWrite(PUMP, LOW);
  } 
  else if (soil_moisture <= air_value - intervals) {
    Serial.println("The soil is wet");
    digitalWrite(PUMP, LOW);
  } 
  else {
    Serial.println("The soil is dry");
    digitalWrite(PUMP, HIGH);
  }

  // Temperature control
  if (!isnan(temperature) && temperature > 15.0) {
    digitalWrite(FAN, HIGH);
    Serial.println("Fan is On");

    if (temperature >= 20.0) {
      seansServo.write(posOpen);
      Serial.println("Roof has extended ");
      delay(8000);
      Serial.println("Servo is retracted");
      seansServo.write(posHome);
    } 
  
  } else {
    digitalWrite(FAN, LOW);
    seansServo.write(posHome);
    Serial.println("Fan is Off");
  }
if (temperature > 10.0){
  digitalWrite(HEATER, HIGH);
}
   else {digitalWrite(HEATER, LOW);
}
  delay(10000);
}