#include <iostream>
#include <stdexcept>
#include <vector>
#include <stack>
#include <time.h>

class Cell{
    public:
        void removeLeftWall(){
            leftWall = false;
        }
        void removeUpWall(){
            upWall = false;
        }
        bool hasLeftWall(){
            return leftWall;
        }
        bool hasUpWall(){
            return upWall;
        }
        void IsOnPath(){
            onPath = true;
        }
        bool OnPath(){
            return onPath;
        }
        void printStatus(){
            std::cout << "left" << leftWall << " up" << upWall << " down" << std::endl;
        }
        bool visited;
        bool onPath;
    private:
        bool leftWall = true, upWall = true; 
};

class Coordinates{
    public:
        Coordinates(){
            x = 0;
            y = 0;
        }
        int getX() const{
            return x;
        }
        int getY() const{
            return y;
        }
        void setPos (int setX, int setY){
            x = setX;
            y = setY;
        }
    private:
        int x = 0;
        int y = 0;
};

void drawMaze(int width, int height, std::vector<std::vector<Cell>> cells, std::stack<Coordinates> backtrack){
    cells.at(height - 1).at(width - 1).onPath = true;

    while(backtrack.size() > 0){
        cells.at(backtrack.top().getY()).at(backtrack.top().getX()).onPath = false;
        backtrack.pop();
    }

    for(int y = 0; y < height; y++){
        std::cout << "+";
        for(int x = 0; x < width; x++){
            if(cells.at(y).at(x).hasUpWall() == true){
                std::cout << "---+";
            }
            else{
                std::cout << "   +";
            }
        }

        std::cout << std::endl;
        for(int x = 0; x < width; x++){
            if(cells.at(y).at(x).onPath == true && cells.at(y).at(x).hasLeftWall() == true){
                std::cout << "| . ";
            }
            else if(cells.at(y).at(x).onPath == true){
                std::cout << "  . ";
            }
            else if(cells.at(y).at(x).hasLeftWall() == true){
                std::cout << "|   ";
            }
            else{
                std::cout << "    ";
            }
        }
        std::cout << "|" << std::endl;
    }

    std::cout << "+";
        for(int i = 0; i < width; i++){
        std::cout << "---+";
    }
    exit(0);
}

void createMaze(unsigned int width, unsigned int height, std::vector<std::vector<Cell>>& cells){
    unsigned int visitedCounter = 0, random;
    Coordinates currentPosition;
    std::stack<Coordinates> history;
    cells.at(0).at(0).visited = true;

    history.push(currentPosition);

    while(visitedCounter < width * height - 1){
        random = rand() % 4;
        if(random == 0 && currentPosition.getY() - 1 >= 0 && cells.at(currentPosition.getY() - 1).at(currentPosition.getX()).visited == false){
            cells.at(currentPosition.getY()).at(currentPosition.getX()).removeUpWall();
            cells.at(currentPosition.getY() - 1).at(currentPosition.getX()).visited = true;
            history.push(currentPosition);
            currentPosition.setPos(currentPosition.getX(), currentPosition.getY() - 1);
            visitedCounter++;
        }
        else if(random == 1 && currentPosition.getX() + 1 < width && cells.at(currentPosition.getY()).at(currentPosition.getX() + 1).visited == false){
            cells.at(currentPosition.getY()).at(currentPosition.getX() + 1).removeLeftWall();
            cells.at(currentPosition.getY()).at(currentPosition.getX() + 1).visited = true;
            history.push(currentPosition);
            currentPosition.setPos(currentPosition.getX() + 1, currentPosition.getY());
            visitedCounter++;           
        }
        else if(random == 2 && currentPosition.getY() + 1 < height && cells.at(currentPosition.getY() + 1).at(currentPosition.getX()).visited == false){
            cells.at(currentPosition.getY() + 1).at(currentPosition.getX()).removeUpWall();
            cells.at(currentPosition.getY() + 1).at(currentPosition.getX()).visited = true;
            history.push(currentPosition);
            currentPosition.setPos(currentPosition.getX(), currentPosition.getY() + 1);
            visitedCounter++;
        }
        else if(random == 3 && currentPosition.getX() - 1 >= 0 && cells.at(currentPosition.getY()).at(currentPosition.getX() - 1).visited == false){
            cells.at(currentPosition.getY()).at(currentPosition.getX()).removeLeftWall();
            cells.at(currentPosition.getY()).at(currentPosition.getX() - 1).visited = true;
            history.push(currentPosition);
            currentPosition.setPos(currentPosition.getX() - 1, currentPosition.getY());
            visitedCounter++;
        }
        else if((currentPosition.getY() -1 < 0 || cells.at(currentPosition.getY()-1).at(currentPosition.getX()).visited == true) && (currentPosition.getX() + 1 >= width || cells.at(currentPosition.getY()).at(currentPosition.getX() + 1).visited == true) && (currentPosition.getY() + 1 >= height || cells.at(currentPosition.getY() + 1).at(currentPosition.getX()).visited == true) && (currentPosition.getX() - 1 < 0 || cells.at(currentPosition.getY()).at(currentPosition.getX() - 1).visited == true)){
            currentPosition.setPos(history.top().getX(), history.top().getY());
            history.pop();
        }
    }
}

bool findPath(Coordinates from, Coordinates to, std::vector<std::vector<Cell>>& cells, std::stack<Coordinates> history, std::stack<Coordinates>& backtrack){
    int width = cells.at(0).size(), height = cells.size();
    Coordinates up, right, down, left;

    up.setPos(from.getX(), from.getY() - 1);
    right.setPos(from.getX() + 1, from.getY());
    down.setPos(from.getX(), from.getY() + 1);
    left.setPos(from.getX() - 1, from.getY());

    cells.at(from.getY()).at(from.getX()).visited = false;

    if(from.getX() == to.getX() && from.getY() == to.getY()){
        return true;
    }
    else{
        if(from.getY() - 1 >= 0 && cells.at(from.getY()).at(from.getX()).hasUpWall() == false && cells.at(from.getY()-1).at(from.getX()).visited == true){
            history.push(from);
            if(findPath(up, to, cells, history, backtrack) == true){
                cells.at(from.getY()).at(from.getX()).onPath = true;
                return true;
            }
        }
        else if(from.getX() + 1 < width && cells.at(from.getY()).at(from.getX() + 1).hasLeftWall() == false && cells.at(from.getY()).at(from.getX() + 1).visited == true){
            history.push(from);
            if(findPath(right, to, cells, history, backtrack) == true){
                cells.at(from.getY()).at(from.getX()).onPath = true;
                return true;
            }
        }
        else if(from.getY() + 1 < height && cells.at(from.getY() + 1).at(from.getX()).hasUpWall() == false && cells.at(from.getY() + 1).at(from.getX()).visited == true){
            history.push(from);
            if(findPath(down, to, cells, history, backtrack) == true){
                cells.at(from.getY()).at(from.getX()).onPath = true;
                return true;
            }
        }
        else if(from.getX() - 1 >= 0 && cells.at(from.getY()).at(from.getX()).hasLeftWall() == false && cells.at(from.getY()).at(from.getX() - 1).visited == true){
            history.push(from);
            if(findPath(left, to, cells, history, backtrack) == true){
                cells.at(from.getY()).at(from.getX()).onPath = true;
                return true;
            }
        }
        else if((from.getY() -1 < 0 || cells.at(from.getY()-1).at(from.getX()).visited == false) && (from.getX() + 1 >= width || cells.at(from.getY()).at(from.getX() + 1).visited == false) && (from.getY() + 1 >= height || cells.at(from.getY() + 1).at(from.getX()).visited == false) && (from.getX() - 1 < 0 || cells.at(from.getY()).at(from.getX() - 1).visited == false)){
            backtrack.push(from);
            from.setPos(history.top().getX(), history.top().getY());
            history.pop();            
            if(findPath(from, to, cells, history, backtrack) == true){
                return true;
            }
        }
        return false;
    }
}

int main(int argc, char* argv[]){
    try{
        if(argc < 3){
            throw std::runtime_error("No dimensions specified");
        }        
    }
    catch(std::runtime_error excpt){
        std::cout << excpt.what() << std::endl;
        exit(-1);
    }

    if(argv[3]){
        std::srand(atoi(argv[3]));
    }
    else{
        std::srand(time(NULL));;
    }

    std::vector<std::vector<Cell>> cells(atoi(argv[1]), std::vector<Cell>(atoi(argv[2])));
    
    createMaze(atoi(argv[2]), atoi(argv[1]), cells);

    Coordinates from, to;
    std::stack<Coordinates> history, backtrack;
    from.setPos(0, 0);
    to.setPos(atoi(argv[2]) - 1, atoi(argv[1]) - 1);
    findPath(from, to, cells, history, backtrack);

    drawMaze(atoi(argv[2]), atoi(argv[1]), cells, backtrack); 

    return 0;
}
