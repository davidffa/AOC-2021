#include <stdio.h>
#include <stdlib.h>

#if 0
#define FILE_NAME "sample.txt"
#else
#define FILE_NAME "input.txt"
#endif

void part1()
{
  FILE *fp = fopen(FILE_NAME, "r");

  int prev = 0, curr, ans = 0;

  while (fscanf(fp, "%d", &curr) == 1)
  {
    if (prev != 0)
      if (curr > prev)
        ans++;

    prev = curr;
  }

  printf("Part 1: %d\n", ans);

  fclose(fp);
}

void part2()
{
  FILE *fp = fopen(FILE_NAME, "r");

  int a, b, c, d, ans = 0;

  fscanf(fp, "%d", &a);
  fscanf(fp, "%d", &b);
  fscanf(fp, "%d", &c);

  while (fscanf(fp, "%d", &d) == 1)
  {
    if (d > a)
      ans++;
    a = b;
    b = c;
    c = d;
  }

  printf("Part 2: %d\n", ans);

  fclose(fp);
}

int main(void)
{
  part1();
  part2();

  return 0;
}