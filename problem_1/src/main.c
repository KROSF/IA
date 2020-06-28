#include <stdio.h>
#include <stdlib.h>

#include "colors.h"
#include "log.h"
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

int handleMenu(int option) {
  int code = 0;
  State initial = state_new((Vehicle[]){{{2, 2}, {3, 3}}, {{2, 0}, {3, 0}}, {{4, 2}, {4, 3}}, {{0, 0}, {0, 0}}}, 8, 4,
                            (Vehicle){{7, 1}, {7, 2}});

  switch (option) {
    case 0:
      log_warn("Call function to handle random initialization");
      break;
    case 1: {
      initial = state_from_stdin();
      a_start_search(&initial);
    } break;
    case 2: {
      state_display(stdout, &initial);
      beam_search(&initial, 4);
      // breadth_first_search(&initial);
    } break;
    case 3:
      break;
    default:
      code = 1;
      break;
  }
  return code;
}

int main() { return handleMenu(menu()); }
