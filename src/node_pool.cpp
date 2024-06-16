#include "../include/quadtree/node_pool.h"
#include "../include/quadtree/node.h"
#include "../include/quadtree/rect.h"

namespace quadtree {
NodeBlock::NodeBlock(unsigned int size)
    : _data(new Node[size]{}), _index(0), _delete_num(0), _size(size),
      _next(nullptr) {}
NodeAccessor NodeBlock::allocate(Node* father, const Rect &box_size, float value) {
  if (_index >= _size) {
    if (_next == nullptr) {
      _next = new NodeBlock(4 * _size);
    }
    return _next->allocate(father, box_size, value);
  }
  _data[_index]._father = father;
  _data[_index]._box_size = box_size;
  _data[_index].value(value);
  return _data + _index++;
}
void NodeBlock::deallocate(Node *node) {
  if (node < _data || node > &_data[_size])
    return _next->deallocate(node);
  if (_index == 0) {
    throw "清错了\n";
  }
  ++_delete_num;
  if (_delete_num == _size) {
    _index = 0;
    _delete_num = 0;
  }
}

NodePool::NodePool() : _node_block(64) {}
NodeAccessor NodePool::allocate(Node* father, const Rect &box_size, float value) {
  return _node_block.allocate(father, box_size, value);
}
void NodePool::deallocate(Node *node) { _node_block.deallocate(node); }
NodePool _node_pool;
} // namespace quadtree
