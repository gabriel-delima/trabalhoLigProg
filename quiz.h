#ifndef QUIZ_H
#define QUIZ_H

#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>
#include <jsoncpp/json/value.h>

#include "requisicao.h"
#include "menu.h"


class Quiz{

    public:
        Quiz(){};
        void setNovoAcerto();
        void setNovoErro();
        unsigned int getNumAcertos();
        unsigned int getNumErros();
        void mostrarQuestao(string questaoJson);
        bool verificarResposta(string numeroQuestao, string resposta);
        void responderQuestao(string questaoJson);
        void deletarQuestao();
        void mostrarPontuacao();
        void adicionarQuestao();

    private:
        unsigned int numAcertos = 0;
        unsigned int numErros = 0;
};
#endif