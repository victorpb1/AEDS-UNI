/* o programa a seguir implementa uma lista ligada simples (lista encadeada) de estudantes,
em que cada no (struct info) armazena o nome, a matricula e um ponteiro para o proximo no. 
o programa possui um CRUD basico por meio de um menu com as seguintes opcoes: inserir, 
listar, atualizar (alterar nome pela matricula) e deletar (remover pela matricula)*/

#include <stdio.h> //biblioteca para entrada e saida de dados 
#include <stdlib.h> //biblioteca pra alocacao dinamica (malloc, free) e null
#include <string.h> //biblioteca pra manipulacao de string

struct info {           //define o formato de cada no da lista
    char nome[35];
    int matricula;
    struct info *prox; //ponteiro para o proximo no da lista (encadeamento)
};

struct info *inicio = NULL; //inicio aponta para o primeiro no da lista; NULL indica que a lista comeca vazia

//funcao p/ inserir aluno (p/ criar)
void inserir (char nome[], int matricula) { //cria um novo no e anexa ao final da lista
    
    struct info novo = (struct info) malloc(sizeof(struct info)); //alocacao; reserva memoria para um novo no; se malloc falhar, retorna null
    if (novo == NULL) {
        printf("Erro: nao foi possivel alocar memoria.\n");
        return;
    }
    
    strcpy(novo->nome, nome);
    novo->matricula = matricula;
    novo->prox = NULL;
    
/* copia o nome para o campo nome do no;
define a matrícula;
prox = NULL porque, ate ser ligado, será o último no */

    if (inicio == NULL) {   
        inicio = novo;              //se a lista estiver vazia, o novo no vira o primeiro elemento
    } else {                        //senao, percorre ate o ultimo no e liga nele
        struct info *aux = inicio;      
    /*cria um ponteiro auxiliar chamado aux, do tipo struct info, que aponta
    para o primeiro no da lista (que esta em inicio)*/
        
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novo;
        
    //aux percorre a lista; aux->prox == NULL identifica o ultimo no
    //o ultimo no passa a apontar para novo
    }
    printf("Aluno %s, matricula %d: inserido com sucesso!\n", nome, matricula);
}
    //complexidade: O(n), ou seja, percorre ate o fim


//funcao p/ exibir lista de alunos (p/ ler)
void listar() {     //percorre a lista e imprime todos os alunos
    if (inicio == NULL) {       
        printf("Lista vazia!\n");   //se inicio == NULL, indica lista vazia
        return;
    }

    struct info *aux = inicio; 
    /*cria um ponteiro auxiliar chamado aux, do tipo struct info, que aponta
    para o primeiro no da lista (que esta em inicio)*/
    
    printf("\n~ Lista de alunos ~\n");  //exibe lista de alunos
    while (aux != NULL) {   //se haver alunos, imprime
        printf("Nome: %s - Matricula: %d\n", aux->nome, aux->matricula);
        aux = aux->prox;
        
        /*aux começa em inicio, e a cada iteracao, avanca para o proximo (aux = aux->prox) ate NULL;
        imprime nome e matricula de cada no;
        complexidade: O(n), ou seja, percorre ate o fim */
    }
}

//funcao p/ alterar dados de aluno (p/ atualizar)
void atualizar(int matricula, char novoNome[]) {        //procura um no pela matricula e troca o nome
    struct info *aux = inicio;
     /*cria um ponteiro auxiliar chamado aux, do tipo struct info, que aponta
    para o primeiro no da lista (que esta em inicio)*/
    
    while (aux != NULL) {
        if (aux->matricula == matricula) {
            strcpy(aux->nome, novoNome);
            printf("Aluno de matricula %d atualizado para %s!\n", matricula, novoNome);
            return;
        }
        aux = aux->prox;
    }
    printf("Aluno com matricula %d não encontrado!\n", matricula);
/*compara aux->matricula com a matricula alvo, percorre, e ao encontrar o no com a matricula, 
substitui novo nome e retorna;
se nao achar, informa que nao encontrou;
atualiza apenas o primeiro no que corresponder (se houver duplicatas, as demais não são alteradas) */
}

//funcao p/ remover aluno da lista (p/ deletar)
void deletar(int matricula) {   //remove o primeiro no que tiver a matricula informada
    if (inicio == NULL) {   //verifica se a lista esta vazia
        printf("Lista vazia!\n");
        return;
    }

    struct info *aux = inicio;
     /*cria um ponteiro auxiliar chamado aux, do tipo struct info, que aponta
    para o primeiro no da lista (que esta em inicio)*/
    struct info *anterior = NULL;
    /*ponteiro auxiliar usado para lembrar do no anterior ao atual durante a 
    busca, especialmente para conseguir remover nos no meio da lista */

    while (aux != NULL && aux->matricula != matricula) { //busca do no alvo
        anterior = aux;
        aux = aux->prox;
    //sai quando encontra (aux->matricula == matricula) ou chega ao fim (aux == NULL)
    }
    
    if (aux == NULL) {  //caso nao encontre
        printf("Aluno com matricula %d nao encontrado!\n", matricula);
        return;
    }

//casos de remocao:
    if (anterior == NULL) {         //remover primeiro no da lista (anterior == NULL)
        inicio = aux->prox;         //atualiza inicio para o proximo no (pode tornar a lista vazia)
    } else {                        //remover no do meio/fim
        anterior->prox = aux->prox; //faz o no anterior pular o aux e apontar para o sucessor de aux
    }

    free(aux);  //libera a memoria do no removido
    printf("Aluno com matricula %d removido com sucesso!\n", matricula);
}
//complexidade: O(n), ou seja, percorre ate o fim 

//menu crud
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
        getchar();      //consumir enter

        switch(opcao) {
            case 1:
                printf("\nDigite o nome: ");
                fgets(nome, 35, stdin);
                nome[strcspn(nome, "\n")] = 0;      //remove \n
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
                getchar();
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

    return 0;
}