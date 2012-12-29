/*mu is a small utility to used for fixing Final Fantasy 5 SRAM data.
 *You can edit your save file and play on real hardware or on an emulator
 * without the need for a patched ROM (or emulator hack). */
#include <iostream>
#include <stdio.h>
#include <stdint.h>

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " <Final Fantasy 5 SRAM> \n";
    return 1;
  }
  
  FILE * sram;
  sram = fopen(argv[1],"r+b");
  //if (!sram)
  // return 1;
  int offset = 0;
  uint32_t checksum;
  uint16_t aw;
  uint16_t rw;
  bool carry = false;
  
  for (int i=0;i < 767 ; i++) {
    fread(&rw,2,1,sram);
    offset += 2;
    if (carry)
      std::cout << "Carry! \n";
    checksum = aw + rw + carry;
    std::cout << "Checksum: " << std::hex << checksum << "\n";
    carry = checksum > 0xffff;
    aw = checksum;
  }
  checksum = int16_t(checksum);
  //  std::cout << offset;
  std::cout << "Checksum = " << std::hex << checksum << "\n";
  //Write to appropriate offset.
  fseek(sram,8176,SEEK_SET);
  fwrite(&checksum,2,1,sram);
  fclose(sram);
 return 0;
}

