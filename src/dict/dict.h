#ifndef DICT_H
# define DICT_H

/* Data type stored in the ditionary */
#define DATA_TYPE void *

/* Data returned by dict_pop and dict_get_item when no data is found */
#define NULL_DATA NULL

/* Free data while freeing the dict or popping if set to 1 */
#define FREE_DATA 1

#include "../parser/parser.h"
/* If DATA_TYPE is 'void *', it might be handy to store an enum in dictonary
** elements to know into which type of data the data field points, to do this
** set ADD_TYPE_ENUM to 1, 0 otherwise. The name of the enum is specified
** in TYPE_ENUM.
**
** --------------------------------------------------------------------
** | You have to include your own header to declare the enum as well  |
** --------------------------------------------------------------------
*/
#define ADD_TYPE_ENUM 1
#define TYPE_ENUM enum data_type

#include <stddef.h>

struct dict_elt
{
  char *key;
  DATA_TYPE data;
  #if ADD_TYPE_ENUM == 1
  TYPE_ENUM type;
  #endif
  struct dict_elt *next;
};

struct dict
{
  size_t size;
  struct dict_elt *head;
};

struct dict *dict_init(void);
void dict_append(struct dict *d, DATA_TYPE data,
                 #if ADD_TYPE_ENUM == 1
                 TYPE_ENUM type,
                 #endif
                 char *key);
void dict_pop(struct dict *d);
DATA_TYPE dict_get_item(struct dict *d, char *key);
size_t dict_get_size(struct dict *d);
void dict_free(struct dict *d);
void dict_print(struct dict *d, int offset, int inc,
     void (*print_fun)(DATA_TYPE data, enum data_type type, int offset));

#endif /* !DICT_H */