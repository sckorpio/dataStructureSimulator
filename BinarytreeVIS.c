#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) (((a)>(b))?(a):(b))

struct TreeNode
{
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
    struct TreeNode *parent;
    char S;
};

typedef struct TreeNode *PtrtoNode;
typedef PtrtoNode TNODE;
typedef PtrtoNode POS;

struct TreeData
{
   TNODE Root;
   int size;
   int height;
};

typedef struct TreeData *PtrtoTree;
typedef PtrtoTree TREE;


TREE CreateTree()
{
    TREE T;
    T=(TREE)(malloc(sizeof(struct TreeData)));
      if(T!=NULL)
      {
          T->Root=NULL;
          T->size=0;
      }

      return (T);
}


void AddLeft(int X,POS P,TREE T)
{
    if(P->left==NULL)
    {
        TNODE temp=(TNODE)(malloc(sizeof(struct TreeNode)));
        temp->left=NULL;
        temp->right=NULL;
        temp->parent=P;
        temp->value=X;
        temp->S='L';

        P->left=temp;
    }
}


void AddRight(int X,POS P,TREE T)
{
    if(P->right==NULL)
    {
        TNODE temp=(TNODE)(malloc(sizeof(struct TreeNode)));
        temp->left=NULL;
        temp->right=NULL;
        temp->parent=P;
        temp->value=X;
        temp->S='R';

        P->right=temp;
    }
}


POS Find(int X,TNODE T)
{
    TNODE L,R;
    if(T!=NULL)
    {
        if(T->value==X)
            return(T);

        L=Find(X,T->left);
          if(L!=NULL)
            return(L);

       R=Find(X,T->right);
       return(R);
    }

    else
        return(NULL);
}

void PrintNodes(POS P)
{
    if(P!=NULL)
    {
    printf("%d ",P->value);
    PrintNodes(P->left);
    PrintNodes(P->right);
    }
}

void PrintTree(TREE T)
{
    PrintNodes(T->Root);
}


void MakeEmpty(POS P)
{
    if(P!=NULL)
    {
        MakeEmpty(P->left);
        MakeEmpty(P->right);
        free(P);
    }
}


void Cut(POS P,TREE T)
{
    if(P->S=='L')
        P->parent->left=NULL;
    else
        P->parent->right=NULL;

    MakeEmpty(P);

}


//########################################################################################################




void Fill(int TA[],int i,POS P)
{
    if(P!=NULL)
    {

      TA[i]=P->value;
      Fill(TA,2*i+1,P->left);
      Fill(TA,2*i+2,P->right);

    }

}


void UpdateTaree(int TA[],POS P)
{   int i;
    for(i=0;i<100;i++)
        TA[i]=-99;
    Fill(TA,0,P);
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



























void PrintMenu()
{
    printf("\n--------------------\n");
    printf("Press 1 to Add\n");
    printf("Press 2 to Find\n");
    printf("Press 3 to Cut Branch\n");
    printf("Press 4 to Make Empty\n");
    printf("\nPress 0 to EXIT\n");
    printf("-----------------------\n");
}


int main()
{

     int Tarre[100];  int HT;
    int CN[100];

    TREE T;    int i;

    T=CreateTree();

   // printf("%u\n",L);

   for(i=0;i<100;i++)
        Tarre[i]=-99;

    int X,Y;
    char C,S;

    do
    {
        system("cls");

        printf("\n__________________________________________  B I N A R Y  T R E E   _________________________________________________\n");

       DrawTree(Tarre,CN,HT+1);

       // printf("Size=%d\n",T->size);

        //PrintTree(T);
        PrintMenu();

        C=getch();

       switch(C)
       {
           case '1': {
                        printf("\nEnter number to Add\n");
                            scanf("%d",&X);

                        if(T->Root==NULL)
                        {
                            TNODE temp=(TNODE)malloc(sizeof(struct TreeNode));
                            if(temp!=NULL)
                            {
                            temp->left=NULL;
                            temp->right=NULL;
                            temp->parent=NULL;
                            temp->value=X;
                            }

                            T->Root=temp;

                          }

                          else
                          {
                              printf("Enter the number after which you wanna add..\n");
                              scanf("%d",&Y);

                              POS P=Find(Y,T->Root);
                              if(P!=NULL)
                              {
                                  printf("Press L to add in left\nPress R to add in Right\n");
                                  S=getche();

                                  if(S=='L')
                                    AddLeft(X,P,T);

                                  else if(S=='R')
                                    AddRight(X,P,T);
                              }
                          }
                       // HT=T->height;
                       HT=3;
                        UpdateTaree(Tarre,T->Root);
                        MakeCN(CN,CTR,HT);

                        printf("ht- %d\n",HT);

                       } break;

           case '2':  {

                        printf("\n Enter no. to Find\n");
                        scanf("%d",&X);
                        POS P=Find(X,T->Root);

                        if(P!=NULL)
                        {
                            printf("Yess  %u\n",P);
                        }

                       }break;

           case '3':  {
                            printf("Enter the number you wanna cut..\n");
                            scanf("%d",&X);

                             POS P=Find(X,T->Root);

                        if(P!=NULL)
                        {
                            Cut(P,T);
                        }

                      //   UpdateTaree(Tarre,T);
                       //   MakeCN(CN,CTR,HT);

                       }  break;


           case '4': { MakeEmpty(T->Root);
                        T->Root=NULL;
                        T->size=0;

                      //  UpdateTaree(Tarre,T);
                      //   MakeCN(CN,CTR,HT);

                       } break;


            case '0':  {

                          printf("BYEEEEEEE\n");
                          exit(0);
                       }

       }

      //system("cls");


       /* for(j=0;j<N;j++)
        printf("%d  ",Tarre[j]);
        printf("\n");
        printf("\n======\n");
        for(j=0;j<N;j++)
        printf("%d  ",CN[j]);
       */
   // printf("\n__________________________________________  B I N A R Y  T R E E   _________________________________________________\n");

     //  DrawTree(Tarre,CN,HT+1);

    }while(C!='0');

    return 0;

}
