#include "cpu.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>


int main() {
    CPU myCPU;
    myCPU.registers[1] = -1;
    std::ifstream file("test.asm");

    if (!file.is_open()) {
        std::cerr << "Error: Couldn't open file!" << std::endl;
        return 1;
    }

    std::vector<std::string> instructions;
    std::string line;
    int count = 0;

    while(std::getline(file, line)) {
        size_t place = line.find('#');
        if(place != std::string::npos) {
            line = line.substr(0, place);
        }

        line = myCPU.cleanFromSpacesAndTabs(line);
        if(line.empty()) continue;
        if (myCPU.isLabel(line)) {
            std::string labelName = line.substr(0, line.length() - 1);
            myCPU.labelMap[labelName] = count;
        } else {
            instructions.push_back(line);
            count++;
        }
    }
    file.close();

    std::vector<Command> program;
    for(std::string line : instructions) {
        program.push_back(myCPU.inspectLine(line));
    } 

    while(static_cast<int>(myCPU.pc) < (int)program.size() && static_cast<int>(myCPU.pc) >= 0) {
        myCPU.execute(program[myCPU.pc]);
        myCPU.registers[0] = 0;
    }


    return 0;
}





