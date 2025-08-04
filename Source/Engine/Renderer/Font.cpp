#include "Font.h"
#include "SDL3_ttf/SDL_ttf.h"
#include <iostream>
namespace bonzai {
	/// <summary>
	/// Destroys the Font object and releases associated resources.
	/// </summary>
	Font::~Font() {
		if (ttfFont != nullptr) {
			TTF_CloseFont(ttfFont);
		}
	}
	/// <summary>
	/// Loads a font from a file with the specified name and size.
	/// </summary>
	/// <param name="name">The path or name of the font file to load.</param>
	/// <param name="fontSize">The desired size of the font.</param>
	/// <returns>True if the font was loaded successfully; false otherwise.</returns>
	bool Font::load(const std::string& name, float fontSize) {
		ttfFont = TTF_OpenFont(name.c_str(), fontSize);
		if (ttfFont == nullptr) {
			std::cerr << "Could not load font: " << name << std::endl;
			return false;
		}

		return true;
	}
}