#pragma once
#include "../Core/Types.h"
namespace GF {
	namespace GameEngine {
		struct Vector3D{
			float x = 0, y = 0, z = 0;
			Vector3D() = default;
			Vector3D(const Vector3D&) = default;
			Vector3D(float x, float y, float z);
			Vector3D(float x, float y);
			Vector3D operator-(const Vector3D&rhs);
			Vector3D operator+(const Vector3D&rhs);
			Vector3D operator*(float s);
			bool operator==(const Vector3D&);
			bool operator!=(const Vector3D&);
		};

		struct Size {
			float width = 0, height = 0, depth = 0;
			Size() = default;
			Size(const Size&) = default;
			Size(float w, float h, float d);
			Size(float w, float h);
		};

		struct Box {
			Box() = default;
			Box(const Box&) = default;
			Box(float x, float y, float z, float w, float h, float d);
			Box(float x, float y, float w, float h);
			float x=0, y = 0, z = 0;
			float width = 0, height = 0, depth = 0;
		};

		typedef Vector3D Pos;


		struct InteractEventArgs :public Core::EventArgs {
			Core::MemGuard<Mob> mob;
		};
	}
}