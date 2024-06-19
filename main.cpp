#include "include/quadtree/evaluator.h"
#include "include/quadtree/node.h"
#include "include/quadtree/node_iterator.h"
#include "include/quadtree/node_pool.h"
#include "include/quadtree/quadtree.h"
#include "include/quadtree/quadtree_active_iterators.h"
#include "include/quadtree/rect.h"
#include "include/quadtree/trapezium.h"
#include <chrono>
#include <iostream>

int main() {
  {
    quadtree::Quadtree q{quadtree::Rect{0.f, 1.f, 0.f, 1.f}};

    q.refine_global(4);
    std::clog << "begin\n";

    int nn = 1;

    auto start = std::chrono::steady_clock::now();
    for (int n = 0; n < 10; ++n) {
      std::clog << "refine\n";
      q.execute_refine_and_coarsen();
      for (int i = 0; i < 10000; ++i) {
        for (auto &it : q.active_node_iterators())
          it->value((it->up_value() + it->down_value() + it->right_value() +
                     it->left_value()) /
                    4);
        q.set_value(quadtree::Trapezium{quadtree::Point{0.15f, 0.65f}, 0.6f,
                                        0.01f, -0.5f, 0.5f},
                    1.f);
        q.set_value(quadtree::Trapezium{quadtree::Point{0.15f, 0.55f}, 0.6f,
                                        0.01f, -0.5f, 0.5f},
                    0.f);
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
      std::clog << q.linear_value(0.6245, 0.3735) << "\n";
      quadtree::Evaluator e{q};
      e.set_refine_and_coarsen_flag(0.2, 0.5);
      //  q.refine_global();
    }
    auto end = std::chrono::steady_clock::now();
    std::clog << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                       start)
                         .count() /
                     1000.
              << "s\n";
    /*
    std::clog << q(0.6245, 0.3735) << "\n";
    std::clog << q.at(0.6245, 0.3735)->value() << "\n";
    std::clog << q.at(0.6245, 0.3735)->down_value() << "\n";
    std::clog << q.at(0.6245, 0.3735)->up_value() << "\n";
    std::clog << q.at(0.6245, 0.3735)->left_value() << "\n";
    std::clog << q.at(0.6245, 0.3735)->right_value() << "\n";
    std::clog << q(0.6245, 0.3725) << "\n";
    std::clog << q(0.6245, 0.3745) << "\n";
    std::clog << q(0.6235, 0.3735) << "\n";
    std::clog << q(0.6255, 0.3735) << "\n";
    */
    /*
    for(auto & it : q.active_node_iterators()) {
        it->value();
    }
    */
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
