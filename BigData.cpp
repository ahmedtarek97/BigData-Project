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

int main(){


	


}
