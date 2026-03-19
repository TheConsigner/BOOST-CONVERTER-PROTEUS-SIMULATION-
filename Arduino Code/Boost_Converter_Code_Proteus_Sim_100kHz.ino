// Boost Converter Control - 100kHz
// Target: ATmega328P (Arduino Uno)

const int pwmPin = 3;       // PWM to MOSFET Gate
const int feedbackPin = A0;  // Voltage divider (10k/1k)
const int potPin = A1;       // Target Voltage Pot

// Control Variables
float targetVoltage = 0;
float currentVoltage = 0;
float lastTarget = -1.0;
float dutyCycle = 0;
float error = 0;
float integral = 0;

// PI Constants
float Kp = 0.4; 
float Ki = 0.04;

void setup() {
  pinMode(pwmPin, OUTPUT);
  Serial.begin(9600);
  
  // Wait for Serial to initialize
  delay(500);
  Serial.println("--- BOOST CONVERTER INITIALIZED ---");
  Serial.println("Frequency: 100kHz | Pin: 3");

  // --- Timer 2 Configuration for 100kHz ---
  TCCR2A = _BV(COM2B1) | _BV(WGM21) | _BV(WGM20); // Fast PWM, Top=OCR2A
  TCCR2B = _BV(WGM22) | _BV(CS20);                // Prescaler = 1
  
  OCR2A = 159;   // 16MHz / (1 * 100kHz) - 1
  OCR2B = 0;     // Start at 0% duty
}

void loop() {
  // 1. Target Voltage from Pot (Range: 12V to 35V)
  int potValue = analogRead(potPin);
  targetVoltage = map(potValue, 0, 1023, 120, 350) / 10.0;

  // 2. Output Voltage Feedback (1k/11k divider)
  int adcRaw = analogRead(feedbackPin);
  currentVoltage = adcRaw * (5.0 / 1024.0) * 11.0;

  // 3. PI Control Logic
  error = targetVoltage - currentVoltage;
  integral += error;
  integral = constrain(integral, -50, 50); // Prevent windup
  
  float adjustment = (Kp * error) + (Ki * integral);
  dutyCycle += adjustment;
  
  // Safe limit: Max 85% duty cycle (159 * 0.85 approx 135)
  dutyCycle = constrain(dutyCycle, 0, 135); 
  OCR2B = (int)dutyCycle;

  // 4. Update Terminal only if values change significantly
  if (abs(targetVoltage - lastTarget) > 0.2) {
    Serial.print("NEW TARGET SET: ");
    Serial.print(targetVoltage);
    Serial.print("V | Feedback: ");
    Serial.print(currentVoltage);
    Serial.print("V | Duty: ");
    Serial.print((dutyCycle / 159.0) * 100.0);
    Serial.println("%");
    
    lastTarget = targetVoltage; // Update reference
  }

  delay(20); // Small delay for ADC stability
}