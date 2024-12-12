#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <vector> // Para usar std::vector (altamente recomendado)

using namespace std;

//cria a struct
struct Tarefa {
    int codigo;
    string titulo;
    string descricao;
    string dataCriacao;
    string status;
    string prioridade;
};

//funcao para salvar as tarefas em arquivio
void salvarTarefas(const vector<Tarefa>& tarefas, const string& nomeArquivo) {
    //abre arquivo para gravar
    ofstream arquivo(nomeArquivo);
    //testa se foi aberto
    if (arquivo.is_open()) {
        //insere vetor tarefas
        for (const auto& tarefa : tarefas) {
            //adiciona os dados em cada linha
            arquivo << tarefa.codigo << endl;
            arquivo << tarefa.titulo << endl;
            arquivo << tarefa.descricao << endl;
            arquivo << tarefa.dataCriacao << endl;
            arquivo << tarefa.status << endl;
            arquivo << tarefa.prioridade << endl;
        }
        //fecha o arquivo
        arquivo.close();
        cout << "Tarefas salvas com sucesso em " << nomeArquivo << endl;
    } else {
        cerr << "Erro ao abrir o arquivo para salvar." << endl;
    }
}

//funcao le as tarefas do arquivo
vector<Tarefa> carregarTarefas(const string& nomeArquivo) {
    //cria vetor das tarefas
    vector<Tarefa> tarefas;
    //abre arquivo para leitura
    ifstream arquivo(nomeArquivo);
    //testa se foi aberto
    if (arquivo.is_open()) {
        Tarefa tarefa;
         // le o arquivo
        while (arquivo >> tarefa.codigo >> ws) {
            getline(arquivo, tarefa.titulo);
            getline(arquivo, tarefa.descricao);
            getline(arquivo, tarefa.dataCriacao);
            getline(arquivo, tarefa.status);
            getline(arquivo, tarefa.prioridade);
            //grava a tarefa no vector
            tarefas.push_back(tarefa); // Usando push_back para adicionar ao vector
        }
        //fecha o arquivo
        arquivo.close();
    } else {
        //cria arquivo se nao existor
        ofstream novoArquivo(nomeArquivo);
        if (!novoArquivo.is_open()) {
            cerr << "Erro ao criar o arquivo de tarefas." << endl;
        }
        novoArquivo.close();
    }
    return tarefas;
}

//funcao para adicionar tarefa
void adicionarTarefa(vector<Tarefa>& tarefas) {
    Tarefa novaTarefa;
    cout << "Código: ";
    cin >> novaTarefa.codigo;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Título: ";
    getline(cin, novaTarefa.titulo);
    cout << "Descrição: ";
    getline(cin, novaTarefa.descricao);
    cout << "Data de Criação: ";
    getline(cin, novaTarefa.dataCriacao);
    cout << "Status (pendente, em andamento, concluída): ";
    getline(cin, novaTarefa.status);
    cout << "Prioridade (baixa, média, alta): ";
    getline(cin, novaTarefa.prioridade);
    //grava tarefa no vetor
    tarefas.push_back(novaTarefa);
}

//funcao para listar tarefas
void listarTarefas(const vector<Tarefa>& tarefas) {
    //testa as tarefas cadastradas
     if (tarefas.empty()) {
        cout << "Nenhuma tarefa cadastrada." << endl;
        return;
    }
    //importa o vetor
    for (const auto& tarefa : tarefas) {
        cout << "\nCódigo: " << tarefa.codigo << endl;
        cout << "Título: " << tarefa.titulo << endl;
        cout << "Descrição: " << tarefa.descricao << endl;
        cout << "Data de Criação: " << tarefa.dataCriacao << endl;
        cout << "Status: " << tarefa.status << endl;
        cout << "Prioridade: " << tarefa.prioridade << endl;
        cout << "--------------------" << endl;
    }
}

int main() {
    //carrega as tarefas do arquivo
    vector<Tarefa> tarefas = carregarTarefas("tarefas.txt");

    int opcao;

    do {
        //menu
        cout << "\n--- Menu ---" << endl;
        cout << "1. Adicionar Tarefa" << endl;
        cout << "2. Listar Tarefas" << endl;
        cout << "3. Salvar Tarefas" << endl;
        cout << "0. Sair" << endl;
        cout << "Opção: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                adicionarTarefa(tarefas);
                break;
            case 2:
                listarTarefas(tarefas);
                break;
            case 3:
                salvarTarefas(tarefas, "tarefas.txt");
                break;
            case 0:
                cout << "Fechando do programa." << endl;
                break;
            default:
                cout << "Opcao invalida." << endl;
        }
    } while (opcao != 0);

    return 0;
}