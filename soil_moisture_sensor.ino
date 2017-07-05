#define A0  A0
int led12 = 12;
int led11 = 11;
int led10 = 10;

int analogValue = 0;
int percentageValue = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(led12, OUTPUT);
  pinMode(led11, OUTPUT);
  pinMode(led10, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  analogValue = analogRead(A0);
  
//  Serial.println( 1023 - analogRead(A0));

  Serial.println(moistureToString(analogValue));
  
  percentageValue = moisture(analogValue);

  if (percentageValue >= 60) {
    digitalWrite(led12, HIGH);
    digitalWrite(led11, LOW);
    digitalWrite(led10, LOW);
  } else if (percentageValue >= 40) {
    digitalWrite(led12, LOW);
    digitalWrite(led11, HIGH);
    digitalWrite(led10, LOW);
  } else {
    digitalWrite(led12, LOW);
    digitalWrite(led11, LOW);
    digitalWrite(led10, HIGH);
  }
  
  delay(1000);
}

int moisture(int sensorValue) {
  return (1023 - sensorValue) / 10;
}

String moistureToString(int sensorValue) {
  String label = "Wilgotnosc gleby: ";
  int valueInPercent = moisture(sensorValue);
  String percentChar = "%";
  String labelWithValue = label + valueInPercent + percentChar;

  return labelWithValue;
}

