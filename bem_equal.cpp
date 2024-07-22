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
    double x,y;
    x=0.68+0.6125;
    y=6.9395-0.001;
    quadtree::Quadtree q{quadtree::Rect{-0.6125f, 0.68f, 0.001f, 2.f}};
    q.refine_global(5);
    std::clog << "begin\n";

    int nn = 1;
    auto start = std::chrono::steady_clock::now();
    for (int n = 0; n < 4; ++n) {
      std::clog << "refine\n";
      //q.execute_refine_and_coarsen();
      q.refine_global(1);
      for (int i = 0; i < 1; ++i) {
          
        for (auto &it : q.active_node_iterators()){
            /*
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
            */
        
          it->value((it->up_value() + it->down_value() + it->right_value() +
                     it->left_value()) /
                    4);
        
        }

        q.set_value(quadtree::Trapezium{quadtree::Point{-0.01792f, 0.3705f}, 0.03584f,
                                        0.096f, -1./10.4822f, 1./10.4822f},
                    1.f);
        
        q.set_value(quadtree::Trapezium{quadtree::Point{0.04958f, 0.3705f}, 0.03584f,
                                        0.096f, -1./10.4822f, 1./10.4822f},
                    0.f);
        q.set_value(quadtree::Trapezium{quadtree::Point{-0.10792f, 0.3705f}, 0.03584f,
                                        0.096f, -1./10.4822f, 1./10.4822f},
                    0.f);
        q.set_value(quadtree::Trapezium{quadtree::Point{0.13f, 0.3705f}, 0.03584f,
                                        0.096f, -1./10.4822f, 1./10.4822f},
                    0.f);
        
        q.set_value(quadtree::Trapezium{quadtree::Point{-0.6125f,0.002}, x,
                                        0.01f, -1e-10f, 1e-10f},
                    0.f);
        q.set_value(quadtree::Trapezium{quadtree::Point{-0.6125f, 2.f}, x,
                                        0.01f, -1e-10f, 1e-10f},
                    0.f);
        q.set_value(quadtree::Trapezium{quadtree::Point{-0.6125f, 0.002f}, 0.01f,
                                        2.f, -1e-10f, 1e-10f},
                    0.f);
        q.set_value(quadtree::Trapezium{quadtree::Point{0.68f, 0.002f}, 0.01f,
                                        2.f, -1e-10f, 1e-10f},
                    0.f);
      }
      std::clog << q.linear_value(0.6245, 0.3735) << "\n";
      quadtree::Evaluator e{q};
      e.set_refine_and_coarsen_flag(0.5, 0.3);
      //  q.refine_global();
    }
    auto end = std::chrono::steady_clock::now();
    std::clog << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                       start)
                         .count() /
                     1000.
              << "s\n";
    //输出
    double dx,dy;
    dx=(x)/2000;
    dy=(2.)/2000;
    for(auto i=0;i<2000;++i){
        for(auto j=0;j<2000;++j){
            std::cout<<q(-0.6125+dx*i,0.001+dy*j)<<",";
        }
        std::cout<<"\n";
    }
    std::cout<<x<<" "<<y<<"\n";
    //计算
    double ddy=0.096;
    double ddx=0.05;
    double dddy=ddy/100;
    for(auto i=0;i<100;++i){
        
    }
    }
}
