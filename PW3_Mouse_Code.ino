const int leftSensorPin = A0;
const int rightSensorPin = A1;

const int leftMotorPin = 5;
const int rightMotorPin = 6;

int baseSpeed = 180;          // normal straight-line speed
int minSpeed = 100;           // lowest speed allowed in sharp turns
float steeringGain = 0.4;     // how strongly sensor difference affects steering
float speedReductionGain = 0.2; // how strongly turning demand reduces speed

void setup() {
  pinMode(leftMotorPin, OUTPUT);
  pinMode(rightMotorPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int leftSensor = analogRead(leftSensorPin);
  int rightSensor = analogRead(rightSensorPin);

  // Difference between sensors determines steering demand
  int error = leftSensor - rightSensor;

  // Turning demand is the size of the error
  int turnDemand = abs(error);

  // Reduce speed when turning demand is high
  int adjustedBaseSpeed = baseSpeed - (int)(speedReductionGain * turnDemand);

  // Prevent speed dropping too low
  if (adjustedBaseSpeed < minSpeed) {
    adjustedBaseSpeed = minSpeed;
  }

  // Steering correction
  int correction = (int)(steeringGain * error);

  // Motor speed commands
  int leftMotorSpeed = adjustedBaseSpeed - correction;
  int rightMotorSpeed = adjustedBaseSpeed + correction;

  // Constrain outputs to valid PWM range
  leftMotorSpeed = constrain(leftMotorSpeed, 0, 255);
  rightMotorSpeed = constrain(rightMotorSpeed, 0, 255);

  analogWrite(leftMotorPin, leftMotorSpeed);
  analogWrite(rightMotorPin, rightMotorSpeed);

  // Debug output
  Serial.print("Left: ");
  Serial.print(leftSensor);
  Serial.print(" Right: ");
  Serial.print(rightSensor);
  Serial.print(" Error: ");
  Serial.print(error);
  Serial.print(" Base speed: ");
  Serial.print(adjustedBaseSpeed);
  Serial.print(" Left motor: ");
  Serial.print(leftMotorSpeed);
  Serial.print(" Right motor: ");
  Serial.println(rightMotorSpeed);

  delay(50);
}

int error = leftSensor - rightSensor;
int turnDemand = abs(error);

// Reduce speed when turning sharply
int adjustedBaseSpeed = baseSpeed - (0.2 * turnDemand);

if (adjustedBaseSpeed < 100) {
  adjustedBaseSpeed = 100;
}
