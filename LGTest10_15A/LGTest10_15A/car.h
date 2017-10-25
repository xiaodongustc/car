#ifndef CAR_H
#define CAR_H

#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;


//����
typedef struct Date 
{
	int year;
	int month;
	int day;
}Date,*PDate;

//������Ϣ
typedef struct Car 
{
	string car_num;//���ƺ�
	PDate start_date;//��������
	PDate now_date;//����ʱ��
	string car_brand;//������
	int distance;//��ʻ���
	bool fix;//�Ƿ����
	bool sign;//�Ƿ����㱨�ϵı�־
	bool flag;//�Ƿ��Ѿ����ѹ��˵ı�־
}Car;

//�������
typedef struct Print 
{
	string car_brand;
	vector<string> car_nums;
}Print,*PPrint;

//��ȡ�ն�����
void Import(vector<Car> &vec);

//��ⱨ��
void Is_Off(vector<Car> &vec,stack<vector<Print>> &sta);

//������
void Is_Distance(vector<Car> &vec,stack<vector<Print>> &sta);

//���ʱ��
void Is_Time(vector<Car> &vec,stack<vector<Print>> &sta);

//������
void Process(vector<Car> &vec,stack<vector<Print>> &sta);

//��ӡ����
void Show(stack<vector<Print>> &sta);

#endif