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

                temp[i] = tok[i];

            else

                index--;
        }
        for (int col = 0; col < dim; col++)
        {

            if (*(a + dim * row + col) == 0)

                temp[index] = '0';

            else

                temp[index] = '1';

            index++;
            if (col != dim - 1)

                temp[index] = ',';

            else

                temp[index] = '\n';

            index++;
        }

        for (int col = 0; col < index; col++)
        {
            if (!(col == index - 1 && row == dim - 1))
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

            printf("%d ", *(arr + i * dim + j));

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

        num++;

    return num;
}

int equal(int *a, int *b)
{
    for (int i = 0; i < dim * dim; i++)

        if (*(a + i) != *(b + i))
            return 0;

    return 1;
}

void copy(int *a, int *b)
{
    // Copies matrix [a] into [b]
    for (int i = 0; i < dim * dim; i++)

        *(b + i) = *(a + i);
}

const char *checkReflexive(int *a)
{
    for (int i = 0; i < dim; i++)

        if (*(a + i * dim + i) == 0)
            return "NO";

    return "YES";
}

const char *checkReflexiveElement(int *a)
{
    for (int i = 0; i < dim; i++)

        if (*(a + i * dim + i) == 1)
            return "YES";

    return "NO";
}

void reflexiveClosure(int *a, int *c)
{
    for (int i = 0; i < dim; i++)

        for (int j = 0; j < dim; j++)
        {
            *(c + i * dim + j) = *(a + i * dim + j);
            if (i == j)

                *(c + i * dim + j) = 1;
        }
}

const char *checkSymmetric(int *a)
{
    for (int i = 0; i < dim; i++)

        for (int j = 0; j <= i; j++)

            if (*(a + i * dim + j) != *(a + j * dim + i))

                return "NO";

    return "YES";
}

const char *checkSymmetricElement(int *a)
{
    // its reverse 
    // if there is a symmetric element it will print NO else YES
    for (int i = 0; i < dim; i++)

        for (int j = 0; j < i; j++)

            if (*(a + i * dim + j) == *(a + j * dim + i) && *(a + j * dim + i)  == 1)

                return "NO";

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

const char *checkAntiSymmetricIncludingDiagonal(int *a)
{
    for (int i = 0; i < dim; i++)

        for (int j = 0; j <= i; j++)

            if (*(a + i * dim + j) == *(a + j * dim + i))

                return "NO";

    return "YES";
}

const char *checkAntiSymmetricExcludingDiagonal(int *a)
{
    for (int i = 0; i < dim; i++)
        for (int j = 0; j < i; j++)
            if (*(a + i * dim + j) == *(a + j * dim + i))
                return "NO";
    return "YES";
}

void transitiveClosure(int *a)
{
    // Warshalls algorithm
    for (int k = 0; k < dim; k++)
        for (int i = 0; i < dim; i++)
            for (int j = 0; j < dim; j++)
                *(a + dim * i + j) = *(a + dim * i + j) | (*(a + dim * i + k) & *(a + dim * k + j));
}

void menu4option2(int *a) {
    int len = 0; 
    int *temp;
    temp = calloc(len,sizeof(int));
    int counter = 0;
    for(int col = 0; col < dim;col++){
        int val = 1;
        for(int row = 0;row<dim;row++){
            if(*(a + row*dim + col) == 0){
                val = 0;
                break;
            }
        }
        if(val == 1){
            len++;
            temp = realloc(temp, len*sizeof(int));
            *(temp + counter) = col+1;
            counter++;
        }
    }
    printf("Following are the required websites: \n");
    for(int i = 0; i<len ; i++){
        printf("%d ", *(temp+i));
    }
    printf("\n");
}

void menu4option3(int *a) {
    int len = 0; 
    int *temp;
    temp = calloc(len,sizeof(int));
    int counter = 0;
    for(int row = 0; row < dim;row++){
        int val = 1;
        for(int col = 0;col<dim;col++){
            if(*(a + row*dim + col) == 0){
                val = 0;
                break;
            }
        }
        if(val == 1){
            len++;
            temp = realloc(temp, len*sizeof(int));
            *(temp + counter) = row+1;
            counter++;
        }
    }
    printf("Following are the required websites: \n");
    for(int i = 0; i<len ; i++){
        printf("%d ", *(temp+i));
    }
    printf("\n");
}

void menu4option4(int *a) {
    int len = 0; 
    int *temp;
    temp = calloc(len,sizeof(int));
    int counter = 0;
    for(int row = 0; row < dim;row++){
        int val = 1;
        if(*(a + row*dim + row) == 1) {
            for(int col = 0;col<dim;col++){
                if(col != row && *(a + row*dim + col) == 1){
                    val = 0;
                    break;
                }
            }
            if(val == 1){
                len++;
                temp = realloc(temp, len*sizeof(int));
                *(temp + counter) = row+1;
                counter++;
            }
        }
    }
    if(len == 0){
        printf("No such websites available.\n");
        return;
    }
    printf("Following are the required websites: \n");
    for(int i = 0; i<len ; i++){
        printf("%d ", *(temp+i));
    }
    printf("\n");
}

void menu4option5(int *a) {
    int len = 0; 
    int *temp;
    temp = calloc(len,sizeof(int));
    int counter = 0;
    for(int col = 0; col < dim;col++){
        int val = 1;
        if(*(a + col*dim + col) == 1) {
            for(int row = 0;row<dim;row++){
                if(col != row && *(a + row*dim + col) == 1){
                    val = 0;
                    break;
                }
            }
            if(val == 1){
                len++;
                temp = realloc(temp, len*sizeof(int));
                *(temp + counter) = col+1;
                counter++;
            }
        }
    }
    if(len == 0){
        printf("No such websites available.\n");
        return;
    }
    printf("Following are the required websites: \n");
    for(int i = 0; i<len ; i++){
        printf("%d ", *(temp+i));
    }
    printf("\n");
}

void menu4option6(int *a) {
    printf("Enter all the query website numbers with a comma (\",\") in between.\n");
    char q[999999];
    scanf("%s",q);
    int *query = calloc(0,sizeof(int)); 
    int queryLength = 0;
    int queryIndex = 0;
    char *tok;
    for (tok = strtok(q, ",");
         tok && *tok;
         tok = strtok(NULL, ","))
    {
        queryLength++;
        query = realloc(query,queryLength*sizeof(int));
        *(query + queryIndex) = atoi(tok) - 1;
        queryIndex++;  
    }
    int * result = calloc(0,sizeof(int));
    int resultLen = 0;
    int resultInd = 0;
    for (int col = 0; col < dim;col++) {
        int val = 1;
        for( int i = 0; i < queryLength ; i++ ) {
            if(*(a + (*(query + i))*dim + col ) == 0) {
                val = 0;
                break;
            }
        }
        if(val == 1) {
            resultLen++;
            *(result + resultInd ) = col+1;
            resultInd++;
        }
    }
    if(resultLen ==0) {
        printf("No such websites available.\n");
        return;
    }
    printf("Following are the required websites: \n");
    for(int i = 0; i<resultLen ; i++){
        printf("%d ", *(result+i));
    }
    printf("\n");
}

void menu4option7(int *a) {
    printf("Enter all the query website numbers with a comma (\",\") in between.\n");
    char q[999999];
    scanf("%s",q);
    int *query = calloc(0,sizeof(int)); 
    int queryLength = 0;
    int queryIndex = 0;
    char *tok;
    for (tok = strtok(q, ",");
         tok && *tok;
         tok = strtok(NULL, ","))
    {
        queryLength++;
        query = realloc(query,queryLength*sizeof(int));
        *(query + queryIndex) = atoi(tok) - 1;
        queryIndex++;  
    }
    int * result = calloc(0,sizeof(int));
    int resultLen = 0;
    int resultInd = 0;
    for (int row = 0; row < dim;row++) {
        int val = 1;
        for( int i = 0; i < queryLength ; i++ ) {
            if(*(a + dim*row + *(query + i)) == 0) {
                val = 0;
                break;
            }
        }
        if(val == 1) {
            resultLen++;
            *(result + resultInd ) = row+1;
            resultInd++;
        }
    }
    if(resultLen ==0) {
        printf("No such websites available.\n");
        return;
    }
    printf("Following are the required websites: \n");
    for(int i = 0; i<resultLen ; i++){
        printf("%d ", *(result+i));
    }
    printf("\n");
}

void menu5option1(int*a) {
    int a,b;
    printf("Enter website A: ");
    scanf("%d", &a);
    printf("Enter website b: ");
    scanf("%d", &b);
    if(a > dim || b > dim || a < 0 || b < 0) {
        printf("Please enter valid websites");
        return menu5option1(a);
    }
    
}

int MENU1(){
    printf("Main Menu\n\
    1) Does every website has a link to itself?\n\
    2) Is it possible to always return back to the previous website from the current website in one step?\n\
    3) Does every website has all the links to the websites which are reachable from it?\n\
    4) Does there exist any website that contains a link to itself?\n\
    5) Is it impossible to return to the previous website from the current website in one step?\n\
    6) Is it impossible to return to the previous website from the current website in one step(excluding the cases where the current and previous website is same)?\n\
    7) Is it possible to divide the network into multiple pieces such that every website in a piece is reachable from every other website in that piece?\n\
    8) Is this relation an example of poset?\n\
    9) Exit\n");
    int response;
    scanf("%d",&response);
    return response;
}

int MENU2(){
    printf("Menu2\n\
    Do you want to visualise how the network will look if we add minimum links to satisfy the property?\n\
    1) Yes\n\
    2)No\n");
    int response;
    scanf("%d",&response);
    return response; 
}

int MENU3(){
    printf("Menu3\n\
    Do you want to know the nodes in each piece?\n1)Yes\n2)No\n");
    int response;
    scanf("%d",&response);
    return response; 
}

int MENU4(){
    printf("Menu4\n\
    1) Display the hasse diagram\n\
    2) Display the website whose link is available in every website.\n\
    3) Display the website which has links of every website.\n\
    4) Display the websites that do not have links to any other website except itself.\n\
    5) Display the websites which can't be reached from any other website except itself.\n\
    6) Given some websites, display the websites which are reachable from all of them.\n\
    7) Given some websites, display the websites from which you can reach all those websites. (Process similar to 5)\n\
    8) Is this relation an example of lattice?\n9) Return to Main Menu\n");
    int response;
    scanf("%d",&response);
    return response; 
}

int MENU5(){
    printf("Menu5\n\
    1) Given two websites A and B, display the website which is reachable by both A and B and can also reach to all such websites that both A and B can reach.\n\
    2) Given two websites A and B, display the website which can reach to both A and B is also reachable fro all such websites which can reach both A and B\n\
    3) Is the lattice distriubutive?\n\
    4) Return to Menu 4\n");
    int response;
    scanf("%d",&response);
    return response; 
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
    // retrieve data from file
    while (fgets(line, 999999, fp))
    {
        char *tmp = strdup(line);
        populateMatrix(MATRIX[0], tmp, row);
        row++;
        free(tmp);
    }

    // Initialisation complete
    // Actual driver code starts

    int closure[dim][dim];

    // Actual Driver code starts here
    int response;

    menu4option7(MATRIX[0]);
    
    return 0;
    // // MENU 1 block
    // MENU1:
    // response = MENU1();
    // switch (response)
    // {
    // case 1:
    //     printf("%s",checkReflexive(MATRIX[0]));
    //     break;
    // case 2:
        
    //     printf("%s",checkSymmetric(MATRIX[0]));

    //     break;  
    // case 3:
    //     copy(MATRIX[0],closure[0]);
    //     transitiveClosure(closure[0]);
    //     switch(equal(closure[0], MATRIX[0])) {
    //         case 0:
    //             printf("NO");
    //             break;
    //         case 1:
    //             printf("YES");
    //             break;
    //     }
    //     break;
    // case 4:
    //     printf("%s",checkReflexiveElement(MATRIX[0]));
    //     break;
    // case 5:
    //     printf("%s",checkSymmetricElement(MATRIX[0]));
    //     break;
    // case 6:
    //     printf("%s",checkAntiSymmetricExcludingDiagonal(MATRIX[0]));
    //     break;
    // case 7:
    //     // TODO: complete the function
    //     break;
    // case 8:
    //     // TODO: exeute remining menus
    //     break;
    // case 9:
    //     return 0;
    // default:
    //     printf("Please give input between 1-9\n");
    //     goto MENU1;
    // }
    // printf("\n");
    // goto END;

    // // MENU 4 block 



    // // END Menu Block
    // END:
    // printf("Return Main Menu?\n1) Yes\n2) No\n");
    // scanf("%d",&response);
    // switch (response)
    // {
    // case 1:
    //     goto MENU1;
    // case 2:
    // return 0;
    // default:
    //     printf("Please enter valid input 1 or 2\n");
    //     goto END;
    // }

}