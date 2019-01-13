#include "lib.h"
#include "double_metaphone.h"
#include "levenshtein.h"

void error (char *msg) {
  printf("%s\n", msg);
  exit(1);
}

// delimeter
char ** delim(char **words, char *str, char delim) {
  int num_words = 0;
  char char_counter = 0; // num of chars in word
  char wordsize[MAXLINEWORDS];
  char c;
  int pos = 0;
  int str_ptr_offset = 0;
  // Determine how many delimetered words there are
  while (++str_ptr_offset && (c = *str++) != '\0' && c != '\n' && ++char_counter <= MAXLINEWORDS) {
        if (c == delim || *str == '\0' || *str == '\n') {
          if (c == delim)             
            char_counter = char_counter - 1;   // don't count delimeter as a letter
	  num_words++;
	  wordsize[pos++] = char_counter;
	  char_counter = 0; 
	}
  }
  str -= str_ptr_offset;

  // allocate for each word in list
  for (pos = 0; pos < num_words; pos++)
	words[pos] = malloc(wordsize[pos] * sizeof(char *));

  char_counter = 0;
  while ((c = *str++) != '\0' && c != '\n') {
    if (c == delim) {
      **words = '\0'; // complete word creation
      *words = *words - char_counter;
      char_counter = 0;
      words++; // next word 
    }
	else {
	  (*(*words)++) = c; // **words = 'c' THEN *words++. 
          char_counter++;
        }
  }
  **words = '\0'; // End last word which has no delimeter after it
  *words = *words - char_counter;
  words -= pos-1; // Note: this time *word didn't go off by 1 but pos is still off by 1, so subtract 1 to error correct
  return words;
}

// load data
int load_data(name_rank *names[], char *filename, int line_length, int max_line_words) {
  int i = 0; //total names
  FILE *fp;
  char **words = calloc(max_line_words + 1, sizeof(char *));
  char *line = malloc(line_length);
  char *codes[2];
  int score;

  // Open ratings file
   if ((fp = fopen (filename, "r")) == NULL) 
     error("Unable to open file \n");

   // Add/update user ratings
   while (fgets(line, line_length, fp) != NULL) {
       delim(words, line, ','); 
       DoubleMetaphone(*words, codes);
       
       score = (int) atof(*(words + 2));
       if (score < 200) continue;
       names[i] = malloc(sizeof(name_rank));
       names[i]->name = malloc(sizeof(char) * strlen(*words));
       names[i]->code = malloc(sizeof(char) * strlen(codes[0]));
	   strcpy(names[i]->name, *words);
       strcpy(names[i++]->code, codes[0]);
       //printf("%s, %s\n", codes[0], names[i-1]->name);
   }

   free(line);
   char **temp = words;
   while (*words) {
       free(*words);
     words++;
   }
   free (temp);
   fclose(fp);
   return i;
}

// score each entry in names according to how similar it is to name
void score_name(char *code, name_rank *names[], int total_names, int weight) {
  for (int i = 0; i < total_names; i++) {
     names[i]->score = (int) levenshtein(code, names[i]->code);
     if (names[i]->score <= weight) printf("%s \n", names[i]->name);
  }  
}

/* Score comparison function: greatest to lowest */
int score_compare(const name_rank *r1, const name_rank *r2) {
  int eq;
  if (r1->score == r2->score)
    eq = 0;
  else if (r1->score < r2->score)
    eq = 1;
  else
    eq = -1;
  return eq;
}

// sort names by rank
void sort_names_by_score(name_rank *names[]) {
  qsort(names, TOTALNAMES, sizeof(name_rank *), (int (*)(const void *, const void*)) score_compare); 
}

void get_similar_sounding_names(char *name, name_rank *names[], int total_names, int weight) {
    char *codes[2];
    DoubleMetaphone(name, codes);
    score_name(codes[0], names, total_names, weight);
   // sort_names_by_score(names); 
}
