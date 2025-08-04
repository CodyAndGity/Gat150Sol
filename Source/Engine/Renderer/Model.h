#pragma once
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Transform.h"
#include <vector>
namespace bonzai {
	class Model {
	public:
		Model() = default;
		Model(const std::vector<vec2>& points, const vec3& color) :
			points(points), 
			color(color) {
			calculateRadius();
		}

		void draw(class Renderer& renderer,const vec2& position,float rotation, float scale);
		void draw(class Renderer& renderer,const Transform& transform);

		float getRadius() const { return radius; }
		vec3 getColor() const{ return color; }
		void setColor(vec3 color) { this->color = color; }
		void smoothSetColor(vec3 color);
	private:
		void calculateRadius();
	private:
		float radius{ 0 };
		std::vector<vec2> points;
		vec3 color{ 1,1,1 };

	};

}