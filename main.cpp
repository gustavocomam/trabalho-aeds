#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Tamanhos da fila

#define TAM_FILA_PASSAGEIROS    10
#define TAM_FILA_ESPERA         5

// Numero de voo

#define BH_RIO          0
#define BH_SP           1
#define BH_BRASILIA     2

// TAD Horario

typedef struct Horario {
    int horas;
    int minutos;
}Horario;

// TAD Passageiro

typedef struct Passageiro {
    string CPF;
    string nome;
    string endereco;
    string telefone;
    int numeroPassagem;
    int numeroPoltrona;
    int numeroVoo;
    Horario horario;
}Passageiro;

// TAD Voo

typedef struct Voo{
    int qtdPassageiros;
    int qtdListaEspera;
    Passageiro listaPassageiro[TAM_FILA_PASSAGEIROS];
    Passageiro listaEspera[TAM_FILA_ESPERA];
}Voo;

// Imprime os dados de um Passageiro

void imprimirPassageiro(Passageiro passageiro) {
    cout << "----------------------------------------------------------" << endl;
    cout << "CPF: " << passageiro.CPF << endl;
    cout << "Nome: " << passageiro.nome << endl;
    cout << "Endereço: " << passageiro.endereco << endl;
    cout << "Telefone: " << passageiro.telefone << endl;
    cout << "Número da Passagem: " << passageiro.numeroPassagem << endl;
    cout << "Número da Poltrona: " << passageiro.numeroPoltrona << endl;
    cout << "Número do Voo: " << passageiro.numeroVoo << endl;
    cout << "Horário: " << passageiro.horario.horas << ":" << passageiro.horario.minutos << endl;
}

// Recebe dados de um passageiro e retorna o mesmo

Passageiro lerDadosPassageiro(int numeroVoo){
    Passageiro passageiro;

    cout << "CPF: ";
    cin >> passageiro.CPF;

    cout << "Nome: ";
    cin.ignore();
    getline(cin, passageiro.nome);

    cout << "Endereço: ";
    getline(cin, passageiro.endereco);

    cout << "Telefone: ";
    cin.ignore();
    cin >> passageiro.telefone;

    cout << "Número da Passagem: ";
    cin >> passageiro.numeroPassagem;

    cout << "Número da Poltrona: ";
    cin >> passageiro.numeroPoltrona;

    passageiro.numeroVoo = numeroVoo;

    cout << "Horário (horas minutos): ";
    cin >> passageiro.horario.horas >> passageiro.horario.minutos;

    return passageiro;
}

// Escrever dados de voo em um arquivo

void escreverVoo(ofstream& arquivo, Voo voo) {
    arquivo << voo.qtdPassageiros << " " << voo.qtdListaEspera << std::endl;

    for (int i = 0; i < voo.qtdPassageiros; i++) {
        arquivo << voo.listaPassageiro[i].CPF << std::endl;
        arquivo << voo.listaPassageiro[i].nome << std::endl;
        arquivo << voo.listaPassageiro[i].endereco << std::endl;
        arquivo << voo.listaPassageiro[i].telefone << std::endl;
        arquivo << voo.listaPassageiro[i].numeroPassagem << std::endl;
        arquivo << voo.listaPassageiro[i].numeroPoltrona << std::endl;
        arquivo << voo.listaPassageiro[i].numeroVoo << std::endl;
        arquivo << voo.listaPassageiro[i].horario.horas << std::endl;
        arquivo << voo.listaPassageiro[i].horario.minutos << std::endl;
    }

    for (int i = 0; i < voo.qtdListaEspera; i++) {
        arquivo << voo.listaEspera[i].CPF << std::endl;
        arquivo << voo.listaEspera[i].nome << std::endl;
        arquivo << voo.listaEspera[i].endereco << std::endl;
        arquivo << voo.listaEspera[i].telefone << std::endl;
        arquivo << voo.listaEspera[i].numeroPassagem << std::endl;
        arquivo << voo.listaEspera[i].numeroPoltrona << std::endl;
        arquivo << voo.listaEspera[i].numeroVoo << std::endl;
        arquivo << voo.listaEspera[i].horario.horas << std::endl;
        arquivo << voo.listaEspera[i].horario.minutos << std::endl;
    }
}

// Ler dados de um determinado Voo a patir de um arquivo

Voo lerVoo(ifstream& arquivo) {
    Voo voo;

    arquivo >> voo.qtdPassageiros >> voo.qtdListaEspera;
    arquivo.ignore();

    for (int i = 0; i < voo.qtdPassageiros; i++) {
        getline(arquivo, voo.listaPassageiro[i].CPF);
        getline(arquivo, voo.listaPassageiro[i].nome);
        getline(arquivo, voo.listaPassageiro[i].endereco);
        getline(arquivo, voo.listaPassageiro[i].telefone);
        arquivo >> voo.listaPassageiro[i].numeroPassagem;
        arquivo >> voo.listaPassageiro[i].numeroPoltrona;
        arquivo >> voo.listaPassageiro[i].numeroVoo;
        arquivo >> voo.listaPassageiro[i].horario.horas;
        arquivo >> voo.listaPassageiro[i].horario.minutos;
        arquivo.ignore();
    }

    arquivo.ignore();

    for (int i = 0; i < voo.qtdPassageiros; i++) {
        getline(arquivo, voo.listaPassageiro[i].CPF);
        getline(arquivo, voo.listaPassageiro[i].nome);
        getline(arquivo, voo.listaPassageiro[i].endereco);
        getline(arquivo, voo.listaPassageiro[i].telefone);
        arquivo >> voo.listaPassageiro[i].numeroPassagem;
        arquivo >> voo.listaPassageiro[i].numeroPoltrona;
        arquivo >> voo.listaPassageiro[i].numeroVoo;
        arquivo >> voo.listaPassageiro[i].horario.horas;
        arquivo >> voo.listaPassageiro[i].horario.minutos;
        arquivo.ignore();
    }

    return voo;
}

// Apresenta menu secundario

void menuSecundario(int numeroVoo){
    ifstream arquivo;

    if (numeroVoo == BH_RIO){
        arquivo.open("rio.txt");
    }else if (numeroVoo == BH_SP){
        arquivo.open("sp.txt");
    }else {
        arquivo.open("brasilia.txt");
    }

    if(!arquivo.is_open()){
        cout << "[ERRO] Nao foi possivel abrir o arquivo de leitura";
        return;
    }

    Voo voo = lerVoo(arquivo);

    int opcao;

    string CPF, nome;

    while(true){
        system("clear");

        if(numeroVoo == BH_RIO){
            cout << "EMPRESA AÉREA QUEDA LIVRE - VOO BH-RIO" << endl;
        }else if(numeroVoo == BH_SP){
            cout << "EMPRESA AÉREA QUEDA LIVRE - VOO BH-SP" << endl;
        }else{
            cout << "EMPRESA AÉREA QUEDA LIVRE - VOO BH-BRASILIA" << endl;
        }

        cout << "MENU DE OPÇÕES\n[1] Mostrar Lista de Passageiros\n[2] Pesquisar Passageiro por CPF\n[3] Pesquisar Passageiro por Nome\n[4] Cadastrar Passageiro\n[5] Excluir Passageiro da Lista\n[6] Mostrar Fila de Espera\n[9] Sair\nDigite sua opção: ";

        cin >> opcao;

        if(opcao == 1){
            for(int i = 0; i < voo.qtdPassageiros; i++){
                imprimirPassageiro(voo.listaPassageiro[i]);
            }
        }else if(opcao == 2){
            cout << "CPF: ";
            cin >> CPF;
            bool encontrou = false;
            for(int i = 0; i < voo.qtdPassageiros; i++){
                if(voo.listaPassageiro[i].CPF == CPF){
                    imprimirPassageiro(voo.listaPassageiro[i]);
                    encontrou = true;
                }
            }
            if(!encontrou){
                cout << "[ERRO] Passageiro não consta neste voo" << endl;
            }
        }else if(opcao == 3){
            cout << "Nome: ";
            cin.ignore();
            getline(cin, nome);

            bool encontrou = false;
            for(int i = 0; i < voo.qtdPassageiros; i++){
                if(voo.listaPassageiro[i].nome == nome){
                    imprimirPassageiro(voo.listaPassageiro[i]);
                    encontrou = true;
                }
            }
            if(!encontrou){
                cout << "[ERRO] Passageiro não consta neste voo" << endl;
            }
        }else if(opcao == 4){
            if(voo.qtdPassageiros == TAM_FILA_PASSAGEIROS && voo.qtdListaEspera == TAM_FILA_ESPERA){
                cout << "[ERRO] Fila Cheia, a reserva não pode ser feita" << endl;   
            }else{
                Passageiro passageiro = lerDadosPassageiro(numeroVoo);
                if(voo.qtdPassageiros < TAM_FILA_PASSAGEIROS){
                    voo.listaPassageiro[voo.qtdPassageiros] = passageiro;
                    voo.qtdPassageiros++;
                }else{
                    voo.listaEspera[voo.qtdListaEspera] = passageiro;
                    voo.qtdListaEspera++;
                }
            }
        }else if(opcao == 5){
            cout << "CPF: ";
            cin >> CPF;
            bool encontrou = false;
            int indice = -1;
            for(int i = 0; i < voo.qtdPassageiros; i++){
                if(voo.listaPassageiro[i].CPF == CPF){
                    encontrou = true;
                    indice = i;
                }
            }
            if(!encontrou){
                cout << "[ERRO] Passageiro não consta neste voo" << endl;
            }else{
                for (int i = indice + 1; i < voo.qtdPassageiros; i++){
                    voo.listaPassageiro[i - 1] = voo.listaPassageiro[i];
                }

                if(voo.qtdPassageiros == TAM_FILA_PASSAGEIROS && voo.qtdListaEspera > 0){
                    voo.listaPassageiro[voo.qtdPassageiros - 1] = voo.listaEspera[0];
                    for (int i = 1; i < voo.qtdListaEspera; i++){
                        voo.listaEspera[i - 1] = voo.listaEspera[i];
                    }                
                    voo.qtdListaEspera--;
                }else{
                    voo.qtdPassageiros--;
                }
            }
        }else if(opcao == 6){
            for(int i = 0; i < voo.qtdListaEspera; i++){
                imprimirPassageiro(voo.listaEspera[i]);
            }
        }else if(opcao == 9){
            break;
        }else{
            cout << "[ERRO] Opcao Invalida" << endl;
        }
    }

    arquivo.close();

    ofstream arquivoSaida;

    if(numeroVoo == BH_RIO){
        arquivoSaida.open("rio.txt");
    }else if(numeroVoo == BH_SP){
        arquivoSaida.open("sp.txt");
    }else{
        arquivoSaida.open("brasilia.txt");
    }

    if(!arquivoSaida.is_open()){
        cout << "[ERRO] Nao foi possivel abrir o arquivo de saida";
        return;
    }

    escreverVoo(arquivoSaida, voo);

    arquivoSaida.close();
}

// Apresenta menu principal

void menuPrincipal(){

    while(true){
        system("clear");

        int opcao;
        cout << "Digite:\n0 - VOO BH-RIO\n1 - VOO BH-SP\n2 - VOO BH-BRASILIA\n3 - Sair" << endl;
        cin >> opcao;
        if(opcao >= 0 && opcao <= 2){
            menuSecundario(opcao);
        }else if(opcao == 3){
            cout << "Voce saiu" << endl;
            break;
        }else{
            cout << "[ERRO] Opcao Invalida" << endl;
        }
    }
}

int main(){

    menuPrincipal();

    return 0;
}