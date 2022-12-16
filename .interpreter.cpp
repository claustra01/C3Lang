#include <bits/stdc++.h>
#define MEM_SIZE 100000
using namespace std;

int compare(char *str1, string str2) {
    for (int i = 0; i < 3; i++) {
	if (str1[i] != str2.at(i)) {
	    return 0;
	}
    }
    return 1;
}

int main(int argc, char **argv) {

    // Initialization
    int ptr = 0;
    unsigned char mem[MEM_SIZE]; 
    stack<char*> loops;

    // Load Source File
    ifstream file;
    if (argc < 2) file.open(".source.c3");
    else file.open(argv[1]);
    filebuf *pbuf =  file.rdbuf();
    size_t size = pbuf->pubseekoff(0, file.end, file.in);
    pbuf->pubseekpos(0, file.in);
    char *buf = new char[size];
    pbuf->sgetn(buf, size);
    char *prg_end = &buf[size-1];
    file.close();

    // interpreter Body
    for (char *prg = buf; prg <= prg_end; prg += 3) {
        // Modify Pointer
        if (compare(prg, "CCC")) ptr = (ptr >= MEM_SIZE-1) ? 0 : ptr+1;
	else if (compare(prg, "CC3")) ptr = (ptr <= 0) ? MEM_SIZE-1 : ptr-1;

        // Modify Memory
	else if (compare(prg, "C3C")) mem[ptr]++;
	else if (compare(prg, "C33")) mem[ptr]--;

        // Input and Output
	else if (compare(prg, "3CC")) putchar(mem[ptr]);
	else if (compare(prg, "3C3")) mem[ptr] = getchar();

        // Loop Start
	else if (compare(prg, "33C")) {
            if (mem[ptr] != 0) loops.push(prg);
            else {
                int depth = 1;
                while (depth>0) {
                    prg+=3;
                    if (compare(prg, "33C")) depth++;
                    if (compare(prg, "333")) depth--;
                }
            }
        }

        // Loop End
	else if (compare(prg, "333")) {
            prg = loops.top()-3;
            loops.pop();
        }
    }

    delete[] buf;
    return 0;
}
