#include "../include/cipher.h"

int write_key();
void error(const char *msg);
void cesar_sentence(int num, char *text);
char crypt_text(int num);
char crypt_file(int num);
void help_call(char *name);

// Error output function
void error(const char *msg) {
  perror(msg);
  exit(1);
}

// Determing the key length
int write_key() {
  int key;

  printf("\nEnter encryption key size (1-26): ");
  while ((key <= 0) || (key > 26)) {
    scanf("%d", &key);
    if ((key <= 0) || (key > 26))
      printf("[!] Invalid key size (1-26). Repeat entry:\n");
    else
      printf("\nKey - %d\n", key);
  }
  return key;
}

// Main function
int main(int argc, char **argv) {
  char *option[2] = {"text", "file"};

  if (argc <= 1) {
    printf("[Usage]: \"%s -h\" or \"%s --help\" for more information.\n", argv[0], argv[0]);
    return 0;
  }

  if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))
    help_call(argv[0]);
  else if (!strcmp(argv[1], "-t") || !strcmp(argv[1], "--text")) {
      cesar_sentence(1, option[0]);
  } else if (!strcmp(argv[1], "-f") || !strcmp(argv[1], "--file")) {
      cesar_sentence(2, option[1]);
  } else {
      printf("Unknown parametr: '%s'. Type %s --help for help\n", argv[1], argv[0]);
      return 0;
  }
  return 0;
}

// Text cryption function
char crypt_text(int num) {
  int  i;
  int  key;
  int  length;
  char *str = malloc(buf * sizeof(char));
  char *buffer = malloc(buf * sizeof(char));

  printf("\nEnter text: ");
  scanf(" %[^\n]*c", str);
  length = check(str, buf-1);
  printf("Length = %d\n", length);

  key = write_key();

  switch (num) {
    case 1:
      for (i = 0; i < strlen(str); i++) {
        if (encrypt(str[i], key) != 0)
          buffer[i] = encrypt(str[i], key);
      }
      break;
    case 2:
      for (i = 0; i < strlen(str); i++) {
        if (decrypt(str[i], key) != 0)
          buffer[i] = decrypt(str[i], key);
      }
      break;
  }
  printf("----------------------------------\n");
  printf("Result - %s\n\n", buffer);

  return *buffer;
}

// Text file cryption function
char crypt_file(int num) {
  int   i;
  int   key;
  int   stata;
  int   read_size;
  off_t size;
  FILE  *file;
  FILE  *open_file;
  char  fname[buf];
  char  *title[2] = {"encrypt_textfile.txt",
                    "decrypt_textfile.txt"};
  struct stat st;

  printf("\nEnter name text file: ");
  scanf("%s", fname);
  printf("\nFile - %s\n", fname);

  file = fopen(fname, "rb");
  if (file == NULL) {
    printf("\nI can't open the file '%s'! It may not exist.\n", fname);
    exit(0);
  }

  if (stat(fname, &st) == -1)
    return st.st_size;
  size = st.st_size;
  printf("Size '%s' - %ld bytes\n", fname, size);

  key = write_key();

  char *result_str = (char *)malloc(size);
  char *buffer = (char *)malloc(size);

  while(!feof(file)) {
    read_size = fread(result_str, sizeof(result_str)-1, size, file);

    switch (num) {
      case 1:
        for (i = 0; i < strlen(result_str); i++) {
          if (encrypt(result_str[i], key) != 0)
            buffer[i] = encrypt(result_str[i], key);
        }
        free(result_str);
        open_file = fopen(title[0], "wb");
        break;
      case 2:
        for (i = 0; i < strlen(result_str); i++) {
          if (decrypt(result_str[i], key) != 0)
            buffer[i] = decrypt(result_str[i], key);
        }
        free(result_str);
        open_file = fopen(title[1], "wb");
        break;
    }

    do {
      stata = fputs(buffer, open_file);
    } while (stata < 0);

    free(buffer);
  }
  printf("----------------------------------\n");
  printf("[+] Written to '%s'\n", title[num-1]);
  fclose(open_file);
  fclose(file);
}

// Menu function
void cesar_sentence(int num, char *text) {
  int pick;
  printf("\nCipher Cesar\n");
  printf("_________________________________\n\n");
  printf("  1          encrypt %s \n", text);
  printf("  2          decrypt %s\n\n", text);
  printf("  3          exit\n");
  printf("_________________________________\n\n");

  while (pick != 3) {
    scanf("%d", &pick);
    if ((pick < 1) || (pick > 3))
      printf("\t[!!!] Number %d is not available.\n", pick);

    switch (num) {
      case 1:
        if (pick == 1) { crypt_text(pick); exit(0); }
        if (pick == 2) { crypt_text(pick); exit(0); }
        break;
      case 2:
        if (pick == 1) { crypt_file(pick); exit(0); }
        if (pick == 2) { crypt_file(pick); exit(0); }
        break;
    }
  }
}

// Help function
void help_call(char *name) {
  printf("[Usage]: %s [KEY]...\n\n", name);
  printf("Encrypts and decrypts plain text and text files using a Caesar's cipher.\n");
  printf("You can use your key (1 - 26).\n\n");
  printf("%s [ARGUMENT]\n", name);
  printf("\t  -h, --help      Calls help for additional information.\n");
  printf("\t  -t, --text      Encrypt-decrypt text.\n");
  printf("\t  -f, --file      Encrypt-decrypt text file.\n\n");
  printf("# Coded by NewLifeOs\n");
  printf("# Github: https://github.com/NewLifeOs/Caesar-cipher\n");
}
