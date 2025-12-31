#pragma once

struct Position {
    int r;
    int c;

    Position(int r = 0, int c = 0) : r(r), c(c) {}

    bool operator==(const Position& other) const {
        return r == other.r && c == other.c;
    }
};
