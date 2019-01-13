#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASHSIZE 101
#define MAXLINE 30 
#define TOTALNAMES 35070
#define MAXLINEWORDS 20
#define MAXVALUES 100

// double metaphone and a rank (to be stored in array of name-ranks)
typedef struct name_rank {
  int score;
  char *name;
  char * code;
} name_rank;

// typedef for add item function
typedef void * (*item_add)(void *, char *);

//void load_data(char *filename);
void error(char *msg);
