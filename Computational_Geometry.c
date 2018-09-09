#include <bits/stdc++.h>
using namespace std;

const double eps=1e-6;

inline int dcmp(double x){
    if (fabs(x)<eps)return 0;
    else return x<0?-1:1;
}

struct Point{
    double x,y;
    Point(double _x=0,double _y=0):x(_x),y(_y){}
    Point(const Point& b):x(b.x),y(b.y){}
    Point operator + (Point b){ //对应坐标加
        return Point(x+b.x,y+b.y);
    }
    Point operator - (Point b){ //对应坐标减
        return Point(x-b.x,y-b.y);
    }
    Point operator * (double b){ //对应坐标除以常数
        return Point(x*b,y*b);
    }
    Point operator / (double b){ //对应坐标除以常数
        return Point(x/b,y/b);
    }
    double operator ^ (Point b){ //叉乘
        return x*b.y-y*b.x;
    }
    bool operator == (Point b){ //判断两个点是否相同
        return dcmp(x-b.x)==0&&dcmp(y-b.y)==0;
    }
};

struct Line{
    Point a,b;
    Line(Point _a=Point(),Point _b=Point()):a(_a),b(_b){}
};

typedef Point Vector;

inline double Dot(Point a,Point b){ //点乘
    return a.x*b.x+a.y*b.y;
}

inline double Cross(Point a,Point b){ //叉乘
    return a.x*b.y-a.y*b.x;
}

inline double Length(Point a){ //线段长度（重载
    return Dot(a,a);
}

inline double Length(Line a){ //线段长度（重载
    return Length(a.a-a.b);
}

inline double Angle(Point a,Point b){ //计算角度（重载
    return acos(Dot(a,b)/Length(a)/Length(b));
}

inline double Angle(Line a){ //计算角度（重载
    return Angle(a.a,a.b);
}


inline double Area2(Point a,Point b,Point c){//三角形面积两倍，平行四边形面积
    return Cross(b-a,c-a);
}

int main(){
    Point a(1,2),b(3,4),c(5,6);
    Point d=a+b+c;
    cout<<d.x<<' '<<d.y<<endl;
    double e= a^b;
    cout<<e<<endl;
    
}