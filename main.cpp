#include <fstream>
#include <iostream>
#include <cmath>

#define INPATH "matrix_input.txt"

using namespace std;

int get_matrix_size()
{ // Helper function just grabs the matrix size
    ifstream infile;
    infile.open(INPATH, ios::in);
    int size;
    infile >> size;
    infile.close();
    return size;
}

void read_matrices_pair(int *matrix1, int *matrix2, int size)
// Populates the two given arrays.

{
    ifstream infile;
    infile.open(INPATH, ios::in);
    int dummy;
    infile >> dummy;
    for (int row = 0; row < size; row++)
    {
        for (int column = 0; column < size; column++)
        {
            infile >> matrix1[column + row * size];
        }
    }
    for (int row = 0; row < size; row++)
    {
        for (int column = 0; column < size; column++)
        {
            infile >> matrix2[column + row * size];
        }
    }
    infile.close();
}

void print_matrix(int *matrix, int size)
{
    int column_widths[size];
    for (int i = 0; i < size; i++)
    {
        column_widths[i] = 0;
    }
    for (int i = 0; i < size * size; i++)
    {
        int digit_width = log10(abs(matrix[i])) + (matrix[i] < 0) + 1;
        if (digit_width > column_widths[i % size])
        {
            column_widths[i % size] = digit_width;
        }
    }
    printf("\u250c");
    for (int i = 0; i < size; i++)
    {
        printf("%*s", column_widths[i] + 1, "");
    }
    printf(" \u2510\n");
    for (int row = 0; row < size; row++)
    {
        printf("\u2502");
        for (int column = 0; column < size; column++)
        {
            printf("%*d", column_widths[column] + 1, matrix[row * size + column]);
        }
        printf(" \u2502\n");
    }
    printf("\u2514");
    for (int i = 0; i < size; i++)
    {
        printf("%*s", column_widths[i] + 1, "");
    }
    printf(" \u2518\n");
}

void print_specific_matrix(int *matrix1, int *matrix2, int size)
{
    printf("Which matrix to print? (1/2): ");
    int target_matrix;
    scanf("%d", &target_matrix);
    if (target_matrix == 1)
    {
        print_matrix(matrix1, size);
    }
    else
    {
        print_matrix(matrix2, size);
    }
}

void print_matrix_sum(int *matrix1, int *matrix2, int size)
{
    int new_matrix[size * size];
    for (int i = 0; i < size * size; i++)
    {
        new_matrix[i] = matrix1[i] + matrix2[i];
    }
    print_matrix(new_matrix, size);
}

void print_matrix_product(int *matrix1, int *matrix2, int size)
{
    int new_matrix[size * size];
    for (int row = 0; row < size; row++)
    {
        for (int column = 0; column < size; column++)
        {
            new_matrix[row * size + column] = 0;
            for (int offset = 0; offset < size; offset++)
            {
                new_matrix[row * size + column] += matrix1[row * size + offset] * matrix2[offset * size + column];
            }
        }
    }
    print_matrix(new_matrix, size);
}

void print_max_val(int *matrix, int size)
{
    int max_val = INT32_MIN;
    for (int i; i < size * size; i++)
    {
        if (matrix[i] > max_val)
            max_val = matrix[i];
    }
    printf("%d\n", max_val);
}

void print_matrix_diff(int *matrix1, int *matrix2, int size)
{
    int new_matrix[size * size];
    for (int i = 0; i < size * size; i++)
    {
        new_matrix[i] = -matrix2[i];
    }
    print_matrix_sum(matrix1, new_matrix, size);
}

void update_element(int *matrix, int size)
{
    int target_row;
    printf("Which row? ");
    scanf("%d", &target_row);
    int target_col;
    printf("Which column? ");
    scanf("%d", &target_col);
    int target_val;
    printf("What value to write? ");
    scanf("%d", &target_val);
    matrix[target_row * size + target_col - size - 1] = target_val;
    print_matrix(matrix, size);
}

void print_transposed(int *matrix, int size)
{
    int new_matrix[size * size];
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            new_matrix[col * size + row] = matrix[row * size + col];
        }
    }
    print_matrix(new_matrix, size);
}

int main()
{
    const int matrix_size = get_matrix_size();
    int matrix_1[matrix_size * matrix_size], matrix_2[matrix_size * matrix_size];
    int menu_select = 0;
    read_matrices_pair(matrix_1, matrix_2, matrix_size);
    printf("Matrices successfully loaded:");
    printf(" %dx%d\n", matrix_size, matrix_size);
    print_matrix(matrix_1, matrix_size);
    print_matrix(matrix_2, matrix_size);
    while (menu_select != 8)
    {
        printf("Select an option:\n");
        printf("\t1) Print a matrix\n");
        printf("\t2) Print sum M1+M2\n");
        printf("\t3) Print product M1M2\n");
        printf("\t4) Print difference M1-M2\n");
        printf("\t5) Update an element in M1\n");
        printf("\t6) Print maximum value in M1\n");
        printf("\t7) Print M1^T\n");
        printf("\t8) Quit\n");
        printf("Enter an option: ");
        scanf("%d", &menu_select);
        switch (menu_select)
        {
        case 1:
            print_specific_matrix(matrix_1, matrix_2, matrix_size);
            break;
        case 2:
            print_matrix_sum(matrix_1, matrix_2, matrix_size);
            break;
        case 3:
            print_matrix_product(matrix_1, matrix_2, matrix_size);
            break;
        case 4:
            print_matrix_diff(matrix_1, matrix_2, matrix_size);
            break;
        case 5:
            update_element(matrix_1, matrix_size);
            break;
        case 6:
            print_max_val(matrix_1, matrix_size);
            break;
        case 7:
            print_transposed(matrix_1, matrix_size);
            break;
        default:
            return 0;
        }
    }
}
