#include <iostream>
#include <stack>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point
{
    int x, y;
};

Point p0;

Point nextToTop(stack<Point> &S)
{
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}

void swap(Point &p1, Point &p2)
{
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}

int distSq(Point p1, Point p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) +
           (p1.y - p2.y) * (p1.y - p2.y);
}

int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0)
        return 0;
    return (val > 0) ? 1 : 2;
}

int compare(const void *vp1, const void *vp2)
{
    Point *p1 = (Point *)vp1;
    Point *p2 = (Point *)vp2;

    int o = orientation(p0, *p1, *p2);
    if (o == 0)
        return (distSq(p0, *p2) >= distSq(p0, *p1)) ? -1 : 1;

    return (o == 2) ? -1 : 1;
}

void convexHull(Point points[], int n)
{
    int ymin = points[0].y, minIndex = 0;
    for (int i = 1; i < n; i++)
    {
        int y = points[i].y;

        if ((y < ymin) || (ymin == y &&
                           points[i].x < points[minIndex].x))
            ymin = points[i].y, minIndex = i;
    }

    swap(points[0], points[minIndex]);

    p0 = points[0];
    qsort(&points[1], n - 1, sizeof(Point), compare);

    int m = 1;
    for (int i = 1; i < n; i++)
    {
        while (i < n - 1 && orientation(p0, points[i], points[i + 1]) == 0)
            i++;

        points[m] = points[i];
        m++;
    }

    if (m < 3)
        return;

    stack<Point> S;
    S.push(points[0]);
    S.push(points[1]);
    S.push(points[2]);

    for (int i = 3; i < m; i++)
    {
        while (S.size() > 1 && orientation(nextToTop(S), S.top(), points[i]) != 2)
            S.pop();
        S.push(points[i]);
    }

    // Tính diện tích của bao lồi
    double area = 0.0;
    vector<Point> convexHullPoints;
    while (!S.empty())
    {
        Point p = S.top();
        convexHullPoints.push_back(p);
        S.pop();
    }

    for (int i = 0; i < convexHullPoints.size(); i++)
    {
        int j = (i + 1) % convexHullPoints.size();
        area += (convexHullPoints[i].x * convexHullPoints[j].y - convexHullPoints[j].x * convexHullPoints[i].y);
    }
    area = abs(area) / 2.0;

    cout << "Bao loi duoc tim thay: ";
    for (int i = 0; i < convexHullPoints.size(); i++)
    {
        cout << "(" << convexHullPoints[i].x << ", " << convexHullPoints[i].y << ") ";
    }
    cout << endl;
    cout << "Dien tich cua bao loi: " << area << endl;

    // Tính khoảng cách ngắn nhất giữa các đỉnh
    double minDist = INT_MAX;
    for (int i = 0; i < convexHullPoints.size(); i++)
    {
        for (int j = i + 1; j < convexHullPoints.size(); j++)
        {
            int dist = distSq(convexHullPoints[i], convexHullPoints[j]);
            minDist = min(minDist, (double)dist);
        }
    }

    cout << "Khoang cach ngan nhat giua cac dinh cua bao loi: " << sqrt(minDist) << endl;

    minDist = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            double dist = sqrt(distSq(points[i], points[j]));
            if (dist < minDist)
            {
                minDist = dist;
            }
        }
    }
    cout << "Khoang cach ngan nhat giua cac diem ben trong bao loi: " << minDist << endl;
}

int main()
{
    Point points[100];
    cout << "Nhap so luong diem:";
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        Point temp;
        temp.x = a;
        temp.y = b;
        points[i] = temp;
    }
    convexHull(points, n);
    return 0;
}
