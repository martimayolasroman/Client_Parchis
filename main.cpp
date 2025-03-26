#include <stdlib.h>
#include <iostream>
#include <string>
#include <SFML/Network.hpp>


#define SERVER_PORT 55000

const sf::IpAddress SERVER_IP = sf::IpAddress(127, 0, 0, 1);
//const sf::IpAddress SERVER_IP = sf::IpAddress(10,40,2,183); -- PC Profe clase

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

 /// Socket Selector-----------------


    
    sf::TcpSocket socket;
    bool gameLoop = true;

    if (socket.connect(SERVER_IP, SERVER_PORT) != sf::Socket::Status::Done) {
        std::cerr << "Error al conectar al servidor" << std::endl;
    }
    else {
        std::cout << "Cliente conectado al servidor" << std::endl;

        while (gameLoop) {
            //sf::sleep(sf::seconds(1));

            std::string message;
            std::cout << "Inserta mensaje para el servidor, -1 para salir " << std::endl;
            std::cin >> message;

            if (message == "-1") {
                std::cout<<"Desconectado... " << std::endl;
                gameLoop = false;
            }
            else {
                sf::Packet packet;
                packet << message;
                if (socket.send(packet) != sf::Socket::Status::Done) {
                    std::cerr << "Error al enviar mensajes del servidor" << std::endl;
                } else {
                    std::cout << "Mensaje Enviado correctamente " << std::endl;
                }

            }


        }

        socket.disconnect();
        std::cout << "Cliente desconectado del servidor" << std::endl;
    }

    /// Socket Selector-----------------



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