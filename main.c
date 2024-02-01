#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct
{
    int month;
    int year;
} date;
typedef struct
{
    char ISBN[14];
    char title[100];
    char author[100];
    int quantity;
    float price;
    date pubdate;
} book;
int i=0,checksave=0,showmenu=1; //global variables to use in all functions
book bk[1000];
char months[12][20]= {"January","February","March","April","May","June","July","August","September","October","November","December"};//string to print month names instead of numbers
void sortbytitle()
{
    book temp;
    for(int pass=1; pass<i; pass++) //a pass to sort an element to its place each time
    {

        for(int j=0; j<i-pass; j++) // the element that will be compared to each element  until i-pass because each pass sorts an element to its place
        {
            if(strcasecmp(bk[j].title,bk[j+1].title)>0)//swaps if j should be alphabetically after j+1
            {
                temp=bk[j];
                bk[j]=bk[j+1];
                bk[j+1]=temp;
            }
        }
    }
    for(int k=0; k<i; k++) //printing the right order after sorting
    {
        printf("ISBN:%s\n",bk[k].ISBN);
        printf("Title:%s\n",bk[k].title);
        printf("Author:%s\n",bk[k].author);
        printf("Quantity:%d\n",bk[k].quantity);
        printf("Price:%f\n",bk[k].price);
        printf("Published:%s %d\n",months[(bk[k].pubdate.month)-1],bk[k].pubdate.year);
        printf("\n");
    }
    MENU();
}
void sortbyprice()
{
    book temp;
    for(int pass=1; pass<i; pass++)
    {

        for(int j=0; j<i-pass; j++)
        {
            if(bk[j].price>bk[j+1].price)
            {
                temp=bk[j];
                bk[j]=bk[j+1];
                bk[j+1]=temp;
            }
        }
    }

    for(int k=0; k<i; k++)
    {
        printf("ISBN:%s\n",bk[k].ISBN);
        printf("Title:%s\n",bk[k].title);
        printf("Author:%s\n",bk[k].author);
        printf("Quantity:%d\n",bk[k].quantity);
        printf("Price:%f\n",bk[k].price);
        printf("Published:%s %d\n",months[(bk[k].pubdate.month)-1],bk[k].pubdate.year);
        printf("\n");
    }
    MENU();
}
void sortbydate()
{
    book temp;
    for(int pass=1; pass<i; pass++)
    {

        for(int j=0; j<i-pass; j++)
        {
            if((bk[j].pubdate.year<bk[j+1].pubdate.year)||(bk[j].pubdate.year==bk[j+1].pubdate.year&&bk[j].pubdate.month<bk[j+1].pubdate.month))//from newest to oldest, if they're in the same year then months are compared
            {
                temp=bk[j];
                bk[j]=bk[j+1];
                bk[j+1]=temp;
            }
        }
    }
    for(int k=0; k<i; k++)
    {
        printf("ISBN:%s\n",bk[k].ISBN);
        printf("Title:%s\n",bk[k].title);
        printf("Author:%s\n",bk[k].author);
        printf("Quantity:%d\n",bk[k].quantity);
        printf("Price:%f\n",bk[k].price);
        printf("Published:%s %d\n",months[(bk[k].pubdate.month)-1],bk[k].pubdate.year);
        printf("\n");
    }
    MENU();
}
void Validation_ISBN(char*n)
{
    int temp=0,kee=0;//temp checking for length,kee checking for digits
    if(strlen(n)!=13)//if the length is not 13
    {
        while(temp==0||kee==0)//as long as one of them equals zero, something is wrong with the ISBN
        {
            printf("Enter correct ISBN number(contains 13 digit):\n");
            gets(n);
            if(strlen(n)==13)//enters if length is 13, if not then back to while loop
            {
                temp=1;//length is 13
                kee=1;//assume they're all digits
            }
            for(int k=0; k<13&&kee==1; k++) //check each element that is a digit
            {
                if(!(n[k]>='0'&&n[k]<='9'))
                {
                    kee=0;//any element that is not a digit will make kee equal zero and back to while loop
                }
            }
        }
    }
    else if(strlen(n)==13)//if length from the beginning is 13, will check they're all digits the same way
    {
        kee=0;
        while(kee==0)
        {
            kee=1;
            for(int k=0; k<13&&kee==1; k++) //check each element that is a digit
            {
                if(!(n[k]>='0'&&n[k]<='9'))
                {
                    kee=0;
                    if(kee==0)
                    {
                        printf("Enter correct ISBN number(contains 13 digit):\n");
                        gets(n);
                    }
                }
            }
        }
    }
}
int Validation_pubdate(char mon[],char ye[])
{
    int j;
    int k;
    for(j=0; j<strlen(mon); j++)//loops every element of the months string
    {
        if(!isdigit(mon[j])) //check that there's no char "each element alone",if any char is found then return 0
            return 0;
    }
    int x=atoi(mon); //change from string to int
    if(!(x>=1&&x<=12))
        return 0;

    for(k=0; k<strlen(ye); k++)//check year same way as with month
    {
        if(!isdigit(ye[k]))
            return 0;
    }
    int y=atoi(ye);
    if(y<=2022)
        return 1;
    else
        return 0;
}
int Validation_int(char*r)
{
    int j;
    for(j=0; j<strlen(r); j++)//loop on each element of the string
    {
        if(!isdigit(r[j]))//checking its all digits, anything that is not a digit return 0
            return 0;
    }
    return 1;
}
int Validation_float(char*r)
{
    int dot,j,k,flag=0;
    for(j=0; j<strlen(r); j++)
    {
        if(r[j]=='.')//if there is "." then its a float
        {
            dot=j;
            for(k=0; k<strlen(r); k++)
            {
                if(!isdigit(r[k])&&k!=dot) //check if there's an element in the string that's a character except the dot
                    return 0;
            }
            flag=1;//all turned out to be digits
        }
        else if (Validation_int(r))//if its not a float it could be an int which is also okay
        {
            flag=1;
            break;
        }
    }
    return flag;
}
void LOGIN()
{
    char logquit[20],j;
    char pass[20]; //password from the user
    char user[20]; //username from the user
    char userfile[20]; //username in the file
    char passfile[20]; //password in the file

    while (1)
    {
        do
        {
            printf("Enter 1 to log in or Enter 2 to quit:\n");
            gets(logquit);
        }
        while(!Validation_int(logquit));//make sure the user chooses 1 or 2
        if(strcmp(logquit,"1")==0)
        {
            printf("Enter username:\n");
            gets(user);
            printf("Enter password:\n");
            gets(pass);
            FILE*f=fopen("credentials.txt","r");
            while(!feof(f))
            {
                fscanf(f,"%s %s",userfile,passfile);
            }
            fclose(f);
            if(strcmp(user,userfile)==0&&strcmp(pass,passfile)==0)//comparing between the data from the user and in file
            {
                MENU();
            }
            else
            {
                printf("username or password incorrect\n");
                LOGIN();
            }
        }

        else if(strcmp(logquit,"2")==0)//quit the program
            exit(0);
        else
        {
            printf("Enter a valid number\n");
            LOGIN();
        }
    }
}
void LOAD()
{
    FILE*f=fopen("books.txt","r");
    while(!feof(f))
    {
        fscanf(f,"%[^,],%[^,],%[^,],%d,%f,%d-%d\n",bk[i].ISBN,bk[i].title,bk[i].author,&bk[i].quantity,&bk[i].price,&bk[i].pubdate.month,&bk[i].pubdate.year);//scan data from file till el comas like how it is in the file cuz scanf will take till space and gets will take the whole line
        i++;
    }
}
void SEARCH(char n[])
{
    int j,flag=0;
    for(j=0; j<i; j++)
    {
        if(!strcmp(n,bk[j].ISBN))//break if comparing equals zero , which means he found the isbn already so no need to continue since each book has different isbn
            break;
    }
    if(j<i)//print book info
    {
        printf("ISBN:%s\n",bk[j].ISBN);
        printf("Title:%s\n",bk[j].title);
        printf("Author:%s\n",bk[j].author);
        printf("Quantity:%d\n",bk[j].quantity);
        printf("Price:%f\n",bk[j].price);
        printf("Published:%s %d\n",months[(bk[j].pubdate.month)-1],bk[j].pubdate.year);
        flag=1;
    }
    if(flag==0)
        printf("NOT FOUND\n");
    MENU();
}
void ADVANCED_SEARCH()
{
    char c[100];
    //search like google
    printf("enter word to find\n");
    gets(c);

    int j,flag=0;//flag zero till the code finds a book searched
    char *src;//pointer for keyword when found
    for(j=0; j<i; j++)
    {
        src=strstr(bk[j].title,c);//creating pointer where word exists to find it
        if(src==NULL)//if the word is not found in titles we search in authors
        {
            src=strstr(bk[j].author,c);
        }
        if(src!=NULL)//if its found "either in title or author"
        {
            printf("ISBN:%s\n",bk[j].ISBN);
            printf("Title:%s\n",bk[j].title);
            printf("Author:%s\n",bk[j].author);
            printf("Quantity:%d\n",bk[j].quantity);
            printf("Price:%f\n",bk[j].price);
            printf("Published:%s %d\n\n",months[(bk[j].pubdate.month)-1],bk[j].pubdate.year);
            flag=1;
        }
    }
    if(flag==0)
        printf("NOT FOUND\n");
    MENU();
}
void ADD()
{
    int duplicate,flag=0;
    printf("Enter the book's ISBN:\n");
    while(!flag)
    {
        flag=1;
        gets(bk[i].ISBN);
        Validation_ISBN(bk[i].ISBN);
        for(duplicate=0; duplicate<i; duplicate++)
        {
            if(!strcmp(bk[i].ISBN,bk[duplicate].ISBN))//checking if the isbn is already in the system
            {
                flag=0;
                printf("This ISBN already exists\n");
                printf("Enter the book's ISBN:\n");
            }
        }

    }

    printf("Enter the book's title:\n");
    gets(bk[i].title);
    printf("Enter the book's author name:\n");
    gets(bk[i].author);
    char qua[100];
    char pri[100];
    do
    {
        printf("Enter the book's quantity:\n");
        gets(qua);
    }
    while(!Validation_int(qua));
    bk[i].quantity=atoi(qua);
    do
    {
        printf("Enter the book's price:\n");
        gets(pri);
    }
    while(!Validation_float(pri));
    bk[i].price=atof(pri);
    char mon[100];
    char ye[100];
    printf("Enter the book's publication date[month & year]:\n");
    gets(mon);
    gets(ye);

    while (Validation_pubdate( mon,ye)==0)//validate the year and month and thats there's no char, if it equals zero then something is wrong
    {
        printf("\nEnter the book's publication date[month & year]:\n");
        gets(mon);
        gets(ye);
    }
    if(Validation_pubdate(mon,ye))//return 1 "true" if the date is valid and can be stored
    {
        bk[i].pubdate.month=atoi(mon);//atoi changes data type char to data type int
        bk[i].pubdate.year=atoi(ye);
    }
    printf("Data is successfully added\n");
    i++;//adding 1 to the number of books
    checksave=0;
    showmenu=1;
    MENU();
}
void MODIFY()
{
    int k,flag=0;
    char modisbn[20];
    printf("Enter the book's isbn:\n");
    gets(modisbn);
    Validation_ISBN(modisbn);//make sure isbn is valid
    for(k=0; k<i; k++)
    {
        if(strcmp(modisbn,bk[k].ISBN)==0)//compare entered isbn to the ones in file to make sure it exists
        {
            printf("enter the title of the book:\n");
            gets(bk[k].title);
            printf("enter the author of the book:\n");
            gets(bk[k].author);
            char qua[100];
            char pri[100];
            do
            {
                printf("Enter the book's quantity:\n");
                gets(qua);
            }
            while(!Validation_int(qua));
            bk[k].quantity=atoi(qua);
            do
            {
                printf("Enter the book's price:\n");
                gets(pri);
            }
            while(!Validation_float(pri));
            bk[k].price=atof(pri);
            char mon[100];
            char ye[100];
            printf("Enter the book's publication date[month & year]:\n");
            gets(mon);
            gets(ye);
            while (Validation_pubdate( mon,ye)==0)
            {
                printf("\nEnter the book's publication date[month & year]:\n");
                gets(mon);
                gets(ye);
            }
            if(Validation_pubdate(mon,ye))
            {
                bk[k].pubdate.month=atoi(mon);
                bk[k].pubdate.year=atoi(ye);
            }
            flag=1;
            printf("Data is successfully modified\n");
        }
    }
    if(flag==0)
    {
        printf("Not found\n");
        MENU();
    }
    checksave=0;
    showmenu=1;
}

void PRINT ()
{
    char type[20];
    do
    {
        printf("please enter the number of sorting:\n");
        printf("1.by price \n2.by date\n3.by title\n");
        gets(type);
    }
    while(!Validation_int(type));//make sure the user chooses 1 or 2 or 3
    if(strcmp(type,"1")==0)
        sortbyprice();
    else if(strcmp(type,"2")==0)
        sortbydate();
    else if(strcmp(type,"3")==0)
        sortbytitle();
    else
    {
        printf("Enter a valid number\n");
        PRINT();
    }
}
void DELETE()
{
    int j,flag=0;
    char delisbn[100];
    printf("Enter the book's isbn\n");
    gets(delisbn);
    Validation_ISBN(delisbn);
    for(j=0; j<i; j++)
    {
        if(strcmp(delisbn,bk[j].ISBN)==0)//if the isbn is found
        {
            bk[j]=bk[i-1];//let the last book in the list over write the book we want to delete
            i--;//removing the las book because we already placed it in place of the deleted one
            printf("Data is successfully deleted\n");
            flag=1;
            break;
        }
    }
    if(!flag)
        printf("NOT FOUND\n");
    checksave=0;
    showmenu=1;
    MENU();
}
void SAVE(int showmenu)
{
    FILE*f=fopen("books.txt","w");
    for(int p=0; p<i; p++)// save data in the file books.txt
    {

        fprintf(f,"%s,%s,%s,%d,%f,%d-%d\n",bk[p].ISBN,bk[p].title,bk[p].author,bk[p].quantity,bk[p].price,bk[p].pubdate.month,bk[p].pubdate.year);

    }
    fclose(f);
    printf("Data is successfully saved\n");
    checksave=1;
    if(showmenu)
        MENU();
    else exit(0);
}
void QUIT()
{
    char ans[5];//users answer to wanting to quit "yes or no"
    if(checksave==0)
    {
        printf("WARNING! your data will be discarded once you quit\nDo you want to save[yes,no]:\n");
        gets(ans);
        if(strcmp(ans,"yes")==0)
            SAVE(0);
        else if(strcmp(ans,"no")==0)
            exit(0);
        else
        {
            printf("Enter a valid data");
            QUIT();
        }
    }
    else
        exit(0);
}
void MENU()
{
    char srch[100], x[100];
    while(1)
    {
        printf("Choose one of the following options\n");
        printf("1.Add\n2.Delete\n3.Modify\n4.Search\n5.Advanced search\n6.Print\n7.Save\n8.Quit\n");
        gets(x);
        if(strcmp(x,"1")==0)
            ADD();
        else if(strcmp(x,"2")==0)
            DELETE();
        else if(strcmp(x,"3")==0)
            MODIFY();
        else if(strcmp(x,"4")==0)
        {
            printf("Enter book ISBN:\n");
            gets(srch);
            Validation_ISBN(srch);
            SEARCH(srch);
        }
        else if(strcmp(x,"5")==0)
            ADVANCED_SEARCH();
        else if(strcmp(x,"6")==0)
            PRINT();
        else if(strcmp(x,"7")==0)
            SAVE(1);
        else if(strcmp(x,"8")==0)
            QUIT();
        else
            printf("\nEnter a valid number\n");
    }
}

int main()
{
    LOAD();
    LOGIN();
    return 0;
}
