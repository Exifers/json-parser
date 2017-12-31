#include <stddef.h>
#include <ctype.h>
#include <err.h>
#include <stdlib.h>
#include <stdio.h>

#include "parser.h"
#include "../utils/digits.h"

static struct string *parse_string(char *addr, size_t len);
static int *parse_number(char *addr, size_t len);
static struct dict *parse_dict(char *addr, size_t len);
static struct llist *parse_list(char *addr, size_t len);
static void *parse_true(char *addr, size_t len);
static void *parse_false(char *addr, size_t len);
static void *parse_null(char *addr, size_t len);

size_t index;

void eat(char *addr, char c)
{
  if (addr[index] != c)
    errx(1, "Incorrect character at index %zu", index);
  index++;
}

static void skip_blanks(char *addr, size_t len)
{
  while (addr[index] == ' '  ||
         addr[index] == '\t' ||
         addr[index] == '\n')
  {
    index++;
    if (index >= len)
      break;
  }
}

static void *parse_null(char *addr, size_t len)
{
  addr = addr;
  len = len;
  return NULL;
}

static void *parse_false(char *addr, size_t len)
{
  addr = addr;
  len = len;
  return NULL;
}

static void *parse_true(char *addr, size_t len)
{
  addr = addr;
  len = len;
  return NULL;
}

static struct llist *parse_list(char *addr, size_t len)
{
  addr = addr;
  len = len;
  return NULL;
}

static struct dict *parse_dict(char *addr, size_t len)
{
  addr = addr;
  len = len;
  return NULL;
}

static int *parse_number(char *addr, size_t len)
{
  int *res = malloc(sizeof(int));
  if (!res)
    perror(NULL);

  len = len;

  // handles only integers
  sscanf(addr, "%d", res);
  
  index += int_width(*res);

  return res;
}

static struct string *parse_string(char *addr, size_t len)
{
  eat(addr, '"');
  if (index >= len)
    errx(1, "Incorrect format: unterminated string");
  
  char *data = addr;
  size_t str_len = 0;
  while (addr[index] != '"')
  {
    str_len++;
    index++;
    if (index >= len)
      errx(1, "Incorrect format: unterminated string");
  }

  eat(addr, '"');

  struct string *res = malloc(sizeof(struct string));
  if (!res)
    perror(NULL);
  res->data = data;
  res->len = str_len;

  return res;
}

void *parse_json(char *addr, size_t len, enum data_type *type)
{
  index = 0;
  skip_blanks(addr, len);
  if (index >= len)
  {
    *type = EMPTY;
    return NULL;
  }
  else if (addr[index] == '"')
  {
    *type = STRING;
    return parse_string(addr, len);
  }
  else if (isdigit(addr[index]))
  {
    *type = NUMBER;
    return parse_number(addr, len);
  }
  else if (addr[index] == '{')
  {
    *type = DICT;
    return parse_dict(addr, len);
  }
  else if (addr[index] == '[')
  {
    *type = LIST;
    return parse_list(addr, len);
  }
  else if (addr[index] == 't')
  {
    *type = TRUE;
    return parse_true(addr, len);
  }
  else if (addr[index] == 'f')
  {
    *type = FALSE;
    return parse_false(addr, len);
  }
  else if (addr[index] == 'n')
  {
    *type = NUL;
    return parse_null(addr, len);
  }
  errx(1, "Incorrect format: first character is incorrect");
  return NULL;
}
