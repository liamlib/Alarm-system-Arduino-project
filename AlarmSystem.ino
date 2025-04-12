#include <Keypad.h>

// Segment pins: A, B, C, D, E, F, G, DP
const int segmentPins[8] = {22, 24, 26, 28, 30, 32, 34, 36}; // 7-segment + DP

// Keypad configuration
const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins,
ROWS, COLS);

// Sensor & Buzzer
const int TRIG_PIN = 10;
const int ECHO_PIN = 11;
const int BUZZER_PIN = 12;

// Password
const int pass_array[4] = {1, 2, 3, 4};
const int SIZE = sizeof(pass_array) / sizeof(pass_array[0]);
int user_input_array[4] = {0};
int passw_index = 0;

// Alarm system state
float distance = 999;
bool is_sensor_active = false;
bool alarm_triggered = false;
unsigned long lastKeypadCheck = 0;
unsigned long lastSensorCheck = 0;

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Set all segment pins as outputs
  for (int i = 0; i < 8; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }

  Serial.println("🔒 Security System Ready!");
  show0(); // Show 0 on startup
}

void loop() {
  delay(5);
  if (millis() - lastKeypadCheck > 50) {
    lastKeypadCheck = millis();
    char customKey = customKeypad.getKey();

    if (customKey) {
      Serial.print("Key Pressed: ");
      Serial.println(customKey);

      // Show the number on the 7-segment display
      if (customKey >= '0' && customKey <= '9') {
        showNumber(customKey - '0');
        user_input_array[passw_index] = customKey - '0';
        passw_index++;
      }

      if (passw_index == SIZE) {
        if (checkPassword(user_input_array, SIZE)) {
          if (is_sensor_active) {
            Serial.println("🔴 Deactivating Alarm...");
            is_sensor_active = false;
            alarm_triggered = false;
            digitalWrite(BUZZER_PIN, LOW);
            showF(); // D = Deactivate → showF
          } else {
            Serial.println("🟢 Activating Alarm...");
            is_sensor_active = true;
            alarm_triggered = false;
            digitalWrite(BUZZER_PIN, LOW);
            Serial.println("Sensor active! Monitoring...");
            showA(); // A = Activate → showA
          }
        }
        passw_index = 0;
        delay(1500);
      }
    }
  }

  // Sensor logic
  if (is_sensor_active && millis() - lastSensorCheck > 300) {
    lastSensorCheck = millis();

    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(5);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH, 50000); // wait for echo (max 50ms)

    if (duration > 0) {
      distance = (duration * 0.0343) / 2.0;
      Serial.print("📏 Distance: ");
      Serial.print(distance);
      Serial.println(" cm");
    } else {
      Serial.println("⚠️ No echo received (duration = 0)");
    }


    if (!alarm_triggered && distance > 0 && distance < 20) {
      alarm_triggered = true;
      Serial.println("🚨 ALARM TRIGGERED");
      digitalWrite(BUZZER_PIN, HIGH);
    }
  }

  if (!is_sensor_active) {
    alarm_triggered = false;
    digitalWrite(BUZZER_PIN, LOW);
  }
}

bool checkPassword(int userInput[], int size) {
  if (size != SIZE) return false;
  for (int i = 0; i < size; i++) {
    if (userInput[i] != pass_array[i]) {
      Serial.println("❌ Wrong password. Try again!");
      showH(); // Error
      delay(2000);
      return false;
    }
  }
  Serial.println("✅ Password Correct!");
  delay(1000);
  return true;
}

// Show number on display

void showNumber(int num) {
  switch (num) {
    case 0: show0(); break;
    case 1: show1(); break;
    case 2: show2(); break;
    case 3: show3(); break;
    case 4: show4(); break;
    case 5: show5(); break;
    case 6: show6(); break;
    case 7: show7(); break;
    case 8: show8(); break;
    case 9: show9(); break;
  }
}
// Segment display functions
void show7() {
  digitalWrite(segmentPins[0], HIGH);  // A
  digitalWrite(segmentPins[1], LOW);  // B
  digitalWrite(segmentPins[2], HIGH);  // C
  digitalWrite(segmentPins[3], HIGH);  // D
  digitalWrite(segmentPins[4], LOW);  // E
  digitalWrite(segmentPins[5], LOW);  // F
  digitalWrite(segmentPins[6], HIGH); // G
  digitalWrite(segmentPins[7], LOW); // DP
  digitalWrite(segmentPins[8], LOW);  // F
  digitalWrite(segmentPins[9], HIGH); // G
  digitalWrite(segmentPins[10], LOW); // DP

}

void show4() {
  digitalWrite(segmentPins[0], HIGH);
  digitalWrite(segmentPins[1], LOW);
  digitalWrite(segmentPins[2], LOW);
  digitalWrite(segmentPins[3], HIGH);
  digitalWrite(segmentPins[4], HIGH);
  digitalWrite(segmentPins[5], LOW);
  digitalWrite(segmentPins[6], HIGH);
  digitalWrite(segmentPins[7], LOW);
}

void show5() {
  digitalWrite(segmentPins[0], HIGH);
  digitalWrite(segmentPins[1], LOW);
  digitalWrite(segmentPins[2], HIGH);
  digitalWrite(segmentPins[3], LOW);
  digitalWrite(segmentPins[4], HIGH);
  digitalWrite(segmentPins[5], HIGH);
  digitalWrite(segmentPins[6], HIGH);
  digitalWrite(segmentPins[7], LOW);
  digitalWrite(segmentPins[8], HIGH);  
  digitalWrite(segmentPins[9], HIGH); 
  digitalWrite(segmentPins[10], HIGH); 
 
}

void show3() {
  digitalWrite(segmentPins[0], LOW);
  digitalWrite(segmentPins[1], LOW);
  digitalWrite(segmentPins[2], HIGH);
  digitalWrite(segmentPins[3], HIGH);
  digitalWrite(segmentPins[4], HIGH);
  digitalWrite(segmentPins[5], HIGH);
  digitalWrite(segmentPins[6], HIGH);
  digitalWrite(segmentPins[7], LOW);
}

void show9() {
  digitalWrite(segmentPins[0], HIGH);
  digitalWrite(segmentPins[1], LOW);
  digitalWrite(segmentPins[2], HIGH);
  digitalWrite(segmentPins[3], HIGH);
  digitalWrite(segmentPins[4], HIGH);
  digitalWrite(segmentPins[5], LOW);
  digitalWrite(segmentPins[6], HIGH);
  digitalWrite(segmentPins[7], LOW);
}

void show1() {
  digitalWrite(segmentPins[0], LOW);
  digitalWrite(segmentPins[1], LOW);
  digitalWrite(segmentPins[2], LOW);
  digitalWrite(segmentPins[3], HIGH);
  digitalWrite(segmentPins[4], LOW);
  digitalWrite(segmentPins[5], LOW);
  digitalWrite(segmentPins[6], HIGH);
  digitalWrite(segmentPins[7], LOW);
}

void show8() {
  digitalWrite(segmentPins[0], HIGH);
  digitalWrite(segmentPins[1], LOW);
  digitalWrite(segmentPins[2], HIGH);
  digitalWrite(segmentPins[3], HIGH);
  digitalWrite(segmentPins[4], HIGH);
  digitalWrite(segmentPins[5], HIGH);
  digitalWrite(segmentPins[6], HIGH);
  digitalWrite(segmentPins[7], HIGH);
}

void show0() {
  digitalWrite(segmentPins[0], HIGH);
  digitalWrite(segmentPins[1], LOW);
  digitalWrite(segmentPins[2], HIGH);
  digitalWrite(segmentPins[3], HIGH);
  digitalWrite(segmentPins[4], LOW);
  digitalWrite(segmentPins[5], HIGH);
  digitalWrite(segmentPins[6], HIGH);
  digitalWrite(segmentPins[7], HIGH);
}

void show6() {
  digitalWrite(segmentPins[0], HIGH);
  digitalWrite(segmentPins[1], LOW);
  digitalWrite(segmentPins[2], HIGH);
  digitalWrite(segmentPins[3], LOW);
  digitalWrite(segmentPins[4], HIGH);
  digitalWrite(segmentPins[5], HIGH);
  digitalWrite(segmentPins[6], HIGH);
  digitalWrite(segmentPins[7], HIGH);
}

void show2() {
  digitalWrite(segmentPins[0], LOW);
  digitalWrite(segmentPins[1], LOW);
  digitalWrite(segmentPins[2], HIGH);
  digitalWrite(segmentPins[3], HIGH);
  digitalWrite(segmentPins[4], HIGH);
  digitalWrite(segmentPins[5], HIGH);
  digitalWrite(segmentPins[6], LOW);
  digitalWrite(segmentPins[7], HIGH);
}

void showA() {
  digitalWrite(segmentPins[0], HIGH);
  digitalWrite(segmentPins[1], LOW);
  digitalWrite(segmentPins[2], HIGH);
  digitalWrite(segmentPins[3], HIGH);
  digitalWrite(segmentPins[4], HIGH);
  digitalWrite(segmentPins[5], LOW);
  digitalWrite(segmentPins[6], HIGH);
  digitalWrite(segmentPins[7], HIGH);
}
void showE() {
  digitalWrite(segmentPins[0], HIGH);
  digitalWrite(segmentPins[1], LOW);
  digitalWrite(segmentPins[2], HIGH);
  digitalWrite(segmentPins[3], LOW);
  digitalWrite(segmentPins[4], HIGH);
  digitalWrite(segmentPins[5], HIGH);
  digitalWrite(segmentPins[6], LOW);
  digitalWrite(segmentPins[7], HIGH);
}
void showF() {
  digitalWrite(segmentPins[0], HIGH);
  digitalWrite(segmentPins[1], LOW);
  digitalWrite(segmentPins[2], HIGH);
  digitalWrite(segmentPins[3], LOW);
  digitalWrite(segmentPins[4], HIGH);
  digitalWrite(segmentPins[5], LOW);
  digitalWrite(segmentPins[6], LOW);
  digitalWrite(segmentPins[7], HIGH);
}

void showH() {
  digitalWrite(segmentPins[0], HIGH);
  digitalWrite(segmentPins[1], LOW);
  digitalWrite(segmentPins[2], LOW);
  digitalWrite(segmentPins[3], HIGH);
  digitalWrite(segmentPins[4], HIGH);
  digitalWrite(segmentPins[5], LOW);
  digitalWrite(segmentPins[6], HIGH);
  digitalWrite(segmentPins[7], HIGH);
}
