#include "lib.h"
HASH(fname, char *, struct fname, char *, HASHSIZE)
/*
 1. Import list of American names into names_rank array [{"metaphone": "score"}]
 2. Create a hash of Metaphone to American names.
 3. Convert input name to Metaphone
 4. Get Levenshtein distance between input and each Metaphone into array [{"metaphone": "score"}]
 5. Sort array of metaphones based on score
 6. Convert top entries in array from metaphone to American 
*/

int main(int argc, char **argv) {
  if (argc < 4) return 0;
 
  char *name = argv[1];
  char *filename = argv[2];
  int weight = atoi(argv[3]);
  name_rank *names[TOTALNAMES];
  char *codes[2];
  int total_names = load_data(names, filename, MAXLINE, 4, (item_add) _fname_add);

  //DoubleMetaphone(name, codes);

  get_similar_sounding_names(name, names, total_names, weight);
  
  for (int i = 0; i < 10; i++) {
    //printf("%s, %s\n", n[0], codes[1]);
  } 
/*
  printf("%s score with %s is %lu", name, "random name\n", levenshtein(name, "hello"));
*/
  return 0;
}
