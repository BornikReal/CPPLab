#include <iostream>
#include <string>
#include "cube.h"

#pragma once

class Solver {
private:
    RubiksCube *cube_;
    std::string commands;
    const int cycle_limit = 30;

    void white_up();

    void make_white_cross();

    void make_first_layer();

    void make_second_layer();

    void make_yellow_cross();

    void make_yellow_side();

    void put_right_edges();

    void rearranging_corners();

    static std::string optimize_solve(const std::string &inp);

public:
    explicit Solver(RubiksCube *cube);

    int num_of_unresolved();

    void pif_paf();

    void left_pif_paf();

    std::string solve();
};