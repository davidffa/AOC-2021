#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#if 0
#define FILE_NAME "sample.txt"
#else
#define FILE_NAME "input.txt"
#endif

#define ULL unsigned long long

#define CAP 150

const int corrupted_table[4] = {3, 57, 1197, 25137};
const int incomplete_table[4] = {1, 2, 3, 4};

char open_stack[CAP];
int open_stack_cnt;

int is_corrupted(char *seg)
{
  int i, len = strlen(seg), score = 0;
  open_stack_cnt = 0;
  bool ok = 1;

  for (i = 0; i < len && ok; ++i)
  {
    if (seg[i] == '(' || seg[i] == '{' || seg[i] == '<' || seg[i] == '[')
    {
      open_stack[open_stack_cnt++] = seg[i];
    }
    else
    {
      switch (seg[i])
      {
      case ')':
        if (open_stack[open_stack_cnt - 1] != '(')
        {
          ok = false;
          score += corrupted_table[0];
        }
        else
          open_stack_cnt--;
        break;
      case ']':
        if (open_stack[open_stack_cnt - 1] != '[')
        {
          ok = false;
          score += corrupted_table[1];
        }
        else
          open_stack_cnt--;
        break;
      case '}':
        if (open_stack[open_stack_cnt - 1] != '{')
        {
          ok = false;
          score += corrupted_table[2];
        }
        else
          open_stack_cnt--;
        break;
      case '>':
        if (open_stack[open_stack_cnt - 1] != '<')
        {
          ok = false;
          score += corrupted_table[3];
        }
        else
          open_stack_cnt--;
        break;
      }
    }
  }

  return score;
}

void part1()
{
  FILE *fp = fopen(FILE_NAME, "r");

  char seg[CAP];
  int ans = 0;

  while (fscanf(fp, "%s", seg) == 1)
  {
    ans += is_corrupted(seg);
  }

  printf("Part 1: %d\n", ans);

  fclose(fp);
}

void part2()
{
  FILE *fp = fopen(FILE_NAME, "r");

  char seg[CAP];
  ULL scores[CAP];
  int scores_sz = 0;

  memset(scores, 0, sizeof(scores));

  while (fscanf(fp, "%s", seg) == 1)
  {
    if (!is_corrupted(seg))
    {
      while (open_stack_cnt > 0)
      {
        scores[scores_sz] *= 5;

        switch (open_stack[--open_stack_cnt])
        {
        case '(':
          scores[scores_sz] += incomplete_table[0];
          break;
        case '[':
          scores[scores_sz] += incomplete_table[1];
          break;
        case '{':
          scores[scores_sz] += incomplete_table[2];
          break;
        case '<':
          scores[scores_sz] += incomplete_table[3];
          break;
        }
      }

      scores_sz++;
    }
  }

  int i, j;
  ULL tmp;
  for (i = 0; i < scores_sz; ++i)
  {
    for (j = 0; j < scores_sz - 1; ++j)
    {
      if (scores[j] < scores[j + 1])
      {
        tmp = scores[j];
        scores[j] = scores[j + 1];
        scores[j + 1] = tmp;
      }
    }
  }

  printf("Part 2: %llu\n", scores[scores_sz / 2]);

  fclose(fp);
}

int main(void)
{
  part1();
  part2();

  return 0;
}