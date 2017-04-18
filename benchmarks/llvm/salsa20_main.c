#include "salsa20.c"

int main(void) {
  uint32_t val, i;
#ifdef SMALL_PROBLEM_SIZE
  uint32_t count = 5379194;
  uint32_t offset = 0xf655703d - 0xb67e7950;
#else
  uint32_t count = 537919488;
  uint32_t offset = 0;
#endif

  for(i=0; i<16; i++)
    STATE[i] = (0xedababe5+(i+13))^(0xdeadbeef-i);
  
  for(i=0; i<count; i++)
    salsa();

  val = salsa();
  val += offset;

  printf("got:       %x\n", val);
  printf("should be: %x\n", 0xf655703d);
  return(val != 0xf655703d);
}
