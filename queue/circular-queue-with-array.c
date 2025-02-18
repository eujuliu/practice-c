#include <stdio.h>
#include <stdbool.h>

#define btoa(x) ((x) ? "true" : "false")
#define SIZE 10

typedef struct Queue
{
  int values[SIZE];
  int capacity;
  int front, rear;
} Queue;

bool empty(Queue *q)
{
  return q->front == -1;
}

bool full(Queue *q)
{
  return (q->rear + 1) % SIZE == q->front;
}

int enqueue(Queue *q, int value)
{
  if (full(q))
    return -1;

  if (q->front == -1)
  {
    q->front = 0;
  }

  q->rear = (q->rear + 1) % SIZE;
  q->values[q->rear] = value;

  printf("%d\n", q->rear);

  return q->values[q->rear];
}

int dequeue(Queue *q)
{
  if (empty(q))
    return -1;

  int value = q->values[q->front];

  if (q->front == q->rear)
  {
    q->front = q->rear = -1;
  }
  else
  {
    q->front = (q->front + 1) % SIZE;
  }

  return value;
}

int main()
{
  Queue queue = {{[0 ... SIZE - 1] = -1}, SIZE, -1, -1};

  printf("Enqueue: %d\n", enqueue(&queue, 1));
  printf("Enqueue: %d\n", enqueue(&queue, 2));
  printf("Enqueue: %d\n", enqueue(&queue, 3));
  printf("Enqueue: %d\n\n", enqueue(&queue, 4));

  printf("Full: %s\n\n", btoa(full(&queue)));

  printf("Dequeue: %d\n", dequeue(&queue));
  printf("Dequeue: %d\n", dequeue(&queue));
  printf("Dequeue: %d\n", dequeue(&queue));
  printf("Dequeue: %d\n", dequeue(&queue));
  printf("Dequeue: %d\n\n", dequeue(&queue));

  printf("Empty: %s\n", btoa(empty(&queue)));

  return 0;
}