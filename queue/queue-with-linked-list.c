#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define btoa(x) ((x) ? "true" : "false")

typedef struct Node
{
  int val;
  struct Node *next;
} Node;

typedef struct Queue
{
  Node *head;
  Node *tail;
  int size;
} Queue;

int enqueue(Queue *q, int value)
{
  Node *node = (Node *)malloc(sizeof(Node));

  if (node == NULL)
  {
    printf("Memory allocation failed \n");
    return -1;
  }

  node->val = value;
  node->next = NULL;

  if (q->head == NULL)
  {
    q->head = node;
    q->tail = node;
  }
  else
  {
    q->tail->next = node;
    q->tail = node;
  }

  q->size += 1;

  return node->val;
}

int dequeue(Queue *q)
{
  if (q->head == NULL)
    return -1;

  Node *node = q->head;
  int value = node->val;

  q->head = q->head->next;
  q->size -= 1;

  free(node);

  return value;
}

bool empty(Queue *q)
{
  return q->head == NULL;
}

int main()
{
  Queue queue = {NULL, NULL, 0};

  printf("Enqueue: %d\n", enqueue(&queue, 1));
  printf("Enqueue: %d\n", enqueue(&queue, 2));
  printf("Enqueue: %d\n", enqueue(&queue, 3));
  printf("Enqueue: %d\n", enqueue(&queue, 4));

  printf("Head: %d\n", queue.head->val);
  printf("Tail: %d\n", queue.tail->val);

  printf("Dequeue: %d\n", dequeue(&queue));
  printf("Dequeue: %d\n", dequeue(&queue));
  printf("Dequeue: %d\n", dequeue(&queue));
  printf("Dequeue: %d\n", dequeue(&queue));
  printf("Dequeue: %d\n", dequeue(&queue));

  printf("Empty: %s\n", btoa(empty(&queue)));

  return 0;
}