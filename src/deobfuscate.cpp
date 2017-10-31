#include "deobfuscate.h"

std::string decrypt(int* arr, int* key) {
  std::string output = "";
  char decrypted = 'x';
  int i = 0;
  int size = arr[i++];
  for (auto i = 1; i < size + 1; i++) {
    decrypted = arr[i] ^ key[(i - 1 % 32)];
    output += decrypted;
  }
  output += '\0';
  return output;
}
