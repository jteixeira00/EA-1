//g++ -std=c++17 -Wall -Wextra -O2 "Trabalho1.cpp" -lm

#include <iostream>
#include <unordered_map>
#include <list>
#include <algorithm>

using namespace std;


int main() {
// We probably do not need this but it is faster
    string order;
    int size;
    //int key;
    int max;
    int count = 0;
    int num;
    int maxSlides;

    int posx = 0;
    int posy = 0;

    cin >> max;

    while(max != count){        

        cin >> size >> maxSlides;

        while(posy != size){

            cin >> num;

            cout << posx << " " << posy << '\n';

            if(posx != size - 1){
                ++posx;
            }
            else{
                ++posy;
                posx = 0;
            }

        }
        posx = posy = 0;
        count++;
        
    }       

    return 0;    
}