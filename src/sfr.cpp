#include "sfr.hpp"
#include <unistd.h>
#include <iostream>
#include <string>  // for debug.

sfr::sfr(xillybus8* xillybus_p) {
    // Save the given pointers to xillybus Rx/Tx.
    xillybus = xillybus_p;
}

void sfr::write(const unsigned char addr, const unsigned char data,
                const bool execute) {
    unsigned char rwmode_address = to_write_mode(addr);
    xillybus->xillybus_write(rwmode_address);

    if (execute)
        xillybus->xillybus_write(enable_execute_bit(data));
    else
        xillybus->xillybus_write(data);
}

void sfr::write(const sfr_cmd_if cmd, const bool execute) {
    unsigned char rwmode_address = to_write_mode(cmd.addr());
    xillybus->xillybus_write(rwmode_address);

    if (execute)
        xillybus->xillybus_write(enable_execute_bit(cmd.data()));
    else
        xillybus->xillybus_write(cmd.data());
}

const unsigned char sfr::read(const unsigned char addr) {
    xillybus->xillybus_write(addr);
    return xillybus->xillybus_read();
}

// Wait for finish the FPGA process.
void sfr::wait_exec_done() {
    unsigned char addr = 0x00;
    unsigned int status = 0x01;
    int timeout_counter = 0;
    const int timeout_deadline = 1000;
    while (status == 0x01) {
        xillybus->xillybus_write(addr);
        status = (unsigned int)(xillybus->xillybus_read());
        status = status & 0x00000001;  // Extract execution bit.
        usleep(50);
        if (timeout_counter++ == timeout_deadline) {
            std::cout << "SFR_timeout: wait_exec_done" << std::endl;
            abort();
        }
    }
}

unsigned char sfr::to_write_mode(unsigned char addr) {
    // Check the address range.
    if (addr > 0x7f) {
        std::cout << "Given SFR address is out of range, too big." << std::endl;
        std::exit(1);
    }
    return addr | 0x80;  // Assert the MSB to one.
}

// 1 bit shift and assert LSB.
// <data: 7 bits>, <exec bit: 1 bit>
const unsigned char sfr::enable_execute_bit(unsigned char in) const {
    return (in << 1) + 1;
}