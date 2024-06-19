#include "../include/quadtree/quadtree_iterators.h"
#include "../include/quadtree/dynamic_node_list.h"
#include "../include/quadtree/node_iterator.h"
#include "../include/quadtree/node_iterators.h"
#include "../include/quadtree/quadtree.h"

namespace quadtree {
QuadtreeIterators::QuadtreeIterators(Quadtree &quadtree) : _quadtree(quadtree) {
  if (quadtree._cache_node_list)
    return;
  quadtree._cache_node_list = new DynamicNodeList;
  quadtree._cache_active_node_list = new DynamicNodeList;
  _emplace(&quadtree._data);
}
NodeIterator QuadtreeIterators::begin() {
  return _quadtree._cache_node_list->iterators().begin();
}
NodeIterator QuadtreeIterators::end() {
  return _quadtree._cache_node_list->iterators().end();
}
void QuadtreeIterators::_emplace(NodeViewer node) {
  _quadtree._cache_node_list->push_back(node);
  if (node->has_child())
    for (NodeViewer &it : node->child_iterators())
      _emplace(it);
  else
    _quadtree._cache_active_node_list->push_back(node);
}
} // namespace quadtree
