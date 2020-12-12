#include <vector>
#include <iostream>
#include <iomanip>
#include "../datatypes.hpp"
using namespace data_types;

#include "memory.hpp"

Memory::Memory(){
}

byte Memory::read(int address){
  if(!bank_addresses.size()){
    std::cerr << std::endl << "Error: Trying to read from adress " << std::hex << address
              << " but memory not yet initialized." << std::endl;
    return 0;
  } if(address > bank_addresses.back()){
    std::cerr << std::endl << "Error: Trying to read from adress 0x" << std::hex << address
              << " but max address is 0x" << std::hex << bank_addresses.back() << "." << std::endl;
    return 0;
  }

  int i;
  for(i=0; address > bank_addresses[i]; i++);
  address -= bank_addresses[i];
  return bank_pointers[i][address];
}

void Memory::insert(int address, byte * data, int len){
  for(int i=0; i<len; i++){
    write(address + i, data[i]);
  }
}

void Memory::write(int address, byte value){
  if(!bank_addresses.size()){
    std::cerr << std::endl << "Error: Trying to write to adress " << std::hex << address
              << " but memory not yet initialized." << std::endl;
    return;
  } if(address > bank_addresses.back()){
    std::cerr << std::endl << "Error: Trying to write to adress 0x" << std::hex << address
              << " but max address is 0x" << std::hex << bank_addresses.back() << "." << std::endl;
    return;
  }

  int i;
  for(i=0; address > bank_addresses[i]; i++);
  address -= bank_addresses[i];
  bank_pointers[i][address] = value;
}

void Memory::add_bank(byte * bank, int size){
  bank_pointers.push_back(bank);
  if(!bank_addresses.size()){
    bank_addresses.push_back(size - 1);
  } else {
    bank_addresses.push_back(bank_addresses.back() + size - 1);
  }
};