// Standby pin is used to turn on and off the motor driver
const int STBY = 3;
// PWM Channel A and B are used to control the speed of the motors
const int PWMA = 5;
const int PWMB = 6;
// Input Channels A and B are used to control the direction of the motors
const int AIN1 = 7;
const int BIN1 = 8;

// Line Tracker Sensor Pins
const int LTleftSensor = A2;
const int LTmiddleSensor = A1;
const int LTrightSensor = A0;

/**
 * @brief Moves the robot forward with the given speed
 *
 * @param carSpeed an integer representing the car's speed.
 * cap at 255
 */
void forward(int carSpeed) {
    // Enable the motor driver
    digitalWrite(STBY, HIGH);
    // Set the direction of the motors
    digitalWrite(AIN1, HIGH);
    digitalWrite(BIN1, HIGH);

    // Write speed to 'A' and 'B' MotorGroups
    analogWrite(PWMA, carSpeed);
    analogWrite(PWMB, carSpeed);
}

/**
 * @brief Moves the robot backwards with the given speed
 *
 * @param carSpeed an integer representing the car's speed.
 * cap at 255
 */
void back(int carSpeed) {
    digitalWrite(STBY, HIGH);
    digitalWrite(AIN1, LOW);
    digitalWrite(BIN1, LOW);
    analogWrite(PWMA, carSpeed);
    analogWrite(PWMB, carSpeed);
}

/**
 * @brief Turns the robot left with the given speed
 *
 * @param carSpeed an integer representing the car's speed.
 * cap at 255
 */
void turnLeft(int carSpeed) {
    digitalWrite(STBY, HIGH);
    digitalWrite(AIN1, HIGH);
    digitalWrite(BIN1, LOW);
    analogWrite(PWMA, carSpeed);
    analogWrite(PWMB, carSpeed);
}

/**
 * @brief Turns the robot right with the given speed
 *
 * @param carSpeed an integer representing the car's speed.
 * cap at 255
 */
void turnRight(int carSpeed) {
    digitalWrite(STBY, HIGH);
    digitalWrite(AIN1, LOW);
    digitalWrite(BIN1, HIGH);
    analogWrite(PWMA, carSpeed);
    analogWrite(PWMB, carSpeed);
}

/**
 * @brief Stops the robot's drive motors.
 */
void stop() {
    digitalWrite(STBY, LOW);
}

void setup() {
    // Configure all of these pins as outputs
    pinMode(STBY, OUTPUT);
    pinMode(PWMA, OUTPUT);
    pinMode(PWMB, OUTPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(BIN1, OUTPUT);

    // Start serial monitor
    Serial.begin(9600);
}

// Track and follow a dark line
void loop() {
    int threshold = 250;
    if (analogRead(LTleftSensor) > threshold && analogRead(LTrightSensor) > threshold && analogRead(LTmiddleSensor) > threshold ) {
        stop();
        forward(40);
        /*
        turnRight(45);
        delay(500);
        forward(40);
        delay(250);
        */
        
        Serial.println("Should be moving");
        Serial.println("111");
    }
    
    if (analogRead(LTleftSensor) < threshold && analogRead(LTrightSensor) > threshold && analogRead(LTmiddleSensor) > threshold ) {
        stop();
        turnRight(45);
        
        Serial.println("Should be R turning");
        Serial.println("011");
    }
    
    if (analogRead(LTleftSensor) < threshold && analogRead(LTrightSensor) > threshold && analogRead(LTmiddleSensor) < threshold ) {
        stop();
        turnRight(45);
       
        Serial.println("Should be R turning");
        Serial.println("001");
    }
    
    if (analogRead(LTleftSensor) > threshold && analogRead(LTrightSensor) < threshold && analogRead(LTmiddleSensor) > threshold ) {
        stop();
        turnLeft(45);
        
        Serial.println("Should be L turning");
        Serial.println("110");
    }
    
    if (analogRead(LTleftSensor) > threshold && analogRead(LTrightSensor) < threshold && analogRead(LTmiddleSensor) < threshold ) {
        stop();
        turnLeft(45);
        Serial.println("Should be L turning");
        Serial.println("100");
    }
    if (analogRead(LTleftSensor) < threshold && analogRead(LTrightSensor) < threshold && analogRead(LTmiddleSensor) > threshold ) {
        forward(50);
        
        Serial.println("Should be moving");
        Serial.println("010");
    }
    if (analogRead(LTleftSensor) < threshold && analogRead(LTrightSensor) < threshold && analogRead(LTmiddleSensor) < threshold ) {
        // Car has gone off the track (most likely 90degree turn) (Should work for other conditions)
        
        stop();
        //Move forward to enable sensor time to lock on line
        forward(40);
        delay(25);
        //Turn until middle sensor detects line
        while (analogRead(LTmiddleSensor) < threshold)
        {
          turnRight(45);
          delay(15);
          stop();
        }
        forward(40);
        delay(25);
        stop();
        
        
        Serial.println("Should NOT");
    }
}