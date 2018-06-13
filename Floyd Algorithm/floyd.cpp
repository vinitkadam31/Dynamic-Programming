#include <iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include<list>
#include<algorithm>
#include <iterator>

using namespace std; 

vector<string> split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

void path(int n, int *P, int q, int r)
{
    if((*((P+q*n) + r)) != 0)
    {
        path(n, P, q, (*((P+q*n) + r)));
        cout<<"v"<<(*((P+q*n) + r));
        path(n, P, (*((P+q*n) + r)), r);
    }
    return;
}

void printIntermediateNodes(int n, int *P)
{
    path(n, P, 2, 3);
}

void floydAlgorithm(int n, int *D, int *P)
{
    for(int k=1;k<=n;k++)
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=1; j<=n;j++)
            {
                int value = (*((D+i*(n+1)) + k)) + (*((D+k*(n+1)) + j));
                if((*((D+i*(n+1)) + j))>value)
                {
                    (*((D+i*(n+1)) + j)) = value;
                    (*((P+i*(n+1)) + j)) = k;
                }
            }
        }
    }
}

int main(int argc, char* argv[])
{
    ifstream in(argv[1]);
    vector<string> input;
    if(!in) {
        cout << "Cannot open input file.\n";
        return 1;
    }

    char str[255];
    int W[100][100];
    int row=1;
    int column;
    int n = 0;
    while(in)
    {
        in.getline(str, 255);  // delim defaults to '\n'
        if(in)
        {
            input.push_back(str);
        }
    }
    in.close();
   // cout<<endl;
    for(int i=0;i<(int)input.size();i++)
    {
        column = 1;
        vector<string> v = split(input[i], ',');
        n=v.size();
        for(int i=0;i<(int)v.size();i++)
        {
            W[row][column++] = atoi(v[i].c_str());
        }
        row++;
    }
    int D[n+1][n+1];
    int P[n+1][n+1];
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            D[i][j] = W[i][j];
            P[i][j] = 0;
         //   cout<<W[i][j]<<"\t";
        }
  //      cout<<endl;
    }

    floydAlgorithm(n, (int *)D, (int *)P);
    /*for(int k=1;k<=n;k++)
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=1; j<=n;j++)
            {
                if(D[i][j]>(D[i][k] + (D[k][j])))
                {
                    (D[i][j]) = (D[i][k]) + (D[k][j]);
                    (P[i][j]) = k;
                }
            }
        }
    }*/

//    cout<<endl;
//    cout<<"D matrix: "<<endl;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cout<<D[i][j]<<"\t";
        }
        cout<<endl;
    }

//    cout<<endl;
/*    cout<<"P matrix: "<<endl;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cout<<P[i][j]<<"\t";
        }
        cout<<endl;
    }
    cout<<endl;*/
 //   printIntermediateNodes(n, (int *)P);
    return 0;
}
