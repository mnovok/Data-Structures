#define _CRT_SECURE_NO_WARNINGS

#include "Player.h"
#include "Menu.h"
#include "Gameplay.h"
#include "Villain.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char** argv) {

	MaximizeOutputWindow(); 

	StartGame();

	RestoreOutputWindow();

	return EXIT_SUCCESS;
}