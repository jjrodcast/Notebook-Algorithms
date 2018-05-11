/*
 * A* algorithm using Manhattan heuristic
 * beacause we use 4 directions (up, right, down, left).
 * In case you want to implement 8 directions using diagonals
 * you can implement Chebyshev heuristic and change the dx and 
 * dy array with length 8 and change the for loop inside 
 * astarsearch function with the same length of the arrays.
 */
#include <iostream>
#include <set>
#include <cmath>
#include <utility>
#include <vector>
#include <cstring>
#include <algorithm>

#define ROW 5
#define COL 5
#define INF -999999999
#define NO_PARENT -1
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair<int , int> Point;
typedef pair<double, Point> PCell;

// We storage the 4 possible movements
int dx[4] = {-1,  0,  1,  0};
int dy[4] = { 0,  1,  0, -1};


struct Father {
   int x; // pos x
   int y; // pos y
};

struct Cell{

   /* Representation
      ---------
      | F     |
      |   P   |
      | G   H |
      ---------
   */

   int f; 
   int g; 
   int h;   
   Father parent;
};

// This function check if we are in a valid cell
bool valid(int row, int col, int i, int j) {
   if(i >= 0 && i < row && j >= 0 && j < col) return true;
   return false;
}

// This function check if the element is a wall or not.
bool isWall(bool element) {
   if(element == true) return true;
   return false;
}

// This function check if we reach the destiny
bool isDestiny(Point p1, Point p2) {
   if(p1.first == p2.first && p1.second == p2.second) return true;
   return false;
}

// This function is just to fill our detail grid with 
// initial values
void fillDetails(Cell cells[][COL]) {
   for(int i = 0; i < ROW; i++) {
      for(int j = 0; j < COL; j++) {
         cells[i][j].f = INF;
         cells[i][j].g = INF;
         cells[i][j].h = INF;
         cells[i][j].parent.x = NO_PARENT;
         cells[i][j].parent.y = NO_PARENT;
      }
   }
}

// This function is the heuristic method to find distances
// between two points. We are using Manhattan distance
// (a, b) (c, d)
// |a - c| + |b - d|
int heuristic(Point p1, Point p2) {
   return fabs(p1.first - p2.first) + fabs(p1.second - p2.second);
}

// This function is useful to print path
void printPath(Cell details[][COL], Point end) {

   vector<Point> path;
   int row = end.first;
   int col = end.second;
   
   path.pb(mp(row, col));

   while(!(details[row][col].parent.x == row && details[row][col].parent.y == col)) {
      int temprow, tempcol;
      temprow = details[row][col].parent.x;
      tempcol = details[row][col].parent.y;
      row = temprow;
      col = tempcol;
      path.pb(mp(row, col));
   }

   reverse(path.begin(), path.end());

   cout << "(" << path[0].first << "," << path[0].second << ")";
   for(int i = 1; i < path.size(); i++) {
      cout << ",(" << path[i].first << "," << path[i].second << ")";
   }
   cout << "\n";
}

// This function does the "magic" using A* search in a grid
void astarsearch(bool arr[][COL], Point ini, Point end) {
  
   bool finished = false; // flag that change when we reach the destiny
   int x, y;
   
   bool visited[ROW][COL]; // This is our closest list
   memset(visited, false, sizeof(visited));
   set<PCell> open;    // This is our open list

   Cell details[ROW][COL]; // This is array of structs holds each new values
   fillDetails(details);
   
   // Initialize values
   x = ini.first; // first Point
   y = ini.second; // second Point
   details[x][y] = { 0, 0, 0, x , y };
   
   // we are assuming that the given Point(s) are inside grid's range
   // if not, you can use the "valid" function created lines above.

   open.insert(mp(0.0, mp(x, y)));

   while(!open.empty()) {
      PCell current = *open.begin();

      open.erase(open.begin());
      
      x = current.second.first;
      y = current.second.second;
      visited[x][y] = true; // Mark as visited in closed list
      for(int i = 0; i < 4; i++) {
         double fNew, gNew, hNew;
         int posx = x + dx[i];
         int posy = y + dy[i];
         if(valid(ROW, COL, posx, posy) && !isWall(arr[posx][posy])) { // check if it's valid cell and is not a wall
            if(!isDestiny(mp(posx, posy), end)) { // If we didn't reach the destiny, we just break the loop
               if(!visited[posx][posy]) {
                  gNew = details[x][y].g + 1; // augment last one Cell + 1 
                  hNew = heuristic(mp(posx, posy), end); // calculate Manhattan distance
                  fNew = gNew + hNew;
                  
                  /*|| details[posx][posy].f > fNew*/
                  if(details[posx][posy].f == INF) {
                    
                     open.insert(mp(fNew, mp(posx, posy)));
                     details[posx][posy].f = fNew;
                     details[posx][posy].g = gNew;
                     details[posx][posy].h = hNew;
                     details[posx][posy].parent.x = x;
                     details[posx][posy].parent.y = y;
                  }
               }

            } else {
               finished = true;
               details[posx][posy].f = fNew;
               details[posx][posy].g = gNew;
               details[posx][posy].h = hNew;
               details[posx][posy].parent.x = x;
               details[posx][posy].parent.y = y;
               
               printPath(details, end);
               
               break;
            }

         }
      }

      if(finished) break;

   }

}

int main() {

   // 1.- Create the matrix arr[LIM][LIM]
   bool arr[ROW][COL] = 
      {
         {0, 0, 0, 0, 0},
         {0, 0, 1, 0, 0},
         {0, 0, 1, 0, 0},
         {0, 0, 1, 0, 0},
         {0, 0, 0, 0, 0}
      };

   // 2.- Choose two points as source and destiny
   Point p1 = mp(2, 0); // source
   Point p2 = mp(2, 4); // destiny
   
   // 3. Call the A* search function 
   astarsearch(arr, p1, p2);

   // Uncomment the line above to keep console open
   //system("pause");
   return 0;
}