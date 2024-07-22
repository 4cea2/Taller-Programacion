#include <iostream>
#include <map>
#include <sstream>
#include <vector>

#include "liberror.h"
#include "server.h"

Server::Server(const char* servname): skt((Socket(servname)).accept()), protocol(skt, false) {}

bool Server::arguments_checker(int argc, const char* args[]) {
    if (argc != 2) {
        std::cerr << "Bad program call. Expected " << args[0] << " <servname>\n";
    }
    return false;
}

/**
 * Cuenta las palabras de str.
 * Retorna la cantidad de palabras encontradas en el str.
 */
static size_t count_words(const std::string& str) {
    std::istringstream new_str(str);
    std::string word;
    size_t counter = 0;

    while (new_str >> word) {
        counter++;
    }

    return counter;
}


/**
 * Busca en el str los combos disponibles, en orden.
 * Retorna la cantidad de acciones procesadas.
 */
static size_t search_combos(std::string& str) {
    std::string first_combo = {"JUMP JUMP HIT"};
    std::string second_combo = {"HIT DUCK LEFT"};
    std::string thrid_combo = {"LEFT RIGHT JUMP HIT"};

    std::map<std::string, std::string> combo_map = {
            {first_combo, "UPPERCUT"}, {second_combo, "SIDEKICK"}, {thrid_combo, "HIGHKICK"}};

    std::vector<std::string> search_order(combo_map.size());
    search_order[0] = first_combo;
    search_order[1] = second_combo;
    search_order[2] = thrid_combo;

    for (const std::string& key: search_order) {
        std::string pattern = key;
        std::string replacement = combo_map[key];
        size_t pos = 0;
        while ((pos = str.find(pattern, pos)) != std::string::npos) {
            str.replace(pos, pattern.length(), replacement);
            pos += replacement.length();
        }
    }

    return count_words(str);
}

void Server::communicate_with_the_client() {
    size_t qty_actions = 0;
    while (true) {
        std::string msj_recv;

        if (!(protocol.recv_msj(msj_recv))) {
            break;
        }

        qty_actions += search_combos(msj_recv);

        if (!(protocol.send_msj(msj_recv))) {
            break;
        }
    }

    std::cout << "Actions: " << qty_actions << std::endl;
}
