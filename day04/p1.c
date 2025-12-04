#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int width;
  int height;
  int **data;
} map_t;

typedef struct {
  int x, y;
} coord_t;

void get_neighbors(coord_t *coords_p, int *neighbor_count, int x, int y,
                   int width, int height) {
  static const int OFFSETS[8][2] = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0},
                                    {1, 0},   {-1, 1}, {0, 1},  {1, 1}};

  int count = 0;

  for (int i = 0; i < 8; i++) {
    int nx = x + OFFSETS[i][0];
    int ny = y + OFFSETS[i][1];

    // Check bounds
    if (nx >= 0 && nx < width && ny >= 0 && ny < height) {

      coords_p[count].x = nx;
      coords_p[count].y = ny;
      count++;
    }
  }

  *neighbor_count = count;
}

map_t parse_map_file(const char *filename) {
  FILE *fp = fopen(filename, "r");
  if (!fp) {
    perror("Failed to open file");
    exit(1);
  }

  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  map_t map = {0, 0, NULL};

  while ((read = getline(&line, &len, fp)) != -1) {
    if (read > 0 && line[read - 1] == '\n') {
      line[--read] = '\0'; // strip newline
    }

    if (map.width == 0)
      map.width = read;

    map.height++;
  }

  map.data = malloc(map.height * sizeof(int *));
  for (int i = 0; i < map.height; i++)
    map.data[i] = malloc(map.width * sizeof(int));

  rewind(fp);
  int row = 0;
  while ((read = getline(&line, &len, fp)) != -1) {
    if (read > 0 && line[read - 1] == '\n') {
      line[--read] = '\0';
    }

    for (int col = 0; col < map.width; col++) {
      char c = line[col];
      map.data[row][col] = (c == '@') ? 1 : 0;
    }
    row++;
  }

  free(line);
  fclose(fp);
  return map;
}

int solve(char *file_path) {
  map_t map = parse_map_file(file_path);
  int acc = 0;

  for (int y = 0; y < map.height; ++y) {
    for (int x = 0; x < map.width; ++x) {
      if (map.data[y][x] == 0) {
        printf(".");
        continue;
      }
      coord_t *neighbors = (coord_t *)malloc(8 * sizeof(coord_t));
      int neighbor_count;

      get_neighbors(neighbors, &neighbor_count, x, y, map.width, map.height);

      int valid_neighbor_count = 0;
      for (int i = 0; i < neighbor_count; ++i) {
        valid_neighbor_count += map.data[neighbors[i].y][neighbors[i].x];
      }

      printf("%d", valid_neighbor_count);
      if (valid_neighbor_count < 4) {
        acc++;
      }
    }

    printf("\n");
  }

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
