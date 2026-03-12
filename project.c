// Bank Management System

#include <stdio.h>  //printf(),scanf()
#include <stdlib.h> //exit(0),system()
#include <conio.h>  //getch()
#include <time.h>   //time(),ctime()
#include <string.h> //strcpy()

struct Account {
    char Name[20];
    int Age;
    char Status[10];
    char Type[20];
    float Balance;
    int Acc_No;
};

int dip_amt, amt=10000, acc_no, ac, count = 0; // Global variables
int trans_amt;
int with_amt;
struct Account acc;
FILE *ptr;
void create();
void deposit_money();
void withdraw_money();
void transfer_money();
void interest();
void exit_program();
void transaction_details();
void menu();

void divider()
{
    for (int i = 0; i < 50; i++)
    {
        printf("-");
    }
}

//#Driver function
int main()
{
    ptr = fopen("Account.txt", "w");

    int ch;
    fclose(ptr);
    while (1)
    {
        menu();
        printf("\nEnter your choice :\n");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            create();
            break;

        case 2:
            deposit_money();
            break;

        case 3:
            withdraw_money();
            break;

        case 4:
            transfer_money();
            break;

        case 5:
            interest();
            break;

        case 6:
            transaction_details();
            break;

        case 7:
            exit_program();
            exit(0);

        default:
            printf("*****Invalid choice*****");
        }
    }

    return 0;
}

void menu()
{
    divider();
    printf("\n\tMENU\n");

    divider();
    printf("\n1.Create Account\n");
    printf("2.Deposit Money\n");
    printf("3.Withdraw Money\n");
    printf("4.Transfer Money\n");
    printf("5.interest\n");
    printf("6.Transaction details\n");
    printf("7.Exit\n");
    divider();
}

//!---------------------------------------------------------

void create() {
    struct Account acc;
    FILE *fp = fopen("bank.dat", "ab");

    // Input Details
    printf("Enter Name: "); 
    scanf("%s", acc.Name);
    printf("Enter Age: ");
    scanf("%d", &acc.Age);

    // Age < 18? Logic
    if (acc.Age < 18) {
        strcpy(acc.Status, "Minor");
        printf("Account Status: Minor\n");
    } else {
        strcpy(acc.Status, "Adult");
        printf("Account Status: Adult\n");
    }

    // Select Type
    printf("Enter Account Type (Savings/Current): ");
    scanf("%s", acc.Type);
    
    printf("Enter Initial Balance: ");
    scanf("%f", &acc.Balance);

    // Assign Acc_No (Simple random/manual)
    printf("Assign Account Number: ");
    scanf("%d", &acc.Acc_No);

    // Save to File
    fwrite(&acc, sizeof(struct Account), 1, fp);
    fclose(fp);
    printf("Account Created Successfully!\n");
}

//!---------------------------------------------------------

void deposit_money()
{

    time_t tm;
    time(&tm);
    FILE *ptr = fopen("Account.txt", "a");
    printf("*****DEPOSITING MONEY*****\n");
    for (int i = 0; i < 50; i++)
    {
        printf("-");
    }

    printf("\nEnter the amount you want to deposit\n");
    scanf("%d", &dip_amt);
    amt+=dip_amt;
    printf("****Money Deposited****\n");
    printf("Now balance : %d\n", amt);
    fprintf(ptr, "\nRs%d had been deposited to your account \n", dip_amt);
    fprintf(ptr, "Date/Time of transaction :  %s\n", ctime(&tm));
    count++;

    fclose(ptr);
    printf("Press any key....\n");
    getch();
}

//!---------------------------------------------------------

void withdraw_money()
{

    time_t tm;
    time(&tm);
    FILE *ptr = fopen("Account.txt", "a");
    printf("*****WITHDRAWING MONEY*****\n");
    for (int i = 0; i < 50; i++)
    {
        printf("-");
    }

    printf("\nEnter the amount you want to withdraw\n");
    scanf("%d", &with_amt);

    if (amt < with_amt)
    {
        printf("****Insufficient balance****\n");
    }
    else
    {
        amt = amt - with_amt;
        printf("*****Money withdrawn*****\n");
        printf("Current balance : %d\n", amt);
        fprintf(ptr, "\nRs%d had been withdrawn from your account \n", with_amt);
        fprintf(ptr, "Date/Time of transaction :  %s\n", ctime(&tm));
        count++;
    }
    fclose(ptr);
    printf("Press any key....\n");

    getch();
}

//!---------------------------------------------------------

void transfer_money()
{

    time_t tm;
    time(&tm);
    FILE *ptr = fopen("Account.txt", "a");
    printf("*****TRANSFERRING MONEY*****\n");
    for (int i = 0; i < 50; i++)
    {
        printf("-");
    }

    printf("\nEnter the account no. in which you want to transfer the money : ");
    scanf("%d", &ac);
    printf("\nEnter the amount you want to transfer\n");
    scanf("%d", &trans_amt);

    if (amt < trans_amt)
    {
        printf("****You have not sufficient balance****\n");
    }
    else
    {
        amt = amt - trans_amt;
        printf("****Money Transferred****\n");
        printf("Current balance : %d\n", amt);
        fprintf(ptr, "\nRs%d had been transferred from your account to %d\n", trans_amt, ac);
        fprintf(ptr, "Date/Time of transaction :  %s\n", ctime(&tm));
        count++;
    }
    fclose(ptr);
    printf("Press any key....\n");
    getch();
}

//!---------------------------------------------------------

void interest() {
    struct Account acc;
    int search_acc, found = 0;
    float T, R = 5.0; // Assume Rate R = 5%
    FILE *fp = fopen("bank.dat", "rb+");

    // Input Acc_No, Years (T)
    printf("******CALCULATING INTEREST*****\n");
    printf("Enter Account Number: ");
    scanf("%d", &search_acc);
    printf("Enter Years (T): ");
    scanf("%f", &T);

    // Search, Get Type
    while(fread(&acc, sizeof(struct Account), 1, fp)) {
        if(acc.Acc_No == search_acc) {
            found = 1;
            // Calculate Interest: I = P*R*T/100
            float interest_amt = (acc.Balance * R * T) / 100;
            acc.Balance = acc.Balance + interest_amt;
            
            // Update File
            fseek(fp, -sizeof(struct Account), SEEK_CUR); // Move back to the position of the account
            fwrite(&acc, sizeof(struct Account), 1, fp);
            printf("******Interest Added******\n");
            printf("Interest Added. New Balance: %.2f\n", acc.Balance);
            break;
        }
    }
    if(!found) printf("Account Not Found!\n");
    fclose(fp);
}

//!---------------------------------------------------------

void transaction_details()
{

    system("cls");

    FILE *ptr;
    ptr = fopen("Account.txt", "r");
    char c = fgetc(ptr);
    if (c == EOF)
    {
        printf("TRANSACTION DETAILS\n");
        divider();
        printf("\n*******NO RECENT TRANSACTION*******\n");
    }
    else
    {
        printf("TRANSACTION DETAILS\n");
        divider();
        printf("\n%d transactions have been made from your account \n", count);
        while (c != EOF) // EOF=End of file
        {
            printf("%c", c);
            c = fgetc(ptr);
        }
    }

    getch();
}

//!---------------------------------------------------------

void exit_program() {
    printf("Exiting Program. Goodbye!\n");
    exit(0);
}