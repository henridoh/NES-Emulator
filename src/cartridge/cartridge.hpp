#include <vector>
#include <string>
#include "../datatypes.hpp"
using namespace data_types;

#define SRAM_SIZE 0x2000
#define PRG_SIZE 0x4000
#define CHR_SIZE 0x2000

class Cartridge{
  private:
  std::vector< byte * > prg_banks;
  std::vector< byte * > sram_banks;
  std::vector< byte * > chr_banks;

  int current_prg_bank = 0;
  int current_sram_bank = 0;
  int current_chr_bank = 0;

  word rom_control = 0;

  public:
  Cartridge();
  Cartridge(std::string filename);
  
  byte * get_prg_banks(int bank);
  byte * get_sram_banks(int bank);
  byte * get_chr_banks(int bank);

  byte * get_prg_bank();
  byte * get_sram_bank();
  byte * get_chr_bank();

};