#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#if 0
#define FILE_NAME "sample.txt"
#else
#define FILE_NAME "input.txt"
#endif

#define MX 1500

int pos[MX];
int pos_cnt = 0;

void read_input()
{
  FILE *fp = fopen(FILE_NAME, "r");

  while (fscanf(fp, "%d,", &pos[pos_cnt]) == 1)
    ++pos_cnt;

  fclose(fp);
}

void part1()
{
  int i, j, fuel_cnt, min = __INT32_MAX__;

  for (i = 0; i < MX; ++i)
  {
    fuel_cnt = 0;
    for (j = 0; j < pos_cnt; ++j)
    {
      fuel_cnt += abs(pos[j] - i);
    }
    min = fmin(min, fuel_cnt);
  }

  printf("Part 1: %d\n", min);
}

// sum of arithmetic progression (thanks math)
int calc_fuel(int dist)
{
  return dist * (dist + 1) / 2;
}

void part2()
{
  int i, j, fuel_cnt, min = __INT32_MAX__;

  for (i = 0; i < MX; ++i)
  {
    fuel_cnt = 0;
    for (j = 0; j < pos_cnt; ++j)
    {
      fuel_cnt += calc_fuel(abs(pos[j] - i));
    }
    if (fuel_cnt < min)
      min = fuel_cnt;
  }

  printf("Part 2: %d\n", min);
}

int main(void)
{
  read_input();
  part1();
  part2();

  return 0;
}