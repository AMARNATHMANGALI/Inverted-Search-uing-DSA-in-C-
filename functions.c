#include "header.h"
/* Function to check the duplicate files in the Single linked list*/
Status check(Slist* head,char* str) 
{
	if( head == NULL)
	{
		return success;
	}
	Slist* temp = head;
	while(temp != NULL)
	{
		if (strcmp(str,temp->data) == 0)
		{
			return failure;
		}
		temp = temp->link;
	}
	return success;
}
/*inserting the file names in the list */
Status insert_list(Slist** head,char* str)
{
	Slist* new = malloc(sizeof(Slist));
	if(new == NULL)
	{
		return failure;
	}
	strcpy(new->data,str);
	new->link = NULL;
	if( *head == NULL)
	{
		*head = new;
		return success;
	}
	Slist* temp = *head;
	while(temp->link != NULL)
	{
		temp = temp->link;
	}
	temp->link = new;

	return success;
}
/*Creating the database for the given files*/
Status Create(hash* arr,Slist* head)
{
	char str[100];
	int index;
	Slist* temp = head;
	while(temp != NULL)
	{
		FILE* fptr = fopen(temp->data,"r");
		while((fscanf(fptr,"%s",str)) != EOF)
		{
			index = find_index(str);
			if(arr[index].link == NULL)
			{
				main_node* mnew = malloc(sizeof(main_node));
				if(mnew == NULL)
				{
					printf("Memory allocation failed\n");
					return failure;
				}
				Subnode* snew = malloc(sizeof(Subnode));
				if(snew == NULL)
				{
					printf("Memory allocation failed\n");
					return failure;
				}
				strcpy(mnew->word,str);
				mnew->filecount = 1;
				mnew->slink = snew;
				mnew->mlink = NULL;
				snew->wordcount = 1;
				strcpy(snew->filename,temp->data);
				snew->slink = NULL;
				arr[index].link = mnew;
			}
			else
			{
				int word_flag = 0,file_flag;
				main_node* temp1 = arr[index].link;
				main_node* prev1 = NULL;
				while( temp1 != NULL)
				{
					if( strcmp(temp1->word,str) == 0)
					{
						word_flag = 1;
						file_flag = 0;
						Subnode* temp2 = temp1->slink; 
						Subnode* prev2 = temp1->slink;
						while(temp2 != NULL)
						{
							if( strcmp(temp2->filename,temp->data) == 0)
							{
								temp2->wordcount++;
								file_flag = 1;
								break;
							}
							else
							{
								prev2 = temp2;
								temp2 = temp2->slink;
							}
						}
						if(file_flag == 0)
						{
							Subnode* snew = malloc(sizeof(Subnode));
							if(snew == NULL)
							{
								printf("Memory allocation failed\n");
								return failure;
							}
							strcpy(snew->filename,temp->data);
							snew->slink = NULL;
							snew->wordcount = 1;
							prev2->slink = snew;
						}
					}
					if( word_flag == 1)
					{
						temp1->filecount++;
						break;
					}
					prev1 = temp1;
					temp1 = temp1->mlink;

				}
				if(word_flag == 0)
				{
					main_node* mnew = malloc(sizeof(main_node));
					Subnode* snew = malloc(sizeof(Subnode));
					if(snew == NULL)
					{
						return failure;
					}
					if(mnew == NULL)
					{
						printf("Memory failed\n");
						return failure;
					}
					strcpy(mnew->word,str);
					mnew->filecount = 1;
					mnew->slink = snew;
					mnew->mlink = NULL;
					snew->wordcount = 1;
					strcpy(snew->filename,temp->data);
					snew->slink = NULL;
					if(prev1 == NULL)
					{
						arr[index].link->mlink = mnew;

					}
					else
					{
						prev1->mlink = mnew;
					}

				}
			}

		}
		temp = temp->link;
	}
}
/*Displaying the database*/
Status Display(hash* arr)
{
	main_node* temp1;
	printf("Index\tWord\t\tFile_count\t   Wordcount\t\tFilename\n");

	for(int i=0;i<28;i++)
	{
		main_node* temp2 = arr[i].link;
		if( temp2 != NULL)
		{
			while(temp2 != NULL)
			{
				printf("[%d]\t  %s\t\t %d\t\t\t",i,temp2->word,temp2->filecount);
				Subnode* temp3 = temp2->slink;
				while( temp3 != NULL)
				{
					printf("%d\t\t%s\t",temp3->wordcount,temp3->filename);
					temp3 = temp3->slink;
				}
				temp2 = temp2->mlink;
				printf("\n");
			}
		}
	}
	return success;
}
/*Function to search the user given word*/
Status Search(hash* arr,char* str)
{
	int index = find_index(str);
	main_node* temp = arr[index].link;
	while( temp != NULL)
	{
		if((strcmp(str,temp->word)) == 0)
		{
			printf("-----------------------------------------------------------\n");
			printf("Word %s is present in %d files\n",temp->word,temp->filecount);
			Subnode* stemp = temp->slink;
			for(int i=1;i<=temp->filecount;i++)
			{
				printf("In File: %s %d time/s\n",stemp->filename,stemp->wordcount);
				stemp = stemp->slink;
			}
			printf("-----------------------------------------------------------\n");
			return success;
		}
		temp = temp->mlink;
	}
	printf("--------------------\n");
	printf("GIVEN WORD NOT FOUND\n");
	printf("--------------------\n");
	return success;
}
/* Function to find the index*/
int find_index(char* str)
{

	if( str[0] >= '0' && str[0] <= '9')
	{
		return 26;
	}
	else if( (str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' && str[0] <= 'Z'))
	{
		char ch = tolower(str[0]);
		return (ch - 97);
	}
	else
	{
		return 27;
	}
}
/*Function to save the data into a file*/
Status Save(hash* arr,FILE* fptr)
{
	for(int i=0;i<28;i++)
	{
		if(arr[i].link != NULL)
		{
			main_node* mnew = arr[i].link;
			while( mnew != NULL)
			{
				fprintf(fptr,"#%d;%s;%d;",i,mnew->word,mnew->filecount);
				Subnode* snew = mnew->slink;
				for(int j=1;j<=mnew->filecount;j++)
				{
					fprintf(fptr,"%d;%s;",snew->wordcount,snew->filename);
					snew = snew->slink;
				}
				fprintf(fptr,"#%s","\n");
				mnew = mnew->mlink;
			}
		}
	}
	return success;

}
/*Update the database*/
Status Update(hash* arr,FILE* fptr,Slist **head)
{
	char str[100];
	int index;
	while( fscanf(fptr,"%s",str) != EOF)
	{

		index = atoi(strtok(str+1,";"));
		Update_database(arr,index,head);
	}
	Create(arr,* head);
	return success;
}
Status Update_database(hash* arr,int index,Slist **head)
{
	char str[50];
	main_node* mnew = malloc(sizeof(main_node));
	if( mnew == NULL)
	{
		printf("Memory allocation failed\n");
		return failure;
	}
	strcpy(mnew->word,strtok(NULL,";"));
	mnew->filecount = atoi(strtok(NULL,";"));
	mnew->slink = NULL;
	mnew->mlink = NULL;
	for(int i=1;i<=mnew->filecount;i++)
	{
		Subnode* snew = malloc(sizeof(Subnode));
		if(snew == NULL)
		{
			printf("Memory allocation failed\n");
			return failure;
		}
		snew->slink = NULL;
		snew->wordcount = atoi(strtok(NULL,";"));
		strcpy(snew->filename,(strtok(NULL,";")));

		free_file(head,snew->filename);


		if(mnew->slink == NULL)
		{
			mnew->slink = snew;
		}
		else
		{
			Subnode* trav = mnew->slink;
			while(trav->slink != NULL)
			{
				trav = trav->slink;
			}
			trav->slink = snew;
		}
	}
	if( arr[index].link == NULL)
	{
		arr[index].link = mnew;
	}
	else
	{
		main_node* trav = arr[index].link;
		while(trav->mlink != NULL)
		{
			trav = trav->mlink;
		}
		trav->mlink = mnew;
	}


}
/*Free the linked list*/
Status free_file(Slist **head,char* filename)
{
	Slist* temp = *head;
	Slist* prev = NULL;
	while( temp != NULL)
	{
		if( strcmp(temp->data,filename) == 0)
		{
			Slist* backup = temp->link;
			free(temp);
			if( prev == NULL)
			{
				*head = backup;
			}
			else
			{
				prev->link = backup;
			}
			return 0;

		}
		prev = temp;
		temp = temp->link;
	}

}
