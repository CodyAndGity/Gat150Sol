#include "TextureAnimation.h"
namespace bonzai {
	bool TextureAnimation::load(const std::string& filename, class Renderer& renderer) {
		// load json
		bonzai::json::document_t document;
		if (!bonzai::json::load(filename, document)) {
			Logger::Error("Could not load TextureAnimation json {}", filename);
			return false;
		}
		// read texture name
		std::string texture_name;
		JSON_READ(document, texture_name);
		// load texture
		texture = resources().get<Texture>(texture_name, renderer);
		if (!texture) {
			Logger::Error("Could not load texture in Texture Animation {}", texture_name);
		}
		JSON_READ_NAME(document, "columns", columns);
		JSON_READ_NAME(document, "rows", rows);
		JSON_READ_NAME(document, "start_frame", startFrame);
		JSON_READ_NAME(document, "total_frames", totalFrames);
		JSON_READ_NAME(document, "frames_per_second", framesPerSecond);
		JSON_READ_NAME(document, "loop", loop);
		return true;
	}
	vec2 TextureAnimation::getSize() const {
		vec2 size = texture->getSize();
		return { size.x / columns, size.y / rows };
	}
	rect TextureAnimation::getFrameRect(int frame) const
	{
		if (!isValidFrame(frame)) {
			Logger::Warning("Frame is outside bounds {}/{}", frame, totalFrames);
			frame = 0;
		}
		rect frameRect;
		vec2 size = getSize();
		frameRect.w = size.x;
		frameRect.h = size.y;
		frameRect.x = ((startFrame + frame) % columns) * frameRect.w;
		frameRect.y = ((startFrame + frame) / columns) * frameRect.h;
		return frameRect;
	}
}