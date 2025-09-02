#pragma once
namespace bonzai {
	class Texture;
	class TextureAnimation : public Resource {
	public:
		TextureAnimation() = default;
		~TextureAnimation() = default;
		bool load(const std::string& filename, class Renderer& renderer);
		vec2 getSize() const;
		rect getFrameRect(int frame) const;
		int getTotalFrames() const { return totalFrames; }
		float getFPS() const { return framesPerSecond; }
		bool isValidFrame(int frame) const { return frame >= 0 && frame < totalFrames; }
		bool isLooping() const { return loop; }
		res_t<Texture> GetTexture() { return texture; }
	private:
		int columns = 0;
		int rows = 0;
		int startFrame = 0;
		int totalFrames = 0;
		float framesPerSecond = 0;
		bool loop = true;
		res_t<Texture> texture;
	};

}