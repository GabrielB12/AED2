#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nome[15];
    int idade;
} Dados;

void trocaPivo(Dados vet[], int i, int j)
{
    Dados temp = vet[i];
    vet[i] = vet[j];
    vet[j] = temp;
}

int particiona(int inicio, int fim, Dados vet[]) //vai retornar o indice do pivo
{
    Dados a, b, c;
    int meio, indiceMediana;

    meio = (inicio + fim) / 2;
    a = vet[inicio];
    b = vet[meio];
    c = vet[fim];
    indiceMediana = 0;

    if (a.idade < b.idade)
    {
        if (b.idade < c.idade) //a < b && b < c
        {
            indiceMediana = meio;
        }
        else if (a.idade < c.idade) // a < c &&c <= b
        {
            indiceMediana = fim;
        }
        else //c <= a && a < b
        {
            indiceMediana = inicio;
        }
    }

    else if (c.idade < b.idade) //c < b && b <= a
    {
        indiceMediana = meio;
    }

    else if (c.idade < a.idade) //b <= c &&c < a
    {
        indiceMediana = fim;
    }
    else //b <= a && a <= c
    {
        indiceMediana = inicio;
    }

    trocaPivo(vet, indiceMediana, fim); //coloca ele no final

    //*******************ALGORITMO DE PARTIÇÃO DE CORMEN*********************
    //o pivo ta em ultimo
    Dados pivo = vet[fim];
    int i = inicio - 1;
    int j;

    for (j = inicio; j <= fim - 1; j++) //ordenando o vetor com o pivo como referencia, menores ou iguais a esquerda
    {
        if (vet[j].idade <= pivo.idade)
        {
            i = i + 1;
            trocaPivo(vet, i, j);
        }
    }
    //coloca o pivô na posição de ordenação
    trocaPivo(vet, i + 1, fim);
    return i + 1; //retorna a posição do pivô
}

void quickSort(Dados vet[], int inicio, int fim)
{
    int pivo, i;
    if (fim > inicio)
    {
        pivo = particiona(inicio, fim, vet);
        quickSort(vet, inicio, pivo - 1);
        quickSort(vet, pivo + 1, fim);
    }
}

void checaEstavel(Dados vet[], Dados vetAux[], int tam)
{
    int i, j, temp;

    for (i = 0; i < tam - 2; i++)
    {
        if (temp == 0 && vet[i].idade == vetAux[i + 1].idade)
        {
            for (j = 0; j < tam; j++)
            {
                if (vet[i].nome != vetAux[i].nome)
                {
                    temp++;
                    break;
                }
            }
        }
    }
    if (temp == 0)
    {
        printf("yes\n");
    }
    else
    {
        printf("no\n");
    }
}

int main()
{
    int numPessoas, i, prim, seg;

    scanf("%d", &numPessoas);

    Dados Info[numPessoas], Infoaux[numPessoas];

    for (i = 0; i < numPessoas; i++)
    {
        scanf("%s %d", Info[i].nome, &Info[i].idade);
        Infoaux[i].idade = Info[i].idade;
        strcpy(Infoaux[i].nome, Info[i].nome);
    }
    scanf("%d %d", &prim, &seg);

    quickSort(Info, 0, numPessoas - 1);

    checaEstavel(Info, Infoaux, numPessoas);

    for (i = 0; i < seg; i++)
    {
        printf("%s %d\n", Info[i + prim - 1].nome, Info[i + prim - 1].idade);
    }

    return 0;
}
