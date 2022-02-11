//Source for MazeSolver

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "myStack.h"
#include "MyQ.h"
#include "MazeCell.h"

using namespace std;

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3
#define DONE 4
#define SUCCESS 10
#define FAILURE 20

//method headers*******************************************************

//depthFirst header
void depthFirst(MazeCell **cells,MazeCell start, MazeCell end, int row, int col);

//global variables*****************************************************

//# rows and cols in the maze
int rows, cols;
//pointer to the grid (2-d array of ints)
int** grid;
//pointer to the maze cells (2-d array of MazeCell objects)
MazeCell** cells;

int main() {

    //create the Maze from the file
    ifstream fin("maze.txt");
    if(!fin){
        cout << "File not found\n";
        exit(2);
    }

    //read in the rows and cols
    fin >> rows >> cols;

    //create the maze rows
    grid = new int* [rows];

    //add each column
    for (int i = 0; i < rows; i++)
        grid[i] = new int[cols];

    //read in the data from the file to populate
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fin >> grid[i][j];
        }
    }

    //look at it
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 3)
                cout << "S" << " ";
            else if (grid[i][j] == 4)
                cout << "E" << " ";
            else
                cout << grid[i][j] << " ";
        }
        cout << endl;
    }

    //make a 2-d array of cells
    cells = new MazeCell * [rows];
    for (int i = 0; i < rows; i++) {
        cells[i] = new MazeCell[cols];
    }

    //all MazeCell in the cells grid has a default init
    //only update those cells that are not walls

    MazeCell start, end;

    //iterate over the grid
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] != 0) {
                cells[i][j].setCoordinates(i, j);
                //look for the start and end cells
                if (grid[i][j] == 3)
                    start = cells[i][j];
                if (grid[i][j] == 4)
                    end = cells[i][j];

            }

        }
    }

    //testing
    cout <<"start: "<< start << " end: " << end << endl;

    //solve it!
    depthFirst(cells ,start, end, rows, cols);


    return 0;
}


//this function should find a path through the maze
//if found, output the path from start to end
//if not path exists, output a message stating so

void depthFirst(MazeCell **cells,MazeCell start, MazeCell end, int row, int col)//traverse distance in maze until it finds end or until termination
{
    MyStack<MazeCell> path;

    int i=start.getCol();
    int j=start.getRow();

    bool valid=false;//to ensure we don't terminate at the start

    while(true){
       // cout<<j<<" "<<i<<endl;
        MazeCell currentCell=cells[j][i];//current cell observed
        if(i==end.getCol() && j==end.getRow()){//if we reached the end
            break;
        }
        if(valid && i==start.getCol() && j== start.getRow()){//if we end up back at the beginning and there are no more places to go
            break;
        }
        valid=false;//are we not trapped?
        if(j>0 && cells[j-1][i].getCol()!=-1 && cells[j-1][i].getRow()!=-1){
            currentCell=cells[j-1][i];
            j--;
            path.push(currentCell);
//            cout<<path.top()<<endl;
            cells[j][i].setCoordinates(-1,-1);
            valid=true;
        }//north
        else if(i + 1 < col && cells[j][i+1].getCol()!=-1 && cells[j][i+1].getRow()!=-1){
            currentCell=cells[j][i+1];
            i++;
            path.push(currentCell);
//            cout<<path.top()<<endl;
            cells[j][i].setCoordinates(-1,-1);
            valid=true;
        }//east
        else if(j + 1 < row && cells[j+1][i].getCol()!=-1 && cells[j+1][i].getRow()!=-1){
            currentCell=cells[j+1][i];
            j++;
            path.push(currentCell);
//            cout<<path.top()<<endl;
            cells[j][i].setCoordinates(-1,-1);
            valid=true;
        }//south
        else if(i > 0 && cells[j][i-1].getCol()!=-1 && cells[j][i-1].getRow()!=-1){
            currentCell=cells[j][i-1];
            i--;
            path.push(currentCell);
//            cout<<path.top()<<endl;
            cells[j][i].setCoordinates(-1,-1);
            valid=true;
        }//west
        else{//checked every direction
            currentCell=path.top();//go to the last spot
            j=currentCell.getRow();
            i=currentCell.getCol();
            path.pop();
        }
    }
//cout<<"done";
while(!path.empty()){
    cout<<path.top()<<endl;
    path.pop();
}

//    for (int i = 0; i < 5; ++i) {
//        MazeCell*currCell=&cells[yPos][xPos];
//        //cout<<*currCell;
//        while (currCell->unVisited()) {
//            MazeCell *nextCell=currCell;
//            if (currCell->getDirection() == 0 && yPos > 0) {
//                nextCell = &cells[yPos - 1][xPos];
//                if (nextCell->unVisited() && grid[yPos - 1][xPos] != 0) {
//                    path.push(*currCell);
//                    currCell->visit();
//                }
//            }
//            if (currCell->getDirection() == 1 && xPos < cols) {
//                cout<<"f";
//                nextCell = &cells[yPos][xPos + 1];
//                if (nextCell->unVisited() && grid[yPos][xPos + 1] != 0) {
//                    path.push(*currCell);
//                    currCell=&cells[yPos][xPos + 1];
//                    currCell->visit();
//                }
//            }
//            if (currCell->getDirection() == 2 && yPos < rows) {
//                nextCell = &cells[yPos + 1][xPos];
//                if (nextCell->unVisited() && grid[yPos + 1][xPos] != 0) {
//                    path.push(*currCell);
//                    currCell->visit();
//                }
//            }
//            if (currCell->getDirection() == 3 && xPos > 0) {
//                nextCell = &cells[yPos][xPos - 1];
//                if (nextCell->unVisited() && grid[yPos][xPos - 1] != 0) {
//                    path.push(*currCell);
//                    currCell->visit();
//                }
//            }
//            //cout<<*nextCell;
//
//            currCell->advanceDirection();
//        }
//        cout<<path.top();
//    }

//    for (int i = 0; i < 7; ++i) {
//        MazeCell currCell = cells[yPos][xPos];
//        int barriers=0;
//        cout<<currCell;
//
//        while (currCell.unVisited()) {
//            if(currCell==end){
//                path.push(currCell);
//                break;
//            }
//            if(currCell.getDirection()==0&&yPos>0){
//                if(cells[yPos-1][xPos].unVisited()&&grid[yPos-1][xPos]!=0){
//                    currCell.visit();
//                    cells[yPos][xPos].visit();
//                    path.push(currCell);
//                    yPos--;
//                }
//            }
//            else if(currCell.getDirection()==1&&xPos<cols){
//                if(cells[yPos][xPos+1].unVisited()&&grid[yPos][xPos+1]!=0){
//                    currCell.visit();
//                    cells[yPos][xPos].visit();
//                    path.push(currCell);
//                    xPos++;
//                }
//            }
//            else if(currCell.getDirection()==2&&yPos<rows){
//                if(cells[yPos+1][xPos].unVisited()&&grid[yPos+1][xPos]!=0){
//                    currCell.visit();
//                    cells[yPos][xPos].visit();
//                    path.push(currCell);
//                    yPos++;
//                }
//            }
//            else if(currCell.getDirection()==3&&xPos>0){
//                if(cells[yPos][xPos-1].unVisited()&&grid[yPos][xPos-1]!=0){
//                    currCell.visit();
//                    cells[yPos][xPos].visit();
//                    path.push(currCell);
//                    xPos--;
//                }
//            }
//            barriers++;
//            currCell.advanceDirection();
////            cells[yPos][xPos].advanceDirection();
//        }
////        cout<<barriers;
//        cout<<currCell;
//        if(barriers==4){
//            cells[yPos][xPos].visit();
//            xPos=path.top().getCol();
//            yPos=path.top().getRow();
//            cells[yPos][xPos].reset();
//            path.pop();
//        }
//
//    }
//    cout<<endl;
//    cout<<"cell visit map:"<<endl;
//    //iterate over the grid
//    for (int i = 0; i < rows; i++) {
//        for (int j = 0; j < cols; j++) {
//            cout<<cells[i][j].getVisit()<<" ";
//
//        }
//        cout<<endl;
//    }

}

