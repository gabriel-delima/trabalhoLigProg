#include "requisicao.h"
#include "excecao.h"
#include <curl/curl.h>


size_t Requisicao::WriteCallBack(char *contents, size_t size, size_t nmemb, char*buffer_in){
    ((string*)buffer_in)->append((char*)contents, size *nmemb);
    return size *nmemb;
}

string Requisicao::curlRequisicaoGet(string url){
    CURL *curl;
    CURLcode res;
    string readBuffer;

    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallBack);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        switch (res){

        case 0:
            return readBuffer;
            break;
        case 1:
            throw erroProtocoloNaoSuportado();
        case 3:
            throw erroUrlFormatoInvalido();
        case 6:
        case 7:
            throw erroProblemaConexao();
        default:
            throw erroGenericoRequisicao();
            break;
        }
    }
    else{
        throw erroCurlNaoReconhecido();
    }
}

string Requisicao::curlRequisicaoPost(string url, string body){
    CURL *curl;
    CURLcode res;
    string readBuffer;
    long http_code = 0;

    curl = curl_easy_init();

    if(curl) {
        /* header */
        struct curl_slist *hs = NULL;
        hs = curl_slist_append(hs, "Accept : application/json");
        hs = curl_slist_append(hs, "Content-Type : application/json");
        hs = curl_slist_append(hs, "charsets : utf-8");
        
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, hs);
        
        /* definir metodos post*/        
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, body.length());
        curl_easy_setopt(curl, CURLOPT_POST, true);

        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 120);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallBack);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        
        res = curl_easy_perform(curl);
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        curl_easy_cleanup(curl);
        if (http_code == 404){
            throw erroQuestaoNaoExiste();
        }
        switch (res){

        case 0:
            return readBuffer;
            break;
        case 1:
            throw erroProtocoloNaoSuportado();
        case 3:
            throw erroUrlFormatoInvalido();
        case 6:
        case 7:
            throw erroProblemaConexao();
        default:
            throw erroGenericoRequisicao();
            break;
        }
    }
    else{
        throw erroCurlNaoReconhecido();
    }
}

string Requisicao::curlRequisicaoDeletar(string url){
    CURL *curl;
    CURLcode res;
    string readBuffer;
    long http_code = 0;

    curl = curl_easy_init();

    if(curl) {

        /* header */
        struct curl_slist *hs = NULL;
        hs = curl_slist_append(hs, "Accept : application/json");
        hs = curl_slist_append(hs, "Content-Type : application/json");
        hs = curl_slist_append(hs, "charsets : utf-8");
        
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "");
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, hs);

        /* definir metodos delete*/        
        curl_easy_setopt(curl,CURLOPT_CUSTOMREQUEST,"DELETE");

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 120);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallBack);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        curl_easy_cleanup(curl);

        if (http_code == 404){
            throw erroQuestaoNaoExiste();
        }
        switch (res){

        case 0:
            return readBuffer;
            break;
        case 1:
            throw erroProtocoloNaoSuportado();
        case 3:
            throw erroUrlFormatoInvalido();
        case 6:
        case 7:
            throw erroProblemaConexao();
        default:
            throw erroGenericoRequisicao();
            break;
        }
    }
    else{
        throw erroCurlNaoReconhecido();
    }
}

string Requisicao::deletar(string url){
    string buffer;

    try{
        buffer = curlRequisicaoDeletar(url); 
    } catch(const erroProtocoloNaoSuportado &erro){
		cerr << erro.what();
	} catch(const erroUrlFormatoInvalido &erro){
		cerr << erro.what();
	} catch(const erroProblemaConexao &erro){
		cerr << erro.what();
	} catch(const erroGenericoRequisicao &erro){
		cerr << erro.what();
	} catch(const erroCurlNaoReconhecido &erro){
		cerr << erro.what();
	} 

    return buffer;  
}


string Requisicao::post(string url, string body){
    string buffer;

    try{
        buffer = curlRequisicaoPost(url, body); 
    } catch(const erroProtocoloNaoSuportado &erro){
		cerr << erro.what();
	} catch(const erroUrlFormatoInvalido &erro){
		cerr << erro.what();
	} catch(const erroProblemaConexao &erro){
		cerr << erro.what();
	} catch(const erroGenericoRequisicao &erro){
		cerr << erro.what();
	} catch(const erroCurlNaoReconhecido &erro){
		cerr << erro.what();
	} 

    return buffer;   
} 

string Requisicao::get(string url){
    string buffer;

    try{
        buffer = curlRequisicaoGet(url); 
    } catch(const erroProtocoloNaoSuportado &erro){
		cerr << erro.what();
	} catch(const erroUrlFormatoInvalido &erro){
		cerr << erro.what();
	} catch(const erroProblemaConexao &erro){
		cerr << erro.what();
	} catch(const erroGenericoRequisicao &erro){
		cerr << erro.what();
	} catch(const erroCurlNaoReconhecido &erro){
		cerr << erro.what();
    } catch(const erroQuestaoNaoExiste &erro){
		cerr << erro.what();
	} 

    return buffer;   
} 