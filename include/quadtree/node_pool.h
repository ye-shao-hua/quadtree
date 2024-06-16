#pragma once

namespace quadtree {

class Node;
class Rect;
class NodeAccessor;
class NodeBlock {
public:
  NodeBlock(unsigned int size);
  NodeAccessor allocate(Node *father, const Rect &box_size,
                        float value = 0.f);
  void deallocate(Node *node);

private:
  Node *_data;
  int _index;
  int _delete_num;
  int _size;
  NodeBlock *_next;
};

class NodePool {
public:
  NodePool();
  NodeAccessor allocate(Node* father, const Rect &box_size, float value = 0.f);
  void deallocate(Node *node);

private:
  NodeBlock _node_block;
};

extern NodePool _node_pool;

} // namespace quadtree
