#include <map>
#include <string>
#include <vector>
#include <cstdint>

struct Command {
    std::string operation;
    int rd;
    int rs1 = -1;
    int rs2 = -1;
    int constant = -1;
    std::string label;
};

class CPU {
    private: 
        std::vector<uint8_t> memory;
        void addToLabelMap(std::string line, int currLine);
        void forOffsets(std::string str, int& cons, std::string& strD);

    public:
        int32_t registers[32];
        uint32_t pc;
        std::map<std::string, int> labelMap;
        static std::map<std::string, int> regMap;
        Command inspectLine(std::string line);
        bool isLabel(std::string& line);
        std::string cleanFromSpacesAndTabs(std::string& line);
        CPU();
        void loadAndRun(std::vector<std::string> lines);
        void execute(Command& cmd);
        void printState();
};