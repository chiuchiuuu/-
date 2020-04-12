#include <iostream>
#include <cmath>
using namespace std;

int wall[17][17], paint[17][17];
int width;
int minCount;

int Count()
{
	int sum = 0;
	for (int i = 1; i <= width; i++)
	{
		for (int j = 1; j <= width; j++)
		{
			sum += paint[i][j];
		}
	}
	return sum;
}

// ��ʼ������ʹ�������
void init()
{
	for (int i = 0; i < 17; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			wall[i][j] = 0;
			paint[i][j] = 0;
		}
	}

	for (int i = 1; i <= width; i++)
	{
		for (int j = 1; j <= width; j++)
		{
			char tmp;
			cin >> tmp;
			switch (tmp)
			{
			case 'y':
				wall[i][j] = 0;
				break;
			case 'w':
				wall[i][j] = 1;
				break;
			}
		}
	}
}

// ��֤���Ƿ���ȷ����Ҫ��֤���һ��
bool guess()
{
	for (int j = 1; j <= width; j++)
	{
		if ((paint[width][j - 1] + paint[width][j] + paint[width][j + 1] + paint[width - 1][j]) % 2 != wall[width][j])
			return false;
	}
	return true;
}

// ���ݵ�һ�е�ö�ٸ���ʣ�༸��
void update()
{
	for (int i = 1; i < width; i++)
	{
		for (int j = 1; j <= width; j++)
		{
			paint[i + 1][j] = (wall[i][j] + paint[i][j] + paint[i][j - 1] + paint[i][j + 1] + paint[i - 1][j]) % 2;
		}
	}
}

// ö�ٵ�һ�е����������ֱ���ó���
void enumerate()
{
	// ��ʼ���
	update();

	for (int i = 0; i < pow(2, width); i++)
	{
		if (guess())
		{
			int count = Count();
			if (count < minCount)
			{
				minCount = count;
			}
		}
		paint[1][1]++;
		int k = 1;
		while (paint[1][k] > 1) // ��λ
		{
			paint[1][k] = 0;
			paint[1][++k]++;
		}
		update();
	}
}

int main()
{
	int ncase;
	cin >> ncase;

	for (int i = 0; i < ncase; i++)
	{
		cin >> width;
		minCount = 226; // ���15*15 = 225
		init();
		enumerate();

		if (minCount == 226)
		{
			cout << "inf" << endl;
		}
		else
		{
			cout << minCount << endl;
		}
	}
}