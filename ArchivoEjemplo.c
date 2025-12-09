#include <iostream>
#include <string>
#include <vector>


void saludar_usuario(const std::string& nombre) {
    if (nombre.length() > 50) {
        std::cout << "Nombre demasiado largo." << std::endl;
        return;
    }
    
    std::string mensaje = "Bienvenido al sistema, " + nombre;
    std::cout << mensaje << std::endl;
}

int main() {
    std::string input = "Desarrollador";
    saludar_usuario(input);
    return 0;
}