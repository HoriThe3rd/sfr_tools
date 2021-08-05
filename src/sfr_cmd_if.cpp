#include "sfr_cmd_if.hpp"

sfr_cmd_if::sfr_cmd_if() : maddr(0x00), mdata(0x00) {}

sfr_cmd_if::sfr_cmd_if(const unsigned char addr, const unsigned char data)
    : maddr(addr), mdata(data) {}

// Setter
void sfr_cmd_if::operator()(const unsigned char in_addr,
                            const unsigned char in_data) {
    maddr = in_addr;
    mdata = in_data;
}

// Getters
const unsigned char sfr_cmd_if::addr() const { return maddr; }
const unsigned char sfr_cmd_if::data() const { return mdata; }