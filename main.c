//
//  main.c
//  Data Structure HW3
//
//  Created by 정우섭 on 2021/05/15.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 100
#define FALSE 0;
#define TRUE 1;

typedef struct BST_node{
    int data;
    int visited;
    struct BST_node * leftChild;
    struct BST_node * rightChild;
}node;

typedef struct {
    int data[MAX_QUEUE_SIZE];
    int front;
    int rear;
}Queue;
//---------------------BST Constructor---------------------------//
void init_Node(node* input_tree, int BST_size);
void Create(node* input_tree, int data[], int BST_size);
//---------------------Queue-------------------------//
void init_Q(Queue* q);
int IsEmpty(Queue* q);
int IsFull(Queue* q);
void enqueue(Queue* q, node data);
int dequeue(Queue* q);
//--------------------Searching Algorithm--------------------------//
int DFS_search(node* Node, int *searching_times);
int BFS_search(node* Node, int searching_times);
//--------------------result passer---------------------------//
void pass_result(int result_num,int *result,int result_arr[]);
void return_result(int result_arr[],int how_many);

void init_Node(node input_tree[], int BST_size)
{
    for(int i=0;i<BST_size;i++)
    {
        input_tree[i].data = 0;
        input_tree[i].leftChild=NULL;
        input_tree[i].rightChild=NULL;
        input_tree[i].visited=FALSE;
    }
}

void Create(node input_tree[], int data[], int BST_size)
{
    for(int i=0;i<BST_size;i++)
    {
        input_tree[i].data=data[i];
    }
    for(int i=0;i<BST_size-1;i++)
    {
        if(input_tree[i].data > input_tree[i+1].data){
            input_tree[i].leftChild=&input_tree[i+1];
        }
        else {
            input_tree[i].rightChild=&input_tree[i+1];
        }
    }
}

void init_Q(Queue* q)
{
    for(int i=0;i<MAX_QUEUE_SIZE;i++)
    {
        q->data[i]=0;
    }
    q->front = q->rear =0;
}

int IsEmpty(Queue* q)
{
    return (q->front == q->rear);
}

int IsFull(Queue* q)
{
    return ((q->rear+1)%MAX_QUEUE_SIZE==q->front);
}

void enqueue(Queue* q,node input)
{
    if(IsFull(q))
    {
        printf("Queue is Full");
    }
    q->rear = (q->rear+1)%MAX_QUEUE_SIZE;
    q->data[q->rear]=input.data;
}

int dequeue(Queue* q)
{
    int temp=0;
    if(IsEmpty(q))
    {
        printf("Queue is empty");
        exit(0);
    }
    q->front = (q->front+1)%MAX_QUEUE_SIZE;
    temp=q->data[q->front];
    q->data[q->front]=0;
    return temp;
}
int DFS_search(node* Node, int *searching_times)
{
    if(*searching_times==1)
    {
        return Node->data;
    }
    if(Node->leftChild==NULL)
    {
        --(*searching_times);
        return DFS_search(Node->rightChild, searching_times);
    }
    if(Node->rightChild==NULL)
    {
        --(*searching_times);
        return DFS_search(Node->leftChild, searching_times);
    }
    else return 1;
}
int BFS_search(node* Node, int searching_times)
{
    Queue q;
    int temp = searching_times;
    int *counter = &temp;
    init_Q(&q);
    for(int i=0;i<(*counter);i++)
    {
        enqueue(&q, Node[i]);
        (*counter) = (*counter)-1;
        if(Node[i].leftChild!=NULL&&i<(*counter))
        {
            enqueue(&q, *Node[i].leftChild);
            i++;
            (*counter)++;
        }
        if(Node[i].rightChild!=NULL&&i<(*counter))
        {
            enqueue(&q, *Node[i].rightChild);
            i++;
            (*counter)++;
        }
    }
    for(int i=0;i<searching_times;i++)
    {
        if(i==searching_times-1)
        {
            return dequeue(&q);
        }
        else dequeue(&q);
    }
    return 1;
}

void pass_result(int result_num,int *result,int result_arr[])
{
    result_arr[result_num]=(*result);
}

void return_result(int result_arr[],int how_many)
{
    FILE *of = fopen("/Users/jungwooseop/모시공/수업자료/자료구조/HW3/output.txt","w");
    for(int i=0;i<how_many;i++)
    {
    fprintf(of, "%d\n",result_arr[i]);
    }
    fclose(of);
}

int main()
{
    int how_many_times;      //the number of input expression
    int BST_size;            //input the number of element here
    char string[7]={0};      //input string data here
    char temp[2]={0};        //input searching num
    int searching_times;     //the number of input expression
    int result;              //result of expression


    FILE *fp = fopen("/Users/jungwooseop/모시공/수업자료/자료구조/HW3/input-3.txt","r");
    fscanf(fp, "%d", &how_many_times);
    int *result_arr=(int*)malloc(sizeof(int)*how_many_times);
    
        for(int i=0;i<how_many_times;i++)
        {
            memset(string, 0, sizeof(char)*7);                              //reset string[]
            memset(temp, 0, sizeof(char)*2);                                //reset temp[]
            fscanf(fp, "%d", &BST_size);                                    //pass BST size
            int* input=(int*)malloc(sizeof(int)*BST_size);                  //allocate heep memory as long as input BST size
            fscanf(fp, "%s", string);                                       //pass string input data to string[]
            node* tree = (node*)malloc(sizeof(node)*BST_size);  //dynamic allocation of nodes
            init_Node(tree, BST_size);                                      //initialization of nodes
            for(int i=0;i<BST_size;i++)                                     //input elements in array
            {
                fscanf(fp, "%d",&input[i]);
            }
            Create(tree, input, BST_size);                                  //Create BST structure with inputed elements
            for(int i=0;i<2;i++)
            {
                temp[i]=string[i+4];
            }
            searching_times=atoi(temp);                                     //input data about searching times becomes integer type
            if(!strncmp(string,"d",1))
            {
                result=DFS_search(tree, &searching_times);//pass the result using BFS or DFS following to input data
            }
            if(!strncmp(string,"b",1))
            {
                result=BFS_search(tree, searching_times);
            }
            pass_result(i, &result, result_arr);        //pass the result
            free(input);
        }
    return_result(result_arr, how_many_times);          //return result in txt file
    free(result_arr);                                   //free result heep data
}
