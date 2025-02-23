#include <stdio.h>
#include <stdlib.h>

typedef struct array2D
{
    int **arr;
    int rows;
    int cols;
} Matrix;

void initializeWithZero(Matrix mat) {
    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {
            mat.arr[i][j] = 0;
        }
    }
}

Matrix createMatrix(int rows, int cols)
{
    Matrix mat;
    mat.rows = rows;
    mat.cols = cols;
    mat.arr = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
    {
        mat.arr[i] = (int *)malloc(cols * sizeof(int));
    }
    return mat;
}

void printMatrix(Matrix mat, char *matname) {
    printf("%s\n", matname);
    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {
            printf("%d\t", mat.arr[i][j]);
        }
        printf("\n");
    }
}

void addMatrix(Matrix mat1, Matrix mat2, Matrix mat3, int splitindex)
{
    int i,j;
    for(i=0;i<splitindex;i++)
    {
        for(j=0;j<splitindex;j++)
        {
            mat3.arr[i][j]=mat1.arr[i][j]+mat2.arr[i][j];
        }
    }
}

Matrix multiplyMatrices(Matrix mat1, Matrix mat2)
{
    int row1 = mat1.rows;
    int col1 = mat1.cols;
    int row2 = mat2.rows;
    int col2 = mat2.cols;

    int i,j;

    if (col1 != row2)
    {
        printf("\nError: The number of columns in Matrix A  must be equal to the number of rows in Matrix B\n");
        Matrix temp = createMatrix(1, 1);
        temp.arr[0][0] = 0;
        return temp;
    }

    Matrix ResultMatrix = createMatrix(mat1.rows, mat2.cols);

    initializeWithZero(ResultMatrix);

    if (mat1.cols == 1)
    {
        ResultMatrix.arr[0][0] = mat1.arr[0][0] * mat2.arr[0][0];
    }
    else
    {
        int splitIndex=mat1.cols/2;

        Matrix ResultMatrix_00 = createMatrix(splitIndex,splitIndex);
        Matrix ResultMatrix_01 = createMatrix(splitIndex,splitIndex);
        Matrix ResultMatrix_10 = createMatrix(splitIndex,splitIndex);
        Matrix ResultMatrix_11 = createMatrix(splitIndex,splitIndex);

        initializeWithZero(ResultMatrix_00);
        initializeWithZero(ResultMatrix_01);
        initializeWithZero(ResultMatrix_10);
        initializeWithZero(ResultMatrix_11);

        Matrix a00 = createMatrix(splitIndex,splitIndex);
        Matrix a01 = createMatrix(splitIndex,splitIndex);
        Matrix a10 = createMatrix(splitIndex,splitIndex);
        Matrix a11 = createMatrix(splitIndex,splitIndex);
        Matrix b00 = createMatrix(splitIndex,splitIndex);
        Matrix b01 = createMatrix(splitIndex,splitIndex);
        Matrix b10 = createMatrix(splitIndex,splitIndex);
        Matrix b11 = createMatrix(splitIndex,splitIndex);

        initializeWithZero(a00);
        initializeWithZero(a01);
        initializeWithZero(a10);
        initializeWithZero(a11);
        initializeWithZero(b00);
        initializeWithZero(b01);
        initializeWithZero(b10);
        initializeWithZero(b11);

        for(i=0;i<splitIndex;i++)
        {
            for(j=0;j<splitIndex;j++)
            {
                a00.arr[i][j]=mat1.arr[i][j];
                a01.arr[i][j]=mat1.arr[i][j+splitIndex];
                a10.arr[i][j]=mat1.arr[i+splitIndex][j];
                a11.arr[i][j]=mat1.arr[i+splitIndex][j+splitIndex];
                b00.arr[i][j]=mat2.arr[i][j];
                b01.arr[i][j]=mat2.arr[i][j+splitIndex];
                b10.arr[i][j]=mat2.arr[i+splitIndex][j];
                b11.arr[i][j]=mat2.arr[i+splitIndex][j+splitIndex];
            }
        }

        addMatrix(multiplyMatrices(a00,b00),multiplyMatrices(a01,b10),ResultMatrix_00,splitIndex);
        addMatrix(multiplyMatrices(a00,b01),multiplyMatrices(a01,b11),ResultMatrix_01,splitIndex);
        addMatrix(multiplyMatrices(a10,b00),multiplyMatrices(a11,b10),ResultMatrix_10,splitIndex);
        addMatrix(multiplyMatrices(a10,b01),multiplyMatrices(a11,b11),ResultMatrix_11,splitIndex);

        for(i=0;i<splitIndex;i++)
        {
            for(j=0;j<splitIndex;j++)
            {
                ResultMatrix.arr[i][j]=ResultMatrix_00.arr[i][j];
                ResultMatrix.arr[i][j+splitIndex]=ResultMatrix_01.arr[i][j];
                ResultMatrix.arr[splitIndex+i][j]=ResultMatrix_10.arr[i][j];
                ResultMatrix.arr[i+splitIndex][j+splitIndex]=ResultMatrix_11.arr[i][j];
            }
        }
        
    }
    return ResultMatrix;
}

int main()
{
    Matrix mat1, mat2, mat3;
    int i, j, k;
    printf("Enter no of row of 1st matrix : ");
    scanf("%d", &mat1.rows);
    printf("Enter no of column of 1st matrix : ");
    scanf("%d", &mat1.cols);
    printf("Enter no of row of 2nd matrix : ");
    scanf("%d", &mat2.rows);
    printf("Enter no of column of 2nd matrix : ");
    scanf("%d", &mat2.cols);
    if (!(mat1.cols == mat2.rows))
    {
        printf("INVALID MATRIX SIZE. MULTIPLICATION NOT POSSIBLE\n");
        return 0;
    }

    mat3.rows = mat1.rows;
    mat3.cols = mat2.cols;

    mat1=createMatrix(mat1.rows,mat1.cols);
    mat2=createMatrix(mat2.rows,mat2.cols);
    mat3=createMatrix(mat3.rows,mat3.cols);

    printf("Enter elements for 1st matrix\n");
    for (i = 0; i < mat1.rows; i++)
    {
        for (j = 0; j < mat1.cols; j++)
        {
            scanf("%d", &mat1.arr[i][j]);
        }
    }
    printf("Enter elements for 2nd matrix\n");
    for (i = 0; i < mat2.rows; i++)
    {
        for (j = 0; j < mat2.cols; j++)
        {
            scanf("%d", &mat2.arr[i][j]);
        }
    }
    initializeWithZero(mat3);

    printMatrix(mat1, "Matrix 1");
    printMatrix(mat2, "Matrix 2");
    
    mat3=multiplyMatrices(mat1,mat2);
    
    printMatrix(mat3, "Matrix 3");

    return 0;
}