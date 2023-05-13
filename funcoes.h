#ifndef PROJETO02_PROG_FUNCOES_H
#define PROJETO02_PROG_FUNCOES_H

// criação de constantes para definir os arquivos usados no código

#define FILE_IP "GeoLite2-City-Blocks-IPv4.csv"
#define FILE_LOCALIZACAO "GeoLite2-City-Locations-pt-BR.csv"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <prglib.h>
#include <unordered_map>


using namespace std;
using prglib::arvore;

struct GeoLoc {
    string pais, cidade, cod_local; // strings para armazenar a localização do ip
};

struct Ip {
    string chave, valor;
};

void imprimirMenu();
vector<string> separa(string & algo, string delimitador);
// unordered_map<string,string>obtem_tab_ip(ifstream & arq);
bool func_comparadora(const Ip & ip1, const Ip & ip2);
bool funcao_comparadora(const GeoLoc & ip1, const GeoLoc & ip2);
arvore<GeoLoc> obtem_tab_localizacao(ifstream & arq_local);
void obtem_localizacao_IP(arvore<Ip>& tab_ip, arvore<GeoLoc>& tab_localizacao);
arvore<Ip>obtem_tabela_ip(ifstream & arq);



#endif //PROJETO02_PROG_FUNCOES_H