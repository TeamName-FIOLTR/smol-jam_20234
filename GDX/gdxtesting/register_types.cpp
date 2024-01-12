#include "register_types.h"
#include "gdx_testing.h"
#include "audio_effect_bit_crush.h"
#include "audio_effect_bit_crush_instance.h"
#include "audio_effect_lufs_meter.h"
#include "audio_effect_lufs_meter_instance.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

void initialize_gdx_testing_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }

    ClassDB::register_class<GdxTesting>();
    ClassDB::register_class<AudioEffectBitCrush>();
    ClassDB::register_class<AudioEffectBitCrushInstance>();
    ClassDB::register_class<AudioEffectLufsMeter>();
    ClassDB::register_class<AudioEffectLufsMeterInstance>();
}

void uninitialize_gdx_testing_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
}


extern "C" {
// Initialization.
GDExtensionBool GDE_EXPORT gdx_testing_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
    godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

    init_obj.register_initializer(initialize_gdx_testing_module);
    init_obj.register_terminator(uninitialize_gdx_testing_module);
    init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

    return init_obj.init();
    }
}