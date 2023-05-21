#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define v 50

typedef struct Meio {
    struct Filme* filme;
    struct Meio* prox;
} Meio;

typedef struct Seq {
    struct Seq* prox;
    struct Seq* ant;
    struct Filme* filme;
} Seq;

typedef struct Filme {
    int id, ano;
    char nome[v];
    struct Seq* seq;
} Filme;

typedef struct Topo {
    int n;
    struct Meio* prim;
    struct Meio* ult;
} Topo;

//Essa função aloca espaço para um novo filme.
Filme* criarFilme() {
    Filme* f = (Filme*)malloc(sizeof(Filme));
    if (f == NULL) {
        printf("Erro ao alocar memória para o filme.\n");
        exit(1);
    }
    printf("\nDigite o nome do filme: ");
    if (fgets(f->nome, v, stdin) == NULL) {
        printf("Erro ao ler o nome do filme.\n");
        free(f);
        exit(1);
    }
    f->nome[strcspn(f->nome, "\n")] = '\0';

    printf("\nDigite o ano: ");
    scanf("%d", &f->ano);
    getchar();

    f->seq = NULL;

    static int x = 1;
    f->id = x;
    x++;
    return f;
}
//Essa função imprime os dados de um filme.
void imprimirFilme(Filme* f) {
    printf("\nNome: %s | Ano: %d | Id: %d", f->nome, f->ano,f->id);
}
void alterarNome(Filme* f, int num) {
    for (Filme* p = f; p != NULL; p = p->seq->filme) {
        if (num == p->id) {
            char aux[v];
            printf("\nDigite o novo nome do filme %d: ", num);
            if (fgets(aux, v, stdin) == NULL) {
                printf("Erro ao ler o nome do filme.\n");
                free(f);
                exit(1);
            }
            aux[strcspn(aux, "\n")] = '\0';
            strcpy(p->nome, aux);
            return;
        }
    }
    printf("\nFilme nao encontrado ou nao existe.");
}
void alterarAno(Filme* f, int num) {
    for (Filme* p=f;p!=NULL;p=p->seq->filme) {
        if (num == p->id) {
            int aux;
            printf("\nDigite o novo ano do filme %d: ", num);
            scanf("%d", &aux);
            getchar();
            f->ano = aux;
            return; // Filme encontrado e ano alterado, sair da função
        } else
            printf("\nFilme nao encontrado ou nao existe.");
    }
}
void alteradado(Meio* m, Filme* f) {
    int num;
    printf("\nDigite o ID do filme que deseja alterar: ");
    scanf("%d", &num);
    getchar();
    alterarNome(f, num);
    alterarAno(f, num);
}
int retornaAno(Filme* f){
    int num;
    printf("\nDigite o ID do filme que deseja saber o ano: ");
    scanf("%d", &num);
    getchar();
    for (Filme* p=f;p!=NULL;p=p->seq->filme){
        if (num == p->id) {
            return p->ano;
        } else
            printf("\nFilme nao encontrado ou nao existe.");
    }
}
Meio* alocaMeio(Filme* f) {
    Meio* m = (Meio*)malloc(sizeof(Meio));
    if (m == NULL) {
        printf("Erro ao alocar memória para o meio.\n");
        exit(1);
    }
    m->filme = f;
    m->prox = NULL;
    return m;
}
Meio* adicionarFilmeOrdenado(Meio* m, Filme* f) {
    Meio* novo = alocaMeio(f);

    if (m == NULL) {
        return novo;
    }

    Meio* atual = m;
    Meio* anterior = NULL;

    // Percorre a lista para encontrar a posição correta de inserção
    while (atual != NULL && strcmp(f->nome, atual->filme->nome) > 0) {
        anterior = atual;
        atual = atual->prox;
    }

    // Insere o novo filme na posição correta
    anterior->prox = novo;
    novo->prox = atual;

    return m;
}
void exibirLista(Meio* m) {
    printf("Lista de Filmes:\n");
    for (Meio* atual = m; atual != NULL; atual = atual->prox) {
        printf("Nome: %s | Ano: %d | Id: %d\n", atual->filme->nome, atual->filme->ano, atual->filme->id);
    }
}
void adicionarFilmeUsuario(Meio* m) {
    Filme* novoFilme = criarFilme();
    m = adicionarFilmeOrdenado(m, novoFilme);
    printf("\nFilme adicionado com sucesso.");
}

int main(){
    //alterarNome(f);
    //imprimirFilme(f);
    //alterarAno(f);
    //imprimirFilme(f);
    //int ano=retornaAno(f);
    //printf("\nAno do filme %d: %d", f->id, ano);
    Filme* f = criarFilme();
    Meio* m = alocaMeio(f);
    //adicionarFilmeUsuario(m);
    //exibirLista(m);
    imprimirFilme(f);
    alteradado(m,f);
    imprimirFilme(f);
    free(m);
    free(f);
    return 0;
}