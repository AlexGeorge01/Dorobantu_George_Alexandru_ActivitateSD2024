#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Academie Academie;
typedef struct Nod Nod;

//Alexandru Dorobantu 
struct Academie{
   char* denumire;
   int nrStudenti;
   int anInfiintare;
};

struct Nod{
  Academie info;
  Nod* next;
};


struct Academie initializareAcademie(const char* denumire,int nrStudenti,int anInfiintare){
    struct Academie a;
    a.nrStudenti=nrStudenti;
    a.anInfiintare=anInfiintare;
    if(denumire){
        a.denumire=malloc(sizeof(char)*strlen(denumire)+1);
        strcpy(a.denumire,denumire);
    }else{
        a.denumire=malloc(strlen("N/A")+1);
        strcpy(a.denumire,"N/A");
    }
    return a;
}

Nod* inserareLaInceput(Nod* cap,Academie a){
    Nod* nou=(Nod*)malloc(sizeof(Nod));
    nou->info=initializareAcademie(a.denumire,a.nrStudenti,a.anInfiintare);
    nou->next=cap;
    return nou;
}

void afisareAcademie(const struct Academie a){
    if(a.denumire){
        printf("Denumire: %s\n",a.denumire);
    }
    printf("Nr Studenti: %d\n",a.nrStudenti);
    printf("An infiintare: %d\n",a.anInfiintare);    
}

void afisareLista(Nod* cap){
   while(cap){
    afisareAcademie(cap->info);
    cap=cap->next;
   }
}

void stergeLista(Nod** cap){
    while(*cap){
        free((*cap)->info.denumire);
        Nod* copie=(*cap);
        *cap=(*cap)->next;
        free(copie);
    }
}

// Nod* citireAcademiiDinFisier(const char* fileName) {
//     FILE* f = fopen(fileName, "r");
//     if (!f) {
//         printf("Eroare la deschiderea fișierului!\n");
//         return NULL;
//     }
    
//     int nrAcademii;
//     fscanf(f, "%d", &nrAcademii);

//     Nod* head = NULL;
//     Nod* tail = NULL;

//     for (int i = 0; i < nrAcademii; i++) {
//         char buffer[50];
//         fscanf(f, "%s", buffer);

//         Academie academie;
//         academie.denumire = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
//         strcpy(academie.denumire, buffer);
//         fscanf(f, "%d", &academie.nrStudenti);
//         fscanf(f, "%d", &academie.anInfiintare);

//         Nod* newNod = (Nod*)malloc(sizeof(Nod));
//         newNod->info = academie;
//         newNod->next = NULL;

//         if (head == NULL) {
//             head = newNod;
//             tail = newNod;
//         } else {
//             tail->next = newNod;
//             tail = newNod;
//         }
//     }

//     fclose(f);
//     return head;
// }
Nod* citireAcademiiDinFisier(const char* fileName) {
    FILE* f = fopen(fileName, "r");
    if (!f) {
        printf("Eroare la deschiderea fișierului!\n");
        return NULL;
    }
    
    int nrAcademii;
    fscanf(f, "%d", &nrAcademii);

    Nod* head = NULL;

    for (int i = 0; i < nrAcademii; i++) {
        char buffer[50];
        fscanf(f, "%s", buffer);

        Academie academie;
        academie.denumire = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
        strcpy(academie.denumire, buffer);
        fscanf(f, "%d", &academie.nrStudenti);
        fscanf(f, "%d", &academie.anInfiintare);

        head = inserareLaInceput(head, academie);
        free(academie.denumire); 
    }

    fclose(f);
    return head;
}

void stergeNod(Nod** head, int pozitie) {
    if (*head == NULL) return;

    Nod* temp = *head;

    if (pozitie == 0) {
        *head = temp->next;
        free(temp->info.denumire);
        free(temp);
        return;
    }

    for (int i = 0; temp != NULL && i < pozitie - 1; i++) {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL) return;

    Nod* next = temp->next->next;
    free(temp->next->info.denumire);
    free(temp->next);
    temp->next = next;
}

Nod* inserareSortata(Nod* cap, Academie a) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = initializareAcademie(a.denumire, a.nrStudenti, a.anInfiintare);
    nou->next = NULL;

    if (cap == NULL || cap->info.nrStudenti >= a.nrStudenti) {
        nou->next = cap;
        return nou;
    }

    Nod* current = cap;
    while (current->next != NULL && current->next->info.nrStudenti < a.nrStudenti) {
        current = current->next;
    }

    nou->next = current->next;
    current->next = nou;

    return cap;
}

void interschimbaElemente(Nod** head, int poz1, int poz2) {
    if (poz1 == poz2) return;

    Nod* prev1 = NULL, * curr1 = *head;
    Nod* prev2 = NULL, * curr2 = *head;

    int i = 0;
    while (curr1 != NULL && i < poz1) {
        prev1 = curr1;
        curr1 = curr1->next;
        i++;
    }

    i = 0;
    while (curr2 != NULL && i < poz2) {
        prev2 = curr2;
        curr2 = curr2->next;
        i++;
    }

    if (curr1 == NULL || curr2 == NULL) return;

    if (prev1 != NULL) {
        prev1->next = curr2;
    } else {
        *head = curr2;
    }

    if (prev2 != NULL) {
        prev2->next = curr1;
    } else {
        *head = curr1;
    }

    Nod* temp = curr2->next;
    curr2->next = curr1->next;
    curr1->next = temp;
}


void main(){
     Nod* listaAcademii = citireAcademiiDinFisier("academii.txt");

    printf("Lista academii initiala:\n");
    afisareLista(listaAcademii);

    stergeNod(&listaAcademii, 3); // Șterge nodul de pe poziția 3

    printf("\nLista academii dupa stergerea nodului de pe pozitia 3:\n");
    afisareLista(listaAcademii);
    interschimbaElemente(&listaAcademii,1,2);
    printf("\nDupa interschimbare:\n");
    afisareLista(listaAcademii);

}