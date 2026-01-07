#pragma once

struct Position {
    int r;
    int c;

    explicit Position(int r_ = 0, int c_ = 0) : r(r_), c(c_) {}
};

inline bool operator==(const Position& a, const Position& b) {
    return a.r == b.r && a.c == b.c;
}