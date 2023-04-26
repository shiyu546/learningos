#include <stdio.h>
#include <string.h>

int binary_to_digit(char *bin);
void my_substr(char *src, char *dest, int position, int length);
int power(int base, int pow);

const char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                    '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

int main() {
  printf("please input binary series:");
  char input[100];
  scanf("%s", input);

  printf("%s\n", input);

  //判断输入字符长度
  size_t len = strlen(input);
  int first_len = len % 4;
  if (first_len == 0) {
    first_len = 4;
  }
  char output[100];
  int index = 0;

  int position = 0;
  char binary[5];
  while (first_len <= len) {
    my_substr(input, binary, position, first_len - position);
    printf("binary is %s\n", binary);
    int num = binary_to_digit(binary);
    char hex_num = hex[num];
    output[index] = hex_num;
    index++;
    position = first_len;
    first_len += 4;
  }
  output[index] = '\0';

  printf("the hex value is: %s\n", output);
}

int power(int base, int pow) {
  int result = 1;
  for (int i = 1; i <= pow; i++) {
    result *= base;
  }
  return result;
}

int binary_to_digit(char *bin) {
  int result = 0;
  size_t len = strlen(bin);
  for (size_t t = 0; t < len; t++) {
    int temp = bin[t] - '0';
    result += temp * power(2, len - 1 - t);
  }
  return result;
}

void my_substr(char *src, char *dest, int position, int length) {
  int c = 0;
  for (; c < length; c++) {
    dest[c] = src[position + c];
  }
  dest[c] = '\0';
}