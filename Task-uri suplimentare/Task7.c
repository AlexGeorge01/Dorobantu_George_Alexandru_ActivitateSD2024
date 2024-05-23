#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Cladire Cladire;
typedef struct Nod Nod;
typedef struct TabelaDispersie TabelaDispersie;

struct Cladire {
    int id;
    int anConstruire;
    char adresa[100];
} ;
 struct Nod {
    Cladire cladire;
    struct Nod* next;
} ;


struct TabelaDispersie {
    int dimensiune;
    Nod** liste; 
} ;


int functieHash(int anConstruire, int dimensiune) {
    return anConstruire % dimensiune;
}


Nod* creareLista() {
    return NULL;
}

void adaugaCladire(Nod** lista, Cladire c) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    if (nou == NULL) {
        printf("Eroare la alocarea memoriei.\n");
        exit(EXIT_FAILURE);
    }
    nou->cladire = c;
    nou->next = *lista;
    *lista = nou;
}


void afisareCladiri(Nod* lista) {
    while (lista != NULL) {
        printf("ID: %d, An construire: %d, Adresa: %s\n", lista->cladire.id, lista->cladire.anConstruire, lista->cladire.adresa);
        lista = lista->next;
    }
}

TabelaDispersie creareTabela(int dimensiune) {
    TabelaDispersie tabela;
    tabela.dimensiune = dimensiune;
    tabela.liste = (Nod**)malloc(dimensiune * sizeof(Nod*));
    if (tabela.liste == NULL) {
        printf("Eroare la alocarea memoriei pentru tabela de dispersie.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < dimensiune; i++) {
        tabela.liste[i] = creareLista();
    }
    return tabela;
}

void adaugaInTabela(TabelaDispersie* tabela, Cladire c) {
    int index = functieHash(c.anConstruire, tabela->dimensiune);
    adaugaCladire(&tabela->liste[index], c);
}

void afisareCluster(TabelaDispersie tabela, int anConstruire) {
    int index = functieHash(anConstruire, tabela.dimensiune);
    printf("Cladirile construite in anul %d:\n", anConstruire);
    afisareCladiri(tabela.liste[index]);
}

void stergeCladireCuIdSiAn(TabelaDispersie* tabela, int id, int anConstruire) {
    int index = functieHash(anConstruire, tabela->dimensiune);
    Nod* anterior = NULL;
    Nod* curent = tabela->liste[index];

    while (curent != NULL) {
        if (curent->cladire.id == id && curent->cladire.anConstruire == anConstruire) {
            if (anterior == NULL) {
                tabela->liste[index] = curent->next;
            } else {
                anterior->next = curent->next;
            }
            free(curent);
            return;
        }
        anterior = curent;
        curent = curent->next;
    }
}

void stergeCladireCuId(TabelaDispersie* tabela, int id) {
    for (int i = 0; i < tabela->dimensiune; i++) {
        Nod* anterior = NULL;
        Nod* curent = tabela->liste[i];

        while (curent != NULL) {
            if (curent->cladire.id == id) {
                if (anterior == NULL) {
                    tabela->liste[i] = curent->next;
                } else {
                    anterior->next = curent->next;
                }
                free(curent);
                return;
            }
            anterior = curent;
            curent = curent->next;
        }
    }
}

void afisareTabela(TabelaDispersie* tabela) {
    for (int i = 0; i < tabela->dimensiune; i++) {
        printf("Cluster %d:\n", i);
        Nod* curent = tabela->liste[i];
        while (curent != NULL) {
            printf("Id: %d, An construire: %d\n", curent->cladire.id, curent->cladire.anConstruire);
            curent = curent->next;
        }
        printf("\n");
    }
}


void main() {
    TabelaDispersie tabela = creareTabela(10); 
    Cladire c1 = {1, 1990, "Str. I.L Caragiale, nr. 1"};
    Cladire c2 = {2, 1985, "Str. Stefan Cel Mare, nr. 10"};
    Cladire c3 = {3, 1995, "Str. Peroni, nr. 5"};
    adaugaInTabela(&tabela, c1);
    adaugaInTabela(&tabela, c2);
    adaugaInTabela(&tabela, c3);
    afisareCluster(tabela, 1990);
    stergeCladireCuId(&tabela,1);
    stergeCladireCuIdSiAn(&tabela,2,1985);
    afisareTabela(&tabela);
}
