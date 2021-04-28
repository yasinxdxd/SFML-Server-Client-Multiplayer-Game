#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

struct Entity
{
	Entity(std::string name) { this->name = name; }
	virtual ~Entity() { }

	virtual void draw(sf::RenderWindow& window) = 0;

	sf::Sprite m_sprite;
	sf::Texture m_texture;

	sf::Vector2f pos;
	sf::Vector2f speed;
	sf::Vector2f size;
	std::string name;

};

#endif//ENTITY_H
