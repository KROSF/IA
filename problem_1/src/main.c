#include <stdio.h>
#include <stdlib.h>

#include "c_printf.h"
#include "log.h"
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
  while (option > 2 || option < 0) {
    c_printf("[y]%s [b]%s\n", "0.", "Initialize board randomly");
    c_printf("[y]%s [b]%s\n", "1.", "Initialize board manually");
    c_printf("[y]%s [b]%s\n", "2.", "Exit");
    scanf("%d", &option);
    clear();
  }
  return option;
}

int handleMenu(int option) {
  int code = 0;
  State initial;
  switch (option) {
    case 0:
      log_warn("Call function to handle random initialization");
      break;
    case 1: {
      initial = state_from_stdin();
      for (size_t i = 0; i < 4; i++) {
        vehicle_display(stdout, &initial.vehicles[i]);
        printf("\n");
      }
    } break;
    case 2:
      break;
    default:
      code = 1;
      break;
  }
  return code;
}

int main() { return handleMenu(menu()); }
