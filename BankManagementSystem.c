
#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>

char accname[30];
int password=1111; //manager ka password, he can change it any time he want

struct bank
{
	int id;
	char name[30];
	char password[12];
	char dob[12];
	char contact[20];
 	struct data
	 {
 		long long balance;
 		long long loan;
 		long long savings;
	 }d;
}a;


//all the function jo program me use huay hain , unko define kia hua hay
void displaymenu();
void accdetails();
void deposit();
void withdraw();
void history();
void manage();


//manager ka login , manager can check all the registered accounts on bank
void manager()
{
	int pass;
	FILE *ptr = fopen("bank.txt","a+");
	printf("\t\t\t\tENTER THE MANAGER PASSWORD : ");
	scanf("%d",&pass);
	if(pass==password)
	{
		printf("\n\t\t\t\tLOGIN SUCCESSFULL\n");
		
		while(fread(&a,sizeof(a),1,ptr)==1)
	{
		printf("ID : %d\tNAME : %s\tCONTACT : %s\n",a.id,a.name,a.contact);
	}
	
	}
	else
	{
		printf("\t\t\t\twrong password\n");
	}
	printf("\t\t\t\tPRESS ANY KEY TO CONTINUE");
	getche();
	fclose(ptr);
}



void create()
{
    FILE *ptr = fopen("bank.txt", "a+"); 
    if (ptr == NULL)
    {
        printf("\t\t\t\tERROR OPENING FILE\n");
        exit(1);
    }
	//id existance ko check krna
    int idExists = 0;
    do
    {
        idExists = 0;
        printf("\t\t\t\tENTER THE ID OF USER (NUMBERS ONLY): ");
        scanf("%d", &a.id);

        
        rewind(ptr);
        //second temporary structure variable bnaya , jo check krega keh main file me kia id exist krti hay ke nai
        struct bank temp;
        while (fread(&temp, sizeof(temp), 1, ptr) == 1)
        {
            if (temp.id == a.id)
            {
                idExists = 1;
                printf("\t\t\t\tTHIS ID IS ALREADY TAKEN. PLEASE ENTER A UNIQUE ID.\n");
                break;
            }
        }
    } while (idExists);

 
    printf("\t\t\t\tENTER THE NAME OF USER: ");
    getchar();
    fgets(a.name, sizeof(a.name), stdin);
    a.name[strcspn(a.name, "\n")] = '\0';

    printf("\t\t\t\tENTER THE PASSWORD OF USER: ");
    scanf("%s", a.password);

    printf("\t\t\t\tENTER THE DATE OF BIRTH (dd-mm-yyyy) OF USER: ");
    scanf("%s", a.dob);

    printf("\t\t\t\tENTER THE CONTACT OF USER: ");
    scanf("%s", a.contact);

    a.d.balance = 0;

    fwrite(&a, sizeof(a), 1, ptr);

    printf("\t\t\t\tACCOUNT CREATED SUCCESSFULLY!\n");
    printf("\t\t\t\tPRESS ANY KEY TO CONTINUE...\n");
    getche();
    fclose(ptr);
}



void login()
{
	char name[30],password[12];
	FILE *ptr = fopen("bank.txt","r+");	
	printf("\t\t\t\tENTER THE NAME OF USER : ");
	fflush(stdin);// removes any garbage value present in stack
	fgets(name,sizeof(name),stdin);
	name[strcspn(name,"\n")] = '\0';
	while(fread(&a,sizeof(a),1,ptr)==1)
	{
		if(strcmp(a.name,name)==0)
		{
			printf("\t\t\t\tACCOUNT FOUND\n\t\t\t\tENTER THE PASSWORD : ");
			fflush(stdin);
			gets(password);
			
			if(strcmp(a.password,password)==0)
			{
				strcpy(accname,name);
				printf("\t\t\t\tLOGGED IN SUCCESSFULL\n");
				displaymenu();
			}
			else
			{
				printf("\t\t\t\tWRONG PASSWORD!\n");
				printf("Enter Any key to continue !!!!!\n"); 
				getche();
				//login();
		
			}
		}
	}
	fclose(ptr);
}




void displaymenu()
{
	int select=1;
	printf("\t\t\t\t1-ACCOUNT DETAILS\n\n");
	printf("\t\t\t\t2-DEPOSIT FUNDS\n\n");
	printf("\t\t\t\t3-WITHDRAW FUNDS\n\n");
	printf("\t\t\t\t4-TRANSACTION HISTORY\n\n");
	printf("\t\t\t\t5-MANAGE ACCOUNT\n\n");
	printf("\t\t\t\t6-LOGOUT\n\n");
	while(select!=6)
	{
		printf("\t\t\t\tPLEASE SELECT THE OPTION ABOVE\n");
	    scanf("%d",&select);
	switch(select)
	{
		case 1:
			accdetails();
			break;
		case 2:
			deposit();
			break;
		case 3:
			withdraw();
			break;
		case 4:
			history();
			break;
		case 5:
			manage();
			break;
		case 6:
			printf("\t\t\t\tSUCCESSFULLY LOGGED OUT\n");
			printf("Press any key to continue.\n");
			getche();
			return;
		default:
			printf("\t\t\t\tINVALID INPUT!\n\n");
			break;					
	}
	}
	return ;
}

void accdetails()
{
	FILE *ptr  = fopen("bank.txt","r+");
	while(fread(&a,sizeof(a),1,ptr)==1)
	{
		if(strcmp(a.name,accname)==0)
		{
			printf("NAME : %s\nTOTAL AMOUNT : %lld\nDATE OF BIRTH : %s\nCONTACT : %s\n",a.name,a.d.balance,a.dob,a.contact);
			printf("\t\t\t\tENTER ANY KEY TO CONTINUE........\n");
			getche();
			system("cls");
			displaymenu();
			break;
		}
	}
//	getche();
//	system("cls");
	fclose(ptr);
}

void deposit()
{
    long long amount = 0;
    FILE *ptr = fopen("bank.txt", "r+");
    FILE *ptr2 = fopen("transactions.txt", "a+");
    if (ptr == NULL || ptr2 == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    long long recsize = sizeof(a);
    rewind(ptr);
    while (fread(&a, sizeof(a), 1, ptr) == 1)
    {
        if (strcmp(a.name, accname) == 0)
        {
            printf("\t\t\t\tENTER AMOUNT TO DEPOSIT: ");
            scanf("%lld", &amount);
            if(amount < 0)
            {
            	printf("SYSTEM ERROR -001: Enter a Valid Amount !\n");
            	Sleep(1000);
            	break;
			}
            a.d.balance += amount;
            fseek(ptr, -recsize, SEEK_CUR); // Move file pointer back to the start of the record
            fwrite(&a, sizeof(a), 1, ptr);
            printf("\t\t\t\tYOUR NEW BALANCE IS %lld\n", a.d.balance);
            fprintf(ptr2, "%s deposited %lld\n", accname, amount);
            printf("\t\t\t\tENTER ANY KEY TO CONTINUE.....\n");
            getche();
            break;
        }
    }
    fclose(ptr);
    fclose(ptr2);
    system("cls");
    displaymenu();
}

void withdraw()
{
    long long amount = 0;
    FILE *ptr = fopen("bank.txt", "r+");
    FILE *ptr2 = fopen("transactions.txt", "a+");
    if (ptr == NULL || ptr2 == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    long long recsize = sizeof(a);
    rewind(ptr);
    while (fread(&a, sizeof(a), 1, ptr) == 1)
    {
        if (strcmp(a.name, accname) == 0)
        {
            printf("\t\t\t\tENTER AMOUNT TO WITHDRAW: ");
            scanf("%lld", &amount);
            if (a.d.balance >= amount)
            {
                a.d.balance -= amount;
                fseek(ptr, -recsize, SEEK_CUR); // Move file pointer back to the start of the record
                fwrite(&a, sizeof(a), 1, ptr);
                printf("\t\t\t\tWITHDRAW SUCCESSFUL\n");
                printf("\t\t\t\tYOUR NEW BALANCE IS %lld\n", a.d.balance);
                fprintf(ptr2, "%s withdrew %lld\n", accname, amount);
            }
            else
            {
                printf("\t\t\t\tINSUFFICIENT FUNDS\n");
            }
            printf("\t\t\t\tENTER ANY KEY TO CONTINUE.....\n");
            getche();
            break;
        }
    }
    fclose(ptr);
    fclose(ptr2);
    system("cls");
    displaymenu();
}


void manage()
{
    int select;
    FILE *ptr = fopen("bank.txt", "r+");
    if (ptr == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    long long recsize = sizeof(a);
    rewind(ptr);
    while (fread(&a, sizeof(a), 1, ptr) == 1)
    {
        if (strcmp(a.name, accname) == 0)
        {
            printf("\t\t\t\tPLEASE SELECT WHAT YOU WANT TO CHANGE:\n1-NAME\n2-PASSWORD\n");
            scanf("%d", &select);
            if (select == 1)
            {
                printf("\t\t\t\tENTER NEW NAME: ");
                getchar();
                fgets(a.name, sizeof(a.name), stdin);
                a.name[strcspn(a.name, "\n")] = '\0';
                fseek(ptr, -recsize, SEEK_CUR);
                fwrite(&a, sizeof(a), 1, ptr);
                strcpy(accname, a.name);
                printf("\nNAME CHANGED SUCCESSFULLY!\n");
                break;
            }
            if (select == 2)
            {
                printf("\t\t\t\tENTER NEW PASSWORD: ");
                scanf("%s", a.password);
                fseek(ptr, -recsize, SEEK_CUR);
                fwrite(&a, sizeof(a), 1, ptr);
                printf("\nPASSWORD CHANGED SUCCESSFULLY!\n");
                break;
            }
        }
    }
    fclose(ptr);
    system("cls");
    displaymenu();
}



void history()
{
    FILE *ptr = fopen("transactions.txt", "r");
    if (ptr == NULL)
    {
        printf("\t\t\t\tERROR: Could not open transactions file.\n");
        printf("\t\t\t\tENTER ANY KEY TO CONTINUE...\n");
        getche();
        system("cls");
        displaymenu();
        return;
    }

    char line[200];
    int count = 0;
    char transactions[10][200];

    while (fgets(line, sizeof(line), ptr) != NULL)
    {
        if (strstr(line, accname) != NULL)
        {
            if (count < 10)
            {
                strcpy(transactions[count], line);
                count++;
            }
            else
            {
                for (int i = 1; i < 10; i++)
                {
                    strcpy(transactions[i - 1], transactions[i]);
                }
                strcpy(transactions[9], line); // Add the latest transaction to the end.
            }
        }
    }

    fclose(ptr);

    printf("\t\t\t\tLAST 10 TRANSACTIONS FOR %s:\n\n", accname);

    if (count == 0)
    {
        printf("\t\t\t\tNO TRANSACTIONS FOUND FOR THIS USER.\n\n");
    }
    else
    {
        for (int i = 0; i < count; i++)
        {
            printf("\t\t\t\t%s", transactions[i]);
        }
    }

    printf("\n\t\t\t\tENTER ANY KEY TO CONTINUE...\n");
    getche();
    system("cls");
    displaymenu();
}




int main()
{
	int select;
	printf("\t\t\t\t||=================================||\n");
	printf("\t\t\t\t\tWELCOME TO CITY BANK\n");
	printf("\t\t\t\t||=================================||\n\n");

	while(1)
	{
	printf("\t\t\t\t  PLEASE SELECT THE OPERATION BELOW\n\n1-CREATE ACCOUNT\n\n2-LOGIN\n\n3-MANAGER LOGIN\n\n4-EXIT\n\n");	
	scanf("%d",&select);
	if(select==1)
	create();
	else if(select==2)
	login();
	else if(select==3)
	manager();
	else if(select==4)
	break;
	system("cls");
	}
}
