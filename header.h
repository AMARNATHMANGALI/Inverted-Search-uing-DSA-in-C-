#ifndef header_h
#define header_h

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct node
{
	char data[50];
	struct node* link;					//Structure for the linked list to store the file names
}Slist;

typedef enum
{
	success,
	failure,								//enum for success or failure indication
}Status;
typedef struct _subnode
{
	int wordcount;
	char filename[20];
	struct _subnode* slink;					//subnode structure to store the filename and wordcout
}Subnode;

typedef struct _mainnode
{
	int filecount;
	char word[20];
	Subnode* slink;
	struct _mainnode* mlink;					//mainnode storing the subnode link,filecount,next main node link and word
}main_node;
typedef struct _hashnode
{
	int index;
	main_node* link;						//hash table structure
}hash;

/* All function declarations*/
Status check(Slist* head,char* str);

Status insert_list(Slist** head,char* str);

Status Create(hash *arr,Slist* head);

Status Display(hash* arr);

Status Search(hash* arr,char* str);

int find_index(char* str);

Status Save(hash* arr,FILE* fptr);

Status Update(hash* arr,FILE* fptr,Slist ** head);

Status Update_database(hash* arr,int index,Slist** head);

Status free_file(Slist **head,char* filename);
#endif
