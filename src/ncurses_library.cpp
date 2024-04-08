/*
** EPITECH PROJECT, 2024
** ncurses_create_debut
** File description:
** arcade
*/
#include <ncurses.h>

extern "C" {
    void createWindow()
    {
        initscr();
        clear();
        printw("Ncurses works!");
        refresh();
        getch();
        endwin();
    }
}
