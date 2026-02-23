#include <iostream>
#include <fstream>
using namespace std;

void print()
{
	cout << ifstream("MainMenu.txt").rdbuf();
}

int main()
{
	print();
}