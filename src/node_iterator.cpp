#include "../include/quadtree/node_iterator.h"
#include "../include/quadtree/node.h"
#include "../include/quadtree/node_viewer.h"

namespace quadtree {
NodeIterator::NodeIterator(const NodeIterator &that)
    : _node(that._node), _index(that._index) {}
NodeIterator::NodeIterator(NodeViewer node[], index_type index)
    : _node(node), _index(index) {}
NodeIterator &NodeIterator::operator++() {
  ++_index;
  return *this;
}
NodeIterator NodeIterator::operator++(int) {
  NodeIterator return_value = *this;
  ++_index;
  return return_value;
}
NodeViewer &NodeIterator::operator*() { return _node[_index]; }
} // namespace quadtree
