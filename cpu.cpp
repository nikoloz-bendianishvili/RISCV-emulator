#include "cpu.hpp"
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iostream>

std::map<std::string, int> CPU::regMap = {
    {"zero", 0}, {"x0", 0},
    {"ra", 1}, {"x1", 1},
    {"sp", 2}, {"x2", 2},
    {"gp", 3}, {"x3", 3},
    {"tp", 4}, {"x4", 4},
    {"t0", 5}, {"x5", 5},
    {"t1", 6}, {"x6", 6},
    {"t2", 7}, {"x7", 7},
    {"s0", 8}, {"x8", 8},
    {"s1", 9}, {"x9", 9},
    {"a0", 10}, {"x10", 10},
    {"a1", 11}, {"x11", 11},
    {"a2", 12}, {"x12", 12},
    {"a3", 13}, {"x13", 13},
    {"a4", 14}, {"x14", 14},
    {"a5", 15}, {"x15", 15},
    {"a6", 16}, {"x16", 16},
    {"a7", 17}, {"x17", 17},
    {"s2", 18}, {"x18", 18},
    {"s3", 19}, {"x19", 19},
    {"s4", 20}, {"x20", 20},
    {"s5", 21}, {"x21", 21},
    {"s6", 22}, {"x22", 22},
    {"s7", 23}, {"x23", 23},
    {"s8", 24}, {"x24", 24},
    {"s9", 25}, {"x25", 25},
    {"s10", 26}, {"x26", 26},
    {"s11", 27}, {"x27", 27},
    {"t3", 28}, {"x28", 28},
    {"t4", 29}, {"x29", 29},
    {"t5", 30}, {"x30", 30},
    {"t6", 31}, {"x31", 31}
};

void CPU::forOffsets(std::string str, int& cons, std::string& strD) {
    std::replace(str.begin(), str.end(), '(', ' ');
    std::replace(str.begin(), str.end(), ')', ' ');
    std::stringstream sstmp(str);
    sstmp >> cons >> strD;
}

Command CPU::inspectLine(std::string line) {
    std::replace(line.begin(), line.end(), ',', ' ');
    std::stringstream ss(line);

    Command cmd;
    ss >> cmd.operation;
    std::transform(cmd.operation.begin(), cmd.operation.end(), cmd.operation.begin(), ::tolower);

    if(cmd.operation == "lui") {
        std::string a1;
        ss >> a1 >> cmd.constant;
        cmd.rd = CPU::regMap.at(a1);
    } else if(cmd.operation == "jal") {
        std::string a1, a2;
        ss >> a1;
        if(ss >> a2) {
            cmd.rd = CPU::regMap.at(a1);
            cmd.label = a2;
        } else {
            cmd.rd = 1;
            cmd.label = a1;
        }
    } else if(cmd.operation == "jalr") {
        std::string a1, a2;
        if(ss >> a1) {
            if(ss >> a2) {
                int cons;
                std::string reg;
                forOffsets(a2, cons, reg);
                cmd.rd = CPU::regMap.at(a1);
                cmd.rs1 = CPU::regMap.at(reg);
                cmd.constant = cons;
            } else {
                cmd.rd = 1;
                cmd.rs1 = CPU::regMap.at(a1);
                cmd.constant = 0;
            }
        }
    } else if(cmd.operation == "beq" || cmd.operation == "bne" || cmd.operation == "blt" || cmd.operation == "bge" ||
              cmd.operation == "bltu" || cmd.operation == "bgeu" || cmd.operation == "bgt" || cmd.operation == "ble" ||
              cmd.operation == "bgtu" || cmd.operation == "bleu") {
        
            std::string a1, a2, a3;
            ss >> a1 >> a2 >> a3;
            cmd.rs1 = CPU::regMap.at(a1);
            cmd.rs2 = CPU::regMap.at(a2);
            cmd.label = a3;
    } else if(cmd.operation == "lb" || cmd.operation == "lh" || cmd.operation == "lw" || cmd.operation == "lbu" || cmd.operation == "lhu") {
        std::string a1, a2;
        ss >> a1 >> a2;
        int cons;
        std::string reg;
        forOffsets(a2, cons, reg);
        cmd.rd = CPU::regMap.at(a1);
        cmd.rs1 = CPU::regMap.at(reg);
        cmd.constant = cons;
    } else if(cmd.operation == "sb" || cmd.operation == "sh" || cmd.operation == "sw") {
        std::string a1, a2;
        ss >> a1 >> a2;
        int cons;
        std::string reg;
        forOffsets(a2, cons, reg);
        cmd.rs1 = CPU::regMap.at(reg);
        cmd.rs2 = CPU::regMap.at(a1);
        cmd.constant = cons;
    } else if(cmd.operation == "addi" || cmd.operation == "slti" || cmd.operation == "sltiu" || cmd.operation == "xori" ||
              cmd.operation == "ori" || cmd.operation == "andi") {
        std::string a1, a2;
        ss >> a1 >> a2 >> cmd.constant;
        cmd.rd = CPU::regMap.at(a1);
        cmd.rs1 = CPU::regMap.at(a2);
    } else if(cmd.operation == "slli" || cmd.operation == "srli" || cmd.operation == "srai") {
        std::string a1, a2;
        ss >> a1 >> a2 >> cmd.constant;
        cmd.rd = CPU::regMap.at(a1);
        cmd.rs1 = CPU::regMap.at(a2);
    } else if(cmd.operation == "add" || cmd.operation == "sub" || cmd.operation == "sll" || cmd.operation == "slt" ||
              cmd.operation == "sltu" || cmd.operation == "xor" || cmd.operation == "srl" || cmd.operation == "sra" ||
              cmd.operation == "or" || cmd.operation == "and" || cmd.operation == "mul" || cmd.operation == "div") {
        std::string a1, a2, a3;
        ss >> a1 >> a2 >> a3;
        cmd.rd = CPU::regMap.at(a1);
        cmd.rs1 = CPU::regMap.at(a2);
        cmd.rs2 = CPU::regMap.at(a3);
    } else if(cmd.operation == "li") {
        std::string a1;
        ss >> a1 >> cmd.constant;
        cmd.rd = CPU::regMap.at(a1);
    } else if(cmd.operation == "mv" || cmd.operation == "not" || cmd.operation == "neg") {
        std::string a1, a2;
        ss >> a1 >> a2;
        cmd.rd = CPU::regMap.at(a1);
        cmd.rs1 = CPU::regMap.at(a2);
    } else if(cmd.operation == "j" || cmd.operation == "call") {
        std::string a1;
        ss >> a1;
        cmd.label = a1;
    } else if(cmd.operation == "jr") {
        std::string a1;
        ss >> a1;
        cmd.rs1 = CPU::regMap.at(a1);
    } else if(cmd.operation == "ret") {
        cmd.rd = 0;
        cmd.rs1 = 1;     
        cmd.constant = 0;
    } else if(cmd.operation == "beqz" || cmd.operation == "bnez" || cmd.operation == "bltz" || cmd.operation == "bgez" ||
              cmd.operation == "bgtz" || cmd.operation == "blez") {
        std::string a1, a2;
        ss >> a1 >> a2;
        cmd.rs1 = CPU::regMap.at(a1);
        cmd.label = a2;
    }  else if(cmd.operation == "strlen") {
        std::string a1;
        ss >> a1;
        cmd.label = a1;
    } else if(cmd.operation == "ecall") {

    } else if(cmd.operation == "printf") {
        std::string a1;
        ss >> a1;
        cmd.label = a1;
    } else if(cmd.operation == "endl") {

    } else if(cmd.operation == "bnefortests") {
        std::string a1, a2;
        ss >> a1 >> cmd.constant >> a2;
        cmd.rs1 = CPU::regMap.at(a1);
        cmd.label = a2;
    } else {
        std::cout << "!!! UNKNOWN OPERATION !!! : " << cmd.operation << std::endl;
        exit(1);
    }
    return cmd;
}

void CPU::addToLabelMap(std::string line, int currLine) {
    std::string newLabel = line.substr(0, line.length() - 1);
    labelMap[newLabel] = currLine;
}


void CPU::execute(Command& cmd) {
    registers[0] = 0;

    if(cmd.operation == "lui") {
        registers[cmd.rd] = cmd.constant << 12;
        pc++;
    } else if(cmd.operation == "jal") {
        if (cmd.rd != 0) {
            registers[cmd.rd] = pc + 1;
        }
        pc = labelMap.at(cmd.label);
    } else if(cmd.operation == "jalr") {
        int pcNext = pc + 1;
        pc = registers[cmd.rs1] + cmd.constant;
        if (cmd.rd != 0) {
            registers[cmd.rd] = pcNext;
        }
    } else if(cmd.operation == "beq") {
        if(registers[cmd.rs1] == registers[cmd.rs2]) {
            pc = labelMap.at(cmd.label);
        } else {
            pc++;
        }
    } else if(cmd.operation == "bne") {
        if(registers[cmd.rs1] != registers[cmd.rs2]) {
            pc = labelMap.at(cmd.label);
        } else {
            pc++;
        }
    } else if(cmd.operation == "blt") {
        if(registers[cmd.rs1] < registers[cmd.rs2]) {
            pc = labelMap.at(cmd.label);
        } else {
            pc++;
        }
    } else if(cmd.operation == "bge") {
        if(registers[cmd.rs1] >= registers[cmd.rs2]) {
            pc = labelMap.at(cmd.label);
        } else {
            pc++;
        }
    } else if(cmd.operation == "bltu") {
        if(static_cast<uint32_t> (registers[cmd.rs1]) < static_cast<uint32_t> (registers[cmd.rs2])) {
            pc = labelMap.at(cmd.label);
        } else {
            pc++;
        }
    } else if(cmd.operation == "bgeu") {
        if(static_cast<uint32_t> (registers[cmd.rs1]) >= static_cast<uint32_t> (registers[cmd.rs2])) {
            pc = labelMap.at(cmd.label);
        } else {
            pc++;
        }
    } else if(cmd.operation == "bgt") {
        if(registers[cmd.rs1] > registers[cmd.rs2]) {
            pc = labelMap.at(cmd.label);
        } else {
            pc++;
        }
    } else if(cmd.operation == "ble") {
        if(registers[cmd.rs1] <= registers[cmd.rs2]) {
            pc = labelMap.at(cmd.label);
        } else {
            pc++;
        }
    } else if(cmd.operation == "bgtu") {
        if(static_cast<uint32_t> (registers[cmd.rs1]) > static_cast<uint32_t> (registers[cmd.rs2])) {
            pc = labelMap.at(cmd.label);
        } else {
            pc++;
        }
    } else if(cmd.operation == "bleu") {
        if(static_cast<uint32_t> (registers[cmd.rs1]) <= static_cast<uint32_t> (registers[cmd.rs2])) {
            pc = labelMap.at(cmd.label);
        } else {
            pc++;
        }
    } else if(cmd.operation == "lb") {
        int address = registers[cmd.rs1] + cmd.constant;
        int8_t value = static_cast<int8_t>(memory[address]);
        if(cmd.rd != 0) {
            registers[cmd.rd] = static_cast<int32_t>(value);
        }
        pc++;
    } else if(cmd.operation == "lbu") {
        int address = registers[cmd.rs1] + cmd.constant;
        uint8_t value = static_cast<uint8_t>(memory[address]);
        if(cmd.rd != 0) {
            registers[cmd.rd] = static_cast<uint32_t>(value);
        }
        pc++;
    } else if(cmd.operation == "lh") {
        int address = registers[cmd.rs1] + cmd.constant;
        int16_t value = static_cast<int16_t>(static_cast<uint8_t> (memory[address]) | static_cast<uint8_t>(memory[address + 1]) << 8);
        if(cmd.rd != 0) {
            registers[cmd.rd] = static_cast<int32_t>(value);
        }
        pc++;
    } else if(cmd.operation == "lhu") {
        int address = registers[cmd.rs1] + cmd.constant;
        uint16_t value = static_cast<uint16_t> (static_cast<uint8_t>(memory[address]) | (static_cast<uint8_t>(memory[address + 1]) << 8));
        if(cmd.rd != 0) {
        registers[cmd.rd] = static_cast<uint32_t>(value);
        }
        pc++;
    } else if(cmd.operation == "lw") {
        int address = registers[cmd.rs1] + cmd.constant;
        int32_t value = static_cast<int32_t>(memory[address] | (memory[address + 1] << 8) | (memory[address + 2] << 16) | (memory[address + 3] << 24));
        if(cmd.rd != 0) {
            registers[cmd.rd] = value;
        }
        pc++;
    } else if(cmd.operation == "sb") {
        int address = registers[cmd.rs1] + cmd.constant;
        int8_t value = static_cast<int8_t>(registers[cmd.rs2]);
        memory[address] = value;
        pc++;
    } else if(cmd.operation == "sh") {
        int address = registers[cmd.rs1] + cmd.constant;
        int16_t value = static_cast<int16_t>(registers[cmd.rs2]);
        memory[address] = value & 0xFF;
        memory[address + 1] = (value >> 8) & 0xFF;
        pc++;
    } else if(cmd.operation == "sw") {
        int address = registers[cmd.rs1] + cmd.constant;
        int32_t value = registers[cmd.rs2];
        memory[address] = value & 0xFF;
        memory[address + 1] = (value >> 8) & 0xFF;
        memory[address + 2] = (value >> 16) & 0xFF;
        memory[address + 3] = (value >> 24) & 0xFF;
        pc++;
    } else if(cmd.operation == "addi") {
        if(cmd.rd != 0) {
            registers[cmd.rd] = registers[cmd.rs1] + cmd.constant;
        }
        pc++;
    } else if(cmd.operation == "slti") {
        if(cmd.rd != 0) {
            if(registers[cmd.rs1] < cmd.constant) {
                registers[cmd.rd] = 1;
            } else {
                registers[cmd.rd] = 0;
            }
        }
        pc++;
    } else if(cmd.operation == "sltiu") {
        if(cmd.rd != 0) {
            if(static_cast<uint32_t> (registers[cmd.rs1]) < static_cast<uint32_t>(cmd.constant)) {
                registers[cmd.rd] = 1;
            } else {
                registers[cmd.rd] = 0;
            }
        }
        pc++;
    } else if(cmd.operation == "xori") {
        if(cmd.rd != 0) {
            registers[cmd.rd] = registers[cmd.rs1] ^ cmd.constant;
        }
        pc++;
    } else if(cmd.operation == "ori") {
        if(cmd.rd != 0) {
            registers[cmd.rd] = registers[cmd.rs1] | cmd.constant;
        }
        pc++;
    } else if(cmd.operation == "andi") {
        if(cmd.rd != 0) {
            registers[cmd.rd] = registers[cmd.rs1] & cmd.constant;
        }
        pc++;
    } else if(cmd.operation == "slli") {
        if(cmd.rd != 0) {
            registers[cmd.rd] = registers[cmd.rs1] << cmd.constant;
        }
        pc++;
    } else if(cmd.operation == "srli") {
        if(cmd.rd != 0) {
            registers[cmd.rd] = static_cast<uint32_t>(registers[cmd.rs1]) >> cmd.constant;
        }
        pc++;
    } else if(cmd.operation == "srai") {
        if(cmd.rd != 0) {
            registers[cmd.rd] = registers[cmd.rs1] >> cmd.constant;
        }
        pc++;
    } else if(cmd.operation == "add") {
        if(cmd.rd != 0) {
            registers[cmd.rd] = registers[cmd.rs1] + registers[cmd.rs2];
        }
        pc++;
    } else if(cmd.operation == "sub") {
        if(cmd.rd != 0) {
            registers[cmd.rd] = registers[cmd.rs1] - registers[cmd.rs2];
        }
        pc++;
    } else if(cmd.operation == "mul") {
        if(cmd.rd != 0) {
            registers[cmd.rd] = registers[cmd.rs1] * registers[cmd.rs2];
        }
        pc++;
    } else if(cmd.operation == "div") {
        if(cmd.rd != 0) {
            if(registers[cmd.rs1] % registers[cmd.rs2] == 0) {
                registers[cmd.rd] = registers[cmd.rs1] / registers[cmd.rs2];
            } else {
                std::cout << "Invalid Arguments For Division" << std::endl;
            }
        }
        pc++;
    } else if(cmd.operation == "strlen") {
        registers[10] = cmd.label.length();
        pc++;
    } else if(cmd.operation == "sll") {
        if(cmd.rd != 0) {
            registers[cmd.rd] = registers[cmd.rs1] << (registers[cmd.rs2] & 0x1F);
        }
        pc++;
    } else if(cmd.operation == "slt") {
        if(cmd.rd != 0) {
            if(registers[cmd.rs1] < registers[cmd.rs2]) {
                registers[cmd.rd] = 1;
            } else {
                registers[cmd.rd] = 0;
            }
        }
        pc++;
    } else if(cmd.operation == "sltu") {
        if(cmd.rd != 0) {
            if(static_cast<uint32_t> (registers[cmd.rs1]) < static_cast<uint32_t>(registers[cmd.rs2])) {
                registers[cmd.rd] = 1;
            } else {
                registers[cmd.rd] = 0;
            }
        }
        pc++;
    } else if(cmd.operation == "xor") {
        if(cmd.rd != 0) {
            registers[cmd.rd] = registers[cmd.rs1] ^ registers[cmd.rs2];
        }
        pc++;
    } else if(cmd.operation == "srl") {
        if(cmd.rd != 0) {
            registers[cmd.rd] = static_cast<uint32_t> (registers[cmd.rs1]) >> static_cast<uint32_t> (registers[cmd.rs2] & 0x1F);
        }
        pc++;
    } else if(cmd.operation == "sra") {
        if(cmd.rd != 0) {
            registers[cmd.rd] = registers[cmd.rs1] >> static_cast<uint32_t> (registers[cmd.rs2] & 0x1F);
        }
        pc++;
    } else if(cmd.operation == "or") {
        if(cmd.rd != 0) {
            registers[cmd.rd] = registers[cmd.rs1] | registers[cmd.rs2];
        }
        pc++;
    } else if(cmd.operation == "and") {
        if(cmd.rd != 0) {
            registers[cmd.rd] = registers[cmd.rs1] & registers[cmd.rs2];
        }
        pc++;
    } else if(cmd.operation == "li") {
        if(cmd.rd != 0) {
            registers[cmd.rd] = cmd.constant;
        }
        pc++;
    } else if(cmd.operation == "mv") {
        if(cmd.rd != 0) {
            registers[cmd.rd] = registers[cmd.rs1];
        }
        pc++;
    } else if(cmd.operation == "not") {
        if(cmd.rd != 0) {
            registers[cmd.rd] = ~(registers[cmd.rs1]);
        }
        pc++;
    } else if(cmd.operation == "neg") {
        if(cmd.rd != 0) {
            registers[cmd.rd] = -(registers[cmd.rs1]);
        }
        pc++;
    } else if(cmd.operation == "j") {
        pc = labelMap.at(cmd.label);
    } else if(cmd.operation == "ret") {
        pc = registers[1];
    } else if(cmd.operation == "call") {
        registers[1] = pc + 1;
        pc = labelMap.at(cmd.label);
    } else if(cmd.operation == "jr") {
        pc = registers[cmd.rs1];
    } else if(cmd.operation == "bgt") {
        if(registers[cmd.rs1] > registers[cmd.rs2]) {
            pc = labelMap.at(cmd.label);
        } else {
            pc++;
        }
    } else if(cmd.operation == "ble") {
        if(registers[cmd.rs1] <= registers[cmd.rs2]) {
            pc = labelMap.at(cmd.label);
        } else {
            pc++;
        }
    } else if(cmd.operation == "bgtu") {
        if(static_cast<uint32_t> (registers[cmd.rs1]) > static_cast<uint32_t> (registers[cmd.rs2])) {
            pc = labelMap.at(cmd.label);
        } else {
            pc++;
        }
    } else if(cmd.operation == "bleu") {
        if(static_cast<uint32_t> (registers[cmd.rs1]) <= static_cast<uint32_t> (registers[cmd.rs2])) {
            pc = labelMap.at(cmd.label);
        } else {
            pc++;
        }
    } else if(cmd.operation == "beqz") {
        if(registers[cmd.rs1] == 0) {
            pc = labelMap.at(cmd.label);
        } else {
            pc++;
        }
    } else if(cmd.operation == "bnez") {
        if(registers[cmd.rs1] != 0) {
            pc = labelMap.at(cmd.label);
        } else {
            pc++;
        }
    } else if(cmd.operation == "bltz") {
        if(registers[cmd.rs1] < 0) {
            pc = labelMap.at(cmd.label);
        } else {
            pc++;
        }
    } else if(cmd.operation == "bgez") {
        if(registers[cmd.rs1] >= 0) {
            pc = labelMap.at(cmd.label);
        } else {
            pc++;
        }
    } else if(cmd.operation == "bgtz") {
        if(registers[cmd.rs1] > 0) {
            pc = labelMap.at(cmd.label);
        } else {
            pc++;
        }
    } else if(cmd.operation == "blez") {
        if(registers[cmd.rs1] <= 0) {
            pc = labelMap.at(cmd.label);
        } else {
            pc++;
        }
    } else if(cmd.operation == "ecall") {
        if(registers[10] == 10) {
            exit(0);
        }
    } else if(cmd.operation == "printf") {
        std::cout << cmd.label;
        pc++;
    } else if(cmd.operation == "endl") {
        std::cout << std::endl;
        pc++;
    } else if(cmd.operation == "bnefortests") {
        if(registers[cmd.rs1] != cmd.constant) {
            pc = labelMap.at(cmd.label);
        } else {
            pc++;
        }
    } else {
        std::cout << "Invalid Operation" << std::endl;
        pc++;
    }
}

bool CPU::isLabel(std::string& line) {
    return line.back() == ':';
}

std::string CPU::cleanFromSpacesAndTabs(std::string& line) {
    size_t first = line.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    size_t last = line.find_last_not_of(" \t\r\n");
    return line.substr(first, (last - first + 1));
}

CPU::CPU() {
    for(int i = 0; i < 32; i++) {
        registers[i] = 0;
    }
    registers[2] = 20000;
    pc = 0;
    memory.resize(20000, 0);
}