#include <sstream>

#include <syslog.h>

#include "client.h"
#include "iostream"

static const char ATTACK[] = "Atacar";
static const char EXIT[] = "Salir";

Client::Client(const char* hostname, const char* servname):
        skt(hostname, servname), protocol(skt, true) {}

bool Client::arguments_checker(int argc, const char* args[]) {
    if (argc != 3) {
        syslog(LOG_ERR, "Bad program call. Expected %s <hostname> <servname>", args[0]);
        return false;
    }
    return true;
}

// Función para manejar la lógica de interacción con el servidor
static bool handle_server_interaction(Protocol& protocol, const std::string& action) {
    if (action == ATTACK) {
        return protocol.send_msg(action);
    } else {
        std::istringstream iss(action);
        std::string aux;
        iss >> aux;
        iss >> aux;
        int n_readings = std::stoi(aux);
        for (int i = 0; i < n_readings; i++) {
            std::string msg_recv;
            if (!protocol.recv_msg(msg_recv)) {
                return false;
            }
            std::cout << msg_recv << std::endl;
        }
    }
    return true;
}

void Client::communicate_with_the_server() {
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == EXIT) {
            return;
        }
        if (!handle_server_interaction(protocol, line)) {
            return;
        }
    }
}
