#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#if 0
#define FILE_NAME "sample.txt"
#else
#define FILE_NAME "input.txt"
#endif

#define MAX_LEN 7

char pattern[10][MAX_LEN + 1];
char *ordered_nums[10];
int lens[10];

void part1()
{
  FILE *fp = fopen(FILE_NAME, "r");

  int ans = 0, len, i = 0;

  char seq[MAX_LEN];

  while (fscanf(fp, "%s", seq) == 1)
  {
    if (seq[0] == '|')
      continue;

    if (++i > 10)
    {
      len = strlen(seq);

      if ((len >= 2 && len <= 4) || len == 7)
        ans++;

      i %= 14;
    }
  }

  printf("Part 1: %d\n", ans);

  fclose(fp);
}

void deduce_nums()
{
  int i;

  // Find 1, 4, 7 and 8.
  for (i = 0; i < 10; ++i)
  {
    switch (lens[i])
    {
    case 2:
      ordered_nums[1] = pattern[i];
      break;
    case 3:
      ordered_nums[7] = pattern[i];
      break;
    case 4:
      ordered_nums[4] = pattern[i];
      break;
    case 7:
      ordered_nums[8] = pattern[i];
      break;
    }
  }

  char six_blank;
  int j;

  // Find 3 and 6
  for (i = 0; i < 10; ++i)
  {
    if (lens[i] == 5)
    {
      if (strchr(pattern[i], ordered_nums[1][0]) != NULL && strchr(pattern[i], ordered_nums[1][1]) != NULL)
        ordered_nums[3] = pattern[i];
    }
    else if (lens[i] == 6)
    {
      if (strchr(pattern[i], ordered_nums[1][0]) == NULL || strchr(pattern[i], ordered_nums[1][1]) == NULL)
      {
        ordered_nums[6] = pattern[i];
        for (j = 0; j < MAX_LEN; ++j)
        {
          if (strchr(pattern[i], ordered_nums[8][j]) == NULL)
          {
            six_blank = ordered_nums[8][j];
            break;
          }
        }
      }
    }
  }

  // Find 2 and 5
  for (i = 0; i < 10; ++i)
  {
    if (lens[i] == 5)
    {
      if (strchr(pattern[i], six_blank) == NULL)
        ordered_nums[5] = pattern[i];
      else if (strstr(pattern[i], ordered_nums[3]) == NULL)
        ordered_nums[2] = pattern[i];
    }
  }

  // Find 9
  char nine[6];

  strcpy(nine, ordered_nums[4]);

  for (i = 0; i < 4; ++i)
  {
    if (strchr(nine, ordered_nums[4][i]) != NULL)
    {
      nine[5] = ordered_nums[4][i];
      break;
    }
  }

  for (i = 0; i < 10; ++i)
  {
    if (lens[i] == 6)
    {
      bool ok = true;
      for (j = 0; j < 6 && ok; ++j)
      {
        if (strchr(pattern[i], nine[j]) == NULL)
          ok = false;
      }

      if (ok)
      {
        ordered_nums[9] = pattern[i];
        break;
      }
    }
  }

  // Finally, find 0
  for (i = 0; i < 10; ++i)
  {
    if (lens[i] == 6 && strstr(pattern[i], ordered_nums[6]) == NULL && strstr(pattern[i], ordered_nums[9]) == NULL)
    {
      ordered_nums[0] = pattern[i];
      break;
    }
  }
}

int find_number(char *seq)
{
  int i, j, len = strlen(seq);
  for (i = 0; i < 10; ++i)
  {
    if ((int)strlen(ordered_nums[i]) != len)
      continue;

    bool ok = true;

    for (j = 0; j < len && ok; ++j)
    {
      if (strchr(ordered_nums[i], seq[j]) == NULL)
        ok = false;
    }

    if (ok)
      return i;
  }

  assert(0 && "Unreachable");
}

void part2()
{
  FILE *fp = fopen(FILE_NAME, "r");

  int ans = 0, output_num = 0, curr_num, len, i = 0;

  char seq[MAX_LEN];

  while (fscanf(fp, "%s", seq) == 1)
  {
    if (seq[0] == '|')
    {
      deduce_nums();
      continue;
    }

    if (i < 10)
    {
      strcpy(pattern[i++], seq);
      len = strlen(seq);
      lens[i - 1] = len;
    }
    else
    {
      curr_num = find_number(seq);

      if (curr_num > 0)
        output_num += curr_num * pow(10, 14 - i++ - 1);
      else
        ++i;

      if (i == 14)
      {
        ans += output_num;
        output_num = 0;
        i = 0;
      }
    }
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