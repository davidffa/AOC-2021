#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#if 0
#define FILE_NAME "sample.txt"
#else
#define FILE_NAME "input.txt"
#endif

#define CAP 100

int matrix[CAP][CAP];
bool vis[CAP][CAP];
int basins_sz[CAP * CAP];
int w, h;

int adjs[4][2] = {
    {-1, 0},
    {0, 1},
    {0, -1},
    {1, 0}};

bool is_low(int r, int c)
{
  int rAdj, cAdj;
  for (int i = 0; i < 4; ++i)
  {
    rAdj = r + adjs[i][0], cAdj = c + adjs[i][1];

    if (rAdj >= 0 && rAdj < h && cAdj >= 0 && cAdj < w && matrix[rAdj][cAdj] <= matrix[r][c])
      return false;
  }

  return true;
}

void read_input()
{
  FILE *fp = fopen(FILE_NAME, "r");

  int i = 0, j = 0;
  char c;

  while (fscanf(fp, "%c", &c) == 1)
  {
    if (c == '\n')
    {
      w = j;
      ++i;
      j = 0;
      continue;
    }

    matrix[i][j++] = c - '0';
  }

  h = i;

  fclose(fp);
}

void part1()
{
  int i, j, ans = 0;

  for (i = 0; i < h; ++i)
  {
    for (j = 0; j < w; ++j)
    {
      if (is_low(i, j))
        ans += matrix[i][j] + 1;
    }
  }

  printf("Part 1: %d\n", ans);
}

void dfs(int r, int c, int *size)
{
  if (vis[r][c])
    return;

  ++(*size);

  vis[r][c] = true;

  int rAdj, cAdj;
  for (int i = 0; i < 4; ++i)
  {
    rAdj = r + adjs[i][0], cAdj = c + adjs[i][1];

    if (rAdj >= 0 && rAdj < h && cAdj >= 0 && cAdj < w && matrix[rAdj][cAdj] >= matrix[r][c] && matrix[rAdj][cAdj] < 9)
      dfs(rAdj, cAdj, size);
  }
}

void sort_basins(int *cnt)
{
  int i, j, tmp;
  for (i = 0; i < *cnt; ++i)
  {
    for (j = 0; j < *cnt - 1; ++j)
    {
      if (basins_sz[j] < basins_sz[j + 1])
      {
        tmp = basins_sz[j];
        basins_sz[j] = basins_sz[j + 1];
        basins_sz[j + 1] = tmp;
      }
    }
  }
}

void part2()
{
  memset(vis, false, sizeof(vis));

  int i, j, cnt = 0, basin_sz;

  for (i = 0; i < h; ++i)
  {
    for (j = 0; j < w; ++j)
    {
      if (is_low(i, j))
      {
        basin_sz = 0;
        dfs(i, j, &basin_sz);
        basins_sz[cnt++] = basin_sz;
      }
    }
  }

  sort_basins(&cnt);

  printf("Part 2: %d\n", basins_sz[0] * basins_sz[1] * basins_sz[2]);
}

int main(void)
{
  read_input();
  part1();
  part2();

  return 0;
}