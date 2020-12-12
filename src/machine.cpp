#include <iostream>
#include "processor/cpu.hpp"

int main(){
  CPU cpu = CPU();
  Memory memory = Memory();
  memory.add_bank(new byte[0x10000], 0x10000);
  byte data[] = {0xa5, 0x00, 0x69, 0x01, 0x4c, 0x02, 0x06};
  memory.insert(0x600, data, sizeof(data));
  cpu.memory = memory;
   while (1){
    std::system("clear");
    cpu.log_current_state();
    cpu.log_hex_dump(0x100, 0x200);
    cpu.log_hex_dump(0x600, 0x700);
    cpu.run(1);
    std::getchar();
  }
}