#include <dht.h>
 
dht DHT21;
#define DHT21PIN 2    // pin 2 for temperature and humidity sensor

#define A0  A0
int led12green = 12;
int led11yellow = 11;
int led10red = 10;
int sensorPower9 = 9;

int analogValue = 0;
int percentageValue = 0;

int MAX_SENSOR_VALUE = 600; // measured by putting moisture sensor into water
int MIN_SENSOR_VALUE = 6; // measured  by putting moisture sensor in the air (not used)
int SENSOR_INIT_TIME = 3*1000; // we have to wait for stabilisation after power is turned on
long SLEEP_TIME = 4L*60L*1000L; // sleeps to increase life time of sensor. It must be long because maximim int value is 32767. For develepment change to 4L*1000L

/**
 * @author Bartek Kwiatkowski, 2018
 */

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(led12green, OUTPUT);
  pinMode(led11yellow, OUTPUT);
  pinMode(led10red, OUTPUT);
  pinMode(sensorPower9, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  // MOISTURE SENSOR ######################################
  digitalWrite(sensorPower9, HIGH);
  delay(SENSOR_INIT_TIME);
  
  analogValue = analogRead(A0);
  percentageValue = moisture(analogValue);

  Serial.print("Moisture sensor value: ");
  Serial.print(analogValue);
  Serial.print("  ");
  Serial.println(moistureToString(analogValue));
  

  if (percentageValue >= 75) {
    digitalWrite(led12green, HIGH);
    digitalWrite(led11yellow, LOW);
    digitalWrite(led10red, LOW);
  } else if (percentageValue >= 50) {
    digitalWrite(led12green, LOW);
    digitalWrite(led11yellow, HIGH);
    digitalWrite(led10red, LOW);
  } else {
    digitalWrite(led12green, LOW);
    digitalWrite(led11yellow, LOW);
    digitalWrite(led10red, HIGH);
  }
  
  digitalWrite(sensorPower9, LOW); // turns off power of moisture sensor to increase its life time





  // TEMPERATURE AND HUMIDITY SENSOR ######################
  int chk = DHT21.read(DHT21PIN);         //reads sensor status
 
  Serial.print("DHT21 sensor status: ");
  switch (chk)
  {
    case DHTLIB_OK: 
        Serial.print("OK"); 
        break;
    case DHTLIB_ERROR_CHECKSUM: 
        Serial.println("ERROR checksum"); 
        break;
    case DHTLIB_ERROR_TIMEOUT: 
        Serial.println("ERROR timeout"); 
        break;
    default: 
        Serial.println("ERROR unknown"); 
        break;
  }
  Serial.print("  ");
  Serial.print("Humidity (%): ");
  Serial.print((float)DHT21.humidity, 2);
  Serial.print("  ");
  Serial.print("Temperature (C): ");
  Serial.println((float)DHT21.temperature, 2);



  
  delay(SLEEP_TIME);
}

int moisture(int sensorValue) {
  return (int)(100.0f * (float)sensorValue / (float)MAX_SENSOR_VALUE);
}

String moistureToString(int sensorValue) {
  String label = "Soil moisture: ";
  int valueInPercent = moisture(sensorValue);
  String percentChar = "%";
  String labelWithValue = label + valueInPercent + percentChar;

  return labelWithValue;
}
