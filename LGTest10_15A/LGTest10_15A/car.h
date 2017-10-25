#ifndef CAR_H
#define CAR_H

#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;


//日期
typedef struct Date 
{
	int year;
	int month;
	int day;
}Date,*PDate;

//车辆信息
typedef struct Car 
{
	string car_num;//车牌号
	PDate start_date;//购买日期
	PDate now_date;//现在时间
	string car_brand;//车牌名
	int distance;//行驶里程
	bool fix;//是否大修
	bool sign;//是否满足报废的标志
	bool flag;//是否已经提醒过了的标志
}Car;

//输出内容
typedef struct Print 
{
	string car_brand;
	vector<string> car_nums;
}Print,*PPrint;

//读取终端输入
void Import(vector<Car> &vec);

//检测报废
void Is_Off(vector<Car> &vec,stack<vector<Print>> &sta);

//检测里程
void Is_Distance(vector<Car> &vec,stack<vector<Print>> &sta);

//检测时间
void Is_Time(vector<Car> &vec,stack<vector<Print>> &sta);

//处理函数
void Process(vector<Car> &vec,stack<vector<Print>> &sta);

//打印函数
void Show(stack<vector<Print>> &sta);

#endif