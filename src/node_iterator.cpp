#include "../include/quadtree/node_iterator.h"
#include "../include/quadtree/node.h"
#include "../include/quadtree/node_viewer.h"

namespace quadtree {

NodeIterator::NodeIterator(const NodeIterator &that)
    : _node(that._node), _index(that._index) {}

NodeIterator::NodeIterator(NodeViewer node[], index_type index)
    : _node(node), _index(index) {}

NodeIterator &NodeIterator::operator=(const NodeIterator &that) {
  _node = that._node;
  _index = that._index;
  return *this;
}

NodeIterator &NodeIterator::operator++() {
  ++_index;
  return *this;
}

NodeIterator NodeIterator::operator++(int) {
  NodeIterator return_value = *this;
  ++_index;
  return return_value;
}

NodeIterator &NodeIterator::operator--() {
  --_index;
  return *this;
}

NodeIterator::index_type
NodeIterator::operator-(const NodeIterator &that) const {
  return _index - that._index;
}

NodeIterator NodeIterator::operator+(int offset) const {
    return {_node, _index + offset};
}

NodeIterator NodeIterator::operator-(int offset) const {
    return operator+(-offset);
}

NodeViewer &NodeIterator::operator*() { return _node[_index]; }

NodeViewer& NodeIterator::operator[](index_type index) {
    return _node[index];
}

bool NodeIterator::operator<(const NodeIterator& that) const {
    return _index < that._index;
}

} // namespace quadtree
