#include <functional>
#include <iomanip>
#include <iostream>
#include <random>

#include "list.hpp"
#include "shape.hpp"

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> gen_distr(0, 4);
    std::uniform_int_distribution<> shape_distr(3, 5);

    std::function<std::shared_ptr<quadrangle>()> generators[5];
    auto g0 = [&]() {
        return std::make_shared<trapezoid>(shape_distr(gen), shape_distr(gen),
                                           shape_distr(gen));
    };

    auto g1 = [&]() {
        return std::make_shared<parallelogram>(shape_distr(gen),
                                               shape_distr(gen));
    };

    auto g2 = [&]() {
        return std::make_shared<rectangle>(shape_distr(gen), shape_distr(gen));
    };

    auto g3 = [&]() {
        return std::make_shared<diamond>(shape_distr(gen), shape_distr(gen));
    };

    auto g4 = [&]() {
        return std::make_shared<square>(shape_distr(gen));
    };

    generators[0] = g0;
    generators[1] = g1;
    generators[2] = g2;
    generators[3] = g3;
    generators[4] = g4;

    riley::list<std::shared_ptr<quadrangle>> shape_list;

    for (int i = 0; i < 9; i++)
        shape_list.push_front(generators[gen_distr(gen)]());

    double ans[shape_list.size()];
    size_t cnt = 0, correct_cnt = 0;

    std::cout << "Practice begins!\n\n";

    for (auto&& item : shape_list) {
        std::cout << item->shape() << ": " << item->statistic() << "\n"
                  << "Please input area: ";

        std::cin >> ans[cnt];
        if (std::abs(ans[cnt] - item->area()) < 0.00005) {
            std::cout << "Correct!\n\n";
            correct_cnt++;
        } else
            std::cout << "Wrong!\n\n";

        cnt++;
    }

    std::cout << "---------------------------------\n\n"
              << "Reviewing.....\n\n";
    cnt = 0;
    for (auto&& item : shape_list) {
        std::cout << item->shape() << "\n"
                  << item->statistic() << "\n"
                  << "area: " << std::fixed << std::setprecision(2)
                  << item->area() << ", Your answer: " << std::fixed
                  << std::setprecision(2) << item->area() << " | "
                  << ((std::abs(ans[cnt++] - item->area()) < 0.00005)
                          ? "Correct"
                          : "Wrong")
                  << "\n\n";
    }

    std::cout << "Total: " << shape_list.size() << ", Correct:" << correct_cnt
              << "\n";

    return 0;
}
