#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "Scene.hpp"
#include "Input.hpp"


// Forward declarations
struct Grid;
struct Cell;
struct BgTile;
struct FgObj;
struct SkyObj;


// The current grid
extern Grid* current_grid;


/* A grid of cells. */
struct Grid {
	// Fields
	size_t width = 0;
	size_t height = 0;
	std::vector<std::vector<Cell>> cells;

	// Constructor
	Grid(size_t _width, size_t _height);
	// Destructor
	~Grid();

	// Methods
	bool is_valid_pos(glm::ivec2 _pos);
	bool on_input(const Input& input);
};



/* A Cell is a single square in the puzzle grid.
 * It contains its position in the grid, 1 bgTile, and 1 fgObj.
 */
struct Cell {
	// Fields
	glm::ivec2 pos = glm::ivec2();
	BgTile* bgTile = nullptr;
	FgObj* fgObj = nullptr;
	SkyObj* skyObj = nullptr;

	// Constructor
	Cell(glm::ivec2 _pos);
	// Destructor
	~Cell();

	// Methods
	void set_bg_tile(BgTile* _bgTile);
	void set_fg_obj(FgObj* _fgObj);
	void set_sky_obj(SkyObj* _skyObj);

	bool can_fg_obj_move_into(FgObj& objBeingMoved, const glm::ivec2 &displ);
	void when_fg_obj_moved_into(FgObj& objBeingMoved, const glm::ivec2& displ);

	bool can_sky_obj_move_into(const SkyObj& objBeingMoved, const glm::ivec2& displ);
	void when_sky_obj_moved_into(SkyObj& objBeingMoved, const glm::ivec2& displ);

	bool on_input(const Input &input);
};



/* Cell Items (parent class of BgTile, FgObj, SkyObj, etc.) */
struct CellItem {
	// Fields
    Scene::Drawable* drawable = nullptr;
	Cell* cell = nullptr;

	// Constructors
	CellItem(Scene::Drawable* _drawable) : drawable(_drawable) {};
	CellItem(Scene::Drawable* _drawable, Cell* _cell) : drawable(_drawable), cell(_cell) {};

	// Pure virtual methods
	virtual bool try_to_move_by(const glm::ivec2& displ) = 0;

	virtual bool can_fg_obj_move_into(FgObj& objBeingMoved, const glm::ivec2& displ) = 0;
	virtual void when_fg_obj_moved_into(FgObj& objBeingMoved, const glm::ivec2& displ) = 0;

	virtual bool can_sky_obj_move_into(const SkyObj& objBeingMoved, const glm::ivec2& displ) = 0;
	virtual void when_sky_obj_moved_into(SkyObj& objBeingMoved, const glm::ivec2& displ) = 0;

	virtual bool on_input(const Input& input) = 0;
};



/* Background Tiles */
struct BgTile : CellItem {
	// Constructors (inherited)
	using CellItem::CellItem;
	// Destructor
	virtual ~BgTile() {};

	// Methods
	bool try_to_move_by(const glm::ivec2& displ) override;

	virtual bool can_fg_obj_move_into(FgObj& objBeingMoved, const glm::ivec2& displ) override;
	virtual void when_fg_obj_moved_into(FgObj& objBeingMoved, const glm::ivec2& displ) override;

	virtual bool can_sky_obj_move_into(const SkyObj& objBeingMoved, const glm::ivec2& displ) override;
	virtual void when_sky_obj_moved_into(SkyObj& objBeingMoved, const glm::ivec2& displ) override;

	virtual bool on_input(const Input& input) override;
};



/* Foreground Objects */
struct FgObj : CellItem {
	// Constructors (inherited)
	using CellItem::CellItem;
	// Destructor
	virtual ~FgObj() {};

	// Methods
	bool try_to_move_by(const glm::ivec2& displ) override;

	virtual bool can_fg_obj_move_into(FgObj& objBeingMoved, const glm::ivec2& displ) override;
	virtual void when_fg_obj_moved_into(FgObj& objBeingMoved, const glm::ivec2& displ) override;

	virtual bool can_sky_obj_move_into(const SkyObj& objBeingMoved, const glm::ivec2& displ) override;
	virtual void when_sky_obj_moved_into(SkyObj& objBeingMoved, const glm::ivec2& displ) override;

	virtual bool on_input(const Input& input) override;
};



/* Sky Objects */
struct SkyObj : CellItem {
	// Constructors (inherited)
	using CellItem::CellItem;
	// Destructor
	virtual ~SkyObj() {};

	// Methods
	bool try_to_move_by(const glm::ivec2& displ) override;

	virtual bool can_fg_obj_move_into(FgObj& objBeingMoved, const glm::ivec2& displ) override;
	virtual void when_fg_obj_moved_into(FgObj& objBeingMoved, const glm::ivec2& displ) override;

	virtual bool can_sky_obj_move_into(const SkyObj& objBeingMoved, const glm::ivec2& displ) override;
	virtual void when_sky_obj_moved_into(SkyObj& objBeingMoved, const glm::ivec2& displ) override;

	virtual bool on_input(const Input& input) override;
};
