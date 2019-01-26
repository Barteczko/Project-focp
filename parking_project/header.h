#pragma once

class parking
{
public:
	int type, id;
	char license[10];
	float in_t, exit_t, duration;
	void arrival();
	void details();
	void costs();
	void departure();
} x;