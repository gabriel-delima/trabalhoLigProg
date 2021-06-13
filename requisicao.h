#ifndef REQUISICAO_H
#define REQUISICAO_H

#include <iostream>
#include <string>
#include <curl/curl.h>

#include "excecao.h"

using namespace std;

class Requisicao{
    public:
        Requisicao(){};
        string get(string url);
        string post(string url, string body);
        string deletar(string url);

    
    private:
        string curlRequisicaoGet(string url);
        string curlRequisicaoPost(string url, string body);
        string curlRequisicaoDeletar(string url);
        static size_t WriteCallBack(char *contents, size_t size, size_t nmemb, char*buffer_in);

};

#endif