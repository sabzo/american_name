#include "lib.h"
HASH(fname, char *, struct fname, char *, HASHSIZE)
/*
 1. Import list of American names
 2. Create a hash of Metaphone to American names.
 3. Convert input name to Metaphone
 4. Get Levenshtein distance between input and each Metaphone into array [{"metaphone": "score"}]
 5. Sort array of metaphones based on score
 6. Convert top entries in array from metaphone to American 
*/

int main(int argc, char **argv) {
  if (argc < 3) return 0;
 
  char *name = argv[1];
  char *filename = argv[2];
  char *names[TOTALNAMES];
  load_data(names, filename, MAXLINE, 4, (item_add) _fname_add);

  /*
  DoubleMetaphone(name, codes);

  printf("%s, %s\n", codes[0], codes[1]);

  printf("%s score with %s is %lu", name, "random name\n", levenshtein(name, "hello"));
*/
  return 0;
}
