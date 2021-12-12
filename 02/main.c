#include <stdio.h>

#if 0
#define FILE_NAME "sample.txt"
#else
#define FILE_NAME "input.txt"
#endif

void part1()
{
  FILE *fp = fopen(FILE_NAME, "r");

  char dir[7];
  int n;
  int d = 0, h = 0;

  while (fscanf(fp, "%s", dir) == 1 && fscanf(fp, "%d", &n) == 1)
  {
    switch (dir[0])
    {
    case 'f':
    {
      h += n;
      break;
    }
    case 'd':
    {
      d += n;
      break;
    }
    case 'u':
    {
      d -= n;
      break;
    }
    default:
    {
      fprintf(stderr, "Unknown direction: %c\n", dir[0]);
      break;
    }
    }
  }

  printf("Part 1: %d\n", d * h);

  fclose(fp);
}

void part2()
{
  FILE *fp = fopen(FILE_NAME, "r");

  char dir[7];
  int n;
  int d = 0, h = 0, aim = 0;

  while (fscanf(fp, "%s", dir) == 1 && fscanf(fp, "%d", &n) == 1)
  {
    switch (dir[0])
    {
    case 'f':
    {
      h += n;
      d += n * aim;
      break;
    }
    case 'd':
    {
      aim += n;
      break;
    }
    case 'u':
    {
      aim -= n;
      break;
    }
    default:
    {
      fprintf(stderr, "Unknown direction: %c\n", dir[0]);
      break;
    }
    }
  }

  printf("Part 2: %d\n", d * h);

  fclose(fp);
}

int main(void)
{
  part1();
  part2();

  return 0;
}