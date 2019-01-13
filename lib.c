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
void load_data(char *names[], char *filename, int line_length, int max_line_words, item_add add) {
  int i = 0;
  FILE *fp;
  char **words = calloc(max_line_words + 1, sizeof(char *));
  char *line = malloc(line_length);
  char *codes[2];

  // Open ratings file
   if ((fp = fopen (filename, "r")) == NULL) 
     error("Unable to open file \n");

   // Add/update user ratings
   while (fgets(line, line_length, fp) != NULL) {
       delim(words, line, '\n'); 
       DoubleMetaphone(*words, codes);
       add(codes[0], *words);
       names[i] = malloc(sizeof(char) * strlen(*words));
       strcpy(names[i++], *words);
       printf("%s, %s\n", codes[0], names[i-1]);
   }

   free(line);
   char **temp = words;
   while (*words) {
       free(*words);
     words++;
   }
   free (temp);
   fclose(fp);
}