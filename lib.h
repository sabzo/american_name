#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASHSIZE 101
#define MAXLINE 30 
#define TOTALNAMES 35070
#define MAXLINEWORDS 20
#define MAXVALUES 100
// Create a Custom Hash Type
#define HASH(name, type_key, type_next, type_obj, size)  \
  typedef struct name { \
    type_key key; \
    type_obj *value; \
    char v_it; /*value array position iterator */ \
    type_next *next; \
  } name; \
  type_next *_##name##_hash[HASHSIZE];\
 \
/* Get position in Hash array based on key */ \
unsigned int _##name##_hashpos(type_key _name) { \
  unsigned hashval = 0; \
  char c; \
  while ((c = *_name++) != '\0') \
    hashval = c + 31 * hashval; \
  return hashval % HASHSIZE; \
} \
  /* Find the object if it exists in the hash */ \
type_next *_##name##_find(type_key key) { \
  type_next *hp; \
  for (hp = _##name##_hash[_##name##_hashpos(key)]; hp != NULL; hp = hp->next) \
    if (strcmp(key, hp->key) == 0) \
      return hp; \
    return NULL; \
} \
  /* Add a new object to Hash. If it exists append its value array */ \
type_next *_##name##_add(type_key key, type_obj value) { \
  name *hp; \
  unsigned int hpos; \
  int hkey; \
  if ((hp = _##name##_find(key)) == NULL) { /* not found */ \
    if ((hp = (name *) malloc(sizeof(*hp))) != NULL) { \
      hkey = _##name##_hashpos(key); \
      hp->key = key; \
      hp->v_it = 0; /* the value array is now initialized with 1 object */ \
      hp->value = calloc(MAXVALUES + 1, sizeof(type_obj)); /* zero fill + 1 off to use as sentinel */\
      hp->value[hp->v_it++] = value; \
      hp->next = _##name##_hash[hkey]; \
      _##name##_hash[hkey] = hp; \
    }\
  } else {/* Found item */ \
    if (hp->v_it < MAXVALUES) \
      hp->value[hp->v_it++] = value; \
  } \
  return hp; \
} \
  /* Remove an Object from the hash */ \
type_next *_##name##_remove(type_key key) { \
  name *prev, *curr; \
  int hkey = _##name##_hashpos(key); \
  int removed = 0; \
  for (prev = curr = _##name##_hash[hkey]; curr != NULL; curr = curr->next) { \
    if (strcmp(key, curr->key) == 0) { \
      prev->next = curr->next; \
      free(curr); \
      removed = 1; \
    } \
  } \
  return 0; \
}



// typedef for add item function
typedef void * (*item_add)(void *, char *);


//void load_data(char *filename);
void error(char *msg);

