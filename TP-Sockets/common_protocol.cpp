#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

#include <netinet/in.h>

#include "protocol.h"


/**
 * Mapeo que usara el cliente a la hora de serializar el mensaje.
 */
static const std::map<std::string, uint8_t> action_map = {{"NOP", 0x00},   {"JUMP", 0x01},
                                                          {"RIGHT", 0x02}, {"LEFT", 0x03},
                                                          {"DUCK", 0x04},  {"HIT", 0x05}};

Protocol::Protocol(Socket& skt, bool is_client): skt(skt), is_client(is_client) {}


/**
 * Serializa el str, ya sea el mensaje del cliente o servidor.
 * Retorna un vector de bytes.
 */
static std::vector<uint8_t> serialize(std::string& str, bool is_client) {
    std::vector<uint8_t> bytes;
    if (is_client) {
        size_t i = 0;
        while (i < str.length()) {
            while (i < str.length() && str[i] == ' ') {
                i++;
            }
            size_t j = i;
            while (j < str.length() && str[j] != ' ') {
                j++;
            }
            std::string word = str.substr(i, j - i);
            bytes.push_back(action_map.at(word));
            i = j;
        }

    } else {

        for (size_t i = 0; (str[i] != '\0'); ++i) {
            bytes.push_back(static_cast<uint8_t>(str[i]));
        }

        uint16_t qty_bytes = ntohs(static_cast<uint16_t>(bytes.size()));
        uint8_t byte_msb = (uint8_t)(qty_bytes);
        uint8_t byte_lsb = (uint8_t)(qty_bytes >> 8);

        bytes.insert(bytes.begin(), byte_lsb);
        bytes.insert(bytes.begin(), byte_msb);
    }
    return bytes;
}

/**
 * Deserializa el vect, ya sea el mensaje del cliente o servidor.
 * Retorna un string.
 */
static std::string deserialize(const std::vector<uint8_t>& vect, bool is_client) {
    std::string result;
    if (is_client) {

        result = std::accumulate(vect.begin(), vect.end(), result,
                                 [](std::string& acc, uint8_t byte) {
                                     acc += static_cast<char>(byte);
                                     return acc;
                                 });

    } else {

        for (uint8_t byte: vect) {
            auto it = std::find_if(action_map.begin(), action_map.end(),
                                   [byte](const auto& pair) { return pair.second == byte; });

            if (it != action_map.end()) {
                result += it->first + " ";
            }
        }

        result.pop_back();
    }
    return result;
}

bool Protocol::send_msj(std::string& msj) {

    std::vector<uint8_t> bytes_to_send = serialize(msj, is_client);
    bool was_closed = false;

    skt.sendall(bytes_to_send.data(), bytes_to_send.size() * sizeof(uint8_t), &was_closed);

    return !was_closed;
}

bool Protocol::recv_msj(std::string& msj_recv) {
    bool was_closed = false;
    std::vector<uint8_t> bytes_received;

    if (is_client) {
        uint16_t msj_length = 0;
        skt.recvall(&msj_length, sizeof(msj_length), &was_closed);

        msj_length = ntohs(msj_length);
        bytes_received.resize(msj_length);

        skt.recvall(bytes_received.data(), msj_length, &was_closed);
    } else {
        while (!was_closed) {
            uint8_t buffer_byte;
            if (skt.recvall(&buffer_byte, sizeof(uint8_t), &was_closed) == 0) {
                return false;
            }
            if (buffer_byte == 0x00) {
                break;
            }
            bytes_received.push_back(buffer_byte);
        }
    }

    msj_recv = deserialize(bytes_received, is_client);
    return !was_closed;
}
