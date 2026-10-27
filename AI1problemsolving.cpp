#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <cmath>
using namespace std;

struct Node
{
    int r;
    int c;
    char state;
    string path;
    int h;
};

struct Compare
{
    bool operator()(const Node& a, const Node& b)
    {
        if (a.h == b.h)
            return a.state > b.state;
        return a.h > b.h;
    }
};

int manhattan(int r1, int c1, int r2, int c2)
{
    return abs(r1 - r2) + abs(c1 - c2);
}

int main()
{
    string filename;
    cout << "Enter name of text file:";
    cin >> filename;

    ifstream file(filename);

    if (!file)
    {
        cout << "File cannot be opened\n";
        return 0;
    }

    int rows = 3;
    int cols = 7;

    char maze[3][7];

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            file >> maze[i][j];

    int rowBorder[3][6];

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 6; j++)
            file >> rowBorder[i][j];

    int colBorder[7][2];

    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 2; j++)
            file >> colBorder[i][j];

    char start, goal;

    cout << "Enter initial state:";
    cin >> start;

    cout << "Enter goal state:";
    cin >> goal;

    int sr, sc, gr, gc;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            if (maze[i][j] == start)
            {
                sr = i;
                sc = j;
            }

            if (maze[i][j] == goal)
            {
                gr = i;
                gc = j;
            }
        }

    priority_queue<Node, vector<Node>, Compare> open;
    set<char> visited;

    Node first;
    first.r = sr;
    first.c = sc;
    first.state = start;
    first.path += start;
    first.h = manhattan(sr, sc, gr, gc);

    open.push(first);

    int expanded = 0;

    while (!open.empty())
    {
        Node current = open.top();
        open.pop();

        char state = maze[current.r][current.c];

        if (visited.count(state))
            continue;

        visited.insert(state);

        if (state == goal)
        {
            cout << "The solution is:" << current.path << endl;
            cout << "Number of nodes expanded:" << expanded << endl;
            return 0;
        }

        expanded++;

        int r = current.r;
        int c = current.c;

        if (r > 0 && colBorder[c][r - 1] == 0)
        {
            Node next;
            next.r = r - 1;
            next.c = c;
            next.state = maze[r - 1][c];
            next.path = current.path + next.state;
            next.h = manhattan(r - 1, c, gr, gc);
            open.push(next);
        }

        if (r < rows - 1 && colBorder[c][r] == 0)
        {
            Node next;
            next.r = r + 1;
            next.c = c;
            next.state = maze[r + 1][c];
            next.path = current.path + next.state;
            next.h = manhattan(r + 1, c, gr, gc);
            open.push(next);
        }

        if (c > 0 && rowBorder[r][c - 1] == 0)
        {
            Node next;
            next.r = r;
            next.c = c - 1;
            next.state = maze[r][c - 1];
            next.path = current.path + next.state;
            next.h = manhattan(r, c - 1, gr, gc);
            open.push(next);
        }

        if (c < cols - 1 && rowBorder[r][c] == 0)
        {
            Node next;
            next.r = r;
            next.c = c + 1;
            next.state = maze[r][c + 1];
            next.path = current.path + next.state;
            next.h = manhattan(r, c + 1, gr, gc);
            open.push(next);
        }
    }

    cout << "No path found\n";
}