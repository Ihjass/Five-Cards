#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct node
{
    int index;
    char suit;
    struct node* next;
};

typedef struct node* nodeptr;
nodeptr list=NULL;
nodeptr addeck;
nodeptr p1=NULL;
nodeptr p2=NULL;

int onepoints=0;
int twopoints=0;

static int MIN=1;
static int MAX=53;

char onename[25];
char twoname[25];

int getssuit();
char getsuit();

nodeptr choose(nodeptr,int);
nodeptr insert(nodeptr p,nodeptr attach);
nodeptr gamecard(nodeptr p);
void declare(nodeptr x);

nodeptr getnode()
{
    nodeptr q;
    q=malloc(sizeof(struct node));
    return q;
}

void freenode(nodeptr p)
{
    free(p);
}

void deckinitialise()      //call using list
{
    int i,j;
    for(j=0;j<4;j++)
    {
        nodeptr temp;
        for(i=1;i<=13;i++)
        {
            temp=getnode();
            if(list==NULL)
            {
                list=temp;
                temp->next=NULL;
                if(i==1)
                    temp->index=65;
                else
                    temp->index=i;
                temp->suit=getsuit(j);

            }

            else
            {
                if(i>10)
                {
                    temp->next=list;
                    list=temp;
                    temp->index=getssuit();
                    temp->suit=getsuit(j);

                }
                else
                {
                    temp->next=list;
                    list=temp;
                    if(i==1)
                        temp->index=65;
                    else
                        temp->index=i;
                    temp->suit=getsuit(j);

                }
            }
        }
    }
    nodeptr temp1;
    temp1=getnode();
    temp1->index=88;
    temp1->suit='X';
    temp1->next=list;
    list=temp1;

}

void deckremodel()
{
    int max=53,min=1;
    int select;
    int i=1;
    srand(time(NULL));
    while(i<=53)
    {
        select=rand()%((max--)-min+1)+min;
        list=insert(list,choose(list,select));

        i++;
    }
}

void display(nodeptr temp)
{

    int ctr=0;
    while(temp!=NULL)
    {
        if(temp->index>10)
        {
            printf("%d\t%c\t",++ctr,temp->index);
            wtdisplay(temp->suit);
        }
        else
        {
            printf("%d\t%d\t",++ctr,temp->index);
            wtdisplay(temp->suit);
        }
        temp=temp->next;
    }
}

void wtdisplay(char get)
{
    if(get=='C')
        printf("CLUB\n");
    else if(get=='D')
        printf("DIAMOND\n");
    else if(get=='H')
        printf("HEART\n");
    else if(get=='S')
        printf("SPADE\n");
    else if(get=='X')
        printf("JOKER\n");
}

int getssuit()
{
    static int var=0;
    static int ctr=0;
    if(var>2)
    {
        ctr=0;
        var=0;
    }
    ctr++;
    if(ctr==1)
    {
        ++var;
        return 74;
    }
    if(ctr==2)
     {
        ++var;
        return 81;
     }
    if(ctr==3)
    {
        ++var;
        return 75;
    }
}

char getsuit(int get)
{
    if(get==0)
        return 'C';
    else if(get==1)
        return 'D';
    else if(get==2)
        return 'H';
    else if(get==3)
        return 'S';

    /*char suit[4][10]={"CLUB","DIAMOND","HEART","SPADE"};
    return suit[get];*/
}

nodeptr choose(nodeptr p,int card)      //call using list
{
    int i=0;
    nodeptr temp=p,q;
    if(list==NULL)
        printf("Deck is Empty\n");
    if(card==1)
    {
        list=temp->next;
        temp->next=NULL;
        return temp;
    }
    else
    {
        while(i<card)
        {
            q=temp;
            if(i!=0)
                temp=temp->next;
            i++;
        }
        q->next=temp->next;
        temp->next=NULL;
        return temp;
    }
}

nodeptr insert(nodeptr p,nodeptr attach)
{
    nodeptr temp;
    if(p==NULL||attach==NULL)
    {

        p=attach;
        attach->next=NULL;
        return p;
    }
    else
    {
        temp=p;
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=attach;
        attach->next=NULL;
        return p;
    }
}

void playerassign(nodeptr one,nodeptr two)  //call using p1 and p2  //it should return the value of one to p1 so that p1 can get updated
{
    static int control=1;
    int i=1;
    int player=1;
    int card;

        while(i<=10)
        {
            srand(time(NULL));
            card=rand()%((MAX--)-MIN+1)+MIN;

            if(i%2==0)
            {
                p1=insert(p1,choose(list,card));
            }
            else
            {
                p2=insert(p2,choose(list,card));
            }
            i++;
        }
}

void lifeassign(nodeptr one,nodeptr two)
{
 //   display(list);

    int control;
    int i=1;
    int max=48;
    int min=1;
    int card;

    if(one==p1)
    {
        control=1;
        p1=NULL;
    }
    else
    {
        control=2;
        p2=NULL;
    }
            while(i<=5)
            {
                srand(time(NULL));
                card=rand()%((max--)-min+1)+min;
                if(control==1)
                {
                    p1=insert(p1,choose(list,card));
                }
                else
                {
                    p2=insert(p2,choose(list,card));
                }
                i++;
            }
}

nodeptr delcard(nodeptr p)
{
    nodeptr q,temp=p;
    int sacrifice;
    int i=0;
    display(p);
    printf("\nEnter the Card position You Want To Sacrifice\n\n");
    scanf("%d",&sacrifice);
    printf("\n");
    while(1)
    {
        if(sacrifice>=1&&sacrifice<=5)
            break;
        else
        {
            printf("\nEnter A Valid Posotion\n");
            scanf("%d",&sacrifice);
        }
    }
    while(i<sacrifice)
    {
        q=temp;
        if(i!=0)
            temp=temp->next;
        i++;
    }

    if(temp==p)
    {
        p=p->next;
    }
    else if(temp->next==NULL)
    {
        q->next=NULL;
    }
    else
    {
        q->next=temp->next;
    }
    readd(list,temp);
    return p;
}

void readd(nodeptr p,nodeptr atlast)
{
    int i=1;
    nodeptr temp=p;
    if(p==NULL)
        printf("\nCard Cannot Be Added\n");
    else
    {
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=atlast;
        atlast->next=NULL;
    }
}

void start()
{
    int cont;
    int loopctr=0;
    int turn=0;
    int get;
    int sum1,sum2;
    int ch;
    int add;
    nodeptr want;
    for(loopctr=1;;loopctr++)
    {
        if(loopctr%5==1&&loopctr!=1)
        {
            static int round;
            printf("\n\n\t\tEND OF ROUND %d\n\n",++round);
          //  printf("\n\n%s :- %d\n\n %s :- %d\n\n",onename,getsum(p1),twoname,getsum(p2));
        }

        if(turn%2==0)
        {
            printf("\n%s TURN\n\n",onename);
            display(p1);
            printf("\nTake A Card From Deck Press (1) OR Press (2)\n");
            scanf("%d",&get);
            printf("\n");
            if(get==1)
            {
                want=gamecard(list);
                p1=delcard(p1);
                printf("\n\n");
                printf("CARD FROM DECK \n\n\t");
                display(want);
                insert(p1,want);
                printf("\nDeck After Adding\n\n");
                display(p1);
            }
            else if(get!=1)
            {
                printf("\n\n\tLIST REMAIN SAME \n\n");
                if(turn==0)
                {
                 //   printf("\nCHECKING RE-ADD\n\n");
                 //   display(list);
                }
            }
            sum1=getsum(p1);

                printf("\nCURRENT VALUE OF %s: %d\n",onename,sum1);
            if(turn>=2)
            {
                printf("\nWould You Like To Declare %s??\nYou Have %d Points\nPress (1) OR (2)\n",onename,getsum(p1));
                scanf("%d",&ch);
                if(ch==1)
                    declare(p1);
            }
        }


        if(turn%2!=0)
        {
            printf("\n%s TURN\n\n",twoname);
            display(p2);
            printf("\nTake A Card From The Deck Press (1) OR Press (2)\n");
            scanf("%d",&get);
            printf("\n");
            if(get==1)
            {
                want=gamecard(list);
                p2=delcard(p2);
                printf("\n\n");
                printf("CARD FROM DECK \n\n\t");
                display(want);
                insert(p2,want);
                printf("\nDeck After Adding\n\n");
                display(p2);
            }
            else if(get!=1)
            {
                printf("\n\n\tLIST REMAIN SAME \n\n");
                if(turn==1)
                {
                   // printf("\n\nCHECKING READD\n\n");
                   // display(list);
                }
            }
            sum2=getsum(p2);
                printf("\nCURRENT VALUE OF %s: %d",twoname,sum2);

            if(turn>=2)
            {
                printf("\nDo You Want To Declare %s??\nYou Have %d Points\nPress (1) OR (2)\n",twoname,getsum(p2));
                scanf("%d",&ch);
                if(ch==1)
                    declare(p2);
            }
        }

        printf("\n\n\n\n\t\t  %s : %d \n\n\t\t  %s : %d\n\n",onename,onepoints,twoname,twopoints);
        printf("\nContinue ?? Press Any No\n");
        scanf("%d",&cont);
        system("cls");
        if(twopoints>=200)
        {
            printf("\n\n\t\t%s WINS\n\n",onename);
            break;
        }
        if(onepoints>=200)
        {
            printf("\n\n\t\t%s WINS\n\n",twoname);
            break;
        }
        turn++;
    }
    printf("\n\n\t\tGAME OVER :)\n\n");
}

nodeptr gamecard(nodeptr p)    //Similar to pop of stack using linked list
{
    nodeptr temp;

    if(p==NULL)
        printf("Deck is Empty\n");
    else if(p->next==NULL)
    {
        temp=list;
        list=NULL;
    }
    else
    {
        temp=list;
        list=list->next;
        temp->next=NULL;
    }
    return temp;
}

int getsum(nodeptr p)
{
    int get;
    int sum=0;
    nodeptr temp=p;
    while(temp!=NULL)
    {
        get=temp->index;
        sum+=findvalue(get);
        temp=temp->next;
    }
    return sum;
}

int findvalue(int get)
{
    if(get>=2&&get<=10)
        return get;
    if(get==65)//RETURN FOR ACE
        return 1;
    if(get==74)
        return 12;
    if(get==81)
        return 14;
    if(get==75)
        return 16;
    if(get==88)
        return 0;
}

void returntodeck(nodeptr p)
{
    int ctr=1;
    nodeptr q,temp=p;
    while(temp!=NULL)
    {
        q=temp->next;
        readd(list,temp);
        if(q==NULL)
        {
            break;
        }
        temp=q;
    }

}

void declare(nodeptr x)
{
    int yn;
    if(x==p1)
    {
        if(getsum(x)==getsum(p2))
        {
            printf("\tIT's A TIEEE\nNO DAMAGE DONE:)\n");
        }
        else if(getsum(x)<getsum(p2))
        {
            printf("\n\nSUCCESSFUL DECLARE %s\n\n",onename);
            twopoints+=getsum(p2);
            printf("\n\n 10 POINTS AND YOU GET FRESH CARDS %s ??\n\n",twoname);
            printf("YOUR CURRENT SET\n");
            display(p2);
            printf("\nWANT TO TRY YOUR LUCK??\n");
            scanf("%d",&yn);
            if(yn==1)
            {
                returntodeck(p2);
                lifeassign(p2,p1);
                twopoints+=10;
            }
        }
        else
        {
            printf("\n\nTOO EARLY YOU LOSE POINTS %s :(\n\n",onename);
            onepoints+=50;
        }
    }

    if(x==p2)
    {
        if(getsum(x)==getsum(p1))
        {
            printf("\tIT's A TIEEE\nNO DAMAGE DONE:)\n");
        }
        else if(getsum(x)<getsum(p1))
        {
            printf("\n\nSUCCESSFUL DECLARE %s\n\n",twoname);
            onepoints+=getsum(p1);
            printf("\n\n 10 POINTS AND YOU GET FRESH CARDS %s ??\n\n",onename);
            printf("YOUR CURRENT SET\n");
            display(p1);
            printf("\nWANT TO TRY YOUR LUCK??\n");
            scanf("%d",&yn);
            if(yn==1)
            {
                returntodeck(p1);
                lifeassign(p1,p2);
                onepoints+=10;
            }
        }

        else
        {
            printf("\n\nTOO EARLY YOU LOSE %s :(\n\n",twoname);
            twopoints+=50;
        }
    }
}

void titledesign()
{
    printf("\t\t\t.........\n\t\t\t.\n\t\t\t.\n\t\t\t.\n\t\t\t.\n\t\t\t.\n\t\t\t.\n\t\t\t.........\n\t\t\t\t.\n\t\t\t\t.\n\t\t\t\t.\n\t\t\t\t.\n\t\t\t\t.\n\t\t\t.........");
}

int main()
{
    int x;
    titledesign();
    printf("\n\n\n\nPLAYER 1 ENTER YOUR NAME  : ");
    gets(onename);
    printf("\n\nPLAYER 2 ENTER YOUR NAME  : ");
    gets(twoname);
    deckinitialise();
    deckremodel();
    deckremodel();
    deckremodel();
    //display(list);
    //printf("\nCont??\n");
    //scanf("%d",&x);
    playerassign(p1,p2);
    printf("\n\nASSIGN OVER\n\n");
    printf("\n\n%s Cards\n\n",onename);
    display(p1);
    printf("\nCont??\n");
    scanf("%d",&x);
    system("cls");
    printf("\n\n%s Cards\n\n",twoname);
    display(p2);
    printf("\nCont??\n");
    scanf("%d",&x);
    system("cls");
    //printf("\n\nAfter Assigning :: DECK\n\n");
    //display(list);
    //printf("\nCont??\n");
    //scanf("%d",&x);
    start();
}
