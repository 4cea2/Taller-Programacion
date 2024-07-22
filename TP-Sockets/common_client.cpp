#include <iostream>

#include "client.h"

Client::Client(const char* hostname, const char* servname):
        skt(hostname, servname), protocol(skt, true) {}

void Client::read_standar_input() {
    std::list<std::string> lines_read;

    std::string line;

    while (std::getline(std::cin, line)) {
        line += " NOP";
        lines_read.push_back(line);
    }

    msjs = lines_read;
}

bool Client::arguments_checker(int argc, const char* args[]) {
    if (argc != 3) {
        std::cerr << "Bad program call. Expected " << args[0] << " <hostname> <servname>\n";
    }
    return false;
}

void Client::communicate_with_the_server() {
    for (std::string msj_to_send: msjs) {
        if (!(protocol.send_msj(msj_to_send))) {
            break;
        }

        std::string msj_recv;

        if (!(protocol.recv_msj(msj_recv))) {
            break;
        }

        std::cout << msj_recv << std::endl;
    }
}
