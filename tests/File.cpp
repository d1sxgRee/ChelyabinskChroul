#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

class Point{
private:
    double a;
    double b;
    double c;
public:
    Point(double _a = 0, double _b = 0, double _c = 0);
    void print();
};

Point::Point(double _a, double _b, double _c) :
    a(_a), b(_b), c(_c){}
void Point::print(){
    cout << a << " "<< b << " " << c << endl;
}


int main(){
    string a, b, c;
    string file_name = "TestFile.txt";
    ifstream level_file;
    level_file.open(file_name);
    assert(level_file.is_open());
    for(size_t i = 0; i < 3; i++)
    {
        while(!level_file.eof())
        {
            level_file >> a;
            if(a == "*")
                break;
            level_file >> b;
            level_file >> c;
            Point ptr(strtod(a.c_str(), NULL), strtod(b.c_str(), NULL), strtod(c.c_str(), NULL));
            ptr.print();
        }
        cout << endl;
    }
    cout << "Success";
    level_file.close();
}


