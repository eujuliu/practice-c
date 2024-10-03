#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

struct Vector
{
  int *raw;
  int size;
  int capacity;
};

int next_power_of_two(int n)
{
  int power = 2;

  while (power < n)
  {
    power *= 2;
  }

  return power;
}

void vector_init(struct Vector *v, int capacity)
{
  capacity = next_power_of_two(capacity);

  v->raw = (int *)malloc(capacity * sizeof(int));

  if (v->raw == NULL)
  {
    perror("Failed to initialize vector data");
    exit(EXIT_FAILURE);
  }

  v->size = 0;
  v->capacity = capacity;
}

char *is_empty(struct Vector *v)
{
  return v->size > 0 ? "true" : "false";
}

int at(struct Vector *v, int index)
{
  if (index > v->size - 1 || index < 0)
  {
    perror("Index out of range");
    exit(EXIT_FAILURE);
  }

  return *(v->raw + index);
}

void resize(struct Vector *v, int new_capacity)
{
  v->raw = (int *)realloc(v->raw, new_capacity * sizeof(int));

  if (v->raw == NULL)
  {
    perror("Failed to realloc vector data");
    exit(EXIT_FAILURE);
  }

  v->capacity = new_capacity;
}

char *list(struct Vector *v)
{
  int buffer_size = v->size * 12;
  char *items = malloc(buffer_size * sizeof(char));

  if (items == NULL)
  {
    perror("Failed to alloc memory for list items");
    exit(EXIT_FAILURE);
  }

  items[0] = '\0';

  for (int i = 0; i < v->size; i++)
  {

    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%d%s", *(v->raw + i), (i == v->size - 1) ? "" : ", ");
    strcat(items, buffer);
  }

  return items;
}

int push(struct Vector *v, int item)
{
  int new_size = v->size + 1;

  if (new_size > v->capacity)
  {
    resize(v, v->capacity * 2);
  }

  v->raw[v->size] = item;
  v->size = new_size;

  return v->raw[v->size - 1];
}

int insert(struct Vector *v, int index, int item)
{
  if (index < 0 || index > v->size)
  {
    perror("Index out of the range");
    exit(EXIT_FAILURE);
  }

  if (v->size == v->capacity)
  {
    resize(v, v->capacity * 2);
  }

  v->size++;

  for (int i = index; i < v->size; i++)
  {
    int data = *(v->raw + i);
    *(v->raw + i) = item;
    item = data;
  }

  return *(v->raw + index);
}

int prepend(struct Vector *v, int item)
{
  insert(v, 0, item);
}

int pop(struct Vector *v)
{
  int removed = *(v->raw + v->size - 1);

  *(v->raw + v->size - 1) = 0;
  v->size = v->size - 1;

  if (v->size <= v->capacity / 4)
  {
    resize(v, v->capacity / 2);
  }

  return removed;
}

int deleteItem(struct Vector *v, int index)
{
  if (index > v->size - 1 || index < 0)
  {
    perror("Index out of range");
    exit(EXIT_FAILURE);
  }

  int removed = *(v->raw + index);

  *(v->raw + index) = 0;

  int last = 0;
  for (int i = v->size - 1; i >= index; i--)
  {
    int crr = *(v->raw + i);
    *(v->raw + i) = last;
    last = crr;
  }

  v->size--;

  if (v->size > 0 && v->size <= v->capacity / 4)
  {
    resize(v, v->capacity / 2);
  }

  return removed;
}

char *removeItem(struct Vector *v, int item)
{
  int removed_count = 0;
  for (int i = 0; i < v->size; i++)
  {
    if (*(v->raw + i) == item)
    {
      deleteItem(v, i);
      removed_count++;
      i--;
    }
  }

  char *message = malloc(50);
  sprintf(message, "%d items are removed from the vector", removed_count);

  return message;
}

int find(struct Vector *v, int item)
{
  for (int i = 0; i < v->size; i++)
  {
    if (*(v->raw + i) == item)
    {
      return i;
    }
  }

  return -1;
}

int main()
{
  struct Vector vector;

  vector_init(&vector, 4);
  printf("size: %d\n", vector.size);
  printf("capacity: %d\n", vector.capacity);
  printf("empty: %s\n", is_empty(&vector));

  for (int i = 0; i < 10; i++)
  {
    push(&vector, i * 2);
  }

  char *list1 = list(&vector);
  printf("list: %s\n", list1);
  free(list1);

  printf("at: %d\n", at(&vector, 9));
  printf("insert: %d\n", insert(&vector, 5, 30));
  printf("prepend: %d\n", prepend(&vector, -1));

  char *list2 = list(&vector);
  printf("list: %s\n", list2);
  free(list2);

  printf("pop: %d\n", pop(&vector));
  printf("delete: %d\n", deleteItem(&vector, 6));

  char *remove_message = removeItem(&vector, 6);
  printf("remove: %s\n", remove_message);
  free(remove_message);

  printf("find in index: %d\n", find(&vector, 4));

  char *list3 = list(&vector);
  printf("list: %s\n", list3);
  free(list3);

  free(vector.raw);
  return 0;
}