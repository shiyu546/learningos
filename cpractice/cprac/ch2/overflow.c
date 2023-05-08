#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int uadd_ok(unsigned x, unsigned y);

int main(int argc, char *argv[]) {
  if (argc != 3) {
    perror("program need two arguments:\n\tusage overflow number1 number2");
    exit(EXIT_FAILURE);
  }

  errno = 0;
  long val1 = strtol(argv[1], NULL, 10);
  if (errno != 0) {
    perror("arguments 1 is not a number");
    exit(EXIT_FAILURE);
  }

  long val2 = strtol(argv[2], NULL, 10);
  if (errno != 0) {
    perror("arguments 2 is not a number");
    exit(EXIT_FAILURE);
  }

  int result = uadd_ok(val1, val2);
  if (result == 1) {
    printf("not ok\n");
  } else {
    printf("ok\n");
  }
  return 0;
}

int uadd_ok(unsigned x, unsigned y) {
  unsigned sum = x + y;
  if (sum < x || sum < y) {
    return 1;
  }
  return 0;
}