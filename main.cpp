#include <stdlib.h>
#include <iostream>


#include <SFML/Graphics.hpp>
#include <cppconn/driver.h>
#include <cppconn/exception.h>

#define SERVER "127.0.0.1:3306"
#define USERNAME "root"
#define PASSWORD ""




void ConnectDatabase(sql::Driver*& driver,sql::Connection*& con){


    try {

        driver = get_driver_instance();
        con = driver->connect(SERVER, USERNAME, PASSWORD);
        std::cout << "Connection done. " << std::endl;

        



    }
    catch (sql::SQLException e) {

        std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
        


    }

}
void DisconnectDatabase(sql::Connection*& con){

    con->close();

    if (con->isClosed()) {

        std::cout << "Connection close. " << std::endl;
        delete con;
    }
    
   
}


int main()
{

    sql::Driver* driver;
    sql::Connection* con;

    ConnectDatabase(driver, con);
    DisconnectDatabase(con);
   
    system("pause");
    // exit(1);



    /*sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }*/
}