
using namespace std;

#include "menu.h"

// Função criada para mostrar as operações disponíveis para o usuário
void Menu::mostrarMenuPrincipal() {

    cout << "\n|----------------------------------------------------|"
         << "\n|                   MENU PRINCIPAL                   |"
         << "\n|----------------------------------------------------|"
         << "\n| 1 - ADICIONAR UMA QUESTÃO AO BANCO                 |"
         << "\n|----------------------------------------------------|"
         << "\n| 2 - REMOVER UMA QUESTÃO                            |"
         << "\n|----------------------------------------------------|"
         << "\n| 3 - ESCOLHER UMA QUESTÃO ALEATÓRIA PARA RESPONDER  |"
         << "\n|----------------------------------------------------|"
         << "\n| 4 - ESCOLHER UMA QUESTÃO ESPECÍFICA PARA RESPONDER |"
         << "\n|----------------------------------------------------|"
         << "\n| 5 - MOSTRAR PONTUAÇÃO (erros e acertos obtidos)    |"
         << "\n|----------------------------------------------------|"
         << "\n| 6 - SAIR DO PROGRAMA                               |"
         << "\n|----------------------------------------------------|\n";
};

// Função criada para receber a opção escolhida pelo usuário
unsigned Menu::receberOpcaoMenu(){
    char entrada_usuario[256];
    unsigned escolhaMenu;
    
    cout << "\n Digite a opção desejada:";
    cin  >> entrada_usuario;

    // vai retornar 0 se entrada_usuario nao for do tipo int
    escolhaMenu = atoi(entrada_usuario);
    
    return escolhaMenu;
};

// Função criada para avisar ao usuário que o programa foi finalizado e terminar a execução
void Menu::finalizarPrograma(){
    cout << "\n|------------------------------------------------|"
         << "\n|                FIM DO PROGRAMA                 |"
         << "\n|------------------------------------------------|\n\n";
};

