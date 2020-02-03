#include<stdio.h>
#include<string.h>

struct symtab{
	char symbol[10];
	int add,length;
};

struct littab{
	char literal[10];
	int add;
};

char pooltab[20];

struct ic{
	char class_code[20],C,sym_lit;
	int constant1,constant2,machine_code,lc;
};

int LC=0,PTP=0,LTP=0,STP=0,RC=0,ic_ptr=0;
struct ic i_counter[20];
struct symtab s[20];
struct littab l[20];

void disp(char *line)
{
	printf("hii");
	int count=0;
	char* token = strtok(line, "\t");

	char buff[20];
    while (token != NULL) {
    	strcpy(buff,token);
    	if(count==0)
    		sscanf(buff,"%d",&i_counter[ic_ptr].lc);

    	else if(count==1)
    		sscanf(buff,"%s",i_counter[ic_ptr].class_code);

    	else if(count==2)
    		sscanf(buff,"%d",&i_counter[ic_ptr].machine_code);

    	else if(count==3)
    	{
    		//printf("\nbuff::%s len::%d",buff,strlen(buff));
    		sscanf(buff,"%c",i_counter[ic_ptr].C);
    		//printf("\nin ic_ptr ::%c",i_counter[ic_ptr].C);
    	}

    	else if(count==4)
    		sscanf(buff,"%d",&i_counter[ic_ptr].constant1);

    	else if(count==5)
    		sscanf(buff,"%c",i_counter[ic_ptr].sym_lit);

    	else if(count==6)
    		sscanf(buff,"%d",&i_counter[ic_ptr].constant2);

        count++;
        strcpy(buff,"NULL");
        printf("%s\n",token);
        token = strtok(NULL, "\t");
    }
    ic_ptr++;
}

void pre_process()
{
	FILE *f=NULL,*f1=NULL;
	char ch;
	f=fopen("Copy of output.txt","r");
	f1=fopen("intermediate_code.txt","w");
	if(f==NULL || f1==NULL)
	{
		printf("\nError in opening file!!");
	}
	else
	{
		while((ch=fgetc(f))!=EOF)
		{
			if(ch==',')
			{
				fprintf(f1,"\t");
			}
			else if(ch!='(' && ch!=')')
			{
				fprintf(f1, "%c",ch);
			}
		}
	}
	fclose(f);
	fclose(f1);
}
//copy tables from file to structure
void copy_from_file()
{
	char *line = NULL;
	size_t len = 0;
    ssize_t nread;
    int counter=0,i=0;

	FILE *fptr=NULL;
	fptr=fopen("symtab.txt","r");

	if(fptr==NULL)
	{
		printf("\nFailed to open file to read!!");
	}
	else
	{
		 while(fscanf(fptr,"%s %d %d",s[i].symbol,&s[i].add,&s[i].length)!=EOF)
		 {
		 	printf("%s\t%d\t%d\n",s[i].symbol,s[i].add,s[i].length);
		 	i++;
		 }
   	}
	fclose(fptr);
	i=0;
	fptr=fopen("littab.txt","r");

	if(fptr==NULL)
	{
		printf("\nFailed to open file to read!!");
	}
	else
	{
		 while(fscanf(fptr,"%s %d",l[i].literal,&l[i].add)!=EOF)
		 {
		 	printf("%s\t%d\n",l[i].literal,l[i].add);
		 	i++;
		 }
   	}
	fclose(fptr);
	i=0;
	fptr=fopen("pooltab.txt","r");

	if(fptr==NULL)
	{
		printf("\nFailed to open file to read!!");
	}
	else
	{
		 while(fscanf(fptr,"%d",&pooltab[i])!=EOF)
		 {
		 	printf("%d\n",pooltab[i]);
		 	i++;
		 }
   	}
	fclose(fptr);

	i=0;

	pre_process();
	fptr=fopen("intermediate_code.txt","r");

	if(fptr==NULL)
	{
		printf("\nFailed to open file to read!!");
	}
	else
	{
		while ((nread = getline(&line, &len, fptr)) != -1)
		{
			counter++;
           printf("\n\nRetrieved line %d of length %zu:",counter, nread);
           disp(line);
        }

        for(int j=0;j<ic_ptr;j++)
        {
        	printf("\n%d %s %d %c %d %c %d",i_counter[j].lc,i_counter[j].class_code,i_counter[j].machine_code,i_counter[j].C,i_counter[j].constant1,i_counter[j].sym_lit,i_counter[j].constant2);
        }
   	}
	fclose(fptr);
}
int main()
{
	copy_from_file();
	return 0;
}
