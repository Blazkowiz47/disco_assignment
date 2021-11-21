#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int dim = 0;
char websites[999999];

void saveMatrixInFile(int *a)
{
    FILE *fptr;

    fptr = fopen("temp.csv", "wb");
    if (fptr == NULL)
    {
        printf("Can't load file. Exiting.");
        return;
    }
    char *tok;
    int row = 0;
    fprintf(fptr, "%s", websites);
    for (tok = strtok(websites, ",");
         tok && *tok;
         tok = strtok(NULL, ","))
    {

        int index = strlen(tok);
        char *temp = (char *)malloc(sizeof(char) * (index));
        for (int i = 0; i < index; i++)
        {
            if (tok[i] != '\n')
            {
                temp[i] = tok[i];
            }
            else
            {
                index--;
            }
        }
        for (int col = 0; col < dim; col++)
        {

            if (*(a + dim * row + col) == 0)
            {
                temp[index] = '0';
            }
            else
            {
                temp[index] = '1';
            }

            index++;
            if (col != dim - 1)
            {
                temp[index] = ',';
            }
            else
            {
                temp[index] = '\n';
            }
            index++;
        }

        for (int col = 0; col < index; col++)
        {
            if (col == index - 1 && row == dim - 1)
            {
            }
            else
                fprintf(fptr, "%c", temp[col]);
        }
        // TODO: print in the file
        row++;
        free(temp);
    }
    fclose(fptr);
}

void populateMatrix(int *arr, char *line, int row)
{
    int col = 0;
    char *tok;
    for (tok = strtok(line, ",");
         tok && *tok;
         tok = strtok(NULL, ","))
    {
        if (col == 0)
        {
            col++;
            continue;
        }
        *(arr + (row)*dim + (col - 1)) = atoi(tok);
        col++;
    }
}

void printMatrix(int *arr)
{

    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            printf("%d ", *(arr + i * dim + j));
        }
        printf("\n");
    }
}

int getLength(char *line)
{
    int num = 0;
    char *tok;
    for (tok = strtok(line, ",");
         tok && *tok;
         tok = strtok(NULL, ","))
    {
        num++;
    }
    return num;
}

int equal(int *a, int *b)
{
    for (int i = 0; i < dim * dim; i++)
    {
        if (*(a + i) != *(b + i))
            return 0;
    }
    return 1;
}

void copy(int *a,int *b) {
    // Copies matrix [a] into [b]
     for (int i = 0; i < dim * dim; i++)
    {
        *(b + i)=*(a + i);
    }
}

const char *checkReflexive(int *a)
{
    for (int i = 0; i < dim; i++)
    {
        if (*(a + i * dim + i) == 0)
            return "NO";
    }
    return "YES";
}

void reflexiveClosure(int *a, int *c)
{
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            *(c + i * dim + j) = *(a + i * dim + j);
            if (i == j)
            {
                *(c + i * dim + j) = 1;
            }
        }
    }
}

const char *checkSymmetric(int *a)
{
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (*(a + i * dim + j) != *(a + j * dim + i))
            {
                return "NO";
            }
        }
    }
    return "YES";
}

void symmetricClosure(int *a, int *b)
{
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (*(a + i * dim + j) == 1)
            {
                *(b + i * dim + j) = *(a + i * dim + j);
                *(b + j * dim + i) = *(a + i * dim + j);
            }
            else if (*(a + j * dim + i) == 1)
            {
                *(b + j * dim + i) = *(a + j * dim + i);
                *(b + i * dim + j) = *(a + j * dim + i);
            }
            else
            {
                *(b + j * dim + i) = 0;
                *(b + i * dim + j) = 0;
            }
        }
    }
}

void transitiveClosure(int *a,int*b) {
    // Warshalls algorithm

}


int main()
{

    FILE *fp;
    fp = fopen("SampleInput.csv", "r");
    if (fp == NULL)
    {
        printf("Can't load file. Exiting.");
        return 0;
    }
    char line[999999];
    // gets first line which gives us dimension of the matrix
    fgets(line, 999999, fp);
    strcpy(websites, line);
    dim = getLength(line);

    int MATRIX[dim][dim];
    if (MATRIX == NULL)
    {
        printf("Can't allocate space for Matrix. Exiting.");
        return 0;
    }
    int row = 0;

    while (fgets(line, 999999, fp))
    {
        char *tmp = strdup(line);
        populateMatrix(MATRIX[0], tmp, row);
        row++;
        free(tmp);
    }

    int closure[dim][dim];
    // Driver code
    return 0;
}