extends Node3D

@export var elf_anim_hting : AnimationTree
@export var camination_thing : AnimationPlayer
# Called when the node enters the scene tree for the first time.
func _ready():
	#elf_anim_hting.active = true
	#elf_anim_hting["parameters/StateMachine/playback"]
	#elf_anim_hting.travel("sometsta")
	elf_anim_hting["parameters/RTHISONE/seek_request"] = -1.0
	camination_thing.play("CameraAction")
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
