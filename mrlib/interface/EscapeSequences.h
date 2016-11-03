//
// EscapeSequences.h
// mrlib
//
// Created by Matthew Remmel on 10/2/16.
// Copyright (c) 2015 Matthew Remmel. All rights reserved.

/*
 * The purpose of the file is to define a set of useful functions and
 * macros for interacting with a POSIX terminal screen using ANSI codes.
 */


#ifndef MRLIB_ESCAPESEQUENCES_H
#define MRLIB_ESCAPESEQUENCES_H

#include <stdio.h>
#include <sys/ioctl.h>

// Convenience Macros
#define update_screen(x) printf(x);
#define print_line(x) printf(x + '\n');

// Control Sequence Initiator
#define CSI                     "\033["

// Formatted Escape Codes
#define _EraseDisplay           "%s%s", CSI, "2J"
#define _EraseLine              "%s%s", CSI, "2K"
#define _ResetCursor            "%s%s", CSI, "H"
#define _ResetCursorLeft        "%s%s", CSI, "1G"
#define _CursorUp(n)            "%s%d%s", CSI, n, "A"
#define _CursorDown(n)          "%s%d%s", CSI, n, "B"
#define _CursorRight(n)         "%s%d%s", CSI, n, "C"
#define _CursorLeft(n)          "%s%d%s", CSI, n, "D"
#define _CursorPosition(r, c)   "%s%d;%d%s", CSI, r, c, "H"
#define _NextLine(n)            "%s%d%s", CSI, n, "E"
#define _PreviousLine(n)        "%s%d%s", CSI, n, "F"
#define _HideCursor             "%s%s", CSI, "?25l"
#define _ShowCursor             "%s%s", CSI, "?25h"
#define _ScrollUp(n)            "%s%d%s", CSI, n, "S"
#define _ScrollDown(n)          "%s%d%s", CSI, n, "T"


// Functions
inline
void clearDisplay() {
    update_screen(_EraseDisplay);
    update_screen(_ResetCursor);
}

inline
void resetCursor() {
    update_screen(_ResetCursor);
}

inline
void clearLine() {
    update_screen(_EraseLine);
    update_screen(_ResetCursorLeft);
}

inline
void cursorToPosition(unsigned short row = 1, unsigned short column = 1) {
    update_screen(_CursorPosition(row, column));
}

inline
void cursorDown(int n = 1) {
    update_screen(_CursorUp(n));
}

inline
void cursorDown(int n = 1) {
    update_screen(_CursorDown(n));
}

inline
void cursorLeft(int n = 1) {
    update_screen(_CursorLeft(n));
}

inline
void cursorRight(int n = 1) {
    update_screen(_CursorRight(n));
}

inline
unsigned short getScreenHeight() {
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    return w.ws_row;
}

inline
unsigned short getScreenWidth() {
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    return w.ws_col;
}

#endif //MRLIB_ESCAPESEQUENCES_H