// ##################### Bibliotecas Externas ##############################

#include <stdio.h>
#include <stdlib.h>

// ########################## TAD X.h ######################################

struct noABB
{
    int valor;
    struct noABB *esq;
    struct noABB *dir;
    struct noABB *pai;
};
typedef struct noABB arvore;

// ###################### Funcoes e Procedimentos do programa ##############

void inicia(int num, arvore *teste)
{
    teste->valor = num;
    teste->dir = NULL;
    teste->esq = NULL;
}

int max(int x, int y) //maior entre 2 valores, funcao auxiliar para achar a altura
{
    if (x > y)
    {
        return x;
    }
    else
    {
        return y;
    }
}

int altura(arvore *teste) //conta quantos "andares" tem, pela comaparacao entre os filhos
{
    if (teste == NULL)
    {
        return 0;
    }
    else
    {
        return max(altura(teste->esq), altura(teste->dir)) + 1;
    }
}

int fatorBalanceamento(arvore *teste)
{
    int x;
    x = altura(teste->esq) - altura(teste->dir);
    return x;
}

void insereOrdem(arvore *aux, arvore **teste) //teste é a raiz no main, e sao dois "*" por ser ponteiro de ponteiro
{
    arvore *y = NULL;
    arvore *x = (*teste);
    while (x != NULL)
    {
        y = x;
        if (aux->valor < x->valor)
        {
            x = x->esq;
        }
        else
        {
            x = x->dir;
        }
    }

    aux->pai = y;

    if (y == NULL)
    {
        *teste = aux;
    }
    else if (aux->valor < y->valor)
    {
        y->esq = aux;
    }
    else
    {
        y->dir = aux;
    }
}

void transplant(arvore **teste, arvore **u, arvore *v) //funcao igual à dos slides
{
    if ((*u)->pai == NULL) //nesse formato por ser **teste
    {
        *teste = v;
    }
    else if ((*u) == (*u)->pai->esq)
    {
        (*u)->pai->esq = v;
    }
    else
    {
        (*u)->pai->dir = v;
    }
    if (v != NULL)
    {
        v->pai = (*u)->pai;
    }
}

arvore *minimo(arvore *teste) //menor numero antes do informado
{
    while (teste->esq)
    {
        teste = teste->esq;
    }
    return teste;
}

void removeNo(arvore **aux, arvore **teste) //aux é o no a ser removido
{
    if ((*aux)->esq == NULL) //nesse formato por ser **teste
    {
        transplant(teste, aux, (*aux)->dir);
    }
    else if ((*aux)->dir == NULL)
    {
        transplant(teste, aux, (*aux)->esq);
    }
    else
    {
        arvore *y = minimo((*aux)->dir);
        if (y->pai != *aux)
        {
            transplant(teste, &y, y->dir);
            y->dir = (*aux)->dir;
            y->dir->pai = y;
        }
        transplant(teste, aux, y);
        y->esq = (*aux)->esq;
        y->esq->pai = y;
    }
}

arvore *busca(int valor, arvore *teste)
{
    if (teste != NULL)
    {
        if (valor < teste->valor)
        {
            busca(valor, teste->esq);
        }
        else if (valor > teste->valor)
        {
            busca(valor, teste->dir);
        }
        else
        {
            return teste; //retorna o elemento encontrado
        }
    }
    else
    {
        return teste; //retorna NULL, ou seja, o elemento não existe na arvore
    }
}

arvore *LL(arvore *pA)
{
    arvore *pB = NULL;
    pB = pA->esq;
    pA->esq = pB->dir;
    pB->dir = pA;
    return pB;
}

arvore *RR(arvore *pA)
{
    arvore *pB = NULL;
    pB = pA->dir;
    pA->dir = pB->esq;
    pB->esq = pA;
    return pB;
}

arvore *LR(arvore *pA)
{
    arvore *pB = NULL, *pC = NULL;
    pB = pA->esq;
    pC = pB->dir;
    pB->dir = pC->esq;
    pC->esq = pB;
    pA->esq = pC->dir;
    pC->dir = pA;
    return pC;
}

arvore *RL(arvore *pA)
{
    arvore *pB = NULL, *pC = NULL;
    pB = pA->dir;
    pC = pB->esq;
    pB->esq = pC->dir;
    pC->dir = pB;
    pA->dir = pC->esq;
    pC->esq = pA;
    return pC;
}

void insereAVL();

void removeAVL();

void Imprime(arvore *teste)
{
    if (teste != NULL)
    {
        printf("(C%d", teste->valor);
        Imprime(teste->esq);
        Imprime(teste->dir);
        printf(")");
    }
    else
        printf("()");
}
// ############################ Principal ###################################

int main()
{
    int qnt, i, num, tam = 0, chave, alturaAVL, novaAlturaAVL;
    arvore *raiz = NULL;
    arvore *checa;
    arvore *novaArvore;
    arvore *final;

    scanf("%d", &qnt);

    for (i = 0; i < qnt; i++) //le os valores e vai colocando eles na arvore
    {
        scanf("%d", &num);
        if (busca(num, raiz) != NULL)
        {
            continue;
        }
        tam++; //contar o tamanho da arvore
        arvore *aux = malloc(sizeof(arvore));
        inicia(num, aux);
        insereOrdem(aux, &raiz); //insere o nó na árvore
    }

    scanf("%d", &chave);
    checa = busca(chave, raiz);

    if (fatorBalanceamento(raiz) > 1 && fatorBalanceamento(raiz->esq) > 0)
    {
        novaArvore = LL(raiz);
    }
    else if (fatorBalanceamento(raiz) < -1 && fatorBalanceamento(raiz->dir) < 0)
    {
        novaArvore = RR(raiz);
    }
    else if (fatorBalanceamento(raiz) > 1 && fatorBalanceamento(raiz->esq) < 0)
    {
        novaArvore = LR(raiz);
    }
    else if (fatorBalanceamento(raiz) < -1 && fatorBalanceamento(raiz->dir) > 0)
    {
        novaArvore = RL(raiz);
    }

    alturaAVL = altura(novaArvore);

    if (checa == NULL)
    {
        if (chave < novaArvore->valor)
        {
            if (altura(novaArvore->esq) > altura(novaArvore->dir))
            {
                arvore *aux2 = malloc(sizeof(arvore));
                inicia(chave, aux2);
                insereOrdem(aux2, &novaArvore); //insere o nó na árvore
                if (fatorBalanceamento(novaArvore) > 1 && fatorBalanceamento(novaArvore->esq) > 0)
                {
                    final = LL(novaArvore);
                }
                else if (fatorBalanceamento(novaArvore) < -1 && fatorBalanceamento(novaArvore->dir) < 0)
                {
                    final = RR(novaArvore);
                }
                else if (fatorBalanceamento(novaArvore) > 1 && fatorBalanceamento(novaArvore->esq) < 0)
                {
                    final = LR(novaArvore);
                }
                else if (fatorBalanceamento(novaArvore) < -1 && fatorBalanceamento(novaArvore->dir) > 0)
                {
                    final = RL(novaArvore);
                }
                Imprime(final);
            }
            else
            {
                arvore *aux2 = malloc(sizeof(arvore));
                inicia(chave, aux2);
                insereOrdem(aux2, &novaArvore); //insere o nó na árvore
                Imprime(novaArvore);
            }
        }

        else if (chave >= novaArvore->valor)
        {
            if (altura(novaArvore->esq) < altura(novaArvore->dir))
            {
                arvore *aux2 = malloc(sizeof(arvore));
                inicia(chave, aux2);
                insereOrdem(aux2, &novaArvore); //insere o nó na árvore
                if (fatorBalanceamento(novaArvore) > 1 && fatorBalanceamento(novaArvore->esq) > 0)
                {
                    final = LL(novaArvore);
                }
                else if (fatorBalanceamento(novaArvore) < -1 && fatorBalanceamento(novaArvore->dir) < 0)
                {
                    final = RR(novaArvore);
                }
                else if (fatorBalanceamento(novaArvore) > 1 && fatorBalanceamento(novaArvore->esq) < 0)
                {
                    final = LR(novaArvore);
                }
                else if (fatorBalanceamento(novaArvore) < -1 && fatorBalanceamento(novaArvore->dir) > 0)
                {
                    final = RL(novaArvore);
                }
                Imprime(final);
            }
            else
            {
                arvore *aux2 = malloc(sizeof(arvore));
                inicia(chave, aux2);
                insereOrdem(aux2, &novaArvore); //insere o nó na árvore
                Imprime(novaArvore);
            }
        }
    }
    else if (checa != NULL)
    {
        int teste = 0;
        removeNo(&checa, &novaArvore);
        if (fatorBalanceamento(novaArvore) > 1 && fatorBalanceamento(novaArvore->esq) > 0)
        {
            final = LL(novaArvore);
            teste++;
        }
        else if (fatorBalanceamento(novaArvore) < -1 && fatorBalanceamento(novaArvore->dir) < 0)
        {
            final = RR(novaArvore);
            teste++;
        }
        else if (fatorBalanceamento(novaArvore) > 1 && fatorBalanceamento(novaArvore->esq) < 0)
        {
            final = LR(novaArvore);
            teste++;
        }
        else if (fatorBalanceamento(novaArvore) < -1 && fatorBalanceamento(novaArvore->dir) > 0)
        {
            final = RL(novaArvore);
            teste++;
        }
        if (teste != 0)
        {
            Imprime(final);
        }
        else
        {
            Imprime(novaArvore);
        }
    }

    return 0;
}
