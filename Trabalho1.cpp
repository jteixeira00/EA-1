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

        matrix = compressLeft(matrix, size);
        matrix = mergeLeft(matrix, size);
        cout << "output left";
        printMatrix(matrix, size);

        x = y = 0;
        count++;
    }

    return 0;
}