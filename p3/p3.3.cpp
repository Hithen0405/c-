#include<iostream>
using namespace std;
class Point{
    int x,y;
    public:
        Point(int x=0,int y=0):x(x),y(y){}
        Point add(const Point &p) const{
            return Point(x+p.x,y+p.y);
        }
        Point& SetX(int x){
            this->x=x;
            return *this;
        }
        Point& SetY(int y){
            this->y=y;
            return *this;
        }
        void show() const{
            cout<<"("<<x<<","<<y<<")"<<endl;
        }
};
void shift(Point &p){
    p.SetX(99);
}
void tryshift(Point p){
    p.SetX(-1);
}
int main(){
    Point a(1,2),b(3,4);
    Point c=a.add(b);
    c.show();
    Point d;
    d.SetX(7).SetY(8);
    d.show();
    shift(a);
    a.show();
    tryshift(b);
    b.show();
    return 0;
}