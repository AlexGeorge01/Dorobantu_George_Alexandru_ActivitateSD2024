#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

typedef struct Academie Academie;

//Alexandru Dorobantu 
struct Academie{
   char* denumire;
   int nrStudenti;
   int anInfiintare;
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

void afisareAcademie(const struct Academie a){
    if(a.denumire){
        printf("Denumire: %s\n",a.denumire);
    }
    printf("Nr Studenti: %d\n",a.nrStudenti);
    printf("An infiintare: %d\n",a.anInfiintare);    
}

void dezalocareAcademie(struct Academie* a){
    free(a->denumire);
    a->denumire=NULL;
}

struct Academie citireAcademieDeLaTastatura() {
    struct Academie a;
    a.denumire = malloc(sizeof(char) * 100);
    
    printf("Introduceti denumirea academiei: ");
    scanf("%99s", a.denumire);
    
  
    printf("Introduceti numarul de studenti: ");
    scanf("%d", &a.nrStudenti);
    
 
    printf("Introduceti anul de infiintare: ");
    scanf("%d", &a.anInfiintare);
    
    return a;
}

int calculVechimeAcademie(struct Academie a){
    int vechime=2024-a.anInfiintare;
    return vechime;
}

void modificaNrStudenti(struct Academie* a,int nrNouStudenti){
    a->nrStudenti=nrNouStudenti;
}

void afisareAcademii(Academie* academii,int nrAcademii){
    if(nrAcademii>0&& academii!=NULL){
        for(int i=0;i<nrAcademii;i++){
            printf("\n");
            afisareAcademie(academii[i]);
        }
    }
}

Academie* filtreazaAcademii(Academie* academii, int nrAcademii, int* nrAcademiiFiltrate, int anMinim, int nrStudentiMinim) {
    *nrAcademiiFiltrate = 0;
    Academie* academiiFiltrate = (Academie*)malloc(sizeof(Academie) * nrAcademii);

    if (academiiFiltrate == NULL) {
        printf("Eroare la alocare!");
        exit(1);
    }

    for (int i = 0; i < nrAcademii; i++) {
        if (academii[i].anInfiintare >= anMinim && academii[i].nrStudenti >= nrStudentiMinim) {
            academiiFiltrate[*nrAcademiiFiltrate] = academii[i];
            (*nrAcademiiFiltrate)++;
        }
    }

    return academiiFiltrate;
}

Academie* mutaAcademii(Academie* academii, int nrAcademii, int* nrAcademiiMutate, int anMaxim, int nrStudentiMaxim) {
    *nrAcademiiMutate = 0;
    Academie* academiiMutate = (Academie*)malloc(sizeof(Academie) * nrAcademii);
    if (academiiMutate == NULL) {
        printf("Eroare la alocare!");
        exit(1); 
    }
    for (int i = 0; i < nrAcademii; i++) {
        if (academii[i].anInfiintare <= anMaxim && academii[i].nrStudenti <= nrStudentiMaxim) {
            academiiMutate[*nrAcademiiMutate] = academii[i];
            (*nrAcademiiMutate)++;
        }
    }
    return academiiMutate;
}

Academie* concateneazaVectori(Academie* vector1, int dimensiune1, Academie* vector2, int dimensiune2, int* dimensiuneConcatenata) {
    *dimensiuneConcatenata = dimensiune1 + dimensiune2;
    Academie* vectorConcatenat = (Academie*)malloc(sizeof(Academie) * (*dimensiuneConcatenata));

    if (vectorConcatenat == NULL) {
        printf("Eroare la alocare!");
        exit(1); 
    }
    for (int i = 0; i < dimensiune1; i++) {
        vectorConcatenat[i] = vector1[i];
    }

    for (int i = 0; i < dimensiune2; i++) {
        vectorConcatenat[dimensiune1 + i] = vector2[i];
    }

    return vectorConcatenat;
}

Academie citireAcademieFisier(FILE* f){
    char buffer[50];
    fscanf(f,"%s",buffer);
    Academie a;
    a.denumire=(char*)malloc(sizeof(char)*(strlen(buffer)+1));
    strcpy_s(a.denumire,strlen(buffer)+1,buffer);
    fscanf(f,"%d",&a.nrStudenti);
    fscanf(f,"%d",&a.anInfiintare);
    return a;
}

Academie* citireAcademiiDinFisier(const char* fileName,int* nr){
    FILE* f;
    f=fopen(fileName,"r");
    fscanf(f,"%d",nr);
    Academie* academii=(Academie*)malloc(sizeof(Academie)*(*nr));
    for(int i=0;i<*nr;i++){
        academii[i]=citireAcademieFisier(f);
    }
    return academii;
}

void salvareAcademieInFisier(FILE* f, const Academie academie) {
    fprintf(f, "%s\n", academie.denumire);
    fprintf(f, "%d\n", academie.nrStudenti);
    fprintf(f, "%d\n", academie.anInfiintare);
}

void salvareVectorAcademiiInFisier(const char* numeFisier, const Academie* vectorAcademii, int nrAcademii) {
    FILE* f = fopen(numeFisier, "w");
    fprintf(f, "%d\n", nrAcademii);
    for (int i = 0; i < nrAcademii; i++) {
        fprintf(f, "%s\n", vectorAcademii[i].denumire);
        fprintf(f, "%d\n", vectorAcademii[i].nrStudenti);
        fprintf(f, "%d\n", vectorAcademii[i].anInfiintare);
    }

    fclose(f);
}


void main(){
    int nrAcademii=5;
    Academie* academii=(Academie*)malloc(sizeof(Academie)*nrAcademii);
    for(int i=0;i<nrAcademii;i++){
        academii[i]=initializareAcademie("12345",i+200,i+1937);
    }
     afisareAcademii(academii,nrAcademii);

    struct Academie a1=initializareAcademie("Academia de Studii Economice",1000,1913);
    afisareAcademie(a1);
    // struct Academie a2=citireAcademieDeLaTastatura();
    // int vechimea2=calculVechimeAcademie(a2);
    // printf("Vechime academie: %d\n",vechimea2);
    modificaNrStudenti(&a1,5000);
    afisareAcademie(a1);
    int nrAcademiiFiltrate = 0;
    Academie* academiiFiltrate = filtreazaAcademii(academii, nrAcademii, &nrAcademiiFiltrate, 1940, 202);
    afisareAcademii(academiiFiltrate, nrAcademiiFiltrate);

    free(academiiFiltrate);

    int nrAcademiiMutate = 0;
    Academie* academiiMutate = mutaAcademii(academii, nrAcademii, &nrAcademiiMutate, 1938, 300);
    afisareAcademii(academiiMutate, nrAcademiiMutate);

    free(academiiMutate);
    int nrAcademii2=6;
     Academie* academii2=(Academie*)malloc(sizeof(Academie)*nrAcademii2);
    for(int i=0;i<nrAcademii2;i++){
        academii2[i]=initializareAcademie("12345",i+500,i+1940);
    }
     afisareAcademii(academii2,nrAcademii2);
    int dimensiuneConcatenata = 0;
    Academie* vectorConcatenat = concateneazaVectori(academii, nrAcademii, academii2, nrAcademii2, &dimensiuneConcatenata);
    afisareAcademii(vectorConcatenat, dimensiuneConcatenata);
    free(vectorConcatenat);

    int nrObiecte = 0;
    Academie* vectorObiecte = citireAcademiiDinFisier("academii.txt", &nrObiecte);
    afisareAcademii(vectorObiecte,nrObiecte);
     for (int i = 0; i < nrObiecte; i++) {
        free(vectorObiecte[i].denumire);
    }
    free(vectorObiecte);

    FILE* f = fopen("academieSalvata.txt", "w");
    salvareAcademieInFisier(f, a1);
    fclose(f);
    salvareVectorAcademiiInFisier("vectorAcademiiSalvate.txt",academii2,nrAcademii2);

}