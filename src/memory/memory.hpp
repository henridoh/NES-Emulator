#include <vector>
#include "../datatypes.hpp"
using namespace data_types;

class Memory{
  private:
  std::vector< byte * > bank_pointers;
  std::vector< int > bank_addresses;
  int bank_count;

  public:
  Memory();
  void add_bank(byte * bank, int size);

  void write(int address, byte value);
  byte read(int address);
  void insert(int address, byte * data, int len);
};