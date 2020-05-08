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
    attribute(){
    	name = "";
    	col = -1;
    	val = -1;
    }
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

    float confidence()
    {
      vector<attribute> tmpRight;
      for(int i=0;i<left.size();i++)tmpRight.push_back(left[i]);
      for(int i=0;i<right.size();i++)tmpRight.push_back(right[i]);
      vector<attribute> attributes = tmpRight;
      float num = support(attributes);
      float den = support(left);
      float conf = num / den;

      return conf * 100 ;
    }


};
void AquireData(){
	ifstream inputFile;
	inputFile.open("ticdata2000.txt");
	DataList = vector<vector<int>>(5822,vector<int>(12));

	for(int i=0;i<5822;i++){
		vector<int> tmp(49);
		for(int j=0;j<49;j++){
			inputFile>>tmp[j];
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

vector<vector<attribute>> aprioriComb(vector<attribute> attributes, vector<attribute> taken, int sz, int start, int end, int index, float minSupport, float minConf){
	vector<vector<attribute>> local;
	// Base case that we have completed a combination now.
	if(index==sz){
		float sup = support(taken);
		if(sup>=minSupport){
			local.push_back(taken);
			return local;
		}
		else return local;
	}
	// sz-index tells us what is left to be added we must add to taken attributes
	// end-i+1 tells us what is left to be added from the original vector attributes
	// so we must have number of attributes left in the original array larger than the number we
	// still have to add to taken as if it is lower we will reach the end of the original
	// and still need to add to our taken attributes vector.
	for(int i=start;i<=end && end-i+1>=sz-index;i++){
		bool flag = false;
		for(int j = 0;j<index;j++)if(attributes[i].col==taken[j].col)flag = true;
		if(flag)continue;
		taken[index] = attributes[i];
		vector<vector<attribute>> found = aprioriComb(attributes,taken,sz,i+1,
										end,index+1,minSupport,minConf);
		for(int j=0;j<found.size();j++)local.push_back(found[j]);
	}
	return local;

}

vector<rule> apriori(vector<attribute> &attributes,float minSupport,float minConf){
	vector<vector<attribute>> maxCombs;
	for(int i=1;i<=attributes.size();i++){
		vector<attribute> tmp(i);
		vector<vector<attribute>> validComb = aprioriComb(attributes,tmp,i,0,attributes.size()-1,0,minSupport,minConf);
		if(validComb.size()>0)maxCombs=validComb;
		else break;
		vector<attribute> newAttr;
		vector<vector<bool>> vis(13,vector<bool>(200));
		for(int i=0;i<maxCombs.size();i++){
			for(int j=0;j<maxCombs[i].size();j++){
				if(!vis[maxCombs[i][j].col][maxCombs[i][j].val]){
					newAttr.push_back(maxCombs[i][j]);
					vis[maxCombs[i][j].col][maxCombs[i][j].val]=true;
				}
			}
		}
		attributes = newAttr;
	}
	// Getting the valid rules from the best attributes we got after computing the support.
	vector<rule> AssociationRules;
	for(int i = 0; i < maxCombs.size();i++){
		vector<attribute> currentAttr = maxCombs[i];

		for(int x = 0;x<currentAttr.size();x++){
			rule tmpRule;
			vector<attribute> onRight;
			// Get the ones before the current and put them on the right side.
			for(int y = 0;y<x;y++)onRight.push_back(currentAttr[y]);
			// combinations on all other attributes.
			for(int y=x;y<currentAttr.size();y++){
				tmpRule.left.push_back(currentAttr[y]);
				tmpRule.right.clear();
				tmpRule.right = onRight;
				for(int z = y+1;z<currentAttr.size();z++){
					tmpRule.right.push_back(currentAttr[z]);
				}
				if(tmpRule.right.size()!=0&&tmpRule.left.size()!=0){
					if(tmpRule.confidence()>=minConf)AssociationRules.push_back(tmpRule);
				}
			}
		}
	}
	return AssociationRules;

}


int main(){

	AquireData();
	vector<attribute> attributes = initialize();
	vector<rule> AssociationRules = apriori(attributes,10,10);
	for(int i = 0;i<AssociationRules.size();i++){
		rule tmp = AssociationRules[i];
		for(int j=0;j<tmp.left.size();j++)cout<<tmp.left[j].name<<" "<<tmp.left[j].val<<" ,";
		cout<<"  -->  ";
		for(int j=0;j<tmp.right.size();j++)cout<<tmp.right[j].name<<" "<<tmp.right[j].val<<" ,";
		cout<<'\n';
	}


}



