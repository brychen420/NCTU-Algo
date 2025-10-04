#include <iostream>
#include <fstream>
using namespace std;
int counts = 0;
ifstream input("input.txt");
ofstream output("output.txt");

bool check(int x, int y, char *board[], int N);
void nqueen(int line, int N, char *board[]);

int main()
{
    int cases;
    input >> cases;
    while (cases--)
    {
        int N;
        int prep;
        input >> N >> prep;
        char *board[N];
        for (int i = 0; i < N; i++)
            board[i] = new char[N];

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                board[i][j] = '.';

        while (prep--)
        {
            int x, y;
            input >> x >> y;
            board[x][y] = 'P';
        }
        nqueen(0, N, board);
        output << counts << "\n";
        counts = 0;
        for (int i = 0; i < N; i++)
            delete[] board[i];
    }
    output.close();
    return 0;
}

bool check(int x, int y, char *board[], int N)
{
    for (int i = 0; i < N; i++){
        if (board[y][i] != '.' and i != x)
            return false;
        if (board[i][x] != '.' and i != y)
            return false;
    }
    for (int i = x - min(x, y), j = y - min(x, y); i < N and j < N; i++, j++)
        if (board[j][i] != '.' and !(j == y and i == x))
            return false;
    for (int i = x + 1, j = y - 1; j >= 0 and i < N; i++, j--)
        if (board[j][i] != '.')
            return false;
    for (int i = x - 1, j = y + 1; i >= 0 and j < N; i--, j++)
        if (board[j][i] != '.')
            return false;
    return true;
}

void nqueen(int line, int N, char *board[])
{
    for (int list = 0; list < N; list++)
    {
        if (check(list, line, board, N))
        {
            if (board[line][list] != 'P')
                board[line][list] = 'Q';
            if (line == N - 1)
            {
                counts++;
                if (board[line][list] != 'P')
                    board[line][list] = '.';
                return;
            }
            nqueen(line + 1, N, board);
            if (board[line][list] != 'P')
                board[line][list] = '.';
        }
    }
}