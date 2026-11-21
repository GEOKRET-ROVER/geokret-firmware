#include "ProximitySensor.hpp"
#include "Config.hpp"

void ProximitySensor::begin()
{
    Wire.begin(Pins::LIDAR_1D.SDA, Pins::LIDAR_1D.SCL);
    Wire.setClock(400000);
    Wire.setTimeOut(5);
}

bool ProximitySensor::updateData()
{
    int16_t rawDistCm, rawSignal, rawTempHundreths;
    bool success = lidar.getData(rawDistCm, rawSignal, rawTempHundreths, I2C_ADDR);
    if (!success) {
        return false;
    }
    distance = rawDistCm;
    // NOTE it converts -1 to 65335, this number should be handled explicitely someday xD
    signal = rawSignal;
    temperature = static_cast<float>(rawTempHundreths) / 100.0;
    distance = (signal < MIN_SIGNAL) ? MAX_DISTANCE : rawDistCm;
    return true;
}