#include <stdio.h>
#include <string.h>

#if 0
#define FILE_NAME "sample.txt"
#else
#define FILE_NAME "input.txt"
#endif

#define MXN 9

#define ULL unsigned long long

ULL hash_table[MXN];

void readInput()
{
  FILE *fp = fopen(FILE_NAME, "r");

  memset(hash_table, 0, sizeof(ULL) * MXN);

  int n;

  while (fscanf(fp, "%d,", &n) == 1)
    hash_table[n]++;

  fclose(fp);
}

ULL solve(int days)
{
  int i, j;
  ULL zeros;

  for (i = 0; i < days; ++i)
  {
    zeros = hash_table[0];
    for (j = 1; j < MXN; ++j)
    {
      hash_table[j - 1] = hash_table[j];
      hash_table[j] = 0;
    }
    hash_table[6] += zeros;
    hash_table[8] = zeros;
  }

  ULL ans = 0;

  for (i = 0; i < MXN; ++i)
    ans += hash_table[i];

  return ans;
}

void part1()
{
  readInput();
  printf("Part 1: %llu\n", solve(80));
}

void part2()
{
  readInput();
  printf("Part 2: %llu\n", solve(256));
}

int main(void)
{
  part1();
  part2();
}