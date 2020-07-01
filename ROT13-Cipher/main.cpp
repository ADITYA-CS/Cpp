/*
 *  Simple ROT13 encrypter and decrypter using ncurses library
 */


#include <ncurses.h>
#include <iostream>
#include <cstring>

using namespace std;

void welcome(const int &, const int &) ;
pair<WINDOW*, WINDOW*> SetupScreen();
void SetupPlainScreen();
void SetupCipherScreen();
void Failure();
void SetupPlainScreen(WINDOW *, const int &rows,const int &cols);
void SetupCipherScreen(WINDOW *, const int &rows,const int &cols);
void Cipher(pair<WINDOW*, WINDOW*>);

int main () {

    auto window = SetupScreen();
    Cipher(window);
    endwin();
    return 0;
}
/*
 * return two WINDOW struct pointer,
 * First point to plain text screen
 * other point to cipher text screen
 */
pair<WINDOW*, WINDOW*> SetupScreen() {
    WINDOW *plain, *cipher;
    initscr();

    start_color();
    init_pair(1,COLOR_RED,COLOR_BLACK);
    init_pair(2,COLOR_WHITE,COLOR_BLACK);

    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    welcome(rows, cols);

    if ((plain = newwin(rows, cols/2, 0, 0)) == NULL)
        Failure();

    if((cipher = newwin(rows, cols/2, 0, cols/2)) == NULL)
        Failure();

    SetupPlainScreen(plain,rows, cols/2);
    SetupCipherScreen(cipher,rows, cols/2);
    return {plain, cipher};
}

/*
 *  Prints welcoming message
 */
void welcome(const int &rows, const int &cols) {
    char welcome_message[] = "Welcome to ROT13";
    attron(A_BOLD);
    mvaddstr(rows/2, (cols - strlen(welcome_message))/2, welcome_message);
    attroff(A_BOLD);

    char instruction[] = "Press any key to Enter";
    attron(A_DIM);
    mvaddstr(rows/2+1, (cols - strlen(instruction))/2, instruction);
    attroff(A_DIM);
    refresh();
    getch();
}
/*
 *  Exit the programming
 */
void Failure() {
    addstr("Unable to allocate memory for new window\n");
    refresh();
    endwin();
    exit(1);
}

/*
 *  Setup plain text screen
 */
void SetupPlainScreen(WINDOW *plain, const int &rows,const int &cols) {
    char heading[] = "Plain Text";
    wbkgd(plain, COLOR_PAIR(1));
    mvwaddstr(plain, 0, (cols - strlen(heading)) / 2, heading);
    for(int  i = 0; i < cols-1; i++) {
        mvwaddch(plain, 1,i,'-');
    }
    wrefresh(plain);
}

/*
 *  Setup cipher text screen
 */
void SetupCipherScreen(WINDOW *cipher, const int &rows,const int &cols) {
    char heading[] = "Cipher Text";
    wbkgd(cipher, COLOR_PAIR(2));
    mvwaddstr(cipher, 0, (cols - strlen(heading)) / 2, heading);
    for(int  i = 0; i < cols; i++) {
        mvwaddch(cipher, 1,i,'-');
    }
    wrefresh(cipher);
}

/*
 *  Encrypt only english alphabets
 */
void Cipher(pair<WINDOW*, WINDOW*> win) {
    auto plain = win.first, cipher  = win.second;
    keypad(plain, TRUE);
    wmove(plain, 2, 0);
    wmove(cipher, 2, 0);
    wrefresh(plain);
    wrefresh(cipher);
    int ch;
    do {
        ch = wgetch(plain);
        if (ch >= 'a' && ch <= 'z') {
            ch = (ch - 'a' + 13) % 26 + 'a';
            waddch(cipher, ch);
        } else if (ch >= 'A' && ch <= 'Z') {
            ch = (ch - 'A' + 13) % 26 + 'A';
            waddch(cipher, ch);
        } else {
            waddch(cipher, ch);
        }
        wrefresh(cipher);
    } while (ch != '~');
}
