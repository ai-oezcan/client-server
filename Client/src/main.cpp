#include <string>
#include <string_view>
#include <fstream>
#include <iostream>
#include "LazyPirateClient.h"

int main(int argc, const char** argv) {

    std::string inFile = "";
    std::string outFile = "";
    std::string ipAddress = "localhost";
    std::string portNumber = "5555";
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            if (std::string_view{ argv[i] } == "-i" && ++i < argc) {
                inFile = argv[i];
            }
            else if (std::string_view{ argv[i] } == "-o" && ++i < argc) {
                outFile = argv[i];
            }
            else if (std::string_view{ argv[i] } == "-a" && ++i < argc) {
                ipAddress = argv[i];
            }
            else if (std::string_view{ argv[i] } == "-p" && ++i < argc) {
                portNumber = argv[i];
            }
        } 
    }
    else {
        std::cout << "usage: [executable] [-i input.txt] [-o output.txt] [-a ip-adress] [-p port-number]" << std::endl;        
        return 0;
    }

    std::string line;
    std::ifstream iFilestream(inFile);
    std::ofstream oFilestream(outFile);
    if (iFilestream.is_open() && oFilestream.is_open()) {

        LazyPirateClient client(ipAddress + ":" + portNumber);
        while (std::getline(iFilestream, line)) {
            std::string reply;
            if (client.getReplyForRequest(line, reply)) {
                oFilestream << reply << std::endl;
            }
            else {
                break;
            }
        }
        iFilestream.close();
        oFilestream.close();
    }
    else {
        std::cout << "input or output file cannot be located." << std::endl;
    }

    return 0;
}