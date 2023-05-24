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
Filme* alocaFilme() {
    Filme* f = (Filme*)malloc(sizeof(Filme));
    if (f == NULL) {
        printf("Erro ao alocar memória para o filme.\n");
        exit(1);
    }
    f->seq = NULL;
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

void inserirFilmeOrdenado(Meio** descritor, Filme* novoFilme) {
    Meio* novoMeio = (Meio*)malloc(sizeof(Meio));
    novoMeio->filme = novoFilme;
    novoMeio->prox = NULL;

    if (*descritor == NULL || strcmp(novoFilme->nome, (*descritor)->filme->nome) < 0) {
        // Inserir no início da lista
        novoMeio->prox = *descritor;
        *descritor = novoMeio;
        (*descritor)->filme->id = 1; // Atualizar o ID do primeiro filme
    } else {
        Meio* atual = *descritor;
        while (atual->prox != NULL && strcmp(novoFilme->nome, atual->prox->filme->nome) > 0) {
            atual = atual->prox;
        }
        novoMeio->prox = atual->prox;
        atual->prox = novoMeio;

        // Atualizar os IDs dos filmes após a inserção
        Meio* temp = novoMeio->prox;
        int novoId = novoMeio->filme->id + 1;
        while (temp != NULL) {
            temp->filme->id = novoId;
            novoId++;
            temp = temp->prox;
        }
    }
}
void exibirLista(Meio* m) {
    printf("Lista de Filmes:\n");
    for (Meio* atual = m; atual != NULL; atual = atual->prox) {
        printf("Nome: %s | Ano: %d | Id: %d\n", atual->filme->nome, atual->filme->ano, atual->filme->id);
    }
}
void adicionarFilmeUsuario(Meio** m) {
    Filme* novoFilme = alocaFilme();
    inserirFilmeOrdenado(m, novoFilme);
    printf("\nFilme adicionado com sucesso.");
}

void removerFilme(Meio** m) {
    int num;
    printf("\nDigite o ID do filme que deseja remover: ");
    scanf("%d", &num);
    getchar();

    Meio* anterior = NULL;

    for (Meio* atual = *m; atual != NULL; anterior = atual, atual = atual->prox) {
        if (num == atual->filme->id) {
            // Remover o filme da sequência
            Seq* seqAtual = atual->filme->seq;
            while (seqAtual != NULL) {
                Seq* seqProx = seqAtual->prox;
                free(seqAtual);
                seqAtual = seqProx;
            }

            // Remover o filme da lista principal
            if (anterior == NULL) {
                *m = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }

            free(atual->filme);
            free(atual);
            printf("\nFilme removido com sucesso.");
            return;
        }
    }

    printf("\nFilme nao encontrado ou nao existe.");
}

void liberarMemoria(Topo* topo) {
    Meio* atual = topo->prim;
    while (atual != NULL) {
        Filme* filme = atual->filme;

        // Liberar a sequência do filme
        Seq* seqAtual = filme->seq;
        while (seqAtual != NULL) {
            Seq* seqProx = seqAtual->prox;
            free(seqAtual);
            seqAtual = seqProx;
        }

        // Liberar o filme
        free(filme);

        // Avançar para o próximo meio
        Meio* prox = atual->prox;
        free(atual);
        atual = prox;
    }

    // Reinicializar o descritor
    topo->prim = NULL;
    topo->ult = NULL;
    topo->n = 0;
}
void clearScreen() {
    // Limpa a tela do console
    printf("\033[2J\033[1;1H");
}

void exibirMenu() {
    printf("\n\nSelecione uma opcao:\n");
    printf("1 - Inserir novo filme\n");
    printf("2 - Alterar dados de um filme\n");
    printf("3 - Remover filme\n");
    printf("4 - Imprimir lista de filmes\n");
    printf("0 - Sair\n");
    printf("Opcao: ");
}

int main() {
    Topo topo;
    topo.n = 0;
    topo.prim = NULL;
    topo.ult = NULL;

    int opcao;
    do {
        exibirMenu();
        scanf("%d", &opcao);
        getchar(); // Limpar o caractere de nova linha do buffer

        switch (opcao) {
            case 1:
                adicionarFilmeUsuario(&topo.prim);
                break;
            case 2:
                // Opção 2: Alterar dados de um filme
                alteradado(topo.prim, topo.prim->filme);
                break;
            case 3:
                // Opção 3: Remover filme
                removerFilme(&topo.prim);
                break;
            case 4:
                // Opção 4: Imprimir lista de filmes
                exibirLista(topo.prim);
                break;
            case 0:
                // Opção 0: Sair
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);
    liberarMemoria(&topo);
    return 0;
}