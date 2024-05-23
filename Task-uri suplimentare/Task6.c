#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Academie Academie;
typedef struct NodLdi NodLdi;
typedef struct ListaDubla listaDubla;

//Alexandru Dorobantu 
struct Academie{
   char* denumire;
   int nrStudenti;
   int anInfiintare;
};

struct NodLdi{
  Academie info;
  NodLdi* next;
  NodLdi* prev;
};

struct ListaDubla{
    NodLdi* prim;
    NodLdi* ultim;
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

void inserareListaDublaSfarsit(listaDubla* listaDubla,Academie a){
    NodLdi* nod=(NodLdi*)malloc(sizeof(NodLdi));
    nod->prev=listaDubla->ultim;
    nod->next=NULL;
    nod->info=initializareAcademie(a.denumire,a.nrStudenti,a.anInfiintare);
    if(listaDubla->ultim!=NULL){
        listaDubla->ultim->next=nod;
    }
    else{
        listaDubla->prim=nod;
    }
    listaDubla->ultim=nod;
}

void afisareAcademie(const struct Academie a){
    if(a.denumire){
        printf("Denumire: %s\n",a.denumire);
    }
    printf("Nr Studenti: %d\n",a.nrStudenti);
    printf("An infiintare: %d\n",a.anInfiintare);    
}

void afisareDeLaInceput(listaDubla listaDubla){
    NodLdi* p=listaDubla.prim;
    while(p){
        afisareAcademie(p->info);
        p=p->next;
    }
}
void afisareDeLaSfarsit(listaDubla listaDubla){
    NodLdi* p=listaDubla.ultim;
    while(p){
        afisareAcademie(p->info);
        p=p->prev;
    }
}

void stergereListaDubla(listaDubla* listaDubla){
    NodLdi* p=listaDubla->prim;
    while(p){
        free(p->info.denumire);
        NodLdi* temp=p->next;
        free(p);
        p=temp;
        
    }
    listaDubla->prim=NULL;
    listaDubla->ultim=NULL;
}

void citireAcademiiDinFisier(const char* fileName, listaDubla* lista) {
    FILE* f = fopen(fileName, "r");
    if (f == NULL) {
        perror("Eroare la deschiderea fișierului");
        return;
    }

    int nrAcademii;
    fscanf(f, "%d", &nrAcademii);

    for (int i = 0; i < nrAcademii; i++) {
        char denumire[50];
        int nrStudenti;
        int anInfiintare;

        fscanf(f, "%s", denumire);
        fscanf(f, "%d", &nrStudenti);
        fscanf(f, "%d", &anInfiintare);

        Academie a = initializareAcademie(denumire, nrStudenti, anInfiintare);
        inserareListaDublaSfarsit(lista, a);
    }

    fclose(f);
}

void stergereNodPozitie(listaDubla* lista, int pozitie) {
    if (lista->prim == NULL) return; 

    NodLdi* temp = lista->prim;
    int count = 0;

    
    while (temp != NULL && count < pozitie) {
        temp = temp->next;
        count++;
    }

    
    if (temp == NULL) return;

    
    if (temp == lista->prim) {
        lista->prim = temp->next;
        if (lista->prim != NULL) {
            lista->prim->prev = NULL;
        } else {
            lista->ultim = NULL; 
        }
    } else if (temp == lista->ultim) { 
        lista->ultim = temp->prev;
        lista->ultim->next = NULL;
    } else { 
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
    }

    
    free(temp->info.denumire);
    free(temp);
}
void inserareSortata(listaDubla* lista, Academie a) {
    NodLdi* nod = (NodLdi*)malloc(sizeof(NodLdi));
    nod->info = initializareAcademie(a.denumire, a.nrStudenti, a.anInfiintare);
    nod->next = NULL;
    nod->prev = NULL;

    if (lista->prim == NULL) { 
        lista->prim = nod;
        lista->ultim = nod;
    } else if (lista->prim->info.anInfiintare >= nod->info.anInfiintare) { // Inserare la început
        nod->next = lista->prim;
        lista->prim->prev = nod;
        lista->prim = nod;
    } else {
        NodLdi* temp = lista->prim;
        while (temp->next != NULL && temp->next->info.anInfiintare < nod->info.anInfiintare) {
            temp = temp->next;
        }
        nod->next = temp->next;
        if (temp->next != NULL) {
            temp->next->prev = nod;
        } else {
            lista->ultim = nod;
        }
        temp->next = nod;
        nod->prev = temp;
    }
}

void interschimbarePozitii(listaDubla* lista, int pozitie1, int pozitie2) {
    if (lista == NULL || lista->prim == NULL) {
        printf("Lista este vida sau invalida.\n");
        return;
    }

    NodLdi *nod1 = lista->prim, *nod2 = lista->prim;
    int lungimeLista = 0;

  
    for (NodLdi* temp = lista->prim; temp != NULL; temp = temp->next) {
        lungimeLista++;
    }


    if (pozitie1 < 1 || pozitie2 < 1 || pozitie1 > lungimeLista || pozitie2 > lungimeLista) {
        printf("Pozitiile nu sunt valide.\n");
        return;
    }

 
    for (int i = 1; i < pozitie1; i++) {
        nod1 = nod1->next;
    }

    for (int i = 1; i < pozitie2; i++) {
        nod2 = nod2->next;
    }

    
    Academie temp = nod1->info;
    nod1->info = nod2->info;
    nod2->info = temp;
}


int comparareAnInfiintare(const void* a, const void* b) {
    return ((Academie*)a)->anInfiintare - ((Academie*)b)->anInfiintare;
}


void afisareSortataCrescator(listaDubla lista) {

    if (lista.prim == NULL) {
        printf("Lista este goala.\n");
        return;
    }

    int nrElemente = 0;
    for (NodLdi* nod = lista.prim; nod != NULL; nod = nod->next) {
        nrElemente++;
    }

 
    Academie* vectorAcademii = (Academie*)malloc(nrElemente * sizeof(Academie));
    if (vectorAcademii == NULL) {
        printf("Eroare la alocare de memorie.\n");
        return;
    }

    int i = 0;
    for (NodLdi* nod = lista.prim; nod != NULL; nod = nod->next) {
        vectorAcademii[i++] = nod->info;
    }

    qsort(vectorAcademii, nrElemente, sizeof(Academie), comparareAnInfiintare);


    printf("Elementele sortate crescator:\n");
    for (int j = 0; j < nrElemente; j++) {
        afisareAcademie(vectorAcademii[j]);
    }

    free(vectorAcademii);
}

void afisareSortataDescrescator(listaDubla lista) {
 
    if (lista.prim == NULL) {
        printf("Lista este goala.\n");
        return;
    }

    int nrElemente = 0;
    for (NodLdi* nod = lista.prim; nod != NULL; nod = nod->next) {
        nrElemente++;
    }

    Academie* vectorAcademii = (Academie*)malloc(nrElemente * sizeof(Academie));
    if (vectorAcademii == NULL) {
        printf("Eroare la alocare de memorie.\n");
        return;
    }

    int i = 0;
    for (NodLdi* nod = lista.prim; nod != NULL; nod = nod->next) {
        vectorAcademii[i++] = nod->info;
    }

    qsort(vectorAcademii, nrElemente, sizeof(Academie), comparareAnInfiintare);

    printf("Elementele sortate descrescator:\n");
    for (int j = nrElemente - 1; j >= 0; j--) {
        afisareAcademie(vectorAcademii[j]);
    }

    free(vectorAcademii);
}


void main(){
 listaDubla lista = {NULL, NULL};

    citireAcademiiDinFisier("academii.txt", &lista);

    printf("Lista inițială:\n");
    afisareDeLaInceput(lista);

    int pozitie = 1;
    stergereNodPozitie(&lista, pozitie);

    printf("\nLista după ștergerea nodului de pe poziția %d:\n", pozitie);
    afisareDeLaInceput(lista);
    
    interschimbarePozitii(&lista,1,2);
    printf("\nDupa interschimbare: \n");
    afisareDeLaInceput(lista);

    stergereListaDubla(&lista);



}