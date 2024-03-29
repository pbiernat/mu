/*mu is a small utility to used for fixing Final Fantasy 5 SRAM data.
 *You can edit your save file and play on real hardware or on an emulator
 * without the need for a patched ROM (or emulator hack). */
#include <iostream>
#include <stdio.h>
#include <stdint.h>

int16_t calc_checksum(FILE * sram, int offset) {
  
  uint32_t checksum_;
  uint16_t aw;
  uint16_t rw;
  bool carry = false;
  std::cout << offset;
  if (offset != 0) 
    fseek(sram,offset,SEEK_SET);
  
  for (int i=0;i < 767 ; i++) {
    fread(&rw,2,1,sram);
    checksum_ = aw + rw + carry;
    carry = checksum_ > 0xffff;
    aw = checksum_;
  }
  checksum_ = int16_t(checksum_);
  return checksum_;
 }

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " <Final Fantasy 5 SRAM> \n";
    return 1;
  }
  FILE * game;
  game = fopen(argv[1],"r+b");
  
  int16_t checksum;
  //1792 == 0x700 == Sive of Each Save File
  //8176 == 0x1FF0 == Offset of Checksum in SRAM.
  for(int i = 0; i < 4; i++) {
    checksum = calc_checksum(game,(i*1792));
    std::cout << std::hex << "Checksum: " << checksum << "\n";
    fseek(game,(8176 + (i*2)),SEEK_SET);
    fwrite(&checksum,2,1,game);
  }
  fclose(game);
  return 0;
}

