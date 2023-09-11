#pragma once

//GAME BOARD SIZE
const float WIDTH = 800.f;
const float HIGHET = 500.f;

//AMOUNT OF SHAPES
const float RADIUS = 15.f; //if need to change the size of the board -> change this parameter
const int AMOUNTCOLORS = 6;

enum class Difficult
{
	Easy,
	Medium,
	Hard,
};

enum class Colors
{
	Blue, 
	Red, 
	Yellow, 
	Green, 
	Cyan, 
	Magenta,
};