#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void Diary_read(char* n);
void Diary_create(char* n);
void Diary_delete(char* n);
void Sort_by_date(char* n);
void Change_status(char *n);
_Bool Data_check(int y, int m,int d);

struct dairy
{
    char Title[20];
    char Content[100];
    int Words_count;
    char status[4];
    int date;
} Diary[1024];


void main()
{
    
    char txt[1024];
    printf("Enter the diary storage address to open.If not, it will create a new diary.\n");
    scanf("%s", txt);
    char* address = txt;

    for (; ; )
    {
        printf("Diary Home Page.\n\
Enter the number below to run the order.\n\
1.Check all diaries.\n\
2.Create new diary.\n\
3.Delete diary.\n\
4.Sort diaries by date.\n\
5.Change diary status.\n\
6.Quit.\n");
        int order;
        scanf("%d", &order);

        if (order < 1 | order > 6)
        {
            printf("Order error");
            exit(0);
        }

        switch (order)
        {
            case 1:
                Diary_read(address);
                break;
            case 2:
                Diary_create(address);
                break;
            case 3:
                Diary_delete(address);
                break;
            case 4:
                Sort_by_date(address);
                break;
            case 5:
                Change_status(address);
                break;
            case 6:
                exit(0);
        }
    }
}


_Bool data_check(int y, int m, int d)
{
    int max;
    if (y%400 == 0) max = 29;
    else if (y%100 == 0 && y%4 == 0) max = 29;
    else max = 28;
    
    if (y <= 0 | y > 2023)
    {
        return false;
    }
    if (m <= 0 | m > 12)
    {
        return false;
    }
    if (d <= 0 | d > 31)
    {
        return false;
    }

    
    if (m == 1 | m == 3 | m == 5 | m == 7 | m == 8 | m == 10 | m == 12)
    {
        if (d <= 0 | d > 31) return false;
        else return true;
    }
    else if (m == 2)
    {
        if (d <= 0 | d > max) return false;
        else return true;
    }
    else
    {
        if (d <= 0 | d > 30) return false;
        else return true;
    }
}

void Diary_read(char* n)
{
    FILE* fp = NULL;
    fp = fopen(n, "a+");
    rewind(fp);

    char* file_row_count[1024];
    int count = 0;

    printf("-----------------------------------------\n");
    while(fgets(file_row_count, 1024, fp) != NULL)
    {    
        printf("%d|  %s", ++count, file_row_count);
    }
    printf("-----------------------------------------\n");

    fclose(fp);
}

void Diary_create(char* n)
{
    printf("Enter the diary title.\n");
    scanf("%s", &Diary[0].Title);

    printf("Enter the diary content.\n");
    scanf("%s", &Diary[0].Content);

    int i;
    for (i = 0; Diary[0].Content[i] != '\0'; i++);
    Diary[0].Words_count = i;

    printf("Enter the diary status (Yes / No).\n");
    scanf("%s", &Diary[0].status);

    int y;
    int m;
    int d;
    printf("Enter the create time (year).\n");
    scanf("%d", &y);
    printf("Enter the create time (month).\n");
    scanf("%d", &m);
    printf("Enter the create time (day).\n");
    scanf("%d", &d);

    if (data_check(y, m, d) == false)
    {
        printf("Error time_value");
        exit(0);
    }
    else
    {
        FILE* fp = NULL;
        fp = fopen(n, "a");

        if (1 <= m && m < 10)
        {
            if (1 <= d && d < 10)    
            {   
                fprintf(fp, "%s %s %d %s %d0%d0%d\n", Diary[0].Title, 
                                                    Diary[0].Content, 
                                                    Diary[0].Words_count, 
                                                    Diary[0].status, 
                                                    y, 
                                                    m, 
                                                    d);
            }
            else
            {
                fprintf(fp, "%s %s %d %s %d0%d%d\n", Diary[0].Title, 
                                                    Diary[0].Content, 
                                                    Diary[0].Words_count, 
                                                    Diary[0].status, 
                                                    y, 
                                                    m, 
                                                    d);
            }

        }
        else
        {
            if (1 <= d && d < 10)
            {
                fprintf(fp, "%s %s %d %s %d%d0%d\n", Diary[0].Title,
                                                    Diary[0].Content,
                                                    Diary[0].Words_count,
                                                    Diary[0].status, 
                                                    y, 
                                                    m, 
                                                    d);
            }
            else
            {
                fprintf(fp, "%s %s %d %s %d%d%d\n", Diary[0].Title,
                                                    Diary[0].Content,
                                                    Diary[0].Words_count,
                                                    Diary[0].status, 
                                                    y, 
                                                    m, 
                                                    d);
            }      
        }

        fclose(fp);
    }
}

void Diary_delete(char* n)
{
    Diary_read(n);
    
    printf("Enter the number below to run the order.\n\
1.Delete all diaries.\n\
2.Delete one diary by row-number.\n");
    int check;
    scanf("%d", &check);

    if (check == 1)
    {
        FILE* fp = NULL;
        fp = fopen(n, "w");
        fclose(fp);
    }
    else if (check == 2)
    {
        printf("Enter the row-number to delete one diary.\n");
        int num;
        scanf("%d", &num);

        FILE* fp = NULL;
        fp = fopen(n, "r");
        
        int row_count = 0;
        char* file_txt[1024];
        while(fgets(file_txt, 1024, fp) != NULL)
        {
            row_count++;
        }
        rewind(fp);

        for (int i = 0; i <= row_count - 1; i++)
        {
            fscanf(fp, "%s %s %d %s %d", &Diary[i].Title, 
                                         &Diary[i].Content, 
                                         &Diary[i].Words_count, 
                                         &Diary[i].status,
                                         &Diary[i].date);
        }
        fclose(fp);

        FILE* fp_copy = NULL;
        fp_copy = fopen(n, "w");

        for (int i = 0; i<= row_count - 1; i++)
        {
            if (i != num - 1)
            {
                fprintf(fp_copy, "%s %s %d %s %d\n", Diary[i].Title,
                                                     Diary[i].Content,
                                                     Diary[i].Words_count,
                                                     Diary[i].status,
                                                     Diary[i].date);
            }
            else
            {
                continue;
            }
        }
        fclose(fp_copy);
        printf("Done.\n");
    }
    else
    {
        printf("Order error");
        exit(0);
    }
}

void Sort_by_date(char* n)
{
    FILE* fp = NULL;
    fp = fopen(n, "a+");
    rewind(fp);
        
    int row_count = 0;
    char* file_txt[1024];
    while(fgets(file_txt, 1024, fp) != NULL)
    {
        row_count++;
    }
    rewind(fp);

    int* date_list = (int*)malloc(sizeof(int) * row_count);
    int* date_list_check = (int*)malloc(sizeof(int) * row_count);
    for (int i = 0; i <= row_count - 1; i++)
    {
        fscanf(fp, "%s %s %d %s %d", &Diary[i].Title, 
                                     &Diary[i].Content, 
                                     &Diary[i].Words_count, 
                                     &Diary[i].status,
                                     &Diary[i].date);
        date_list[i] = Diary[i].date;
    }
    fclose(fp);

    int j;
    int save;
    for (int i = 1; i < row_count; i++)
    {
        save = date_list[i];
        for (j = i - 1; 0 <= j && date_list[j] > save; j--)
        {
            date_list[j + 1] = date_list[j];
        }
        date_list[j + 1] = save;
    }

    for (int i = 0; i <= row_count - 1; i++)
    {
        if (date_list[i] != date_list[i + 1])
        {
            date_list_check[i] = date_list[i];
        }
        else
        {
            continue;
        }
    }

    FILE* fp_copy = NULL;
    fp_copy = fopen(n, "w");

    for (int x = row_count - 1; x >= 0; x--)
    {
        for (int y = 0; y <= row_count - 1; y++)
        {
            if (Diary[y].date == date_list_check[x])
            {
                fprintf(fp_copy, "%s %s %d %s %d\n", Diary[y].Title,
                                                     Diary[y].Content,
                                                     Diary[y].Words_count,
                                                     Diary[y].status,
                                                     Diary[y].date);
            }
            else
            {
                continue;
            }
        }
    }

    fclose(fp_copy);
    printf("Done.\n");
}

void Change_status(char* n)
{
    Diary_read(n);
    printf("Enter the number below to run the order.\n\
1.Change all 'Yes' to 'No'.\n\
2.Change all 'No' to 'Yes'.\n\
3.Change one diary-status by row-number.\n");
    int check;
    scanf("%d", &check);

    FILE* fp = NULL;
    fp = fopen(n, "a+");
    rewind(fp);
        
    int row_count = 0;
    char* file_txt[1024];
    while(fgets(file_txt, 1024, fp) != NULL)
    {
        row_count++;
    }
    rewind(fp);

    for (int i = 0; i <= row_count - 1; i++)
    {
        fscanf(fp, "%s %s %d %s %d", &Diary[i].Title, 
                                     &Diary[i].Content, 
                                     &Diary[i].Words_count, 
                                     &Diary[i].status,
                                     &Diary[i].date);
    }
    fclose(fp);

    if (check == 1)
    {
        for (int i = 0; i <= row_count - 1; i++)
        {
            strcpy(Diary[i].status, "No");
        }
    }
    else if (check == 2)
    {
        for (int i = 0; i <= row_count - 1; i++)
        {
            strcpy(Diary[i].status, "Yes");
        }
    }
    else if (check == 3)
    {
        printf("Enter the row-number to change the diary-status.\n");
        int num;
        scanf("%d", &num);
        printf("Enter the new diary-status. (Yes / No)\n");
        char new_status[4];
        scanf("%s", &new_status);
        strcpy(Diary[num-1].status, new_status);
    }
    else
    {
        printf("Order error");
        exit(0);
    }

    FILE* fp_copy = NULL;
    fp_copy = fopen(n, "w");
    for (int i = 0; i <= row_count - 1; i++)
    {
        fprintf(fp, "%s %s %d %s %d\n", Diary[i].Title, 
                                        Diary[i].Content, 
                                        Diary[i].Words_count, 
                                        Diary[i].status,
                                        Diary[i].date);
    }
    fclose(fp_copy);
    printf("Done.\n");
}