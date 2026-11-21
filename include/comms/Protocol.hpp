#pragma once

#include <cstdint>

namespace Packets
{
// used for the verification with upper layer
constexpr uint8_t VERSION = 1; 

enum class Type : uint8_t
{
    Scan = 1,
    Command = 2,
};

struct __attribute__((packed)) Header {
    uint8_t version;
    Type type;
    uint16_t seq;
};

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

static_assert(sizeof(Header)    == 4,  "Header size is incorrect");
static_assert(sizeof(ScanPoint) == 10, "ScanPoint size is incorrect");

} // namespace Packets