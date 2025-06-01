#include "write_to_file.h"

#include <fstream>
#include <iostream>

void toFile(int operationChoice, const std::string& sectionName, unsigned long long duration,const std::string& dataSet) {
    std::string fileName;
    if (sectionName == "Max priority queue heap" || sectionName == "Max priority queue doubly linked list") {
        switch (operationChoice) {
            case 1: {
                fileName = "insert.txt";
                break;
            }
            case 2: {
                fileName = "extract_max.txt";
                break;
            }
            case 3: {
                fileName = "peek.txt";
                break;
            }
            case 4: {
                fileName = "modify_key.txt";
                break;
            }
            case 5: {
                fileName = "return_size.txt";
                break;
            }
            default:
                std::cerr << "Unknown operation" << std::endl;
                break;
        }
    }else if (sectionName == "Array list" || sectionName == "Singly linked list"|| sectionName == "Doubly linked list"){
    switch (operationChoice) {
        case 1: {
            fileName = "push_first.txt";
            break;
        }
        case 2: {
            fileName = "push_last.txt";
            break;
        }
        case 3: {
            fileName = "push.txt";
            break;
        }
        case 4: {
            fileName = "remove_first.txt";
            break;
        }
        case 5: {
            fileName = "remove_last.txt";
            break;
        }
        case 6: {
            fileName = "remove.txt";
            break;
        }
        case 7: {
            fileName = "search.txt";
            break;
        }
        default: {
            std::cerr << "Unknown operation" << std::endl;
            break;
        }
    }
    }else {
        switch (operationChoice) {
            case 1: {
                fileName = "insert.txt";
                break;
            }
            case 2: {
                fileName = "remove.txt";
                break;
            }
            default: {
                std::cerr << "Unknown operation" << std::endl;
                break;
            }
        }
    }


    std::ofstream file(fileName, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return;
    }

    file<< "\nData set: "<< dataSet;
    file << "\n" << sectionName << " results measured in nanoseconds: " << duration << "\n";
}