#pragma once

#include "ILink.hpp"
#include "Protocol.hpp"

class HostComm
{
public: // CONFIGURABLE CONSTANS
    static constexpr std::size_t MAX_POINTS = 20;
    static constexpr std::size_t SCANPOINT_SIZE = sizeof(Packets::ScanPoint);
    static constexpr std::size_t HEADER_SIZE = sizeof(Packets::Header);
    static constexpr std::size_t MAX_SCAN_BUFFER_SIZE = HEADER_SIZE + MAX_POINTS * SCANPOINT_SIZE;
public:
    explicit HostComm(ILink& link_);
    void begin();
    void update();
    void queueScan(const Packets::ScanPoint& packet);
private:
    void flushScan();

    ILink& link;
    uint8_t scanBuf[MAX_SCAN_BUFFER_SIZE];
    std::size_t scanCount = 0;
    uint16_t scanSeq = 0;
};