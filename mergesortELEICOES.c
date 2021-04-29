/* 
Programa: Eleicoes
Autor: Gabriel Bianchi e Silva
Versao: 1.0 - 18/01/2021
*/

#include <stdio.h>
#include <stdlib.h>

void primeiroTurno(int n, int mat[n][3], int candidatos) // n == eleitores
{
    int i, j, verCandidatos[candidatos], checar = 0, tamanhoreal = 0;
    float vetPorcentagem[candidatos], x, vetAux[candidatos];
    for (i = 0; i < candidatos; i++)
    {
        verCandidatos[i] = 0;
    }

    i = 0;

    for (i = 0; i < n; i++) //le a primeira linha, com as primeiras opcoes
    {
        for (j = 0; j < candidatos; j++)
        {
            if (mat[i][0] == j + 1)
            {
                if (mat[i][0] != 0 || mat[i][0] <= n) //checar se o voto eh valido
                {
                    verCandidatos[j]++;
                    tamanhoreal++;
                }
            }
        }
    }

    for (i = 0; i < candidatos; i++) //preenche um segundo vetor com as porcentagens relativas a cada candidato
    {
        x = verCandidatos[i];
        vetPorcentagem[i] = (x / tamanhoreal) * 100;
    }
    for (i = 0; i < candidatos; i++) //vetor auxiliar para saber o numero de cada candidato mesmo depois de ordenar as porcentagens
    {
        vetAux[i] = vetPorcentagem[i];
    }

    for (i = 0; i < candidatos; i++)
    {
        if (vetPorcentagem[i] >= 50)
        {
            printf("%d %.2f", i + 1, vetPorcentagem[i]);
            checar++;
        }
    }

    if (tamanhoreal == 0)
    {
        printf("0\n");
        checar++;
    }

    float cand1, cand2, aux;

    if (checar == 0) //segundo turno começa
    {
        for (i = 0; i < candidatos; i++)
        {
            for (j = 0; j < candidatos; j++)
            {
                if (vetPorcentagem[i] > vetPorcentagem[j])
                {
                    aux = vetPorcentagem[i];
                    vetPorcentagem[i] = vetPorcentagem[j];
                    vetPorcentagem[j] = aux;
                }
            }
        }
        int pos1 = 0, pos2 = 0, votosprimeiro = 0, votossegundo = 0;
        i = 0;
        cand1 = vetPorcentagem[i]; //os 2 que passarem para o segundo turno
        cand2 = vetPorcentagem[i + 1];
        for (i = 0; i < candidatos; i++) //verifica qual o numero dos que passaram para o segundo turno
        {
            if (pos1 == 0 || pos2 == 0)
            {
                if (vetPorcentagem[0] == vetAux[i]) //desempatar AQUI!!!
                {
                    pos1 = i + 1;
                }
                else if (vetPorcentagem[1] == vetAux[i]) //desempatar AQUI!!!
                {
                    pos2 = i + 1;
                }
            }
        }
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < 3; j++)
            {
                if (mat[i][j] == pos1)
                {
                    votosprimeiro++;
                    break;
                }
                else if (mat[i][j] == pos2)
                {
                    votossegundo++;
                    break;
                }
            }
        }
        float temp1, temp2;
        int novoTotal;
        novoTotal = votosprimeiro + votossegundo;
        float porcent1, porcent2;
        temp1 = votosprimeiro;
        temp2 = votossegundo;
        porcent1 = (temp1 / novoTotal) * 100;
        porcent2 = (temp2 / novoTotal) * 100;
        if (votosprimeiro > votossegundo)
        {
            printf("%d %.2f", pos1, cand1);
            printf("\n");
            printf("%d %.2f", pos1, porcent1);
        }
        else if (votossegundo > votosprimeiro)
        {
            printf("%d %.2f", pos1, cand1);
            printf("\n");
            printf("%d %.2f", pos2, porcent2);
        }
        else //empate no segundo turno
        {
            if (pos1 < pos2)
            {
                printf("%d %.2f", pos1, cand1);
                printf("\n");
                printf("%d %.2f", pos1, porcent1);
            }
            else if (pos2 < pos1)
            {
                printf("%d %.2f", pos1, cand1);
                printf("\n");
                printf("%d %.2f", pos2, porcent2);
            }
        }
    }
    //cand1 eh a porcentagem do primeiro lugar no primeiro turno, e pos1 o numero dele, para printar no final
}

int main()
{
    int i, j, k, candidatos, eleitores, primeiro, segundo, terceiro;

    scanf("%d %d", &eleitores, &candidatos);

    int matVotos[eleitores][3];

    for (i = 0; i < eleitores; i++) //preenchendo a matriz
    {
        scanf("%d %d %d", &primeiro, &segundo, &terceiro);
        matVotos[i][0] = primeiro;
        matVotos[i][1] = segundo;
        matVotos[i][2] = terceiro;
    }

    primeiroTurno(eleitores, matVotos, candidatos);

    return 0;
}
