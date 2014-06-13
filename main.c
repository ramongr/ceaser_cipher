#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "cipher.h"

#define MAX 200
#define UNDEF -1
#define CODE 1
#define ONFILE 1
#define DECODE 0
#define SCREEN 0

/*This is the Caesar's Cipher main file. Coded by :
 * grramon - Ramon Rodrigues author of The Coding
 * thecoding.wordpress.com
 * [2012]
 * You're free to modify, update and use the functions bellow anyway you want
 * do not remove previous developers information, and make sure your version's
 * available for everybody in the WWW.*/

String s;

void file_get(char fname[])
{
	int i=0;
	int j;
	FILE *fp;
	
	fp=fopen(fname,"r");
	
	while(!feof(fp))
	{
		if(s->size<i)
		{
			char *new=(char *)malloc(sizeof(char)*s->size*2);
			
			for(j=0;s->size>j;new[j]=s->string[j++]);
			
			free(s->string);
			s->string=new;
			s->size=s->size*2;
		}
		
		s->string[i]=fgetc(fp);
		i++;
	}
	
	fclose(fp);
}


void file_io(char *args[],char iname[],char outname[],int c)
{
	c=UNDEF;
	do
	{
		system("clear");
		
		if(!args[2])
		{
			printf("Insert input file here:\n");
			fgets(iname,50,stdin);
			iname[strlen(iname)-1]='\0';
		}
		else
		{
			iname="";
		}
		
		printf("Insert output file here or leave blanc:\n");
		fgets(outname,50,stdin);

	}while(strlen(outname)<1);
	
	if(strlen(outname)>2)
	{
		outname[strlen(outname)-1]='\0';
		c=ONFILE;
	}
	else
	{
		c=SCREEN;
	}
	
}

void screen_io(int c)
{	
	do
	{
		system("clear");
		printf("Message: (200 char max.)\n");
		fgets(s->string,200,stdin);
		printf("1 to code 2 to decode \n");
		scanf("%d",&c);
		
		switch(c)
		{
			case 1 : c=CODE;break;
			case 2 : c=DECODE;break;
			default : c=CODE;break;
		}
	}while(c==UNDEF);
}

/* This is the code/decode function. Since they are so similar
 * there is no need to do two functions. When we are coding the message
 * delta is the value that the user input, when we decode delta is the 
 * value delta=26-delta' assuming delta' is the value the user input.*/
void code(int delta)
{
    int i;
    
    for(i=0;i<s->size && s->string[i]!='\0';i++)
    {
        if(isupper(s->string[i]))
        {
            if(s->string[i]+delta>'Z')
            {
                s->string[i]='A'-1+(s->string[i]+delta-'Z');
            }
            else
            {
                s->string[i]=s->string[i]+delta;
            }
        }
        if(islower(s->string[i]))
        {
            if(s->string[i]+delta>'z')
            {
                s->string[i]='a'-1+(s->string[i]+delta-'z');
            }
            else
            {
                s->string[i]=s->string[i]+delta;
            }
        }
    }
}

/* Simple FILE printing function
 * Returns coded/decoded message*/
void retfile(char outname[])
{
	FILE *fp;
	
	fp=fopen(outname,"w");
	
	fprintf(fp,"%s",s->string);
	fclose(fp);
}

/*Simple pretty printing function
 * Returns coded/decoded message*/
void retscreen()
{
    printf("Output:\n");
    printf("%s",s->string);
}

int delta_io()
{
	int c=3;
	
	do
	{
		system("clear");
		printf("Press 1 to code or 2 to decode\n");
		scanf("%d",&c);
	}while(c>2);
	
	switch(c)
	{
		case 1 : return CODE;break;
		case 2 : return DECODE;break;
	}
}

/*Pre-condition:
 * strlen(delta_str[])>0*/
int calcdelta(char delta_str[], int c)
{
    int delta;
    if(delta_str[0]<'9')
    {
        delta=atoi(delta_str);
    }
    
    if(delta_str[0]>97)
    {
        delta=delta_str[0]-'a';
    }
    if(delta_str[0]>65)
    {
        delta=delta_str[0]-'A';
    }
    if(delta>26)
    {
        delta=delta%26;
    }
    
    return (c==CODE) ? delta++ : 26-delta;
}
/*Post-condition:
 * delta>0*/
 
/*Pre-conditions:
 * There are none at the moment*/
int main(int argc, char *argv[])
{
	int out=UNDEF, choice=UNDEF, choice_code=UNDEF, delta=0;
	
	char delta_str[3];
	char iname[50]="";
	char outname[50]="";
	
	s=(String)malloc(sizeof(DString));
	s->size=MAX;
	s->string=(char *)malloc(sizeof(char)*s->size);
	
	
	if(!argv[1])
	{
		screen_io(choice);
		out=SCREEN;
	}
	else
	{
		file_io(argv,iname,outname,out);
		
		switch(strcmp(argv[1],"filecode"))
		{
			case 0 :choice_code=CODE;break;
			default: choice_code=DECODE;break;
		}
		
		if(strlen(iname)>0)
		{
			file_get(iname);
		}
		else
		{
			file_get(argv[2]);
		}
	}
	
	if(!choice_code)
	{
		choice_code=delta_io();
	}
	
	getchar();
	printf("Insert shift from A \n");
	fgets(delta_str,3,stdin);
	
	delta=calcdelta(delta_str,choice);
	code(delta);
	
	switch(out)
	{
		case SCREEN : retscreen();break;
		default : retfile(outname);break;
	}
	
	free(s->string);
	free(s);
    return 0;
}
