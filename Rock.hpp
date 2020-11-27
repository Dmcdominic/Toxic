#pragma once

#include "Grid.hpp"
#include "Scene.hpp"
#include "ModelLoader.hpp"


struct Rock : FgObj {
	// Constructors (inherited)
	using FgObj::FgObj;
  	Rock(Scene *scene); 

	// Methods
	std::optional<AudioManager::AudioClip> get_move_clip() override;
};