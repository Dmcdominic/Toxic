#pragma once

#include "Grid.hpp"
#include "Scene.hpp"
#include "ModelLoader.hpp"


struct Tree : FgObj {
	// Constructors (inherited)
	using FgObj::FgObj;
  	Tree(Scene *scene, int _id); 

	// Fields
	int id = 0;
	Scene::Drawable tree1 = nullptr;
	Scene::Drawable tree2 = nullptr;
	Scene::Drawable tree3 = nullptr;


	// Methods
	bool can_fg_obj_move_into(FgObj& objBeingMoved, const glm::ivec2& displ) override;

	void on_post_tick() override;
};