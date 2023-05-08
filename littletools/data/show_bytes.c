#include <stdio.h>
#include<string.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer starter, size_t len) {
  size_t t;
  for (t = 0; t < len; t++) {
    printf(" %.2x", starter[t]);
  }
  printf("\n");
}

void show_int(int x) { show_bytes((byte_pointer)&x, sizeof(int)); }

void show_float(float x) { show_bytes((byte_pointer)&x, sizeof(float)); }

void show_pointer(void *x) { show_bytes((byte_pointer)&x, sizeof(void *)); }

int main() {
  // int ival = 12345;
  // float fval = (float)ival;
  // int *pval = &ival;
  // show_int(ival);
  // show_float(fval);
  // show_pointer(pval);

  // const char *s = "abcdef";
  // show_bytes((byte_pointer)s, strlen(s));

  short sx=-12345;
  unsigned uy=sx;
  printf("uy = %u:\t",uy);
  show_bytes((byte_pointer)&uy,sizeof(unsigned));
}