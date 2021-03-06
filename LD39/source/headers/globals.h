#ifndef GLOBALS_H
#define GLOBALS_H

namespace globals {
	const int SCREEN_WIDTH = 960;
	const int SCREEN_HEIGHT = 640;
}

enum Direction {
	LEFT,
	RIGHT,
	UP,
	DOWN
};

/// <summary>
/// For use in our animated sprite class, not defined in sdl
/// </summary>
struct Vector2 {
	int x;
	int y;
	Vector2() : x(0), y(0) {}
	Vector2(int x, int y) : x(x), y(y) {}
	Vector2 zero() {
		return Vector2(0, 0);
	}
};

#endif // !GLOBALS_H
