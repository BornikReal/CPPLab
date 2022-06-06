#include <iostream>
#include <windows.h>
#include <vector>
#include <ctime>

#pragma once

class Solver;

enum color {
    GREEN, ORANGE, RED, WHITE, YELLOW, BLUE
};

class RubiksCube {
private:
    friend class Solver;

    std::vector<char> dic = {'G', 'O', 'R', 'W', 'Y', 'B'};

    struct corner_cube {
        color front, side, up;

        bool operator==(const corner_cube &rhs) const;

        bool operator>(const corner_cube &rhs) const;
    };

    struct side_cube {
        color front, side;

        bool operator==(const side_cube &rhs) const;

        bool operator>(const side_cube &rhs) const;
    };

    struct middle_cube {
        color front;

        bool operator==(const middle_cube &rhs) const;

        bool operator>(const middle_cube &rhs) const;
    };

    corner_cube FLU_{}, FRU_{}, FLD_{}, FRD_{}, BLU_{}, BRU_{}, BLD_{}, BRD_{};
    side_cube FU_{}, FD_{}, FL_{}, FR_{}, BU_{}, BD_{}, BL_{}, BR_{}, SLU_{}, SLD_{}, SRU_{}, SRD_{};
    middle_cube F_{}, B_{}, L_{}, R_{}, U_{}, D_{};

    static side_cube change_orientation(side_cube inp);

    static corner_cube change_orientation1(corner_cube inp);

    static corner_cube change_orientation2(corner_cube inp);

    static corner_cube change_orientation3(corner_cube inp);

public:
    RubiksCube();

    void R();

    void R2();

    void Rb();

    void L();

    void L2();

    void Lb();

    void U();

    void U2();

    void Ub();

    void D();

    void D2();

    void Db();

    void F();

    void F2();

    void Fb();

    void B();

    void B2();

    void Bb();

    void E();

    void E2();

    void Eb();

    void M();

    void M2();

    void Mb();

    void S();

    void S2();

    void Sb();

    void x();

    void x2();

    void xb();

    void y();

    void y2();

    void yb();

    void z();

    void z2();

    void zb();

    void multpy_com(const std::string &inp);

    void print() const;

    std::string shuffle(int length = 0);

    friend std::istream &operator>>(std::istream &in, RubiksCube &rhs);

    friend std::ostream &operator<<(std::ostream &out, const RubiksCube &rhs);
};