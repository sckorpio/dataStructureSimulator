#include <stdio.h>
#include <stdlib.h>

struct SNODE
{
    int value;
    struct SNODE *below;
};

typedef struct SNODE *PtrtoSNode;
typedef  PtrtoSNode STACK;
typedef  PtrtoSNode POS;

STACK CreateStack()
{
    STACK S;
    S=(STACK)malloc(sizeof(struct SNODE));

    if(S==NULL)
        printf("ERROR...Out of Memory\n");

    else
    {
        S->value=-99;
        S->below=NULL;
    }

    return(S);
}


int IsEmpty(STACK S)
{
    return (S->below==NULL);
}

void MakeEmpty(STACK S)
{
    POS P,temp;
    P=S->below;

       while(P!=NULL)
       {
           temp=P->below;
           free(P);
           P=temp;
       }

       S->below=NULL;
}

void DisposeStack(STACK S)
{
    MakeEmpty(S);
    free(S);
}

int Top(STACK S)
{
    if(!(IsEmpty(S)))
    return(S->below->value);

    else
        return -999;
}


void Pop(STACK S)
{
    POS temp;

    if(!IsEmpty(S))
    {temp=S->below;
    S->below=((S->below)->below);
    free(temp);
    }
}


void Push(int X,STACK S)
{
    POS temp;
    temp=(POS)malloc(sizeof(struct SNODE));

       if(temp==NULL)
        printf("ERROR...Out of Memory\n");

       else
       {
           temp->value=X;
           temp->below=S->below;
           S->below=temp;
       }
}

void PrintStack(STACK S)
{
    POS temp;
    temp=S->below;

    printf("###########\n");
    while(temp!=NULL)
    {
        printf("%5d\n",(temp->value));
        temp=temp->below;
    }
    printf("-----------\n\n");
}




//#######################################################################################################3












































void PrintMenu()
{
    printf("\n--------------------\n");
    printf("Press 1 to see TOP\n");
    printf("Press 2 to PUSH\n");
    printf("Press 3 to POP\n");
    printf("Press 4 to Empty Stack\n");
    printf("\nPress 0 to EXIT\n");
    printf("-----------------------\n");
}

int main()
{
    STACK S;

    S=CreateStack();

   // printf("%u\n",L);

    int i;   int X,Y;
    POS P;   char C;

    do
    {
        system("cls");

        PrintStack(S);
        PrintMenu();

        C=getch();

       switch(C)
       {
           case '1': {
                         X=Top(S);
                         printf("On TOP== %d\n",X);
                        } break;

           case '2':  {

                        printf("\n Enter no. to PUSH\n");
                        scanf("%d",&X);
                        Push(X,S);
                       }break;

           case '3':  {
                         X=Top(S);

                         Pop(S);
                         system("cls");
                         PrintStack(S);

                          printf("%d POPED\n",X);

                          getche();

                       }  break;


           case '4':  MakeEmpty(S);  break;


            case '0':  {

                          printf("BYEEEEEEE\n");
                          exit(0);
                       }

       }

    }while(C!='0');

    return 0;

}
