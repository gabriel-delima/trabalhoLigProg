#include <iostream>
#include <string>
using namespace std;

#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>
#include <jsoncpp/json/value.h>

#include "menu.h"
#include "requisicao.h"
#include "excecao.h"
#include "quiz.h"

int main() {
    Menu menu;
    unsigned escolha_menu;
	string nomeBusca;

/////////////////// 
Requisicao requisicao = Requisicao();
Quiz quiz = Quiz();
unsigned opcao;
string questao;
string url;

/////////////////// Inicio do Programa
cout << "\n|----------------------------------------------------|"
	 << "\n|--------------  PERGUNTAS-E-REPOSTAS  --------------|"
     << "\n|----------------------------------------------------|\n";

/////////////////// Execução do menu com suas respectivas funções
	do {
        
        menu.mostrarMenuPrincipal();
        escolha_menu = menu.receberOpcaoMenu();



        // código extra para limpar o terminal toda vez que o menu é reiniciado
		#ifdef linux
		system("clear");
		#endif
		#ifdef WIN32
		system("cls");
		#endif

		switch (escolha_menu) {


			case 1:  
				quiz.adicionarQuestao();

				break;

			case 2:
				cout << "\n|------------------------------------------------|"
			 		 << "\n|       ESCOLHA UMA QUESTÃO PELO SEU NÚMERO      |"
					 << "\n|------------------------------------------------|\n\n";
					 do {
					 	opcao = menu.receberOpcaoMenu();
					 	if (opcao == 0){
							 cout << "Erro - você deve digitar um número maior que 0";
					 	}
					 }while(opcao == 0);
				try{
				requisicao.deletar("https://apiflasklingprog.herokuapp.com/questoes/"+to_string(opcao));
				}
				catch(const erroQuestaoNaoExiste &erro){
					cerr << erro.what();
				}
				break;

			case 3:     
				questao = requisicao.get("https://apiflasklingprog.herokuapp.com/questoes/random");
				try{
					quiz.responderQuestao(questao);
				}
				catch(const erroQuestaoNaoExiste &erro){
					cerr << erro.what();
				}
				break;


			case 4:         
				cout << "\n|------------------------------------------------|"
			 		 << "\n|       ESCOLHA UMA QUESTÃO PELO SEU NÚMERO      |"
					 << "\n|------------------------------------------------|\n\n";
					 do {
					 	opcao = menu.receberOpcaoMenu();
					 	if (opcao == 0){
							 cout << "Erro - você deve digitar um número maior que 0";
					 	}
					 }while(opcao == 0);
				
				questao = requisicao.get("https://apiflasklingprog.herokuapp.com/questoes/"+to_string(opcao));
				try{
					quiz.responderQuestao(questao);
				}
				catch(const erroQuestaoNaoExiste &erro){
					cerr << erro.what();
				}

			 	break;
            
            case 5:
				quiz.mostrarPontuacao();
                 break;
            

            // SAIR DO PROGRAMA
			case 6:
				menu.finalizarPrograma();
                escolha_menu = 7;
				break;

            default:
                escolha_menu = 0;
                cout << "Opção Inválida - Tente Novamente" << endl;
            
	    }

    } while (escolha_menu != 7);

return 0;
}

