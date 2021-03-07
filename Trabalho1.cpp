//g++ -std=c++17 -Wall -Wextra -O2 "Trabalho1.cpp" -lm

#include <iostream>
#include <unordered_map>
#include <list>
#include <algorithm>
#include <vector>

using namespace std;

int min_moves;
int maxSlides;

void MergeCompress(vector<vector<int>>, int, int, vector<vector<int>>);
void checkSolved(vector<vector<int>> &, int, int, vector<vector<int>> &);

//Utilities

void printMatrix(vector<vector<int>> matrix, int size)
{
    cout << "\n";
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}

//MOVEMENT FUNCTIONS
//return com std::tuple para devolver (array, changeBool)

vector<vector<int>> compressDown(vector<vector<int>> matrix, int size)
{
    vector<vector<int>> new_matrix(size, vector<int>(size));
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            new_matrix[j][i] = 0;
        }
    }
    for (int i = 0; i < size; i++)
    {
        int last_pos = size - 1;
        for (int j = size - 1; j >= 0; j--)
        {
            if (matrix[j][i] != 0)
            {
                new_matrix[last_pos][i] = matrix[j][i];
                last_pos--;
            }
        }
    }

    return new_matrix;
}

void mergeDown(vector<vector<int>> &matrix, int size)
{

    for (int i = 0; i < size; i++)
    {
        for (int j = size - 1; j > 0; j--)
        {
            if ((matrix[j][i] == matrix[j - 1][i]) && (matrix[j][i] != 0))
            {
                matrix[j][i] = matrix[j][i] + matrix[j - 1][i];
                matrix[j - 1][i] = 0;
            }
        }
    }

    return;
}

vector<vector<int>> compressUp(vector<vector<int>> matrix, int size)
{
    vector<vector<int>> new_matrix(size, vector<int>(size));
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            new_matrix[i][j] = 0;
        }
    }
    for (int i = 0; i < size; i++)
    {
        int last_pos = 0;
        for (int j = 0; j < size; j++)
        {
            if (matrix[j][i] != 0)
            {
                new_matrix[last_pos][i] = matrix[j][i];
                last_pos++;
            }
        }
    }

    return new_matrix;
}

void mergeUp(vector<vector<int>> &matrix, int size)
{

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - 1; j++)
        {
            if ((matrix[j][i] == matrix[j + 1][i]) && (matrix[j][i] != 0))
            {
                matrix[j][i] = matrix[j + 1][i] + matrix[j][i];
                matrix[j + 1][i] = 0;
            }
        }
    }

    return;
}

vector<vector<int>> compressRight(vector<vector<int>> matrix, int size)
{
    vector<vector<int>> new_matrix(size, vector<int>(size));
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            new_matrix[i][j] = 0;
        }
    }
    for (int i = 0; i < size; i++)
    {
        int last_pos = size - 1;
        for (int j = size - 1; j >= 0; j--)
        {
            if (matrix[i][j] != 0)
            {
                new_matrix[i][last_pos] = matrix[i][j];
                last_pos--;
            }
        }
    }

    return new_matrix;
}

void mergeRight(vector<vector<int>> &matrix, int size)
{

    for (int i = 0; i < size; i++)
    {
        for (int j = size - 1; j > 0; j--)
        {
            if ((matrix[i][j] == matrix[i][j - 1]) && (matrix[i][j] != 0))
            {
                matrix[i][j] = matrix[i][j] + matrix[i][j - 1];
                matrix[i][j - 1] = 0;
            }
        }
    }
    return;
}

vector<vector<int>> compressLeft(vector<vector<int>> matrix, int size)
{
    vector<vector<int>> new_matrix(size, vector<int>(size));
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            new_matrix[i][j] = 0;
        }
    }
    for (int i = 0; i < size; i++)
    {
        int last_pos = 0;
        for (int j = 0; j < size; j++)
        {
            if (matrix[i][j] != 0)
            {
                new_matrix[i][last_pos] = matrix[i][j];
                last_pos++;
            }
        }
    }

    return new_matrix;
}

void mergeLeft(vector<vector<int>> &matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - 1; j++)
        {
            if ((matrix[i][j] == matrix[i][j + 1]) && (matrix[i][j] != 0))
            {
                matrix[i][j] = matrix[i][j] + matrix[i][j + 1];
                matrix[i][j + 1] = 0;
            }
        }
    }

    return;
}

int possible(vector<vector<int>> &matrix, int size)
{
    vector<int> matrix_flattened;
    vector<int> flat_old;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            matrix_flattened.push_back(matrix[i][j]);
        }
    }

    do
    {

        sort(matrix_flattened.begin(), matrix_flattened.end(), greater<int>());
        flat_old = matrix_flattened;
        /*
        while (matrix_flattened[size - 1] == 0) //compress
        {
            matrix_flattened.pop_back();
            size--;
        }
        */
        for (int i = 0; i < (size * size) - 1; i++) //merge
        {
            if ((matrix_flattened[i] == matrix_flattened[i + 1]) && (matrix_flattened[i] != 0))
            {
                matrix_flattened[i] = matrix_flattened[i] * 2;
                matrix_flattened[i + 1] = 0;
            }
        }

        sort(matrix_flattened.begin(), matrix_flattened.end(), greater<int>()); //compress

    } while (matrix_flattened != flat_old);

    if ((matrix_flattened[1] == 0) && (matrix_flattened[0] != 0))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void MergeCompress(vector<vector<int>> matrix, int size, int n, vector<vector<int>> matrix_old)
{
    if (n++ >= min_moves)
    {
        return;
    }
    vector<vector<int>> matrix_og;
    matrix_og = matrix;

    if (!possible(matrix, size))
    {
        return;
    }

    matrix = compressRight(matrix_og, size);
    mergeRight(matrix, size);
    matrix = compressRight(matrix, size);
    if ((matrix != matrix_og) && (matrix != matrix_old))
    {
        checkSolved(matrix, size, n, matrix_og);
    }

    matrix = compressDown(matrix_og, size);
    mergeDown(matrix, size);
    matrix = compressDown(matrix, size);
    if ((matrix != matrix_og) && (matrix != matrix_old))
    {
        checkSolved(matrix, size, n, matrix_og);
    }

    matrix = compressUp(matrix_og, size);
    mergeUp(matrix, size);
    matrix = compressUp(matrix, size);
    if ((matrix != matrix_og) && (matrix != matrix_old))
    {
        checkSolved(matrix, size, n, matrix_og);
    }

    matrix = compressLeft(matrix_og, size);
    mergeLeft(matrix, size);
    matrix = compressLeft(matrix, size);
    if ((matrix != matrix_og) && (matrix != matrix_old))
    {
        checkSolved(matrix, size, n, matrix_og);
    }
}

void checkSolved(vector<vector<int>> &matrix, int size, int n_moves, vector<vector<int>> &matrix_old)
{
    //possivel otimizar -> verificar apenas as arestas da matriz
    //maybe verificar apenas a aresta onde encontra o primeiro valor?
    int n = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (matrix[i][j] != 0)
            {
                if (n == 0)
                {
                    n = 1;
                }
                else
                {
                    MergeCompress(matrix, size, n_moves, matrix_old);
                    return;
                }
            }
        }
    }
    if (n_moves < min_moves)
    {
        min_moves = n_moves;
        return;
    }
    return;
}

int main()
{
    // We probably do not need this but it is faster
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string order;
    int size;
    //int key;
    int max;
    int count = 0;
    int num;

    int x = 0;
    int y = 0;

    cin >> max;

    while (max != count)
    {

        cin >> size >> maxSlides;
        vector<vector<int>> matrix(size, vector<int>(size));

        min_moves = maxSlides * 0.6 + 1;
        while (y != size)
        {

            cin >> num;
            matrix[y][x] = num;
            if (x != size - 1)
            {
                ++x;
            }
            else
            {
                ++y;
                x = 0;
            }
        }
        //cout << "is it possible:" << possible(matrix, size) << "\n";
        vector<vector<int>> new_matrix(size, vector<int>(size));
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                new_matrix[j][i] = 0;
            }
        }
        MergeCompress(matrix, size, 0, new_matrix);
        if (min_moves <= 0.6 * maxSlides)
        {
            cout << min_moves << "\n";
        }
        else
        {

            min_moves = maxSlides * 0.8 + 1;
            MergeCompress(matrix, size, 0, new_matrix);

            if (min_moves <= maxSlides * 0.8)
            {
                cout << min_moves << "\n";
            }

            else
            {

                min_moves = maxSlides + 1;
                MergeCompress(matrix, size, 0, new_matrix);
                if (min_moves <= maxSlides)
                {
                    cout << min_moves << "\n";
                }
                else
                {
                    cout << "no solution\n";
                }
            }
        }

        x = y = 0;
        count++;
    }

    return 0;
}