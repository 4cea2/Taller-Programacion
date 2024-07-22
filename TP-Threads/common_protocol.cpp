#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

#include <netinet/in.h>

#include "protocol.h"

#define FIRST_BYTE (uint8_t)0x06
#define MAX_BYTES_CLIENT 6
#define MAX_BYTES_SERVER 1

/**
 * Mapeo que usara el cliente/servidor a la hora de serializar/deserializar el mensaje.
 */
static const std::map<std::string, uint8_t> action_map = {
        {"Atacar", 0x03}, {"revivido.", 0x05}, {"muerto.", 0x04}};

Protocol::Protocol(Socket& skt, bool is_client): skt(skt), is_client(is_client) {}

/**
 * Serializa el str, ya sea el mensaje del cliente o servidor.
 *
 * @param str String a serializar.
 * @param is_client Booleano que indica si el msg es del cliente o no.
 *
 * @return vector de uint_8 que representa al msg.
 */
static std::vector<uint8_t> serialize(const std::string& msg, bool is_client) {
    std::vector<uint8_t> bytes;
    if (is_client) {
        bytes.push_back(action_map.at(msg));
    } else {
        size_t i = 0;
        while (i < 2) {
            while (i < msg.length() && msg[i] == ' ') {
                i++;
            }
            size_t j = i;
            while (j < msg.length() && msg[j] != ' ') {
                j++;
            }
            std::string word = msg.substr(i, j - i);
            int number = std::stoi(word);

            uint16_t value = ntohs(static_cast<uint16_t>(number));
            uint8_t byte_msb = (uint8_t)(value);
            uint8_t byte_lsb = (uint8_t)(value >> 8);

            bytes.push_back(byte_msb);
            bytes.push_back(byte_lsb);

            i = j;
        }
        bytes.insert(bytes.begin(), FIRST_BYTE);
        bytes.push_back(action_map.at(msg.substr(i + 1)));
    }
    return bytes;
}

static int int16_to_int(uint8_t byte_msb, uint8_t byte_lsb) { return (byte_msb << 8) | byte_lsb; }

/**
 * Deserializa el vect, ya sea el mensaje del cliente o servidor.
 *
 * @param vect Referencia a un vector de uint_8 a deserializar.
 * @param is_client Booleano que indica si el vect es para el cliente o no.
 *
 * @return String que representa el msg.
 */
static std::string deserialize(const std::vector<uint8_t>& vect, bool is_client) {
    std::string result = "";
    if (is_client) {
        // 0x06 <alives> <deads> <type event>
        //  0     1  2    3  4         5
        uint8_t byte_msb = vect[1];
        uint8_t byte_lsb = vect[2];
        int deads = int16_to_int(byte_msb, byte_lsb);

        byte_msb = vect[3];
        byte_lsb = vect[4];
        int lives = int16_to_int(byte_msb, byte_lsb);

        uint8_t event_byte = vect[5];
        std::string event_str = "";
        auto it =
                std::find_if(action_map.begin(), action_map.end(),
                             [event_byte](const auto& pair) { return pair.second == event_byte; });
        if (it != action_map.end()) {
            event_str = it->first;
        }

        result = "Un enemigo ha " + event_str + ' ' + std::to_string(deads) + " vivo(s) y " +
                 std::to_string(lives) + " muerto(s).";
    } else {
        result = "Atacar";
    }
    return result;
}

bool Protocol::send_msg(const std::string& msg) {

    std::vector<uint8_t> bytes_to_send = serialize(msg, is_client);
    bool was_closed = false;

    skt.sendall(bytes_to_send.data(), bytes_to_send.size() * sizeof(uint8_t), &was_closed);

    return !was_closed;
}

bool Protocol::recv_msg(std::string& msg_recv) {
    bool was_closed = false;
    std::vector<uint8_t> bytes_received(MAX_BYTES_SERVER);

    if (is_client) {
        bytes_received.resize(MAX_BYTES_CLIENT);
    }

    skt.recvall(bytes_received.data(), bytes_received.size() * sizeof(uint8_t), &was_closed);
    msg_recv = deserialize(bytes_received, is_client);

    return !was_closed;
}
