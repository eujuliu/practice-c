#include <stdio.h>
#include <stdbool.h>

#define btoa(x) ((x) ? "true" : "false")

typedef struct Stack
{
  int values[10];
  int size;
  int capacity;
} Stack;

bool empty(Stack *s)
{
  return s->size < 1;
}

int push(Stack *s, int value)
{
  if (s->size == s->capacity)
  {
    printf("Max stack capacity exceeded! Please peek a value");
    return -1;
  }

  s->values[s->size] = value;
  s->size += 1;

  return s->values[s->size - 1];
}

int pop(Stack *s)
{
  int result = s->values[s->size - 1];

  s->values[s->size - 1] = 0;
  s->size -= 1;

  return result;
}

int peek(Stack *s)
{
  int result = s->values[s->size - 1];

  return result;
}

int main()
{
  Stack stack;
  stack.size = 0;
  stack.capacity = 10;

  printf("Push: %d\n", push(&stack, 1));
  printf("Push: %d\n", push(&stack, 2));
  printf("Push: %d\n", push(&stack, 3));
  printf("Push: %d\n", push(&stack, 4));
  printf("Push: %d\n", push(&stack, 5));

  printf("Pop: %d\n", pop(&stack));
  printf("Pop: %d\n", pop(&stack));
  printf("Pop: %d\n", pop(&stack));

  printf("Peek: %d\n", pop(&stack));

  printf("Size: %d\n", stack.size);
  printf("Empty: %s\n", btoa(empty(&stack)));

  return 0;
}