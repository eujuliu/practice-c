#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define btoa(x) ((x) ? "true" : "false")

typedef struct Node
{
  int val;
  struct Node *next;
} Node;

typedef struct LinkedList
{
  Node *head;
  Node *tail;
  int size;
} LinkedList;

bool empty(LinkedList *ll)
{
  return ll->head == NULL;
}

void append(LinkedList *ll, int val)
{
  Node *node = (Node *)malloc(sizeof(Node)); // Will persist after function finish

  if (node == NULL)
  {
    printf("Memory allocation failed \n");
    return;
  }

  node->val = val;
  node->next = NULL;

  if (ll->head == NULL)
  {
    ll->head = node;
    ll->tail = node;
  }
  else
  {
    ll->tail->next = node;
    ll->tail = node;
  }

  ll->size += 1;
}

void pop(LinkedList *ll)
{
  if (ll->head == NULL)
    return;

  Node *last;
  Node *current = ll->head;

  while (current->next != NULL)
  {
    last = current;
    current = current->next;
  }

  last->next = NULL;
  ll->tail = last;
  ll->size -= 1;

  free(current);
}

void unshift(LinkedList *ll, int val)
{
  Node *node = (Node *)malloc(sizeof(Node));

  node->val = val;
  node->next = ll->head;

  ll->head = node;
  ll->size += 1;
}

void shift(LinkedList *ll)
{
  Node *node;
  Node *old = ll->head;

  node = ll->head->next;
  ll->head = node;
  ll->size -= 1;

  free(old);
}

int front(LinkedList *ll)
{
  return ll->head != NULL ? ll->head->val : -1;
}

int back(LinkedList *ll)
{
  return ll->tail != NULL ? ll->tail->val : -1;
}

int at(LinkedList *ll, int index)
{
  if (ll->head == NULL || index > ll->size - 1)
  {
    return -1;
  }

  Node *node = ll->head;

  for (int i = 0; i < ll->size; i++)
  {
    if (i == index)
    {
      return node->val;
    }

    node = node->next;
  }

  return -1;
}

void insert(LinkedList *ll, int index, int val)
{
  Node *last = NULL;
  Node *current = ll->head;

  if (index == 0)
    unshift(ll, val);
  if (index == -1)
    append(ll, val);

  for (int i = 0; i < ll->size; i++)
  {
    if (i > index)
      break;

    if (i == index)
    {
      Node *newNode = (Node *)malloc(sizeof(Node));

      newNode->val = val;
      newNode->next = current;

      last->next = newNode;
      ll->size += 1;
    }

    last = current;
    current = current->next;
  }
}

char *values(LinkedList *ll)
{
  int bufferSize = ll->size * 10;
  char *result = (char *)malloc(bufferSize * sizeof(char));

  if (result == NULL)
  {
    printf("Memory allocation failed!\n");
    return NULL;
  }

  result[0] = '\0';

  Node *node = ll->head;
  while (node != NULL)
  {
    char temp[20];
    sprintf(temp, "%d", node->val);
    strcat(result, temp);

    if (node != NULL)
    {
      strcat(result, " -> ");
    }

    node = node->next;
  }

  strcat(result, "NULL");

  return result;
}

void erase(LinkedList *ll, int index)
{
  Node *last;
  Node *current = ll->head;

  for (int i = 0; i < ll->size; i++)
  {
    if (i == index)
    {
      last->next = current->next;
      ll->size -= 1;
      break;
    }

    last = current;
    current = current->next;
  }

  free(current);
}

void removeValue(LinkedList *ll, int value)
{
  Node *last;
  Node *current = ll->head;

  while (current != NULL)
  {
    if (current->val == value)
    {
      last->next = current->next;
      ll->size -= 1;

      break;
    }

    last = current;
    current = current->next;
  }

  free(current);
}

LinkedList *reverse(LinkedList *ll)
{
  Node *curr = ll->head;
  Node *prev = NULL;
  Node *next = NULL;

  ll->tail = curr;

  while (curr != NULL)
  {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }

  ll->head = prev;

  return ll;
}

int valueNFromEnd(LinkedList *ll, int n)
{
  if (n < 0)
    return -1;

  int target = (ll->size - n);

  if (target < 0)
    return -1;

  Node *node = ll->head;
  for (int i = 0; i < target; i++)
  {
    node = node->next;
  }

  return node->val;
}

int main()
{
  LinkedList ll = {NULL, NULL, 0};
  append(&ll, 3);
  append(&ll, 8);
  append(&ll, 6);
  append(&ll, 2);
  append(&ll, 4);
  append(&ll, 9);

  pop(&ll);
  unshift(&ll, 0);
  shift(&ll);
  printf("Front: %d\n", front(&ll));
  printf("Back: %d\n", back(&ll));

  int index = 4;
  printf("at (%d): %d\n", index, at(&ll, index));
  insert(&ll, index, 10);

  printf("Size: %d\n", ll.size);
  printf("Empty: %s\n", btoa(empty(&ll)));
  printf("at (%d): %d\n", index, at(&ll, index));
  erase(&ll, index);
  removeValue(&ll, 6);

  printf("values: %s\n", values(&ll));

  printf("reverse values: %s\n", values(reverse(&ll)));
  printf("value n from end: %d\n", valueNFromEnd(&ll, 1));

  return 0;
}