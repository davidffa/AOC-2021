#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#if 0
#define FILE_NAME "sample.txt"
#else
#define FILE_NAME "input.txt"
#endif

#define N_CAP 100
#define BOARDS_CAP 100
#define BOARD_SIZE 5

union Board
{
  int board[BOARD_SIZE][BOARD_SIZE];
  int board_flat[BOARD_SIZE * BOARD_SIZE];
};

int nums[N_CAP];
bool winner_boards[BOARDS_CAP];
union Board boards[BOARDS_CAP][BOARD_SIZE * BOARD_SIZE];

int nums_sz = 0;
int boards_sz = 0;

union Board *checkWin(union Board *board)
{
  int i;

  for (i = 0; i < BOARD_SIZE; ++i)
  {
    if (board->board[i][0] == board->board[i][1] &&
        board->board[i][1] == board->board[i][2] &&
        board->board[i][2] == board->board[i][3] &&
        board->board[i][3] == board->board[i][4])
    {
      return board;
    }

    if (board->board[0][i] == board->board[1][i] &&
        board->board[1][i] == board->board[2][i] &&
        board->board[2][i] == board->board[3][i] &&
        board->board[3][i] == board->board[4][i])
    {
      return board;
    }
  }

  return NULL;
}

void markBoards(int n)
{
  int i, j;

  for (i = 0; i < boards_sz; ++i)
  {
    for (j = 0; j < BOARD_SIZE * BOARD_SIZE; ++j)
    {
      if (boards[i]->board_flat[j] == n)
        boards[i]->board_flat[j] = -1;
    }
  }
}

void printBoards()
{
  int i, j, k;
  for (i = 0; i < boards_sz; ++i)
  {
    printf("Board %d:\n", i);
    for (j = 0; j < BOARD_SIZE; ++j)
    {
      for (k = 0; k < BOARD_SIZE; ++k)
      {
        printf(" %02d ", boards[i]->board[j][k]);
      }
      printf("\n");
    }
  }
}

void readInput()
{
  FILE *fp = fopen(FILE_NAME, "r");

  char c;
  int i;

  while (fscanf(fp, "%d%c", &i, &c) == 2)
  {
    nums[nums_sz++] = i;

    if (c == '\n')
      break;
  }

  i = 0;

  while (fscanf(fp, "%d", &boards[boards_sz]->board_flat[i++]) == 1)
  {
    if (i == BOARD_SIZE * BOARD_SIZE)
    {
      boards_sz++;
      i = 0;
    }
  }

  fclose(fp);
}

void part1()
{
  int i, j, sum = 0;
  union Board *winner = NULL;

  for (i = 0; i < nums_sz && winner == NULL; ++i)
  {
    markBoards(nums[i]);
    for (j = 0; j < boards_sz && winner == NULL; ++j)
    {
      winner = checkWin(boards[j]);
    }
  }

  assert(winner != NULL && "No winner found");

  for (j = 0; j < BOARD_SIZE * BOARD_SIZE; ++j)
  {
    if (winner->board_flat[j] != -1)
      sum += winner->board_flat[j];
  }

  // printBoards();

  printf("Part 1: %d\n", sum * nums[i - 1]); // i - 1 because of the last increment of the for loop
}

void part2()
{
  memset(winner_boards, 0, sizeof(bool) + BOARDS_CAP);

  int i, j, sum = 0, winner_cnt = 0;
  union Board *last_winner = NULL;

  for (i = 0; i < nums_sz && winner_cnt != boards_sz; ++i)
  {
    markBoards(nums[i]);

    for (j = 0; j < boards_sz; ++j)
    {
      if (winner_boards[j])
        continue;

      last_winner = checkWin(boards[j]);
      if (last_winner != NULL)
      {
        winner_boards[j] = true;
        ++winner_cnt;
      }
    }
  }

  for (j = 0; j < BOARD_SIZE * BOARD_SIZE; ++j)
  {
    if (last_winner->board_flat[j] != -1)
      sum += last_winner->board_flat[j];
  }

  printf("Part 2: %d\n", sum * nums[i - 1]);
}

int main(void)
{
  readInput();
  part1();
  part2();

  return 0;
}