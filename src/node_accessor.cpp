#include "../include/quadtree/node_accessor.h"
#include "../include/quadtree/node.h"
#include "../include/quadtree/node_pool.h"
#include "../include/quadtree/node_viewer.h"

namespace quadtree {
NodeAccessor::NodeAccessor() : NodeAccessor(nullptr) {}
NodeAccessor::NodeAccessor(Node *node) : NodeViewer(node) {}
NodeAccessor::NodeAccessor(NodeAccessor &&that) : NodeViewer(that._node) {
  if (that.accessible()) {
    that._node = nullptr;
  }
}
NodeAccessor &NodeAccessor::operator=(NodeAccessor &&that) {
  this->~NodeAccessor();
  if (that.accessible()) {
    _node = that._node;
    that._node = nullptr;
  }
  return *this;
}
NodeAccessor::~NodeAccessor() {
  if (accessible()) {
    for (int i = 0; i < 4; ++i)
      _node->_child[i].~NodeAccessor();
    _node_pool.deallocate(_node);
    _node = nullptr;
  }
}
const Node *NodeAccessor::operator->() const { return _node; }
Node *NodeAccessor::operator->() { return _node; }
const Node &NodeAccessor::operator*() const { return *_node; }
Node &NodeAccessor::operator*() { return *_node; }
bool NodeAccessor::accessible() const { return !unaccessible(); }
bool NodeAccessor::unaccessible() const { return _node == nullptr; }
NodeViewer NodeAccessor::view() { return _node; }
const NodeViewer NodeAccessor::view() const { return _node; }



} // namespace quadtree
