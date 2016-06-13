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

		struct Vector3Di {
			int x = 0, y = 0, z = 0;
			Vector3Di() = default;
			Vector3Di(const Vector3Di&) = default;
			Vector3Di(int x, int y, int z);
			Vector3Di(int x, int y);
			Vector3Di operator-(const Vector3Di&rhs);
			Vector3Di operator+(const Vector3Di&rhs);
			Vector3Di operator*(int s);
			bool operator==(const Vector3Di&);
			bool operator!=(const Vector3Di&);
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
			Box(const Box& rhs);
			Box(Vector3D, Size);
			Box(float x, float y, float z, float w, float h, float d);
			Box(float x, float y, float w, float h);
			float x=0, y = 0, z = 0;
			float width = 0, height = 0, depth = 0;
		};

		typedef Vector3D Pos;
		typedef Vector3Di Posi;

		class Mob;
		struct InteractEventArgs :public Core::EventArgs {
			Core::shared_ptr<Mob> mob;
		};

		typedef std::runtime_error GameEngineError;

		enum RTState {
			Started,
			Stoped,
			Paused,
			Frozen,
		};

		enum MobState {
			Alive,
			Dead,
		};

		enum MobGroup {
			Hostile,
			Neutral,
			Friendly,
		};
	}
}