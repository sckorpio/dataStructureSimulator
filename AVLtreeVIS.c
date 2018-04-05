#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) (((a)>(b))?(a):(b))

struct AVLnode
{
    int value;
    struct AVLnode *Left;
    struct AVLnode *Right;
    int H;
};

typedef struct AVLnode *PtrtoAVLnode;

typedef PtrtoAVLnode Pos;
typedef PtrtoAVLnode AVLtree;


int Height(AVLtree P)
{
    if(P==NULL)
        return -1;

    else
        return(P->H);
}

void UpdateHeight(Pos K)
{
     K->H=MAX(Height(K->Left),Height(K->Right))+1;


}

int getBalance(Pos P)
{
    if (P==NULL)
        return 0;
    return Height(P->Left)-Height(P->Right);
}


AVLtree SingleRotateWithLeft(Pos K2)
{
    Pos K1;

    K1=K2->Left;
    K2->Left=K1->Right;
    K1->Right=K2;

   UpdateHeight(K2);

   UpdateHeight(K1);

   return K1;
}


AVLtree SingleRotateWithRight(Pos K2)
{
    Pos K1;

    K1=K2->Right;
    K2->Right=K1->Left;
    K1->Left=K2;

   UpdateHeight(K2);

   UpdateHeight(K1);

   return K1;


}

AVLtree DoubleRotateWithLeft(Pos K3)
{
    K3->Left=SingleRotateWithRight(K3->Left);

    return(SingleRotateWithLeft(K3));
}

AVLtree DoubleRotateWithRight(Pos K3)
{
    K3->Right=SingleRotateWithLeft(K3->Right);

    return (SingleRotateWithRight(K3));
}


AVLtree AVLInsert(int X,AVLtree T)
{
    if(T==NULL)
    {

        T=(AVLtree)(malloc(sizeof(struct AVLnode)));

        if(T!=NULL)
        {
            T->value=X;
            T->Left=NULL;
            T->Right=NULL;
            T->H=0;


        }
    }



        else if(X<T->value)
        {
            T->Left=AVLInsert(X,T->Left);

            if(getBalance(T)>=2)
            {
                if(X<((T->Left)->value))
                    T=SingleRotateWithLeft(T);
                else
                    T=DoubleRotateWithLeft(T);
            }
        }


        else if(X>T->value)
        {
            T->Right=AVLInsert(X,T->Right);

            if(getBalance(T)<=-2)
            {
                if(X>((T->Right)->value))
                    T=SingleRotateWithRight(T);
                else
                    T=DoubleRotateWithRight(T);
            }
        }




    UpdateHeight(T);

    return T;
}



Pos minValueNode(AVLtree T)
{
   while(T->Left!=NULL)
    T=T->Left;
  return T;
}











AVLtree Delete(int X,AVLtree T)
{
    Pos temp;

     if(T==NULL)
     return T;

     if(X<T->value)
     T->Left=Delete(X,T->Left);

    else if(X>T->value)
    T->Right=Delete(X,T->Right);

   else
    {
         if((T->Left==NULL)||(T->Right==NULL))
         {
            temp=T->Left?T->Left:T->Right;

            if(temp==NULL)
            {
                temp=T;
                T=NULL;
             }

             else
              {
                 *T=*temp;
               }

             free(temp);
          }



        else
           {
              temp=minValueNode(T->Right);

              T->value=temp->value;

               T->Right=Delete(temp->value,T->Right);
            }


      }


       if(T==NULL)
      return NULL;


    UpdateHeight(T);




           if(getBalance(T)>=2)
            {
                if(getBalance(T->Left)>=1)
                    T=SingleRotateWithLeft(T);
                else
                    T=DoubleRotateWithLeft(T);
            }


            else if(getBalance(T)<=-2)
            {
                if(getBalance(T->Right)<=-1)
                    T=SingleRotateWithRight(T);
                else
                    T=DoubleRotateWithRight(T);
            }

    return T;

}


void PrintNode(Pos P)
{
    printf("P--- %u\n left-- %u \n right-- %u \n height-- %d\n--------\n",P,P->Left,P->Right,P->H);
}

void PrintTree(AVLtree T)
{
    if(T!=NULL)
    {
    printf("%d ",T->value);
    PrintTree(T->Left);
    PrintTree(T->Right);
    }
}

void Fill(int TA[],int i,Pos P)
{
    if(P!=NULL)
    {

      TA[i]=P->value;
      Fill(TA,2*i+1,P->Left);
      Fill(TA,2*i+2,P->Right);

    }

}


void UpdateTaree(int TA[],AVLtree T)
{   int i;
    for(i=0;i<100;i++)
        TA[i]=-99;
    Fill(TA,0,T);
}


int MAX=130;
int CTR=70;

void FillCN(int Crr[],int X,int i,int p)
{
    int Pr;
    if(p>=0)
    {
    Crr[i]=X;
    Pr=pow(2,p);
    FillCN(Crr,X-Pr,2*i+1,p-1);
    FillCN(Crr,X+Pr,2*i+2,p-1);
    }
}

void MakeCN(int Crr[],int X,int h)
{
    int i;
    for(i=0;i<100;i++)
        Crr[i]=0;
    FillCN(Crr,X,0,h);
}




void DrawTree(int TAR[],int CN[],int H)
{
    int l,h,e,c,k,i;
    h=H; e=1;

    printf("\n\n\n");
    for(i=0;i<MAX;i++)
    {
        if(i==CTR)
            printf("%d",TAR[0]);
        else
            printf(" ");
    }

    printf("\n");


    while(h--)
    {
        l=(int)pow(2,e)-1;
          k=(int)pow(2,h)-1;

      if(k==0)
        break;

        for(;k>=0;k--)
        {
            c=l;

            for(i=0;i<=MAX;i++)
            {
                if((c%2==0)&&(i==CN[c]-k))
                {
                    if(TAR[c]!=-99)
                    {
                        if(k==0)
                           {
                               printf("%d",TAR[c]);

                               if(TAR[c]>9||TAR[c]<0)  i++;
                           }
                        else
                            printf("\\");
                    }
                    else
                        printf(" ");
                    c++;
                }

                else if((c%2!=0)&&(i==CN[c]+k))
                {
                    if(TAR[c]!=-99)
                    {
                        if(k==0)
                           {
                               printf("%d",TAR[c]);

                               if(TAR[c]>9||TAR[c]<0)  i++;
                           }
                        else
                            printf("/");
                    }
                    else
                        printf(" ");
                    c++;
                }

                else
                    printf(" ");
            }

            printf("\n");
        }

        e++;
    }

}

int main()
{
    int num;
    int i,j;
    int N;
    int Tarre[100];  int HT;
    int CN[100];
    int choice;


   // printf("Enter the maximum numb AVL TREE---\n");
   // scanf("%d",&N);

    AVLtree TR;

    TR=NULL;

    for(i=0;i<100;i++)
        Tarre[i]=-99;

   // printf("TR--%u  \n",TR);
   //printf("Enter the first Element..(<100)\n");

    //for(i=1;i<=N;i++)
    do
    {
        printf("-------------------------------\n");
        printf("Press 1 to Add element..\n");
        printf("Press 0 to Delete element..\n");
        printf("Press -1 to EXIT...\n");
        printf("-------------------------------\n");

        scanf("%d",&choice);

        if(choice==1)
        {
        printf("\nEnter theElement to insert..\n");
        scanf("%d",&num);

        TR=AVLInsert(num,TR);
        HT=TR->H;
       /*  printf("\n--------------------\n");
        printf("TR--%u  Height-- %d\n",TR,HT);
        PrintTree(TR);
        printf("\n--------------------\n");
       */
       UpdateTaree(Tarre,TR);
       MakeCN(CN,CTR,HT);

        }


        else if(choice==0)
        {
            printf("Enter the element to delete\n");
            scanf("%d",&num);

        TR=Delete(num,TR);
        HT=TR->H;
       /*  printf("\n--------------------\n");
        printf("TR--%u  Height-- %d\n",TR,HT);
        PrintTree(TR);
        printf("\n--------------------\n");
       */
       UpdateTaree(Tarre,TR);
       MakeCN(CN,CTR,HT);
        }

        else
            break;

       system("cls");


       /* for(j=0;j<N;j++)
        printf("%d  ",Tarre[j]);
        printf("\n");
        printf("\n======\n");
        for(j=0;j<N;j++)
        printf("%d  ",CN[j]);
       */
        printf("\n__________________________________________  A V L   T R E E   _________________________________________________\n");

        DrawTree(Tarre,CN,HT+1);

       // printf("\n\n\nEnter next Element..(<100)\n");
    }while(choice>=0);

    return 0;
}
