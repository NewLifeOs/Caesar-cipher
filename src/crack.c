#include "../include/cipher.h"

int main(void) {
  char *buffer = malloc(buf * sizeof(char));
  char *str = malloc(buf * sizeof(char));
  int i, n, key;
  int s = 1;

  printf("\nEnter text: ");
  scanf("%s", str);
  check(str, buf);

  printf("______________________________________________________\n");
  for (n=25; n>0; n--) {
    for (i=0; i<strlen(str); i++) {
      if (decrypt(str[i], n) !=0)
        buffer[i] = decrypt(str[i], n);
	   }
  printf("%d - '%s'\n", s++, buffer);
  printf("______________________________________________________\n");
  }
  return 0;
}
