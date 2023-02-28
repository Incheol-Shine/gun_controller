#include <EEPROM.h>

typedef struct  s_bias
{
    float   acc_bias[3];
    float   gyro_bias[3];
    float   mag_bias[3];
    float   mag_scale[3];
}   t_bias;

void setup()
{
    Serial.begin(115200);
    get_calib_data(0);
}
    
void get_calib_data(int location)
{
    t_bias  calib;

    EEPROM.get(location, calib);
    delay(1000);
    Serial.print("acc_bias = ");
    println_array(calib.acc_bias);
    Serial.print("gyro_bias = ");
    println_array(calib.gyro_bias);
    Serial.print("mag_bias = ");
    println_array(calib.mag_bias);
    Serial.print("mag_scale = ");
    println_array(calib.mag_scale);
}

void println_array(float  data[])
{
    for (int i = 0; i < 3; i++)
    {
        Serial.print(data[i]);
        Serial.print(" ");
    }
    Serial.println();
}

void loop()
{
    
}
