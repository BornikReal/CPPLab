#include "solver.h"

void Solver::white_up() {
    if (cube_->F_.front == WHITE) {
        cube_->x();
        commands += "x ";
    } else if (cube_->B_.front == WHITE) {
        cube_->xb();
        commands += "x' ";
    } else if (cube_->R_.front == WHITE) {
        cube_->zb();
        commands += "z' ";
    } else if (cube_->L_.front == WHITE) {
        cube_->z();
        commands += "z ";
    } else if (cube_->D_.front == WHITE) {
        cube_->x2();
        commands += "x2 ";
    }
}

void Solver::make_white_cross() {
    white_up();
    int cycle = 0;
    while (!(cube_->FU_.side == WHITE && cube_->BU_.side == WHITE && cube_->SRU_.side == WHITE &&
             cube_->SLU_.side == WHITE)) {
        if (cube_->FU_.front == WHITE) {
            cube_->F();
            commands += "F ";
            while (cube_->SRU_.side == WHITE) {
                cube_->U();
                commands += "U ";
            }
            cube_->R();
            commands += "R ";
        }
        if (cube_->FD_.front == WHITE) {
            cube_->F();
            commands += "F ";
            while (cube_->SLU_.side == WHITE) {
                cube_->U();
                commands += "U ";
            }
            cube_->Rb();
            commands += "R' ";
        }
        if (cube_->FD_.side == WHITE) {
            while (cube_->FU_.side == WHITE) {
                cube_->U();
                commands += "U ";
            }
            cube_->F2();
            commands += "F2 ";
        }
        if (cube_->FL_.front == WHITE) {
            while (cube_->SLU_.side == WHITE) {
                cube_->U();
                commands += "U ";
            }
            cube_->Lb();
            commands += "L' ";
        }
        if (cube_->FR_.front == WHITE) {
            while (cube_->SRU_.side == WHITE) {
                cube_->U();
                commands += "U ";
            }
            cube_->R();
            commands += "R ";
        }
        cube_->y();
        commands += "y ";
        ++cycle;
        if (cycle == cycle_limit)
            throw std::runtime_error("The cube is unsolvable");
    }
    cycle = 0;
    int num = 0;
    while (num != 2 && num != 4) {
        num = 0;
        cube_->U();
        commands += "U ";
        for (int i = 0; i < 4; ++i) {
            if (cube_->FU_.front == cube_->F_.front)
                ++num;
            cube_->y();
            commands += "y ";
        }
        ++cycle;
        if (cycle == cycle_limit)
            throw std::runtime_error("The cube is unsolvable");
    }
    if (num == 4)
        return;
    cube_->y();
    commands += "y ";
    cycle = 0;
    while (cube_->FU_.front != cube_->F_.front) {
        cube_->yb();
        commands += "y' ";
        ++cycle;
        if (cycle == cycle_limit)
            throw std::runtime_error("The cube is unsolvable");
    }
    if (cube_->BU_.front == cube_->B_.front) {
        pif_paf();
        cube_->R();
        commands += "R ";
        num = 0;
        cycle = 0;
        while (num != 2 && num != 4) {
            num = 0;
            cube_->U();
            commands += "U ";
            for (int i = 0; i < 4; ++i) {
                if (cube_->FU_.front == cube_->F_.front)
                    ++num;
                cube_->y();
                commands += "y ";
            }
            ++cycle;
            if (cycle == cycle_limit)
                throw std::runtime_error("The cube is unsolvable");
        }
        if (num == 4)
            return;
        cube_->y();
        commands += "y ";
        cycle = 0;
        while (cube_->FU_.front != cube_->F_.front) {
            cube_->yb();
            commands += "y' ";
            ++cycle;
            if (cycle == cycle_limit)
                throw std::runtime_error("The cube is unsolvable");
        }
        pif_paf();
        cube_->R();
        commands += "R ";
    } else {
        if (cube_->SRU_.front == cube_->R_.front) {
            cube_->y();
            commands += "y ";
        }
        pif_paf();
        cube_->R();
        commands += "R ";
    }
}

void Solver::make_first_layer() {
    cube_->x2();
    commands += "x2 ";
    bool d = true;
    int cycle = 0;
    while (d) {
        d = false;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                RubiksCube::corner_cube temp = {cube_->F_.front, cube_->R_.front, WHITE};
                if (cube_->FRU_ == temp || cube_->FRU_ == RubiksCube::change_orientation1(temp) ||
                    cube_->FRU_ == RubiksCube::change_orientation2(temp) ||
                    cube_->FRU_ == RubiksCube::change_orientation3(temp)) {
                    d = true;
                    int cycle1 = 0;
                    while (cube_->FRD_.up != WHITE) {
                        pif_paf();
                        ++cycle1;
                        if (cycle1 == cycle_limit)
                            throw std::runtime_error("The cube is unsolvable");
                    }
                }
                if (cube_->FRD_.front == WHITE || cube_->FRD_.side == WHITE ||
                    (cube_->FRD_.up == WHITE && cube_->FRD_.front != cube_->F_.front &&
                     cube_->FRD_.side != cube_->R_.front)) {
                    d = true;
                    pif_paf();
                }
                cube_->U();
                commands += "U ";
            }
            cube_->y();
            commands += "y ";
        }
        ++cycle;
        if (cycle == cycle_limit)
            throw std::runtime_error("The cube is unsolvable");
    }
}

void Solver::make_second_layer() {
    bool d = true;
    int cycle = 0;
    while (d) {
        d = false;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (cube_->FU_.front == cube_->F_.front) {
                    if (cube_->FU_.side == cube_->R_.front) {
                        d = true;
                        cube_->U();
                        commands += "U ";
                        pif_paf();
                        cube_->y();
                        commands += "y ";
                        left_pif_paf();
                        cube_->yb();
                        commands += "y' ";
                    } else if (cube_->FU_.side == cube_->L_.front) {
                        d = true;
                        cube_->Ub();
                        commands += "U' ";
                        left_pif_paf();
                        cube_->yb();
                        commands += "y' ";
                        pif_paf();
                        cube_->y();
                        commands += "y ";
                    }
                }
                if ((cube_->FR_.front != cube_->F_.front || cube_->FR_.side != cube_->R_.front) &&
                    cube_->FR_.front != YELLOW &&
                    cube_->FR_.side != YELLOW) {
                    d = true;
                    pif_paf();
                    cube_->y();
                    commands += "y ";
                    left_pif_paf();
                    cube_->yb();
                    commands += "y' ";
                }
                cube_->U();
                commands += "U ";
            }
            cube_->y();
            commands += "y ";
        }
        ++cycle;
        if (cycle == cycle_limit)
            throw std::runtime_error("The cube is unsolvable");
    }
}

void Solver::make_yellow_cross() {
    if ((cube_->SLU_.side == YELLOW) && (cube_->SRU_.side == YELLOW) && (cube_->BU_.side == YELLOW) &&
        (cube_->FU_.side == YELLOW))
        return;
    int num = 0;
    while (!((cube_->SLU_.side == YELLOW) && ((cube_->SRU_.side == YELLOW) || (cube_->BU_.side == YELLOW)))) {
        cube_->U();
        commands += "U ";
        num++;
        if (num == 5)
            break;
    }
    if (num == 5) {
        cube_->F();
        commands += "F ";
        pif_paf();
        cube_->Fb();
        commands += "F' ";
        cube_->U2();
        commands += "U2 ";
        cube_->F();
        commands += "F ";
        pif_paf();
        pif_paf();
        cube_->Fb();
        commands += "F' ";
    } else if ((cube_->SLU_.side == YELLOW) && (cube_->SRU_.side == YELLOW)) {
        cube_->F();
        commands += "F ";
        pif_paf();
        cube_->Fb();
        commands += "F' ";
    } else {
        cube_->F();
        commands += "F ";
        pif_paf();
        pif_paf();
        cube_->Fb();
        commands += "F' ";
    }
}

void Solver::make_yellow_side() {
    cube_->zb();
    commands += "z' ";
    for (int i = 0; i < 5; ++i) {
        if (cube_->BLU_.up == YELLOW) {
            for (int j = 0; j < 4; ++j)
                pif_paf();
        } else if (cube_->BLU_.front == YELLOW) {
            for (int j = 0; j < 2; ++j)
                pif_paf();
        }
        cube_->Lb();
        commands += "L' ";
    }
}

void Solver::put_right_edges() {
    cube_->z();
    commands += "z ";
    int num = 0, cycle = 0;
    while (num != 2 && num != 4) {
        num = 0;
        cube_->U();
        commands += "U ";
        for (int i = 0; i < 4; ++i) {
            if (cube_->FU_.front == cube_->F_.front)
                ++num;
            cube_->y();
            commands += "y ";
        }
        ++cycle;
        if (cycle == cycle_limit)
            throw std::runtime_error("The cube is unsolvable");
    }
    if (num == 4)
        return;
    cycle = 0;
    while (cube_->FU_.front != cube_->F_.front) {
        cube_->yb();
        commands += "y' ";
        ++cycle;
        if (cycle == cycle_limit)
            throw std::runtime_error("The cube is unsolvable");
    }
    if (cube_->R_.front == cube_->SRU_.front) {
        cube_->y();
        commands += "y ";
    }
    if (cube_->BU_.front == cube_->B_.front) {
        cube_->multpy_com("R U R' F' R U R' U' R' F R2 U' R' U' U2 R U R' F' R U R' U' R' F R2 U' R' U' U'");
        commands += "R U R' F' R U R' U' R' F R2 U' R' U' U2 R U R' F' R U R' U' R' F R2 U' R' U' U' ";
    } else {
        cube_->y();
        commands += "y ";
        cube_->multpy_com("R U R' F' R U R' U' R' F R2 U' R' U'");
        commands += "R U R' F' R U R' U' R' F R2 U' R' U' ";
    }
}

void Solver::rearranging_corners() {
    cube_->zb();
    commands += "z' ";
    int cycle = 0;
    while (num_of_unresolved() != 0) {
        for (int i = 0; i < 5; ++i) {
            cube_->x();
            commands += "x ";
            if (cube_->FLD_.front == cube_->F_.front && cube_->FLD_.up == cube_->D_.front)
                break;
        }
        cube_->xb();
        commands += "x' ";
        cube_->multpy_com("U2 R U2 R' F2 U2 L' U2 L F2");
        commands += "U2 R U2 R' F2 U2 L' U2 L F2 ";
        ++cycle;
        if (cycle == cycle_limit)
            throw std::runtime_error("The cube is unsolvable");
    }
}

std::string Solver::optimize_solve(const std::string &inp) {
    std::string cur, prev, res;
    int i, t = (int) inp.find(' '), s = 0;
    i = t + 1;
    prev = inp.substr(0, t);
    if (prev.length() == 1)
        s += 1;
    else if (prev[1] == '\'')
        s -= 1;
    else
        s += 2;
    while (i < inp.length()) {
        t = (int) inp.find(' ', i);
        if (t == -1)
            t = (int) inp.length();
        cur = inp.substr(i, t - i);
        if (cur[0] == prev[0]) {
            if (cur.length() == 1)
                s += 1;
            else if (cur[1] == '\'')
                s -= 1;
            else
                s += 2;
        } else {
            s %= 4;
            if ((s == 1) || (s == -3))
                res += std::string(1, prev[0]) + " ";
            else if ((s == 2) || (s == -2))
                res += std::string(1, prev[0]) + "2 ";
            else if ((s == 3) || (s == -1))
                res += std::string(1, prev[0]) + "' ";
            s = 0;
            if (cur.length() == 1)
                s += 1;
            else if (cur[1] == '\'')
                s -= 1;
            else
                s += 2;
        }
        i = t + 1;
        prev = cur;
    }
    s %= 4;
    if ((s == 1) || (s == -3))
        res += std::string(1, prev[0]);
    else if ((s == 2) || (s == -2))
        res += std::string(1, prev[0]) + "2";
    else if ((s == 3) || (s == -1))
        res += std::string(1, prev[0]) + "'";
    return res;
}

Solver::Solver(RubiksCube *cube) : cube_(cube) {}

int Solver::num_of_unresolved() {
    int num = 0;
    if (cube_->FRU_.front != cube_->F_.front)
        num++;
    if (cube_->FLU_.front != cube_->F_.front)
        num++;
    if (cube_->FRD_.front != cube_->F_.front)
        num++;
    if (cube_->FLD_.front != cube_->F_.front)
        num++;
    if (cube_->FU_.front != cube_->F_.front)
        num++;
    if (cube_->FD_.front != cube_->F_.front)
        num++;
    if (cube_->FR_.front != cube_->F_.front)
        num++;
    if (cube_->FL_.front != cube_->F_.front)
        num++;

    if (cube_->BRU_.front != cube_->B_.front)
        num++;
    if (cube_->BLU_.front != cube_->B_.front)
        num++;
    if (cube_->BRD_.front != cube_->B_.front)
        num++;
    if (cube_->BLD_.front != cube_->B_.front)
        num++;
    if (cube_->BU_.front != cube_->B_.front)
        num++;
    if (cube_->BD_.front != cube_->B_.front)
        num++;
    if (cube_->BR_.front != cube_->B_.front)
        num++;
    if (cube_->BL_.front != cube_->B_.front)
        num++;

    if (cube_->BRU_.up != cube_->U_.front)
        num++;
    if (cube_->BLU_.up != cube_->U_.front)
        num++;
    if (cube_->FRU_.up != cube_->U_.front)
        num++;
    if (cube_->FLU_.up != cube_->U_.front)
        num++;
    if (cube_->BU_.side != cube_->U_.front)
        num++;
    if (cube_->SRU_.side != cube_->U_.front)
        num++;
    if (cube_->SLU_.side != cube_->U_.front)
        num++;
    if (cube_->FU_.side != cube_->U_.front)
        num++;

    if (cube_->BRD_.up != cube_->D_.front)
        num++;
    if (cube_->BLD_.up != cube_->D_.front)
        num++;
    if (cube_->FRD_.up != cube_->D_.front)
        num++;
    if (cube_->FLD_.up != cube_->D_.front)
        num++;
    if (cube_->BD_.side != cube_->D_.front)
        num++;
    if (cube_->SRD_.side != cube_->D_.front)
        num++;
    if (cube_->SLD_.side != cube_->D_.front)
        num++;
    if (cube_->FD_.side != cube_->D_.front)
        num++;

    if (cube_->BLU_.side != cube_->L_.front)
        num++;
    if (cube_->BLD_.side != cube_->L_.front)
        num++;
    if (cube_->FLD_.side != cube_->L_.front)
        num++;
    if (cube_->FLU_.side != cube_->L_.front)
        num++;
    if (cube_->BL_.side != cube_->L_.front)
        num++;
    if (cube_->SLU_.front != cube_->L_.front)
        num++;
    if (cube_->SLD_.front != cube_->L_.front)
        num++;
    if (cube_->FL_.side != cube_->L_.front)
        num++;

    if (cube_->BRU_.side != cube_->R_.front)
        num++;
    if (cube_->BRD_.side != cube_->R_.front)
        num++;
    if (cube_->FRD_.side != cube_->R_.front)
        num++;
    if (cube_->FRU_.side != cube_->R_.front)
        num++;
    if (cube_->BR_.side != cube_->R_.front)
        num++;
    if (cube_->SRU_.front != cube_->R_.front)
        num++;
    if (cube_->SRD_.front != cube_->R_.front)
        num++;
    if (cube_->FR_.side != cube_->R_.front)
        num++;
    return num;
}

void Solver::pif_paf() {
    cube_->multpy_com("R U R' U'");
    commands += "R U R' U' ";
}

void Solver::left_pif_paf() {
    cube_->multpy_com("L' U' L U");
    commands += "L' U' L U ";
}

std::string Solver::solve() {
    if (num_of_unresolved() == 0)
        return "";
    commands = "";
    make_white_cross();
    make_first_layer();
    make_second_layer();
    make_yellow_cross();
    make_yellow_side();
    put_right_edges();
    rearranging_corners();
    if (num_of_unresolved() != 0)
        throw std::runtime_error("The cube is unsolvable");
    return optimize_solve(optimize_solve(optimize_solve(commands)));
}