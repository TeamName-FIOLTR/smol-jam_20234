#include "gdx_testing.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void GdxTesting::_bind_methods(){
    ClassDB::bind_method(D_METHOD("gdxtesting"), &GdxTesting::gdxtesting);
    ClassDB::bind_method(D_METHOD("get_hello_world"), &GdxTesting::get_hello_world);
}

String GdxTesting::get_hello_world() {
	return String("it works");
}

GdxTesting::GdxTesting(){
    gdxtesting_gdxtesting = String("gdxtesting");
}

GdxTesting::~GdxTesting(){

}

String GdxTesting::gdxtesting(){
    return gdxtesting_gdxtesting;
}
