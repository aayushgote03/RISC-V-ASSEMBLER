#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <iomanip>
#include <bitset>

using namespace std;

// Structure to hold instruction information
struct InstructionInfo {
    string opcode;
    string funct3;
    string funct7;
};

// Map to hold register names and their corresponding binary values
unordered_map<string, string> registerMap = {
    {"x0", "00000"}, {"x1", "00001"}, {"x2", "00010"}, {"x3", "00011"},
    {"x4", "00100"}, {"x5", "00101"}, {"x6", "00110"}, {"x7", "00111"},
    {"x8", "01000"}, {"x9", "01001"}, {"x10", "01010"}, {"x11", "01011"},
    {"x12", "01100"}, {"x13", "01101"}, {"x14", "01110"}, {"x15", "01111"},
    {"x16", "10000"}, {"x17", "10001"}, {"x18", "10010"}, {"x19", "10011"},
    {"x20", "10100"}, {"x21", "10101"}, {"x22", "10110"}, {"x23", "10111"},
    {"x24", "11000"}, {"x25", "11001"}, {"x26", "11010"}, {"x27", "11011"},
    {"x28", "11100"}, {"x29", "11101"}, {"x30", "11110"}, {"x31", "11111"}
};

// Map to hold instruction information
unordered_map<string, InstructionInfo> instructionMap = {
    {"add",  {"0110011", "000", "0000000"}},
    {"sub",  {"0110011", "000", "0100000"}},
    {"addi", {"0010011", "000", ""}},
    {"and",  {"0110011", "111", "0000000"}},
    {"or",   {"0110011", "110", "0000000"}},
    {"xor",  {"0110011", "100", "0000000"}},
    {"andi", {"0010011", "111", ""}},
    {"ori",  {"0010011", "110", ""}},
    {"xori", {"0010011", "100", ""}},
    {"beq",  {"1100011", "000", ""}},
    {"bne",  {"1100011", "001", ""}},
    {"blt",  {"1100011", "100", ""}},
    {"bge",  {"1100011", "101", ""}},
    {"jal",  {"1101111", "", ""}},
    {"jalr", {"1100111", "000", ""}},
    {"lw",   {"0000011", "010", ""}},
    {"sw",   {"0100011", "010", ""}},
    {"lb",   {"0000011", "000", ""}},
    {"sb",   {"0100011", "000", ""}}
};

// Function to encode an R-type instruction
string encodeRType(const InstructionInfo& info, const string& rd, const string& rs1, const string& rs2) {
    return info.funct7 + registerMap[rs2] + registerMap[rs1] + info.funct3 + registerMap[rd] + info.opcode;
}

// Function to encode an I-type instruction
string encodeIType(const InstructionInfo& info, const string& rd, const string& rs1, int immediate) {
    string immBinary = bitset<12>(immediate).to_string();
    return immBinary + registerMap[rs1] + info.funct3 + registerMap[rd] + info.opcode;
}

// Function to encode a B-type instruction (used for branches)
string encodeBType(const InstructionInfo& info, const string& rs1, const string& rs2, int offset) {
    string immBinary = bitset<13>(offset).to_string(); // 13 bits for signed immediate
    string imm_12 = immBinary.substr(0, 1);   // imm[12]
    string imm_10_5 = immBinary.substr(1, 6); // imm[10:5]
    string imm_4_1 = immBinary.substr(7, 4);  // imm[4:1]
    string imm_11 = immBinary.substr(11, 1);  // imm[11]

    return imm_12 + imm_10_5 + registerMap[rs2] + registerMap[rs1] + info.funct3 + imm_4_1 + imm_11 + info.opcode;
}

// Function to encode a J-type instruction (used for jumps)
string encodeJType(const InstructionInfo& info, const string& rd, int offset) {
    string immBinary = bitset<21>(offset).to_string(); // 21 bits for signed immediate
    string imm_20 = immBinary.substr(0, 1);   // imm[20]
    string imm_10_1 = immBinary.substr(1, 10); // imm[10:1]
    string imm_11 = immBinary.substr(11, 1);  // imm[11]
    string imm_19_12 = immBinary.substr(12, 8);  // imm[19:12]

    return imm_20 + imm_19_12 + imm_11 + imm_10_1 + registerMap[rd] + info.opcode;
}

string parseAndEncode(const string& assembly) {
    stringstream ss(assembly);
    string instruction, rd, rs1, rs2;
    int immediate;

    ss >> instruction;

    if (instruction == "add" || instruction == "sub" || instruction == "and" || instruction == "or" || instruction == "xor") {
        // R-type instruction format: add rd, rs1, rs2
        ss >> rd >> rs1 >> rs2;
        rd = rd.substr(0, rd.size() - 1);   // Remove comma
        rs1 = rs1.substr(0, rs1.size() - 1); // Remove comma
        return encodeRType(instructionMap[instruction], rd, rs1, rs2);
    }
    else if (instruction == "addi" || instruction == "andi" || instruction == "ori" || instruction == "xori" || instruction == "jalr") {
        // I-type instruction format: addi rd, rs1, immediate
        ss >> rd >> rs1 >> immediate;
        rd = rd.substr(0, rd.size() - 1);   // Remove comma
        rs1 = rs1.substr(0, rs1.size() - 1); // Remove comma
        return encodeIType(instructionMap[instruction], rd, rs1, immediate);
    }
    else if (instruction == "beq" || instruction == "bne" || instruction == "blt" || instruction == "bge") {
        // B-type instruction format: beq rs1, rs2, offset
        ss >> rs1 >> rs2 >> immediate;
        rs1 = rs1.substr(0, rs1.size() - 1); // Remove comma
        rs2 = rs2.substr(0, rs2.size() - 1); // Remove comma
        return encodeBType(instructionMap[instruction], rs1, rs2, immediate);
    }
    else if (instruction == "jal") {
        // J-type instruction format: jal rd, offset
        ss >> rd >> immediate;
        rd = rd.substr(0, rd.size() - 1);   // Remove comma
        return encodeJType(instructionMap[instruction], rd, immediate);
    }
    
    
    else {
        return "Unknown instruction";
    }
}

int main() {
    // Example input assembly lines
    string assemblyCode[] = {
        "add x1, x2, x3",
        "sub x0, x1, x3",
        "addi x2, x1, 10",
        "and x4, x5, x6",
        "or x7, x8, x9",
        "xor x10, x11, x12",
        "beq x1, x2, 8",
        "jal x1, 16",
        "jalr x3, x2, 4",
        "andi x13, x14, 15",
    };

    // Process each line of assembly code
    for (const auto& line : assemblyCode) {
        string machineCode = parseAndEncode(line);
        cout << "Assembly: " << line << "\nMachine Code: " << machineCode << "\n" << endl;
    }

    return 0;
}