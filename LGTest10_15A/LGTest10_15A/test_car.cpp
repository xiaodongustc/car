#include "car.h"
#include <iostream>
using namespace std;

int main()
{
	vector<Car> vec;
	stack<vector<Print>> sta;
	Import(vec);
	Process(vec,sta);
	Show(sta);

}