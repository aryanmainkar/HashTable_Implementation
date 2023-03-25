// Aryan Mainkar
// 1001844964
// Coding Assignment 6
// CSE 3318-001

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define HASHTABLESIZE 30

typedef struct studentprofile
{
    char *full_name;
    char intial;
    int age;
    int student_id;
    int graduation_year;
    float current_gpa;
    struct studentprofile *nextptr;
}
STUDENTPROFILE;

// Basic Code Outline
int MyHashFunction(char FirstName[])
{
   int asscivalue=0;
   for(int i=0;i<=strlen(FirstName);i++)
   {
     asscivalue = asscivalue + FirstName[i];
   }
   
   return asscivalue%HASHTABLESIZE; 
}


int main(int argc,char*argv[])
{
    char FirstName[20];

    printf("Enter First Name :");
    scanf("%s", FirstName);
 
    printf("The hash value for %s is %d\n",FirstName,MyHashFunction(FirstName));
    return 0;
}

