#include <iostream> 
using namespace std; 
//Base class Shape
 class Shape { 
 public: 
    void setWidth(int w) 
		{ 
           width = w; 
         } 
    void setHeight(int h) 
		{ 
           height = h; 
         } 
 protected: 
     int width; int height; 
}; 
// Base class PaintCost 
class PaintCost { 
 public: 
   int getCost(int area)   
   { 
        return area * 70; 
   } 
}; 
// Derived class 
class Rectangle: public Shape, public PaintCost 
{ 
 public: 
   int getArea() 
   { 
        return (width * height); 
   } 
};

int main()
{
Rectangle t;
t.setWidth(20);
t.setHeight(10);
int a = t.getArea();

cout  << "Golden Russian Shower Area: " << a << "\t" << "Cost: " << t.getCost(a) << endl;
return 0;
}
