# json-parser
Quick home-made json parser into C structures. This is some very basic program,
threre's no warranty.

# Prerequisites
GNU/Linux, gcc, make

# How to compile ?
Type 'make', the produced binary is 'main'.

# Usage
'./main \<filename.json\>'
Outputs the formatted json, or raise an error if input is incorrect.

# Include in an existing project
You can remove src/main.c and src/main.h. Everything else in the src/ folder
is needed.

# API
{  } objects are named dictionaries.
[  ] arrays are named llist (for linked lists).

## parse file and free structure

\#include "src/parser/parser.h"

void \*parse\_json(char \*string, size\_t len, enum data\_type &type);
Parses the input string of length len into a C structure whose type is given
by the type variable after calling this function.
The data\_type enum is the following :
    enum data\_type
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


    \#include "src/parser/parser.h"
    \#include "src/free/free.h"

    void free\_data(void \*data, enum data\_type type);
Frees everything returned from parse\_json. data must be the pointer returned
by parse\_json, and type the enum set by parse\_json.

## browse the structure

    \#include "src/dict/dict.h"

    void \*dict\_get\_item(struct dict \*d, char \*key);
Returns a pointer to the key's value, NULL if key is not found.

    size\_t dict\_get\_size(struct dict \*d);
Returns the size of the dictionary.

    \#include "src/llist/llist.h"

    void \*llist\_get\_item(struct llist \*l, size\_t index);
Returns a pointer to element at index, raises an error if index exceeds list's
size.

    size\_t llist\_get\_size(struct llist \*l);
Returns the size of the list.

## print the structure

    \#include "src/display/display.h"
    \#include "src/parser/parser.h"

    void print\_data(void \*data, enum data\_type type);

# Licence
Public domaine

# Authors
Exifers, Dec 2017
