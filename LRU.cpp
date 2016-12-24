#include<iostream>
using namespace std;
#include<map>
#include<list>
#define capacity 4
struct klist
{
	int data;
	struct klist * next;
};
void push_back(struct klist ** root,int data)
{
	struct klist * cur = new struct klist;
	cur->data = data;
	cur->next = *root;
	*root = cur;
}
void print(struct klist * root)
{
	while(root)
	{
		cout<<root->data<<" ";
		root = root->next;
	}
}
int pop_front(struct klist **root)
{
	struct klist * cur = *root;
	if(cur==NULL)
		return 0;
	int data =0;
	if(cur->next == NULL)
	{
		data = cur->data;
		delete cur;
		cur = NULL;
	}
	else
	{
		while(cur->next->next)
			cur = cur->next;

		struct klist * temp = cur->next;
		data = temp->data; 
		delete temp;
		cur->next = NULL;
		//*root = cur;//Not Needed 
	}
	return data; 
}
//Pop from anywhere
void pop(struct klist **root,int data)
{
	struct klist * cur = *root;
	if(cur==NULL)
		return;
	if(cur->data==data)
	{
		struct klist * temp = cur;
		cur = cur->next;
		delete temp;
		*root = cur;
	}
	else
	{
		while(cur->next->data!=data)
		{
			cur = cur->next;
		}
		struct klist * temp = cur->next; 
		cur->next = cur->next->next;
		delete temp;
	}
	
}
void LRU(struct klist **root,map<int,int> &m,int data,int *size)
{
	if(*size>capacity)
	{
		int temp = pop_front(root);
		cout<<endl<<temp<<endl;
		m[temp]=0;
		push_back(root,data);
	}
	else
	{
		if(m[data])
		{
			pop(root,data);
			(*size)--;
			push_back(root,data);
		}
		else
		{
			push_back(root,data);
			m[data]=1;
		}
	}
}
int main()
{
	int arr[]={1,2,3,1,4,5};
	int sz = sizeof(arr)/sizeof(arr[0]);
	//list<int> l;
	struct klist * root=NULL;
	int size = 0;
	map<int,int> m;
	for(int i =0;i<sz;++i)
	{
		size++;
		LRU(&root,m,arr[i],&size);
	}
	print(root);
	

	getchar();
	return 0;
}
