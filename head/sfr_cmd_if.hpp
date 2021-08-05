// Interface object to communicate between SFR class and commands class.
#pragma once

class sfr_cmd_if {
   public:
    sfr_cmd_if();
    sfr_cmd_if(const unsigned char addr, const unsigned char data);
    void operator()(const unsigned char addr, const unsigned char data);
    const unsigned char addr() const;
    const unsigned char data() const;

   private:
    unsigned char maddr;
    unsigned char mdata;
};