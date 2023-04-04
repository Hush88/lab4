#include <iostream> 
#include <vector> 
#define _USE_MATH_DEFINES //M_PI
#include <cmath>

using namespace std;

// ���������� ����� Point ��� �������� ��������� �����
class Point {
private:
    double x, y;
public:
    Point(double _x, double _y) : x(_x), y(_y) {}
    double getX() const { return x; }
    double getY() const { return y; }
    void setX(double _x) { x = _x; }
    void setY(double _y) { y = _y; }
    void print() const {
        cout << "(" << x << "," << y << ")";
    }
};

// ���������� ����� Segment ��� �������� �������
class Segment {
private:
    Point p1, p2; // ��������� � �������� ����� �������
public:
    Segment(Point _p1, Point _p2) : p1(_p1), p2(_p2) {}
    Point getP1() const { return p1; } // ����� ��� ��������� ��������� ����� �������
    Point getP2() const { return p2; } // ����� ��� ��������� �������� ����� �������
    void setP1(Point _p1) { p1 = _p1; } // ����� ��� ��������� ��������� ����� �������
    void setP2(Point _p2) { p2 = _p2; } // ����� ��� ��������� �������� ����� �������
    double length() const { // ����� ��� ��������� ����� �������
        double dx = p1.getX() - p2.getX();
        double dy = p1.getY() - p2.getY();
        return sqrt(dx * dx + dy * dy);
    }
};

// ���������� ����� Square ��� �������� ��������
class Square {
private:
    vector<Point> vertices; // �������� ������ ��������
    char fillChar; // ������, ������������ ��� ���������� ��������
public:
    Square(Point center, double size, char _fillChar = '*') : fillChar(_fillChar) {
        // ������� ������� � �������� ������� � ��������, � ���������� ��� �������
        Point p1(center.getX() - size / 2, center.getY() - size / 2);
        Point p2(center.getX() - size / 2, center.getY() + size / 2);
        Point p3(center.getX() + size / 2, center.getY() + size / 2);
        Point p4(center.getX() + size / 2, center.getY() - size / 2);
        vertices.push_back(p1);
        vertices.push_back(p2);
        vertices.push_back(p3);
        vertices.push_back(p4);
    }
    void draw() const {
        // ������ �������
        double minX = vertices[0].getX();
        double maxX = vertices[0].getX();
        double minY = vertices[0].getY();
        double maxY = vertices[0].getY();
        for (const auto& vertex : vertices) {
            minX = min(minX, vertex.getX());
            maxX = max(maxX, vertex.getX());
            minY = min(minY, vertex.getY());
            maxY = max(maxY, vertex.getY());
        }
        for (double y = minY; y <= maxY; y++) {
            for (double x = minX; x <= maxX; x++) {
                bool inside = false;
                for (size_t i = 0, j = vertices.size() - 1; i < vertices.size(); j = i++) {
                    const Point& vi = vertices[i];
                    const Point& vj = vertices[j];
                    if ((vi.getY() > y) != (vj.getY() > y) &&
                        (x < (vj.getX() - vi.getX()) * (y - vi.getY()) / (vj.getY() - vi.getY()) + vi.getX())) {
                        inside = !inside;
                    }
                }
                if (inside) {
                    cout << fillChar;
                }
                else {
                    cout << " ";
                }
            }
            cout << endl;
        }
    }
    void resize(double factor) {
        // ��������������� ��������
        Point center = getCenter();
        for (auto& vertex : vertices) {
            double dx = vertex.getX() - center.getX();
            double dy = vertex.getY() - center.getY();
            dx *= factor;
            dy *= factor;
            vertex.setX(center.getX() + dx);
            vertex.setY(center.getY() + dy);
        }
    }
    void rotate(double angle) {
        // ��������� ����� ��������
        Point center = getCenter();
        for (auto& vertex : vertices) {
            double dx = vertex.getX() - center.getX();
            double dy = vertex.getY() - center.getY();
            // ������������ ����� �� �������� ����
            double newX = dx * cos(angle) - dy * sin(angle);
            double newY = dx * sin(angle) + dy * cos(angle);
            // ���������� ����� ������� � ��������� ������������ ������ ��������
            vertex.setX(center.getX() + newX);
            vertex.setY(center.getY() + newY);
        }
    }
    void setColor(char _fillChar) {
        // ������������� ������ ���������� ��������
        fillChar = _fillChar;
    }
    Point getCenter() const {
        double sumX = 0, sumY = 0;
        // ��������� ���������� ���� ������
        for (const auto& vertex : vertices) {
            sumX += vertex.getX();
            sumY += vertex.getY();
        }
        // ��������� ������� �������������� ��������� ������, ����� �������� ���������� ������ ��������
        double centerX = sumX / vertices.size();
        double centerY = sumY / vertices.size();
        return Point(centerX, centerY);
    }
};

int main() {
    // ���������� ��������� M_PI
    const double M_PI = acos(-1);
    // ������� ������� � ���������� ���
    Point center(10, 10);
    Square square(center, 10);
    square.draw();
    // �������� ������ ���������� � ������������ ������� �����
    square.setColor('#');
    square.resize(2);
    square.draw();
    // ������������ ������� �� 45 �������� � ���������� ���
    square.rotate(M_PI / 4);
    square.draw();
    return 0;
}
