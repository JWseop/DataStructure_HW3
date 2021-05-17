//
//  main.c
//  Data Structure HW3
//
//  Created by 정우섭 on 2021/05/15.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct BST_Node
{
    int visited;
    int value;
    struct BST_Node* leftChild;
    struct BST_Node* rightChild;
}NODE;

NODE* BST_insert(NODE* root, int value)
{
    if(root == NULL)
    {
        root = (NODE*)malloc(sizeof(NODE));
        root->leftChild = NULL;
        root->rightChild = NULL;
        root->value = value;
        root->visited = FALSE;
        return root;
    }
    else
    {
        if(root->value > value)
            root->leftChild = BST_insert(root->leftChild, value);
        else
            root->rightChild = BST_insert(root->rightChild, value);
    }
    return root;
}
/*
NODE* BFS_search(NODE* root, int searching_element_num)
{
    for(int i=0;i<searching_element_num;i++)
    {
        
    }
}

NODE* DFS_search(NODE* root, int searching_element_num)
*/


void pass_result(int result_num,int *result,int result_arr[])
{
    result_arr[result_num]=(*result);
}

void return_result(int result_arr[],int how_many)
{
    FILE *of = fopen("/Users/jungwooseop/모시공/수업자료/자료구조/HW2/output-1.txt","w");
    for(int i=0;i<how_many;i++)
    {
    fprintf(of, "%d\n",result_arr[i]);
    }
    fclose(of);
}

int main()
{
    int length;             //check the length of input expression
    int BST_size;        //input the number of element here
    char temp[7]={0};      //input string data here
    int how_many_times;     //the number of input expression
    int result;             //result of expression
    FILE *fp = fopen("/Users/jungwooseop/모시공/수업자료/자료구조/HW3/input-3.txt","r");
        fscanf(fp, "%d", &how_many_times);
    int *result_arr=(int*)malloc(sizeof(int)*how_many_times);
    
        for(int i=0;i<how_many_times;i++)
        {
            memset(temp, 0, sizeof(char)*7);            //reset temp[]
            fscanf(fp, "%d", &BST_size);                //pass BST size
            int* input=malloc(sizeof(int)*BST_size);    //allocate heep memory as long as input BST size
            fscanf(fp, "%s", temp);                     //pass string input data to temp[]
            NODE* root= NULL;
            for(int j=0;j<BST_size;j++)                 //input elements in array
            {
                fscanf(fp, "%d",&input[j]);
                BST_insert(root, input[j]);             //construct BST form
            }
            //result=search;             //operate DFS or BFS
            pass_result(i, &result, result_arr);        //pass the result
            free(input);
        }
    return_result(result_arr, how_many_times);          //return result in txt file
    free(result_arr);                                   //free result heep data
}
//케이스가 몇 개인지 받음
//이번 케이스의 원소 수 입력받음, 입력된 3개의 str에 따라 다른 함수 실행, 함수안의 num만큼 노드 찾기 반복.
//큐에다가 인풋 num 저장
