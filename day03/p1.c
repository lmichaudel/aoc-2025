#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int solve(char* file_path) {
  FILE *fp = fopen(file_path, "r");
  if(!fp) {
    fprintf(stderr, "Invalid file: %s\n", file_path);
    exit(EXIT_FAILURE);
  }

  int acc = 0;

  char* line = NULL; 
  size_t len;
  ssize_t slen;

  while((slen = getline(&line, &len, fp)) != -1) {
    int battery;

    int first_digit = 0;
    size_t first_digit_index = -1;
    for(size_t i = 0; i < slen - 2; ++i) {
      int digit = line[i] - '0';

      if(digit > first_digit) {
        first_digit = digit;
        first_digit_index = i;
      }
    }

    int second_digit = 0;
    for(size_t i = first_digit_index + 1; i < slen - 1; ++i) {
      int digit = line[i] - '0';

      if(digit > second_digit)
        second_digit = digit;
    }

    acc += first_digit * 10 + second_digit;
  }

  return acc;
}

int main(int argc, char **argv) {
  if (argc < 2) {
      fprintf(stderr, "Usage: %s <inputfile>\n", argv[0]);
      return 1;
  }
  
  printf("%s: %d\n", argv[1],  solve(argv[1]));

  return 0;
}
