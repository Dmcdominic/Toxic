.PHONY : all

#n.b. the '-y' sets autoexec scripts to 'on' so that driver expressions will work
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	BLENDER = /Applications/Blender/blender.app/Contents/MacOS/blender -y
else ifeq ($(UNAME_S),Linux)
	BLENDER = ../../blender-2.90.0-linux64/blender -y
else
	BLENDER = blender
endif

EXPORT_MESHES=export-meshes.py
EXPORT_SCENE=export-scene.py

DIST=../dist

all : \
	$(DIST)/toxic-prefabs.pnct \
	$(DIST)/toxic-prefabs.scene \

$(DIST)/toxic-prefabs.pnct : toxic-prefabs.blend $(EXPORT_MESHES)
	blender --background --python $(EXPORT_MESHES) -- '$<':Main '$@'

$(DIST)/toxic-prefabs.scene : toxic-prefabs.blend $(EXPORT_SCENE)
	blender --background --python $(EXPORT_SCENE) -- '$<':Main '$@'
