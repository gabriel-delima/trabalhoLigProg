
#include <iostream>
#include <string>



#include "requisicao.h"
#include "excecao.h"
using namespace std;



int main() {

    Requisicao requisicao = Requisicao();

    cout << requisicao.get("https://loripsum.net/api/plaintext"); 

return 0;
}
