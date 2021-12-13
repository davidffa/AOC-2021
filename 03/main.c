#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#if 0
#define FILE_NAME "sample.txt"
#define BIT_COUNT 5
#else
#define FILE_NAME "input.txt"
#define BIT_COUNT 12
#endif

void part1()
{
  FILE *fp = fopen(FILE_NAME, "r");

  int count[BIT_COUNT][2];
  char n[BIT_COUNT];

  memset(count, 0, sizeof(int) * BIT_COUNT * 2);

  while (fscanf(fp, "%s", n) == 1)
  {
    for (int i = 0; i < BIT_COUNT; i++)
    {
      if (n[i] == '1')
      {
        count[BIT_COUNT - i - 1][1]++;
      }
      else
      {
        count[BIT_COUNT - i - 1][0]++;
      }
    }
  }

  int gamma = 0, epsilon = 0;

  for (int i = 0; i < BIT_COUNT; i++)
  {
    if (count[i][1] > count[i][0])
    {
      gamma |= 1 << i;
    }
    else
    {
      epsilon |= 1 << i;
    }
  }

  printf("Part 1: %d\n", gamma * epsilon);

  fclose(fp);
}

#define CAP 1000

int cnt = 0;
int nums[CAP];
bool removed[CAP];
int count[2];

void countBits(int pos)
{
  memset(count, 0, sizeof(int) * 2);

  for (int i = 0; i < cnt; ++i)
  {
    if (removed[i])
      continue;

    if (nums[i] & (1 << (BIT_COUNT - pos - 1)))
    {
      count[1]++;
    }
    else
    {
      count[0]++;
    }
  }
}

int calc(bool o2)
{
  memset(removed, 0, sizeof(int) * CAP);

  int rmCnt = 0;

  for (int i = 0; i < BIT_COUNT; ++i)
  {
    countBits(i);

    int j;

    for (j = 0; j < cnt; ++j)
    {
      if (removed[j])
        continue;

      if (o2)
      {
        if (count[1] >= count[0])
        {
          if (!(nums[j] & (1 << (BIT_COUNT - i - 1))))
          {
            removed[j] = 1;
            ++rmCnt;
          }
        }
        else
        {
          if (nums[j] & (1 << (BIT_COUNT - i - 1)))
          {
            removed[j] = 1;
            ++rmCnt;
          }
        }
      }
      else
      {
        if (count[1] < count[0])
        {
          if (!(nums[j] & (1 << (BIT_COUNT - i - 1))))
          {
            removed[j] = 1;
            ++rmCnt;
          }
        }
        else
        {
          if (nums[j] & (1 << (BIT_COUNT - i - 1)))
          {
            removed[j] = 1;
            ++rmCnt;
          }
        }
      }
    }

    if (cnt - rmCnt == 1)
    {
      for (j = 0; j < cnt; ++j)
      {
        if (!removed[j])
          return nums[j];
      }
    }
  }

  assert(0 && "Unreachable");
}

void part2()
{
  FILE *fp = fopen(FILE_NAME, "r");

  char n[BIT_COUNT];

  memset(nums, 0, sizeof(int) * CAP);

  while (fscanf(fp, "%s", n) == 1)
  {
    for (int i = 0; i < BIT_COUNT; ++i)
    {
      nums[cnt] |= (n[i] - '0') << (BIT_COUNT - i - 1);
    }

    ++cnt;
  }

  int o2 = calc(true);
  int co2 = calc(false);

  printf("O2 = %d\nCO2: %d\n", o2, co2);
  printf("Part 2: %d\n", o2 * co2);

  fclose(fp);
}

int main(void)
{
  part1();
  part2();

  return 0;
}