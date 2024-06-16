#include "../include/quadtree/quadtree_iterator.h"

namespace quadtree {
QuadtreeIterator::QuadtreeIterator(Quadtree &quadtree, index_type index)
    : _quadtree(quadtree) {
  _calling_stack.push(index);
}
QuadtreeIterator &QuadtreeIterator::operator++() {
  index_type top_index = _calling_stack.top();
  if (top_index < 3) {
    _calling_stack.pop();
    _calling_stack.push(top_index + 1);
    return *this;
  }
  _calling_stack.pop();
  return operator++();
}
} // namespace quadtree
