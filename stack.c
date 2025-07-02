#include<stdio.h>
#include<stdlib.h>
struct Node
{
    int data;
    struct Node* next;
    struct Node*pre;
};
int n=0;
 
 struct Node*head=NULL;
 struct Node*tail=NULL;
  
void push(int data)
{
 struct Node*newNode=(struct Node*)malloc(sizeof(struct Node));
 newNode->data=data;
 newNode->next=head;
 newNode->pre=NULL;
 if(head==NULL)
 tail=newNode;
 else
 head->pre=newNode;
 
 head=newNode;
}
void isEmp()
{
    if (head==NULL)
    printf("the stack is empty\n");
    else
    printf("not empty\n");
}
void pop()
{
   struct Node*temp=head;
   head=temp->next;
   free(temp);
}
 void peak()
  {
   printf("%d\n",head->data);   
  }
void display()
{
   struct Node*temp=head;
   while(temp!=NULL)
   {
  
   printf("%d->",temp->data);
   temp=temp->next;
   }
   printf("NULL");
}
void displayRev()
{
   struct Node*temp=tail;
   while(temp!=NULL)
   {
  
   printf("%d->",temp->data);
   temp=temp->pre;
   }
   printf("NULL");
}

int main()
{
printf("Enter Number of elements : \n");
    int len;
    scanf("%d",&len);
    printf("Enter elements to push into stack : \n");
    int val;
    for(int i=0;i<len;i++)
    {
    scanf("%d",&val);
    push(val);
    }
    
    isEmp();
    printf("Peak value of stack is:\n");
    peak();
    printf("Elements in stack :\n");
    display();
    printf("\n");
    printf("Reversing elements in stack :\n");
    displayRev();
    pop();
    pop();
    
    
    printf("\nafter pop:\n");
    isEmp();
    //return 0;
}

