#include <bits/stdc++.h>


using namespace std;

class attribute{

public:
    string name;
    int col;
    int val ;
    attribute(string n , int c , int v)
    {
        name = n;
        col = c;
        val = v;

    }

};

class rule{

public:
    vector<attribute> right;
    vector<attribute> left;
    rule(vector<attribute>&r, vector<attribute>&l)
    {
        right = r;
        left = l;
    }
    double confidence()
    {
      vector<attribute>attributes = right.insert( right.end(), left.begin(), left.end() );
      double num = support(attributes);
      double den = support(left);
      double conf = num / den;

      return conf * 100 ;
    }


};

int computeInter(vector<attribute> list);
float support(vector<attribute> list);

int main(){


	


}

int computeInter(vector<attribute> list)
{
	//in case of there are 2 element in the same colum
	for (int i = 0; i < list.size()-1; i++)
	{
		for (int j = i + 1; j < list.size(); j++)
		{
			if (list[i].col == list[j].col)
			{
				return 0;
			}
		}
	}
	int sum = 0;
	for (int i = 0; i < datalist.size(); i++)
	{
		int flag = 0;
		for (int j=0;j< list.size();j++)
		{
			if (list[j].val == datalist[i][list[j].col])
			{
				flag = 1;
			}
			else
			{
				flag = 0;
				break;
			}
		}
		if (flag == 1)
		{
			sum++;
		}
	}
	return sum;
}

float support(vector<attribute> list)
{
	return ((computeInter(list) / 5822) * 100);
}




