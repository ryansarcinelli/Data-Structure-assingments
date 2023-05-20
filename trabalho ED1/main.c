#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define v 50

typedef struct Descritor {
    struct Filme* filme;
    struct Descritor* prox;
} Meio;

typedef struct ListaDup {
    struct ListaDup* prox;
    struct ListaDup* ant;
    struct Filme* filme;
} Seq;

typedef struct Filme {
    int id, ano;
    char nome[v];
    struct ListaDup* seq;
} Filme;

typedef struct Desc {
    int n;
    struct Desc* prim;
    struct Desc* ult;
} Topo;

//Essa função aloca espaço para um novo filme.
Filme* criarFilme() {
    Filme* f = (Filme*)malloc(sizeof(Filme));
    printf("\nDigite o nome do filme: ");
    fgets(f->nome, v, stdin);
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

void alterarNome(Filme* f) {
    int num;
    printf("\nDigite o ID do filme que deseja alterar o nome: ");
    scanf("%d", &num);
    fflush(stdin);
    for (Filme* p = f; p != NULL; p = p->seq->filme) {
        if (num == p->id) {
            char aux[v];
            printf("\nDigite o novo nome do filme %d: ", num);
            fgets(aux, v, stdin);
            aux[strcspn(aux, "\n")] = '\0';
            fflush(stdin);
            strcpy(p->nome, aux);
            return;
        } else {
            printf("\nFilme nao encontrado ou nao existe.");
        }
    }
}
void alterarAno(Filme* f) {
    int num;
    printf("\nDigite o ID do filme que deseja alterar o ano: ");
    scanf("%d", &num);
    fflush(stdin);
    for (Filme* p=f;p!=NULL;p=p->seq->filme) {
        if (num == p->id) {
            int aux;
            printf("\nDigite o novo ano do filme %d: ", num);
            scanf("%d", &aux);
            f->ano = aux;
            return; // Filme encontrado e ano alterado, sair da função
        } else
            printf("\nFilme nao encontrado ou nao existe.");
    }
}

int retornaAno(Filme* f){
    int num;
    printf("\nDigite o ID do filme que deseja saber o ano: ");
    scanf("%d", &num);
    fflush(stdin);
    for (Filme* p=f;p!=NULL;p=p->seq->filme){
        if (num == p->id) {
            return p->ano;
        } else
            printf("\nFilme nao encontrado ou nao existe.");
        
    }
}
int main(){
    Filme* f = criarFilme();
    imprimirFilme(f);
    //alterarNome(f);
    //imprimirFilme(f);
    //alterarAno(f);
    //imprimirFilme(f);
    //int ano=retornaAno(f);
    //printf("\nAno do filme %d: %d", f->id, ano);
    free(f);
    return 0;
}