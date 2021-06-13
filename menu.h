#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>

using namespace std;

class Menu {
    public:
        void mostrarMenuPrincipal();
        unsigned receberOpcaoMenu();
        void finalizarPrograma();

};

#endif