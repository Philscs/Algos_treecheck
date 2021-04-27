#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

#include "Tree.h"

void setColor(int i);

int main(int argc, char *argv[]){
    Tree bst;

    //Missing argument for filename
    if(argc <= 1){
        setColor(12); std::cout << "Required format: treecheck [filename]" << std::endl; setColor(7);
        return 0;
    }

    //Take first input parameter as tree-filename
    std::ifstream ifs(argv[1]);
    if (!ifs.is_open()){
        setColor(12); std::cerr << std::endl << "[Error: File not found!]" << std::endl; setColor(7);
        return false;
    }
    while(!ifs.eof()){
        int value;
        ifs >> value;
        setColor(12); bst.addNode(value); setColor(7);
    }

    bst.printStats();

    return 0;
}

void setColor(int i){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
}
