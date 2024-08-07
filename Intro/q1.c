#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
void update(int *BItree, int idx, int val, int n)
{
        while (idx <= n)
        {
                BItree[idx] += val;
                idx += (idx & -idx);
        }
}
int query(int *BItree, int idx)
{
        int sum = 0;
        while (idx > 0)
        {
                sum += BItree[idx];
                idx -= (idx & -idx);
        }
        return sum;
}
void function1(int *Arr, int n)
{
        int *CIarr = (int *)malloc(n * sizeof(int));
        CIarr[0] = Arr[0];
        for (int i = 1; i < n; i++)
                CIarr[i] = CIarr[i - 1] + Arr[i];
        // Query 1
        clock_t start = clock();
        *(Arr + 1) += 5;
        for (int i = 1; i < n; i++)
                CIarr[i] += 5;
        clock_t end = clock();
        double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("By function 1:\n");
        printf("The time taken for query 1 by function 1 is %f seconds\n", cpu_time_used);
        printf("The incremented value of the first index element is %d\n", *(Arr+1));
        // Query 2
        start = clock();
        int sum = CIarr[n - 6];
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("The time taken for query 2 by function 1 is %f seconds\n", cpu_time_used);
        printf("The sum of first n-5 elements is %d\n", sum);
        free(CIarr);
}
void function2(int *Arr, int n)
{
        int *BItree = (int *)malloc((n + 1) * sizeof(int));
        for (int i = 0; i <= n; i++)
                BItree[i] = 0;
        for (int i = 1; i <= n; i++)
                update(BItree, i, Arr[i - 1], n);
        // Query 1
        *(Arr + 1) += 5;
        clock_t start = clock();
        update(BItree, 1, 5, n);
        clock_t end = clock();
        double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("By function 2:\n");
        printf("The time taken for query 1 by function 2 is %f seconds\n", cpu_time_used);
        printf("The incremented value of the first index element is %d\n", *(Arr+1));
        // Query 2
        start = clock();
        int sum = query(BItree, n - 5);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("The time taken for query 2 by function 2 is %f seconds\n", cpu_time_used);
        printf("The sum of first n-5 elements is %d\n", sum);
        free(BItree);
}
int readArrayFromInput(int **Arr)
{
        printf("Please input an integer array with space-separator and press Enter when done: ");
        char input[1000];
        int size = 0;
        int capacity = 10;
        *Arr = (int *)malloc(capacity * sizeof(int));
        fgets(input, sizeof(input), stdin);
        char *token = strtok(input, " ");
        while (token != NULL)
	{
                int value;
                if (sscanf(token, "%d", &value) == 1)
		{
                        if (size >= capacity)
			{
                                capacity *= 2;
                                *Arr = (int *)realloc(*Arr, capacity * sizeof(int));
                                if (*Arr == NULL)
				{
                                        printf("Memory allocation failed\n");
                                        exit(1);
                                }
                        }
                        (*Arr)[size++] = value;
                }
                token = strtok(NULL, " ");
        }
        return size;
}
int readArrayFromFile(char *filename, int **Arr)
{
        FILE *file = fopen(filename, "r");
        if (!file)
	{
                printf("Error opening file\n");
                exit(1);
        }
        int capacity = 10;
        int size = 0;
        *Arr = (int *)malloc(capacity * sizeof(int));
        if (*Arr == NULL)
	{
                printf("Memory allocation failed\n");
                exit(1);
        }
        int value;
        while (fscanf(file, "%d", &value) == 1)
	{
                if (size >= capacity) 
		{
                        capacity *= 2;
                        *Arr = (int *)realloc(*Arr, capacity * sizeof(int));
                        if (*Arr == NULL)
			{
                                printf("Memory allocation failed\n");
                                exit(1);
                        }
                }
                (*Arr)[size++] = value;
        }
        fclose(file);
        return size;
}

int main()
{
        char choice;
        int *Arr, n;
        printf("Please enter a choice: ");
        scanf(" %c", &choice);
        getchar();
        if (choice == 'a')
                n = readArrayFromFile("ExampleFile.txt", &Arr);
        else
                n = readArrayFromInput(&Arr);
        function1(Arr, n);
        function2(Arr, n);
        free(Arr);
        return 0;
}
