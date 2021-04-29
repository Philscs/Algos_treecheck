#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

#include "Tree.h"

void setColor(int i);

int main(int argc, char *argv[]){
    Tree bst;
    Tree subtree;

    std::cout << std::endl;
    //Missing argument for filename
    if(argc <= 1 || argc >= 4){
        setColor(12); std::cout << "Required format: treecheck [tree] OR treecheck [searchtree] [subtree]" << std::endl; setColor(7);
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
        bst.addNode(value);
    }

    bst.printStats();

    //Take second input parameter as subtree-filename for search
    if(argc == 3){
        int counter = 0;
        std::ifstream ifs(argv[2]);
        if (!ifs.is_open()){
            setColor(12); std::cerr << std::endl << "[Error: File not found!]" << std::endl; setColor(7);
            return false;
        }
        while(!ifs.eof()){
            int value;
            ifs >> value;
            subtree.addNode(value);
            counter++;
        }

        if(counter == 1){
            //Search for one single node
            std::cout << "--------------------------" << std::endl;
            std::cout << "Searching " << subtree.getRoot()->value << ": ";
            if(bst.searchNode(bst.getRoot(), subtree.getRoot())){
                setColor(10); std::cout << "found"; setColor(7);
            }else{
                setColor(12); std::cout << "not found"; setColor(7);
            }
        }else{
            //Search for subtree
            std::cout << "--------------------------" << std::endl;
            std::cout << "Searching subtree: ";
            if(bst.searchSubtree(bst.getRoot(), subtree.getRoot())){
                setColor(10); std::cout << "Subtree found"; setColor(7);
            }else{
                setColor(12); std::cout << "Subtree not found"; setColor(7);
            }
        }

    }

    std::cout << std::endl;

    return 0;
}

void setColor(int i){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
}
