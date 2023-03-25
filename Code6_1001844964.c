//Coding Assignment 6
//Aryan Mainkar
//1001844964
//CSE-3318-001

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
 
#define HASHTABLESIZE 30
#define MAXNAMESTRING 100

typedef struct studentprofile
{
    char *full_name;
    char intial;
    int age;
    int student_id;
    int graduation_year;
    float current_gpa;
    struct studentprofile *next_ptr;
    
}
STUDENTPROFILE;
 
int CalculateHashIndex(char *key)
{
    int HashIndex = 0;
	
    for(int i = 0; i < strlen(key); i++)
    {
	    HashIndex += key[i];
    }
	
    return HashIndex %= HASHTABLESIZE; 
}

void AddNode(STUDENTPROFILE *NewNode, STUDENTPROFILE *Stdinfo[])
{
    int HashIndex = CalculateHashIndex(NewNode->full_name);
	
    if(Stdinfo[HashIndex] == NULL) 
    {
	    #if PRINTINSERT
	        printf("\nInserting %s at index %d\n", NewNode->full_name, HashIndex);
	    #endif
	    Stdinfo[HashIndex] = NewNode;
    }
    else   
    {
	    STUDENTPROFILE *TempPtr = Stdinfo[HashIndex];
	
		
	    while(TempPtr->next_ptr != NULL) 
	    {
		    TempPtr = TempPtr->next_ptr;
        }
	    TempPtr->next_ptr = NewNode;
	    #if PRINTINSERT
	        printf("\nInserting %s at index %d\n", NewNode->full_name, HashIndex);
	    #endif
    }
}

void FreeDynamicMemory(STUDENTPROFILE *Stdinfo[])
{
    STUDENTPROFILE *TempPtr = NULL, *NextPtr = NULL;
	
    for(int i = 0; i < HASHTABLESIZE; i++)
    {
	    TempPtr = Stdinfo[i];
 
	    if(TempPtr != NULL) 
	    {
		    while(TempPtr != NULL) 
		    {
			    free(TempPtr->full_name);
			    NextPtr = TempPtr->next_ptr;
			    free(TempPtr);
			    TempPtr = NextPtr;
		    }	
	    }
    }
}

int DeleteNode(STUDENTPROFILE *Stdinfo[])
{
    char LookupName[MAXNAMESTRING] = {};
    int result = 0;
	
    fgets(LookupName,sizeof(LookupName)-1,stdin);
    printf("Enter the full name of the Student to delete from the Student Profile:");
    fgets(LookupName,MAXNAMESTRING,stdin);

    if(LookupName[strlen(LookupName)-1] == '\n')
    {
        LookupName[strlen(LookupName)-1] = '\0';
    }
	
    int HashIndex = CalculateHashIndex(LookupName);
    STUDENTPROFILE *TempPtr = Stdinfo[HashIndex];
    STUDENTPROFILE *PrevPtr = NULL;
 
    if(TempPtr == NULL) 
    {
	    printf("\n\nStudent's full name %s does not exist in the Student Profile\n\n", LookupName);
	    result = 0;
    }
	
    else 
    {
	    while(TempPtr != NULL) 
	    {
		    if(strcmp(TempPtr->full_name, LookupName) == 0)
		    {
			    if (TempPtr == Stdinfo[HashIndex])
			    {
				    Stdinfo[HashIndex] = TempPtr->next_ptr;
				    printf("\nStudent's full name %s has been deleted from the Student profile\n\n", TempPtr->full_name);
				    free(TempPtr);
				    TempPtr = NULL;
			    }
				
			    else
			    {
				    PrevPtr->next_ptr = TempPtr->next_ptr;
				    printf("\nStudent's full name %s has been deleted from the Student profile\n\n", TempPtr->full_name);
				    free(TempPtr);
				    TempPtr = NULL;
			    }
			    result = 1;
		    }
			
		    else
		    {
			    PrevPtr = TempPtr;
			    TempPtr = TempPtr->next_ptr;
		    }
	    }
		
	    if(result == 0)
	    {
		    printf("\n\nStudent's full name %s does not exist in the Student profile\n\n", LookupName);
	    }
    }
    return result;
}

void DisplayHashTable(STUDENTPROFILE *Stdinfo[])
{
    int i;
    STUDENTPROFILE *TempPtr = NULL;
	
    for(i = 0; i < HASHTABLESIZE; i++) 
    {
	    TempPtr = Stdinfo[i];
	    printf("\nStdinfo[%d]-", i);
		
	    if(TempPtr != NULL) 
        {
		    while(TempPtr != NULL)
		    {
			    printf("%s|", TempPtr->full_name);
			    TempPtr = TempPtr->next_ptr;
		    }
	    }
    }
}

void ShowByLetter(STUDENTPROFILE *Stdinfo[])
{
    int i;
    STUDENTPROFILE *TempPtr = NULL;
    char LookupLetter = 'A';

    printf("\n\nEnter a letter of the alphabet ");
    scanf(" %c", &LookupLetter);
    LookupLetter = toupper(LookupLetter);

    for(i = 0; i < HASHTABLESIZE; i++) 
    {
	    TempPtr = Stdinfo[i];

	    if(TempPtr != NULL) 
	    {
		    while(TempPtr != NULL)
		    {
			    if(toupper(TempPtr->full_name[0]) == LookupLetter)
			    {
				    printf("%s\n", TempPtr->full_name);
			    }
			    TempPtr = TempPtr->next_ptr;
		    }
	    }
    }
}

void ShowByName(STUDENTPROFILE *Stdinfo[])
{
    STUDENTPROFILE *TempPtr = NULL;
    char LookupName[MAXNAMESTRING] = {};
    int FoundIt = 0;
    
	fgets(LookupName,sizeof(LookupName)-1,stdin);
    printf("\n\nEnter Student's full name:");
    fgets(LookupName,MAXNAMESTRING,stdin);

    if(LookupName[strlen(LookupName)-1] == '\n')
    {
        LookupName[strlen(LookupName)-1] = '\0';
    }
	
    #if TIMING
        clock_t start, end;
        start = clock();
    #endif
	
    for(int i = 0; i < HASHTABLESIZE; i++) 
    {
	    TempPtr = Stdinfo[i];

	    if (TempPtr != NULL) 
	    {
		    while (TempPtr != NULL)
		    {
			    if (strcmp(TempPtr->full_name, LookupName) == 0)
			    {
				    #if TIMING
				        end = clock();
					    printf("\n\nSearch took %ld tics\n\n", end-start);
				    #endif

				    FoundIt = 1;
				    printf("\n\nFull Name : %s\n", TempPtr->full_name);
				    printf("Intial : %c\n", TempPtr->intial);
				    printf("Age : %d\n", TempPtr->age);
				    printf("Student ID :%d\n",TempPtr->student_id);
				    printf("Graduation Year: %d\n", TempPtr->graduation_year);
				    printf("GPA : %0.2f\n", TempPtr->current_gpa);
			    }  
				TempPtr = TempPtr->next_ptr;
		    }
	    }
    }
	
    if(FoundIt == 0)
	    printf("\n\nStudent %s not found in Student Profile\n\n", LookupName);
}

void AddNewStudent(STUDENTPROFILE *Stdinfo[])
{
    int HashIndex = 0;
    STUDENTPROFILE *NewNode;
    char TempBuffer[MAXNAMESTRING] = {};
    
	fgets(TempBuffer,sizeof(TempBuffer)-1,stdin);
    NewNode = malloc(sizeof(STUDENTPROFILE));
    NewNode->next_ptr = NULL;

    printf("\n\nEnter new Student's full name:");
    fgets(TempBuffer,sizeof(TempBuffer),stdin);
   
    if(TempBuffer[strlen(TempBuffer)-1] == '\n')
    {
        TempBuffer[strlen(TempBuffer)-1] = '\0';
    }
   
    NewNode->full_name = malloc(strlen(TempBuffer)*sizeof(char)+1);
    strcpy(NewNode->full_name, TempBuffer);

    printf("Enter %s's intial:", NewNode->full_name);
    scanf("%c", &(NewNode->intial));

    printf("\n\nEnter %s's age:", NewNode->full_name);
    scanf("%d", &(NewNode->age));
	
    printf("\n\nEnter %s's student id:", NewNode->full_name);
    scanf("%d", &(NewNode->student_id));

    printf("\n\nEnter %s's graduation year:", NewNode->full_name);
    scanf("%d", &(NewNode->graduation_year));

    printf("\n\nEnter %s's gpa:", NewNode->full_name);
    scanf("%f", &(NewNode->current_gpa));

    fgets(TempBuffer, sizeof(TempBuffer)-1, stdin);
    AddNode(NewNode, Stdinfo);
}

int ReadFileIntoHashTable(int argc, char *argv[], STUDENTPROFILE *Stdinfo[])
{
    FILE *FH = NULL;
    char FileLine[MAXNAMESTRING] = {};
    char *token = NULL;
    int counter = 0;
    int HashIndex = 0;
    STUDENTPROFILE *NewNode;
    
    if(argc > 1)
    {
	    FH = fopen(argv[1], "r");

	    if(FH == NULL)
	    {
		    perror("Exiting ");
		    exit(0);
	    }

	    while(fgets(FileLine, sizeof(FileLine)-1, FH))
	    { 
		    token = strtok(FileLine, "|");

		    NewNode = malloc(sizeof(STUDENTPROFILE));
		    NewNode->next_ptr = NULL;
			
		    NewNode->full_name = malloc(strlen(token)*sizeof(char)+1);
		    strcpy(NewNode->full_name, token);

		    token = strtok(NULL, "|");
		    NewNode->intial = *token;
			
		    token = strtok(NULL, "|");
		    NewNode->age = atof(token);
			
		    token = strtok(NULL, "|");
		    NewNode->student_id = atof(token);

		    token = strtok(NULL, "|");
		    NewNode->graduation_year = atoi(token);
			
		    token = strtok(NULL, "|");
		    NewNode->current_gpa = atoi(token);

		    AddNode(NewNode, Stdinfo);
		    counter++;
		
	    }

    }
	
    else
    {
	    printf("File must be provided on command line...exiting\n");
	    exit(0);
    }
	
    fclose(FH);
    return counter;	
}

int main(int argc, char *argv[]) 
{
    int MenuChoice = 0;
    int counter = 0;	
    STUDENTPROFILE *Stdinfo[HASHTABLESIZE] = {};

    enum Menu {SHOWBYLETTER=1, SHOWBYNAME, COUNT, DISPLAY, ADD, DELETE, EXIT};
 
    counter = ReadFileIntoHashTable(argc, argv, Stdinfo);
    
    do
    {
		
	    printf("\n\nStudent Profile Menu\n\n"
			    "1. Show all Students in Student Profile for a given letter\n"
			    "2. Look up Student by full name\n"
			    "3. How many Students are in the Student Profile?\n"
			    "4. Display the Student Profile\n"
			    "5. Add a new Student\n"
			    "6. Delete a Student from the Student Profile\n"
			    "7. Exit\n\n"
			    "Enter menu choice: ");
	
	    scanf("%d", &MenuChoice);
	    printf("\n\n");
        
		
	    switch(MenuChoice)
	    {	
		    case SHOWBYLETTER:
			    ShowByLetter(Stdinfo);
			    break;
		    case SHOWBYNAME:
			    ShowByName(Stdinfo);
			    break;
		    case COUNT:
			    printf("Your Student Profile contains %d Students\n", counter); 
			    break;
 		    case DISPLAY:
			    DisplayHashTable(Stdinfo);
			    break;
		    case ADD:
			    AddNewStudent(Stdinfo);
			    counter++;
			    break;
		    case DELETE:
			    if(DeleteNode(Stdinfo))
			    {
				    counter--;
			    }
			    break;
		    case EXIT:
			    break;
		    default : 
			    printf("Invalid menu choice\n\n"); 
	    }
    }
    while(MenuChoice != EXIT);
	
    FreeDynamicMemory(Stdinfo);

    return 0;
}			  
