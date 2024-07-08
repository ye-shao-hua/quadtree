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
#include <cmath>

int main() {
  {
    quadtree::Quadtree q{quadtree::Rect{-0.f, 1.f, 0.f, 1.f}};
    q.refine_global(4);
    std::clog << "begin\n";

    int nn = 1;
    auto start = std::chrono::steady_clock::now();
    for (int n = 0; n < 5; ++n) {
      std::clog << "refine\n";
      q.execute_refine_and_coarsen();
      for (int i = 0; i < 100; ++i) {
        for (auto &it : q.active_node_iterators()){
            double h1,h2;//水平方向的左段，右段，以及二阶导。
            h1=(it->box_size().center().x())-(it->left()->box_size().center().x());
            h2=(it->right()->box_size().center().x())-(it->box_size().center().x());
            double v1,v2;
            v1=(it->box_size().center().y())-(it->down()->box_size().center().y());
            v2=(it->up()->box_size().center().y())-(it->box_size().center().y());
            if(h1==0||h2==0||v1==0||v2==0){
                //it->value(99);
                it->value((it->up_value() + it->down_value() + it->right_value() +
                         it->left_value()) /
                        4);
            }else{
                it->value(
                            (
                                (h2+h1)*(h1*it->right_value()+h2*it->left_value())*std::pow(v1,2)*std::pow(v2,2)
                                +std::pow(h1,2)*std::pow(h2,2)*(v1*it->up_value()+v2*it->down_value())*(v2+v1)
                            )/
                            (
                                std::pow(h1+h2,2)*std::pow(v1,2)*std::pow(v2,2)+std::pow(h1,2)*std::pow(h2,2)*std::pow(v1+v2,2)
                            )
                        );
            }
            
        /*
          it->value((it->up_value() + it->down_value() + it->right_value() +
                     it->left_value()) /
                    4);
        */
        }

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
      e.set_refine_and_coarsen_flag(0.5, 0.5);
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
