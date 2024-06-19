namespace quadtree {

class Quadtree;

class Evaluator {
public:
  Evaluator(Quadtree &quadtree);
  void set_refine_and_coarsen_flag(float refine_percent = 0.2f,
                                   float coarsen_percent = 0.5f);

private:
  Quadtree &_quadtree;
};
} // namespace quadtree
