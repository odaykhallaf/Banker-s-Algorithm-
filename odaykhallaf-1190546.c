#include <stdio.h>
#include <stdlib.h>


//-------------------------------------------------- oday khallaf -1190546--------------------------------------------------------------------------------


#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int P; // Number of processes
int  R; // Number of resources
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int available[MAX_RESOURCES];

void ReadInput(char* file_path)   // to select  file
{
    FILE* file = fopen(file_path, "r"); // to read file
    if (file == NULL)   // if file is null print -->there was an error opening the file, please enter the path correctly
    {
        printf("---------- there was an error opening the file, please enter the path correctly-------- \n");
        exit(1);
    }
// Read the number of processe
    fscanf(file, "%d", &P);
    // Read the number of resource
    fscanf(file, "%d", &R);

    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < R; j++)
        {
            fscanf(file, "%d", &maximum[i][j]);
        }
    }

    // Read the allocation matrix
    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < R; j++)
        {
            fscanf(file, "%d", &allocation[i][j]);
        }
    }

    // Read the available array
    for (int i = 0; i < R; i++)
    {
        fscanf(file, "%d", &available[i]);
    }

    fclose(file);
}

void NeedCalculate()
{
    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < R; j++)
        {
            need[i][j] = maximum[i][j] - allocation[i][j]; // Calculate the need matrix =max- allocate
        }
    }
}
// Initialize the safe state to check it safe or not

int SafeState()
{
    int work[MAX_RESOURCES];
    int finish[P];

    // Initialize the work
    // finish arrays
    for (int i = 0; i < R; i++)
    {
        work[i] = available[i];
    }

    for (int i = 0; i < P; i++)
    {
        finish[i] = 0;
    }

    // Check if the system is a  safe state or not
int count = 0;
int found;
do {
    found = 0;
    for (int i = 0; i < P; i++) {
        if (!finish[i]) {
            int j;
            for (j = 0; j < R; j++) {
                if (need[i][j] > work[j])
                    break;
            }

            if (j == R) {
                for (int k = 0; k < R; k++) {
                    work[k] += allocation[i][k];
                }

                finish[i] = 1;
                found = 1;
                count++;
            }
        }
    }
} while (found && count < P);

    return count == P; // Return  the system is  a safe state
}

int GrantedRequest(int process_id, int* request)   // to check thr request it is granted or not
{
    for (int i = 0; i < R; i++)
    {
        if (request[i] > need[process_id][i] || request[i] > available[i])
        {
            return 0; // Request can not be granted
        }
    }
//to update  allocation, need, and available arrays
    for (int i = 0; i < R; i++)
    {
        available[i] -= request[i];
        allocation[process_id][i] += request[i];
        need[process_id][i] -= request[i];
    }

    return 1; // Request granted successfully
}

void PrintMatrices()
{
    printf("Maximum matrix  \n");
    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < R; j++)
        {
            printf("%d ", maximum[i][j]); // Print the Maximum matrix
        }
        printf("\n");
    }
    printf("\n");

    printf("Allocation matrix:-\n");
    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < R; j++)
        {
            printf("%d ", allocation[i][j]); // Print the allocation matrix
        }
        printf("\n");
    }
    printf("\n");

    printf("need matrix:-\n");
    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < R; j++)
        {
            printf("%d ", need[i][j]); // Print the Need matrix
        }
        printf("\n");
    }
    printf("\n");

    printf("Available array:-\n");
    for (int i = 0; i < R; i++)
    {
        printf("%d ", available[i]); // Print the available array
    }
    printf("\n");
}

int main()
{
    char file_path[100];
    printf("please Enter the file path-------->  ");
    scanf("%s", file_path);
// Read input from the file
    ReadInput(file_path);
// Calculate the need matrix
    NeedCalculate();
// Print the matrices and arrays
    PrintMatrices();

    if (SafeState())
    {
        printf("---------The system it is a safe state------- \n");
        int process_id;
        int request[MAX_RESOURCES];

        printf("please Enter the process ID please----->  ");
        scanf("%d", &process_id);

        printf("please Enter the resource request please -------------> ");
        for (int i = 0; i < R; i++)
        {
            scanf("%d", &request[i]);
        }

        if (GrantedRequest(process_id, request))
        {
            printf("\n");
            printf("Maximum matrix:-\n");
            for (int i = 0; i < P; i++)
            {
                for (int j = 0; j < R; j++)
                {
                    // Print the Maximum matrix after granting the request
                    printf("%d ", maximum[i][j]);
                }
                printf("\n");
            }
            printf("\n");

            printf("----------------Allocation matrix after granting the request---------- \n");
            for (int i = 0; i < P; i++)
            {
                for (int j = 0; j < R; j++)
                {
                    // Print the allocation matrix after granting the request
                    printf("%d ", allocation[i][j]);
                }
                printf("\n");
            }
            printf("\n");

            printf("--------Need matrix after granting the request ---------\n");
            for (int i = 0; i < P; i++)
            {
                for (int j = 0; j < R; j++)
                {
                    // Print the Need matrix after granting the request
                    printf("%d ", need[i][j]);
                }
                printf("\n");
            }
            printf("\n");

            printf("---------Available array after granting the request-------- \n");
            for (int i = 0; i < R; i++)
            {
                // Print the Available array after granting the request
                printf("%d ", available[i]);
            }
            printf("\n");

            if (SafeState())
            {
                printf("-----Safe sequence of processes-------- \n");
                int work[MAX_RESOURCES];
                int finish[P];

                for (int i = 0; i < R; i++)
                {
                    work[i] = available[i];
                }

                for (int i = 0; i < P; i++)
                {
                    finish[i] = 0;
                }


              int found;
do {
    found = 0;
    for (int i = 0; i < P; i++) {
        if (!finish[i]) {
            int j;
            for (j = 0; j < R; j++) {
                if (need[i][j] > work[j])
                    break;
            }

            if (j == R) {
                for (int k = 0; k < R; k++) {
                    work[k] += allocation[i][k];
                }
                printf("P%d ", i); // Print the process in the safe sequence
                finish[i] = 1;
                found = 1;
            }
        }
    }
} while (found);


                printf("\n");
            }
            else
            {
                printf("--------The system is not in a safe state---------- \n");
            }
        }
        else
        {
            printf("------The request can not be granted------- \n");
        }
    }
    else
    {
        printf("------The system is not  a safe state------ \n");
    }

    return 0;
}
