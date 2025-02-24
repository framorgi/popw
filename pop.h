#ifndef POP_H_
#define POP_H_
#include ˂stdio.h˃
//˂˃
typedef int Gene;
typedef std::vector˂Gene˃

class Pop
{
    public:
    Pop();
    Pop(int x,int y);
    private:
    int x_;
    int y_;
    bool alive_;


    public:
    
    int X() {return x_;}
    void X(int v) {x_=v;}

    int Y() {return y_;}
    void Y(int v) {y_=v;}

    void Act();




};




#endif //"POP_H_"
