#include "MPU9250.h"
#include "eeprom_utils.h"

# define DEADZONE 7
MPU9250 mpu;

void setup() {
    Serial.begin(115200);
    Wire.begin();
    delay(2000);

    mpu.setMagneticDeclination(-8.53);
//    mpu.selectFilter(QuatFilterSel::MAHONY);
    mpu.setFilterIterations(5);

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

void loop() {
    if (mpu.update()) {
        static uint32_t prev_ms = millis();
        if (millis() > prev_ms + 25) {
//            if (is_move())
            print_euler();
//            print_quaternion();
            prev_ms = millis();
        }
    }
}

void print_roll_pitch_yaw() {
    // Serial.print("Yaw, Pitch, Roll: ");
    Serial.print(mpu.getYaw(), 2);
    Serial.print(mpu.getPitch(), 2);
    Serial.println(mpu.getRoll(), 2);
}

//void print_euler() {
//    char buf[8];
//    dtostrf(mpu.getEulerX(), 7, 2, buf);
//    Serial.println(buf);
//    dtostrf(mpu.getGyroY(), 7, 2, buf);
//    Serial.println(buf);
//    dtostrf(mpu.getGyroZ() * -1, 7, 2, buf);
//    Serial.println(buf);
//}

int is_move() {
    int temp;
    temp = fabs(mpu.getGyroX()) + fabs(mpu.getGyroY()) + fabs(mpu.getGyroZ());
//    Serial.println(temp);
    if (temp > DEADZONE)
        return 1;
    else
        return 0;
}

//void print_euler() {
//    Serial.println(mpu.getEulerX()/2, 2);
//    Serial.println(mpu.getEulerY()/2, 2);
//    Serial.println(mpu.getEulerZ()/2, 2);
//}

void print_euler() {
    Serial.print("Euler x, y, z : ");
//    Serial.print(mpu.getEulerX(), 2);
//    Serial.print(", ");
//    Serial.print(mpu.getEulerY(), 2);
//    Serial.print(", ");
//    Serial.print(mpu.getEulerZ(), 2);
//    Serial.print(", ");
    Serial.print(mpu.getRoll(), 2);
    Serial.print(", ");
    Serial.print(mpu.getPitch(), 2);
    Serial.print(", ");
    Serial.print(mpu.getYaw(), 2);
    Serial.println();
}


void print_quaternion() {
    Serial.print("Quaternion x, y, z : ");
    Serial.print(mpu.getQuaternionX(), 2);
    Serial.print(", ");
    Serial.print(mpu.getQuaternionY(), 2);
    Serial.print(", ");
    Serial.print(mpu.getQuaternionZ(), 2);
    Serial.println();
}
