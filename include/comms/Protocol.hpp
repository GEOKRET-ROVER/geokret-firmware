#pragma once

#include <cstdint>

namespace Packets
{

struct __attribute__((packed)) ScanPoint {
    uint16_t angle;
    uint16_t distCm;
    int16_t signal;
    uint32_t tMs;
};

struct __attribute__((packed)) Command {
    // ?? to be determined
    int16_t  left;
    int16_t  right;
    uint8_t  turretMode;
    int16_t  turretArg;
};

} // namespace Packets