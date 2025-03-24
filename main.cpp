#include <stdlib.h>
#include <iostream>
#include <string>
#include <SFML/Network.hpp>


#define SERVER_PORT 55000

const sf::IpAddress SERVER_IP = sf::IpAddress(127, 0, 0, 1);

enum tipoPaquete
{
    HANDSHAKE, LOGIN, MOVIMIENTO
};

sf::Packet& operator >> (sf::Packet& packet, tipoPaquete& tipo) {

    int temp;
    packet >> temp;
    tipo = static_cast<tipoPaquete>(temp);

    return packet;
}

void HandShake(sf::Packet data) {
    std::string message;
    data >> message;
    std::cerr << "Mensaje recibido : " << message << std::endl;

}



int main()
{

 
    
    sf::TcpSocket socket;

    if (socket.connect(SERVER_IP, SERVER_PORT) != sf::Socket::Status::Done) {
        std::cerr << "Error al conectar al servidor" << std::endl;
    }

    std::cout << "Cliente conectado al servidor" << std::endl;

    sf::Packet packet;

    if (socket.receive(packet) == sf::Socket::Status::Done) {

   
        tipoPaquete tipo;

        packet >> tipo;

        switch (tipo)
        {
        case HANDSHAKE:
            HandShake(packet);
            break;
        case LOGIN:
            break;
        case MOVIMIENTO:
            break;
        default:
            break;
        }
        
        packet.clear();

    }
    else {
        std::cerr << "Error al recibir mensajes del servidor" << std::endl;
    }

    socket.disconnect();
    
}