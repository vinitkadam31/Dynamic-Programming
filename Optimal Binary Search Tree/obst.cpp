#include <iostream>
#include<vector>
#include<math.h>

using namespace std;
//const int n=4;

void print(int n, int *R, float *A);

typedef struct OBSTN
{
 int root;
 int low;
 int high;
 int depth;
int counter;
}
OBSTN;

int rootValue;

//probability calculation
float getProb(const float p[], int i, int j)
{
    float value = 0;
    for(int m=i-1;m<=j-1;m++)
    {
        value += p[m];
    }
    return value;
}

//To find minimum value
float findMin(int n, int *R, int i, int j, float *A, float prob)//, float prob
{
    float min[j-i+1];
    int counter = 0;
    float minValue = 599;
    for(int m= i;m<=j;m++)
    {
        //min[counter] = A[i][i-1] + A[i+1][j]+ prob;
        min[counter] = *((A+i*n) + (m-1)) + *((A+(m+1)*n) + j)+ prob;//+ prob;
        if(min[counter]< minValue)
        {
            minValue = min[counter];
            rootValue = m;
        }

        counter++;
    }
    return minValue;
}

//Calculate Optimum binary tree
void optsearchtree(int n, const float p[], int *R, float *A)
{
    int i, j, k, diagonal;

    for (i = 0; i <= n; i++)
    {
        for(int j=0;j<=n;j++)
        {
            *((A+i*n) + j) = 0;
            *((R+i*n) + j) = 0;
        }
    }

    for (i = 1; i <= n; i++) //initialization
    {
         //A[i][i-1] = 0;
         *((A+i*n) + i-1) = 0;
         *((R+i*n) + i-1) = 0;
         //R[i][i-1] = 0;

         //A[i][i] = p[i-1];
         *((A+i*n) + i) = p[i-1];
         *((R+i*n) + i) = i;
         //R[i][i] = i;
    }

    //A[n+1][n] = 0;
    *((A+(n+1)*n) + n) = 0;
    *((R+(n+1)*n) + n) = 0;
    //R[n+1][n] = 0;
    //findMin(n, R);
    //print(n, R, A);
    for (diagonal = 1; diagonal <= n-1; diagonal++)
	for (i = 1; i <= n - diagonal; i++)
	{
			j = i + diagonal;
            *((A+i*n) + j) = findMin(n, R, i, j, A, getProb(p, i, j));//getProb(p, i, j)
            *((R+i*n) + j) = rootValue;
			///R[i][j] = a value of k that gave the minimum
	}
    float minavg = *((A+1*n) + n);
    int counter = 0;
    int variable = n;
    /*while(1)
    {
        //float minavg = A[1][variable];
        int root = *((R+1*variable) + variable);
        cout<<"depth "<<counter++<<":"<<root<<endl;
        variable = root;
    }*/

}

//print Root and A matrix
void print(int n, int *R, float *A)
{
    cout<<"matrix R: "<<endl;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cout<<*((R+i*n) + j)<<"\t";
        }
        cout<<endl;
    }
    cout<<endl;
/*
    cout<<"matrix A: "<<endl;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cout<<*((A+i*n) + j)<<"\t";
        }
        cout<<endl;
    }*/
}

/*OBST *CONSTRUCT_OBST(int i, int j, int *R, int n)
{
     OBST *p;
     if((i == j)
        p = NULL;
     else
     {
         p = new OBST;
         p->KEY = *((R+i*n) + j);//KEYS[R[i][j]];
         p->left = CONSTRUCT_OBST(i, (*((R+i*n) + j)) - 1, R, n); //left subtree
         p->right = CONSTRUCT_OBST(*((R+i*n) + j), j, R, n); //right subtree
     }
     return p;
}*/

/*void DISPLAY(OBST *ROOT, int nivel)
{
     int i;
     if(ROOT != 0)
     {
         DISPLAY(ROOT->right, nivel+1);
         for(i = 0; i <= nivel; i++)
         cout<<" ";
         cout<<ROOT->KEY<<endl;
         //printf("%d\n", ROOT->KEY);
         DISPLAY(ROOT->left, nivel + 1);

     }
}*/

//To display printTemp for debugging
void printTemp(vector<OBSTN*> temp)
{
    //OBSTN dir[temp.size()];
  for(int i=0;i<temp.size();i++)
  {
        //dir[i] = temp[i];
        cout << temp[i]->root << " - " << temp[i]->low<<" - "<<temp[i]->high<<" - "<<temp[i]->depth<<" - "<<temp[i]->counter<<endl;
  }
  cout<<endl;
}

//To check element already traversed or not for printing
bool CheckElementAlreadyTraversed(vector<int> selectedElements, int current)
{
    for(int i=0;i<selectedElements.size();i++)
    {
        if(selectedElements[i]==current)
            return true;
    }
    return false;
}

//return power of 2
int GetPowerOf2(int n)
{
    if(n==0)
        return 1;
    if(n==1)
        return 2;
    else
    {
        int result = 1;;
        for(int i=0;i<n;i++)
            result = result * 2;
        return result;
    }
}

/*int GetLeftIncreament(int counter)
{
    return counter + counter;
}

int GetRightIncreament(int leftCounter, int counter)
{
    return leftCounter + counter;
}*/

//To print element depth wise
void printAllNodes(OBSTN *root, int *R, int n)
{

  vector<OBSTN*> temp;
  OBSTN *traverse;
  vector<int> selectedElements;

  temp.push_back(root);
    //R[traverse.low][traverse.high]//print root
    int counter = 0;
    int depth = 0;
    int PrintA [n][GetPowerOf2(n)];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<GetPowerOf2(n);j++)
        {
            PrintA[i][j]=0;
        }
    }
    int maxDepth = 0;
  while (temp.size()!=0) {
    int rt = temp.size();
    //cout<<"before:"<<endl;
    //printTemp(temp);
    traverse = temp[temp.size()-1];//temp.size()-1
    temp.pop_back();
    //cout<<"after pop back"<<endl;
    //printTemp(temp);
    int value = (*((R+(traverse->low)*n) + traverse->high));
    if(traverse->root == 0)
    {
        //cout<<"Depth "<<traverse->depth<<": "<<(*((R+(traverse->low)*n) + traverse->high))<<", "<<traverse->counter<<endl;
        selectedElements.push_back(*((R+(traverse->low)*n) + traverse->high));
        //traverse->depth = traverse->depth+1;
        if(maxDepth<traverse->depth)
            maxDepth = traverse->depth;
        PrintA[traverse->depth][traverse->counter] = value;
    }
    else if((traverse->low != traverse->high) || (traverse->root != traverse->low && traverse->root != traverse->high))
    {
        if(traverse->root > (*((R+(traverse->low)*n) + traverse->high)))//R[traverse.low][traverse.high]
        {
            if((CheckElementAlreadyTraversed(selectedElements, value)))//((traverse->high - traverse->low) == 1) &&
            {
                if(value == traverse->low)
                    value = traverse->high;
                else if(value == traverse->high)
                    value = traverse->low;

                if(CheckElementAlreadyTraversed(selectedElements, value))
                    continue;
            }
            //cout<<"Depth "<<traverse->depth<<": "<<value<<", "<<traverse->counter<<endl;
            //cout<<"parent: "<<traverse->root<<", left: "<<(*((R+(traverse->low)*n) + traverse->high))<<endl;
            selectedElements.push_back(value);
            PrintA[traverse->depth][traverse->counter] = value;
            if(maxDepth<traverse->depth)
            maxDepth = traverse->depth;
        }
        else
        {
            bool print = true;
            if((CheckElementAlreadyTraversed(selectedElements, value)))//((traverse->high - traverse->low) == 1) &&
            {

                if(value == traverse->low)
                    value = traverse->high;
                else if(value == traverse->high)
                    value = traverse->low;

                if(CheckElementAlreadyTraversed(selectedElements, value))
                    continue;
            }
            //cout<<"Depth "<<traverse->depth<<": "<<value<<", "<<traverse->counter<<endl;
            //cout<<"parent: "<<traverse->root<<", right: "<<(*((R+(traverse->low)*n) + traverse->high))<<endl;
            selectedElements.push_back(value);
            PrintA[traverse->depth][traverse->counter] = value;
            if(maxDepth<traverse->depth)
            maxDepth = traverse->depth;
        }
        //print R[traverse.low][traverse.high]
    }

    traverse->depth = traverse->depth + 1;
    if(traverse->low == traverse->high)
    {
        continue;
    }
    //int value = (*((R+(traverse->low)*n) + traverse->high));//R[traverse->low][traverse->high]//print

    //int leftIncreament = GetLeftIncreament(traverse->depth-1, traverse->counter);
    //int rightIncrement = GetRightIncreament(traverse->depth, leftIncreament);

    //Right
    OBSTN *p1 = new OBSTN;
    p1->low = value;
    p1->high = traverse->high;
    p1->root = value;//R[traverse->low][traverse->high]
    p1->depth = traverse->depth;
    p1->counter = (traverse->counter+traverse->counter+1);
    /*if(traverse->counter == 0)
        p1->counter = traverse->counter + 1;
    else
        p1->counter = traverse->counter + (traverse->counter+1);//2
        */
    if(p1->low == p1->high && traverse->root == p1->low && traverse->root == p1->high)
    {
        cout<<"";
    }
    else{
        temp.push_back(p1);
    }

    //Left
    OBSTN *p2 = new OBSTN;
    p2->low = traverse->low;
    p2->high = value-1;
    p2->root = value;//R[traverse->low][traverse->high]
    p2->depth = traverse->depth;
    p2->counter = (traverse->counter+traverse->counter);
    //if(traverse->counter != 0)
        //p2->counter = traverse->counter+1;
    if(p2->low == p2->high && traverse->root == p2->low && traverse->root == p2->high)
    {
        cout<<"";
    }
    else{
        temp.push_back(p2);
    }
      //temp.push_back(traverse->right);
  }
  //cout<<"Max Depth: "<< maxDepth<<endl;
    for(int i=0;i<=maxDepth;i++)
    {
        cout<<"Depth "<<i<<":";
        bool elementFound = false;

        for(int j=0;j<GetPowerOf2(i);j++)
        {
            /*if(PrintA[i][j] != 0)
                elementFound = true;

            if(elementFound == true && PrintA[i][j] == 0)
                break;*/
            cout<<PrintA[i][j]<<",";
        }
        cout<<endl;
    }
}

int main(int argc, char* argv[])
{
    int n;
    if(argc<2)
    {
	cout<<"Insufficient Argument"<<endl;
        return 1;
    }
    else
    {
	n= atoi(argv[1]);
        if(argc < n+2)
	{
	    cout<<"Insufficient Argument"<<endl;
            return 1;
	}
    }
    //cout<<atoi(argv[1])<<"-"<<atoi(argv[2])<<"-"<<argc<<endl;
    //int n= atoi(argv[1]);//9;
    float p[n];
    for(int i=0;i<n;i++)
    {
	p[i] = atof(argv[i+2]);
    }
    /*for(int i=0;i<n;i++)
    {
	cout<<p[i]<<"\t";
    }*/
    cout<<endl;
    //float p[] = {0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9};///{0.1,0.2,0.3,0.4};//{0.25,0.2,0.05,0.2,0.3};//{0.1,0.7,0.3,0.4,0.5,0.6,0.2};
    int R[n+1][n+1];
    float A[n+1][n+1];
    optsearchtree(n, p, (int *)R, (float *)A);
    print(n, (int *)R, (float *)A);
	cout<<endl;
    //ROOT = CONSTRUCT_OBST(1, n, (int *)R, n);
    //DISPLAY(ROOT, 0);
    OBSTN *p1 = new OBSTN;

    p1->root = 0;
    p1->low = 1;
    p1->high = n;
    p1->depth = 0;
    p1->counter = 0;
    printAllNodes(p1, (int *)R, n);
    //cout<<"done"<<endl;
    return 0;
}
