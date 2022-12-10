#include <bits/stdc++.h>
using namespace std;

int main() {

    // Initialization
    int mem_size = 100000;
    unsigned int ptr = 0;
    vector<unsigned char> mem(mem_size, 0);
    stack<int> loops;

    // Load Source File
    ifstream file(".source.c3");
    stringstream buffer;
    buffer << file.rdbuf();
    string code = buffer.str();
    int len = code.size()/3;

    // interpreter Body
    for (int prg=0; prg<len; prg++) {

        // Get Order
        string ord = code.substr(prg*3, 3);

        // Modify Pointer
        if (ord == "CCC") ptr = (ptr >= mem_size-1) ? 0 : ptr+1;
        if (ord == "CC3") ptr = (ptr <= 0) ? mem_size-1 : ptr-1;

        // Modify Memory
        if (ord == "C3C") mem[ptr]++;
        if (ord == "C33") mem[ptr]--;

        // Input and Output
        if (ord == "3CC") putchar(mem[ptr]);
        if (ord == "3C3") mem[ptr] = getchar();

        // Loop Start
        if (ord == "33C") {
            if (mem[ptr] != 0) loops.push(prg);
            else {
                int depth = 1;
                while (depth>0) {
                    prg++;
                    if (code.substr(prg*3, 3) == "33C") depth++;
                    if (code.substr(prg*3, 3) == "333") depth--;
                }
            }
        }

        // Loop End
        if (ord == "333") {
            prg = loops.top()-1;
            loops.pop();
        }

    }

}