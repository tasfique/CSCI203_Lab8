#include <limits>
#include <bits/stdc++.h>
using namespace std;

void findFirst(int arr[][10], int N);
int findHighest(int arr[][10], int N);
void findLowest(int arr[][10],int N, int M[]);
int findMinimum(int costMatrix[][10], int N);

int main()
{
    int number;
    cout<<"Please Enter the number of Workers and Tasks: " << endl;
    cin>>number;

    while(number<=0)
    {
        cout<<"Error"<<endl;
        cout<<"Please Enter the number of Workers and Tasks: " << endl;
        cin>>number;

    }

    while(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout<<"Error"<<endl;
             cout<<"Please Enter the number of workers and Tasks: " ;
            cin>>number;
        }

    int JobArray[number][10];
    int minimum[number];
    for(int i=0;i<number;i++)
    {
        cout<<"Worker "<<i+1<<"\n*****************************"<<endl;
        for(int j=0;j<number;j++)
        {
            cout<<"Please Enter the cost of Task "<<j+1<<": ";
            cin>>JobArray[i][j];

            while(JobArray[i][j]<0)
    {
        cout<<"Error"<<endl;
         cout<<"Please Enter the cost of Task "<<j+1<<": ";
            cin>>JobArray[i][j];

    }

     while(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout<<"Error"<<endl;
            cout<<"Please Enter the cost of Task "<<j+1<<": ";
            cin>>JobArray[i][j];

        }



        }
        cout<<endl;
    }
    cout<<"\t\t";
    for(int i=0;i<number;i++)
    {
        cout<<"Task "<<i+1<<"\t";
    }
    cout<<endl;
    for(int i=0;i<number;i++)
    {
        cout<<"Worker "<<i+1<<"\t";
        for(int j=0;j<number;j++)
        {
            cout<<JobArray[i][j]<<"\t";
        }
        cout<<endl;
    }
    cout<<endl;
    findLowest(JobArray,number,minimum);
    int smallest=0;
    for(int i=0;i<number;i++)
    {
        cout<<"The minimum cost for task "<<i+1<<": "<<minimum[i]<<endl;
        smallest=smallest+minimum[i];
    }

    findFirst(JobArray,number);
    cout<<"The lower bound: "<<smallest<<endl;
    cout<<smallest<<" <= Cost <= ";
     cout<<findHighest(JobArray,number)<<endl;

    cout << "\nThe Optimal Total Cost: "<< findMinimum(JobArray,number)<<endl;
    return 0;
}

void findFirst(int arr[][10], int N)
{
    int number1=0;
    int number2=0;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(i==j)
            {
                number1=number1+arr[i][j];
            }
        }
    }

    for(int i=0;i<N;i++)
    {
        for(int j=N-1;j>=0;j--)
        {
            if((i+j)==(N-1))
            {
                number2=number2+arr[i][j];
            }
        }
    }
cout<<"\n Calculating Upper boundary from the left diagonal = "<<number1;
cout<<"\n Calculating Upper Boundary from the right diagonal = "<<number2<<endl;


}

int findHighest(int arr[][10], int N)
{
    int num1=0;
    int num2=0;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(i==j)
            {
                num1=num1+arr[i][j];
            }
        }
    }

    for(int i=0;i<N;i++)
    {
        for(int j=N-1;j>=0;j--)
        {
            if((i+j)==(N-1))
            {
                num2=num2+arr[i][j];
            }
        }
    }
    if(num1<=num2)
    {
        return num1;
    }
    else
    {
        return num2;
    }

}
void findLowest(int arr[][10],int N, int M[])
{
    for(int i=0; i<N;i++)
    {
        M[i]=arr[0][i];
    }
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(M[i]>arr[j][i])
            {
                M[i]=arr[j][i];
            }
        }
    }
}
// state space tree node
struct Node
{
    // stores parent node of current node
    // helps in tracing path when answer is found
    Node* parent;

    // contains cost for ancestors nodes
    // including current node
    int pathCost;

    // contains least promising cost
    int cost;

    // contain worker number
    int workerID;

    // contains Job ID
    int jobID;

    // Boolean array assigned will contains
    // info about available jobs
    bool *assigned;

    int indiCost;
};

// Function to allocate a new search tree node
// Here Person x is assigned to job y
Node* newNode(int x, int y, bool assigned[],
              Node* parent,int N)
{

    Node* node = new Node;
    node->assigned=new bool[N];
    for (int j = 0; j < N; j++)
    node->assigned[j] = assigned[j];
    node->assigned[y] = true;

    node->parent = parent;
    node->workerID = x;
    node->jobID = y;
    return node;
}

// Function to calculate the least promising cost
// of node after worker x is assigned to job y.
int calculateCost(int costMatrix[][10], int x,int y, bool assigned[], int N)
{
    int cost = 0;

    // to store unavailable jobs
    bool available[N] = {true};

    // start from next worker
    for (int i = x + 1; i < N; i++)
    {
        int min =2147483647, minIndex = -1;

        // do for each job
        for (int j = 0; j < N; j++)
        {
            // if job is unassigned
            if (!assigned[j] && available[j] &&
                costMatrix[i][j] < min)
            {
                // store job number
                minIndex = j;

                // store cost
                min = costMatrix[i][j];
            }
        }

        // add cost of next worker
        cost += min;

        // job becomes unavailable
        available[minIndex] = false;
    }

    return cost;
}

// Comparison object to be used to order the heap
struct comp
{
    bool operator()(const Node* lhs,
                   const Node* rhs) const
    {
        return lhs->cost > rhs->cost;
    }
};

// print Assignments
void printAssignments(Node *min)
{
    if(min->parent==NULL)
    {
        return;
    }
    printAssignments(min->parent);
    cout << "Assign Worker " << char(min->workerID + 'A')
         << " to JOB " << (min->jobID)+1 <<"\tCost: "<<(min->pathCost)-(min->parent->pathCost)<< endl;

}

// Finds minimum cost using Branch and Bound.
int findMinimum(int costMatrix[][10], int N)
{
    // Create a priority queue to store live nodes of
    // search tree;
    priority_queue<Node*, std::vector<Node*>, comp> pq;

    // initailize heap to dummy node with cost 0
    bool assigned[N] = {false};
    Node* root = newNode(-1, -1, assigned, NULL,N);
    root->pathCost = root->cost = 0;
    root->workerID = -1;
    // Add dummy node to list of live nodes;
    pq.push(root);

    // Finds a live node with least cost,
    // add its childrens to list of live nodes and
    // finally deletes it from the list.
    while (!pq.empty())
    {
      // Find a live node with least estimated cost
      Node* min = pq.top();

      // The found node is deleted from the list of
      // live nodes
      pq.pop();

      // i stores next worker
      int i = min->workerID + 1;

      // if all workers are assigned a job
      if (i == N)
      {
          printAssignments(min);
          return min->cost;
      }

      // do for each job
      for (int j = 0; j < N; j++)
      {
        // If unassigned
        if (!min->assigned[j])
        {
          // create a new tree node
          Node* child = newNode(i, j, min->assigned, min,N);
          // cost for ancestors nodes including current node
          child->pathCost = min->pathCost + costMatrix[i][j];

          // calculate its lower bound
          child->cost = child->pathCost +
            calculateCost(costMatrix, i, j, child->assigned, N);

          // Add child to list of live nodes;
          pq.push(child);
        }
      }
    }
}

