#include <iomanip>
#include <iostream>

class Point3D {
   public:
    Point3D(double x = 0.0f, double y = 0.0f, double z = 0.0f)
        : x(x), y(y), z(z) {}
    // Point3D(const Point3D& p) = default;
    // Point3D(Point3D&& p) = default;

    ~Point3D() = default;

    Point3D translate(double dx, double dy, double dz) {
        return Point3D(x + dx, y + dy, z + dz);
    }

    Point3D scale(double sx, double sy, double sz) {
        return Point3D(x * sx, y * sy, z * sz);
    }

    friend std::istream& operator>>(std::istream& is, Point3D& p);
    friend std::ostream& operator<<(std::ostream& os, Point3D& p);

   private:
    double x, y, z;
};

std::istream& operator>>(std::istream& is, Point3D& p) {
    is >> p.x >> p.y >> p.z;
    return is;
}

std::ostream& operator<<(std::ostream& os, Point3D& p) {
    os << std::fixed << std::showpoint;
    os << std::setprecision(2) << "(" << p.x << "," << p.y << "," << p.z << ")";
    return os;
}

int main() {
    Point3D p1, p2;
    std::cin >> p1;
    p2 = p1.translate(2, 3, 4);
    p1 = p2.scale(1.5, 0.5, 2.5);
    std::cout << p1;
    return 0;
}