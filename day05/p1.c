#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uint64_t i64;

typedef struct {
  i64 start;
  i64 end;
} range_t;

int solve(char *file_path) {
  FILE *fp = fopen(file_path, "r");
  if (!fp) {
    perror("Failed to open file");
    exit(1);
  }

  char line[128];

  range_t *ranges = NULL;
  size_t range_count = 0;

  while (fgets(line, sizeof(line), fp)) {
    if (line[0] == '\n' || line[0] == '\r')
      break;

    i64 a, b;
    if (sscanf(line, "%llu-%llu", &a, &b) == 2) {
      ranges = realloc(ranges, (range_count + 1) * sizeof(range_t));
      ranges[range_count].start = a;
      ranges[range_count].end = b;
      range_count++;
    }
  }

  int acc = 0;
  while (fgets(line, sizeof(line), fp)) {
    if (isspace((unsigned char)line[0]))
      continue;

    i64 n;
    if (sscanf(line, "%llu", &n) == 1) {
      for (int i = 0; i < range_count; ++i) {
        if (n >= ranges[i].start && n <= ranges[i].end) {
          acc++;
          break;
        }
      }
    }
  }

  fclose(fp);
  free(ranges);
  return acc;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <inputfile>\n", argv[0]);
    return 1;
  }

  printf("%s: %d\n", argv[1], solve(argv[1]));

  return 0;
}
