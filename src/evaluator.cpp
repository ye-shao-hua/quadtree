#include "../include/quadtree/evaluator.h"
#include "../include/quadtree/dynamic_node_list.h"
#include "../include/quadtree/node_iterator.h"
#include "../include/quadtree/node_iterators.h"
#include "../include/quadtree/quadtree.h"
#include "../include/quadtree/quadtree_active_iterators.h"
#include <algorithm>

namespace quadtree {
Evaluator::Evaluator(Quadtree &quadtree) : _quadtree(quadtree) {}
void Evaluator::set_refine_and_coarsen_flag(float refine_percent,
                                            float coarsen_percent) {
  _quadtree.active_node_iterators();
  std::sort(_quadtree._cache_active_node_list->iterators().begin(),
            _quadtree._cache_active_node_list->iterators().end(),
            [](const NodeViewer &first, const NodeViewer &second) {
              return first->curvature() > second->curvature();
            });
  int index = 0;
  for (auto &it : _quadtree.active_node_iterators()) {
    it->refine_flag(false);
    it->coarsen_flag(false);
    if (index < (_quadtree.active_node_iterators().end() -
                 _quadtree.active_node_iterators().begin()) *
                    refine_percent)
      it->refine_flag(true);

    if (static_cast<float>(index) /
            (_quadtree.active_node_iterators().end() -
             _quadtree.active_node_iterators().begin()) >
        1. - coarsen_percent)
      it->coarsen_flag(true);
    ++index;
  }
}
} // namespace quadtree
