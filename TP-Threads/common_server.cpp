#include <syslog.h>

#include "acceptor.h"
#include "constant_queue.h"
#include "gameloop.h"
#include "server.h"

const int QTY_ENEMIES = 5;

static const char EXIT[] = "q";

Server::Server(const char* servname):
        serv(servname),
        queue_gameloop(MAX_ACTIONS),
        msg_queue_list(),
        acceptor(serv, queue_gameloop, msg_queue_list),
        gameloop(QTY_ENEMIES, queue_gameloop, msg_queue_list) {}

bool Server::arguments_checker(int argc, const char* args[]) {
    if (argc != 2) {
        syslog(LOG_ERR, "Bad program call. Expected %s <servname>", args[0]);
        return false;
    }
    return true;
}

void Server::accept_clients() { acceptor.start(); }

void Server::start_game() { gameloop.start(); }

void Server::read_standard_input() {
    std::string line;
    while (getline(std::cin, line)) {
        if (line == EXIT) {
            break;
        }
    }
}

void Server::end_game() {
    gameloop.end_game();
    acceptor.finish_accepting();
    serv.shutdown(2);
    serv.close();
}
