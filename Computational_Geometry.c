#include <bits/stdc++.h>
using namespace std;

const double eps=1e-6;
const double Pi=acos(-1);
typedef vector<int> Poly;

inline int dcmp(double x){
    fabs(x)<eps?0:(x<0?-1:1);
}

struct Point{ // 点类型
    double x,y;
    Point(double x=0,double y=0):x(x),y(y){}
    Point(const Point& b):x(b.x),y(b.y){}
    Point operator + (Point b){ // 对应坐标加
        return Point(x+b.x,y+b.y);
    }
    Point operator - (Point b){ // 对应坐标减
        return Point(x-b.x,y-b.y);
    }
    Point operator * (double b){ // 对应坐标除以常数
        return Point(x*b,y*b);
    }
    Point operator / (double b){ // 对应坐标除以常数
        return Point(x/b,y/b);
    }
    double operator ^ (Point b){ // 叉乘
        return x*b.y-y*b.x;
    }
    bool operator == (Point b){ // 判断两个点是否相同
        return dcmp(x-b.x)==0&&dcmp(y-b.y)==0;
    }
};

typedef Point Vector;

struct Circle{ // 圆类型
    Point c;
    double r;
    Circle(Point c=Point(),double r=0):c(c),r(r){}
};

struct Line{ // 线段类型
    double a,b,c,angle;
    Point p1,p2;
    Line(Point _a=Point(),Point _b=Point()):p1(_a),p2(_b){
        a=p1.y-p2.y;
        b=p2.x-p1.x;
        c=p1.x*p2.y-p2.x*p1.y;
        angle=atan2(p2.y-p1.y,p2.x-p1.x);
    }
};

inline double Dot(Point a,Point b){ // 点乘
    return a.x*b.x+a.y*b.y;
}

inline double Cross(Point a,Point b){ // 叉乘
    return a.x*b.y-a.y*b.x;
}

inline double Length(Point a){ // 线段长度（重载
    return Dot(a,a);
}

inline double Length(Line a){ // 线段长度（重载
    return Length(a.p1-a.p2);
}

inline double Angle(Point a,Point b){ // 计算角度
    return acos(Dot(a,b)/Length(a)/Length(b));
}

inline double Area2(Point a,Point b,Point c){// 三角形面积两倍，平行四边形面积
    return Cross(b-a,c-a);
}

// 最小圆覆盖

// 最近点对最远点对

//

int main(){
    Point a(1,2),b(3,4),c(5,6);
    Point d=a+b+c;
    cout<<d.x<<' '<<d.y<<endl;
    double e= a^b;
    cout<<e<<endl;
    return 0;
}