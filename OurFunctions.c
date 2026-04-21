#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct
{
    int month;
    int year;

} Date;

typedef struct
{
    long long int number;
    char name[100];
    char email[100];
    float balance;
    Date date;
    char mobile[100];
    char status[100];

} account;

void Load()
{
    FILE *accounts = fopen("accounts.txt", "r");
    if (accounts == NULL)
    {
        printf("\033[31mFailed to open the txt file\033[0m\n");
        return;
    }

    char string[100];

    int i = 0;
    int c = 0;
    char ch;
    while ((ch = fgetc(accounts)) != EOF) // Instead of making unnecessary space
    {

        if (ch == '\n')
            c++;
    }
    fseek(accounts, 0, SEEK_SET); // Return the file pointer back
    account a[c];

    while (fgets(string, 100, accounts)) // Store the info first in a temporary struct then print it
    {
        if (i == c)
            break;

        char *token = strtok(string, ",");
        if (!token)
            continue;
        a[i].number = atoll(token);
        token = strtok(NULL, ",");
        if (!token)
            continue;
        strcpy(a[i].name, token);
        token = strtok(NULL, ",");
        if (!token)
            continue;
        strcpy(a[i].email, token);
        token = strtok(NULL, ",");
        if (!token)
            continue;
        a[i].balance = atof(token);
        token = strtok(NULL, ",");
        if (!token)
            continue;
        strcpy(a[i].mobile, token);
        token = strtok(NULL, ",-");
        if (!token)
            continue;
        a[i].date.month = atoi(token);
        token = strtok(NULL, ",-");
        if (!token)
            continue;
        a[i].date.year = atoi(token);
        token = strtok(NULL, ",");
        if (!token)
            continue;
        strcpy(a[i].status, token);

        printf("\033[31m Account Number: %lld || \033[32m Name: %s ||\033[33m Email: %s || \033[34mBalance: %.2f$ || \033[35m Mobile: %s || \033[36m Month: %d  || Year: %d  || \033[37m Status: %s\n \033[0m", a[i].number, a[i].name, a[i].email, a[i].balance, a[i].mobile, a[i].date.month, a[i].date.year, a[i].status);
        i++;
    }

    fclose(accounts);
}

void Login()
{
    FILE *users = fopen("users.txt", "r");
    if (users == NULL)
    {
        printf("\033[31mFailed to open the txt file\033[0m\n");
        return;
    }

    char pass[100];
    char user[100];

    int found = 0;
    int login = 0;
    char string[100];
    printf("Enter Username: ");
    scanf("%s", user);
    printf("Enter Password: ");
    scanf("%s", pass);

    while (fgets(string, 100, users) != NULL)
    {

        char *username = strtok(string, " \n\r"); // This was done by debugging the last two characters and checking their ASCII integer codes
        char *password;
        password = strtok(NULL, " \n\r");

        if (strcmp(user, username) == 0)
        {
            if (strcmp(pass, password) == 0)
            {
                printf("\033[32mAccess Granted\033[0m\n");
                login = 1;
                fclose(users);
                return;
            }

            else
                printf("\033[31mWrong Password\033[0m\n");

            found = 1;
            break;
        }

        else
            continue;
    }
    if (!found)
        printf("\033[31mUser not found\033[0m\n");

    fclose(users);
}

void Query()
{
    FILE *accounts = fopen("accounts.txt", "r");
    if (accounts == NULL)
    {
        printf("\033[31mFailed to open the txt file\033[0m\n");
        return;
    }

    char string[100];
    long long int num;
    account a;
    printf("Account Number:");
    scanf("%lld", &num);
    while (fgets(string, 100, accounts) != NULL)
    {

        char *account_num = strtok(string, ",");
        if (atoll(account_num) == num)
        {

            strcpy(a.name, strtok(NULL, ","));
            strcpy(a.email, strtok(NULL, ","));
            a.balance = atof(strtok(NULL, ","));
            strcpy(a.mobile, strtok(NULL, ","));
            a.date.month = atoi(strtok(NULL, ",-"));
            a.date.year = atoi(strtok(NULL, "-,"));
            strcpy(a.status, strtok(NULL, ","));
            const char *months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"}; // To turn the integer of the month into a string as shown in the example

            printf("\033[31mName: %s \n\033[32mEmail: %s \n\033[33mBalance: %.2f$ \n\033[34mMobile: %s \n\033[35mDate Opened: %s %d \n\033[36mStatus: %s\033[0m\n\n", a.name, a.email, a.balance, a.mobile, months[(a.date.month) - 1], a.date.year, a.status);

            fclose(accounts);
            return;
        }
    }
    printf("\033[31mUser not found\033[0m\n");
    fclose(accounts);
    return;
}

int Save()
{
    char c[100];
    while (1)
    {
        printf("Save changes? (y/n): ");
        scanf(" %s", c);

        if (tolower(c[0]) == 'y' && strlen(c) == 1)
            return 1;

        else if (tolower(c[0]) == 'n' && strlen(c) == 1)
            return 0;
        else
            printf("Enter (y/n)\n");
    }
}

int dailyLimit(long long num)
{
    char str3[100];
    int limit = 0;
    int money = 0;
    int found = 0;
    sprintf(str3, "%lld", num);
    strcat(str3, ".txt");
    FILE *f = fopen(str3, "r");
    if (f == NULL)
    {
        return -1;
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    int cur_day = t->tm_mday;
    int cur_month = t->tm_mon + 1;
    int cur_year = t->tm_year + 1900;
    int day = 0;
    int month = 0;
    int year = 0;
    char string[100];

    while (fgets(string, 100, f))
    {
        char *token = strtok(string, ",");
        if (!token)
            continue;
        if (strcmp(token, "Withdraw") == 0)
        {
            found = 1;
            token = strtok(NULL, ",");
            if (!token)
                continue;
            money = atoi(token);
            token = strtok(NULL, "-");
            if (!token)
                continue;
            day = atoi(token);
            token = strtok(NULL, "-");
            if (!token)
                continue;
            month = atoi(token);
            token = strtok(NULL, "-");
            if (!token)
                continue;
            year = atoi(token);

            if ((month == cur_month) && (year == cur_year) && (day == cur_day))
            {
                limit += money;
            }
            if (limit >= 50000)
            {
                printf("\033[31mDaily limit exceeded\033[0m\n");
                fclose(f);
                return -2;
            }
        }
    }

    fclose(f);
    if (found)
        return limit;
    return 1;
}

void Advanced_Search()
{
    FILE *accounts = fopen("accounts.txt", "r");
    if (accounts == NULL)
    {
        printf("\033[31mFailed to open the txt file\033[0m\n");
        return;
    }

    int i = 0;
    int found = 0;
    char name[100];
    printf("Enter Name: ");
    fgets(name, 100, stdin);
    name[strlen(name) - 1] = '\0'; // Eliminate the last annoying character added by fgets
    char string[100];

    int c = 0;
    char ch;
    while ((ch = fgetc(accounts)) != EOF) // Instead of making too much space array for the struct we can easily count the lines of the files
    {

        if (ch == '\n')
            c++;
    }

    fseek(accounts, 0, SEEK_SET);
    account a[c];

    while (fgets(string, 100, accounts) != NULL)
    {
        if (i == c)
            break;

        char temp[101];       // Remember from the exam :)
        strcpy(temp, string); // Make a temporary string that iterates through the file like variable string
        char *n = strtok(string, ",");
        if (!n)
            continue;
        n = strtok(NULL, ","); // Since the name is the second string after the delimiter ,
        if (!n)
            continue;
        char *Name = strstr(n, name); // Search if part of the prompted name is inside the name of the file
        Name = strtok(Name, " ,");    // Cut the occurence of the pointer and , just incase that name is the last name
        if (!Name)
            continue;

        if (strcmp(Name, name) == 0)
        {
            char *token = strtok(temp, ",");
            if (!token)
                continue;
            a[i].number = atoll(token);
            token = strtok(NULL, ",");
            if (!token)
                continue;
            strcpy(a[i].name, token);
            token = strtok(NULL, ",");
            if (!token)
                continue;
            strcpy(a[i].email, token);
            token = strtok(NULL, ",");
            if (!token)
                continue;
            a[i].balance = atof(token);
            token = strtok(NULL, ",");
            if (!token)
                continue;
            strcpy(a[i].mobile, token);
            token = strtok(NULL, ",-");
            if (!token)
                continue;
            a[i].date.month = atoi(token);
            token = strtok(NULL, ",-");
            if (!token)
                continue;
            a[i].date.year = atoi(token);
            token = strtok(NULL, ",");
            if (!token)
                continue;
            strcpy(a[i].status, token);
            printf("\033[31mAccount Number: %lld \n\033[32mName: %s \n\033[33mEmail: %s  \n\033[34mBalance: %.2f$ \n\033[35mMobile: %s \n\033[36mMonth: %d  \nYear: %d  \n\033[37mStatus: %s\n\n", a[i].number, a[i].name, a[i].email, a[i].balance, a[i].mobile, a[i].date.month, a[i].date.year, a[i].status);
            i++;
            found = 1;
        }
    }
    if (!found)
        printf("\033[31mUser not found\033[0m\n");

    fclose(accounts);
}

int uniqueAccountNumber(long long num)
{
    FILE *accounts = fopen("accounts.txt", "r");
    if (!accounts)
    {
        return -1;
    }
    char line[500];
    while (fgets(line, sizeof(line), accounts))
    {
        account temp;
        char *token = strtok(line, ",");
        temp.number = atoll(token);
        if (temp.number == num)
        {
            fclose(accounts);
            return 0;
        }
    }
    fclose(accounts);
    return 1;
}

void addAccount()
{
    account newAcc;
    printf("Enter account number: ");
    char ptr1[100];
    scanf("%s", ptr1);
    char *temp = ptr1;
    if (strlen(ptr1) > 10)
    {
        printf("\033[31mAccount number must be less than 10 digits\033[0m\n");
        return;
    }

    while (*temp != '\0')
    {
        if (!isdigit(*temp)) // If the character doesnt contain a digit
        {
            printf("\033[31mInvalid Account Number\033[0m\n");
            return;
        }

        temp++;
    }
    newAcc.number = atoll(ptr1);

    int flag = uniqueAccountNumber(newAcc.number);
    if (flag == 0)
    {
        printf("\033[31mError: Account number already exists\033[0m\n");
        return;
    }

    getchar();

    printf("Enter name: ");
    fgets(newAcc.name, sizeof(newAcc.name), stdin);
    newAcc.name[strcspn(newAcc.name, "\n")] = '\0';
    char *ptr = newAcc.name;
    while (*ptr != '\0')
    {

        if (!isalpha(*ptr) && *ptr != ' ' && *ptr != '\r') // If the character isnt a letter nor \n nor ' '
        {
            printf("\033[31mInvalid Name\033[0m\n");
            return;
        }

        ptr++;
    }

    printf("Enter email: ");
    fgets(newAcc.email, sizeof(newAcc.email), stdin);
    newAcc.email[strcspn(newAcc.email, "\n")] = '\0';
    char *ptr2 = newAcc.email;
    int contains_char = 0;
    int contains_char1 = 0;

    while (*ptr2 != '\0')
    {
        if (*ptr2 == '@')
            contains_char = 1;
        else if (*ptr2 == '.')
            contains_char1 = 1;
        else if (*ptr2 == ' ') // If the string contains a space
        {
            printf("\033[31mInvalid Email\033[0m\n");
            return;
        }
        ptr2++;
    }
    if (!(contains_char && contains_char1)) // If the string didnt contain an @
    {
        printf("\033[31mInvalid Email\033[0m\n");
        return;
    }

    printf("Enter balance: ");
    char ptr3[100];
    scanf("%s", ptr3);
    char *temp2 = ptr3;

    while (*temp2 != '\0')
    {
        if (!(isdigit(*temp2) || *temp2 == '.')) // If the character doesnt contain a digit or a decimal .
        {
            printf("\033[31mInvalid Account Balance\033[0m\n");
            return;
        }

        temp2++;
    }
    newAcc.balance = atof(ptr3);
    printf("Enter mobile number: ");
    scanf("%s", newAcc.mobile);
    newAcc.mobile[strcspn(newAcc.mobile, "\n")] = '\0';
    char *ptr4 = newAcc.mobile;

    while (*ptr4 != '\0')
    {
        if (!(isdigit(*ptr4) && *ptr4 != '+')) // If the character doesnt contain a digit
        {
            printf("\033[31mInvalid Account Mobile Number\033[0m\n");
            return;
        }

        ptr4++;
    }

    time_t t = time(NULL); // Our mate forgot that he could have just put December 2025 x)
    struct tm tm = *localtime(&t);
    newAcc.date.month = tm.tm_mon + 1;
    newAcc.date.year = tm.tm_year + 1900;

    strcpy(newAcc.status, " active");

    FILE *accounts = fopen("accounts.txt", "a");
    if (!accounts)
    {
        printf("\033[31mError opening file\033[0m\n");
        return;
    }
    if (Save() == 1)
    {

        char str3[100];
        sprintf(str3, "%lld", newAcc.number);
        strcat(str3, ".txt");
        FILE *ff = fopen(str3, "w");
        fclose(ff);

        fprintf(accounts, "%lld,%s,%s,%.2f,%s,%d-%d,%s\n", newAcc.number, newAcc.name,
                newAcc.email, newAcc.balance, newAcc.mobile, newAcc.date.month,
                newAcc.date.year, newAcc.status);

        fclose(accounts);
        printf("\033[32mAccount successfully added!\033[0m\n");
    }
    else
        printf("\033[31mOperation Abandoned\033[0m\n");

    fclose(accounts);
}

float accData(long long num)
{
    FILE *accounts = fopen("accounts.txt", "r");
    if (!accounts)
        return -1;

    char line[500];
    while (fgets(line, sizeof(line), accounts))
    {

        account temp;
        char *token = strtok(line, ",");
        temp.number = atoll(token);

        if (temp.number == num)
        {
            token = strtok(NULL, ",");
            strcpy(temp.name, token);

            token = strtok(NULL, ",");
            strcpy(temp.email, token);

            token = strtok(NULL, ",");
            temp.balance = atof(token);

            fclose(accounts);
            return temp.balance;
        }
    }

    fclose(accounts);
    return -1;
}

void deleteAccount()
{
    FILE *accounts = fopen("accounts.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (!accounts || !tempFile)
    {
        printf("\033[31mError opening the files\033[0m\n");
        remove("temp.txt");
        return;
    }
    long long accnum;
    printf("Enter account number: ");
    scanf("%lld", &accnum);

    float balance = accData(accnum);

    if ((int)balance < 0)
    {
        printf("\033[31mError: account number doesn't exist\033[0m\n");
        fclose(accounts);
        fclose(tempFile);
        remove("temp.txt");
        return;
    }

    else if ((int)balance > 0)
    {
        printf("\033[31mError: cannot delete account with non-zero balance\033[0m\n");
        fclose(accounts);
        fclose(tempFile);
        remove("temp.txt");
        return;
    }

    if (Save() == 1)
    {
        char line[500];
        while (fgets(line, sizeof(line), accounts))
        {
            char copy[500];
            strcpy(copy, line);

            account temp;
            char *token = strtok(line, ",");
            if (!token)
                continue;
            temp.number = atoll(token);

            if (temp.number != accnum)
            {
                fputs(copy, tempFile);
            }
        }

        fclose(accounts);
        fclose(tempFile);

        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");

        printf("\033[32mAccount %lld deleted successfully!\033[0m\n", accnum);
        return;
    }
    else
        printf("\033[31mOperation Abandoned\033[0m\n");
    fclose(accounts);
    fclose(tempFile);
}

void modifyAccount()
{
    int Saved;
    long long accnum;

    FILE *test = fopen("accounts.txt", "r");
    if (test == NULL)
    {
        printf("\033[31mCouldnt open the txt file\033[0m\n");
        return;
    }
    fclose(test);

    printf("Enter account number: ");
    scanf("%lld", &accnum);

    int flag = uniqueAccountNumber(accnum);
    if (flag == -1)
    {
        printf("\033[31mError opening files\033[0m\n");
        return;
    }

    getchar();

    if (flag == 0)
    {

        FILE *accounts = fopen("accounts.txt", "r");
        FILE *tempFile = fopen("temp.txt", "w");
        if (!accounts || !tempFile)
        {
            printf("\033[31mError opening files\033[0m\n");
            remove("temp.txt");
            return;
        }

        char line[500];
        while (fgets(line, sizeof(line), accounts))
        {
            char copy[500];
            strcpy(copy, line);

            account temp;
            char *token = strtok(line, ",");
            if (!token)
                continue;
            temp.number = atoll(token);

            if (temp.number == accnum)
            {
                token = strtok(NULL, ",");
                if (!token)
                    continue;
                strcpy(temp.name, token);

                token = strtok(NULL, ",");
                if (!token)
                    continue;
                strcpy(temp.email, token);

                token = strtok(NULL, ",");
                if (!token)
                    continue;
                temp.balance = atof(token);

                token = strtok(NULL, ",");
                if (!token)
                    continue;
                strcpy(temp.mobile, token);

                token = strtok(NULL, ",-");
                if (!token)
                    continue;
                temp.date.month = atoll(token);

                token = strtok(NULL, ",-");
                if (!token)
                    continue;
                temp.date.year = atoll(token);

                token = strtok(NULL, ",");
                if (!token)
                    continue;
                strcpy(temp.status, token);

                printf("Enter new name (current: %s): ", temp.name);
                fgets(temp.name, sizeof(temp.name), stdin);
                temp.name[strcspn(temp.name, "\n")] = '\0';

                char *ptr = temp.name;
                while (*ptr != '\0')
                {

                    if (!isalpha(*ptr) && *ptr != ' ' && *ptr != '\r') // If the character isnt a letter nor \n nor ' '
                    {
                        printf("\033[31mInvalid Name\033[0m\n");
                        fclose(tempFile);
                        fclose(accounts);
                        remove("temp.txt");
                        return;
                    }

                    ptr++;
                }

                printf("Enter new email (current: %s): ", temp.email);
                fgets(temp.email, sizeof(temp.email), stdin);
                temp.email[strcspn(temp.email, "\n")] = '\0';

                char *ptr2 = temp.email;
                int contains_char = 0;
                int contains_char1 = 0;

                while (*ptr2 != '\0')
                {
                    if (*ptr2 == '@')
                        contains_char = 1;
                    else if (*ptr2 == '.')
                        contains_char1 = 1;
                    else if (*ptr2 == ' ') // If the string contains a space
                    {
                        printf("\033[31mInvalid Email\033[0m\n");
                        fclose(tempFile);
                        fclose(accounts);
                        remove("temp.txt");
                        return;
                    }
                    ptr2++;
                }
                if (!(contains_char && contains_char1)) // If the string didnt contain an @
                {
                    printf("\033[31mInvalid Email\033[0m\n");
                    fclose(tempFile);
                    fclose(accounts);
                    remove("temp.txt");
                    return;
                }

                printf("Enter new mobile (current: %s): ", temp.mobile);
                scanf("%s", temp.mobile);

                char *ptr4 = temp.mobile;

                while (*ptr4 != '\0')
                {
                    if (!isdigit(*ptr4) && *ptr4 != '+') // If the character doesnt contain a digit
                    {
                        printf("\033[31mInvalid Account Mobile Number\033[0m\n");
                        fclose(accounts);
                        fclose(tempFile);
                        remove("temp.txt");
                        return;
                    }

                    ptr4++;
                }
                Saved = Save();

                if (Saved)
                {
                    fprintf(tempFile, "%lld,%s,%s,%.2f,%s,%d-%d,%s", temp.number, temp.name,
                            temp.email, temp.balance, temp.mobile, temp.date.month,
                            temp.date.year, temp.status);
                }
            }
            else
                fputs(copy, tempFile);
        }

        fclose(accounts);
        fclose(tempFile);
        if (Saved)
        {
            remove("accounts.txt");
            rename("temp.txt", "accounts.txt");
            printf("\033[32mAccount %lld modified successfully\033[0m\n", accnum);
        }
        else
            printf("\033[31mOperation Abandoned\033[0m\n");
    }

    else if (flag == 1)
    {
        printf("\033[31mError: Account number %lld not found\033[0m\n", accnum);
    }

    remove("temp.txt");
}

void changeStatus()
{
    FILE *accounts = fopen("accounts.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (!accounts || !tempFile)
    {
        printf("\033[31mError opening files\033[0m\n");
        remove("temp.txt");
        return;
    }

    long long int accnum;
    int Saved;
    printf("Enter account number: ");
    scanf("%lld", &accnum);
    int flag = uniqueAccountNumber(accnum);
    if (flag == 0)
    {

        char line[500];
        while (fgets(line, sizeof(line), accounts))
        {
            char copy[500];
            strcpy(copy, line);

            account temp;
            char *token = strtok(line, ",");
            if (!token)
                continue;
            temp.number = atoll(token);

            if (temp.number == accnum)
            {
                token = strtok(NULL, ",");
                if (!token)
                    continue;
                strcpy(temp.name, token);

                token = strtok(NULL, ",");
                if (!token)
                    continue;
                strcpy(temp.email, token);

                token = strtok(NULL, ",");
                if (!token)
                    continue;
                temp.balance = atof(token);

                token = strtok(NULL, ",");
                if (!token)
                    continue;
                strcpy(temp.mobile, token);

                token = strtok(NULL, ",-");
                if (!token)
                    continue;
                temp.date.month = atoll(token);

                token = strtok(NULL, ",-");
                if (!token)
                    continue;
                temp.date.year = atoll(token);

                token = strtok(NULL, ",");
                if (!token)
                    continue;
                strcpy(temp.status, token);

                printf("The current status:%s\n", temp.status);
                int flag;
                printf("if you want to change the status enter '1' if not enter '2': ");
                scanf("%d", &flag);

                char *tmp = temp.status;
                while (*tmp == ' ')
                    tmp++;
                tmp[strcspn(tmp, "\r\n")] = '\0';

                switch (flag)
                {
                case 1:
                {
                    if (strcmp(tmp, "active") == 0)
                        strcpy(temp.status, " inactive");
                    else
                        strcpy(temp.status, " active");
                    printf("\033[32mThe status changed successfully\033[0m\n");
                    break;
                }
                case 2:
                    printf("Keeping current status\n");
                    break;
                default:
                    printf("\033[31mInvalid choice, keeping current status\033[0m\n");
                }
                if (flag != 2)
                    Saved = Save();
                else
                    Saved = 0;
                if (Saved)
                {
                    fprintf(tempFile, "%lld,%s,%s,%.2f,%s,%d-%d,%s\n", temp.number, temp.name,
                            temp.email, temp.balance, temp.mobile, temp.date.month,
                            temp.date.year, temp.status);
                }
            }
            else
                fputs(copy, tempFile);
        }

        fclose(accounts);
        fclose(tempFile);
        if (Saved)
        {
            remove("accounts.txt");
            rename("temp.txt", "accounts.txt");
        }
        else
        {
            printf("\033[31mOperation Abandoned\033[0m\n");
            fclose(tempFile);
            fclose(accounts);
            remove("temp.txt");
        }
    }

    else if (flag == 1)
    {
        printf("\033[31mError: Account number %lld not found\033[0m\n", accnum);
        fclose(tempFile);
        fclose(accounts);
        remove("temp.txt");
    }
    else
    {
        printf("\033[31mError opening files\033[0m\n");
        fclose(tempFile);
        fclose(accounts);
        remove("temp.txt");
    }
}

void Load_Print()
{

    FILE *accounts = fopen("temp.txt", "r");
    if (accounts == NULL)
    {
        printf("\033[31mFailed to open the txt file\n");
        return;
    }

    char string[100];

    int i = 0;
    int c = 0;
    char buf[200];
    while (fgets(buf, sizeof buf, accounts))
    {
        if (buf[0] == '\n' || buf[0] == '\r')
            continue;
        c++;
    }
    fseek(accounts, 0, SEEK_SET); // Return the file pointer back
    account a[c];

    while (fgets(string, 100, accounts)) // Store the info first in a temporary struct then print it
    {
        if (i == c)
            break;

        char *token = strtok(string, ",");
        if (!token)
            continue;
        a[i].number = atoll(token);
        token = strtok(NULL, ",");
        if (!token)
            continue;
        strcpy(a[i].name, token);
        token = strtok(NULL, ",");
        if (!token)
            continue;
        strcpy(a[i].email, token);
        token = strtok(NULL, ",");
        if (!token)
            continue;
        a[i].balance = atof(token);
        token = strtok(NULL, ",");
        if (!token)
            continue;
        strcpy(a[i].mobile, token);
        token = strtok(NULL, ",-");
        if (!token)
            continue;
        a[i].date.month = atoi(token);
        token = strtok(NULL, ",-");
        if (!token)
            continue;
        a[i].date.year = atoi(token);
        token = strtok(NULL, ",");
        if (!token)
            continue;
        strcpy(a[i].status, token);
        printf("\033[31mAccount Number: %lld || \033[32mName: %s || \033[33mEmail: %s || \033[34mBalance: %.2f$ || \033[35mMobile: %s || \033[36mMonth: %d  || Year: %d  || \033[37mStatus: %s\n\n", a[i].number, a[i].name, a[i].email, a[i].balance, a[i].mobile, a[i].date.month, a[i].date.year, a[i].status);
        i++;
    }

    fclose(accounts);
    remove("temp.txt");
}

void sortByBalance()
{

    int c = 0;
    FILE *f = fopen("accounts.txt", "r");

    if (f == NULL)
    {
        printf("\033[31mError opening the file\033[0m\n");
        return;
    }

    char buf[200];
    while (fgets(buf, sizeof buf, f))
    {
        if (buf[0] == '\n' || buf[0] == '\r')
            continue;
        c++;
    }

    account s[c];
    char string[100];
    int i = 0;
    rewind(f);
    while (fgets(string, 100, f))
    {
        if (i == c)
            break;

        char *token = strtok(string, ",");
        if (!token)
            continue;
        s[i].number = atoll(token);
        token = strtok(NULL, ",");
        if (!token)
            continue;
        strcpy(s[i].name, token);
        token = strtok(NULL, ",");
        if (!token)
            continue;
        strcpy(s[i].email, token);
        token = strtok(NULL, ",");
        if (!token)
            continue;
        s[i].balance = atof(token);
        token = strtok(NULL, ",");
        if (!token)
            continue;
        strcpy(s[i].mobile, token);
        token = strtok(NULL, ",-");
        if (!token)
            continue;
        s[i].date.month = atoi(token);
        token = strtok(NULL, ",-");
        if (!token)
            continue;
        s[i].date.year = atoi(token);
        token = strtok(NULL, ",");
        if (!token)
            continue;
        strcpy(s[i].status, token);
        i++;
    }
    int j, k;
    for (j = 0; j < c - 1; j++)
    {
        for (k = 0; k < c - j - 1; k++)
        {
            if (s[k].balance > s[k + 1].balance)
            {
                account temp = s[k + 1];
                s[k + 1] = s[k];
                s[k] = temp;
            }
        }
    }
    FILE *fp = fopen("temp.txt", "w");
    i = 0;
    while (i < c)
    {
        fprintf(fp, "%lld,%s,%s,%f,%s,%d,%d,%s\n", s[i].number, s[i].name, s[i].email, s[i].balance, s[i].mobile, s[i].date.month, s[i].date.year, s[i].status);
        i++;
    }
    fclose(fp);
    fclose(f);
    Load_Print();
}

void sortByName()
{
    int c = 0;
    FILE *f = fopen("accounts.txt", "r");
    if (f == NULL)
    {
        printf("\033[31mError opening the txt file\033[0m\n");
        return;
    }
    char buf[200];
    while (fgets(buf, sizeof buf, f))
    {
        if (buf[0] == '\n' || buf[0] == '\r')
            continue;
        c++;
    }
    account s[c];
    char string[100];
    int i = 0;
    rewind(f);
    while (fgets(string, 100, f))
    {

        char *token = strtok(string, ",");
        if (!token)
            continue;
        s[i].number = atoll(token);
        token = strtok(NULL, ",");
        if (!token)
            continue;

        strcpy(s[i].name, token);
        token = strtok(NULL, ",");
        if (!token)
            continue;
        strcpy(s[i].email, token);
        token = strtok(NULL, ",");
        if (!token)
            continue;
        s[i].balance = atof(token);
        token = strtok(NULL, ",");
        if (!token)
            continue;
        strcpy(s[i].mobile, token);
        token = strtok(NULL, ",-");
        if (!token)
            continue;
        s[i].date.month = atoi(token);
        token = strtok(NULL, ",-");
        if (!token)
            continue;
        s[i].date.year = atoi(token);
        token = strtok(NULL, ",");
        if (!token)
            continue;
        strcpy(s[i].status, token);
        i++;
    }
    int j, k;
    for (j = 0; j < c - 1; j++)
    {
        for (k = 0; k < c - j - 1; k++)
        {
            if (strcmp(s[k].name, s[k + 1].name) > 0)
            {
                account temp = s[k + 1];
                s[k + 1] = s[k];
                s[k] = temp;
            }
        }
    }
    FILE *fp = fopen("temp.txt", "w");
    i = 0;
    while (i < c)
    {
        fprintf(fp, "%lld,%s,%s,%f,%s,%d,%d,%s", s[i].number, s[i].name, s[i].email, s[i].balance, s[i].mobile, s[i].date.month, s[i].date.year, s[i].status);
        i++;
    }
    fclose(fp);
    Load_Print();

    fclose(f);
}

void sortByDate()
{
    int c = 0;
    FILE *f = fopen("accounts.txt", "r");
    if (f == NULL)
    {
        printf("\033[31mCouldnt open the txt file\033[0m\n");
        return;
    }
    char buf[200];
    while (fgets(buf, sizeof buf, f))
    {
        if (buf[0] == '\n' || buf[0] == '\r')
            continue;
        c++;
    }
    account s[c];
    char string[100];
    int i = 0;
    rewind(f);
    while (fgets(string, 100, f))
    {
        if (i == c)
            break;
        char *token = strtok(string, ",");
        if (!token)
            continue;
        s[i].number = atoll(token);
        token = strtok(NULL, ",");
        if (!token)
            continue;
        strcpy(s[i].name, token);
        token = strtok(NULL, ",");
        if (!token)
            continue;
        strcpy(s[i].email, token);
        token = strtok(NULL, ",");
        if (!token)
            continue;
        s[i].balance = atof(token);
        token = strtok(NULL, ",");
        if (!token)
            continue;
        strcpy(s[i].mobile, token);
        token = strtok(NULL, ",-");
        if (!token)
            continue;
        s[i].date.month = atoi(token);
        token = strtok(NULL, ",-");
        if (!token)
            continue;
        s[i].date.year = atoi(token);
        token = strtok(NULL, ",");
        if (!token)
            continue;
        strcpy(s[i].status, token);
        i++;
    }
    int j, k;
    for (j = 0; j < c - 1; j++)
    {
        for (k = 0; k < c - j - 1; k++)
        {
            if (s[k].date.year > s[k + 1].date.year)
            {
                account temp = s[k + 1];
                s[k + 1] = s[k];
                s[k] = temp;
            }
            else if (s[k].date.year == s[k + 1].date.year)
            {
                if (s[k].date.month > s[k + 1].date.month)
                {
                    account temp = s[k + 1];
                    s[k + 1] = s[k];
                    s[k] = temp;
                }
            }
        }
    }
    FILE *fp = fopen("temp.txt", "w");
    i = 0;
    while (i < c)
    {
        fprintf(fp, "%lld,%s,%s,%f,%s,%d,%d,%s", s[i].number, s[i].name, s[i].email, s[i].balance, s[i].mobile, s[i].date.month, s[i].date.year, s[i].status);
        i++;
    }
    fclose(fp);
    Load_Print();

    fclose(f);
}

void Print()
{
    FILE *test = fopen("accounts.txt", "r");
    if (test == NULL)
    {
        printf("\033[31mCouldnt open the txt file\033[0m\n");
        return;
    }
    fclose(test);
    char string[100];
    printf("How do you want the print to be sorted? (name,balance,date): ");
    scanf("%s", string);
    char *ptr = string;
    while (*ptr != '\0')
    {
        *ptr = tolower(*ptr);
        ptr++;
    }

    if (strcmp(string, "name") == 0)
    {
        sortByName();
    }
    else if (strcmp(string, "balance") == 0)
    {

        sortByBalance();
    }
    else if (strcmp(string, "date") == 0)
    {
        sortByDate();
    }
    else
    {
        printf("\033[31mInvalid arguement..Enter (name,date,balance) \033[0m\n");
        return;
    }
}

void deleteAccount_Multiple2(long long accnum)
{
    float balance = accData(accnum);

    if ((int)balance < 0)
    {
        return;
    }
    else if ((int)balance > 0)
    {
        return;
    }

    FILE *accounts = fopen("accounts.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (!accounts || !tempFile)
    {
        printf("\033[31mError opening files\033[0m\n");
        remove("temp.txt");
        return;
    }

    char line[500];
    while (fgets(line, sizeof(line), accounts))
    {
        char copy[500];
        strcpy(copy, line);

        account temp;
        char *token = strtok(line, ",");
        temp.number = atoll(token);

        if (temp.number != accnum)
        {
            fputs(copy, tempFile);
        }
    }

    fclose(accounts);
    fclose(tempFile);

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    printf("\033[32mAccount %lld deleted successfully!\033[0m\n", accnum);
}

void deleteAccount_Multiple(long long accnum)
{
    float balance = accData(accnum);

    if ((int)balance < 0)
    {
        printf("\033[31mError: account number doesn't exist\033[0m\n");
        return;
    }

    FILE *accounts = fopen("accounts.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (!accounts || !tempFile)
    {
        printf("\033[31mError opening files\n");
        remove("temp.txt");
        return;
    }

    char line[500];
    while (fgets(line, sizeof(line), accounts))
    {
        char copy[500];
        strcpy(copy, line);

        account temp;
        char *token = strtok(line, ",");
        temp.number = atoll(token);

        if (temp.number != accnum)
        {
            fputs(copy, tempFile);
        }
    }

    fclose(accounts);
    fclose(tempFile);

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    printf("\033[32mAccount %lld deleted successfully!\033[0m\n", accnum);
}

void deleteByActivity()
{
    int c = 0;
    int Saved;
    long long int arr[100];
    FILE *f = fopen("accounts.txt", "r");
    char string2[100];
    while (fgets(string2, sizeof(string2), f))
    {
        char *token2 = strtok(string2, ",");
        if (!token2)
            continue;
        long long int accnum = atoll(token2);
        token2 = strtok(NULL, ",");
        if (!token2)
            continue;
        token2 = strtok(NULL, ",");
        if (!token2)
            continue;
        token2 = strtok(NULL, ",");
        if (!token2)
            continue;
        float bal = atof(token2);
        token2 = strtok(NULL, ",");
        if (!token2)
            continue;
        token2 = strtok(NULL, "-");
        if (!token2)
            continue;
        int month = atoi(token2);
        token2 = strtok(NULL, ",-");
        if (!token2)
            continue;
        int year = atoi(token2);
        token2 = strtok(NULL, ",\n\r");
        if (!token2)
            continue;
        char state[15];
        strcpy(state, token2);
        if (strcmp(state, " inactive") == 0)

            if (((year == 2025 && month <= 9) || (year < 2025)) && (bal == 0) && strcmp(state, " inactive") == 0)
            {
                arr[c++] = accnum;
            }
    }
    fclose(f);
    int i;
    if (c == 0)
    {
        printf("\033[31mNo accounts to be found to be deleted\033[0m\n");
        fclose(f);
        return;
    }
    Saved = Save();
    if (Saved)
    {
        for (i = 0; i < c; i++)
            deleteAccount_Multiple2(arr[i]);
    }
    else
        printf("\033[31mOperation Abandoned\033[0m\n");

    fclose(f);
}

void deleteByDate()
{
    char string[100];
    int Saved;
    int c = 0;
    long long int arr[100];
    printf("Enter date of accounts you want deleted (YYYY-MM): ");
    scanf("%s", string);
    char *token = strtok(string, "-");
    if (!token)
    {
        printf("\033[31mEnter a valid number\033[0m\n");
        return;
    }
    char *ptr = token;
    while (*ptr != '\0')
    {
        if (!isdigit(*ptr))
        {
            printf("\033[31mEnter a valid number\033[0m\n");
            return;
        }
        ptr++;
    }
    int year = atoi(token);
    token = strtok(NULL, "-");
    if (!token)
    {
        printf("\033[31mEnter a valid number\033[0m\n");
        return;
    }

    ptr = token;
    while (*ptr != '\0')
    {
        if (!isdigit(*ptr))
        {
            printf("\033[31mEnter a valid number\033[0m\n");
            return;
        }
        ptr++;
    }
    int month = atoi(token);
    if (month > 12 || month <= 0)
    {
        printf("\033[31mEnter a valid month\033[0m\n");
        return;
    }
    else if (year < 1990 || year >= 2026)
    {
        printf("\033[31mEnter a valid year\033[0m\n");
        return;
    }
    FILE *f = fopen("accounts.txt", "r");
    char string2[100];
    while (fgets(string2, sizeof(string2), f))
    {
        char *token2 = strtok(string2, ",");
        if (!token2)
            continue;
        long long int accnum = atoll(token2);

        token2 = strtok(NULL, ",");
        if (!token2)
            continue;

        token2 = strtok(NULL, ",");
        if (!token2)
            continue;

        token2 = strtok(NULL, ",");
        if (!token2)
            continue;
        float bal = atof(token2);

        token2 = strtok(NULL, ",");
        if (!token2)
            continue;

        token2 = strtok(NULL, ",-");
        if (!token2)
            continue;
        int month1 = atoi(token2);

        token2 = strtok(NULL, ",-");
        if (!token2)
            continue;
        int year1 = atoi(token2);

        if (year1 == year && month1 == month && (bal == 0))
        {
            arr[c++] = accnum;
        }
    }
    fclose(f);
    int i;
    if (c == 0)
    {
        printf("\033[31mNo accounts to be found to be deleted\033[0m\n");
        fclose(f);
        return;
    }
    Saved = Save();
    if (Saved)
    {
        for (i = 0; i < c; i++)
            deleteAccount_Multiple(arr[i]);
    }
    else
        printf("\033[31mOperation Abandoned\033[0m\n");

    fclose(f);
}

void deleteMultiple()
{
    FILE *test = fopen("accounts.txt", "r");
    if (test == NULL)
    {
        printf("\033[31mCouldnt open the txt file\033[0m\n");
        return;
    }
    fclose(test);

    printf("Delete multiple accounts by (activity,date): ");
    char string[100];
    scanf("%s", string);
    char *ptr = string;
    while (*ptr)
    {
        *ptr = tolower(*ptr);
        ptr++;
    }
    if (strcmp(string, "activity") == 0)
    {
        deleteByActivity();
    }
    else if (strcmp(string, "date") == 0)
    {
        deleteByDate();
    }
    else
    {
        printf("\033[31mEnter the valid format (activity,date)\033[0m\n");
    }
}

void Withdraw()
{
    FILE *accounts = fopen("accounts.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    int Saved;

    if (accounts == NULL || temp == NULL)
    {
        printf("\033[31mFailed to open files.\033[0m\n");
        remove("temp.txt");
        return;
    }

    char string[200];
    char lineCopy[200];
    long long int num;
    int amount, found = 0;
    account a;
    char str[100];
    printf("Please enter account number: ");
    scanf("%s", str);
    char *ptr = str;
    while (*ptr != '\0')
    {

        if (!isdigit(*ptr))
        {
            printf("\033[31mEnter a valid number\033[0m\n");
            fclose(accounts);
            fclose(temp);
            remove("temp.txt");
            return;
        }
        ptr++;
    }
    num = atoll(str);
    int limit = dailyLimit(num);
    if (limit == -2)
    {
        fclose(accounts);
        fclose(temp);
        remove("temp.txt");
        return;
    }

    while (fgets(string, 200, accounts) != NULL)
    {

        strcpy(lineCopy, string);

        char *token = strtok(string, ",");

        if (token != NULL && atoll(token) == num)
        {
            found = 1;

            a.number = atoll(token);
            token = strtok(NULL, ",");
            strcpy(a.name, token);
            if (!token)
                continue;
            token = strtok(NULL, ",");
            strcpy(a.email, token);
            if (!token)
                continue;
            token = strtok(NULL, ",");
            a.balance = atof(token);
            if (!token)
                continue;
            token = strtok(NULL, ",");
            strcpy(a.mobile, token);
            if (!token)
                continue;
            token = strtok(NULL, "-");
            a.date.month = atoi(token);
            if (!token)
                continue;
            token = strtok(NULL, ",");
            a.date.year = atoi(token);
            if (!token)
                continue;
            token = strtok(NULL, ",");
            if (!token)
                continue;
            token[strcspn(token, "\n")] = 0;
            strcpy(a.status, token);

            a.status[strcspn(a.status, "\r\n")] = '\0';
            if (strcmp(a.status, " active") == 0)
            {

                do
                {
                    char str2[100];

                    printf("Please enter the amount you wish to withdraw (Balance: %.2f)(maximum $10,000): ", a.balance);
                    scanf("%s", str2);
                    char *ptr2 = str2;
                    while (*ptr2 != '\0')
                    {

                        if (!isdigit(*ptr2) || atoi(str2) <= 0)
                        {
                            printf("\033[31mEnter a valid number\033[0m\n");
                            fclose(accounts);
                            fclose(temp);
                            return;
                        }
                        ptr2++;
                    }
                    amount = atoi(str2);

                } while (amount > 10000);

                if (amount > a.balance)
                {
                    printf("\033[31mThe amount entered exceeds your current balance. \033[0m\n");
                    fprintf(temp, "%s", lineCopy);
                }
                else
                {
                    if (limit + amount > 50000)
                    {
                        printf("\033[31mDaily limit exceeded\033[0m\n");
                        fclose(accounts);
                        fclose(temp);
                        return;
                    }
                    a.balance -= amount;

                    printf("\033[32mTransaction Successful! Your new balance is  %.2f$\033[0m\n", a.balance);

                    Saved = Save();
                    if (Saved)
                    {
                        fprintf(temp, "%lld,%s,%s,%.2f,%s,%d-%d,%s\n", a.number, a.name, a.email, a.balance, a.mobile, a.date.month, a.date.year, a.status);
                        char str3[100];
                        sprintf(str3, "%lld", a.number);
                        strcat(str3, ".txt");
                        FILE *ff = fopen(str3, "a");

                        time_t now = time(NULL);
                        struct tm *t = localtime(&now);
                        int day = t->tm_mday;
                        int month = t->tm_mon + 1;
                        int year = t->tm_year + 1900;

                        fprintf(ff, "%s,%d,%d-%d-%d\n", "Withdraw", amount, day, month, year);
                        fclose(ff);
                    }
                    else
                    {
                        a.balance += amount;
                        fprintf(temp, "%lld,%s,%s,%.2f,%s,%d-%d,%s\n", a.number, a.name, a.email, a.balance, a.mobile, a.date.month, a.date.year, a.status);
                        printf("\033[31mOperation Abandoned\033[0m\n");
                    }
                }
            }
            else
            {
                printf("\033[31mError, account inactive.\033[0m\n");
                fprintf(temp, "%s", lineCopy);
            }
        }
        else
        {
            fprintf(temp, "%s", lineCopy);
        }
    }

    fclose(accounts);
    fclose(temp);

    if (!found)
    {
        printf("\033[31mUser not found.\033[0m\n");
        remove("temp.txt");
    }
    else
    {
        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");
    }
}

void Deposit()
{
    FILE *accounts = fopen("accounts.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    int Saved;

    if (accounts == NULL || temp == NULL)
    {
        printf("\033[31mFailed to open files.\033[0m\n");
        remove("temp.txt");
        return;
    }

    char string[200];
    char lineCopy[200];
    long long int num;
    int amount, found = 0;
    account a;
    char str[100];
    printf("Please enter account number: ");
    scanf("%s", str);
    char *ptr = str;
    while (*ptr != '\0')
    {

        if (!isdigit(*ptr))
        {
            printf("\033[31mEnter a valid number\033[0m\n");
            fclose(accounts);
            fclose(temp);
            remove("temp.txt");
            return;
        }
        ptr++;
    }
    num = atoll(str);

    while (fgets(string, 200, accounts) != NULL)
    {

        strcpy(lineCopy, string);

        char *token = strtok(string, ",");

        if (token != NULL && atoll(token) == num)
        {
            found = 1;

            a.number = atoll(token);
            token = strtok(NULL, ",");
            strcpy(a.name, token);
            if (!token)
                continue;
            token = strtok(NULL, ",");
            strcpy(a.email, token);
            if (!token)
                continue;
            token = strtok(NULL, ",");
            a.balance = atof(token);
            if (!token)
                continue;
            token = strtok(NULL, ",");
            strcpy(a.mobile, token);
            if (!token)
                continue;
            token = strtok(NULL, "-");
            a.date.month = atoi(token);
            if (!token)
                continue;
            token = strtok(NULL, ",");
            a.date.year = atoi(token);
            if (!token)
                continue;
            token = strtok(NULL, ",");
            if (!token)
                continue;
            strcpy(a.status, token);
            a.status[strcspn(a.status, "\r\n")] = '\0';

            if (strcmp(a.status, " active") == 0)
            {

                do
                {
                    char str2[100];

                    printf("Please enter the amount you wish to deposit (Balance: %.2f)(maximum $10,000): ", a.balance);
                    scanf("%s", str2);
                    char *ptr2 = str2;
                    while (*ptr2 != '\0')
                    {

                        if (!isdigit(*ptr2) || atoi(str2) <= 0)
                        {
                            printf("\033[31mEnter a valid number\033[0m\n");
                            fclose(accounts);
                            fclose(temp);
                            remove("temp.txt");
                            return;
                        }
                        ptr2++;
                    }
                    amount = atoi(str2);
                } while (amount > 10000);
                a.balance += amount;

                printf("\033[32mTransaction Successful! Your balance is  %.2f$\033[0m\n", a.balance);

                Saved = Save();
                if (Saved)
                {
                    fprintf(temp, "%lld,%s,%s,%.2f,%s,%d-%d,%s\n", a.number, a.name, a.email, a.balance, a.mobile, a.date.month, a.date.year, a.status);
                    char str3[100];
                    sprintf(str3, "%lld", a.number);
                    strcat(str3, ".txt");
                    FILE *ff = fopen(str3, "a");

                    time_t now = time(NULL);
                    struct tm *t = localtime(&now);
                    int day = t->tm_mday;
                    int month = t->tm_mon + 1;
                    int year = t->tm_year + 1900;

                    fprintf(ff, "%s,%d,%d-%d-%d\n", "Deposit", amount, day, month, year);
                    fclose(ff);
                }
                else
                {
                    a.balance -= amount;
                    fprintf(temp, "%lld,%s,%s,%.2f,%s,%d-%d,%s\n", a.number, a.name, a.email, a.balance, a.mobile, a.date.month, a.date.year, a.status);
                    printf("\033[31mOperation Abandoned\033[0m\n");
                }
            }
            else if (strcmp(a.status, " inactive") == 0)
            {
                printf("\033[31mError, account inactive.\033[0m\n");
                fprintf(temp, "%s", lineCopy);
            }
        }
        else
        {
            fprintf(temp, "%s", lineCopy);
        }
    }
    fclose(accounts);
    fclose(temp);
    if (!found)
    {
        printf("\033[31mUser not found.\033[0m\n");
        remove("temp.txt");
    }
    else
    {
        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");
    }
}

void Transfer()
{
    FILE *accounts = fopen("accounts.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL || accounts == NULL)
    {
        printf("\033[31mError in opening the files\033[0m\n");
        remove("temp.txt");
        return;
    }

    char string[200];
    char lineCopy[201];
    long long int num1, num2;
    int amount, found1 = 0, found2 = 0;
    account a1, a2;
    char str[100];
    printf("Please Enter Sender Account Number: ");
    scanf("%s", str);
    char *ptr = str;
    while (*ptr != '\0')
    {

        if (!isdigit(*ptr))
        {
            printf("\033[31mEnter a valid number\033[0m\n");
            fclose(accounts);
            fclose(temp);
            remove("temp.txt");
            return;
        }
        ptr++;
    }
    num1 = atoll(str);
    if (uniqueAccountNumber(num1) == 1)
    {
        printf("\033[31mSender Doesnt Exist\033[0m\n");
        fclose(accounts);
        fclose(temp);
        remove("temp.txt");
        return;
    }

    char str1[100];
    printf("Please Enter Reciever Account Number: ");
    scanf("%s", str1);
    char *ptr1 = str1;
    while (*ptr1 != '\0')
    {

        if (!isdigit(*ptr1))
        {
            printf("\033[31mEnter a valid number\033[0m\n");
            fclose(temp);
            fclose(accounts);
            remove("temp.txt");
            return;
        }
        ptr1++;
    }
    num2 = atoll(str1);
    if (uniqueAccountNumber(num2) == 1)
    {
        printf("\033[31mReciever Doesnt Exist\033[0m\n");
        fclose(temp);
        fclose(accounts);
        remove("temp.txt");
        return;
    }
    if (num1 == num2)
    {
        printf("\033[31mYou can't transfer to yourself!\033[0m\n");
        fclose(temp);
        fclose(accounts);
        remove("temp.txt");
        return;
    }
    int Saved = 0;

    if (accounts == NULL || temp == NULL)
    {
        printf("\033[31mFailed to open files.\033[0m\n");
        remove("temp.txt");
        return;
    }
    while (fgets(string, sizeof(string), accounts))
    {
        char *token = strtok(string, ",");
        if (!token)
            continue;
        long long int temp = atoll(token);
        if (temp == num1)
        {
            found1 = 1;
            a1.number = num1;

            token = strtok(NULL, ",");
            if (!token)
                continue;
            strcpy(a1.name, token);

            token = strtok(NULL, ",");
            if (!token)
                continue;
            strcpy(a1.email, token);

            token = strtok(NULL, ",");
            if (!token)
                continue;
            a1.balance = atof(token);

            token = strtok(NULL, ",");
            if (!token)
                continue;
            strcpy(a1.mobile, token);

            token = strtok(NULL, ",-");
            if (!token)
                continue;
            a1.date.month = atoi(token);

            token = strtok(NULL, ",-");
            if (!token)
                continue;
            a1.date.year = atoi(token);

            token = strtok(NULL, ",-");
            if (!token)
                continue;
            strcpy(a1.status, token);
        }
        if (temp == num2)
        {
            found2 = 1;
            a2.number = num2;

            token = strtok(NULL, ",");
            if (!token)
                continue;
            strcpy(a2.name, token);

            token = strtok(NULL, ",");
            if (!token)
                continue;
            strcpy(a2.email, token);

            token = strtok(NULL, ",");
            if (!token)
                continue;
            a2.balance = atof(token);

            token = strtok(NULL, ",");
            if (!token)
                continue;
            strcpy(a2.mobile, token);

            token = strtok(NULL, ",-");
            if (!token)
                continue;
            a2.date.month = atoi(token);

            token = strtok(NULL, ",-");
            if (!token)
                continue;
            a2.date.year = atoi(token);

            token = strtok(NULL, ",-");
            if (!token)
                continue;
            strcpy(a2.status, token);
        }
    }

    a1.status[strcspn(a1.status, "\r\n")] = '\0';
    a2.status[strcspn(a2.status, "\r\n")] = '\0';
    if (strcmp(a1.status, " inactive") == 0)
    {
        printf("\033[31mSender is Inactive\033[0m\n");
        fclose(accounts);
        fclose(temp);
        remove("temp.txt");
        return;
    }

    if (strcmp(a2.status, " inactive") == 0)
    {
        printf("\033[31mReciever is Inactive\033[0m\n");
        fclose(accounts);
        fclose(temp);
        remove("temp.txt");
        return;
    }
    float cash = 0;
    char str3[100];
    printf("Enter the amount you wish to send (Sender's Balance: %.2f$)(Reciever's Balance: %.2f$): ", a1.balance, a2.balance);
    scanf("%s", str3);
    char *ptr3 = str3;
    while (*ptr3)
    {
        if (!isdigit(*ptr3))
        {
            printf("\033[31mEnter a Valid number\033[0m\n");
            fclose(temp);
            fclose(accounts);
            remove("temp.txt");
            return;
        }
        ptr3++;
    }
    cash = atof(str3);
    if (cash > a1.balance)
    {
        printf("\033[31mThis amount exceeds the sender's balance\033[0m\n");
        fclose(accounts);
        fclose(temp);
        remove("temp.txt");
        return;
    }
    else if (cash <= 0)
    {
        printf("\033[31mYou cant transfer zero or negative dollars!\033[0m\n");
        fclose(accounts);
        fclose(temp);
        remove("temp.txt");
        return;
    }

    a1.balance -= cash;
    a2.balance += cash;
    fseek(accounts, 0, SEEK_SET);
    while (fgets(string, sizeof(string), accounts))
    {
        strcpy(lineCopy, string);

        char *token2 = strtok(string, ",");
        if (!token2)
            continue;

        long long int tempn = atoll(token2);
        if (tempn == num1)
        {
            fprintf(temp, "%lld,%s,%s,%f,%s,%d-%d,%s\n", a1.number, a1.name, a1.email, a1.balance, a1.mobile, a1.date.month, a1.date.year, a1.status);
        }
        else if (tempn == num2)
        {
            fprintf(temp, "%lld,%s,%s,%f,%s,%d-%d,%s\n", a2.number, a2.name, a2.email, a2.balance, a2.mobile, a2.date.month, a2.date.year, a2.status);
        }
        else
        {
            fputs(lineCopy, temp);
        }
    }
    Saved = Save();
    if (Saved)
    {
        char v1[100];
        sprintf(v1, "%lld", num1);
        strcat(v1, ".txt");
        char v2[100];
        sprintf(v2, "%lld", num2);
        strcat(v2, ".txt");
        FILE *f = fopen(v1, "a");
        FILE *ff = fopen(v2, "a");

        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        int day = t->tm_mday;
        int month = t->tm_mon + 1;
        int year = t->tm_year + 1900;

        fprintf(f, "%s,%lld,%lld,-%f,%d-%d-%d\n", "Transfer", num1, num2, cash, day, month, year);
        fprintf(ff, "%s,%lld,%lld,+%f,%d-%d-%d\n", "Transfer", num1, num2, cash, day, month, year);

        fclose(f);
        fclose(ff);

        fclose(accounts);
        fclose(temp);
        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");
        printf("\033[32mTransaction Successful!\033[0m\n");
    }
    else
    {
        printf("\033[31mOperation Abandoned\033[0m\n");
        fclose(accounts);
        fclose(temp);
        remove("temp.txt");
    }
}

int LLogin()
{
    FILE *users = fopen("users.txt", "r");
    if (users == NULL)
    {
        printf("\033[31m Failed to open the txt file\033[0m\n");
        return 0;
    }

    char pass[100];
    char user[100];

    int found = 0;
    int login = 0;
    char string[100];
    printf("Enter Username: ");
    scanf("%s", user);
    printf("Enter Password: ");
    scanf("%s", pass);

    while (fgets(string, 100, users) != NULL)
    {

        char *username = strtok(string, " \n\r"); // This was done by debugging the last two characters and checking their ASCII integer codes
        char *password;
        password = strtok(NULL, " \n\r");

        if (strcmp(user, username) == 0)
        {
            if (strcmp(pass, password) == 0)
            {
                printf("\033[32mAccess Granted\033[0m\n");
                login = 1;
                fclose(users);
                return 1;
            }

            else
            {
                printf("\033[31mWrong Password\033[0m\n");
                fclose(users);
                return 0;
            }

            found = 1;
            break;
        }

        else
            continue;
    }
    if (!found)
        printf("\033[31mUser not found\033[0m\n");

    fclose(users);
    return 0;
}

void Quit()
{
    printf("\033[32mYou have exited the program\033[0m\n");
    exit(1);
}

void Report()
{
    int flag = 0;
    printf("Enter account number: ");
    char acc[100];
    long long int num;
    scanf("%lld", &num);
    flag = uniqueAccountNumber(num);
    if (flag == 1)
    {
        printf("\033[31mUser Doesnt exist\033[0m\n");
        return;
    }
    sprintf(acc, "%lld", num);
    strcat(acc, ".txt");
    FILE *f = fopen(acc, "r");
    if (f == NULL)
    {
        printf("\033[31mError opening file!\033[0m\n");
        return;
    }
    int ch, count = 0;
    ch = fgetc(f);
    if (ch == '\n' || ch == '\r' || ch == EOF)
    {
        printf("\033[31mUser has no record\033[0m\n");
        fclose(f);
        return;
    }
    rewind(f);

    char line[200];
    while ((ch = fgetc(f)) != EOF)
    {

        if (ch == '\n')
            count++;
    }
    rewind(f);
    int index = (count > 5) ? count - 5 : 0;
    int i = 0;
    while (fgets(line, sizeof(line), f) != NULL)
    {
        if (i >= index)
            printf("\033[33m%s\033[0m", line);
        i++;
    }
    fclose(f);
}

void Menu()
{
    int flag = 0;
    while (1)
    {
        printf("-LOGIN\n-QUIT\n");
        char str[100];
        str[strcspn(str, "\n\r")] = '\0';
        scanf("%s", str);
        char *s = str;
        while (*s)
        {
            if (isalpha(*s))
                *s = tolower(*s);
            s++;
        }
        if (strcmp(str, "login") == 0)
        {
            flag = LLogin();
            if (flag == 1)
            {
                Load();
                while (1)
                {
                    // Load();
                    printf("-ADD\n-DELETE\n-DELETE_MULTIPLE\n-MODIFY\n-SEARCH\n-ADVANCED_SEARCH\n-CHANGE_STATUS\n-WITHDRAW\n-DEPOSIT\n-TRANSFER\n-REPORT\n-PRINT\n-QUIT\n");
                    printf("Choose an option: ");
                    char str2[100];
                    scanf("%s", str2);
                    getchar();
                    str2[strcspn(str2, "\n\r")] = '\0';
                    char *s2 = str2;
                    while (*s2)
                    {
                        if (isalpha(*s2))
                            *s2 = tolower(*s2);
                        s2++;
                    }
                    if (strcmp(str2, "add") == 0)
                        addAccount();
                    else if (strcmp(str2, "delete") == 0)
                        deleteAccount();
                    else if (strcmp(str2, "delete_multiple") == 0)
                        deleteMultiple();
                    else if (strcmp(str2, "modify") == 0)
                        modifyAccount();
                    else if (strcmp(str2, "search") == 0)
                        Query();
                    else if (strcmp(str2, "advanced_search") == 0)
                        Advanced_Search();
                    else if (strcmp(str2, "change_status") == 0)
                        changeStatus();
                    else if (strcmp(str2, "withdraw") == 0)
                        Withdraw();
                    else if (strcmp(str2, "deposit") == 0)
                        Deposit();
                    else if (strcmp(str2, "transfer") == 0)
                        Transfer();
                    else if (strcmp(str2, "report") == 0)
                        Report();
                    else if (strcmp(str2, "print") == 0)
                        Print();
                    else if (strcmp(str2, "quit") == 0)
                        Quit();
                    else
                        printf("\033[31mInvalid input!\nplease try again.\033[0m\n");
                }
            }
            else if (flag == 0)
                continue;
        }
        else if (strcmp(str, "quit") == 0)
            Quit();
        else
        {
            printf("\033[31mInvalid Input!\nplease try again..\033[0m\n");
            continue;
        }
        break;
    }
}
