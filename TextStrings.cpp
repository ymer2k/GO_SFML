#include "TextStrings.h"
#include <SFML/Graphics.hpp>



TextStrings::TextStrings(FontHolder& font, const std::string& string, sf::Color color, int textSize, sf::Uint32 style, sf::Vector2f pos):
	m_font(font)
	, m_textString(string)
	, m_color(color)
	, m_textSize(textSize)
	, m_style(style)
	, m_position(pos)
{
	m_text.setFont(font.get(FontHolder::FontID::Ariel));
	m_text.setString(m_textString);
	m_text.setFillColor(m_color);
	m_text.setCharacterSize(m_textSize);
	m_text.setStyle(m_style);
	m_text.setPosition(m_position);
}

sf::Text TextStrings::getText()
{
	return m_text;
}
