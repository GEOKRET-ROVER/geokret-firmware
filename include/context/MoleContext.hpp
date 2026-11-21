#pragma once

#include "GamePadInput.hpp"
#include "ProximitySensor.hpp"
#include "HallSensor.hpp"

struct MoleContext 
{
    GamePadInput pad;
    ProximitySensor prox;
    HallSensor hall;
    void begin() {
        prox.begin();
        hall.begin();
    }
    void updatePad(ControllerPtr ctl) {
        pad.processData(ctl);
    }
    bool updateSensors() {
        return prox.updateData();
    }
    void printData() const {
        pad.printData();
    }
};