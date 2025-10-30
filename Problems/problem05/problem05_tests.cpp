#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "solver.hpp"
#include "constants.hpp"

/* Provided test cases */

/* Matrix vector product tests */
TEST_CASE("Test matrix vector product dim 2", "[product]")
{
    const int dim = 2;
    double matrix[dim][CAP] = {{0.4, 1.2}, {1.7, -3.2}};
    double vector[dim] = {1, -2};
    double result[dim];
    double test[dim] = {-2, 8.1};
    matrix_vector_product(matrix, vector, result, dim);

    for (int i = 0; i < dim; i++)
    {
        REQUIRE(abs(result[i] - test[i]) <= THRESHOLD);
    }
}

TEST_CASE("Test matrix vector product dim 3", "[product]")
{
    const int dim = 3;
    double matrix[dim][CAP] = {{2, 1, 1}, {1, -1, -1}, {1, 2, 1}};
    double vector[dim] = {1, -2, 3};
    double result[dim];
    double test[dim] = {3, 0, 0};
    matrix_vector_product(matrix, vector, result, dim);

    for (int i = 0; i < dim; i++)
    {
        REQUIRE(abs(result[i] - test[i]) <= THRESHOLD);
    }
}

TEST_CASE("Test matrix vector product dim 4", "[product]")
{
    const int dim = 4;
    double matrix[dim][CAP] = {{0, 10, 4, -2},
                               {-3, -17, 1, 2},
                               {1, 1, 1, 0},
                               {8, -34, 16, -10}};
    double vector[dim] = {4, 0, 2, 6};
    double result[dim];
    double test[dim] = {-4, 2, 6, 4};
    matrix_vector_product(matrix, vector, result, dim);

    for (int i = 0; i < dim; i++)
    {
        REQUIRE(abs(result[i] - test[i]) <= THRESHOLD);
    }
}

TEST_CASE("Test matrix vector product dim 5", "[product]")
{
    const int dim = 5;
    double matrix[dim][CAP] = {{1, 1, 0, 1, 0},
                               {1, 0, 1, 0, 1},
                               {0, 300, 0, -300, 0},
                               {0, 0, 150, 0, -150},
                               {45000, -22500, -45000, 0, 0}};
    double vector[dim] = {36.0 / 7.0, -81.0 / 7.0, 153.0 / 14.0, 129.0 / 7.0, -57.0 / 14.0};
    double result[dim];
    double test[dim] = {12, 12, -9000, 2250, 0};
    matrix_vector_product(matrix, vector, result, dim);

    for (int i = 0; i < dim; i++)
    {
        REQUIRE(abs(result[i] - test[i]) <= THRESHOLD);
    }
}

/* Test submatrix */
TEST_CASE("Test submatrix dim 2", "[solver]")
{
    const int dim = 2;
    int row = 0, col = 0;
    double matrix[dim][CAP] = {{0.4, 1.2}, {1.7, -3.2}};
    double result[dim - 1][CAP];
    double test[dim - 1][CAP] = {-3.2};
    submatrix(matrix, row, col, result, dim);

    for (int i = 0; i < dim - 1; i++)
    {
        for (int j = 0; j < dim - 1; j++)
        {
            REQUIRE(abs(result[i][j] - test[i][j]) <= THRESHOLD);
        }
    }
}

TEST_CASE("Test submatrix dim 3", "[solver]")
{
    const int dim = 3;
    int row = 1, col = 1;
    double matrix[dim][CAP] = {{2, 1, 1}, {1, -1, -1}, {1, 2, 1}};
    double result[dim - 1][CAP];
    double test[dim - 1][CAP] = {{2,1},{1,1}};
    submatrix(matrix, row, col, result, dim);

    for (int i = 0; i < dim - 1; i++)
    {
        for (int j = 0; j < dim - 1; j++)
        {
            REQUIRE(abs(result[i][j] - test[i][j]) <= THRESHOLD);
        }
    }
}

TEST_CASE("Test submatrix dim 4", "[solver]")
{
    const int dim = 4;
    int row = 2, col = 2;
    double matrix[dim][CAP] = {{0, 10, 4, -2},{-3, -17, 1, 2},{1, 1, 1, 0},{8, -34, 16, -10}};
    double result[dim - 1][CAP];
    double test[dim - 1][CAP] = {{0,10,-2},{-3,-17,2},{8,-34,-10}};
    submatrix(matrix, row, col, result, dim);

    for (int i = 0; i < dim - 1; i++)
    {
        for (int j = 0; j < dim - 1; j++)
        {
            REQUIRE(abs(result[i][j] - test[i][j]) <= THRESHOLD);
        }
    }
}

TEST_CASE("Test submatrix dim 5", "[solver]")
{
    const int dim = 5;
    int row = 4, col = 4;
    double matrix[dim][CAP] = {{1, 1, 0, 1, 0},{1, 0, 1, 0, 1},{0, 300, 0, -300, 0},{0, 0, 150, 0, -150},{45000, -22500, -45000, 0, 0}};
    double result[dim - 1][CAP];
    double test[dim - 1][CAP] = {{1, 1, 0, 1}, {1, 0, 1, 0}, {0, 300, 0, -300}, {0, 0, 150, 0}};
    submatrix(matrix, row, col, result, dim);

    for (int i = 0; i < dim - 1; i++)
    {
        for (int j = 0; j < dim - 1; j++)
        {
            REQUIRE(abs(result[i][j] - test[i][j]) <= THRESHOLD);
        }
    }
}

/* Test determinant */
TEST_CASE("Test determinant base case", "[solver]")
{
    double matrix[1][CAP] = {3.4};
    double test = 3.4;
    double result = determinant(matrix, 1);

    REQUIRE(abs(result - test) <= THRESHOLD);
}

TEST_CASE("Test determinant case 1", "[solver]")
{
    double matrix[2][CAP] = {{0.4, 1.2}, {1.7, -3.2}};
    double test = -3.32;
    double result = determinant(matrix, 2);

    REQUIRE(abs(result - test) <= THRESHOLD);
}

TEST_CASE("Test determinant case 2", "[solver]")
{
    double matrix[3][CAP] = {{2, 1, 1}, {1, -1, -1}, {1, 2, 1}};
    double test = 3;
    double result = determinant(matrix, 3);

    REQUIRE(abs(result - test) <= THRESHOLD);
}

TEST_CASE("Test determinant case 3", "[solver]")
{
    double matrix[4][CAP] = {{0, 10, 4, -2}, {-3, -17, 1, 2}, {1, 1, 1, 0}, {8, -34, 16, -10}};
    double test = -1568;
    double result = determinant(matrix, 4);

    REQUIRE(abs(result - test) <= THRESHOLD);
}

TEST_CASE("Test determinant case 4", "[solver]")
{
    double matrix[5][CAP] = {{1, 1, 0, 1, 0}, {1, 0, 1, 0, 1}, {0, 300, 0, -300, 0}, {0, 0, 150, 0, -150}, {45000, -22500, -45000, 0, 0}};
    double test = 1.4175e10;
    double result = determinant(matrix, 5);

    REQUIRE(abs(result - test) <= THRESHOLD);
}

/* Column replace tests */
TEST_CASE("Test col replace dim 2", "[solver]")
{
    const int dim = 2;
    double matrix[dim][CAP] = {{0.4, 1.2}, {1.7, -3.2}};
    double vector[dim] = {-2, 8.1};
    double result[dim][CAP];
    int col = 0;
    double test[dim][CAP] = {{-2, 1.2}, {8.1, -3.2}};
    replace_column(matrix, col, vector, result, dim);

    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            REQUIRE(abs(result[i][j] - test[i][j]) <= THRESHOLD);
        }
    }
}

TEST_CASE("Test col replace dim 3", "[solver]")
{
    const int dim = 3;
    double matrix[dim][CAP] = {{2, 1, 1}, {1, -1, -1}, {1, 2, 1}};
    double vector[dim] = {3, 0, 0};
    double result[dim][CAP];
    int col = 1;
    double test[dim][CAP] = {{2, 3, 1}, {1, 0, -1}, {1, 0, 1}};
    replace_column(matrix, col, vector, result, dim);

    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            REQUIRE(abs(result[i][j] - test[i][j]) <= THRESHOLD);
        }
    }
}

TEST_CASE("Test col replace dim 4", "[solver]")
{
    const int dim = 4;
    double matrix[dim][CAP] = {{0, 10, 4, -2}, {-3, -17, 1, 2}, {1, 1, 1, 0}, {8, -34, 16, -10}};
    double vector[dim] = {-4, 2, 6, 4};
    double result[dim][CAP];
    int col = 2;
    double test[dim][CAP] = {{0, 10, -4, -2}, {-3, -17, 2, 2}, {1, 1, 6, 0}, {8, -34, 4, -10}};
    replace_column(matrix, col, vector, result, dim);

    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            REQUIRE(abs(result[i][j] - test[i][j]) <= THRESHOLD);
        }
    }
}

/* Test Cramer's rule */
TEST_CASE("Test cramer's rule dim 2", "[solver]")
{
    const int dim = 2;
    double matrix[dim][CAP] = {{0.4, 1.2}, {1.7, -3.2}};
    double vector[dim] = {-2, 8.1};
    double result[dim];
    double test[dim] = {1, -2};
    cramers_rule(matrix, vector, result, dim);

    for (int i = 0; i < dim; i++)
    {
        REQUIRE(abs(result[i] - test[i]) <= THRESHOLD);
    }
}

TEST_CASE("Test cramer's rule dim 3", "[solver]")
{
    const int dim = 3;
    double matrix[dim][CAP] = {{2, 1, 1}, {1, -1, -1}, {1, 2, 1}};
    double vector[dim] = {3,0,0};
    double result[dim];
    double test[dim] = {1,-2,3};
    cramers_rule(matrix, vector, result, dim);

    for (int i = 0; i < dim; i++)
    {
        REQUIRE(abs(result[i] - test[i]) <= THRESHOLD);
    }
}

TEST_CASE("Test cramer's rule dim 4", "[solver]")
{
    const int dim = 4;
    double matrix[dim][CAP] = {{0, 10, 4, -2}, {-3, -17, 1, 2}, {1, 1, 1, 0}, {8, -34, 16, -10}};
    double vector[dim] = {-4,2,6,4};
    double result[dim];
    double test[dim] = {4, 0, 2, 6};
    cramers_rule(matrix, vector, result, dim);

    for (int i = 0; i < dim; i++)
    {
        REQUIRE(abs(result[i] - test[i]) <= THRESHOLD);
    }
}

TEST_CASE("Test cramer's rule dim 5", "[solver]")
{
    const int dim = 5;
    double matrix[dim][CAP] = {{1, 1, 0, 1, 0}, {1, 0, 1, 0, 1}, {0, 300, 0, -300, 0}, {0, 0, 150, 0, -150}, {45000, -22500, -45000, 0, 0}};
    double vector[dim] = {12,12,-9000,2250,0};
    double result[dim];
    double test[dim] = {(36 / 7.0), (-81 / 7.0), (153 / 14.0), (129 / 7.0), (-57 / 14.0)};
    cramers_rule(matrix, vector, result, dim);

    for (int i = 0; i < dim; i++)
    {
        REQUIRE(abs(result[i] - test[i]) <= THRESHOLD);
    }
}