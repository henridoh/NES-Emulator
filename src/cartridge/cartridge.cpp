#include "../datatypes.hpp"
using namespace data_types;

#include "cartridge.hpp"
#include <fstream>
#include <string>
#include <vector>

Cartridge::Cartridge(){ 
  // empty cartridge
  byte * prg_ram = new byte[PRG_SIZE];
  prg_banks.push_back(prg_ram);
  prg_banks.push_back(prg_ram);

  byte * chr_ram = new byte[CHR_SIZE];
  prg_banks.push_back(prg_ram);

  sram_banks.push_back(new byte[SRAM_SIZE]);
}

Cartridge::Cartridge(std::string filename){
  std::ifstream file("./test.nes", std::ios::binary);
  std::vector<byte> buffer(std::istreambuf_iterator<char>(file), {});


  int n_prg = buffer[4];
  int n_chr = buffer[5];
  int n_ram = buffer[8];
  n_ram |= n_ram ? 1 : 0;

  rom_control |= buffer[6];
  bool has_trainer = rom_control & 4;
  rom_control = (rom_control << 8) | buffer[7];

  int a_start = has_trainer ? 512 + 16 : 16;
  if (n_prg == 1){
    prg_banks.push_back(&buffer[a_start]);
    prg_banks.push_back(&buffer[a_start]);
  } else {
    for(int i=0; i < n_prg; i++){
      prg_banks.push_back(&buffer[a_start + i * PRG_SIZE]);
    }
  }

  a_start += n_prg * PRG_SIZE;

  for(int i=0; i < n_chr; i++){
    chr_banks.push_back(&buffer[a_start + i * CHR_SIZE]);
  }
  sram_banks.push_back(new byte[SRAM_SIZE]);
}


byte * Cartridge::get_prg_banks(int bank){
  return prg_banks[bank];
}
byte * Cartridge::get_sram_banks(int bank){
  return sram_banks[bank];
}
byte * Cartridge::get_chr_banks(int bank){
  return chr_banks[bank];
}

byte * Cartridge::get_prg_bank(){
  return prg_banks[current_prg_bank];
}
byte * Cartridge::get_sram_bank(){
  return sram_banks[current_sram_bank];
}
byte * Cartridge::get_chr_bank(){
  return chr_banks[current_chr_bank];
}