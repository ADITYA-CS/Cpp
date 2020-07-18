#include <iostream>
#include <ncurses.h>
#include <cstring>

using namespace std;
#define FORGROUND_BACKGROUND_COLOR 1
#define SEARCH_FB_COLOR 2
#define DEFINITION_FB_COLOR 3
#define TEXT_COLOR 4

void Setup();
void Color();
WINDOW * SearchWindow();
WINDOW * DefinitionWindow();
void WriteToDefinition(char *, WINDOW *);
string ReadFromSearch(WINDOW *);
string CharToString(char *);
void WriteInCenter(WINDOW *, int, int, char *);

int main() {
  Setup();
  auto def = DefinitionWindow();
  auto search = SearchWindow();
  char srch[80];
  ReadFromSearch(search);
  char definition[] = "1.fond of the company of others; sociable.\n2.living in flocks or herds, as animals.";
  WriteToDefinition(definition, def);
  wgetch(search);
  wrefresh(search);
  endwin();
}

void Setup() {
  initscr();
  start_color();
  Color();
  bkgd(COLOR_PAIR(FORGROUND_BACKGROUND_COLOR));
  box(stdscr, 0, 0);
  refresh();
}

void Color() {
  init_pair(FORGROUND_BACKGROUND_COLOR, COLOR_CYAN, COLOR_BLACK);
  init_pair(SEARCH_FB_COLOR, COLOR_CYAN, COLOR_BLACK);
  init_pair(DEFINITION_FB_COLOR, COLOR_CYAN, COLOR_BLACK);
  init_pair(TEXT_COLOR, COLOR_CYAN, COLOR_BLACK);
}

WINDOW * SearchWindow() {
  int rows, cols;
  getmaxyx(stdscr, rows, cols);

  int width = 2 * cols / 3;
  int height = 3;
  int lcr = 4; // left corner row
  int lcc = cols / 3 - cols / 6; // left corner column
  WINDOW * search = subwin(stdscr, height, width, lcr, lcc);
  wbkgd(search, COLOR_PAIR(SEARCH_FB_COLOR));
  box(search, 0, 0);
  char message[] = " Search ";
  WriteInCenter(search, 0, width, message);
  wrefresh(search);
  return search;
}

WINDOW * DefinitionWindow() {
  int rows, cols;
  getmaxyx(stdscr, rows, cols);

  int width = 2 * cols / 3;
  int height = 2 * rows / 3;
  int lcr = 8; // left corner row
  int lcc = cols / 3 - cols / 6; // left corner column
  WINDOW * def = subwin(stdscr, height, width, lcr, lcc);
  wbkgd(def, COLOR_PAIR(DEFINITION_FB_COLOR));
  box(def, 0, 0);

  char message[] = " Definition ";
  WriteInCenter(def, 0, width, message);
  wrefresh(def);
  return def;
}

void WriteToDefinition(char *str, WINDOW *win) {
  int rows, cols;
  int len = strlen(str);
  getmaxyx(win, rows, cols);
  wmove(win, 1, 1);
  curs_set(0);
  for (int i = 0, R = 1, c, r; i < len; i++) {
    if(str[i] == '\n') {
      wmove(win, ++R, 1);
      continue;
    }
    getyx(win, r, c);
    if(c == cols - 1)
      wmove(win, ++R, 1);
    waddch(win, str[i]);
    wrefresh(win);
  }
}

void WriteInCenter(WINDOW *win, int rows, int cols, char *str) {
    int len = strlen(str);
    mvwaddstr(win, rows, (cols - len) / 2, str);
    wrefresh(win);
}

string ReadFromSearch(WINDOW *win) {
  curs_set(1);
  char str[1000];
  wmove(win, 1, 1);
  wgetstr(win, str);
  return CharToString(str);
}

string CharToString(char * str) {
  int len = strlen(str);
  string res;
  for (int i = 0; i < len; i++) {
    res += str[i];
  }
  return res;
}
