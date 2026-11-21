#include <cstring>

#include "HostComm.hpp"

HostComm::HostComm(ILink& link_) : link{link_}
{

}

void HostComm::begin()
{
    link.begin();
}

void HostComm::update()
{
    if (!link.isUp()) {
        scanCount = 0;
        return;
    }
    if (scanCount < MAX_POINTS) {
        return;
    }
    flushScan();
}

void HostComm::queueScan(const Packets::ScanPoint& packet)
{
    if (scanCount >= MAX_POINTS) {
        return;
    }
    //scanBuf[scanCount * scanPointSize] = packet;
    std::memcpy(
        scanBuf + HEADER_SIZE + scanCount * SCANPOINT_SIZE,
        &packet,
        SCANPOINT_SIZE
    );
    ++scanCount;
}

void HostComm::flushScan()
{
    if (!link.isUp()) {
        return;
    }
    if (scanCount == 0) {
        return;
    }
    Packets::Header header{
        Packets::VERSION,
        Packets::Type::Scan,
        scanSeq++
    };
    std::memcpy(scanBuf, &header, sizeof(header));
    link.send(scanBuf, HEADER_SIZE + scanCount * SCANPOINT_SIZE);
    scanCount = 0;
}