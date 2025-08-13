#include "Mesh.h"
#include "Renderer.h"
#include "Math/Vector3.h"
namespace bonzai {
	bool Mesh::load(const std::string& filename){
		std::string buffer;
		file::ReadTextFile(filename, buffer);
		std::stringstream stream(buffer);
		stream >> color;
		vec2 point;
		while (stream >> point) {
			points.push_back(point);
		}
		return true;
	}
	/// <summary>
	/// Draws the model by connecting its points with lines using the specified renderer.
	/// </summary>
	/// <param name="renderer">The Renderer object used to draw the model.</param>
	void Mesh::draw(Renderer& renderer, const vec2& position, float rotation, float scale) {
		if (points.size() < 2) return; // need at least 2 points to draw a line
		renderer.setColor(color.r, color.g, color.b);
		//draw through all points
		for (int i=0; i < points.size(); i++) {
			 vec2 p1 = points[i].rotate(math::degToRad(rotation))*scale+position;
			 vec2 p2 = points[(i + 1) % points.size()].rotate(math::degToRad(rotation)) * scale +position; // wrap around to first point
			renderer.drawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}

	/// <summary>
	/// Draws the model using the specified renderer and transformation.
	/// </summary>
	/// <param name="renderer">The renderer used to draw the model.</param>
	/// <param name="transform">The transformation to apply, including position, rotation, and scale.</param>
	void Mesh::draw(Renderer& renderer, const Transform& transform){
		draw(renderer, transform.position, transform.rotation, transform.scale);
	}
	void Mesh::smoothSetColor(vec3 color){
		for (int i = 0; i < 3; i++) {
			this->color[i] = this->color[i] + 0.2f * (-1 * this->color[i] + color[i]);
		}
	}
	/// <summary>
	/// Calculates and updates the radius of the model based on ,
	/// the maximum distance of its points from the origin.
	/// </summary>
	void Mesh::calculateRadius(){
		radius = 0;
		for (auto& point : points) {
			float length = point.length();
			if(length > radius){
				radius = length;
			}
		}

	}

}