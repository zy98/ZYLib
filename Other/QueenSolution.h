#ifndef QUEENSOLUTION_H
#define QUEENSOLUTION_H

#include "Object/Object.h"
#include "iostream"

using namespace std;

namespace ZYLib
{

template <const int SIZE>
class QueenSolution:public Object
{
protected:
    enum{N=SIZE+2};
    //static const int N=SIZE+2;?
    int chess[N][N];
    int m_count;

    struct Pos:public Object
    {
        Pos(int i=0,int j=0):x(i),y(j){}
        int x;
        int y;
    };

public:
    QueenSolution()
    {
        m_count=0;

        for(int i=0;i<N;i++)
        {
            if(i==0 || i==N-1)
            {
                for(int j=0;j<N;j++)
                    chess[i][j]=2;
            }
            else
            {
                chess[i][0]=chess[i][N-1]=2;
                for(int j=1;j<N-1;j++)
                    chess[i][j]=0;
            }
        }
    }

    int count() const
    {
        return m_count;
    }

    void print()
    {
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                switch(chess[i][j])
                {
                    case 0:cout<<"+ ";break;
                    case 1:cout<<"* ";break;
                    case 2:cout<<"# ";break;
                }
            }
            cout<<endl;
        }
    }

    bool check(Pos point,const Pos& d)
    {
        bool ret=true;

        do
        {
            point.x+=d.x;
            point.y+=d.y;
            ret=ret && (chess[point.x][point.y] == 0);
        }
        while(ret);

        return chess[point.x][point.y] == 2;
    }

    bool checkAll(Pos point)
    {
        return check(point,Pos(-1,-1)) && check(point,Pos(0,-1)) && check(point,Pos(1,-1));
    }

    void run(int j)
    {
        if(j <= SIZE)
        {
            for(int i=1;i<=SIZE;i++)
            {
                if(checkAll(Pos(i,j)))
                {
                    chess[i][j]=1;

                    run(j+1);

                    chess[i][j]=0;
                }
            }
        }
        else
        {
            cout<<m_count++<<endl;
            print();
            cout<<endl;
        }
    }
};

}

#endif // QUEENSOLUTION_H
