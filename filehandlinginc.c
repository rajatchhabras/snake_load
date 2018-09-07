#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include<time.h>
struct food
{
    int a;
    int b;
    char value;
};
void get_food(struct food *foo,int x,int y,char value)
{

    foo->a=x;
    foo->b=y;
    foo->value=value;
}
struct snake
{
    int x;
    int y;
    char data;
    struct snake *next;
};
void print(char mat[][100])
{
    int i,j;
for(i=0;i<30;i++)
    {
      for(j=0;j<25;j++)
      {
          printf("%c",mat[i][j]);
      }
      printf("\n");
    }
}
//WHETHER SNAKE BIT ITSELF
int bit_itself(struct snake **ske,char move)
{
    int c_r,c_c,flag=0;
    struct snake *temp;
    temp=*ske;
     c_r=temp->x;
     c_c=temp->y;

    if(move=='r')
    {
     c_c=c_c+1;
    }
    else if(move=='l')
    {
      c_c=c_c-1;
    }
    else if(move=='t')
    {
       c_r=c_r-1;
    }
     else if(move=='b')
    {
       c_r=c_r+1;
    }

if(temp->next!=NULL)
       temp=temp->next;
       if(temp->next!=NULL)
       temp=temp->next;
    while(temp!=NULL)
    {
     if(c_r==temp->x&&c_c==temp->y)
     flag=1;
temp=temp->next;
}
    if(flag==1)
        return 1;
        else return 0;
}
//FOR INSERTING AFTER EATING OF THE FOOD
void insert(struct snake **ske, struct food *valu)
{
   struct snake *temp=*ske;
  struct  snake *newnode=(struct snake *)malloc(sizeof(struct snake));
  if(temp->next!=NULL){
    while(temp->next->next!=NULL)
    {
        temp=temp->next;
    }
    newnode->x=valu->a;
    newnode->y=valu->b;
    newnode->data='#';
    newnode->next=temp->next;
    temp->next=newnode;
  }
  else if(temp->next==NULL)
  {
      newnode->x=valu->a;
    newnode->y=valu->b;
    newnode->data='#';
    newnode->next=temp;
    *ske=newnode;
  }
}
//DATASAVING IN THE FILE
void datasaved(struct snake **ske,struct food *fo,struct food *po,FILE *ptr)
{
struct snake  *temp;
  temp=*ske;
  int x;
  fprintf(ptr,"%d\n%d\n%c\n$$\n",fo->a,fo->b,fo->value);
    fprintf(ptr,"%d\n%d\n%c\n$$\n",po->a,po->b,po->value);
  while(temp!=NULL)
  {
      fprintf(ptr,"%d\n%d\n%c\n",temp->x,temp->y,temp->data);
      fprintf(ptr,"%s","**\n");
      temp=temp->next;
  }
}
//CREATING A SNAKE
void create_snake(struct snake **ske,int a,int b,char valu)
{
    struct snake *temp=*ske;
   struct  snake *newnode;
   newnode=(struct snake *)malloc(sizeof(struct snake));
   newnode->x=a;
   newnode->y=b;
   newnode->data=valu;
   newnode->next=NULL;
    if(temp==NULL)
    {
        *ske=newnode;
    }
    else
    {
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=newnode;
    }
}
//DELETING LAST SECOND ELEMENT OF THE SNAKE
void delete_f(char mat[][100],struct snake **ske)
{
    struct snake *temp;
    temp=*ske;
    if(temp->next!=NULL)
    {
    while(temp->next->next!=NULL)
    {
        temp=temp->next;
    }
    temp->data=temp->next->data;

      mat[temp->next->x][temp->next->y]=' ';
    temp->next=NULL;

}
else
        {
        temp=NULL;
        }
}
//GENERATING THE RANDOM NUMBER FOR POISON AND FOOD USING RAND FUNCTION
void generated(struct snake **ske,int *l,int *r,struct food *f)
{
  *l=(rand()%(28-1+1))+1;
  *r=(rand()%(22-1+1))+1;
   int flag=0;
   struct snake *temp;
   temp=*ske;
   while(temp!=NULL)
   {
   if((temp->x==*l)&&(temp->y==*r))
       {
           flag=1;
           break;
       }
       temp=temp->next;
   }
   if((*l==f->a)&&(*r==f->b))
    flag=1;
   if(flag==1)
    generated(ske,l,r,f);
}
//ASSIGNING POSITION ON THE MATRIX
void traverse(char mat[][100],struct snake **ske)
{
    struct snake *temp=*ske;
    while(temp!=NULL)
    {
        mat[temp->x][temp->y]=temp->data;

        temp=temp->next;
    }
}
//MAKE THE MATRIX BOUNDARY * AND THE LEFT PLACE WITH SPACE
void space(char mat[][100])
{
   int i,j;
     for(i=0;i<30;i++)
   {
       for(j=0;j<25;j++)
       {
           if(i==0||i==29||j==0||j==24)
           mat[i][j]='*';
           else
           mat[i][j]=' ';
       }
   }
}
//CHECKING WHETHER SNAKE HAS BIT THE FOOOD
int check(struct food *fe,struct snake **ske)
{
    int choice;
    if((*ske)->x==fe->a&&(*ske)->y==fe->b)
        return 1;
    else
        return 0;
}
//FOR CHANGING THE MOVE VALUE IF SNAKE GOES IN OVERLAP ON ITS BODY
char movecheck(struct snake **ske,char move)
{
 int flag;
    int c_row,c_col;
    struct snake *temp;
    temp=*ske;
    int p_row=temp->x;
    int p_col=temp->y;

        if(move=='t'){
                if(temp->x-1==temp->next->x||(temp->x==1&&temp->next->x==28))
                        flag=1;
                if(flag==1)
                    move='b';
                  else
                     move='t';
                   }
                else if(move=='b'){
                if(temp->x+1==temp->next->x||(temp->x==28&&temp->next->x==1))
                   flag=1;
                if(flag==1)
                  move='t';
                   else
                     move='b';
                    }
                    else if(move=='r'){
                if(temp->y+1==temp->next->y||(temp->y==23&&temp->next->y==1))
                    flag=1;
                if(flag==1)
                    move='l';
                     else
                     move='r';
                    }
                    else if(move=='l'){
                if(temp->y-1==temp->next->y||(temp->y==1&&temp->next->y==23))
                  flag=1;
                if(flag==1)
                    move='r';
                     else
                     move='l';
                    }
              return move;
}
//FOR MOVING IN FOUR DIFFERENT DIRECTIONS
void movetop(struct snake **ske,char move,char mat[][100])
{
    int flag=0;
     int c_row,c_col;
    struct snake *temp;
    temp=*ske;
    int p_row=temp->x;
    int p_col=temp->y;

        if(move=='t'){
                if(temp->next==NULL&&temp->x!=1)
                {
                    mat[p_row][p_col]=' ';
                    temp->x=p_row-1;
                }
        else if(temp->x==1){
        temp->x=28;
        flag=1;
        }
         else if(temp->x-1!=temp->next->x){
     temp->x=p_row-1;
     flag=1;
         }
}
     else if(move=='b'){

              if(temp->next==NULL&&temp->x!=28)
                {
                   mat[p_row][p_col]=' ';
                    temp->x=p_row+1;
                }
 else if(temp->x==28){
        temp->x=1;
        flag=1;
 }
    else if(temp->x+1!=temp->next->x){
        temp->x=p_row+1;
        flag=1;
    }
     }
      else if(move=='r'){
              if(temp->next==NULL&&temp->y!=23)
                {
                    mat[p_row][p_col]=' ';
                    temp->y=p_col+1;
                }

       else if(temp->y==23){
        temp->y=1;
        flag=1;
 }
    else if(temp->y+1!=temp->next->y){
        temp->y=p_col+1;
       flag=1;
    }
}
   else if(move=='l'){
                     if(temp->next==NULL&&temp->y!=1)
                     {
                    mat[p_row][p_col]=' ';
                    temp->y=p_col-1;
                     }
                    else if(temp->y==1){
                       temp->y=23;
                        flag=1;
                        }
                    else if(temp->y-1!=temp->next->y){
                         temp->y=p_col-1;
                          flag=1;
                        }
                      }

       if(flag==1){
        temp=temp->next;
        c_row=temp->x;
        c_col=temp->y;
        while(temp->next!=NULL)
     {
         temp->x=p_row;
         temp->y=p_col;
          p_row=c_row;
          p_col=c_col;
         temp=temp->next;
          c_row=temp->x;
          c_col=temp->y;
      }
     temp->x=p_row;
     temp->y=p_col;
     mat[c_row][c_col]=' ';
}
}
//DEFAULT SNAKE POSITON, FOOD POSITON AND POISON POSITION
void defalut(char mat[][100],struct food *foo,struct snake **ske,struct food *poison)
{
   get_food(foo,15,12,'F');
      mat[foo->a][foo->b]=foo->value;
       get_food(poison,3,18,'P');
     mat[poison->a][poison->b]=poison->value;
  create_snake(ske,22,1,'H');
  create_snake(ske,22,2,'#');
  create_snake(ske,22,3,'#');
  create_snake(ske,22,4,'T');

}
//DATARETERIVAL OF THE SNAKE
int datareterive(struct food *foo,struct food *poo,struct snake **ske,char mat[][100])
{
   char x[100][100];
    char c;
     FILE *ptr;
    int i,a=0,b=0,p;
    ptr=fopen("abc.txt","r");
       i=0;
fscanf(ptr,"%s",x[i]);
if(strcmp(x[i],"empty")==0)
    return -1;
        while((strcmp(x[i],"$$"))!=0){
        printf("%s\n",x[i]);
            i++;
         fscanf(ptr,"%s",x[i]);
    }
    p=0;
  while(x[0][p]!='\0')
  {
    a=a*10+(x[0][p]-48);
    p++;
  }
p=0;
while(x[1][p]!='\0')
  {
    b=b*10+(x[1][p]-48);
    p++;
  }
c=x[2][0];
get_food(foo,a,b,c);
mat[a][b]=c;
    i=0;
    fscanf(ptr,"%s",x[i]);
while((strcmp(x[i],"$$"))!=0){
    printf("%s\n",x[i]);
        i++;
         fscanf(ptr,"%s",x[i]);
    }
    a=0;
    b=0;
 p=0;
  while(x[0][p]!='\0')
  {
    a=a*10+(x[0][p]-48);
    p++;
  }
p=0;
while(x[1][p]!='\0')
  {
    b=b*10+(x[1][p]-48);
    p++;
  }
c=x[2][0];
    get_food(poo,a,b,c);
    printf("%d %d %c\n",poo->a,poo->b,c);
    mat[poo->a][poo->b]=poo->value;
    i=0;
 fscanf(ptr,"%s",x[i]);

 while((strcmp(x[i],"$$"))!=0)
{
    if(strcmp(x[i],"**")!=0){
    printf("%s\n",x[i]);
    }
        else{
                   a=0;
                   b=0;
                   p=0;
   while(x[0][p]!='\0')
  {
    a=a*10+(x[0][p]-48);
    p++;
  }
p=0;
while(x[1][p]!='\0')
  {
    b=b*10+(x[1][p]-48);
    p++;
  }
c=x[2][0];
         create_snake(ske,a,b,c);
         i=-1;
        }
            i++;
         fscanf(ptr,"%s",x[i]);
}
  fclose(ptr);
  return 1;
}
int main()
{
    char mat[100][100],prev;
    int reload,flag=0,rt;
    printf("\tWELCOME TO SNAKE LOAD GAME \n\n Whether You Want To  Resume The Previous Game \n \n IF YES PRESS 1 ELSE 0\n");
    scanf("%d",&reload);
    FILE *ptr;
struct snake *ske=NULL;
struct food foo;
struct food poison;
char move,k,chck[100];
   int i,j,d_save,strt;
space(mat);
   int l,b;
   int choice,p_get,bit;
if(reload==1){
    rt=datareterive(&foo,&poison,&ske,mat);
if(rt==-1){
     printf(" ****** YOU DONT HAVE SAVED GAME ******\n\n");
    printf("Do You Want To Start A New Game \n IF YES PRESS 1 ELSE 0 \n");
    scanf("%d",&strt);
    if(strt==1){
       defalut(mat,&foo,&ske,&poison);
       flag=1;
    }
    else{
             system("cls");
        printf("    \n\tTHANKS FOR PLAYING     ");
        flag=0;
}
}
else
{
    flag=1;
}
}
else{
        defalut(mat,&foo,&ske,&poison);
       flag=1;
   }
if(flag==1){

traverse(mat,&ske);
 print(mat);
  move='t';
k=movecheck(&ske,move);
 while(1){
        if(kbhit())
        {
          move=getch();
          if(move==27)
                break;
            if(move=='r'||move=='l'||move=='t'||move=='b')
            {

               k=movecheck(&ske,move);
            }
        }
bit=bit_itself(&ske,k);
   if(bit)
      {
          printf(" You lose ");
          break;
      }
    movetop(&ske,k,mat);
     choice=check(&foo,&ske);
      p_get=check(&poison,&ske);
if(choice){
    insert(&ske,&foo);
    l=0;
    b=0;
     srand(time(NULL));
    generated(&ske,&l,&b,&poison);
    get_food(&foo,l,b,'F');
    mat[foo.a][foo.b]=foo.value;
}
if(p_get)
{
    delete_f(mat,&ske);
     l=0;
    b=0;
     srand(time(0));
    generated(&ske,&l,&b,&foo);
    get_food(&poison,l,b,'P');
    mat[poison.a][poison.b]=poison.value;
}
    traverse(mat,&ske);
  system("cls");
  print(mat);
  Sleep(50);
 }
   ptr=fopen("abc.txt","w");
  printf("\n Whether You Want To Save Game \n IF YES PRESS 1 else 0 \n");
  scanf("%d",&d_save);
  if(d_save==1){
 datasaved(&ske,&foo,&poison,ptr);
  fprintf(ptr,"$$");
  }
  else
  {
 fprintf(ptr,"empty");
  }
  fclose(ptr);
}
}




