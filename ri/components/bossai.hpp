#ifndef ZBOSS_BOSSAI_HPP
#define ZBOSS_BOSSAI_HPP

#include <stack>
#include <set>
#include <cfloat>

#include <limits>

#include <zboss/entity/component.hpp>
#include <zboss/entity/entity.hpp>
#include <zboss/scene.hpp>
#include <zboss/components/transform.hpp>
#include <zboss/components/tilemap.hpp>
#include <zboss/components/animatedsprite.hpp>

#include "mytilemap.hpp"

using namespace zboss;

using namespace std;

typedef enum {
    BOSS_LOOKING,
    BOSS_FOLLOWING,
    BOSS_VICTORY
} BossState;

// class GridPosition;

typedef std::pair<int, int> GridPosition; // first - y, second - x

class BossAiComponent : public EntityComponent {

    private:

    TransformComponent* transform;

    stack<GridPosition> path;

    public:

    BossState state;

    explicit BossAiComponent() = default;

    private:

    void updateAnimation();

    public:

    void init() override;

    void update() override;

};

/*class GridPosition {

    public:

    int first;

    int second;

    explicit GridPosition(int first, int second) : first(first), second(second) {}

};*/

// typedef double HeuristicType;
typedef int HeuristicType;

// Creating a shortcut for int, int pair type

// Creating a shortcut for pair<int, pair<int, int>> type
// typedef pair<double, pair<int, int>> pPair;

typedef std::pair<HeuristicType, GridPosition> HeuristicGridPosition;

/*class HeuristicGridPosition : public GridPosition {

    public:

    double h;

    explicit HeuristicGridPosition(double h, int first, int second) : GridPosition(first, second), h(h) {}

};*/

// Creating a shortcut for int, int pair type
// typedef pair<int, int> Pair;

// Creating a shortcut for pair<int, pair<int, int>> type
// typedef pair<double, pair<int, int>> pPair;

// A structure to hold the neccesary parameters
class GridCell {

    public:

    // Row and Column index of its parent
    // Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
    int parent_i, parent_j;

    // f = g + h
    HeuristicType f, g, h;

};

// A Utility Function to check whether given cell (row, col)
// is a valid cell or not.

template <int ROW, int COL>
inline bool isValid(int row, int col) {

    // Returns true if row number and column number
    // is in range
    return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);

}

// A Utility Function to check whether the given cell is
// blocked or not

template <class T, int COL>
inline bool isUnBlocked(T* grid, int row, int col) {

    // Returns true if the cell is not blocked else false
    return grid[row * COL + col] == 0; // == 1

}

// A Utility Function to check whether destination cell has
// been reached or not
inline bool isDestination(int row, int col, GridPosition dest) {
    return row == dest.first && col == dest.second;
}

inline HeuristicType calculateHValue(int row, int col, GridPosition dest) {

    /*return ((double) sqrt((row - dest.first) * (row - dest.first)
                          + (col - dest.second) * (col - dest.second)));*/

    return static_cast<HeuristicType>(abs(row - dest.first) + abs(col - dest.second));

}

template <int ROW, int COL>
static void tracePath(stack<GridPosition>& path, GridCell cellDetails[][COL], GridPosition dest) {

    // printf("\nThe Path is ");

    int row = dest.first;
    int col = dest.second;

    // stack<GridPosition> path;

    while (!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col)) {

        path.push(GridPosition(row, col));

        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;

        row = temp_row;
        col = temp_col;

    }

    path.push(GridPosition(row, col));

    /*while (!Path.empty()) {
        GridPosition p = Path.top();
        Path.pop();
        printf("-> (%d,%d) ", p.first, p.second);
    }*/

}

// A Function to find the shortest path between
// a given source cell to a destination cell according
// to A* Search Algorithm
template<class T, int ROW, int COL>
static bool aStarSearch(stack<GridPosition>& result, T* grid, GridPosition src, GridPosition dest) {

    // If the source is out of range
    if (!isValid<ROW, COL>(src.first, src.second)) {
        return false;
    }

    // If the destination is out of range
    if (!isValid<ROW, COL>(dest.first, dest.second)) {
        return false;
    }

    // Either the source or the destination is blocked
    if (!isUnBlocked<T, COL>(grid, src.first, src.second) ||
        !isUnBlocked<T, COL>(grid, dest.first, dest.second)) {
        return false;
    }

    // If the destination cell is the same as source cell
    if (isDestination(src.first, src.second, dest)) {

        // result.push(GridPosition(src.first, src.second));

        // We are already at the destination

        return false;

    }

    // Create a closed list and initialise it to false which means
    // that no cell has been included yet
    // This closed list is implemented as a boolean 2D array
    static bool closedList[ROW][COL];

    memset(closedList, false, sizeof(closedList));

    // Declare a 2D array of structure to hold the details
    //of that cell
    GridCell cellDetails[ROW][COL];

    int i, j;

    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            /*cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;*/
            cellDetails[i][j].f = std::numeric_limits<HeuristicType>::max();
            cellDetails[i][j].g = std::numeric_limits<HeuristicType>::max();
            cellDetails[i][j].h = std::numeric_limits<HeuristicType>::max();
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }

    // Initialising the parameters of the starting node
    i = src.first, j = src.second;

    cellDetails[i][j].f = 0; // 0.0
    cellDetails[i][j].g = 0; // 0.0
    cellDetails[i][j].h = 0; // 0.0

    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;

    /*
     Create an open list having information as-
     <f, <i, j>>
     where f = g + h,
     and i, j are the row and column index of that cell
     Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
     This open list is implenented as a set of pair of pair.*/
    set<HeuristicGridPosition> openList;

    // Put the starting cell on the open list and set its
    // 'f' as 0
    // openList.insert(HeuristicGridPosition(0., i, j));
    openList.insert(make_pair(0., GridPosition(i, j)));

    while (!openList.empty()) {

        HeuristicGridPosition p = *openList.begin();

        // Remove this vertex from the open list
        openList.erase(openList.begin());

        // Add this vertex to the closed list
        i = p.second.first;
        j = p.second.second;

        closedList[i][j] = true;

        /*
         Generating all the 8 successor of this cell

             N.W   N   N.E
               \   |   /
                \  |  /
             W----Cell----E
                  / | \
                /   |  \
             S.W    S   S.E

         Cell-->Popped Cell (i, j)
         N -->  North       (i-1, j)
         S -->  South       (i+1, j)
         E -->  East        (i, j+1)
         W -->  West           (i, j-1)
         N.E--> North-East  (i-1, j+1)
         N.W--> North-West  (i-1, j-1)
         S.E--> South-East  (i+1, j+1)
         S.W--> South-West  (i+1, j-1)*/

        // To store the 'g', 'h' and 'f' of the 8 successors
        HeuristicType gNew, hNew, fNew;

        //----------- 1st Successor (North) ------------

        // Only process this cell if this is a valid one
        if (isValid<ROW, COL>(i - 1, j)) {

            // If the destination cell is the same as the
            // current successor
            if (isDestination(i - 1, j, dest)) {

                // Set the Parent of the destination cell
                cellDetails[i - 1][j].parent_i = i;
                cellDetails[i - 1][j].parent_j = j;
                
                tracePath<ROW, COL>(result, cellDetails, dest);

                return true;

            }
            else if (!closedList[i - 1][j] &&
                     isUnBlocked<T, COL>(grid, i - 1, j)) {

                gNew = cellDetails[i][j].g + 1; // 1.0

                hNew = calculateHValue(i - 1, j, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is better,
                // using 'f' cost as the measure.
                if (cellDetails[i - 1][j].f == std::numeric_limits<HeuristicType>::max() ||
                    cellDetails[i - 1][j].f > fNew) {

                    openList.insert(make_pair(fNew, GridPosition(i - 1, j)));

                    // Update the details of this cell
                    cellDetails[i - 1][j].f = fNew;
                    cellDetails[i - 1][j].g = gNew;
                    cellDetails[i - 1][j].h = hNew;
                    cellDetails[i - 1][j].parent_i = i;
                    cellDetails[i - 1][j].parent_j = j;
                }
            }
        }

        //----------- 2nd Successor (South) ------------

        // Only process this cell if this is a valid one
        if (isValid<ROW, COL>(i + 1, j)) {

            // If the destination cell is the same as the
            // current successor
            if (isDestination(i + 1, j, dest)) {

                // Set the Parent of the destination cell
                cellDetails[i + 1][j].parent_i = i;
                cellDetails[i + 1][j].parent_j = j;
                
                tracePath<ROW, COL>(result, cellDetails, dest);

                return true;

            }
            else if (!closedList[i + 1][j] &&
                     isUnBlocked<T, COL>(grid, i + 1, j)) {

                gNew = cellDetails[i][j].g + 1; // 1.0

                hNew = calculateHValue(i + 1, j, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is better,
                // using 'f' cost as the measure.
                if (cellDetails[i + 1][j].f == std::numeric_limits<HeuristicType>::max() ||
                    cellDetails[i + 1][j].f > fNew) {

                    openList.insert(make_pair(fNew, GridPosition(i + 1, j)));

                    // Update the details of this cell
                    cellDetails[i + 1][j].f = fNew;
                    cellDetails[i + 1][j].g = gNew;
                    cellDetails[i + 1][j].h = hNew;
                    cellDetails[i + 1][j].parent_i = i;
                    cellDetails[i + 1][j].parent_j = j;
                }
            }
        }

        //----------- 3rd Successor (East) ------------

        // Only process this cell if this is a valid one
        if (isValid<ROW, COL>(i, j + 1)) {

            // If the destination cell is the same as the
            // current successor
            if (isDestination(i, j + 1, dest)) {

                // Set the Parent of the destination cell
                cellDetails[i][j + 1].parent_i = i;
                cellDetails[i][j + 1].parent_j = j;
                
                tracePath<ROW, COL>(result, cellDetails, dest);

                return true;

            }
            else if (!closedList[i][j + 1] &&
                     isUnBlocked<T, COL>(grid, i, j + 1)) {

                gNew = cellDetails[i][j].g + 1; // 1.0

                hNew = calculateHValue(i, j + 1, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is better,
                // using 'f' cost as the measure.
                if (cellDetails[i][j + 1].f == std::numeric_limits<HeuristicType>::max() ||
                    cellDetails[i][j + 1].f > fNew) {

                    openList.insert(make_pair(fNew, GridPosition(i, j + 1)));


                    // Update the details of this cell
                    cellDetails[i][j + 1].f = fNew;
                    cellDetails[i][j + 1].g = gNew;
                    cellDetails[i][j + 1].h = hNew;
                    cellDetails[i][j + 1].parent_i = i;
                    cellDetails[i][j + 1].parent_j = j;
                }
            }
        }

        //----------- 4th Successor (West) ------------

        // Only process this cell if this is a valid one
        if (isValid<ROW, COL>(i, j - 1)) {

            // If the destination cell is the same as the
            // current successor
            if (isDestination(i, j - 1, dest)) {

                // Set the Parent of the destination cell
                cellDetails[i][j - 1].parent_i = i;
                cellDetails[i][j - 1].parent_j = j;
                
                tracePath<ROW, COL>(result, cellDetails, dest);

                return true;

            }
            else if (!closedList[i][j - 1] &&
                     isUnBlocked<T, COL>(grid, i, j - 1)) {

                gNew = cellDetails[i][j].g + 1; // 1.0

                hNew = calculateHValue(i, j - 1, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is better,
                // using 'f' cost as the measure.
                if (cellDetails[i][j - 1].f == std::numeric_limits<HeuristicType>::max() ||
                    cellDetails[i][j - 1].f > fNew) {


                    openList.insert(make_pair(fNew, GridPosition(i, j - 1)));

                    // Update the details of this cell
                    cellDetails[i][j - 1].f = fNew;
                    cellDetails[i][j - 1].g = gNew;
                    cellDetails[i][j - 1].h = hNew;
                    cellDetails[i][j - 1].parent_i = i;
                    cellDetails[i][j - 1].parent_j = j;
                }
            }
        }

        //----------- 5th Successor (North-East) ------------

        // Only process this cell if this is a valid one
        if (isValid<ROW, COL>(i - 1, j + 1)) {

            // If the destination cell is the same as the
            // current successor
            if (isDestination(i - 1, j + 1, dest)) {

                // Set the Parent of the destination cell
                cellDetails[i - 1][j + 1].parent_i = i;
                cellDetails[i - 1][j + 1].parent_j = j;
                
                tracePath<ROW, COL>(result, cellDetails, dest);

                return true;

            }
            else if (!closedList[i - 1][j + 1] &&
                     isUnBlocked<T, COL>(grid, i - 1, j + 1)) {

                gNew = cellDetails[i][j].g + 1; // 1.414 because diagonal

                hNew = calculateHValue(i - 1, j + 1, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is better,
                // using 'f' cost as the measure.
                if (cellDetails[i - 1][j + 1].f == std::numeric_limits<HeuristicType>::max() ||
                    cellDetails[i - 1][j + 1].f > fNew) {


                    openList.insert(make_pair(fNew, GridPosition(i - 1, j + 1)));

                    // Update the details of this cell
                    cellDetails[i - 1][j + 1].f = fNew;
                    cellDetails[i - 1][j + 1].g = gNew;
                    cellDetails[i - 1][j + 1].h = hNew;
                    cellDetails[i - 1][j + 1].parent_i = i;
                    cellDetails[i - 1][j + 1].parent_j = j;
                }
            }
        }

        //----------- 6th Successor (North-West) ------------

        // Only process this cell if this is a valid one
        if (isValid<ROW, COL>(i - 1, j - 1)) {

            // If the destination cell is the same as the
            // current successor
            if (isDestination(i - 1, j - 1, dest)) {

                // Set the Parent of the destination cell
                cellDetails[i - 1][j - 1].parent_i = i;
                cellDetails[i - 1][j - 1].parent_j = j;
                
                tracePath<ROW, COL>(result, cellDetails, dest);

                return true;

            }
            else if (!closedList[i - 1][j - 1] &&
                     isUnBlocked<T, COL>(grid, i - 1, j - 1)) {

                gNew = cellDetails[i][j].g + 1; // 1.414

                hNew = calculateHValue(i - 1, j - 1, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is better,
                // using 'f' cost as the measure.
                if (cellDetails[i - 1][j - 1].f == std::numeric_limits<HeuristicType>::max() ||
                    cellDetails[i - 1][j - 1].f > fNew) {

                    openList.insert(make_pair(fNew, GridPosition(i - 1, j - 1)));


                    // Update the details of this cell

                    cellDetails[i - 1][j - 1].f = fNew;
                    cellDetails[i - 1][j - 1].g = gNew;
                    cellDetails[i - 1][j - 1].h = hNew;
                    cellDetails[i - 1][j - 1].parent_i = i;
                    cellDetails[i - 1][j - 1].parent_j = j;

                }
            }
        }

        //----------- 7th Successor (South-East) ------------

        // Only process this cell if this is a valid one
        if (isValid<ROW, COL>(i + 1, j + 1)) {

            // If the destination cell is the same as the
            // current successor
            if (isDestination(i + 1, j + 1, dest)) {

                // Set the Parent of the destination cell
                cellDetails[i + 1][j + 1].parent_i = i;
                cellDetails[i + 1][j + 1].parent_j = j;
                
                tracePath<ROW, COL>(result, cellDetails, dest);

                return true;

            }

                // If the successor is already on the closed
                // list or if it is blocked, then ignore it.
                // Else do the following
            else if (!closedList[i + 1][j + 1] &&
                     isUnBlocked<T, COL>(grid, i + 1, j + 1)) {

                gNew = cellDetails[i][j].g + 1; // 1.414

                hNew = calculateHValue(i + 1, j + 1, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is better,
                // using 'f' cost as the measure.
                if (cellDetails[i + 1][j + 1].f == std::numeric_limits<HeuristicType>::max() ||
                    cellDetails[i + 1][j + 1].f > fNew) {


                    openList.insert(make_pair(fNew, GridPosition(i + 1, j + 1)));

                    // Update the details of this cell
                    cellDetails[i + 1][j + 1].f = fNew;
                    cellDetails[i + 1][j + 1].g = gNew;
                    cellDetails[i + 1][j + 1].h = hNew;
                    cellDetails[i + 1][j + 1].parent_i = i;
                    cellDetails[i + 1][j + 1].parent_j = j;
                }
            }
        }

        //----------- 8th Successor (South-West) ------------

        // Only process this cell if this is a valid one
        if (isValid<ROW, COL>(i + 1, j - 1)) {

            // If the destination cell is the same as the
            // current successor
            if (isDestination(i + 1, j - 1, dest)) {

                // Set the Parent of the destination cell
                cellDetails[i + 1][j - 1].parent_i = i;
                cellDetails[i + 1][j - 1].parent_j = j;
                

                tracePath<ROW, COL>(result, cellDetails, dest);

                return true;

            }

                // If the successor is already on the closed
                // list or if it is blocked, then ignore it.
                // Else do the following
            else if (!closedList[i + 1][j - 1] &&
                     isUnBlocked<T, COL>(grid, i + 1, j - 1)) {

                gNew = cellDetails[i][j].g + 1; // 1.414

                hNew = calculateHValue(i + 1, j - 1, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is better,
                // using 'f' cost as the measure.
                if (cellDetails[i + 1][j - 1].f == std::numeric_limits<HeuristicType>::max() ||
                    cellDetails[i + 1][j - 1].f > fNew) {


                    openList.insert(make_pair(fNew, GridPosition(i + 1, j - 1)));

                    // Update the details of this cell
                    cellDetails[i + 1][j - 1].f = fNew;
                    cellDetails[i + 1][j - 1].g = gNew;
                    cellDetails[i + 1][j - 1].h = hNew;
                    cellDetails[i + 1][j - 1].parent_i = i;
                    cellDetails[i + 1][j - 1].parent_j = j;
                }
            }
        }
    }

    // no path found

    return false;

}

#endif //ZBOSS_BOSSAI_HPP