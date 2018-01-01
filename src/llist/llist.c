#include <stdio.h>
#include <stdlib.h>
#include <err.h>

#include "llist.h"

struct llist *llist_init(void)
{
  struct llist *res = malloc(sizeof(struct llist));
  if (!res)
    perror(NULL);

  res->size = 0;
  res->head = NULL;

  return res;
}

void llist_append(struct llist *l, LLIST_DATA_TYPE data
                  #if LLIST_ADD_TYPE_ENUM == 1
                  , LLIST_TYPE_ENUM type
                  #endif
                  )
{
  if (!l)
    errx(1, "linked list is NULL");

  struct llist_elt *new = malloc(sizeof(struct llist_elt));
  if (!new)
    perror(NULL);
  new->data = data;
  new->next = NULL;
  #if LLIST_ADD_TYPE_ENUM == 1
  new->type = type;
  #endif

  struct llist_elt *cur = l->head;
  if (!cur)
  {
    l->head = new;
    l->size++;
    return;
  }
  while (cur->next)
    cur = cur->next;
  cur->next = new;
  l->size++;
}

LLIST_DATA_TYPE llist_pop(struct llist *l)
{
  if (!l)
    errx(1, "linked list is NULL");

  struct llist_elt *cur = l->head;

  if (!cur)
    return LLIST_NULL_DATA;

  if (!cur->next)
  {
    LLIST_DATA_TYPE ret = cur->data;
    #if LLIST_FREE_DATA != 0
    free(cur->data);
    #endif
    free(cur);
    l->head = NULL;
    l->size--;
    return ret;
  }

  while(cur->next->next)
    cur = cur->next;
  LLIST_DATA_TYPE ret = cur->next->data;
  #if LLIST_FREE_DATA != 0
  free(cur->next->data);
  #endif
  free(cur->next);
  cur->next = NULL;
  l->size--;

  return ret;
}

LLIST_DATA_TYPE llist_get_item(struct llist *l, size_t index)
{
  if (!l)
    errx(1, "linked list is NULL");

  if (index >= l->size)
    errx(1, "list index out of range");

  struct llist_elt *cur = l->head;
  for (size_t i = 0; i < index; i++)
    cur = cur->next;

  return cur->data;
}

size_t llist_get_size(struct llist *l)
{
  if (!l)
    errx(1, "linked list is NULL");

  return l->size;
}

void llist_free(struct llist *l)
{
  if (!l)
    errx(1, "linked list is NULL");

  size_t size = l->size;
  for (size_t i = 0; i < size; i++)
    llist_pop(l);
  free(l);
}

static void print_offset(int offset)
{
  for (int i = 0; i < offset; i++)
    printf(" ");
}

void llist_print(struct llist *l, int offset, int inc,
     void (*print_fun)(LLIST_DATA_TYPE data, enum data_type type, int offset))
{
  if (!l)
    errx(1, "linked list is NULL");

  if (l->size == 0)
  {
    printf("empty linked list\n");
    return;
  }

  struct llist_elt *cur = l->head;
  print_offset(offset);
  printf("[\n");
  for (size_t i = 0; i < l->size; i++)
  {
    print_fun(cur->data, cur->type, offset + inc);
    if (i != l->size - 1)
      printf(",");
    printf("\n");
    cur = cur->next;
  }
  print_offset(offset);
  printf("]");
}
