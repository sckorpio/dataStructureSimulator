#include <stdio.h>
#include <stdlib.h>
#include <windows.h>



struct NODE
{
    int value;
    struct NODE *next;
    struct NODE *prev;
};

typedef struct NODE *PointertoNode;
typedef PointertoNode POS;


struct ListData
{
    struct NODE *HEAD;
    struct NODE *LAST;
    long int size;
};


typedef struct ListData *PointertoList;
typedef PointertoList LIST;



LIST CreateList()
{
    LIST temp;
    temp=(LIST)malloc(sizeof(struct ListData));
      if(temp==NULL)
        printf("Out of Space\n");
      else
         {
          temp->HEAD=NULL;
          temp->LAST=NULL;
          temp->size=0;
         }
   return temp;
}


void ReverseList(LIST L)
{
    POS A,B;  unsigned int j=L->size/2;  int temp;

    A=L->HEAD;
    B=L->LAST;

    while(j--)
    {
       temp=A->value;
       A->value=B->value;
       B->value=temp;

       A=A->next;
       B=B->prev;
    }

}

int IsEmpty(LIST L)
{
    return (L->HEAD==NULL);
}


int IsLast(POS P,LIST L)
{
    return (P==L->LAST);
}

POS Find(int X,LIST L)
{
    POS P;
    P=L->HEAD;
      while((P!=NULL)&&(P->value!=X))
        P=P->next;
      return P;
}

void Deletelist(LIST L)
{
    POS temp,P;
    temp=L->HEAD;

      while(temp->next!=NULL)
      {
          P=temp;
          temp=temp->next;
          free(P);

      }
        free(temp);

        L->HEAD=NULL;
        L->LAST=NULL;
        L->size=0;

}

void Delete(POS P,LIST L)
{
       if(P==L->HEAD)
       {
           L->HEAD=P->next;
           L->HEAD->prev=NULL;
       }

       else if(P==L->LAST)
       {
           L->LAST=P->prev;
           L->LAST->next=NULL;
       }

       else
       {
          P->prev->next=P->next;
          P->next->prev=P->prev;
       }
          free(P);
          (L->size)--;

}


void Insert(int X,LIST L,POS P)
{
    POS temp;
    temp=(POS)malloc(sizeof(struct NODE));
      if(temp==NULL)
        printf("Out of Space\n");
      else
      {
          temp->value=X;

          P->next->prev=temp;
          temp->next=P->next;
          temp->prev=P;
          P->next=temp;

          (L->size)++;
      }
}



void Add(int X,LIST L)
{
   POS temp;
    temp=(POS)malloc(sizeof(struct NODE));
      if(temp==NULL)
        printf("Out of Space\n");
      else
      {
          temp->value=X;
          temp->next=NULL;

          if(IsEmpty(L))
          {
              temp->prev=NULL;
             L->HEAD=temp;
             L->LAST=temp;
          }

          else
          {
          temp->prev=L->LAST;
          L->LAST->next=temp;

          L->LAST=temp;
          }
          (L->size)++;
      }
}


void PrintList(LIST L)
{
    POS P;
     P=L->HEAD;



     printf("\nL I S T\n-------\n");
     printf("#--->  ");

     while(P!=NULL)
     {
         printf("%d ",(P->value));
         P=(P->next);
     }

     printf("\n-------\n");
}

void PrintNode(POS P)
{
    printf("\n|-------------------|\n");
    printf("|  I D--  %10u|\n",P);
    printf("|-------------------|\n");
    printf("| VALUE-- %10d|\n",P->value);
    printf("| PREV--- %10u|\n",P->prev);
    printf("| NEXT--- %10u|\n",P->next);
    printf("|-------------------|\n\n");

}

//##########################################################################################################################
























































































void PrintMenu()
{
    printf("\n--------------------\n");
    printf("Press 1 to ADD\n");
    printf("Press 2 to Insert\n");
    printf("Press 3 to Find\n");
    printf("Press 4 to Reverse\n");
    printf("Press 5 to Delete\n");
    printf("Press 6 to Delete List\n");
    printf("\nPress 0 to EXIT\n");
    printf("-----------------------\n");
}

int main()
{
    LIST L;

    L=CreateList();


   // printf("%u\n",L);

    int i;   int X,Y;
    POS P;   char C;

    do
    {
        system("cls");

         printf("HEAD-%u\n",L->HEAD);
    printf("LAST-%u\n",L->LAST);
    printf("size=%ld\n",L->size);


        PrintList(L);
        PrintMenu();

        C=getch();

       switch(C)
       {
           case '1': {
                      printf("\n Enter no. to Add\n");
                       scanf("%d",&X);
                       Add(X,L);
                        } break;

           case '2':  {
                       printf("\n Enter the number after you want to Insert\n");
                       scanf("%d",&Y);
                       P=Find(Y,L);
                       if(P==L->LAST)
                       {
                        printf("\n Enter no. to Add\n");
                        scanf("%d",&X);
                        Add(X,L);
                       }

                       else if((P!=L->LAST)&&(P!=NULL))
                       {
                        printf("\n Enter no. to Add\n");
                        scanf("%d",&X);
                        Insert(X,L,P);
                       }


                       else
                        {
                          printf("%d Not FOUND!!!",Y);
                          Sleep(400);
                        }
                   }  break;

           case '3':  {    printf("\n Enter no. to Find\n");
                       scanf("%d",&X);
                       P=Find(X,L);
                         if(P!=NULL)
                       {
                           PrintNode(P);
                           getche();

                       }

                       else
                          printf("%d Not FOUND!!!",X);

                        Sleep(500);
                   }  break;



            case '4':  {
                            ReverseList(L);

                            }   break;


            case '5':  {
                        printf("\n Enter no. to Delete\n");
                       scanf("%d",&X);
                       P=Find(X,L);
                         if(P!=NULL)
                       {
                           Delete(P,L);
                           printf("%d DELETED!!!",X);

                       }

                       else
                          printf("%d Not FOUND!!!",X);

                        Sleep(500);
                   }  break;



            case '6':
                      {
                          Deletelist(L);
                      } break;





       }



    }while(C!='0');

   printf("\n------------BYE--------");
   Sleep(1000);


  return 0;
}






