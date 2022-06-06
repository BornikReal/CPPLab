#include <iostream>
#include <string>
#include <fstream>
#include "cube.h"
#include "solver.h"

int main() {
    RubiksCube cube;
    std::ifstream file1("test.txt");
    file1 >> cube;
    int mode;
    std::cout
            << "Select the mode of operation:\n"
               "(1 - generation of a random cube, writing it to a file, reading from this file and assembling)\n"
               "(2 - reading the cube from the selected file and assembling it)\n"
               "(3 - manual control of the cube)\n";
    std::cin >> mode;
    if (mode == 1) {
        RubiksCube cube;
        std::cout << cube.shuffle(20) << "\n\n";
        cube.print();
        std::ofstream file("test.txt");
        file << cube;
        file.close();
        std::ifstream file1("test.txt");
        file1 >> cube;
        file1.close();
        cube.print();
        Solver s(&cube);
        std::cout << s.solve() << "\n\n";
        cube.print();
    } else if (mode == 2) {
        RubiksCube cube;
        std::string filename;
        std::cout << "Enter the file name:\n";
        std::cin >> filename;
        std::cout << "\n";
        std::ifstream file1(filename);
        file1 >> cube;
        file1.close();
        cube.print();
        Solver s(&cube);
        std::cout << s.solve() << "\n\n";
        cube.print();
    } else if (mode == 3) {
        RubiksCube cube;
        Solver s(&cube);
        std::cout
                << "Enter commands to rotate the cube. Use [shuffle_number] to shuffle the dice, [solve] to solve the current position and [exit] to exit\n";
        std::string command;
        while (true) {
            cube.print();
            std::cin >> command;
            if (command == "exit")
                return 0;
            else if (command.substr(0, command.find('_')) == "shuffle") {
                if (command == "shuffle")
                    std::cout << cube.shuffle() << "\n";
                else
                    std::cout << cube.shuffle(stoi(command.substr(command.find('_') + 1), nullptr, 10)) << "\n";
            } else if (command.substr(0, command.find('_')) == "file") {
                std::ifstream file1(command.substr(command.find('_') + 1));
                file1 >> cube;
            } else if (command == "solve")
                std::cout << s.solve() << "\n";
            else
                cube.multpy_com(command);
        }
    } else
        std::cout << "The wrong mode is selected!\n";
    return 0;
}