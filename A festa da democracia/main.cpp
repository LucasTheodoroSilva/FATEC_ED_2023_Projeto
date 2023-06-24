#include <iostream>
#include <fstream>
#include <string>
#include <locale>
using namespace std;
const string CANDIDATES_FILE = "candidatos.txt";
const string VOTERS_FILE = "eleitores.txt";
const string VOTES_FILE = "votos.txt";
const string REPORT_FILE = "relatorio.txt";

struct Candidato {
    string nome;
    int numero;
    Candidato* proximo;
};

struct Eleitor {
    string nome;
    int titulo;
    Eleitor* proximo;
};

struct Voto {
    int numeroCandidato;
    Voto* proximo;
};

Candidato* candidatos = NULL;
Eleitor* eleitores = NULL;
Voto* votos = NULL;

void cadastrarCandidato(const string& nome, int numero) {
    Candidato* novoCandidato = new Candidato;
    novoCandidato->nome = nome;
    novoCandidato->numero = numero;
    novoCandidato->proximo = NULL;

    if (candidatos == NULL) {
        candidatos = novoCandidato;
    } else {
        Candidato* atual = candidatos;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novoCandidato;
    }
}

void removerCandidato(int numero) {
    if (candidatos != NULL) {
        if (candidatos->numero == numero) {
            Candidato* temp = candidatos;
            candidatos = candidatos->proximo;
            delete temp;
            return;
        }

        Candidato* atual = candidatos;
        while (atual->proximo != NULL) {
            if (atual->proximo->numero == numero) {
                Candidato* temp = atual->proximo;
                atual->proximo = atual->proximo->proximo;
                delete temp;
                return;
            }
            atual = atual->proximo;
        }
    }
}

void listarCandidatos() {
    if (candidatos == NULL) {
        cout << "Não há candidato cadastrado." << endl;
    } else {
        Candidato* atual = candidatos;
        while (atual != NULL) {
            cout << "Nome: " << atual->nome << ", Número: " << atual->numero << endl;
            atual = atual->proximo;
        }
    }
}

void carregarCandidatos() {
    ifstream arquivo(CANDIDATES_FILE.c_str());
    if (arquivo.is_open()) {
        string nome;
        int numero;
        while (arquivo >> nome >> numero) {
            cadastrarCandidato(nome, numero);
        }
        arquivo.close();
    }
}

void salvarCandidatos() {
    ofstream arquivo(CANDIDATES_FILE.c_str());
    if (arquivo.is_open()) {
        Candidato* atual = candidatos;
        while (atual != NULL) {
            arquivo << atual->nome << " " << atual->numero << endl;
            atual = atual->proximo;
        }
        arquivo.close();
    }
}

void cadastrarEleitor(const string& nome, int titulo) {
    Eleitor* novoEleitor = new Eleitor;
    novoEleitor->nome = nome;
    novoEleitor->titulo = titulo;
    novoEleitor->proximo = NULL;

    if (eleitores == NULL) {
        eleitores = novoEleitor;
    } else {
        Eleitor* atual = eleitores;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novoEleitor;
    }
}

void removerEleitor(int titulo) {
    if (eleitores != NULL) {
        if (eleitores->titulo == titulo) {
            Eleitor* temp = eleitores;
            eleitores = eleitores->proximo;
            delete temp;
            return;
        }

        Eleitor* atual = eleitores;
        while (atual->proximo != NULL) {
            if (atual->proximo->titulo == titulo) {
                Eleitor* temp = atual->proximo;
                atual->proximo = atual->proximo->proximo;
                delete temp;
                return;
            }
            atual = atual->proximo;
        }
    }
}

void listarEleitores() {
    if (eleitores == NULL) {
        cout << "Não há eleitor cadastrado." << endl;
    } else {
        Eleitor* atual = eleitores;
        while (atual != NULL) {
            cout << "Nome: " << atual->nome << ", Título: " << atual->titulo << endl;
            atual = atual->proximo;
        }
    }
}

void carregarEleitores() {
    ifstream arquivo(VOTERS_FILE.c_str());
    if (arquivo.is_open()) {
        string nome;
        int titulo;
        while (arquivo >> nome >> titulo) {
            cadastrarEleitor(nome, titulo);
        }
        arquivo.close();
    }
}

void salvarEleitores() {
    ofstream arquivo(VOTERS_FILE.c_str());
    if (arquivo.is_open()) {
        Eleitor* atual = eleitores;
        while (atual != NULL) {
            arquivo << atual->nome << " " << atual->titulo << endl;
            atual = atual->proximo;
        }
        arquivo.close();
    }
}

void votar(int numeroCandidato) {
    Voto* novoVoto = new Voto;
    novoVoto->numeroCandidato = numeroCandidato;
    novoVoto->proximo = NULL;

    if (votos == NULL) {
        votos = novoVoto;
    } else {
        Voto* atual = votos;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novoVoto;
    }
}

void listarVotos() {
    if (votos == NULL) {
        cout << "Nenhum voto registrado." << endl;
    } else {
        Voto* atual = votos;
        while (atual != NULL) {
            cout << "Número do candidato: " << atual->numeroCandidato << endl;
            atual = atual->proximo;
        }
    }
}

void carregarVotos() {
    ifstream arquivo(VOTES_FILE.c_str());
    if (arquivo.is_open()) {
        int numeroCandidato;
        while (arquivo >> numeroCandidato) {
            votar(numeroCandidato);
        }
        arquivo.close();
    }
}

void salvarVotos() {
    ofstream arquivo(VOTES_FILE.c_str());
    if (arquivo.is_open()) {
        Voto* atual = votos;
        while (atual != NULL) {
            arquivo << atual->numeroCandidato << endl;
            atual = atual->proximo;
        }
        arquivo.close();
    }
}

void gerarRelatorio() {
    ofstream arquivo(REPORT_FILE.c_str());
    if (arquivo.is_open()) {
        arquivo << "Relatório de Votação" << endl;
        arquivo << "-------------------" << endl;

        Candidato* atual = candidatos;
        while (atual != NULL) {
            int totalVotos = 0;
            Voto* votoAtual = votos;
            while (votoAtual != NULL) {
                if (votoAtual->numeroCandidato == atual->numero) {
                    totalVotos++;
                }
                votoAtual = votoAtual->proximo;
            }

            arquivo << "Candidato: " << atual->nome << ", Número: " << atual->numero << ", Votos: " << totalVotos << endl;
            atual = atual->proximo;
        }

        arquivo.close();
        cout << "Relatório gerado!" << endl;
    } else {
        cout << "Erro ao gerar o relatório! :(" << endl;
    }
}

int main() {
	setlocale(LC_ALL, "Portuguese");
    carregarCandidatos();
    carregarEleitores();
    carregarVotos();

    int opcao;
    do {
    cout << endl;
    cout << "==========================" << endl;
    cout << "   Sistema de Votação" << endl;
    cout << "==========================" << endl;
    cout << "[1] Cadastrar Candidato" << endl;
    cout << "[2] Remover Candidato" << endl;
    cout << "[3] Motrar Candidatos" << endl;
    cout << "[4] Cadastrar Eleitor" << endl;
    cout << "[5] Remover Eleitor" << endl;
    cout << "[6] Mostrar Eleitores" << endl;
    cout << "[7] Votar agora" << endl;
    cout << "[8] Mostrar Votos" << endl;
    cout << "[9] Emitir Relatório" << endl;
    cout << "[0] Sair" << endl;
    cout << "==========================" << endl;
    cout << "Digite sua opção: ";
    cin >> opcao;
    cout << endl;

        switch (opcao) {
            case 1: {
                string nome;
                int numero;
                cout << "Digite o nome do candidato: ";
                cin.ignore();
                getline(cin, nome);
                cout << "Digite o número do candidato: ";
                cin >> numero;
                cadastrarCandidato(nome, numero);
                salvarCandidatos();
                break;
            }
            case 2: {
                int numero;
                cout << "Digite o número do candidato a ser removido: ";
                cin >> numero;
                removerCandidato(numero);
                salvarCandidatos();
                break;
            }
            case 3: {
                listarCandidatos();
                break;
            }
            case 4: {
                string nome;
                int titulo;
                cout << "Digite o nome do eleitor: ";
                cin.ignore();
                getline(cin, nome);
                cout << "Digite o número do título do eleitor: ";
                cin >> titulo;
                cadastrarEleitor(nome, titulo);
                salvarEleitores();
                break;
            }
            case 5: {
                int titulo;
                cout << "Digite o número do título do eleitor a ser removido: ";
                cin >> titulo;
                removerEleitor(titulo);
                salvarEleitores();
                break;
            }
            case 6: {
                listarEleitores();
                break;
            }
            case 7: {
                int numeroCandidato;
                cout << "Digite o número do candidato para votar: ";
                cin >> numeroCandidato;
                votar(numeroCandidato);
                salvarVotos();
                break;
            }
            case 8: {
                listarVotos();
                break;
            }
            case 9: {
                gerarRelatorio();
                break;
            }
            case 0: {
                cout << "Saindo..." << endl;
                break;
            }
            default: {
                cout << "Opção inválida. Tente novamente." << endl;
                break;
            }
        }
    } while (opcao != 0);

    return 0;
}

