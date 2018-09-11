#include <bits/stdc++.h>
using namespace std;

const double eps=1e-7;
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
    Point operator * (double b){ // 数乘
        return Point(x*b,y*b);
    }
    double operator * (Point b){ // 点乘
        return x*b.x+y*b.y;
    }
    Point operator / (double b){ // 数除
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
    inline Point vec(){
        return p1-p2;
    }
    inline bool operator || (Line l2){ // 判断两直线是否平行
        return (dcmp(a*l2.b-b*l2.a)==0);
    }
    inline bool operator == (Line l2){ // 判断两直线是否相等
        if (!(*this||l2)) return 0;
        else return (dcmp(a*l2.c-c*l2.a)==0 &&
            dcmp(b*l2.c-c*l2.b)==0);
    }
};

inline double Length(Point a){ // 线段长度（重载
    return a*a;
}

inline double Length(Line a){ // 线段长度（重载
    return Length(a.p1-a.p2);
}

inline double Length(Point a,Point b){ // 两点之间的距离
    return Length(a-b);
}

inline double Angle(Point a,Point b){ // 计算角度
    return acos(a*b/Length(a)/Length(b));
}

inline double Angle(Line a,Line b){
    return Angle(a.vec(),b.vec());
}

inline double Area2(Point a,Point b,Point c){// 三角形面积两倍，平行四边形面积
    return (b-a)^(c-a);
}

inline Point SymPoint(Point p,Line l) {  // 求二维平面上点p关于直线p1p2的对称点
    Point result;
    double a=l.p2.x-l.p1.x;
    double b=l.p2.y-l.p1.y;
    double t=((p.x-l.p1.x)*a+(p.y-l.p1.y)*b)/(a*a+b*b);
    result.x=2*l.p1.x+2*a*t-p.x;
    result.y=2*l.p1.y+2*b*t-p.y;
    return result;
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