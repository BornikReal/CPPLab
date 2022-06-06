#include "cube.h"


std::ostream &operator<<(std::ostream &out, const color &inp) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (inp == WHITE)
        SetConsoleTextAttribute(handle, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
    else if (inp == RED)
        SetConsoleTextAttribute(handle, BACKGROUND_RED | BACKGROUND_INTENSITY);
    else if (inp == BLUE)
        SetConsoleTextAttribute(handle, BACKGROUND_BLUE | BACKGROUND_INTENSITY);
    else if (inp == GREEN)
        SetConsoleTextAttribute(handle, BACKGROUND_GREEN | BACKGROUND_INTENSITY);
    else if (inp == ORANGE)
        SetConsoleTextAttribute(handle, 98);
    else if (inp == YELLOW)
        SetConsoleTextAttribute(handle, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
    out << "  ";
    SetConsoleTextAttribute(handle, 0xF);
    return out;
}

std::istream &operator>>(std::istream &in, color &rhs) {
    int t;
    in >> t;
    if (t == 0)
        rhs = GREEN;
    else if (t == 1)
        rhs = ORANGE;
    else if (t == 2)
        rhs = RED;
    else if (t == 3)
        rhs = WHITE;
    else if (t == 4)
        rhs = YELLOW;
    else if (t == 5)
        rhs = BLUE;
    else
        throw std::runtime_error("No matching found for this color number");
    return in;
}

bool RubiksCube::corner_cube::operator==(const corner_cube &rhs) const {
    return (front == rhs.front && side == rhs.side && up == rhs.up);
}

bool RubiksCube::corner_cube::operator>(const corner_cube &rhs) const {
    return false;
}

bool RubiksCube::side_cube::operator==(const side_cube &rhs) const {
    return (front == rhs.front && side == rhs.side);
}

bool RubiksCube::side_cube::operator>(const side_cube &rhs) const {
    return false;
}

bool RubiksCube::middle_cube::operator==(const middle_cube &rhs) const {
    return front == rhs.front;
}

bool RubiksCube::middle_cube::operator>(const middle_cube &rhs) const {
    return false;
}

RubiksCube::side_cube RubiksCube::change_orientation(side_cube inp) {
    side_cube new_side = inp;
    std::swap(new_side.front, new_side.side);
    return new_side;
}

RubiksCube::corner_cube RubiksCube::change_orientation1(corner_cube inp) {
    corner_cube new_corner = inp;
    std::swap(new_corner.front, new_corner.side);
    return new_corner;
}

RubiksCube::corner_cube RubiksCube::change_orientation2(corner_cube inp) {
    corner_cube new_corner = inp;
    std::swap(new_corner.front, new_corner.up);
    return new_corner;
}

RubiksCube::corner_cube RubiksCube::change_orientation3(corner_cube inp) {
    corner_cube new_corner = inp;
    std::swap(new_corner.side, new_corner.up);
    return new_corner;
}

RubiksCube::RubiksCube() {
    F_ = {RED};
    R_ = {BLUE};
    U_ = {WHITE};
    D_ = {YELLOW};
    L_ = {GREEN};
    B_ = {ORANGE};
    FU_ = {RED, WHITE};
    FD_ = {RED, YELLOW};
    FL_ = {RED, GREEN};
    FR_ = {RED, BLUE};
    BU_ = {ORANGE, WHITE};
    BD_ = {ORANGE, YELLOW};
    BR_ = {ORANGE, BLUE};
    BL_ = {ORANGE, GREEN};
    SRU_ = {BLUE, WHITE};
    SRD_ = {BLUE, YELLOW};
    SLU_ = {GREEN, WHITE};
    SLD_ = {GREEN, YELLOW};
    FLU_ = {RED, GREEN, WHITE};
    FRU_ = {RED, BLUE, WHITE};
    FLD_ = {RED, GREEN, YELLOW};
    FRD_ = {RED, BLUE, YELLOW};
    BRU_ = {ORANGE, BLUE, WHITE};
    BLU_ = {ORANGE, GREEN, WHITE};
    BRD_ = {ORANGE, BLUE, YELLOW};
    BLD_ = {ORANGE, GREEN, YELLOW};
}

void RubiksCube::R() {
    corner_cube temp1 = FRU_;
    FRU_ = change_orientation2(FRD_);
    FRD_ = change_orientation2(BRD_);
    BRD_ = change_orientation2(BRU_);
    BRU_ = change_orientation2(temp1);
    side_cube temp2 = FR_;
    FR_ = change_orientation(SRD_);
    SRD_ = change_orientation(BR_);
    BR_ = change_orientation(SRU_);
    SRU_ = change_orientation(temp2);
}

void RubiksCube::R2() {
    std::swap(FRU_, BRD_);
    std::swap(FRD_, BRU_);
    std::swap(FR_, BR_);
    std::swap(SRU_, SRD_);
}

void RubiksCube::Rb() {
    corner_cube temp1 = FRU_;
    FRU_ = change_orientation2(BRU_);
    BRU_ = change_orientation2(BRD_);
    BRD_ = change_orientation2(FRD_);
    FRD_ = change_orientation2(temp1);
    side_cube temp2 = FR_;
    FR_ = change_orientation(SRU_);
    SRU_ = change_orientation(BR_);
    BR_ = change_orientation(SRD_);
    SRD_ = change_orientation(temp2);
}

void RubiksCube::L() {
    corner_cube temp1 = FLU_;
    FLU_ = change_orientation2(BLU_);
    BLU_ = change_orientation2(BLD_);
    BLD_ = change_orientation2(FLD_);
    FLD_ = change_orientation2(temp1);
    side_cube temp2 = FL_;
    FL_ = change_orientation(SLU_);
    SLU_ = change_orientation(BL_);
    BL_ = change_orientation(SLD_);
    SLD_ = change_orientation(temp2);
}

void RubiksCube::L2() {
    std::swap(FLU_, BLD_);
    std::swap(FLD_, BLU_);
    std::swap(FL_, BL_);
    std::swap(SLU_, SLD_);
}

void RubiksCube::Lb() {
    corner_cube temp1 = FLU_;
    FLU_ = change_orientation2(FLD_);
    FLD_ = change_orientation2(BLD_);
    BLD_ = change_orientation2(BLU_);
    BLU_ = change_orientation2(temp1);
    side_cube temp2 = FL_;
    FL_ = change_orientation(SLD_);
    SLD_ = change_orientation(BL_);
    BL_ = change_orientation(SLU_);
    SLU_ = change_orientation(temp2);
}

void RubiksCube::U() {
    corner_cube temp1 = FRU_;
    FRU_ = change_orientation1(BRU_);
    BRU_ = change_orientation1(BLU_);
    BLU_ = change_orientation1(FLU_);
    FLU_ = change_orientation1(temp1);
    side_cube temp2 = FU_;
    FU_ = SRU_;
    SRU_ = BU_;
    BU_ = SLU_;
    SLU_ = temp2;
}

void RubiksCube::U2() {
    std::swap(FRU_, BLU_);
    std::swap(FLU_, BRU_);
    std::swap(FU_, BU_);
    std::swap(SRU_, SLU_);
}

void RubiksCube::Ub() {
    corner_cube temp1 = FRU_;
    FRU_ = change_orientation1(FLU_);
    FLU_ = change_orientation1(BLU_);
    BLU_ = change_orientation1(BRU_);
    BRU_ = change_orientation1(temp1);
    side_cube temp2 = FU_;
    FU_ = SLU_;
    SLU_ = BU_;
    BU_ = SRU_;
    SRU_ = temp2;
}

void RubiksCube::D() {
    corner_cube temp1 = FRD_;
    FRD_ = change_orientation1(FLD_);
    FLD_ = change_orientation1(BLD_);
    BLD_ = change_orientation1(BRD_);
    BRD_ = change_orientation1(temp1);
    side_cube temp2 = FD_;
    FD_ = SLD_;
    SLD_ = BD_;
    BD_ = SRD_;
    SRD_ = temp2;
}

void RubiksCube::D2() {
    std::swap(FRD_, BLD_);
    std::swap(FLD_, BRD_);
    std::swap(FD_, BD_);
    std::swap(SRD_, SLD_);
}

void RubiksCube::Db() {
    corner_cube temp1 = FRD_;
    FRD_ = change_orientation1(BRD_);
    BRD_ = change_orientation1(BLD_);
    BLD_ = change_orientation1(FLD_);
    FLD_ = change_orientation1(temp1);
    side_cube temp2 = FD_;
    FD_ = SRD_;
    SRD_ = BD_;
    BD_ = SLD_;
    SLD_ = temp2;
}

void RubiksCube::F() {
    corner_cube temp1 = FRU_;
    FRU_ = change_orientation3(FLU_);
    FLU_ = change_orientation3(FLD_);
    FLD_ = change_orientation3(FRD_);
    FRD_ = change_orientation3(temp1);
    side_cube temp2 = FU_;
    FU_ = FL_;
    FL_ = FD_;
    FD_ = FR_;
    FR_ = temp2;
}

void RubiksCube::F2() {
    std::swap(FLU_, FRD_);
    std::swap(FRU_, FLD_);
    std::swap(FL_, FR_);
    std::swap(FD_, FU_);
}

void RubiksCube::Fb() {
    corner_cube temp1 = FRU_;
    FRU_ = change_orientation3(FRD_);
    FRD_ = change_orientation3(FLD_);
    FLD_ = change_orientation3(FLU_);
    FLU_ = change_orientation3(temp1);
    side_cube temp2 = FU_;
    FU_ = FR_;
    FR_ = FD_;
    FD_ = FL_;
    FL_ = temp2;
}

void RubiksCube::B() {
    corner_cube temp1 = BRU_;
    BRU_ = change_orientation3(BRD_);
    BRD_ = change_orientation3(BLD_);
    BLD_ = change_orientation3(BLU_);
    BLU_ = change_orientation3(temp1);
    side_cube temp2 = BU_;
    BU_ = BR_;
    BR_ = BD_;
    BD_ = BL_;
    BL_ = temp2;
}

void RubiksCube::B2() {
    std::swap(BLU_, BRD_);
    std::swap(BRU_, BLD_);
    std::swap(BL_, BR_);
    std::swap(BD_, BU_);
}

void RubiksCube::Bb() {
    corner_cube temp1 = BRU_;
    BRU_ = change_orientation3(BLU_);
    BLU_ = change_orientation3(BLD_);
    BLD_ = change_orientation3(BRD_);
    BRD_ = change_orientation3(temp1);
    side_cube temp2 = BU_;
    BU_ = BL_;
    BL_ = BD_;
    BD_ = BR_;
    BR_ = temp2;
}

void RubiksCube::E() {
    middle_cube temp1 = F_;
    F_ = L_;
    L_ = B_;
    B_ = R_;
    R_ = temp1;
    side_cube temp2 = FR_;
    FR_ = change_orientation(FL_);
    FL_ = change_orientation(BL_);
    BL_ = change_orientation(BR_);
    BR_ = change_orientation(temp2);
}

void RubiksCube::E2() {
    std::swap(F_, B_);
    std::swap(R_, L_);
    std::swap(FR_, BL_);
    std::swap(FL_, BR_);
}

void RubiksCube::Eb() {
    middle_cube temp1 = F_;
    F_ = R_;
    R_ = B_;
    B_ = L_;
    L_ = temp1;
    side_cube temp2 = FR_;
    FR_ = change_orientation(BR_);
    BR_ = change_orientation(BL_);
    BL_ = change_orientation(FL_);
    FL_ = change_orientation(temp2);
}

void RubiksCube::M() {
    middle_cube temp1 = F_;
    F_ = U_;
    U_ = B_;
    B_ = D_;
    D_ = temp1;
    side_cube temp2 = FU_;
    FU_ = change_orientation(BU_);
    BU_ = change_orientation(BD_);
    BD_ = change_orientation(FD_);
    FD_ = change_orientation(temp2);
}

void RubiksCube::M2() {
    std::swap(F_, B_);
    std::swap(U_, D_);
    std::swap(FU_, BD_);
    std::swap(FD_, BU_);
}

void RubiksCube::Mb() {
    middle_cube temp1 = F_;
    F_ = D_;
    D_ = B_;
    B_ = U_;
    U_ = temp1;
    side_cube temp2 = FU_;
    FU_ = change_orientation(FD_);
    FD_ = change_orientation(BD_);
    BD_ = change_orientation(BU_);
    BU_ = change_orientation(temp2);
}

void RubiksCube::S() {
    middle_cube temp1 = U_;
    U_ = L_;
    L_ = D_;
    D_ = R_;
    R_ = temp1;
    side_cube temp2 = SRU_;
    SRU_ = change_orientation(SLU_);
    SLU_ = change_orientation(SLD_);
    SLD_ = change_orientation(SRD_);
    SRD_ = change_orientation(temp2);
}

void RubiksCube::S2() {
    std::swap(R_, L_);
    std::swap(U_, D_);
    std::swap(SRU_, SLD_);
    std::swap(SRD_, SLU_);
}

void RubiksCube::Sb() {
    middle_cube temp1 = U_;
    U_ = R_;
    R_ = D_;
    D_ = L_;
    L_ = temp1;
    side_cube temp2 = SRU_;
    SRU_ = change_orientation(SRD_);
    SRD_ = change_orientation(SLD_);
    SLD_ = change_orientation(SLU_);
    SLU_ = change_orientation(temp2);
}

void RubiksCube::x() {
    R();
    Lb();
    Mb();
}

void RubiksCube::x2() {
    R2();
    L2();
    M2();
}

void RubiksCube::xb() {
    Rb();
    L();
    M();
}

void RubiksCube::y() {
    U();
    Db();
    Eb();
}

void RubiksCube::y2() {
    U2();
    D2();
    E2();
}

void RubiksCube::yb() {
    Ub();
    D();
    E();
}

void RubiksCube::z() {
    F();
    Bb();
    S();
}

void RubiksCube::z2() {
    F2();
    B2();
    S2();
}

void RubiksCube::zb() {
    Fb();
    B();
    Sb();
}

void RubiksCube::multpy_com(const std::string &inp) {
    std::string temp;
    int i = 0, t;
    while (i < inp.length()) {
        t = (int) inp.find(' ', i);
        if (t == -1)
            t = (int) inp.length();
        temp = inp.substr(i, t - i);
        if (temp == "R") R();
        else if (temp == "R2") R2();
        else if (temp == "R'") Rb();
        else if (temp == "L") L();
        else if (temp == "L2") L2();
        else if (temp == "L'") Lb();
        else if (temp == "U") U();
        else if (temp == "U2") U2();
        else if (temp == "U'") Ub();
        else if (temp == "D") D();
        else if (temp == "D2") D2();
        else if (temp == "D'") Db();
        else if (temp == "F") F();
        else if (temp == "F2") F2();
        else if (temp == "F'") Fb();
        else if (temp == "B") B();
        else if (temp == "B2") B2();
        else if (temp == "B'") Bb();
        else if (temp == "M") M();
        else if (temp == "M2") M2();
        else if (temp == "M'") Mb();
        else if (temp == "E") E();
        else if (temp == "E2") E2();
        else if (temp == "E'") Eb();
        else if (temp == "S") S();
        else if (temp == "S2") S2();
        else if (temp == "S'") Sb();
        else if (temp == "x") x();
        else if (temp == "x2") x2();
        else if (temp == "x'") xb();
        else if (temp == "y") y();
        else if (temp == "y2") y2();
        else if (temp == "y'") yb();
        else if (temp == "z") z();
        else if (temp == "z2") z2();
        else if (temp == "z'") zb();
        i = t + 1;
    }
}

void RubiksCube::print() const {
    std::cout << "      " << BLU_.up << BU_.side << BRU_.up << "\n";
    std::cout << "      " << SLU_.side << U_.front << SRU_.side << "\n";
    std::cout << "      " << FLU_.up << FU_.side << FRU_.up << "\n";
    std::cout << BLU_.side << SLU_.front << FLU_.side;
    std::cout << FLU_.front << FU_.front << FRU_.front;
    std::cout << FRU_.side << SRU_.front << BRU_.side;
    std::cout << BRU_.front << BU_.front << BLU_.front << "\n";
    std::cout << BL_.side << L_.front << FL_.side;
    std::cout << FL_.front << F_.front << FR_.front;
    std::cout << FR_.side << R_.front << BR_.side;
    std::cout << BR_.front << B_.front << BL_.front << "\n";
    std::cout << BLD_.side << SLD_.front << FLD_.side;
    std::cout << FLD_.front << FD_.front << FRD_.front;
    std::cout << FRD_.side << SRD_.front << BRD_.side;
    std::cout << BRD_.front << BD_.front << BLD_.front << "\n";
    std::cout << "      " << FLD_.up << FD_.side << FRD_.up << "\n";
    std::cout << "      " << SLD_.side << D_.front << SRD_.side << "\n";
    std::cout << "      " << BLD_.up << BD_.side << BRD_.up << "\n\n";
}

std::string RubiksCube::shuffle(int length) {
    srand(time(nullptr));
    if (length == 0)
        length = rand() % 1000;
    std::string res;
    for (int i = 0; i < length; ++i) {
        int t = rand() % 18;
        switch (t) {
            case 0:
                R();
                res += "R ";
                break;
            case 1:
                R2();
                res += "R2 ";
                break;
            case 2:
                Rb();
                res += "R' ";
                break;
            case 3:
                L();
                res += "L ";
                break;
            case 4:
                L2();
                res += "L2 ";
                break;
            case 5:
                Lb();
                res += "L' ";
                break;
            case 6:
                U();
                res += "U ";
                break;
            case 7:
                U2();
                res += "U2 ";
                break;
            case 8:
                Ub();
                res += "U' ";
                break;
            case 9:
                D();
                res += "D ";
                break;
            case 10:
                D2();
                res += "D2 ";
                break;
            case 11:
                Db();
                res += "D' ";
                break;
            case 12:
                F();
                res += "F ";
                break;
            case 13:
                F2();
                res += "F2 ";
                break;
            case 14:
                Fb();
                res += "F' ";
                break;
            case 15:
                B();
                res += "B ";
                break;
            case 16:
                B2();
                res += "B2 ";
                break;
            case 17:
                Bb();
                res += "B' ";
                break;
        }
    }
    return res;
}

std::istream &operator>>(std::istream &in, RubiksCube &rhs) {
    in >> rhs.BLU_.up >> rhs.BU_.side >> rhs.BRU_.up;
    in >> rhs.SLU_.side >> rhs.U_.front >> rhs.SRU_.side;
    in >> rhs.FLU_.up >> rhs.FU_.side >> rhs.FRU_.up;
    in >> rhs.BLU_.side >> rhs.SLU_.front >> rhs.FLU_.side;
    in >> rhs.BL_.side >> rhs.L_.front >> rhs.FL_.side;
    in >> rhs.BLD_.side >> rhs.SLD_.front >> rhs.FLD_.side;
    in >> rhs.FLU_.front >> rhs.FU_.front >> rhs.FRU_.front;
    in >> rhs.FL_.front >> rhs.F_.front >> rhs.FR_.front;
    in >> rhs.FLD_.front >> rhs.FD_.front >> rhs.FRD_.front;
    in >> rhs.FRU_.side >> rhs.SRU_.front >> rhs.BRU_.side;
    in >> rhs.FR_.side >> rhs.R_.front >> rhs.BR_.side;
    in >> rhs.FRD_.side >> rhs.SRD_.front >> rhs.BRD_.side;
    in >> rhs.BRU_.front >> rhs.BU_.front >> rhs.BLU_.front;
    in >> rhs.BR_.front >> rhs.B_.front >> rhs.BL_.front;
    in >> rhs.BRD_.front >> rhs.BD_.front >> rhs.BLD_.front;
    in >> rhs.FLD_.up >> rhs.FD_.side >> rhs.FRD_.up;
    in >> rhs.SLD_.side >> rhs.D_.front >> rhs.SRD_.side;
    in >> rhs.BLD_.up >> rhs.BD_.side >> rhs.BRD_.up;
    return in;
}

std::ostream &operator<<(std::ostream &out, const RubiksCube &rhs) {
    out << (int) rhs.BLU_.up << " " << (int) rhs.BU_.side << " " << (int) rhs.BRU_.up << "\n";
    out << (int) rhs.SLU_.side << " " << (int) rhs.U_.front << " " << (int) rhs.SRU_.side << "\n";
    out << (int) rhs.FLU_.up << " " << (int) rhs.FU_.side << " " << (int) rhs.FRU_.up << "\n";
    out << (int) rhs.BLU_.side << " " << (int) rhs.SLU_.front << " " << (int) rhs.FLU_.side << "\n";
    out << (int) rhs.BL_.side << " " << (int) rhs.L_.front << " " << (int) rhs.FL_.side << "\n";
    out << (int) rhs.BLD_.side << " " << (int) rhs.SLD_.front << " " << (int) rhs.FLD_.side << "\n";
    out << (int) rhs.FLU_.front << " " << (int) rhs.FU_.front << " " << (int) rhs.FRU_.front << "\n";
    out << (int) rhs.FL_.front << " " << (int) rhs.F_.front << " " << (int) rhs.FR_.front << "\n";
    out << (int) rhs.FLD_.front << " " << (int) rhs.FD_.front << " " << (int) rhs.FRD_.front << "\n";
    out << (int) rhs.FRU_.side << " " << (int) rhs.SRU_.front << " " << (int) rhs.BRU_.side << "\n";
    out << (int) rhs.FR_.side << " " << (int) rhs.R_.front << " " << (int) rhs.BR_.side << "\n";
    out << (int) rhs.FRD_.side << " " << (int) rhs.SRD_.front << " " << (int) rhs.BRD_.side << "\n";
    out << (int) rhs.BRU_.front << " " << (int) rhs.BU_.front << " " << (int) rhs.BLU_.front << "\n";
    out << (int) rhs.BR_.front << " " << (int) rhs.B_.front << " " << (int) rhs.BL_.front << "\n";
    out << (int) rhs.BRD_.front << " " << (int) rhs.BD_.front << " " << (int) rhs.BLD_.front << "\n";
    out << (int) rhs.FLD_.up << " " << (int) rhs.FD_.side << " " << (int) rhs.FRD_.up << "\n";
    out << (int) rhs.SLD_.side << " " << (int) rhs.D_.front << " " << (int) rhs.SRD_.side << "\n";
    out << (int) rhs.BLD_.up << " " << (int) rhs.BD_.side << " " << (int) rhs.BRD_.up;
    return out;
}