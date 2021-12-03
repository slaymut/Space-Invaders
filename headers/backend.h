#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


/* Block Object */
struct Block {
  int x, y;
  char symbol;
};

struct Block **createBlocks(int max_y);
struct Block *createBlock(int x, int y);
void individualBlocks(struct Block **blocks, int i, int edge_d, int y);
void freeBlocks(struct Block **blocks);
struct Block *findTopBlock(struct Block **blocks);

