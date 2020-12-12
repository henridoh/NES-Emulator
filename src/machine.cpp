#include <iostream>
#include <fstream>
#include "processor/cpu.hpp"
#include "cartridge/cartridge.hpp"

#define RAM_SIZE 0x800
#define IO_PPU_REG_SIZE 0x8
#define IO_REGS_SIZE 0x020
#define EXPANSION_SIZE 0x1fe0

class Machine{
  private:
  CPU cpu;
  Cartridge cartridge;

  struct{
    // main memory
    byte * ram;
    byte * io_ppu_regs;
    byte * io_regs;
    byte * expansion;
    byte * sram; 
    byte * lower_prg;
    byte * upper_prg;

    // cartridge:
    byte * chr_rom;
  } memory_arrays;

  public:
  Memory * memory;

  Machine(){
    cpu = CPU();

    cartridge = Cartridge("test.nes");


    // load memory from cartridge
    memory_arrays.chr_rom = cartridge.get_chr_bank();
    

    memory_arrays.sram = cartridge.get_sram_bank();
    memory_arrays.lower_prg = cartridge.get_prg_banks(0);
    memory_arrays.upper_prg = cartridge.get_prg_banks(1);
    
    memory_arrays.ram = new byte[RAM_SIZE]{0};
    memory_arrays.io_ppu_regs = new byte[IO_PPU_REG_SIZE]{0};
    memory_arrays.io_regs = new byte[IO_REGS_SIZE]{0};

    // TODO: implement expansion as Cartridge memory
    memory_arrays.expansion = new byte[EXPANSION_SIZE]{0};


    memory = &cpu.memory;
    // ram mirrors (repeats 4 times)
    cpu.memory.add_mirrored_banks(memory_arrays.ram, RAM_SIZE, 4);
    // ppu reg mirrors (repeats 1024 times)
    cpu.memory.add_mirrored_banks(memory_arrays.io_ppu_regs, IO_PPU_REG_SIZE, 1024);
    cpu.memory.add_bank(memory_arrays.io_regs, IO_REGS_SIZE);

    // cartridge memory
    cpu.memory.add_bank(memory_arrays.expansion, EXPANSION_SIZE);
    cpu.memory.add_bank(memory_arrays.sram, SRAM_SIZE);
    cpu.memory.add_bank(memory_arrays.lower_prg, PRG_SIZE);
    cpu.memory.add_bank(memory_arrays.upper_prg, PRG_SIZE);

    for(int i = 0x8000; i < 0x8000+0x10; i++){
      std::cout << " 0x" << std::hex << (int)cartridge.get_prg_banks(0)[i];
    } std::cout << std::endl;

  }

  void debug_run(){
    while (1){
      //std::system("clear");
      cpu.log_current_state();
      cpu.log_hex_dump(0x100, 0x200);
      cpu.log_hex_dump(0x8000, 0x8100);
      cpu.run(1);
      std::getchar();
    }
  }
};

int main(){
  Machine machine = Machine();

  /* sample program:
   * LDA #0
   * l:
   * ADC #1
   * JMP l
   */
  // byte data[] = {0xa5, 0x00, 0x69, 0x01, 0x4c, 0x02, 0x06};
  // machine.memory->insert(0x8000, data, sizeof(data));

  machine.debug_run();
}