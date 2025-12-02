#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef uint64_t i64;

bool is_a_repeat(i64 n) {
  char buf[64];
  snprintf(buf, sizeof(buf), "%llu", n);

  int len = strlen(buf);

  if (len % 2 != 0)
      return false;

  int half = len / 2;
  return strncmp(buf, buf + half, half) == 0;
}

i64 solve(char* file_path) {
  FILE *fp = fopen(file_path, "r");
  if(!fp) {
    fprintf(stderr, "Invalid file: %s\n", file_path);
    exit(EXIT_FAILURE);
  }

  i64 acc = 0;

  char* line = NULL; 
  size_t len;
  getline(&line, &len, fp);

  char* token = strtok(line, ",");
  while (token) {
      i64 a, b;

      if (sscanf(token, "%llu-%llu", &a, &b) == 2) {
          for(; a <= b; ++a) {
            if(is_a_repeat(a))
              acc += a;
          }
      }

      token = strtok(NULL, ",");
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
