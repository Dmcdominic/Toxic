#pragma once

#include <SDL.h>
#include <glm/glm.hpp>

#include <memory>

struct Mode : std::enable_shared_from_this< Mode > {
	virtual ~Mode() { }

	//handle_event is called when new mouse or keyboard events are received:
	// (note that this might be many times per frame or never)
	//The function should return 'true' if it handled the event.
	virtual bool handle_event(SDL_Event const &, glm::uvec2 const &window_size) { return false; }

	//update is called at the start of a new frame, after events are handled:
	// 'elapsed' is time in seconds since the last call to 'update'
	virtual void update(float elapsed) { }

	//draw is called after update:
	virtual void draw(glm::uvec2 const &drawable_size) = 0;

    virtual void on_quit(){}

	//Mode::current is the Mode to which events are dispatched.
	// use 'set_current' to change the current Mode (e.g., to switch to a menu)
	static std::shared_ptr< Mode > current;
    static std::shared_ptr< Mode > menu;
    static std::shared_ptr< Mode > play;
    static void set_current(std::shared_ptr< Mode > const &);
    static void set_menu(std::shared_ptr< Mode > const &);
    static void set_play(std::shared_ptr< Mode > const &);
    static void switch_to_menu();
    static void switch_to_play();

	//Set this bool to quit if you want the main loop to quit after this frame.
	bool quit = false;
};

