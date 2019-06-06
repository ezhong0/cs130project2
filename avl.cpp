#include "Tree.h"
#include <fstream>
#include <iostream>

int main(int argc, char** argv){
    if(argc < 1){
        std::cerr<<"must have a file\n";
        exit(1);
    }

    AVLTree tree;
    std::string fileName = argv[1];

    std::ifstream reader(fileName);
    if(reader.fail()){
        std::cerr<<"can't open file\n";
        exit(1);
    }

    std::string nextLine;
    while(std::getline(reader, nextLine)){
        if(nextLine.substr(0, 7) == "insert "){
            int pos = 7;
            int nextPos;
            int numTotal = 0;
            while(true){
                nextPos = nextLine.find(' ', pos+1);
                if(tree.insert(stoi(nextLine.substr(pos, nextPos))))
                    numTotal++;
                pos = nextPos;
                if(nextPos == int(std::string::npos)) break;
            }
            std::cout << "Added " << tree.getNumAdded() << " of " << numTotal << " nodes.\n"
                    << "Visited " << tree.getNumVisited() << " (" << tree.getNumVisited()/numTotal << ") nodes and performed " 
                    << tree.getNumRotations() << " (" << tree.getNumRotations()/numTotal << ") rotations.\n";
            tree.resetStats();
        } else if(nextLine.substr(0, 7) == "lookup "){
            std::string resultStr = "";
            int pos = 7;
            int nextPos;
            int numFound = 0;
            int numTotal = 0;
            while(true){
                nextPos = nextLine.find(' ', pos+1);
                std::string nextStr = nextLine.substr(pos, nextPos-pos);
                if(tree.lookup(stoi(nextStr))){
                    resultStr += nextStr + ", ";
                    numFound++;
                }
                numTotal++;
                pos = nextPos;
                if(nextPos == int(std::string::npos)) break;
            }
            std::cout << "Found " << numFound << " of " << numTotal << " nodes: ["
                << resultStr.substr(0, resultStr.length() - 2) << "]\n"
                << "Visited " << tree.getNumVisited() << " (" << tree.getNumVisited()/numTotal << ") nodes and performed "
                << tree.getNumRotations() << " (" << tree.getNumRotations()/numTotal << ") rotations.\n";
            tree.resetStats();
        } else if(nextLine.substr(0, 6) == "print "){
            if(nextLine.substr(6, 10) == "tree"){
                std::cout<<tree.print();
            }else if(nextLine.substr(6, 15) == "left-left"){
                std::cout<<tree.rangeLL();
            }else if(nextLine.substr(6, 16) == "left-right"){
                std::cout<<tree.rangeLR();
            }else if(nextLine.substr(6, 16) == "right-left"){
                std::cout<<tree.rangeRL();
            }else if(nextLine.substr(6, 17) == "right-right"){
                std::cout<<tree.rangeRR();
            }else{
                continue;
            }
        }else{
            continue;
        }
        std::cout<<"\n";
    }
    reader.close();
}