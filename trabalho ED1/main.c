#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define v 50
int x = 1;
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
    printf("\nDigite o nome do filme: ");
    fgets(f->nome, v, stdin);
    f->nome[strcspn(f->nome, "\n")] = '\0';

    printf("\nDigite o ano: ");
    scanf("%d", &f->ano);
    getchar();

    f->seq = NULL;

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

void inserirFilmeOrdenado(Meio** m, Filme* novoFilme, int id) {
    Meio* novoMeio = (Meio*)malloc(sizeof(Meio));
    novoMeio->filme = novoFilme;
    novoMeio->prox = NULL;

    if (*m == NULL || strcmp(novoFilme->nome, (*m)->filme->nome) < 0) {
        // Inserir no início da lista
        novoMeio->prox = *m;
        *m = novoMeio;
    } else {
        Meio* atual = *m;
        while (atual->prox != NULL && strcmp(novoFilme->nome, atual->prox->filme->nome) > 0) {
            atual = atual->prox;
        }
        novoMeio->prox = atual->prox;
        atual->prox = novoMeio;
    }
}
void exibirLista(Meio* m) {
    printf("Lista de Filmes:\n");
    for (Meio* atual = m; atual != NULL; atual = atual->prox) {
        printf("Nome: %s | Ano: %d | Id: %d\n", atual->filme->nome, atual->filme->ano, atual->filme->id);
    }
}
void adicionarFilmeUsuario(Meio** m, int id) {
    Filme* novoFilme = criarFilme();
    inserirFilmeOrdenado(m, novoFilme, id);
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
Seq* criarlista(){
    return NULL;
}

int estavazia(Seq** l){
    return (*l==NULL);
}

void inserirFilmeSequencia(Meio** m) {
    int num;
    printf("\nDigite o ID do filme que inicia a sequencia: ");
    scanf("%d", &num);
    getchar();

    Filme* novoFilme = criarFilme();

    for (Meio* atual = *m; atual != NULL; atual = atual->prox) {
        if (atual->filme->id == num) {
            Seq* novaSeq = (Seq*)malloc(sizeof(Seq));
            novaSeq->filme = novoFilme;
            novaSeq->ant = NULL;
            novaSeq->prox = NULL;

            if (atual->filme->seq == NULL) {
                atual->filme->seq = novaSeq;
            } else {
                Seq* ultimaSeq = atual->filme->seq;
                while (ultimaSeq->prox != NULL) {
                    ultimaSeq = ultimaSeq->prox;
                }
                ultimaSeq->prox = novaSeq;
                novaSeq->ant = ultimaSeq;
            }
            return;
        }
    }
    printf("Filme com identificador %d não encontrado na sequência.\n", num);
}

void imprimirListaSequencia(Meio* m) {
    int num;
    printf("\nDigite o Id do filme que inicia a sequencia: ");
    scanf("%d", &num);
    getchar();

    for (Meio* atual = m; atual != NULL; atual = atual->prox) {
        if (atual->filme->id == num) {
            Seq* seqAtual = atual->filme->seq;
            printf("Sequência de filmes:\n");
            while (seqAtual != NULL) {
                imprimirFilme(seqAtual->filme);
                seqAtual = seqAtual->prox;
            }
            return;
        }
    }

    printf("Filme com identificador %d não encontrado na sequência.\n", num);
}
void removerFilmeSequencia(Meio** m) {
    int num,n;
    printf("\nDigite o ID do filme que inicia a sequencia: ");
    scanf("%d", &num);
    getchar();
    
    Meio* Atual = *m;
    for (; Atual != NULL; Atual = Atual->prox) {
        if (Atual->filme->id == num) {
            printf("Digite o ID do filme que deseja remover: ");
            scanf("%d", &n);

            Seq* seqAtual = Atual->filme->seq;
            for (; seqAtual != NULL; seqAtual = seqAtual->prox) {
                if (seqAtual->filme->id == n) {
                    // Remover o filme da sequência
                    if (seqAtual->ant == NULL) {
                        Atual->filme->seq = seqAtual->prox;
                    } else {
                        seqAtual->ant->prox = seqAtual->prox;
                    }
                    if (seqAtual->prox != NULL) {
                        seqAtual->prox->ant = seqAtual->ant;
                    }
                    free(seqAtual);
                    printf("Filme com identificador %d removido da sequência.\n", n);
                    return;
                }
            }
            printf("Filme com identificador %d não encontrado na sequência.\n", n);
            return;
        }
    }

    printf("Filme com identificador %d não encontrado na sequência.\n", num);
}
void imprimirFilmeAntecessor(Meio* m) {
    int num;
    printf("Digite o ID do filme: ");
    scanf("%d", &num);
    getchar();

    for (Meio* atual = m; atual != NULL; atual = atual->prox) {
        Seq* seqAtual = atual->filme->seq;
        while (seqAtual != NULL) {
            if (seqAtual->filme->id == num) {
                Seq* antecessor = seqAtual->ant;
                if (antecessor != NULL) {
                    printf("Antecessor do filme %d na sequência: \n", num);
                    imprimirFilme(antecessor->filme);
                    return;
                } else {
                    printf("O filme %d não possui um antecessor na sequência.\n", num);
                    return;
                }
            }
            seqAtual = seqAtual->prox;
        }
    }

    printf("Filme com identificador %d não encontrado na sequência.\n", num);
}

void imprimirFilmeSucessor(Meio* m) {
    int num;
    printf("Digite o ID do filme: ");
    scanf("%d", &num);
    getchar();

    for (Meio* atual = m; atual != NULL; atual = atual->prox) {
        if (atual->filme->id == num) {
            Seq* seqAtual = atual->filme->seq;
            printf("Sucessor do filme %d na sequência:\n", num);
            imprimirFilme(seqAtual->filme);
            return;
        }
        else {
            Seq* seqAtual = atual->filme->seq;
            for (Seq* aux = seqAtual; aux != NULL; aux = aux->prox) {
                if (aux->filme->id == num) {
                    Seq* sucessor = aux->prox;
                    if (sucessor != NULL) {
                        printf("Sucessor do filme %d na sequência:\n", num);
                        imprimirFilme(sucessor->filme);
                        return;
                    } else {
                        printf("O filme %d não possui um sucessor na sequência.\n", num);
                        return;
                    }
                }
            }
        }
    }
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

    // Reinicializar o m
    topo->prim = NULL;
    topo->ult = NULL;
    topo->n = 0;
}
void clearScreen() {
    // Limpa a tela do console
    printf("\033[2J\033[1;1H");
}

void exibirMenu() {
    printf("\n\n");
    printf("1 - Inserir novo filme\n");
    printf("2 - Alterar dados de um filme\n");
    printf("3 - Remover filme\n");
    printf("4 - Imprimir dados de todos os filmes\n");
    printf("5 - Inserir novo filme na sequencia\n");
    printf("6 - Imprimir lista sequencial de filmes\n");
    printf("7 - Remover filme da sequencia\n");
    printf("8 - Imprimir filme antecessor na saga\n");
    printf("9 - Imprimir filme sucessor na saga\n");
    printf("0 - Sair\n");
}

int main() {
    Topo topo;
    topo.n = 0;
    topo.prim = NULL;
    topo.ult = NULL;

    int idFilmeInicio;
    int idFilmeRemover;
    int opcao;
    do {
        exibirMenu();
        scanf("%d", &opcao);
        getchar(); // Limpar o caractere de nova linha do buffer

        switch (opcao) {
            case 1:
                adicionarFilmeUsuario(&topo.prim, topo.n);
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
            case 5:
                inserirFilmeSequencia(&topo.prim);
                break;
            case 6:
                imprimirListaSequencia(topo.prim);
                break;
            case 7:
                removerFilmeSequencia(&topo.prim);
                break;
            case 8:
                imprimirFilmeAntecessor(topo.prim);
                break;
            case 9:
                imprimirFilmeSucessor(topo.prim);
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção invalida. Por favor, tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    liberarMemoria(&topo);

    return 0;
}