#include "header.h"

int main(int argc,char* argv[])
{
	Slist* head = NULL;
	if( argc == 1 )
	{
		printf("Please pass file names through command line arguments\n");
		return 0;
	}
	hash arr[28];
	for(int j=0;j<28;j++)
	{
		arr[j].index = j;
		arr[j].link = NULL;
	}
	int i=1;
	while ( argv[i] != NULL)
	{
		if ( strcmp(strstr(argv[i],"."),".txt") != 0)
		{
			printf("%s is not a txt file\n",argv[i]);
		}
		else
		{
			FILE* fptr = fopen(argv[i],"r");
			if( fptr == NULL)
			{
				printf("%s is not present in current directory\n",argv[i]);
			}
			else
			{
				fseek(fptr,0,SEEK_END);
				int size = ftell(fptr);
				if( size == 0)
				{
					printf("%s File is empty\n",argv[i]);
				}
				else
				{
					if( check(head,argv[i]) != failure)
					{
						if ( insert_list(&head,argv[i]) == success)
						{
							//printf("Inserting successful\n");
						}
					}
					else
					{
						printf("Duplicate file detected %s\n",argv[i]);
					}	
				}
			}
		}
		i++;
	}
	int ch;
	int flag = 0;
	while(1)
	{
		printf("1.Create database\n2.Display Database\n3.Search\n4.Save Database\n5.Update Database\n6.Exit\nEnter your choice: ");
		scanf("%d",&ch);
		char str[50];
		FILE* fptr;
		switch(ch)
		{
			case 1:
				if(flag == 0)
				{
					if( Create(arr,head) == success)
					{
						flag = 1;
						printf("-------------------------------\nDatabase successfully created\n-------------------------------\n");
					}
					else
					{
						printf("-------------------------\n");
						printf("Database creation failed\n");
						printf("-------------------------\n");
					}
				}
				else
				{
					printf("-------------------------------\nDatabase successfully created\n-------------------------------\n");
				}
				break;
			case 2:
				if( Display(arr) == success)
				{
					printf("-----------------------\nDISPLAYED SUCCESSFULLY\n-----------------------\n");
				}
				break;
			case 3:
				printf("Enter the word that you want to search\n");
				str[50];
				getchar();
				scanf("%[^\n]",str);
				Search(arr,str);
				break;
			case 4:
				printf("Enter the output filename: ");
				str[50];
				getchar();
				scanf("%[^\n]",str);
				if( strcmp((strstr(str,".")),".txt") == 0)
				{
					fptr = fopen(str,"w");
					if( Save(arr,fptr) == success)
					{
						printf("-------------------\nSAVED SUCCESSFULLY\n-------------------\n");
					}
					fclose(fptr);
				}
				else
				{
					printf("----------------------------------\n");
					printf("Error: PLEASE PASS ONLY .txt FILE\n");
					printf("----------------------------------\n");
				}
				break;
			case 5:
				printf("Enter the output filename: ");
				getchar();
				scanf("%[^\n]",str);
				if( strcmp(strstr(str,"."),".txt") != 0)
				{
					printf("----------------------------------\n");
					printf("Error: PLEASE PASS .txt FILE ONLY\n");
					printf("----------------------------------\n");
				}
				else
				{
					fptr = fopen(str,"r");
					if(flag == 0)
					{
						if( Update(arr,fptr,&head) == success)
						{
							flag = 1;
							printf("\n---------------------\nUPDATED SUCCESSFULLY\n---------------------\n");
						}
						fclose(fptr);
					}
					else
					{
						printf("\n---------------------\nUPDATED SUCCESSFULLY\n---------------------\n");

					}
				}	
				break;
			case 6:
				return 0;
				break;
		}
	}

}
