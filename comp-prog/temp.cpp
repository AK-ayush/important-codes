#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Point{
  public:
    int x;
    int y;
  Point(int x, int y): x(x), y(y){} //constructor initialiser
};

struct list{
 int data;
 struct list* next;
};
typedef struct list node;

void traverse(node* head){
while(head!=NULL){
        cout<<head->data<<"  ";
        head = head->next;
    }
cout<<"\n";
}

void insert(node** head, int cond, int val){
  if (*head==NULL){
    node* temp = NULL;
    temp = (node*)malloc(sizeof(node));
    temp->data = val;
    temp->next = NULL;
    *head = temp;
    temp=NULL;
    return;
  }
node* temp=NULL;
temp = *head;
while(temp!=NULL){
    if (temp->data==cond){
       node* nn=NULL;
       nn = (node*)malloc(sizeof(node));
       nn->data= val;
       nn->next = temp->next;
      temp->next=nn;
      break;
     }
  temp = temp->next;
  }
}


void delete_node(node** head, int val){
    node *temp=NULL;
    if((*head)->data==val){
      temp = *head;
      *head = temp->next;
      free(temp);
      return;
  }
node *prev=NULL;
prev = *head;
temp = prev->next;
while(temp!=NULL){
    if(temp->data==val){
        prev->next = temp->next;
        free(temp);
        break;
    }// end if
      prev = temp;
      temp = temp->next;
  } // end while
} // end delete


int search_node(node *head, int val){
  if(head==NULL) return -1;
   int ret=-1;
   while(head!=NULL){
     ret++;
     if(head->data == val)return ret;
     head = head->next;
  }//while
return -1;
}//search_node

int main(){

    node *head=NULL;
    cout<<"insert\n";
    insert(&head, 2, 3);
    cout<<search_node(head,2)<<endl;
    traverse(head);
    cout<<"insert\n";
    insert(&head, 3, 4);
    cout<<search_node(head,3)<<endl;
    traverse(head);
    cout<<"delete\n";
    delete_node(&head, 3);
    traverse(head);
    insert(&head, 4, 11);
    insert(&head, 11, 12);
    traverse(head);
    cout<<search_node(head,12)<<endl;
    cout<<"delete\n";
    delete_node(&head, 11);
    //int x,y;
    //cin>>x>>y;
    //Point p(x,y);
    //cout<<p.x<<p.y<<endl;

    return 0;
}
