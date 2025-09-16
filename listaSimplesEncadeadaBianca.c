/* O programa a seguir implementa uma lista ligada simples (lista encadeada) de estudantes,
em que cada nó (struct info) armazena o nome, a matricula e um ponteiro para o proximo no. 
O programa possui um CRUD basico por meio de um menu com as seguintes opcoes: inserir, 
listar, atualizar (alterar nome pela matricula) e deletar (remover pela matricula).
*/

#include <stdio.h>  // Biblioteca para entrada e saida de dados
#include <stdlib.h> // Biblioteca para alocacao dinamica (malloc, free) e NULL
#include <string.h> // Biblioteca para manipulacao de string

// Define o formato de cada nó da lista
struct info {
    char nome[35];
    int matricula;
    struct info *prox; // Ponteiro para o proximo nó da lista (encadeamento)
};

// 'inicio' aponta para o primeiro nó da lista; NULL indica que a lista comeca vazia
struct info *inicio = NULL; 

// --- Funções do CRUD ---

// Funcao para inserir aluno (Create)
void inserir(char nome[], int matricula) {
    // CORREÇÃO: 'novo' deve ser um ponteiro para 'struct info'.
    struct info *novo = (struct info *) malloc(sizeof(struct info)); 
    
    // Verifica se a alocação de memória foi bem-sucedida
    if (novo == NULL) {
        printf("Erro: nao foi possivel alocar memoria.\n");
        return;
    }
    
    // Preenche os dados do novo nó
    strcpy(novo->nome, nome);
    novo->matricula = matricula;
    novo->prox = NULL; // O novo nó será o último, então seu 'prox' aponta para NULL

    // Se a lista estiver vazia, o novo nó se torna o primeiro
    if (inicio == NULL) {
        inicio = novo;
    } else { // Senão, percorre a lista até o final para adicionar o novo nó
        struct info *aux = inicio;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novo;
    }
    printf("Aluno %s (matricula %d) inserido com sucesso!\n", nome, matricula);
}

// Funcao para exibir lista de alunos (Read)
void listar() {
    if (inicio == NULL) {
        printf("\nA lista esta vazia!\n");
        return;
    }

    struct info *aux = inicio;
    printf("\n~ Lista de Alunos ~\n");
    while (aux != NULL) {
        printf("Nome: %s - Matricula: %d\n", aux->nome, aux->matricula);
        aux = aux->prox;
    }
}

// Funcao para alterar dados de aluno (Update)
void atualizar(int matricula, char novoNome[]) {
    struct info *aux = inicio;
    int encontrado = 0; // Flag para verificar se o aluno foi encontrado

    while (aux != NULL) {
        if (aux->matricula == matricula) {
            strcpy(aux->nome, novoNome);
            printf("Nome do aluno com matricula %d atualizado para %s!\n", matricula, novoNome);
            encontrado = 1;
            break; // Otimização: para a busca após encontrar
        }
        aux = aux->prox;
    }
    
    if (!encontrado) {
        printf("Aluno com matricula %d nao encontrado!\n", matricula);
    }
}

// Funcao para remover aluno da lista (Delete)
void deletar(int matricula) {
    if (inicio == NULL) {
        printf("A lista esta vazia!\n");
        return;
    }

    struct info *aux = inicio;
    struct info *anterior = NULL;

    // Busca o nó a ser removido, guardando o nó anterior
    while (aux != NULL && aux->matricula != matricula) {
        anterior = aux;
        aux = aux->prox;
    }

    // Se aux é NULL, o aluno não foi encontrado
    if (aux == NULL) {
        printf("Aluno com matricula %d nao encontrado!\n", matricula);
        return;
    }

    // Caso 1: Remover o primeiro nó da lista
    if (anterior == NULL) {
        inicio = aux->prox;
    } else { // Caso 2: Remover um nó do meio ou do fim da lista
        anterior->prox = aux->prox;
    }

    free(aux); // Libera a memória do nó removido
    printf("Aluno com matricula %d removido com sucesso!\n", matricula);
}

// MELHORIA: Função para liberar toda a memória alocada ao sair
void liberar_lista() {
    struct info *aux = inicio;
    struct info *proximo_no;
    
    while(aux != NULL) {
        proximo_no = aux->prox; // Guarda a referência para o próximo
        free(aux);              // Libera o nó atual
        aux = proximo_no;       // Avança para o próximo
    }
    inicio = NULL; // Garante que a lista seja considerada vazia
}


// --- Função Principal e Menu ---

int main() {
    int opcao, matricula;
    char nome[35];

    do {
        printf("\n~ Menu ~\n");
        printf("1) Inserir aluno\n");
        printf("2) Listar alunos\n");
        printf("3) Atualizar aluno\n");
        printf("4) Deletar aluno\n");
        printf("0) Sair\n");
        printf("Informe uma das opcoes: ");
        scanf("%d", &opcao);
        getchar(); // Consome o caractere '\n' deixado pelo scanf

        switch(opcao) {
            case 1:
                printf("\nDigite o nome: ");
                fgets(nome, 35, stdin);
                nome[strcspn(nome, "\n")] = 0; // Remove o '\n' do final do nome
                printf("Digite a matricula: ");
                scanf("%d", &matricula);
                inserir(nome, matricula);
                break;

            case 2:
                listar();
                break;

            case 3:
                printf("\nDigite a matricula do aluno a atualizar: ");
                scanf("%d", &matricula);
                getchar(); // Consome o '\n'
                printf("Digite o novo nome: ");
                fgets(nome, 35, stdin);
                nome[strcspn(nome, "\n")] = 0;
                atualizar(matricula, nome);
                break;

            case 4:
                printf("\nDigite a matricula do aluno a deletar: ");
                scanf("%d", &matricula);
                deletar(matricula);
                break;

            case 0:
                printf("\nSaindo do programa...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }
    } while(opcao != 0);
    
    // MELHORIA: Chama a função para limpar a memória antes de encerrar
    liberar_lista();

    return 0;
}