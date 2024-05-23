#include<stdlib.h>
#include<stdio.h>

typedef struct Pacient {
    char* nume;
    int anNastere;
    int gradPrioritate;
} Pacient;

typedef struct Heap {
    Pacient* vector;
    int dimensiune;
} Heap;


Pacient initPacient(const char* nume, int anNastere, int gradPrioritate) {
    Pacient p;
    p.nume = malloc(sizeof(char) * (1 + strlen(nume)));
    strcpy(p.nume, nume);
    p.anNastere = anNastere;
    p.gradPrioritate = gradPrioritate;

    return p;
}


void afisarePacient(Pacient p) {
    printf("Pacientul %s, născut în anul %d, are prioritatea %d\n", p.nume, p.anNastere, p.gradPrioritate);
}


Heap createHeap(int dimensiune) {
    Heap h;
    h.dimensiune = dimensiune;
    h.vector = malloc(sizeof(Pacient) * dimensiune);
    return h;
}


void afisareHeap(Heap h) {
    printf("\nHeap:\n");
    for (int i = 0; i < h.dimensiune; i++) {
        afisarePacient(h.vector[i]);
    }
}


void filtrareHeap(int pozitieRadacina, Heap h) {
    int pozitieFiuDreapta = 2 * pozitieRadacina + 2;
	int pozitieFiuStanga = 2 * pozitieRadacina + 1;

	int indexMaxim = pozitieRadacina;

	if (pozitieFiuDreapta < h.dimensiune &&
		h.vector[indexMaxim].gradPrioritate < h.vector[pozitieFiuDreapta].gradPrioritate) {
		indexMaxim = pozitieFiuDreapta;
	}

	if (pozitieFiuStanga < h.dimensiune &&
		h.vector[indexMaxim].gradPrioritate < h.vector[pozitieFiuStanga].gradPrioritate) {
		indexMaxim = pozitieFiuStanga;
	}

	if (pozitieRadacina != indexMaxim) {
		Pacient pacientDeMutat = h.vector[indexMaxim];
		h.vector[indexMaxim] = h.vector[pozitieRadacina];
		h.vector[pozitieRadacina] = pacientDeMutat;
		if (2 * indexMaxim + 1 < h.dimensiune) {
			filtrareHeap(indexMaxim, h);
		}
	}
}


void inserarePacientInHeap(Pacient p, Heap* h) {
    Pacient* vectorTemp = malloc(sizeof(Pacient) * (h->dimensiune + 1));
	for (int i = 0; i < h->dimensiune; i++) {
		vectorTemp[i] = h->vector[i];
	}
	vectorTemp[h->dimensiune] = p;
	h->dimensiune++;
	free(h->vector);
	h->vector = vectorTemp;
	for (int i = ((*h).dimensiune - 1) / 2; i >= 0; i--) {
		filtrareHeap(i, (*h));
	}
}

Pacient extragePacientGrav(Heap* heap) {
    struct Pacient aux = heap->vector[0];
	heap->vector[0] = heap->vector[heap->dimensiune - 1];
	heap->vector[heap->dimensiune - 1] = aux;
	heap->dimensiune--;
	for (int i = (heap->dimensiune - 1) / 2; i >= 0; i--) {
		filtrareHeap(i, *heap);
	}
	return aux;
}

int main() {
   
    Heap h = createHeap(7);
    h.vector[0] = initPacient("Gheorghe Matei", 2001, 5);
    h.vector[1] = initPacient("Popescu Ion", 1995, 7);
    h.vector[2] = initPacient("George Ioan", 1946, 6);
    h.vector[3] = initPacient("Mateescu Tudor", 2000, 2);
    h.vector[4] = initPacient("Ganea Maria", 2018, 4);
    h.vector[5] = initPacient("Claudiu Marian", 1991, 3);
    h.vector[6] = initPacient("Alexandru Popa", 2007, 8);

    
    afisareHeap(h);

    
    for (int i = (h.dimensiune - 2) / 2; i >= 0; i--) {
        filtrareHeap(i, h);
    }

    printf("\n Heap filtrat \n");
    afisareHeap(h);

    // Adăugarea de noi pacienți în heap
    inserarePacientInHeap(initPacient("Grav", 2004, 8), &h);
    inserarePacientInHeap(initPacient("Mediu", 2004, 5), &h);
    inserarePacientInHeap(initPacient("OK", 2004, 2), &h);
    printf("\n Heap cu pacienți adăugați \n");
    afisareHeap(h);

    // Extragerea a 3 pacienți cu cea mai mare prioritate și afișarea lor
    printf("\n Extragem 3 pacienți gravi  \n");
    for (int i = 0; i < 3; i++) {
        Pacient pacient = extragePacientGrav(&h);
        afisarePacient(pacient);
    }

    // Afișarea heap-ului după extragere
    printf("\n Afisare heap \n");
    afisareHeap(h);

    return 0;
}
