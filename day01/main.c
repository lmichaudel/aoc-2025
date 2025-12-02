#include <stdio.h>
#include <stdlib.h>

int solve(char* file_path) {
  FILE *fp = fopen(file_path, "r");
  if(!fp) {
    fprintf(stderr, "Invalid file: %s\n", file_path);
    exit(EXIT_FAILURE);
  }

  int dial = 50; 
  int zero_count = 0;

  char line[128];
  while (fgets(line, sizeof(line), fp)) {
    char turn;
    int steps;

    if (sscanf(line, " %c%d", &turn, &steps) == 2) {
      int sign = turn == 'R' ? 1 : -1;
      dial = (dial + sign*steps) % 100;
      if (dial < 0) dial += 100;

      if(0 == dial)
        zero_count++;
    }
  }

  return zero_count;
}

int main(int argc, char **argv) {
  if (argc < 2) {
      fprintf(stderr, "Usage: %s <inputfile>\n", argv[0]);
      return 1;
  }
  
  printf("%s: %d\n", argv[1],  solve(argv[1]));

  return 0;
}
