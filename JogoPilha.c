#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define tamMax 4

struct pilha{
    int Elem[tamMax];
    int topo;
};

typedef struct pilha Pilha;

void InicializaPilha(Pilha *P){
    P->topo = -1;
}

int PilhaVazia(Pilha *P){
    return (P->topo == -1);
}

int PilhaCheia(Pilha *P){
    return (P->topo == tamMax-1);

}

void Empilha(Pilha *P,int x){
    if (PilhaCheia(P) != 1)
    {
        P->topo++;
        P->Elem[P->topo] = x;
    }
    else
    {
        printf("Erro: PILHA CHEIA\n");
    }
}

void Desempilha(Pilha *P,int *x){
    if (PilhaVazia(P) != 1)
    {
        *x = P->Elem[P->topo];
        P->topo--;
    }
    else
    {
        printf("Erro: PILHA VAZIA\n");
        *x = -1;
    }
}

int ElementoDoTopo(Pilha *P){
    if (PilhaVazia(P) == 0)
    {
        return P->Elem[P->topo];
    }
    else
    {
        printf("Erro: PILHA VAZIA\n");
    }
}

//Função para mostrar uma pilha
void MostraPilha(Pilha *P)
{
    int i;
    if (PilhaVazia(P) == 1)
    {
        printf("Vazia\n");
    }
    else
    {
        for(i=0;i<P->topo+1;i++)
        {
            printf("%d ",P->Elem[i]);
        }
        printf("\n");
    }
}

//Função para adicionar um elemento à outra pilha
int AddP(Pilha *P,int x){
    if(PilhaCheia(P) == 0)
    {
        if((PilhaVazia(P) == 1) || (ElementoDoTopo(P) == x))
        {
            Empilha(P,x);
            return 0;
        }
        else
        {
            printf("\nElemento do topo da Pilha selecionada diferente do elemento desempilhado!");
            printf("\nEscolha Outra pilha!\n\n");
            return 1;
        }
    }
    else
    {
        printf("\nPilha Cheia!, Escolha outra\n\n");
        return 1;
    }
}

//Função que recebe duas pilhas como argumentos e troca os elementos delas aleatóriamente
void ramdomizarPilhas(Pilha *P,Pilha *X)
{
    int j,i,x,temp;
    srand(time(NULL));
 
    for (x = 0; x < 127; x++)
    {   
        i = rand() % 4;
        j = rand() % 4;
        temp = P->Elem[i];
        P->Elem[i] = X->Elem[j];
        X->Elem[j] = temp;
    }
}

//Função que verifica se os 4 elementos da Pilha dada são iguais
int VerificaPilha(Pilha *P)
{
    int i,c = 0;
    if(PilhaCheia(P))
    {
        for(i=0;i<4;i++)
        {
            if(P->Elem[i] == P->Elem[P->topo])
            {
                c++;
            }
        }
    }
    return c;
}


int main(){
    printf("***********************************************\n");
    printf("* Trabalho 2- Jogo de gerenciamento de pilhas *\n");
    printf("* Nome: Davi Yoshio Toyokawa RA:125066        *\n");
    printf("***********************************************\n");
    printf("\n\n");

    int n,i,x,p1,p2,aux,temp,escolha,Sair,count;
    Sair = count = 0;

    printf("O jogo consiste em organizar os numeros dentro das pilhas\n");
    printf("Exemplo: n = 3:\nPilha 1 = 2 2 2 2\nPilha 2 = 3 3 3 3\nPilha 3 = 1 1 1 1\n");
    printf("Escolha quantos numeros diferentes para distribuir nas pilhas: ");
    scanf("%d",&n);             //Pede para o usuário escolher com quantas pilhas vai querer jogar 


    Pilha P[n+2];               //Cria n+2 Pilhas      

    for(i=0;i<n+2;i++)          //Inicializa n+2 Pilhas
    {
        InicializaPilha(&P[i]);
    }

    for(i=0;i<n;i++)            //Preenche n pilhas para ramdomizar posteriormente
    {
        Empilha(&P[i],i+1);
        Empilha(&P[i],i+1);
        Empilha(&P[i],i+1);
        Empilha(&P[i],i+1);
    }

    for (i = 0; i < n-1; i++)       //Randomiza n pilhas
    {
        ramdomizarPilhas(&P[i],&P[i+1]);  
    }
    
    do{                             //Opções do jogo(Empilhar, mostrar as pilhas, sair)
        printf("\n1.Desempilhar//Empilhar\n2.MostrarPilhas\n3.Sair/Terminar\n");
        printf("\nO que quer fazer?: ");
        scanf("%d",&escolha);
        switch (escolha)
        {
        case 1:
            do                    //Enquanto o usuário digitar uma pilha menor que 1 ou maior que n+2
            {
                printf("Numero da Pilha para Desempilhar: ");
                scanf("%d",&p1);                                //Escolher qual pilha quer desempilhar
                if((p1 <= 0) || (p1 > n+2))
                {
                    printf("\nPilha Invalida escolha outra\n\n");
                }
            }while((p1 <= 0) || (p1 > n+2));  
            Desempilha(&P[p1-1],&temp);
            if(temp == -1)                                      //Caso a pilha escolhida for vazia
            {
                break;
            }
            else
            {
                do                                              //Enquanto não for possível colocar na pilha escolhida 
                {
                    printf("Numero desempilhado: %d\n",temp);
                    do
                    {
                        printf("Quer colocar em qual pilha?: ");
                        scanf("%d",&p2);
                    }while ((p2 <= 0) || (p2 > n+2));
                    
                    if(p2 == p1)                                //Caso a pilha escolhida for a mesma que desempilhou
                    {
                        Empilha(&P[p2-1],temp);
                        printf("\n%d foi empilhado na pilha %d! \n",temp,p2);
                        break;
                    }

                    aux = AddP(&P[p2-1],temp);                  //Tenta adicionar o numero na pilha desejada
                    if(aux == 0)                                
                    {
                        printf("\n%d foi empilhado na pilha %d! \n",temp,p2);
                    }
                }while (aux == 1);
            }
            break;
        case 2:
            printf("Pilhas: \n");
            for(i=0;i<n+2;i++){                                 //Mostra todas as pilhas
                printf("Pilha %d: ",i+1);
                MostraPilha(&P[i]);
            }
            break;
        case 3:
            printf("Tem certeza?(0 = Nao // 1 = Sim): ");       //Termina o jogo
            scanf("%d",&Sair);
            break;
        default:
            printf("ERRO: Nao tem esse numero nas escolhas");
        }
    }while(Sair != 1);

    printf("Resultados: \n");
    for(i=0;i<n+2;i++)                              //Verifica quantas pilhas o usuário acertou
    {
        if(VerificaPilha(&P[i]) == 4)
        {
            count++;
        }
    }

    if(count == n)                                  //Se acertou todas as pilhas
    {
        printf("**Parabens, completou o jogo**\n");
    }
    else
    {
        printf("Tente outra vez!\n");
        printf("Numero de pilhas certas: %d\n",count);
    }
    printf("\nFim de jogo\n");
    system("pause");
    return 0;
}