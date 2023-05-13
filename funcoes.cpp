#include "funcoes.h"

vector<string> separa(string & algo, string delimitador) {
    vector<string> sequencia; // vetor de strings vazio que irá armazenar as partes separadas da string "algo"
    size_t pos = 0; // variável usada para armazenar a posição onde o delimitador é encontrado
    string trecho; // "trecho" é uma string que será usada para armazenar cada parte separada da string original

    // loop que será executado até que não haja mais ocorrências do delimitador na string "algo"
    // se a função "find" retornar "npos", significa que não há mais ocorrências do delimitador na string "algo", e para o loop
    while ((pos = algo.find(delimitador)) != string::npos) {
        trecho = algo.substr(0, pos); // função "substr" é usada para extrair o trecho da string "algo" que vai desde o início até a posição do delim
        sequencia.push_back(trecho); // o trecho separado é adicionado ao final do vetor "sequencia"
        algo.erase(0, pos + delimitador.length()); // função "erase" é usada para remover o trecho já separado da string "algo"
    }
    sequencia.push_back(algo); // ultima parte da string "algo" é adicionado ao final do vetor "sequencia"
    return sequencia;
}

bool func_comparadora(const Ip & ip1, const Ip & ip2) {
    return ip1.chave.size() < ip2.chave.size();
}


arvore<Ip>obtem_tabela_ip(ifstream & arq){
    Ip ip_lido;
    string linha, name_col;
    getline(arq, name_col); // ler a primeira linha do arquivo, que é o nome das colunas do csv

    // cria uma árvore a partir do arquivo para armazenar os IPs e Códigos da geolocalização
    auto tabela_de_ip = prglib::cria_arvore<Ip>(func_comparadora);

    //laço para obter o ip e o código da geolocalização do arquivo GeoLite2-City-Blocks-IPv4.csv
    while (getline(arq, linha)){

        // separa as informações da linha do arquivo usando delimitado ",", atraveś da função separa declarada em funcoes.cpp
        auto colunas = separa(linha, ",");

        auto geoname_id = colunas[1]; // obtem do vector colunas o cód da localização

        // chama a função separa para conseguir obter apenas o ip sem a máscara do vector colunas
        auto ip = separa(colunas[0], "/");

        ip_lido.chave = ip[0];
        ip_lido.valor = geoname_id;

        tabela_de_ip.adiciona(ip_lido);

    }
    return tabela_de_ip;
}


/*
unordered_map<string,string>obtem_tab_ip(ifstream & arq){
    string linha, name_col;
    getline(arq, name_col); // ler a primeira linha do arquivo, que é o nome das colunas do csv

    unordered_map<string,string> tabela_ip; // cria uma tabela hash para armazenar os IPs e Códigos da geolocalização

    //laço para obter o ip e o código da geolocalização do arquivo GeoLite2-City-Blocks-IPv4.csv
    while (getline(arq, linha)){

        // separa as informações da linha do arquivo usando delimitado ",", atraveś da função separa declarada em funcoes.cpp
        auto colunas = separa(linha, ",");

        auto geoname_id = colunas[1]; // obtem do vector colunas o cód da localização

        // chama a função separa para conseguir obter apenas o ip sem a máscara do vector colunas
        auto ip = separa(colunas[0], "/");

        tabela_ip.emplace(ip[0], geoname_id);
    }
    return tabela_ip;
}

*/

bool funcao_comparadora(const GeoLoc & ip1, const GeoLoc & ip2) {
    return ip1.cod_local.size() < ip2.cod_local.size();
}

arvore<GeoLoc> obtem_tab_localizacao(ifstream & arq_local){
    string linha, name_col, cod_local;
    GeoLoc local; // struct para armazenar em uma variável o pais e a cidade

    getline(arq_local, name_col); // ler a primeira linha do arquivo, que é o nome das colunas do csv

    // criando uma tabela para armazenar o país e cidade referente a um certo código de localização
    auto tabela_localizacao = prglib::cria_arvore<GeoLoc>(funcao_comparadora);

    //laço para obter o país e a cidade da localização de um certo ip
    while (getline(arq_local, linha)){

        auto colunas = separa(linha, ",");
        auto cidade = separa(colunas[12], "/");
        local.cod_local = colunas[0];
        local.pais = colunas[5];
        if (cidade.size() >= 2) {
            local.cidade = cidade[1];
        } else {
            local.cidade = ""; // se não tiver a informação de cidade, deixa como padrão uma string vazia
        }
        tabela_localizacao.adiciona(local);
    }
    return tabela_localizacao;
}

/*
unordered_map<string, GeoLoc> obtem_tab_localizacao(ifstream & arq_local){
    string linha, name_col, cod_local;
    GeoLoc local; // struct para armazenar em uma variável o pais e a cidade

    getline(arq_local, name_col); // ler a primeira linha do arquivo, que é o nome das colunas do csv

    // criando uma tabela para armazenar o país e cidade referente a um certo código de localização
    unordered_map<string, GeoLoc> tabela_localizacao;

    //laço para obter o país e a cidade da localização de um certo ip
    while (getline(arq_local, linha)){

        auto colunas = separa(linha, ",");
        auto cidade = separa(colunas[12], "/");
        cod_local = colunas[0];
        local.pais = colunas[5];
        if (cidade.size() >= 2) {
            local.cidade = cidade[1];
        } else {
            local.cidade = ""; // se não tiver a informação de cidade, deixa como padrão uma string vazia
        }
        tabela_localizacao.emplace(cod_local, local);
    }
    return tabela_localizacao;
}

*/


void imprimirMenu() {
    cout << endl << "Geolocalizador IP" << endl << endl;
    cout << "Para consultar a localizacao de um IP, basta digitar um IP valido e clicar 'enter'. EX: 1.0.0.0" << endl;
    cout << "Para sair do programa, basta digitar 'sair' e clicar no Enter, ou apenas clicar no Enter sem digitar nada." << endl << endl;
}


void obtem_localizacao_IP(arvore<Ip>& tab_ip, arvore<GeoLoc>& tab_localizacao) {
    // loop para obter o ip do usuário com uma única execução do geolocalizador e permitir ser possível realizar múltiplas consultas
    while (true) {
        cout << "Digite o IP >>  ";
        Ip entrada;
        GeoLoc geo_loc;
        getline(cin, entrada.chave);
        // Se o usuário digitar apenas enter ou "sair", finaliza a função
        if (entrada.chave.empty() || entrada.chave == "sair") {
            break;
        }
        // o IF abaixo verifica se o IP digitado existe na tabela hash usando a função "count()", e retorna o nº de elementos com a chave especificada na tab hash
        if (tab_ip.existe(entrada) > 0) {
            //armazena o cód da geoloc referente ao ip digitado usando o acesso direto pelo operador "[]"
            auto cod_local = tab_ip.obtem(entrada);

            geo_loc.cod_local = cod_local.valor;

            //consulta a segunda tabela hash criada e obtem o país e a cidade referente ao ip digitado pelo usuário

            auto geo_localizacao = tab_localizacao.obtem(geo_loc);

            auto geo_pais = geo_loc.pais;
            auto geo_cidade = geo_loc.cidade;

            cout << "Local: " << geo_pais << ", " << geo_cidade << endl;
        } else {
            cout << "IP " << entrada.chave << " desconhecido" << endl;
        }
        cout << endl;
    }
}
