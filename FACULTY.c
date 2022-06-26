#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
COORD coord = {0,0};
void gotoxy(int x,int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
int main()
{
    FILE *fp, *ft;
    char another, choice;
    struct faculty
    {
        char code[10];
        char fname[40];
        char lname[40];
        int age;
        float bs;
        char deg[25];
        char sub[20];
        int exp;
        char ph[15];
    };
    struct faculty f;
    char empcode[5];
    long int recsize;
    fp = fopen("EMP.DAT","r+");
    if(fp == NULL)
    {
        fp = fopen("EMP.DAT","w+");
        if(fp == NULL)
        {
            printf("Connot open file");
            exit(1);
        }
    }
    recsize = sizeof(f);
    while(1)
    {
        system("cls");
        gotoxy(30,6);
        printf("WELCOME TO FACULTY MANAGEMENT SYSTEM");
        gotoxy(36,7);
        printf("CREATED BY TEAM TECHNO");
        gotoxy(38,10);
        printf("1. Add Record");
        gotoxy(38,12);
        printf("2. List Records");
        gotoxy(38,14);
        printf("3. List Specific Record");
        gotoxy(38,16);
        printf("4. Modify Record");
        gotoxy(38,18);
        printf("5. Delete Record");
        gotoxy(38,20);
        printf("6. Exit");
        gotoxy(30,22);
        printf("Your Choice: ");
        fflush(stdin);
        choice  = getche();
        switch(choice)
        {
            //ADD RECORDS
        case '1':
            system("cls");
            fseek(fp,0,SEEK_END);
            another = 'y';
            while(another == 'y')
            {
                printf("\nEnter Faculty Code: ");
                scanf("%s",f.code);
                printf("\nEnter First Name: ");
                scanf("%s",f.fname);
                printf("\nEnter Last Name: ");
                scanf("%s",f.lname);
                printf("\nEnter Age: ");
                scanf("%d", &f.age);
                printf("\nEnter Basic Salary: ");
                scanf("%f", &f.bs);
                printf("\nEnter Qualification: ");
                scanf("%s",f.deg);
                printf("\nEnter Subject: ");
                scanf("%s",f.sub);
                printf("\nEnter Experience: ");
                scanf("%d",&f.exp);
                printf("\nEnter Contact Number: ");
                scanf("%s",f.ph)
                ;fwrite(&f,recsize,1,fp);
                printf("\nPRESS ANY KEY TO GO BACK TO MAIN SCREEN");
                fflush(stdin);
                another = getche();
            }
            break;
            //LIST RECORDS
        case '2':
            system("cls");
            rewind(fp);
            printf("FACULTY DETAILS:\n");
            while(fread(&f,recsize,1,fp)==1)
            {
                printf("\nFACULTY CODE: %s\nNAME: %s %s\nAGE: %d YEARS\nBASIC SALARY: Rs. %.2f\nQUALIFICATION: %s\nSUBJECT: %s\nEXPERIENCE: %d YEARS\nCONTACT NUMBER: %s\n",f.code,f.fname,f.lname,f.age,f.bs,f.deg,f.sub,f.exp,f.ph);
            }
            getch();
            break;
            //LIST SPECIFIC RECORD
            case '3':
            system("cls");
            another = 'y';
            while(another == 'y')
            {
                printf("Enter the FACULTY CODE to list details: ");
                scanf("%s", empcode);
                rewind(fp);
                while(fread(&f,recsize,1,fp)==1)
                {
                    if(strcmp(f.code,empcode) == 0)
                    {
                        printf("\nFACULTY CODE: %s\nNAME: %s %s\nAGE: %d YEARS\nBASIC SALARY: Rs. %.2f\nQUALIFICATION: %s\nSUBJECT: %s\nEXPERIENCE: %d YEARS\nCONTACT NUMBER: %s\n",f.code,f.fname,f.lname,f.age,f.bs,f.deg,f.sub,f.exp,f.ph);
                        fseek(fp,-recsize,SEEK_CUR);
                        fwrite(&f,recsize,1,fp);
                        break;
                    }
                }
                printf("\nPRESS ANY KEY TO GO BACK TO MAIN SCREEN");
                fflush(stdin);
                another = getche();
            }
            break;
            //MODIFY RECORDS
        case '4':
            system("cls");
            another = 'y';
            while(another == 'y')
            {
                printf("Enter the FACULTY CODE to modify: ");
                scanf("%s", empcode);
                rewind(fp);
                while(fread(&f,recsize,1,fp)==1)
                {
                    if(strcmp(f.code,empcode) == 0)
                    {
                        printf("\nEnter First Name: ");
                        scanf("%s",f.fname);
                        printf("\nEnter Last Name: ");
                        scanf("%s",f.lname);
                        printf("\nEnter Age: ");
                        scanf("%d", &f.age);
                        printf("\nEnter Basic Salary: ");
                        scanf("%f", &f.bs);
                        printf("\nEnter Qualification: ");
                        scanf("%s",f.deg);
                        printf("\nEnter Subject: ");
                        scanf("%s",f.sub);
                        printf("\nEnter Experience: ");
                        scanf("%d",&f.exp);
                        printf("\nEnter Contact Number: ");
                        scanf("%s",f.ph);
                        fseek(fp,-recsize,SEEK_CUR);
                        fwrite(&f,recsize,1,fp);
                        break;
                    }
                }
                printf("SUCCESSFULLY MODIFIED THE FACULTY DETAILS!!");
                printf("\nPRESS ANY KEY TO GO BACK TO MAIN SCREEN");
                fflush(stdin);
                another = getche();
            }
            break;
            //DELETE RECORDS
        case '5':
            system("cls");
            another = 'y';
            while(another == 'y')
            {
                printf("\nEnter FACULTY CODE of faculty to be deleted: ");
                scanf("%s",empcode);
                ft = fopen("Temp.dat","w");
                rewind(fp);
                while(fread(&f,recsize,1,fp) == 1)
                {
                    if(strcmp(f.code,empcode) != 0)
                    {
                        fwrite(&f,recsize,1,ft);
                    }
                }
                fclose(fp);
                fclose(ft);
                remove("EMP.DAT");
                rename("Temp.dat","EMP.DAT");
                fp = fopen("EMP.DAT", "r+");
                printf("SUCCESSFULLY DELETED THE FACULTY DETAILS!!");
                printf("\nPRESS ANY KEY TO GO BACK TO MAIN SCREEN");
                fflush(stdin);
                another = getche();
            }
            break;
            //EXIT
        case '6':
            printf("\nTHANKS FOR USING THE SYSTEM");
            fclose(fp);
            exit(0);
            break;
        default:
            gotoxy(34,24);
            printf("SORRY! WRONG INPUT");
            gotoxy(34,25);
            printf("PLEASE TRY AGAIN!!");
            getch();
            break;
        }
    }
    return 0;
}
