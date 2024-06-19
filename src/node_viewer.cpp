#include "../include/quadtree/node_viewer.h"
#include "../include/quadtree/node.h"
#include "../include/quadtree/node_accessor.h"

namespace quadtree {
NodeViewer::NodeViewer() : _node(nullptr) {}
NodeViewer::NodeViewer(const Node *node) : _node(const_cast<Node *>(node)) {}
NodeViewer::NodeViewer(const NodeViewer &that) : _node(that._node) {}
NodeViewer::NodeViewer(NodeViewer &&that) : _node(that._node) {
  that._node = nullptr;
}
NodeViewer &NodeViewer::operator=(const NodeViewer &that) {
  _node = that._node;
  return *this;
}
NodeViewer &NodeViewer::operator=(NodeViewer &&that) {
  _node = that._node;
  that._node = nullptr;
  return *this;
}
const Node *NodeViewer::operator->() const { return _node; }
Node *NodeViewer::operator->() { return _node; }
bool NodeViewer::viewable() const { return !unviewable(); }
bool NodeViewer::unviewable() const { return _node == nullptr; }
// Node *NodeViewer::data() { return _node; }
bool NodeViewer::operator==(const NodeViewer that) const {
  return _node == that._node;
}
bool NodeViewer::operator!=(const NodeViewer that) const {
    return !(_node != that._node);
}
} // namespace quadtree
