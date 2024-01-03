#ifndef GDX_TESTING_H
#define GDX_TESTING_H

#include <godot_cpp/classes/node.hpp>

namespace godot{
    class GdxTesting : public Node{
        GDCLASS(GdxTesting, Node)

protected:
    static void _bind_methods();

private:
    String gdxtesting_gdxtesting;

public:
    GdxTesting();
    ~GdxTesting();

    String gdxtesting();

    };
};

#endif