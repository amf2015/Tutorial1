#include <curses.h>

int main(int argc, char ** argv) {
  // 1. Collects information on the terminal window
  // 2. Allocates memory for the two special WINDOWs `stdscr` and `curscr`
  initscr();
  
  // Prints "Hello, World!" at the current cursor position
  printw("Hello, World!");
  
  // Updates the terminal window to match `stdscr`
  refresh();
  
  // Wait for user input (blocks to allow us to see the output)
  getch()
  
  endwin();
  // Deallocates memory and restores terminal to saved state prior to program runtime
  
  return 0;
}
