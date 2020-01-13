#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>

class quadrangle {
   protected:
    quadrangle() = default;

   public:
    ~quadrangle() = default;

    virtual double area() = 0;
    virtual std::string shape() = 0;
    virtual std::string statistic() = 0;
};

class trapezoid : public quadrangle {
   public:
    trapezoid() = delete;
    trapezoid(double topline, double baseline, double height)
        : topline(topline), baseline(baseline), height(height) {}

    double area() { return (topline + baseline) * height / 2.0; }

    std::string shape() { return std::string("trapezoid"); }

    std::string statistic() {
        return std::string("topline: ") + std::to_string(topline).substr(0, 4) +
               std::string(", baseline: ") +
               std::to_string(baseline).substr(0, 4) +
               std::string(", height: ") + std::to_string(height).substr(0, 4);
    }

   private:
    double topline, baseline, height;
};

class parallelogram : public quadrangle {
   protected:
    parallelogram() = default;

   public:
    parallelogram(double baseline, double height)
        : baseline(baseline), height(height) {}

    double area() { return baseline * height; }

    virtual std::string shape() { return std::string("parallelogram"); }

    virtual std::string statistic() {
        return std::string("baseline: ") +
               std::to_string(baseline).substr(0, 4) +
               std::string(", height: ") + std::to_string(height).substr(0, 4);
    }

   protected:
    double baseline, height;
};

class rectangle : virtual public parallelogram {
   protected:
    rectangle() = default;

   public:
    rectangle(double baseline, double height)
        : parallelogram(baseline, height) {}

    virtual std::string shape() { return std::string("rectangle"); }
};

class diamond : virtual public parallelogram {
   protected:
    diamond() = default;

   public:
    diamond(double diag1, double diag2) : parallelogram(diag1, diag2) {}

    virtual std::string shape() { return std::string("diamond"); }

    virtual std::string statistic() {
        return std::string("diagnal1: ") +
               std::to_string(baseline).substr(0, 4) +
               std::string(", diagnal2: ") +
               std::to_string(height).substr(0, 4);
    }
};

class square : public rectangle, public diamond {
   public:
    square() = delete;
    square(double side_length) : parallelogram(side_length, side_length) {}

    std::string shape() { return std::string("square"); }

    std::string statistic() {
        return std::string("side length: ") +
               std::to_string(baseline).substr(0, 4);
    }
};

#endif