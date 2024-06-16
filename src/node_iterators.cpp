#include "../include/quadtree/node_iterators.h"
#include "../include/quadtree/node_iterator.h"
#include "../include/quadtree/node_viewer.h"
namespace quadtree {

NodeIterators::NodeIterators(NodeViewer node[], index_type size)
    : _node(node), _size(size) {}
NodeIterators::NodeIterators(const NodeIterators &that)
    : _node(that._node), _size(that._size) {}
NodeIterator NodeIterators::begin() { return NodeIterator{_node, 0}; }
NodeIterator NodeIterators::end() { return NodeIterator{_node, _size}; }
const NodeIterator NodeIterators::begin() const {
  return NodeIterator{_node, 0};
}
const NodeIterator NodeIterators::end() const {
  return NodeIterator{_node, _size};
}

} // namespace quadtree
