//g++ -std=c++17 -Wall -Wextra -O2 "Trabalho1.cpp" -lm

#include <iostream>
#include <unordered_map>
#include <list>
#include <algorithm>
#include <vector>

using namespace std;

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

vector<vector<int>> mergeDown(vector<vector<int>> matrix, int size)
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
    return matrix;
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

vector<vector<int>> mergeUp(vector<vector<int>> matrix, int size)
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
    return matrix;
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

vector<vector<int>> mergeRight(vector<vector<int>> matrix, int size)
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
    return matrix;
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

vector<vector<int>> mergeLeft(vector<vector<int>> matrix, int size)
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
    return matrix;
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
    int maxSlides;

    int x = 0;
    int y = 0;

    cin >> max;

    while (max != count)
    {

        cin >> size >> maxSlides;
        vector<vector<int>> matrix(size, vector<int>(size));
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

        matrix = compressDown(matrix, size);
        cout << "compressDown:";
        printMatrix(matrix, size);

        matrix = mergeDown(matrix, size);
        cout << "mergeDown:";
        printMatrix(matrix, size);

        /*
        matrix = compressUp(matrix, size);
        cout << "compressUp:";
        printMatrix(matrix, size);

        matrix = mergeUp(matrix, size);
        cout << "mergeDownsUp:";
        printMatrix(matrix, size);
        
        matrix = compressLeft(matrix, size);
        cout << "compressLeft:";
        printMatrix(matrix, size);

        matrix = mergeLeft(matrix, size);
        cout << "mergeLeft:";
        printMatrix(matrix, size);
        
        matrix = compressRight(matrix, size);
        cout << "compressRight:";
        printMatrix(matrix, size);

        matrix = mergeRight(matrix, size);
        cout << "mergeRight";
        printMatrix(matrix, size);
        */
        x = y = 0;
        count++;
    }

    return 0;
}