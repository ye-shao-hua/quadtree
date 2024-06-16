#include "../include/quadtree/dynamic_node_list.h"
#include "../include/quadtree/node_iterators.h"
#include "../include/quadtree/node_viewer.h"

namespace quadtree {
DynamicNodeList::DynamicNodeList()
    : _nodes(new NodeViewer[8]), _size(0), _capacity(8) {}
DynamicNodeList::~DynamicNodeList() {
    delete []_nodes;
}
void DynamicNodeList::push_back(NodeViewer node) {
  if (_size == _capacity) {
    index_type new_capacity = _capacity * 1.5f;
    NodeViewer *new_nodes = new NodeViewer[new_capacity];
    for (int i = 0; i < _capacity; ++i)
      new_nodes[i] = _nodes[i];
    delete[] _nodes;
    _nodes = new_nodes;
    _capacity = new_capacity;
  }
  _nodes[_size++] = node.data();
}
bool DynamicNodeList::empty() const { return _size == 0; }
DynamicNodeList::index_type DynamicNodeList::size() const { return _size; }
DynamicNodeList::index_type DynamicNodeList::capacity() const {
  return _capacity;
}
NodeIterators DynamicNodeList::iterators() { return {_nodes, _size}; }
} // namespace quadtree
