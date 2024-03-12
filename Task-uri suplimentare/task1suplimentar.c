#include<stdio.h>
#include<malloc.h>

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

void afisareAcademie(const struct Academie* a){
    if(a->denumire){
        printf("Denumire: %s\n",a->denumire);
    }
    printf("Nr Studenti: %d\n",a->nrStudenti);
    printf("An infiintare: %d\n",a->anInfiintare);    
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

void main(){
    struct Academie a1=initializareAcademie("Academia de Studii Economice",1000,1913);
    afisareAcademie(&a1);
    struct Academie a2=citireAcademieDeLaTastatura();
    int vechimea2=calculVechimeAcademie(a2);
    printf("Vechime academie: %d\n",vechimea2);
    modificaNrStudenti(&a1,5000);
    afisareAcademie(&a1);
}