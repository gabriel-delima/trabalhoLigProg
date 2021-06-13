#include "quiz.h"
#include "requisicao.h"

void Quiz::setNovoAcerto(){
    numAcertos++;
}

void Quiz::setNovoErro(){
    numErros++;
}

unsigned int Quiz::getNumAcertos(){
    return numAcertos;
}

unsigned int Quiz::getNumErros(){
    return numErros;
}

void Quiz::mostrarPontuacao(){
    cout << "\n|----------------------------------------|"
         << "\n|     PONTUACAO OBTIDA ATÉ O MOMENTO     |"
         << "\n|----------------------------------------|"
         << "\n\n       Acertos :  "<< getNumAcertos()
         << "\n       Erros :    "<< getNumErros()
         << "\n\n       Total de Questões respondidas : "<< getNumErros() + getNumAcertos();
}

void Quiz::mostrarQuestao(string questaoJson){

    Json::Value root;   
    Json::Reader reader;
    
    bool parsingSuccessful = reader.parse( questaoJson.c_str(), root );


    if ( !parsingSuccessful ) {
        throw erroQuestaoNaoExiste();
    }

    cout << "|----------------------------------------------------|\n"
         << "    Questão de nº" << root.get("numero", "" ).asString() << "\n"
         << "|----------------------------------------------------| \n \n"
         << root.get("pergunta","").asString()<<"\n\n"
         << "1 - A)  " << root.get("opcaoA","").asString()<<"\n"    
         << "2 - B)  " << root.get("opcaoB","").asString()<<"\n"  
         << "3 - C)  " << root.get("opcaoC","").asString()<<"\n"  
         << "4 - D)  " << root.get("opcaoD","").asString()<<"\n";

}

bool Quiz::verificarResposta(string numeroQuestao, string resposta){
    Requisicao requisicao = Requisicao();
    string jsonResposta;
    string url = "apiflasklingprog.herokuapp.com/questoes/" + numeroQuestao;
    string body = "{\"resposta\":\""+resposta+"\"}";

    try{
    jsonResposta = requisicao.post(url,body);
    } 
    catch(const erroQuestaoNaoExiste &erro){
        cerr << erro.what();
    }

    Json::Value root;   
    Json::Reader reader;
    bool parsingSuccessful = reader.parse( jsonResposta.c_str(), root );
    if ( !parsingSuccessful ) {
        throw erroQuestaoNaoExiste();
    }

    if (root.get("resultado", "" ).asString() == "certo"){
        return true;
    }
    return false;
}

void Quiz::responderQuestao(string questaoJson){
    Menu menu = Menu();
    Json::Value root;   
    Json::Reader reader;
    bool parsingSuccessful = reader.parse( questaoJson.c_str(), root );
    if ( !parsingSuccessful ) {
        throw erroQuestaoNaoExiste();
    }
    mostrarQuestao(questaoJson);


    unsigned escolha;
    do {
        
        cout << "\n|-------------------------------------------------------|"
             << "\n|     ESCOLHA A OPÇÃO CORRESPONDENTE A SUA RESPOSTA     |"
             << "\n|-------------------------------------------------------|"
             << "\n|  1 - Opção A                                          |"
             << "\n|  2 - Opção B                                          |"
             << "\n|  3 - Opção C                                          |"
             << "\n|  4 - Opção D                                          |"
             << "\n|                                                       |"
             << "\n|  5 - DESISTIR DA PERGUNTA                             |"
             << "\n|-------------------------------------------------------|\n";
        escolha = menu.receberOpcaoMenu();

        switch (escolha) {
            case 1:
                if (verificarResposta(root.get("numero","").asString(),"A")){ 
                    
                       cout << "\n|----------------------|"
                            << "\n|   RESPOSTA CORRETA   |"
                            << "\n|----------------------|\n";
                            setNovoAcerto();
                }
                else {
                       cout << "\n|----------------------|"
                            << "\n|   RESPOSTA ERRADA    |"
                            << "\n|----------------------|\n";
                            setNovoErro();
                }
                escolha = 6;
                break;
            case 2:
                if (verificarResposta(root.get("numero","").asString(),"B")){ 
                    
                       cout << "\n|----------------------|"
                            << "\n|   RESPOSTA CORRETA   |"
                            << "\n|----------------------|\n";
                            setNovoAcerto();
                }
                else {
                       cout << "\n|----------------------|"
                            << "\n|   RESPOSTA ERRADA    |"
                            << "\n|----------------------|\n";
                            setNovoErro();
                }
                escolha = 6;
                break;
            case 3:
                if (verificarResposta(root.get("numero","").asString(),"C")){ 
                    
                       cout << "\n|----------------------|"
                            << "\n|   RESPOSTA CORRETA   |"
                            << "\n|----------------------|\n";
                            setNovoAcerto();
                }
                else {
                       cout << "\n|----------------------|"
                            << "\n|   RESPOSTA ERRADA    |"
                            << "\n|----------------------|\n";
                            setNovoErro();
                }
                escolha = 6;
                break;
            case 4:
                if (verificarResposta(root.get("numero","").asString(),"D")){ 
                    
                       cout << "\n|----------------------|"
                            << "\n|   RESPOSTA CORRETA   |"
                            << "\n|----------------------|\n";
                            setNovoAcerto();
                }
                else {
                       cout << "\n|----------------------|"
                            << "\n|   RESPOSTA ERRADA    |"
                            << "\n|----------------------|\n";
                            setNovoErro();
                }
                escolha = 6;
                break;

            case 5:
                escolha = 6;
                cout << "\n|-------------------------------------|"
                     << "\n|         TENTATIVA CANCELADA         |"
                     << "\n|-------------------------------------|\n\n";
                break;

            default:
                escolha = 0;
                cout << "Opção Inválida - Tente Novamente" << endl;
        }

    }while(escolha!=6);
}

void Quiz::adicionarQuestao(){
    string numeroEntrada;
    string respostaEntrada;
    string pergunta;
    string opcaoA;
    string opcaoB;
    string opcaoC;
    string opcaoD;
    string resposta;

    bool entradaInvalida2 = false;
    string respostaEntrada2;
    unsigned int numero2; 
    
    string body;
    Requisicao requisicao = Requisicao();

    unsigned int numero;
    bool entradaInvalida = false;

    cout << "\n|--------------------------------|"
         << "\n|    ADICIONANDO NOVA QUESTÃO    |"
         << "\n|--------------------------------|\n";

    cout << "  Digite o enunciado da questão: ";
    cin.ignore();
    getline(cin, pergunta);

    cout << "  Digite o texto para a alternativa A: ";
   
    getline(cin, opcaoA);


    cout << "  Digite o texto para a alternativa B: ";
   
    getline(cin, opcaoB);


    cout << "  Digite o texto para a alternativa C: ";
   
    getline(cin, opcaoC);


    cout << "  Digite o texto para a alternativa D: ";
   
    getline(cin, opcaoD);

    do{
        cout << "\n|---------------------|"
             << "\n|  OPCOES DE RESPOSTA |"
             << "\n|---------------------|\n"
             << "\n|    1 -  A)          |\n"
             << "\n|    2 -  B)          |\n"
             << "\n|    3 -  C)          |\n"
             << "\n|    4 -  D)          |\n"
             << "\n|---------------------|\n";  
        
        cout <<" Digite o número que corresponde à alternativa correta: ";
        cin >> respostaEntrada;
        entradaInvalida = false;
        try{
            numero = stoul(respostaEntrada); 
        }
        catch(...){
            cout << "\n|------------------------------------------------|"
                 << "\n|    ERRO - ENTRADA INVÁLIDA, DIGITE NOVAMENTE   |"
                 << "\n|------------------------------------------------|\n\n";
            entradaInvalida = true;
        }

        if (!entradaInvalida){
            switch (numero) {

            case 1:
                resposta = "A";

                    do{
                        cout << "\n|---------------------------------------------------------|"
                             << "\n|  Você tem certeza de que a alternatica A) é a correta?  |"
                             << "\n|---------------------------------------------------------|"
                             << "\n|  1 - SIM                                                |"
                             << "\n|  2 - MUDAR ALTERNATIVA                                  |"
                             << "\n|  3 - CANCELAR CRIAÇÃO DA QUESTÃO                        |"
                             << "\n|---------------------------------------------------------|\n";
                        
                        cout <<" Informe a opção escolhida: ";
                        cin >> respostaEntrada2;
                        entradaInvalida2 = false;
                        try{
                            numero2 = stoul(respostaEntrada2); 
                        }
                        catch(...){
                            cout << "\n|------------------------------------------------|"
                                 << "\n|    ERRO - ENTRADA INVÁLIDA, DIGITE NOVAMENTE   |"
                                 << "\n|------------------------------------------------|\n\n";
                            entradaInvalida2 = true;
                        }   
                        if (!entradaInvalida2){
                            switch (numero2){
                            case 1:
                                break;
                            case 2:
                                entradaInvalida = true;
                                break;
                            case 3:
                                return;
                            
                            default:
                                cout << "\n|------------------------------------------------|"
                                     << "\n|     ERRO - OPÇÃO INVÁLIDA, DIGITE NOVAMENTE    |"
                                     << "\n|------------------------------------------------|\n\n";
                                entradaInvalida = true;
                                break;                            
                            }
                        }
                    }while(entradaInvalida2);     
                break;
            
            case 2:
                resposta = "B";
                    do{
                        cout << "\n|---------------------------------------------------------|"
                             << "\n|  Você tem certeza de que a alternatica B) é a correta?  |"
                             << "\n|---------------------------------------------------------|"
                             << "\n|  1 - SIM                                                |"
                             << "\n|  2 - MUDAR ALTERNATIVA                                  |"
                             << "\n|  3 - CANCELAR CRIAÇÃO DA QUESTÃO                        |"
                             << "\n|---------------------------------------------------------|\n";
                        
                        cout <<" Informe a opção escolhida: ";
                        cin >> respostaEntrada2;
                        entradaInvalida2 = false;
                        try{
                            numero2 = stoul(respostaEntrada2); 
                        }
                        catch(...){
                            cout << "\n|------------------------------------------------|"
                                 << "\n|    ERRO - ENTRADA INVÁLIDA, DIGITE NOVAMENTE   |"
                                 << "\n|------------------------------------------------|\n\n";
                            entradaInvalida2 = true;
                        }   
                        if (!entradaInvalida2){
                            switch (numero2){
                            case 1:
                                break;
                            case 2:
                                entradaInvalida = true;
                                break;
                            case 3:
                                return;
                            
                            default:
                                cout << "\n|------------------------------------------------|"
                                     << "\n|     ERRO - OPÇÃO INVÁLIDA, DIGITE NOVAMENTE    |"
                                     << "\n|------------------------------------------------|\n\n";
                                entradaInvalida = true;
                                break;                            
                            }
                        }
                    }while(entradaInvalida2);     
                break;
            
            case 3:
                resposta = "C";
                    do{
                        cout << "\n|---------------------------------------------------------|"
                             << "\n|  Você tem certeza de que a alternatica C) é a correta?  |"
                             << "\n|---------------------------------------------------------|"
                             << "\n|  1 - SIM                                                |"
                             << "\n|  2 - MUDAR ALTERNATIVA                                  |"
                             << "\n|  3 - CANCELAR CRIAÇÃO DA QUESTÃO                        |"
                             << "\n|---------------------------------------------------------|\n";
                        
                        cout <<" Informe a opção escolhida: ";
                        cin >> respostaEntrada2;
                        entradaInvalida2 = false;
                        try{
                            numero2 = stoul(respostaEntrada2); 
                        }
                        catch(...){
                            cout << "\n|------------------------------------------------|"
                                 << "\n|    ERRO - ENTRADA INVÁLIDA, DIGITE NOVAMENTE   |"
                                 << "\n|------------------------------------------------|\n\n";
                            entradaInvalida2 = true;
                        }   
                        if (!entradaInvalida2){
                            switch (numero2){
                            case 1:
                                break;
                            case 2:
                                entradaInvalida = true;
                                break;
                            case 3:
                                return;
                            
                            default:
                                cout << "\n|------------------------------------------------|"
                                     << "\n|     ERRO - OPÇÃO INVÁLIDA, DIGITE NOVAMENTE    |"
                                     << "\n|------------------------------------------------|\n\n";
                                entradaInvalida = true;
                                break;                            
                            }
                        }
                    }while(entradaInvalida2);     
                break;
            
            case 4:
                resposta = "D";
                    do{
                        cout << "\n|---------------------------------------------------------|"
                             << "\n|  Você tem certeza de que a alternatica D) é a correta?  |"
                             << "\n|---------------------------------------------------------|"
                             << "\n|  1 - SIM                                                |"
                             << "\n|  2 - MUDAR ALTERNATIVA                                  |"
                             << "\n|  3 - CANCELAR CRIAÇÃO DA QUESTÃO                        |"
                             << "\n|---------------------------------------------------------|\n";
                        
                        cout <<" Informe a opção escolhida: ";
                        cin >> respostaEntrada2;
                        entradaInvalida2 = false;
                        try{
                            numero2 = stoul(respostaEntrada2); 
                        }
                        catch(...){
                            cout << "\n|------------------------------------------------|"
                                 << "\n|    ERRO - ENTRADA INVÁLIDA, DIGITE NOVAMENTE   |"
                                 << "\n|------------------------------------------------|\n\n";
                            entradaInvalida2 = true;
                        }   
                        if (!entradaInvalida2){
                            switch (numero2){
                            case 1:
                                break;
                            case 2:
                                entradaInvalida = true;
                                break;
                            case 3:
                                return;
                            
                            default:
                                cout << "\n|------------------------------------------------|"
                                     << "\n|     ERRO - OPÇÃO INVÁLIDA, DIGITE NOVAMENTE    |"
                                     << "\n|------------------------------------------------|\n\n";
                                entradaInvalida = true;
                                break;                            
                            }
                        }
                    }while(entradaInvalida2);     
                break;

            default:
                cout << "\n|------------------------------------------------|"
                     << "\n|     ERRO - OPÇÃO INVÁLIDA, DIGITE NOVAMENTE    |"
                     << "\n|------------------------------------------------|\n\n";
                entradaInvalida = true;
                break;
            }
        }
        
    }while (entradaInvalida);    

    do{
        cout <<" Digite o número que será associado à questão: ";
        cin >> numeroEntrada;
        entradaInvalida = false;
        try{
            numero = stoul(numeroEntrada); 
        }
        catch(...){
            cout << "\n|------------------------------------------------|"
                 << "\n|    ERRO - NÚMERO INVÁLIDO, DIGITE NOVAMENTE    |"
                 << "\n|------------------------------------------------|\n\n";
            entradaInvalida = true;
        }
        if (!entradaInvalida){

                body = "{ \"numero\": "+to_string(numero)+", \"pergunta\": \""+pergunta+"\", \"opcaoA\": \""+opcaoA+"\", \"opcaoB\": \""+opcaoB+"\", \"opcaoC\": \""+opcaoC+"\", \"opcaoD\": \""+opcaoD+"\", \"resposta\": \""+resposta+"\"}";
            
                requisicao.post("apiflasklingprog.herokuapp.com/questoes",body);
        }

    }while (entradaInvalida);    

}
