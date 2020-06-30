#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "colors.h"
#include "search.h"
#include "state.h"

void clear() {
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
  system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
  system("cls");
#endif
}

char menu() {
  int option = -1;
  while (option > 3 || option < 0) {
    printf("%s%s %s%s\n", YELLOW, "0.", BLUE, "Initialize board randomly");
    printf("%s%s %s%s\n", YELLOW, "1.", BLUE, "Initialize board manually");
    printf("%s%s %s%s\n", YELLOW, "2.", BLUE, "Default board");
    printf("%s%s %s%s%s\n", YELLOW, "3.", BLUE, "Exit", NORMAL);
    scanf("%d", &option);
    clear();
  }
  return option;
}

void strategies(State* initial) {
  int option = -1;
  while (option > 7 || option < 0) {
    printf("%s%s %s%s\n", YELLOW, "0.", BLUE, "breadth first search (Anchura)");
    printf("%s%s %s%s\n", YELLOW, "1.", BLUE, "depth first search (Profundida)");
    printf("%s%s %s%s\n", YELLOW, "2.", BLUE, "A* (A Estrella)");
    printf("%s%s %s%s\n", YELLOW, "3.", BLUE, "Vorax");
    printf("%s%s %s%s\n", YELLOW, "4.", BLUE, "Beam search [n=2] ( haz local )");
    printf("%s%s %s%s\n", YELLOW, "5.", BLUE, "Beam search [n=4] ( haz local )");
    printf("%s%s %s%s%s\n", YELLOW, "6.", BLUE, "Exit", NORMAL);
    scanf("%d", &option);
    clear();
  }

  switch (option) {
    case 0:
      breadth_first_search(initial);
      break;
    case 1:
      depth_first_search(initial);
      break;
    case 2:
      a_start_search(initial);
      break;
    case 3:
      vorax_search(initial);
      break;
    case 4:
      beam_search(initial, 2);
      break;
    case 5:
      beam_search(initial, 4);
      break;
    default:
      break;
  }
}

int handleMenu(int option) {
  int code = 0;
  State initial = state_new((Vehicle[]){{{2, 2}, {3, 3}}, {{2, 0}, {3, 0}}, {{4, 2}, {4, 3}}, {{0, 0}, {0, 0}}}, 8, 4,
                            (Vehicle){{7, 1}, {7, 2}});

  switch (option) {
    case 0: {
      initial = state_random();
      strategies(&initial);
    } break;
    case 1: {
      initial = state_from_stdin();
      strategies(&initial);
    } break;
    case 2: {
      strategies(&initial);
    } break;
    case 3:
      break;
    default:
      code = 1;
      break;
  }
  return code;
}

int main() {
  srand(time(NULL));
  return handleMenu(menu());
}
