#include <iostream>
#include <cmath>

//Записать алгоритм нахождения точек пересечения двух прямых, прямой и отрезка, 
//двух отрезков, прямой и окружности, отрезка и окружности, двух окружностей.
//С помощью данных алгоритмов решить следующую задачу :


//В заданном множестве точек на плоскости найти 11 точек, определяющих
//систему из двух четырехугольников и окружности : "малый" четырехугольник
//и окружность вложены в "большой" четырехугольник, "малый" четырехугольник
//и окружность не пересекаются и не вложены друг в друга.






struct Point {
    double x;
    double y;
};

struct Line {
    double A;
    double B;
    double C;
};

//Находим расстояние между двумя точками
double distanceBetweenPoints(Point p1, Point p2) {
    return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
}

//Нахождение пересечения прямых
//прямые представилены как Ax+by+c=0
void findIntersectionPoints(Line line1, Line line2, Point& intersectionPoint) {
    double determinant = line1.A * line2.B - line2.A * line1.B;

    if (determinant == 0) {
        std::cout << "Lines are parallel, no intersection points." << std::endl;
        return;
    }

    intersectionPoint.x = (line2.B * line1.C - line1.B * line2.C) / determinant;
    intersectionPoint.y = (line1.A * line2.C - line2.A * line1.C) / determinant;
}

//точка пересечения прямой и отрезка
void findIntersectionPoints(Line line, Point linePoint, Point point1, Point point2, Point& intersectionPoint) {
    double deltaX = point2.x - point1.x;
    double deltaY = point2.y - point1.y;

    Line segmentLine;
    segmentLine.A = -deltaY;
    segmentLine.B = deltaX;
    segmentLine.C = -segmentLine.A * point1.x - segmentLine.B * point1.y;

    findIntersectionPoints(line, segmentLine, intersectionPoint);
}

//Нахождение точкек пересечения прямой и окружности
void findIntersectionPoints(Point center, double radius, Line line, Point& intersectionPoint1, Point& intersectionPoint2) {
    double A = line.A;
    double B = line.B;
    double C = line.C;
    double r = radius;

    double distance = A * center.x + B * center.y + C;

    if (std::abs(distance) > r) {
        std::cout << "No intersection points." << std::endl;
        return;
    }

    double sqrtPart = std::sqrt(std::pow(r, 2) - std::pow(distance, 2));
    double mult = 1 / std::sqrt(std::pow(A, 2) + std::pow(B, 2));

    intersectionPoint1.x = center.x - B * mult * distance + A * mult * sqrtPart;
    intersectionPoint1.y = center.y + A * mult * distance + B * mult * sqrtPart;

    intersectionPoint2.x = center.x - B * mult * distance - A * mult * sqrtPart;
    intersectionPoint2.y = center.y + A * mult * distance - B * mult * sqrtPart;
}

//Нахождение точки пересечения окружности с отрезком
void findIntersectionPoints(Point center, double radius, Point point1, Point point2, Point& intersectionPoint1, Point& intersectionPoint2) {
    Line line;
    line.A = point1.y - point2.y;
    line.B = point2.x - point1.x;
    line.C = point1.x * point2.y - point2.x * point1.y;

    findIntersectionPoints(center, radius, line, intersectionPoint1, intersectionPoint2);
}

int main() {
    //не доделано
   //начал делать 19, расписал методы для нахождения пересечений точек, 
   // но я не совсем понимаю как дальше подступить к задаче

    return 0;
}
