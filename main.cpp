#include "include/quadtree/node.h"
#include "include/quadtree/node_iterator.h"
#include "include/quadtree/node_pool.h"
#include "include/quadtree/quadtree.h"
#include "include/quadtree/quadtree_iterators.h"
#include "include/quadtree/rect.h"
#include "include/quadtree/trapezium.h"
#include <chrono>
#include <iostream>

int main() {
  {
    quadtree::Quadtree q{quadtree::Rect{0.f, 1.f, 0.f, 1.f}};

    q.refine_global(7);
    std::clog << "begin\n";

    int nn = 1;

    auto start = std::chrono::steady_clock::now();
    q.set_value(quadtree::Trapezium{quadtree::Point{0.15f, 0.65f}, 0.1f, 0.1f,
                                    -0.5f, 0.5f},
                12.45f);
    q.set_value(quadtree::Trapezium{quadtree::Point{0.55f, 0.15f}, 0.1f, 0.1f,
                                    -0.5f, 0.5f},
                12.45f);
    q.set_value(quadtree::Trapezium{quadtree::Point{-0.005f, -0.1f}, 0.01f,
                                    1.2f, -1e-10f, 1e-10f},
                0.f);
    q.set_value(quadtree::Trapezium{quadtree::Point{-0.1f, -0.005f}, 1.2f,
                                    0.01f, -1e-10f, 1e-10f},
                0.f);
    q.set_value(quadtree::Trapezium{quadtree::Point{0.995f, -0.1f}, 0.01f, 1.2f,
                                    -1e-10f, 1e-10f},
                0.f);
    q.set_value(quadtree::Trapezium{quadtree::Point{-0.1f, 0.995f}, 1.2f, 0.01f,
                                    -1e-10f, 1e-10f},
                0.f);
    for (int i = 0; i < 1000; ++i) {
      for (auto &it : q.node_iterators())
        if (it->has_child())
          it->uniform(false);
        else
          it->set_value(it->box_size().x_center(), it->box_size().y_center(),
                        (it->up_value() + it->down_value() + it->right_value() +
                         it->left_value()) /
                            4);
      q.set_value(quadtree::Trapezium{quadtree::Point{0.15f, 0.65f}, 0.1f, 0.1f,
                                      -0.5f, 0.5f},
                  12.45f);
      q.set_value(quadtree::Trapezium{quadtree::Point{0.55f, 0.15f}, 0.1f, 0.1f,
                                      -0.5f, 0.5f},
                  12.45f);
      q.set_value(quadtree::Trapezium{quadtree::Point{-0.005f, -0.1f}, 0.01f,
                                      1.2f, -1e-10f, 1e-10f},
                  0.f);
      q.set_value(quadtree::Trapezium{quadtree::Point{-0.1f, -0.005f}, 1.2f,
                                      0.01f, -1e-10f, 1e-10f},
                  0.f);
      q.set_value(quadtree::Trapezium{quadtree::Point{0.995f, -0.1f}, 0.01f,
                                      1.2f, -1e-10f, 1e-10f},
                  0.f);
      q.set_value(quadtree::Trapezium{quadtree::Point{-0.1f, 0.995f}, 1.2f,
                                      0.01f, -1e-10f, 1e-10f},
                  0.f);
    }
    auto end = std::chrono::steady_clock::now();
    std::clog << std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                                       start)
                     .count()
              << "us\n";
    std::clog << q(0.6245, 0.3735) << "\n";
    std::clog << q.at(0.6245, 0.3735).value() << "\n";
    std::clog << q.at(0.6245, 0.3735).down_value() << "\n";
    std::clog << q.at(0.6245, 0.3735).up_value() << "\n";
    std::clog << q.at(0.6245, 0.3735).left_value() << "\n";
    std::clog << q.at(0.6245, 0.3735).right_value() << "\n";
    std::clog << q(0.6245, 0.3725) << "\n";
    std::clog << q(0.6245, 0.3745) << "\n";
    std::clog << q(0.6235, 0.3735) << "\n";
    std::clog << q(0.6255, 0.3735) << "\n";
     return 0;
    for (int i = 0; i < 1000; ++i) {
      for (int j = 0; j < 1000; ++j) {

        try {
          std::cout << q(i * 0.001 + 0.0005, j * 0.001 + 0.0005) << ",\t";
        } catch (const char *str) {
          std::cerr << str << "\n";
        }
      }
      std::cout << "\n";
    }
  }
  // std::cin.ignore();
}
