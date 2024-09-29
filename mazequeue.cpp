#include <iostream>
#include <queue>
using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {
    queue<Coord> cs;
    Coord start(sr, sc);
    Coord end(er, ec);
    int i = 1;

    //Push starting coordinates
    cs.push(start);
    maze[sr][sc] = 'c';

    while (!cs.empty()) {
        Coord c = cs.front();
        cs.pop();
        cout <<i<<": (" << c.r() <<"," << c.c()<<")"<<endl;
        i++;

        //Check if at end coord
        if ((c.c() == end.c()) && (c.r() == end.r()))
            return true;

        //Check if you can move south
        if (maze[c.r() + 1][c.c()] == '.') {
            Coord next(c.r() + 1, c.c());
            cs.push(next);
            maze[c.r() + 1][c.c()] = 'c';
        }
        //Check if you can move east
        if (maze[c.r()][c.c() + 1] == '.') {
            Coord next(c.r(), c.c() + 1);
            cs.push(next);
            maze[c.r()][c.c() + 1] = 'c';
        }

        //Check if you can move north
        if (maze[c.r() - 1][c.c()] == '.') {
            Coord next(c.r() - 1, c.c());
            cs.push(next);
            maze[c.r() - 1][c.c()] = 'c';
        }

        //Check if you can move west
        if (maze[c.r()][c.c() - 1] == '.') {
            Coord next(c.r(), c.c() - 1);
            cs.push(next);
            maze[c.r()][c.c() - 1] = 'c';
        }

    }

    //Return false outside for loop
    return false;

}
