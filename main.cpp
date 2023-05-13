#include "funcoes.h"

int main(int argc, char **argv){

    // Abra o arquivo CSV para leitura
    ifstream arq(FILE_IP);

    arvore<Ip>tab_ip;

    // Verifique se o arquivo foi aberto com sucesso
    if (arq.is_open()) {
        // ao abrir o arquivo já chama a função "obtem_tab_ip" para obter uma tab hash contendo como chave o IP e valor o Cód da localizaçao do arquivo lido
        tab_ip = obtem_tabela_ip(arq);
        arq.close(); // fecha o arquivo de GeoLite2-City-Blocks-IPv4.csv
    } else{
        cerr << "Erro ao abrir o arquivo." << endl;
        return 1;
    }

    // Abra o segundo arquivo CSV para leitura
    ifstream arq_local(FILE_LOCALIZACAO);

    arvore<GeoLoc> tab_localizacao;

    // Verifique se o arquivo foi aberto com sucesso
    if (arq_local.is_open()) {
        // ao abrir o arquivo já chama a função para obter a tabela hash contendo como chave o Cód da localizaçao e valor o pais e cidade
        tab_localizacao = obtem_tab_localizacao(arq_local);
        arq_local.close(); // fecha o arquivo de GeoLite2-City-Locations-pt-BR.csv
    } else{
        cerr << "Erro ao abrir o arquivo." << endl;
        return 1;
    }

    // Imprimi o menu de explicação do programa antes de entrar no loop de consulta
    imprimirMenu();

    // chama a função "obtem_localizacao_IP" para entrar no LOOP  de consulta, e buscar a localização do IP digitado pelo usuário
    obtem_localizacao_IP(tab_ip, tab_localizacao);

    return 0;

}