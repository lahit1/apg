#pragma once

namespace RENDERER {

struct Ball {
	Renderable* renderable;
	Ball* next;
};

struct Pool { // basicly a linked list :d, i love giving different names than frequent terms :)
	Ball *start, *end;
	inline void link(Ball* b);
	inline void unlink(Ball* b);
};

void BEGIN(Pool* p);
void RENDER(void);
void END(void);
}
