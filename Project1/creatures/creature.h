#pragma once

//#include "../logic/game.h"

#define CREAURE_WIDTH 0.8
#define CREAURE_HEIGHT 0.8

#define HEADING_UP 0
#define HEADING_DOWN 2
#define HEADING_LEFT 3
#define HEADING_RIGHT 1

class Region;
class Creature {
protected:
	int m_counterToRemoveSwingAnimation = 0;
	int m_id;
	int m_swingDir;
	int m_regionIndex;

	int m_untilnexttarget;
	int m_wait;
	float m_curtarget_x;
	float m_curtarget_y;
	float m_health;

	void enemyAi();

public:
	bool m_item;
	float x, y;
	float vel_x, vel_y;
	float acc_x, acc_y;
	uint8_t heading : 2;

	Creature(float x, float y, int id, bool item);
	Creature();

	virtual void submitToRenderer(graphics::Renderer *renderer, float renderOffsetX, float renderOffsetY);
	virtual void update();
	virtual void collide(); //Collision check must happen after processing new area
	virtual void hit();

	inline int getId() { return m_id; }

	//#if !STORE_MAP_IN_RAM
	//inline float getListRegionX() {
	//	if (x >= 0) return x / (float)REGION_SIZE + 0.5f;
	//	else return x / (float)REGION_SIZE - 0.5f;
	//}
	//inline float getListRegionY() {
	//	if (y >= 0) return y / (float)REGION_SIZE + 0.5f;
	//	else return y / (float)REGION_SIZE - 0.5f;
	//}
	//#endif

	inline float getHealth() { return m_health; }
	inline float getX() { return x - 0.5f; }
	inline float getY() { return y - 0.5f; }

	inline int getRegionIndex() { return m_regionIndex; }
	
	inline void setX(float n) { x = n + 0.5f; }
	inline void setY(float n) { y = n + 0.5f; }
	inline void setRegionIndex(int i) { m_regionIndex = i; }
	void heal(float amount);
	void heal();
};