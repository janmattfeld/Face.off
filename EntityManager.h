#pragma once

#include <vector>
#include <queue>
#include <memory>
#include <SFML/Graphics.hpp>

class Entity;

typedef std::unique_ptr<Entity> EntityPtr;
typedef std::vector<EntityPtr> EntityPtrList;
typedef std::queue<EntityPtr> EntityPtrQueue;


class EntityManager {
public:
	EntityManager();
	//...
	void add(Entity* entity);
	void update(int frame_time);
	void render(sf::RenderTarget* target);
	void renderFront(sf::RenderTarget* target);
	void renderBack(sf::RenderTarget* target);
	void screenShake(float mag, int time);

	EntityPtrList* getEntities();
	sf::Font* getFont();

	void displayScrollingMessage(std::string string, int time);
private:
	sf::RenderTexture background_;
	sf::Font font_;
	sf::View view_;

	bool is_scrolling_;
	int scroll_timer_;
	int scroll_duration_;
	sf::Text scroll_text_;

	bool in_shake_;
	float shake_magnitude_;
	int shake_length_;
	int shake_timer_;

	EntityPtrQueue newent_q_;
	EntityPtrList entities_;

	std::vector<sf::Text> render_fronts_;
};