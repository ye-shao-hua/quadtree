
#include "../include/quadtree/quadtree_active_iterators.h"
#include "../include/quadtree/dynamic_node_list.h"
#include "../include/quadtree/node_iterator.h"
#include "../include/quadtree/node_iterators.h"
#include "../include/quadtree/quadtree.h"

namespace quadtree {
NodeIterator QuadtreeActiveIterators::begin() {
  return _quadtree._cache_active_node_list->iterators().begin();
}
NodeIterator QuadtreeActiveIterators::end() {
  return _quadtree._cache_active_node_list->iterators().end();
}
} // namespace quadtree
