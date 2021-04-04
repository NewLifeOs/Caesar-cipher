#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

#define buf 100

// Text encryption function
char encrypt(char str, int key) {
  char s = str;
  if (str >= 'a' && str <= 'z')
    s = (((str+key) - 'a')%26)+'a';
  else if (str >= 'A' && str <= 'Z')
    s = (((str+key) - 'A')%26)+'A';
  return s;
}

// Text decryption function
char decrypt(char str, int key) {
  char s = str;
  if (str >= 'a' && str <= 'z')
    s = (((26+str-key) - 'a')%26)+'a';
  else if (str >= 'A' && str <= 'Z')
    s = (((26+str-key) - 'A')%26)+'A';
  return s;
}

// Function for determining the length of a string
int check(char *string, int length) {
  if (strlen(string)>length) {
    printf("\nSorry. You have entered a valid character limit - [100] vs your %ld\n", strlen(string));
    exit(1);
  } else return strlen(string);
}
