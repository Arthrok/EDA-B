#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <time.h>


typedef struct Data
{
    int thumbsup;
    char *review;
} Data;

typedef struct
{
    size_t size;
    size_t capacity;
    Data *data;
} Vector;

void init(Vector *vetor){
    vetor->capacity = 1;
    vetor->size = 0;
    vetor->data = (Data*)malloc(sizeof(Data));
}

void push_back(Vector *vetor, Data *nData){
    if (vetor->size == vetor->capacity){
        vetor->capacity++;
        vetor->data = realloc(vetor->data, vetor->capacity * sizeof(Data));
    }

    vetor->data[vetor->size].review = (char*)malloc(sizeof(char)*(strlen(nData->review) + 1));
    strcpy(vetor->data[vetor->size].review, nData->review);
    vetor->data[vetor->size].thumbsup = nData->thumbsup;
    vetor->size++;
}

void bs(int n, Vector *vetor) {
	int c = 0, d; Data troca; int trocou = 1; 
	while ((c < (n - 1)) & trocou) {
		trocou = 0;
		for (d = 0; d < n - c - 1; d++)
			if (vetor->data[d].thumbsup < vetor->data[d + 1].thumbsup) { // COMANDO A SER CONTABILIZADO
				troca = vetor->data[d];
				vetor->data[d] = vetor->data[d + 1];
				vetor->data[d + 1] = troca;
				trocou = 1; 
			}
	}
}

void read(char *arquivo, Vector *vetor){
    FILE *fp;
    char line[5000];
    char *delimiter = ";\n";
    char *token;
    int k = 0;
    Data nData;
    nData.review = (char*)malloc(sizeof(char)*210);

    fp = fopen(arquivo, "r");
    

    while (fgets(line, sizeof(line), fp))
    {
        token = strtok(line, delimiter);
        while (token != NULL)
        {
            if(k == 1){
                strncpy(nData.review, token, 200);
                nData.review[200] = '\0';
                push_back(vetor, &nData);
                
                k = 0;
            } else{
                nData.thumbsup = atoi(token);
                k++;
            }


            token = strtok(NULL, delimiter);
        }
        
    }
    
    free(nData.review);
    fclose(fp);
}

void write(char *arquivo, Vector *vetor){
    FILE *fp;
    int i = 0;
    char buffer[5];
    fp = fopen(arquivo, "w+");

    while (i != vetor->size)
    {
        sprintf(buffer, "%d", vetor->data[i].thumbsup);
        fprintf(fp, "%-5s  %-22s\n", buffer, vetor->data[i].review);
        i++;
    }

    fclose(fp);
}


int main(){
    clock_t start = clock();

    Vector vetor;
    init(&vetor);

    read("review.txt", &vetor);

    bs(vetor.size, &vetor);

    write("reviewFormat.txt", &vetor);

    free(vetor.data);
    vetor.data = NULL;

    clock_t end = clock();
    double tempo = (end - start) / (double)CLOCKS_PER_SEC;

    printf("Tempo de execucao: %f segundos\n", tempo);

    return 0;
}