namespace my_namespace {

template <typename T, typename U> class my_template_class {
  public:
    T a;
    U b;
    T my_template_func(U u) { return a; }
};

class my_abc {
  public:
    virtual void my_virtual_func(int param) = 0;
};

struct my_struct {
    int x;
    int y;
    my_struct(int x, int y) : x(x), y(y) {}
};

union my_union {
    my_struct s;
    int i;
};

enum my_enum { A, B, C };

typedef my_template_class<int, my_struct> my_typedef;

bool my_func(my_typedef a, my_enum b);

} // namespace my_namespace