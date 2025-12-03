#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef uint64_t i64;

i64 solve(char* file_path) {
  FILE *fp = fopen(file_path, "r");
  if(!fp) {
    fprintf(stderr, "Invalid file: %s\n", file_path);
    exit(EXIT_FAILURE);
  }

  i64 acc = 0;

  char* line = NULL; 
  size_t len;
  ssize_t slen;

  while((slen = getline(&line, &len, fp)) != -1) {

    int last_digit_id = -1;
    i64 _pow = pow(10, 11);

    for(size_t k = 0; k < 12; ++k) {

      int best_digit = 0;
      for(size_t i = last_digit_id + 1; i < slen - 12 + k; ++i) {
        int digit = line[i] - '0';

        if(digit > best_digit) {
          best_digit = digit;
          last_digit_id = i;
        }
      }

      acc += best_digit * _pow;
      _pow /= 10;
    }
  }

  return acc;
}

int main(int argc, char **argv) {
  if (argc < 2) {
      fprintf(stderr, "Usage: %s <inputfile>\n", argv[0]);
      return 1;
  }
  
  printf("%s: %llu\n", argv[1],  solve(argv[1]));

  return 0;
}
