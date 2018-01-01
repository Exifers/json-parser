# json-parser
Quick home-made json parser into C structures. This is some very basic program,
threre's no warranty.

# Prerequisites
-GNU/Linux
-glibc
-gcc
-make

# How to compile ?
Type *make* to produce binary *main*.

# Usage
*./main \<filename.json\>*
Outputs the formatted json, or raise an error if input is incorrect.

# Include in an existing project
You can remove src/main.c and src/main.h. Everything else in the src/ folder
is needed.

# API
{  } objects are named dict (for dictionaries).
[  ] arrays are named llist (for linked lists).

## parse file and free structure

    #include "src/parser/parser.h"

    void *parse_json(char *string, size_t len, enum data_type *type);
Parses the input string of length len into a C structure whose type is given
by the type variable after calling this function.
The data\_type enum is the following :
    enum data_type
    {
      DICT, // dictionnary
      LIST, // linked list
      STRING, // string
      NUMBER, // number (only integers supported yet)
      TRUE,
      FALSE,
      NUL, // "null"
      EMPTY // empty file
    };

Your json file may not contain much things if the returned type is not DICT or
LIST, but this is handled by this program anyway.


    #include "src/parser/parser.h"
    #include "src/free/free.h"

    void free_data(void *data, enum data_type type);
Frees everything returned from parse\_json. data must be the pointer returned
by parse\_json, and type the enum set by parse\_json.

## browse the structure

    #include "src/dict/dict.h"

    void *dict_get_item(struct dict *d, char *key);
Returns a pointer to the key*s value, NULL if key is not found.

    size_t dict_get_size(struct dict *d);
Returns the size of the dictionary.

    #include "src/llist/llist.h"

    void *llist_get_item(struct llist *l, size_t index);
Returns a pointer to element at index, raises an error if index exceeds list's
size.

    size_t llist_get_size(struct llist *l);
Returns the size of the list.

## print the structure

    #include "src/display/display.h"
    #include "src/parser/parser.h"

    void print_data(void *data, enum data_type type);

Prints the structure on standard output.

# Bugs / Todo
-Only integers are supported for numbers.

# Licence
Public domaine

# Authors
Exifers, Dec 2017
