#include <iostream>
#include <ctime>
#include "TXLib.h"
using namespace std;

int main()
{
    clock_t start;
    int i = 3; //Время перезарядки в секундах
    start = clock();
    txMessageBox("Space - перезарядка 3 секунды\nSpace + Shift - перезарядка 6 секунд");
    while(!GetAsyncKeyState(VK_ESCAPE)){
        if(GetAsyncKeyState(VK_SPACE) && (clock() - start) / CLK_TCK >= i){
            cout << "Прошло секунд " << (clock() - start) / CLK_TCK;
            start = clock();
            i = 3;
            if(GetAsyncKeyState(VK_SHIFT))
                i = 6;
            cout << ": До следующего нажатия " << i << " секунд(ы)" << endl;
        }
    }
    cout << "Программа работала " << clock() / CLK_TCK << " секунд(ы)";
}
