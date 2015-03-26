#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void* ecMalloc(int size){
  void* ptr = malloc(size);
  if(ptr==NULL){
    printf("Memory Error\n");
    exit(-1);
  }
  return ptr;
}

typedef struct List_{
  int data;
  List_ *next;
} List;

int ListLength(List *head){
  List *current = head;
  int cnt = 0;
  while(current!=NULL){
    cnt++;
    current = current->next;
  }
  return cnt;
}

void InsertLinkedList(List **head,int data,int position){
  int k=1;
  List *p,*q,*newNode;
  newNode = (List*)ecMalloc(sizeof(List));
  newNode->data = data;
  p = *head;
  if(position==1){
    newNode->next = p;
    *head = newNode;
  } else {
    while(p!=NULL && k<position){
      k++;
      q = p;
      p = p->next;
    }
    q->next = newNode;
    newNode->next = p;
  }
}

void DeleteNodeFromLinkedList(List **head,int position){
  int k = 1;
  List *p,*q;
  if(*head==NULL){
    printf("List is Empty.\n");
    return;
  }else {
    while(p!=NULL && k < position){
      k++;
      q = p;
      p = p->next;
    }
    if(p==NULL){
      printf("Position does not exits");
    } else {
      q->next = p->next;
      free(p);
    }
  }
}

void DeleteLinkedList(List **head){
  List *auxilaryNode,*iterator;
  iterator = *head;
  while(iterator){
    auxilaryNode = iterator->next;
    free(iterator);
    iterator = auxilaryNode;
  }
  *head = NULL;
}

typedef struct DllNode_{
  int data;
  struct DllNode_ *prev;
  struct DllNode_ *next;
} DllNode;

void DllInsert(DllNode **head,int data,int position){
  int k=1;
  DllNode *temp,*newNode;
  newNode = (DllNode*)ecMalloc(sizeof(DllNode));
  newNode->data = data;
  if(position==1){
    newNode->next = *head;
    newNode->prev = NULL;
    if(*head) (*head)->prev = newNode;
    *head = newNode;
    return;
  }
  temp = *head;
  while( k < position-1 && temp->next != NULL){
    temp = temp->next;
    k++;
  }
  if(k != position){
    printf("Desired position does not exist.\n");
    return;
  }
  newNode->next = temp->next;
  newNode->prev = temp;
  if(temp->next){
    temp->next->prev = newNode;
    temp->next = newNode;
  }
  return;
}

void DllDelte(DllNode **head,int position){
  DllNode *temp,*temp2;
  temp = *head;
  if(*head==NULL){
    printf("List is Empty.\n");
    return;
  }
  if(position==1){
    *head = (*head)->next;
    if(*head!=NULL){
      (*head)->prev = NULL;
    }
    free(temp);
    return;
  }
  while(k<position && temp->next!=NULL){
    temp = temp->next;
    k++;
  }
  if(k!=position-1){
    printf("Desired position does not exist.\n");
    return;
  }

  temp2 = temp->prev;
  temp2->next = temp->next;
  if(temp->next){
    tmep->next->prev = temp2;
    free(temp);
  }
  return;
}

typedef struct CllNode_{
  int data;
  struct CllNode_ *next;
} CllNode;

int CircularListLength(CllNode *head){
  CllNode *current = head;
  int cnt = 0;
  if(head==NULL)return 0;
  do{
    current = current->next;
    cnt++;
  } while(current!=head);
  return cnt;
}
void PrintCircularListData(CllNode *head){
  CllNode *current = head;
  if(head == NULL){
    return;
  }
  do{
    printf("%d\n",current->data);
    current = current->data;
  } while(current!=head);
}

void InsertAtEndCll(CllNode **head,int data){
  CllNode *current = *head;
  CllNode *newNode = (CllNode*)ecMalloc(sizeof(CllNode));
  newNode->data = data;
  while(current->next != *head){
    current = current->next;
  }
  newNode->next = newNode;
  if(*head==NULL)
    *head = newNode;
  else{
    newNode->next = *head;
    current->next = newNode;
  }
}

void InsertAtBeginInCll(CllNode **head,int data){
  CllNode *current = *head;
  CllNode *newNode = (CllNode*)ecMalloc(sizeof(CllNode));

  newNode->data = data;
  while(current->next != *head){
    current = current->next;
  }

  newNode->next = newNode;
  if(*head==NULL) *head = *newNode;
  else{
    newNode->next = *head;
    current->next = newNode;
    *head = newNode;
  }
  return;

}

void DeleteLastNodeFromCll(CllNode **head){
  CllNode *temp = *head,*current = *head;
  if(*head==NULL){
    printf("List if Empty.\n");
    return;
  }
  while(current->next != *head){
    temp = current;
    current = current->next;
  }
  temp->next = current->next;
  free(current);
  return;
}

void DeleteFrontNodeFromCll(CllNode **head){
  CllNode *temp = *head;
  CllNode *current = *head;
  if(*head==NULL){
    printf("List is Empty.\n");
    return;
  }
  while(current->next != *head){
    current = current->next;
  }
  current->next = (*head)->next;
  *head = *head->next;
  free(temp);
  return;
}

int IsLinkedListContainsLoop(List *head){
  List *slowPtr = head,*fastPtr = head;
  while(slowPtr && fastPtr){
    fastPtr = fastPtr->next;
    if(fastPtr==slowPtr){
      return 1;
    }
    if(fastPtr==NULL){
      return 0;
    }
    fastPtr = fastPtr->next;
    if(fastPtr == slowPtr){
      return 1;
    }
    slowPtr = slowPtr->next;
  }
  return 0;
}

int FindBeginLoop(List *head){
  List *slowPtr = head,*fastPtr = head;
  int loopExists = 0;
  while(slowPtr && fastPtr){
    fastPtr = fastPtr->next;
    if(fastPtr == slowPtr){
      loopExists = 1;
      break;
    }
    if(fastPtr == NULL){
      loopExists = 0;
      break;
    }
    fastPtr = fastPtr->next;
    if(fastPtr==slowPtr){
      loopExists = 1;
      break;
    }
    slowPtr = slowPtr->next;
  }
  if(loopExists){
    slowPtr = head;
    while(slowPtr!=fastPtr){
      fastPtr = fastPtr->next;
      slowPtr = slowPtr->next;
    }
    return slowPtr;
  }
  return NULL;
}

int FindLoopLength(List *head){
  List *slowPtr = head;
  List *fastPtr = head;
  int loopExists = 0;
  int cnt = 0;
  while(slowPtr && fastPtr){
    fastPtr = fastPtr->next;
    if(fastPtr == slowPtr){
      loopExists = 1;
      break;
    }
    if(fastPtr==NULL){
      loopExists = 0;
      break;
    }
    fastPtr = fastPtr->next;
    if(fastPtr==slowPtr){
      loopExists = 1;
      break;
    }
    slowPtr = slowPtr->next;
  }
  if(loopExists){
    fastPtr = fastPtr->next;
    while(slowPtr!=fastPtr){
      cnt++;
      fastPtr=fastPtr->next;
    }
    return cnt;
  }
  return 0;
}

List *InsertInSortedList(List *head,int data,List *newNode){
  List *current = head;
  List *temp;
  if(!head){
    return newNode;
  }
  while(current != NULL && current->data < newNode->data){
    temp = current;
    current = current->next;
  }
  newNode->next = current;
  temp->next = newNode;
  return head;
}

List *ReverseList(List *head){
  List *temp = NULL, *newNode = NULL;
  while(head){
    newNode = head->next;
    head->next = temp;
    temp = head;
    head = newNode;
  }
  return temp;
}

List *RecursiveReverse(List *head){
  if(head==NULL)
    return NULL;
  if(head->next == NULL){
    return head;
  }
  List *secondElem = head->next;
  head->next = NULL;
  List *reverseList = RecursiveReverse(secondElem);
  secondElem->next = head;
  return reverseList;
}
