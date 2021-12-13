#include <stdio.h>
#include <string.h>
#include <math.h>

#if 0
#define FILE_NAME "sample.txt"
#else
#define FILE_NAME "input.txt"
#endif

#define CAP 1000

int matrix[CAP][CAP];

void part1()
{
  FILE *fp = fopen(FILE_NAME, "r");

  memset(matrix, 0, sizeof(int) * CAP * CAP);

  int x1, y1, x2, y2, i, j, ans = 0;

  while (fscanf(fp, "%d,%d -> %d,%d", &x1, &y1, &x2, &y2) == 4)
  {
    if (x1 == x2)
    {
      for (i = fmin(y1, y2); i <= fmax(y1, y2); ++i)
      {
        ++matrix[i][x1];
      }
    }
    else if (y1 == y2)
    {
      for (i = fmin(x1, x2); i <= fmax(x1, x2); ++i)
      {
        ++matrix[y1][i];
      }
    }
  }

  for (i = 0; i < CAP; ++i)
    for (j = 0; j < CAP; ++j)
      if (matrix[i][j] > 1)
        ans++;

  printf("Part 1: %d\n", ans);

  fclose(fp);
}

void part2()
{
  FILE *fp = fopen(FILE_NAME, "r");

  memset(matrix, 0, sizeof(int) * CAP * CAP);

  int x1, y1, x2, y2;

  while (fscanf(fp, "%d,%d -> %d,%d", &x1, &y1, &x2, &y2) == 4)
  {
    int signX = 0, signY = 0;

    if (x1 > x2)
      signX = -1;
    else if (x1 < x2)
      signX = 1;

    if (y1 > y2)
      signY = -1;
    else if (y1 < y2)
      signY = 1;

    while (y1 != y2 || x1 != x2)
    {
      ++matrix[y1][x1];
      y1 += signY;
      x1 += signX;
    }
    ++matrix[y1][x1];
  }

  int i, j, ans = 0;

  for (i = 0; i < CAP; ++i)
    for (j = 0; j < CAP; ++j)
      if (matrix[i][j] > 1)
        ans++;

  printf("Part 2: %d\n", ans);

  fclose(fp);
}

int main(void)
{
  part1();
  part2();

  return 0;
}