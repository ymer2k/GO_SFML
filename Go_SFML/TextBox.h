#pragma once

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

// Define keys:
#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Textbox {
public:
	Textbox(int size, sf::Color color, bool sel);

	// Make sure font is passed by reference:
	void setFont(sf::Font& fonts);

	void setPosition(sf::Vector2f point);

	// Set char limits:
	void setLimit(bool ToF);

	void setLimit(bool ToF, int lim);

	// Change selected state:
	void setSelected(bool sel);

	std::string getText();

	void drawTo(sf::RenderWindow& window);

	// Function for event loop:
	void typedOn(sf::Event input);
private:
	sf::Text textbox;

	std::ostringstream text;
	bool isSelected;
	bool hasLimit;
	int limit;

	// Delete the last character of the text:
	void deleteLastChar();


	// Get user input:
	void inputLogic(int charTyped);
};