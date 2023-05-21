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
    if (f == NULL){
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
int FilmeVazia(Filme *f){
    if(f->nome==NULL){
        return 1;
    }else{
        return 0;
    }
}
//Essa função imprime os dados de um filme.
void imprimirFilme(Filme* f) {
    printf("\nNome: %s | Ano: %d | Id: %d", f->nome, f->ano,f->id);
}
void alterarNome(Filme* f) {
    int num;
    printf("\nDigite o ID do filme que deseja alterar o nome: ");
    scanf("%d", &num);
    getcehr();
    for (Filme* p = f; p != NULL; p = p->seq->filme) {
        if (num == p->id) {
            char aux[v];
            printf("\nDigite o nome do filme: ");
            if (fgets(f->nome, v, stdin) == NULL) {
                printf("Erro ao ler o nome do filme.\n");
                free(f);
                exit(1);
            }
            f->nome[strcspn(f->nome, "\n")] = '\0';
            getchar();
            strcpy(p->nome, aux);
            return;
        } else
            printf("\nFilme nao encontrado ou nao existe.");
    }
}
void alterarAno(Filme* f) {
    int num;
    printf("\nDigite o ID do filme que deseja alterar o ano: ");
    scanf("%d", &num);
    getchar();
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
    getchar();
    for (Filme* p=f;p!=NULL;p=p->seq->filme){
        if (num == p->id) {
            return p->ano;
        } else
            printf("\nFilme nao encontrado ou nao existe.");
    }
}
Meio* alocaMeio(Filme* f){
    Meio* m = (Meio*)malloc(sizeof(Meio));
    if (m == NULL){
        printf("Erro ao alocar memória para o meio.\n");
        exit(1);
    }
    m->filme = f;
    m->prox = NULL;
    return m;
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
    Meio*m=alocaMeio(f);
    free(f);
    return 0;
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
    if (f == NULL){
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
int FilmeVazia(Filme *f){
    if(f->nome==NULL){
        return 1;
    }else{
        return 0;
    }
}
//Essa função imprime os dados de um filme.
void imprimirFilme(Filme* f) {
    printf("\nNome: %s | Ano: %d | Id: %d", f->nome, f->ano,f->id);
}
void alterarNome(Filme* f) {
    int num;
    printf("\nDigite o ID do filme que deseja alterar o nome: ");
    scanf("%d", &num);
    getcehr();
    for (Filme* p = f; p != NULL; p = p->seq->filme) {
        if (num == p->id) {
            char aux[v];
            printf("\nDigite o nome do filme: ");
            if (fgets(f->nome, v, stdin) == NULL) {
                printf("Erro ao ler o nome do filme.\n");
                free(f);
                exit(1);
            }
            f->nome[strcspn(f->nome, "\n")] = '\0';
            getchar();
            strcpy(p->nome, aux);
            return;
        } else
            printf("\nFilme nao encontrado ou nao existe.");
    }
}
void alterarAno(Filme* f) {
    int num;
    printf("\nDigite o ID do filme que deseja alterar o ano: ");
    scanf("%d", &num);
    getchar();
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
    getchar();
    for (Filme* p=f;p!=NULL;p=p->seq->filme){
        if (num == p->id) {
            return p->ano;
        } else
            printf("\nFilme nao encontrado ou nao existe.");
    }
}
Meio* alocaMeio(Filme* f){
    Meio* m = (Meio*)malloc(sizeof(Meio));
    if (m == NULL){
        printf("Erro ao alocar memória para o meio.\n");
        exit(1);
    }
    m->filme = f;
    m->prox = NULL;
    return m;
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
    Meio*m=alocaMeio(f);
    free(f);
    return 0;
}
