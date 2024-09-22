#include <iostream>
#include "Menu.h"


int main() {
	setlocale(LC_CTYPE, "Spanish"); //Define el español como lenguaje del programa, permitiendo leer letras tildadas, "ñ", "¿" y demás
	Menu* menu = new Menu();

	menu->menuPrincipal();
	
	delete menu;
	return 0;
}

/*
Recursos:

https://en.cppreference.com/w/cpp/container/list

https://en.cppreference.com/w/cpp/container/deque

https://en.cppreference.com/w/cpp/container/map


*/