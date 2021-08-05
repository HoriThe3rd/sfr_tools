#pragma once
#include "sfr_cmd_if.hpp"
#include "xillybus.hpp"

class sfr {
   public:
    sfr(xillybus8* xillybs_p);
    void write(const unsigned char addr, const unsigned char data,
               const bool execute);
    void write(const sfr_cmd_if cmd, const bool execute);
    const unsigned char read(const unsigned char addr);
    void wait_exec_done();

   private:
    xillybus8* xillybus;
    unsigned char to_write_mode(unsigned char addr);
    const unsigned char enable_execute_bit(unsigned char in) const;
};