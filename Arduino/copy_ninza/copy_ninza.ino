#include "MPU9250.h"
#include "eeprom_utils.h"
#include <math.h>

/* Set the delay between fresh samples */
// #define BNO055_SAMPLERATE_DELAY_MS (10)

#define DEG_2_RAD       0.01745329251994329576923690768489
#define IMU_DELAY_MS    1
#define FRAME_MAX_SIZE  30
#define DEAD_ZONE       0
// ===================== 코드에서 사용할 전역 변수 값들 =====
// 가속도의 무시를 위한 데드존

// ========================================================

MPU9250 mpu;
const int buttonPin = 7;

void setup(void)
{
    pinMode(buttonPin, INPUT);
    Serial.begin(115200);
    Wire.begin();
    delay(2000);

    mpu.setMagneticDeclination(-8.53);
//    mpu.selectFilter(QuatFilterSel::MAHONY);
    // mpu.setFilterIterations(5);

    if (!mpu.setup(0x68)) {  // change to your own address
        while (1) {
            Serial.println("MPU connection failed. Please check your connection with `connection_check` example.");
            delay(5000);
        }
    }

#if defined(ESP_PLATFORM) || defined(ESP8266)
    EEPROM.begin(0x80);
#endif
    // load from eeprom
    loadCalibration();
}

void loop(void)
{
  // Possible vector values can be:
  // - VECTOR_ACCELEROMETER - m/s^2
  // - VECTOR_MAGNETOMETER  - uT
  // - VECTOR_GYROSCOPE     - rad/s
  // - VECTOR_EULER         - degrees
  // - VECTOR_LINEARACCEL   - m/s^2
  // - VECTOR_GRAVITY       - m/s^2

    if (mpu.update()) {
        static uint32_t prev_ms = millis();
        if (millis() > prev_ms + 1) {
            test_mouse();
            prev_ms = millis();
        }
    }
}

void test_mouse(){
    float eulerX = mpu.getEulerX();
    float gyroX = mpu.getGyroZ();
    float gyroY = mpu.getGyroY();


    float c = cos(eulerX * DEG_2_RAD);
    float s = sin(eulerX * DEG_2_RAD);
    float newGyroX = gyroX * c + gyroY * s;
    float newGyroY = gyroX * -s + gyroY * c;

    int mouse_x = (int)(newGyroX * -100);
    int mouse_y = (int)(newGyroY * 100);
    int button = digitalRead(buttonPin);
;
    char buffer[FRAME_MAX_SIZE];

    // 각속도 테스트용 출력 부분
    // Serial.print("newGyroX:");
//  Serial.println(mouse_x);
//  // Serial.print(" newGyroY:");
//  Serial.println(mouse_y);

    sprintf(buffer, "%d %d %d", mouse_x, mouse_y, button);
    Serial.println(buffer);
}


//void test_mouse(){
//    char euler_x[8];
//    char euler_y[8];
//    char euler_z[8];
//    char buffer[FRAME_MAX_SIZE];
//
//    dtostrf(mpu.getEulerX(), -1, 2, euler_x);
//    dtostrf(mpu.getEulerY(), -1, 2, euler_y);
//    dtostrf(mpu.getEulerZ(), -1, 2, euler_z);
//    sprintf(buffer, "%s %s %s", euler_x, euler_y, euler_z);
//    Serial.println(buffer);
//}
