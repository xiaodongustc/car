#include "car.h"


const int n = 10;
Date now_date;
Date start_date[n];

//�Գ���Ʒ�ư���������
void sort_brand(vector<Print> &p)
{
	vector<Print>::iterator it = p.begin();

	int size = p.size();

	for (int i = 0;i < size;++i)
	{
		for (int j = 0;j < size-i-1;++j)
		{
			if (it[j].car_brand.compare(it[j+1].car_brand)>0)
			{
				Print temp;
				temp.car_brand = it[j].car_brand;
				temp.car_nums = it[j].car_nums;
				it[j].car_brand = it[j+1].car_brand;
				it[j].car_nums = it[j+1].car_nums;
				it[j+1].car_brand = temp.car_brand;
				it[j+1].car_nums = temp.car_nums;
			}
		}
	}
}

//��ȡ�ն�����
void Import(vector<Car> &vec)
{
	
	Car car[n];

	cout<<"SubmitDate��";
	char ch;
	cin>>now_date.year>>ch;
	cin>>now_date.month>>ch;
	cin>>now_date.day;
//	cout<<vec.size()<<endl;
	for(int i=0;i<n;++i)
	{
		if (!cin.good())
		{
			break;
		}
		car[i].now_date = &now_date;
		cin>>car[i].car_num>>ch;
		cin>>start_date[i].year>>ch;
		cin>>start_date[i].month>>ch;
		cin>>start_date[i].day>>ch;
		car[i].start_date = &start_date[i];
		cin>>car[i].car_brand>>ch;
		cin>>car[i].distance>>ch;
		cin>>ch;
		if(ch == 'F')
		{
			car[i].fix = 0;
		}
		else if(ch == 'T')
		{
			car[i].fix = 1;
		}
		car[i].sign = 0;
		car[i].flag = 0;
		vec.push_back(car[i]);

		
	}

	//��ӡ�ն����������

	//cout<<car[0].now_date->year<<"/"<<car[0].now_date->month<<"/"<<car[0].now_date->day<<endl;
	//vector<Car>::iterator it = vec.begin();
	//for (it;it != vec.end();it++)
	//{
	//	
	//	cout<<it->car_num<<"|";
	//	cout<<it->start_date->year<<"/"<<it->start_date->month<<"/"<<it->start_date->day<<"|";
	//	cout<<it->car_brand<<"|"<<it->distance<<"|";
	//	if (it->fix)
	//	{
	//		cout<<"T"<<it->flag<<endl;
	//	}
	//	else
	//	{
	//		cout<<"F"<<it->flag<<endl;
	//	}
	//}
	
}

//��ⱨ��
void Is_Off(vector<Car> &vec,stack<vector<Print>> &sta)
{
	vector<Car>::iterator it = vec.begin();
	
	for (it;it != vec.end();it++)//�������еĳ�����Ϣ
	{
		//�������
		int length_year = it->now_date->year - it->start_date->year;
		//�����²�
		int length_month = it->now_date->month - it->start_date->month;

		int length_day = it->now_date->day - it->start_date->day;

		
		//����Ƿ񱨷ϻ��߽��뱨��������
		//it->sign == 1 ˵���ѱ���
		//success = 1��ʾ�ѽ��뱨��������
		bool success = 0;


		if (it->fix)//����д���
		{
			if (length_year > 3)//ֱ�ӳ���3��
			{
				it->sign = 1;
			}
			else if (length_year == 3 && (length_month > 0 || (length_month == 0 && length_day >= -1)))//�պ����꣬���ҿ����·ݳ���
			{
				it->sign = 1;
			}
			else if(length_year == 3 && length_month <= 0 && length_month >= -2)//�·ݲ�һ�¾͸պ�����
			{
				success = 1;
			}
		}
		else	//û�й�����
		{
			if (length_year > 6)//ֱ�ӳ���6��
			{
				it->sign = 1;
			}
			else if (length_year == 6 && (length_month > 0 || (length_month == 0 && length_day >= -1)))////�պ�6�꣬���ҿ����·ݳ���
			{
				it->sign = 1;
			}
			else if(length_year == 6 && length_month <= 0 && length_month >= -2)////�·ݲ�һ�¾͸պ�6��
			{
				success = 1;
			}
		}
		
		//������뱨�������� success == 1;
		
		if (!it->sign && success)
		{
			vector<Print> vec_off = sta.top();//���뱨���������ڵĳ�������Ϣ
			sta.pop();
			it->flag = 1;
			vector<Print>::iterator it1 = vec_off.begin();//�����е�Print���б���
			for(it1;it1 != vec_off.end();it1++)
			{
				if(it1->car_brand.compare(it->car_brand) == 0)//���������Ϣ���иó��Ƶĵĳ���
				{
					it1->car_nums.push_back(it->car_num);//�����ƺ�ѹ�뼯����
					sta.push(vec_off);
					return;
				}
			}
			//���������Ϣ��û�иó����ĳ��ƺţ��½�һ��Print
			Print off;
			off.car_nums.push_back(it->car_num);
			off.car_brand = it->car_brand;
			vec_off.push_back(off);	
			sort_brand(vec_off);
			sta.push(vec_off);
			
		}
	}
	
}

//������
void Is_Distance(vector<Car> &vec,stack<vector<Print>> &sta)
{
	vector<Car>::iterator it = vec.begin();
	for (it;it != vec.end();it++)
	{
		bool success = 0;
		//����Ƿ��ܹ�һ����
		int length_dis = it->distance % 10000;
		if(length_dis >= 9500 || length_dis == 0)//���뱣��������
		{
			success = 1;
		}

		//������뱣�������ڣ�success == 1
		if(!it->sign && success && !it->flag)
		{
			vector<Print> vec_dis = sta.top();
			sta.pop();
			it->flag = 1;
			vector<Print>::iterator it1 = vec_dis.begin();//�����е�Print���б���
			for(it1;it1 != vec_dis.end();it1++)
			{
				if(it1->car_brand.compare(it->car_brand) == 0)//���������Ϣ���иó��Ƶĵĳ���
				{
					it1->car_nums.push_back(it->car_num);//�����ƺ�ѹ�뼯����
					sta.push(vec_dis);
					return;
				}
			}
			//��������Ϣ��û�иó����ĳ��ƺţ��½�һ��Print
			Print dis;
			dis.car_nums.push_back(it->car_num);
			dis.car_brand = it->car_brand;
			vec_dis.push_back(dis);
			sort_brand(vec_dis);
			sta.push(vec_dis);			
		}
	}
}

//���ʱ��
void Is_Time(vector<Car> &vec,stack<vector<Print>> &sta)
{
	vector<Car>::iterator it = vec.begin();
	for (it;it != vec.end();it++)
	{
		int length_year = it->now_date->year - it->start_date->year;
		int length_month = (it->now_date->month + length_year * 12) - it->start_date->month;

		bool success = 0;
		//����Ƿ��˶��ڱ���������
		if (it->fix)//�����д���
		{
			if (length_month % 3 == 2 || length_month % 3 == 0)//���ڱ���ȫ����ǰһ��������
			{
				success = 1;
			}
		}
		else
		{
			if (length_year >= 3)
			{
				if (length_month % 6 == 5 || length_month % 6 == 0)
				{
					success = 1;
				}
			}
			else
			{
				if (length_month % 12 == 11 || length_month % 12 == 0)
				{
					success = 1;
				}
				
			}
		}

		//������뱣�������ڣ�success == 1
		if(!it->sign && success && !it->flag)
		{
			vector<Print> vec_time = sta.top();
			sta.pop();
			it->flag = 1;
			vector<Print>::iterator it1 = vec_time.begin();//�����е�Print���б���
			for(it1;it1 != vec_time.end();it1++)
			{
				if(it1->car_brand.compare(it->car_brand) == 0)//���������Ϣ���иó��Ƶĵĳ���
				{
					it1->car_nums.push_back(it->car_num);//�����ƺ�ѹ�뼯����
					sta.push(vec_time);
					return;
				}
			}
			//���������Ϣ��û�иó����ĳ��ƺţ��½�һ��Print
			Print time;
			time.car_nums.push_back(it->car_num);
			time.car_brand = it->car_brand;
			vec_time.push_back(time);
			sort_brand(vec_time);
			sta.push(vec_time);
		}
	}
}

//������
void Process(vector<Car> &vec,stack<vector<Print>> &sta)
{
	vector<Print> vec_off;
	sta.push(vec_off);
	Is_Off(vec,sta);

	vector<Print> vec_dis;
	sta.push(vec_dis);
	Is_Distance(vec,sta);

	vector<Print> vec_time;
	sta.push(vec_time);
	Is_Time(vec,sta);

}

//��ӡ����
void Show(stack<vector<Print>> &sta)
{
	cout<<"Reminder"<<endl;
	cout<<"============================"<<endl<<endl;

	string arr[3] = {
		"* Time-related maintenance coming soon...",
		"* Distance-related maintenance coming soon...",
		"* Write-off coming soon..."
	};
	int i = 0;
	while(!sta.empty())
	{
		//��ӡջ�������Ԫ��
		vector<Print> vec2 = sta.top();
		sta.pop();
		cout<<arr[i]<<endl;
		i++;
		vector<Print>::iterator it = vec2.begin();

		for (it;it != vec2.end();it++)
		{
			vector<string> car_nums = it->car_nums;
			cout<<it->car_brand<<"��"<<car_nums.size()<<" (";
			vector<string>::iterator it2 = car_nums.begin();
			for (it2;it2 != car_nums.end();it2++)
			{
				if (it2+1 != car_nums.end())
				{
					cout<<*it2<<",";
				}
				else
				{
					cout<<*it2;
				}
				
			}
			cout<<")"<<endl;
		}

	}
}