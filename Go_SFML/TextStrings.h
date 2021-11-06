#pragma once
#include "FontHolder.h"

class TextStrings
{
public:
	TextStrings(FontHolder& font, const std::string& string, sf::Color color, int textSize, sf::Uint32 style, sf::Vector2f pos);
	sf::Text getText();

private:
	sf::Text m_text;
	FontHolder & m_font;
	std::string m_textString;
	sf::Color m_color;
	int m_textSize;
	sf::Uint32 m_style;
	sf::Vector2f m_position;

	std::string m_newText;

};

