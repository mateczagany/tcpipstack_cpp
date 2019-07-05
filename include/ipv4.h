#pragma once

#include <cstdint>
#include <memory>
#include <unordered_map>
#include <vector>

#include "packets.h"
#include "buffer.h"

#define IPV4_ADDRESS_LEN 4
#define IPV4_DEFAULT_TTL 64
#define IPV4_FLAG_DF 0x4000  // don't fragment
#define IPV4_FLAG_MF 0x2000 // more fragments

class Tap;
class Arp;
class Icmp;


class Ipv4 {
public:
    Ipv4(Tap &tap_device, Arp &arp_state, Icmp &icmp_state);

    void processIpv4Packet(EthernetFrame *frame);
    std::shared_ptr<Buffer> createPacket(uint32_t ip_destination, uint8_t ip_protocol, size_t size);
    void transmitPacket(const std::shared_ptr<Buffer>& buffer);
    void retryPendingPackets(uint32_t ip_destination);

private:
    Tap &m_tap_device;
    Arp &m_arp_state;
    Icmp &m_icmp_state;

    std::unordered_map<uint32_t, std::vector<std::shared_ptr<Buffer>>> m_pending_packets;
};