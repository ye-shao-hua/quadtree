#include "../include/quadtree/quadtree.h"
#include "../include/quadtree/dynamic_node_list.h"
#include "../include/quadtree/node_iterator.h"
#include "../include/quadtree/quadtree_active_iterators.h"
#include "../include/quadtree/quadtree_iterators.h"

namespace quadtree {
Quadtree::Quadtree(const Rect &box_size)
    : _data(nullptr, box_size), _cache_node_list(nullptr),
      _cache_active_node_list(nullptr) {}
Quadtree::~Quadtree() {
  delete _cache_node_list;
  delete _cache_active_node_list;
}
float Quadtree::operator()(float x, float y) const { return _data(x, y); }
void Quadtree::refine_global(int times) {
  delete _cache_node_list;
  delete _cache_active_node_list;
  _cache_node_list = nullptr;
  _cache_active_node_list = nullptr;
  for (int i = 0; i < times; ++i)
    _data.refine();
}
void Quadtree::execute_refine_and_coarsen() {
  for (auto &it : node_iterators()) {
    it->uncache();
    if (!it->has_child() && it->refine_flag())
      it->refine();
    it->refine_flag(false);
    if (it->has_child()) {
      if (it->child(0)->coarsen_flag() && it->child(1)->coarsen_flag() &&
          it->child(2)->coarsen_flag() && it->child(3)->coarsen_flag()) {
        it->coarsen();
        continue;
      }
      for (int i = 0; i < 4; ++i)
        it->child(i)->coarsen_flag(false);
    }
  }
  delete _cache_node_list;
  delete _cache_active_node_list;
  _cache_node_list = nullptr;
  _cache_active_node_list = nullptr;
}
void Quadtree::set_value(float x, float y, float new_value) {
  if (!_data.include(x, y))
    throw "无效地址\n";
  _data.set_value(x, y, new_value);
}
void Quadtree::set_value(const Trapezium &trapezium, float new_value) {
  if (_data.include(trapezium) || trapezium.include(_data.box_size()))
    _data.set_value(trapezium, new_value);
}
NodeViewer Quadtree::at(float x, float y) { return _data.at(x, y); }
const NodeViewer Quadtree::at(float x, float y) const { return _data.at(x, y); }
QuadtreeIterators Quadtree::node_iterators() { return {*this}; }
QuadtreeActiveIterators Quadtree::active_node_iterators() { return {*this}; }
Quadtree::value_type Quadtree::linear_value(float x, float y) const {
  return _data.at(x, y)->linear_value(x, y);
}

} // namespace quadtree
