#pragma once


struct MKCommand {
	char* name;
	int air_ground; // or not
	int action_key;
	char pad[24]; // mk11 only
	int* directions; // 4 max, close with -1
};