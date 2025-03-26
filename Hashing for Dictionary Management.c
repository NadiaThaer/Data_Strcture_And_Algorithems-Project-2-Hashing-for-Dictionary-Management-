
/*
  Nadia Thaer.
  1210021.
  s 1 .
*/
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>
#define  MAX    100
#define MaxElements  100
FILE *input;//pointer To Input File.
FILE *output;//pointer to outputFile.
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Define the Strcut of Doubly Linked List.//
typedef struct node *ptr;
struct node
{
    char Data[MAX];
    ptr next;
    ptr prev;
} ;
/////////////////////////////////////////Define the struct of tree////////////////////////////////
typedef struct tree*ptt;
struct tree
{
    char  data;
    ptt left;
    ptt right;


};
//////////////////////////////////////////////////Define a Struct of Stack////////////////////////////////////////////////////////////////
typedef struct stack*STK;
struct stack
{
    //First Define The Array type of Ptt Becouse it will Contain the Node of Tree.
    ptt *S;
    int top;//the will Point on The top Element in Stack.
    int Size ;//This Mean How many Element in Array of Stack.
    int Capacity;//And this Mean how many Element that can The Array of Stack Contain.
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ptr tail=NULL;//This Pointer Is To Point in The Last Node Of My List.
char nameOFFaile[20];//This Array Is To Store The Name Of File From User.
ptr L=NULL;//This List Will Store The Arithmetic Expression in infix Form After Reading It From File.
ptt ArrayOfRoot[MaxElements];//This array will store the Roots of Tree.
int indixOfroot=0;//index to traversal the Array of Root.
int i=1;
////////////////////////////////Starting With Menu Function //////////////
void Menu();
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////Functions of Doubly Linked List////////////////////////////////////////////////////////////////////
//Creating anode of List That Will Contain the infix Exp Readed from File.
ptr Creating_Node_List(char *infixEq);
//insert the Node to The List Eq.
ptr insert_End(ptr L,char *infixEq);
//printing Eq List.
void Display(ptr L);
//Get How Many Node The List Have.
int Get_SizeOf_List(ptr L);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Function Read From File and Store in List.
ptr ReadFile(ptr L) ;
//This Function is To Ignore the Space and special Char .
char * without_Spasing_And_special_characters(char *);
///////////////////////////////////////////////////////Implementation the Stack As Array///////////////////////////
/*
this Function will Do To Thing To Initialize the stack:
1-make the variable top=-1>>Because No Element in This Stack.
2-make  the variable size=0>>This Mean The Stack Has No Element.
*/
void InisilaizeS_tack(STK s);
/*
the creat Function of the Stack is Do :
1)allocat the Block To This Stack
2)allocat the Array That We will To Use it To Implement The Stack
Note:Because This Stack Will Contain a Node So The Type of The Array Will Be ->>>>ptt.
3)make the Capcity of thies Stack Is EQuel the Max Element Can The Arrray Of Stack can Contain.
4)Initialize this Stack
5)the stack is Ready To Use Return It.
*/
STK Create_Stack();
//Check if The Stack Is Empty Return 1 else Return 0
int Is_Empty(STK s);
//Check if The Stack Is FULL Return 1 else Return 0
int is_FULL(STK s);
/*
the push Function :use To Push The Node To The Stack.
*/
void push(STK s,ptt node);
/*
pop the node From Stack.
*/
ptt pop(STK s);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//This Function Check if The Char is operator return 1 else return 0.
int isOperater(char s);
////this Function Check The Prec of the operator on the operator Stack.
int precedence(int top,int Symbol);
//Creating a node of Tree.
ptt creat_node_of_tree(char Data);
//Give me the node that the top is pointing it.
char peek(STK s);
//Build the Expression Of Tree.
ptt Build_EXP_Tree(char *EXP);
/*
in THis Function :
1-creat an Expression Tree For a Arthmatic Eq.
2-Store this root on Array of Root.
3-Evaluate .
*/
void Evaluate_By_Expression_Tree_one();
//this will Give the result After Evalute For Each Root From Array Of Root.
int Evaluat_Expression_tree_Tow(ptt);
int  aplay_operater(char operater,int num1,int num2);
void printing_Eq_Post();
void traversal_one(ptt T);//This is to travarsel the tree and print the postfix.
void traversal_File(ptt T);
void save_In_File();

//////////////////////////////////////////////////////////////Creat a node To Added it in The List//////////////////////////////////////////////

int main()
{


    int Choice=0;

    while(Choice<6)
    {
        printf("\nEnter Your Choice.\n");
        Menu();//Display the Menu To Select Choice .
        scanf("%d",&Choice);
        if(Choice>6)
        {
        printf("InVaild Choice .\n");
             printf("\nEnter Your Choice.\n");
        Menu();//Display the Menu To Select Choice .
        scanf("%d",&Choice);
        }
        switch(Choice)
        {
        case 1:
                L=ReadFile(L);
                if(L==NULL)
                    break;
                printf("Your infix Expression Loaded Successfully ,and the number of  infix Expression is:%d.\n",Get_SizeOf_List(L));
                break;
        case 2:printf("The Equation in File <Note:I read The Eq Without White Space and special characters>.\n");
               Display(L);
               break;
        case 3://///////////////////////////////In This Case We Will Build an Ex tree For all the infix Exp///////
                 Evaluate_By_Expression_Tree_one();
                 break;
        case  4:
               printing_Eq_Post();
               break;
        case  5:
                 save_In_File();
                 break;
        case   6:printf("Ending\n");
                  break;
        }

    }
    return 0;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ptr Creating_Node_List(char *infix)
{
    ptr newNode=(ptr)malloc(sizeof(struct node));
    strcpy(newNode->Data,infix);
    newNode->next=NULL;
    newNode->prev=NULL;
    return newNode;
}
//////////////////////////////////////////////////////////Insert The Node In The End Of The List///////////////////////////////////////
ptr insert_End(ptr L, char *Data) {
    ptr newNode=Creating_Node_List(Data);//Creat a new Node Using Function Creat_Node.
    //First Step :Check if the List Is Empty THen The New Node Will Be The First Node I want To Add.
        if(L==NULL)
        {
        L=tail=newNode;
        }
        else//This Mean That The List is Not Empty So I will Add The New Node in The last of The List.
        {
          tail ->next=newNode;//Note:Tail is pointer I defined it To Pointer To the Last Node in The List.
           newNode->prev=tail;
          tail=newNode;//After this Step:The New Node is Will Be The Last Node So:The tail Will Pointer to New Node..
        }
    return L;//Return Updating List.
}
/////////////////////////////////////////////Display List in Recursion Way ////////////////////////////////////////////////////
void Display(ptr L) {

    if(L==NULL)//This Mean arraived to The End of List.
    {

        return;//get out From Function
    }
       printf("\nEquation %d: %s\n",i,L->Data);//printing Data Before Call The Function To Do The Recursion.
       i++;
        Display( L->next);
}
////////////////////////////////////////////////////////////////////////////
int isOperater(char s)
{
    if(s=='+'||s=='-'||s=='%'||s=='/'||s=='*')
        return 1;
    else
        return 0;
}
/////////////////////////////////////////////////////////////////////////////////
char * without_Spasing_And_special_characters(char *s)
{
    char*res=(char* )malloc((MAX)*sizeof(char));
    int i=0;
    int j=0;
    while(s[i]!='\0')
    {
        if(isspace(s[i]))
        {
            i++;
            continue;
        }
        else if(!isdigit(s[i])&&!isOperater(s[i])&&s[i]!='('&&s[i]!=')')
        {
            i++;
            continue;
        }
        else
        {
            res[j++]=s[i];
            i++;
        }
    }
    res[j]='\0';
    return res;
}
ptr ReadFile(ptr L) {

    printf("Enter The Name Of File You Wont To Load A data From It(Note:your name must beas >>name.txt\n");
    scanf("%s",nameOFFaile);
    input = fopen(nameOFFaile, "r");//open File To Read It.
    if (input == NULL){
        printf("**********File could not Found**********\n");
        return NULL ;
    }
    char Data[MAX];//To Store The Data When I read It From File.
 while(fscanf(input,"%[^\n]%*c",Data))
    {
        L = insert_End(L,without_Spasing_And_special_characters(Data));//when I read A new Data Put It In The List Directly.
        }



    fclose(input);//Close The File.

    return L;// Return List After Update it.
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Is_Empty(STK s)
{
    if( s->Size == 0)
    {
        return 1;
    }
    else
        return 0;
}
int is_FULL(STK s)
{
    if(s->Size == s->Capacity)
        return 1;
    else
        return 0;
}
void push(STK s,ptt node)
{
    if(is_FULL(s))
    {
        printf("FULL\n");
        return;
    }
    else
    {
        s->Size++;
        s->top=s->top+1;
        s->S[s->top]=node;
    }

}
ptt pop(STK s)
{
    if(Is_Empty(s))
    {
        printf("Empty\n");
        return;
    }
    else
    {

        ptt res=s->S[s->top];
        s->top=s->top-1;
         s->Size--;
        return res;
    }
}
/////////////////////////////////////////////////////////////////////////
void Inisilaize_Stack(STK s)
{
    s->Size = 0;
    s->top=-1;

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
STK Create_Stack(){
        STK s;//pointer point on the Block of sTACK.
        s = (STK)malloc(sizeof( struct stack ));//Malloc For this Block
        if( s == NULL)
        {
             printf("Out of space");
             return;
        }
       //malloc for the Array insaid the Block the taype of the Array is ptt
        s->S = (ptt)malloc(sizeof(ptt) * MaxElements);
        if( s->S == NULL )
        {
             printf("Out of space");
             return;
        }

        s->Capacity = MaxElements;
        Inisilaize_Stack( s );
return s;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////Starting With Creating a node of tree //////////////////////////////
ptt creat_node_of_tree(char Data)
{
    ptt newNode;
    newNode=(ptt)malloc(sizeof(struct tree));
    newNode->data=Data;
    newNode->left=NULL;
    newNode->right=NULL;
    return newNode;

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int precedence(int top,int symbol)
{

    if ((top == '*' || top == '/' || top == '%') && (symbol == '+' || symbol == '-'))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//this function to get the peek of stack
char peek(STK s)
{
    return s->S[s->top]->data;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ptt Build_EXP_Tree(char *infix)
{
    int index=0;
    char Sympol, Operator;
    ptt t=NULL;
    ptt t1=NULL;
    //Defined a Tow Type Of Stack//
    STK operandStack=Create_Stack();
    STK  operaterStack=Create_Stack();
    //////////////////////////////////////
    while(infix[index]!='\0')
    {
        Sympol=infix[index];
        index++;
        //check if the symbol is an open (
              if (Sympol == '(')
        {
            push(operaterStack, creat_node_of_tree(Sympol));//push it in the operator Stack.
        }
        //Check if reading symbol is Close )
        else if (Sympol == ')')
        {
            //then :according the operater stack is Still not Empty.
            //i need to get the operater the get the left anf the Right Children The push it in the Operand Stack.
            while (!Is_Empty(operaterStack) && peek(operaterStack)!= '(')
            {
                Operator = pop(operaterStack)->data;
                t1 = creat_node_of_tree(Operator);
                t1->right = pop(operandStack);
                t1->left = pop(operandStack);
                push(operandStack, t1);
            }
            //pop  (
            pop(operaterStack);
        }
       else if(isdigit(Sympol))
        {


            t=creat_node_of_tree(Sympol);
            push(operandStack,t);

        }

        else
        {
            /*
            if the operater readed:
                1-we Must to Check if the operator Stack is Impty Or Not.
                2-get the peek of the operator Stack .
                3-and Check if i can push the operator or not (Note :this according to the preced of the operatot.)
            */
         while (!Is_Empty(operaterStack) && !precedence(peek(operaterStack), Sympol))
            {
                Operator = pop(operaterStack)->data;
                t1 = creat_node_of_tree(Operator);
                t1->right = pop(operandStack);
                t1->left = pop(operandStack);
                push(operandStack, t1);
            }
            push(operaterStack,creat_node_of_tree(Sympol));
        }

    }
    while(!Is_Empty(operaterStack))
    {
            Operator=pop(operaterStack)->data;
                t1=creat_node_of_tree( Operator);
                t1->right=pop(operandStack);
                t1->left=pop(operandStack);
                push(operandStack,t1);
    }
     ptt root=pop(operandStack);

    return root;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int  aplay_operater(char operater,int num1,int num2)
{
    int  res=0;
    if(operater=='/')
    {
        if(num2==0)
        {

            return -1;

        }
        else if(num1==0)
        {
             return 0;
        }

        else {
              res= num1/num2;
                return  res;
        }
    }
 if(operater=='%')
    {
        if(num2==0)
        {
            //printf("The operataion is not Valid according To Math");
            return -1;

        }
        else if(num1==0)
        {
             return 0;
        }

        else {
              res= num1%num2;
                return  res;
        }
    }
    switch(operater)
    {
        case '*':res=num1*num2;
                 break;
         case '-':res= num1-num2;
                 break;
        case '+':res= num1+num2;
                 break;

             default:break;
    }
return res;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int  Evaluat_Expression_tree_Tow(ptt root)
{
    if(root==NULL)
    {
        printf("The tree is Empty\n");
        return 0;
    }
    if(root->left==NULL&&root->right==NULL)
    {
        return (root->data-'0');//to get the leafe node (digit) and Convert it to int .
    }
    int num1=Evaluat_Expression_tree_Tow(root->left);//this is to give the result from left child
    int  num2=Evaluat_Expression_tree_Tow(root->right);//this is to give the result from the right child.
    return aplay_operater(root->data,num1,num2);//and this to give me the final result and will update when the recursion Function work.
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void traversal_one(ptt T)
{
        //Base Case.
        if ( T == NULL)
         return ;
traversal_one(T->left);
traversal_one(T->right);
printf("%c ",T->data );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Menu()
{
    printf("1-Read	equations.\n");
    printf("2-Print the equation.\n");
    printf("3-Evaluate using Expression tree.\n");
    printf("4-Printing postFix Expression.\n");
    printf("5-Save in file.\n");
    printf("6-Exit.\n");


}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Get_SizeOf_List(ptr L)
{
    //First Step:Check if The List Is Empty Or Not.
    if(L==NULL)
    {
        printf("Your List is Empty With Zero Node!!\n ");
        return 0;
    }
    int node=0;//Initialize the Counter=0;
    ptr temp=L;//This pointer point to The List.
    while(temp!=NULL)
    {

        temp=temp->next;
         node++;
    }

    return node;

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void printing_Eq_Post()
{
    int i=0;
    while(i<indixOfroot)
    {
        traversal_one(ArrayOfRoot[i]);
        printf("\n\n");
        i++;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void Evaluate_By_Expression_Tree_one()
{
     char Data[MAX];
     ptr t=L;
      int i=0;
      while(t!=NULL)
    {
       ptt root = NULL;
        root = Build_EXP_Tree(t->Data);
        ArrayOfRoot[indixOfroot]=root;
         printf("\nThe Evaluatin For This Expression:");
         printf("%s ",t->Data);
         int evaluateresult=Evaluat_Expression_tree_Tow( ArrayOfRoot[indixOfroot]);
         //IF THE evaluating ==-1 then thier is a noon Vailed Use in operater.
        if(evaluateresult!=-1)
{
    printf("=%d",evaluateresult);

}
else
{
      printf("The operataion is not Valid according To Math");
}
         indixOfroot++;
        printf("\n");
          t=t->next;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void  traversal_File(ptt T)
{
               if ( T == NULL)
                  return ;
             traversal_File(T->left);
             traversal_File(T->right);
              fprintf(output,"%c ",T->data );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void  save_In_File()
{
    output=fopen("output.txt","w");

    if(output==NULL)
        return;
        fprintf(output,"\n***********************************The postFix Expression + The Result of Evaluate*************\n\n");
    int i=0;
    while(i<indixOfroot)
    {
        fprintf(output,"The postFix Expression:");
        traversal_File(ArrayOfRoot[i]);
        int res=Evaluat_Expression_tree_Tow(ArrayOfRoot[i]);
        if(res!=-1)
        {
             fprintf(output,"\n\nthe result After Evaluating=%d",res);
        }
        else
        {
             fprintf(output,"\n\n The operataion is not Valid according To Math");
        }

        fprintf(output,"\n\n");
        i++;
    }
    fclose(output);
    printf("the postfix and the result Saved in file output.\n");

}
////////////////////////////////////////////////////////////////////////////***//////////////////////////////////////////////////////////
