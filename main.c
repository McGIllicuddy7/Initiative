#define COG_IMPLEMENTATION
#include "cog.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#define BUFFERSIZE 1024
typedef struct {
  String name;
  int count;
} initType;
typedef struct {
  String name;
  int bonus;
  int count;
} monsterType;
void print_init_type(initType init) {
  printf("%ls: %d\n", init.name.arr, init.count);
}
enable_slice_type(initType);
int cmp_init(const void *a, const void *b) {
  return ((initType *)b)->count - ((initType *)a)->count;
}
void initiative_sort(initTypeSlice slice) {
  qsort(slice.arr, len(slice), sizeof(initType), cmp_init);
}
bool is_valid_int(char *str) {
  while (*str == ' ') {
    str++;
  }
  if (*str == '-') {
    str++;
  }
  while (*str != 0) {
    if (!isdigit(*str)) {
      return false;
    }
    str++;
  }
  return true;
}
void remove_new_lines(char *str) {
  while (*str != 0) {
    if (*str == '\n') {
      *str = 0;
      break;
    }
    str++;
  }
}
initTypeSlice parse_initiatives(Arena *arena) {
  initTypeSlice out = make(initType, arena);
  while (0 == 0) {
    char namebuf[BUFFERSIZE];
    printf("enter character name or end to end: ");
    fgets(namebuf, BUFFERSIZE - 1, stdin);
    remove_new_lines(namebuf);
    if (namebuf[0] == 'e' && namebuf[1] == 'n' && namebuf[2] == 'd' &&
        namebuf[3] == '\0') {
      break;
    }
    char buffer[BUFFERSIZE];
    printf("enter initiative number: ");
    fgets(buffer, BUFFERSIZE - 1, stdin);
    remove_new_lines(buffer);
    if (!is_valid_int(buffer)) {
      printf("please enter a valid initiative count\n");
      continue;
    }
    String name = new_string(arena, namebuf);
    int count = atoi(buffer);
    initType init = {name, count};
    append(out, init);
  }
  return out;
}
initTypeSlice parse_monsters(Arena *arena) {
  Arena *local = init_arena();
  srand(time(0));
  initTypeSlice out = make(initType, arena);
  while (0 == 0) {
    char namebuf[BUFFERSIZE];
    printf("enter monster name or end to end: ");
    fgets(namebuf, BUFFERSIZE - 1, stdin);
    remove_new_lines(namebuf);
    if (namebuf[0] == 'e' && namebuf[1] == 'n' && namebuf[2] == 'd' &&
        namebuf[3] == '\0') {
      break;
    }
    char buffer[BUFFERSIZE];
    printf("enter initiative bonus: ");
    fgets(buffer, BUFFERSIZE - 1, stdin);
    remove_new_lines(buffer);
    if (!is_valid_int(buffer)) {
      printf("please enter a valid initiative bonus\n");
      continue;
    }
    int bonus = atoi(buffer);
    printf("enter amount of monsters: ");
    fgets(buffer, BUFFERSIZE - 1, stdin);
    remove_new_lines(buffer);
    if (!is_valid_int(buffer)) {
      printf("please enter a valid amount\n");
      continue;
    }
    int count = atoi(buffer);
    String name = new_string(local, namebuf);
    for (int i = 0; i < count; i++) {
      int tmp = rand() % 20 + bonus;
      String tmp_name = string_format(arena, "%ls %d", name.arr, i + 1);
      initType init = {tmp_name, tmp};
      append(out, init);
    }
  }
  free_arena(local);
  return out;
}
int main() {
  Arena *local = init_arena();
  initTypeSlice base = parse_monsters(local);
  initTypeSlice inits = parse_initiatives(local);
  append_slice(inits, base);
  initiative_sort(inits);
  for (int i = 0; i < len(inits); i++) {
    print_init_type(array(inits)[i]);
  }
  free_arena(local);
}
