#include <bits/stdc++.h>

using namespace std;

vector<string> ColumnNames = {"Customer","Roman catholic","Protestant","Other religion","No religion",
"Married","Living together","Other relation","Singles","Household without children","Household with children",
"High level education"};
vector<vector<int>> DataList;

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
int computeIntersect(vector<attribute> list)
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
	for (int i = 0; i < DataList.size(); i++)
	{
		int flag = 0;
		for (int j=0;j< list.size();j++)
		{
			if (list[j].val == DataList[i][list[j].col])
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
	return (((float)computeIntersect(list) / 5822) * 100);
}

class rule{

public:
    vector<attribute> right;
    vector<attribute> left;
    rule(vector<attribute> &r, vector<attribute> &l)
    {
        right = r;
        left = l;
    }
    double confidence()
    {

      right.insert( right.end(), left.begin(), left.end() );
      vector<attribute> attributes = right;
      double num = support(attributes);
      double den = support(left);
      double conf = num / den;

      return conf * 100 ;
    }


};
void AquireData(){
	ifstream inputFile;
	inputFile.open("ticdata2000.txt");
	vector<vector<int>> DataList(5822,vector<int>(12));

	for(int i=0;i<5822;i++){
		vector<int> tmp(49);
		for(int j=0;j<49;j++){
			cin>>tmp[j];
		}
		for(int j=4;j<16;j++){
			DataList[i][j-4] = tmp[j];
		}
	}
	return ;


}

vector<attribute> initialize(){
	vector<attribute> attributes;
	vector<vector<bool>> vis(12,vector<bool>(6000));
	for(int i=0;i<12;i++){
		for(int j=0;j<5822;j++){
			attribute tmpAttr = attribute(ColumnNames[i],i,DataList[j][i]);
			if(vis[i][DataList[j][i]])continue;
			vis[i][DataList[j][i]] =true;
			attributes.push_back(tmpAttr);
		}
	}

	return attributes;
}



int main(){

//	vector<vector<int>> DataList = AquireData();
//	vector<attribute> attributes = initialize(DataList);
//	for(int i=0;i<attributes.size();i++){
//		cout<<attributes[i].name<<" "<<attributes[i].col<<" "<<attributes[i].val<<'\n';
//	}



}



