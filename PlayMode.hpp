#include "Mode.hpp"

#include "Scene.hpp"
#include "GridLoader.hpp"
#include "CloudCover.hpp"
#include "Grid.hpp"
#include "ModelLoader.hpp"
//#include "game_menu.hpp"
#include "level_sequence.hpp"

#include "PngHelper.hpp"
#include "Menu.hpp"

#include <glm/glm.hpp>
#include <queue>


struct PlayMode : Mode {
	PlayMode(uint8_t _completed_level = 0, int _environment_score = 100);
	virtual ~PlayMode();

	//functions called by main loop:
	virtual bool handle_event(SDL_Event const &, glm::uvec2 const &window_size) override;
	virtual void update(float elapsed) override;
	virtual void draw(glm::uvec2 const &drawable_size) override;


//	void update_congrats_items(std::vector< MenuMode::Item > &items);
//	void update_pass_items(std::vector< MenuMode::Item > &items);

	void load_level(uint8_t level_index);
	void reset_level();
	bool undo_move();
	void clear_undo_stack();

	bool loading_level = false;
	bool load_main_menu = false;
	bool load_credits = false;
	int level_to_load = 0;


	//----- game state -----

	static bool DEBUG;
	static uint8_t current_level;
	static uint8_t completed_level;
	static bool is_Overworld() {
		return current_level == 0;
	}

	static glm::ivec2 last_node_pos;

	ModelLoader loader; 

	//input tracking:
	std::queue<Input> input_q;

	//local copy of the game scene (so code can change it during gameplay):
	Scene scene;
	Scene cloud_scene; 

	// Active camera
	Scene::Camera *active_camera = nullptr;
	Scene::Camera *cloud_camera = nullptr;

	//Cloud Cover for loading
	CloudCover *cloud_cover = nullptr;

	const float min_cam_height = 7.5f;
	const float max_cam_height = 11.0f;
	const float cam_height_OW = 10.0f;
	const size_t min_grid_width = 4;
	const size_t max_grid_width = 15;

	glm::vec3 smooth_player_target_for_cam = glm::vec3();
	glm::vec2 base_cam_offset_from_player = glm::vec2(-0.2f, -2.0f);
	glm::vec3 camera_offset_from_player = glm::vec3();
	glm::vec3 randomized_offset_range = glm::vec3(1.9f, 1.9f, 2.5f);

	virtual void update_camera(float elapsed);
	virtual void reset_cam_offset_from_player();
	int environment_score;
	void check_level_completion();
	bool level_completion = false;

	void save_game();

	PngHelper *pngHelper = new PngHelper();

	// Menu
	Menu *menu = nullptr;
};
