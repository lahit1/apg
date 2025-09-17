#include <ape/g3d/animation.hxx>

void Animation::act(float dt) {
	if(!pmode) return;
	current_time += dt;
	if(current_time > duration) {
		switch(amode) {
			case AMODE_ONCE:
				current_time = duration;
				pmode = false;
				break;
			case AMODE_REPEAT:
				current_time = 0;
		}
		
	}
}
