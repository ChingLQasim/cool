#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string>
using namespace std;
//---------------------------
int i = 0;//数组读取位置
//---------------------------

//家族成员各项信息结构体
struct member
{
	char name[21] = { 0 };             //家族成员的姓名
	int age = 0;                 //成员的年龄
	bool  engage = 0;			//成员是否已婚：0代表未婚，1代表已婚
	bool exist = 1;				//成员是否健在：0代表已逝，1代表在世
	int birthdate = 0;			//成员的出生日期
	int deathdate = 0;			//成员的死亡日期，若该值为0，则该成员未死亡
	char location[1000] = { 0 };		//成员的家庭住址
	int flag = 1;				//该成员是否存在
};

//以数据结构__孩子兄弟树__建立族谱关系
struct node
{
	member data;           //存储家族成员信息
	struct node* chi = NULL;      //子孙分支
	struct node* bro = NULL;      //兄弟分支
};

//------------------------------------------
member group[100];//存储家族信息数组
//------------------------------------------

//链式队列数据结构-----------------------
typedef struct LNode
{
	node* data;
	struct LNode* next;
}LNode, * QueuePtr;
typedef struct LinkQueue
{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;
//队列有关函数
int InitQueue(LinkQueue& Q)					//初始化队列
{
	Q.front = Q.rear = new LNode;
	if (Q.front == NULL)
	{
		cout << "Init fall!" << endl;
		exit(-1);
	}
	Q.front->next = NULL;
	return 0;
}

int DestroyQueue(LinkQueue& Q)			//销毁队列
{
	LNode* p;
	while (Q.front->next != NULL)
	{
		p = Q.front->next;
		Q.front->next = p->next;
		delete p;
	}
	delete Q.front;
	Q.front = NULL;
	Q.rear = NULL;
	return 0;
}

int EnQueue(LinkQueue& Q, node* e)			//进队
{
	LNode* pNew = new LNode;
	pNew->data = e;
	Q.rear->next = pNew;
	Q.rear = pNew;
	Q.rear->next = NULL;
	return 0;
}

int DeQueue(LinkQueue& Q, node* &e)			//出队
{
	if (Q.front->next == NULL)
	{
		cout << "Queue dosen't exsit!" << endl;
		exit(-1);
	}
	if (Q.front == Q.rear)
	{
		cout << "Queue is empty!" << endl;
		return 0;
	}
	LNode* p;
	p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if (Q.rear == p)
	{
		Q.rear = Q.front;
	}
	delete p;
	return 0;
}

int QueEmp(LinkQueue Q)		//判定队列是否为空
{
	if (Q.front == Q.rear)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void QueueTraverse(LinkQueue Q)//遍历队列
{
	LNode* p;
	p = Q.front->next;
	while (p != NULL)
	{
		cout << p->data->data.name << ",";
		p = p->next;
	}
	cout <<"."<< endl;
}

//利用先序输入创建孩子兄弟树

int Create(node*& T)
{
	member person = group[i];//传入存有整个家谱的信息的数组
	if (person.flag == 8)//最后一个停止信息
	{
		return 0;
	}
	if (person.flag == 0 || person.deathdate == 1)//标志为0或者死亡日期为1则表示此信息为空
	{
		T = NULL;
	}
	else
	{
		T = new node;
		for (int j = 0; j < 21; j++)									//保存数组信息
		{
			T->data.name[j] = person.name[j];
		}
		T->data.age = person.age;
		T->data.birthdate = person.birthdate;
		T->data.engage = person.engage;
		T->data.exist = person.exist;
		T->data.deathdate = person.deathdate;
		for (int j = 0; j < 100; j++)
		{
			T->data.location[j] = person.location[j];
		}
		T->data.flag = person.flag;								//保存数组信息
		i++;																	//使读取信息移至下一位
		Create(T->chi);												//优先创建孩子子枝
		i++;																	//使读取信息移至下一位
		Create(T->bro);												//创建完孩子子枝后创建兄弟子枝
	}
	return 0;
}

//基于后序删除孩子兄弟树
void DestroyTree(node*& T)
{
	if (T)
	{
		DestroyTree(T->chi);//删除孩子
		DestroyTree(T->bro);//删除兄弟
		delete T;//释放指针所指向空间
		T = NULL;//将指针指向空
	}
}

//输出每一代人的姓名
int Travse(node* T, int i)
{
	int temp = 0;
	node* p = T, * head;
	LNode *walker;
	if (i == 0)
	{
		cout << "输入有误，请重新输入！"<<endl;
		return 0;
	}
	if (i == 1)
	{
		cout << T->data.name << endl;
		return 0;
	}
	LinkQueue Q;
	InitQueue(Q);
	EnQueue(Q, p);//先让老祖宗进队
	while (!QueEmp(Q))
	{
		i--;													//计算代数，直到1即为所求代数
		EnQueue(Q, NULL);
		walker = Q.front->next;
		while (walker ->data!= NULL)			//让下一代进队
		{
			head = walker->data;
			if (head->chi!=NULL)
			{
				EnQueue(Q, head->chi);			//第一个孩子进队，那么他的兄弟就是同一代人
				node* temp2=head->chi;
				while (temp2->bro != NULL)
				{
					EnQueue(Q, temp2->bro);
					temp2 = temp2->bro;
				}
			}
			walker = walker->next;
		}														//下一代全部进队
		walker = Q.front->next;
		head = walker->data;
		while (head != NULL)
		{
			DeQueue(Q,head);						//上一代出队
		}
		if (i == 1)
		{
			QueueTraverse(Q);						//遍历队列输出这一代人
		}
	}
	DestroyQueue(Q);
	return 0;
}

int PreOrderTraverse(node*T)
{
	if (T != NULL)
	{
		PreOrderTraverse(T->chi);
		PreOrderTraverse(T->bro);
	}
	else
	{
		cout << "#" << endl;
	}
	return 0;
}
//寻找特定的家族成员
node* search_person(node* T, char* m)
{
	LinkQueue Q;
	node* e;
	InitQueue(Q);
	EnQueue(Q, T);
	if (string(m) == string(Q.front->next->data->data.name))
	{
		return Q.front->next->data;
	}
	while (!QueEmp(Q))
	{
		if (Q.front->next->data->chi != NULL)
		{
			if (string(m) == string(Q.front->next->data->chi->data.name))
			{
				return Q.front->next->data->chi;
			}
			EnQueue(Q, Q.front->next->data->chi);
		}
		if (Q.front->next->data->bro != NULL)
		{
			if (string(m) == string(Q.front->next->data->bro->data.name))
			{
				return Q.front->next->data->bro;
			}
			EnQueue(Q, Q.front->next->data->bro);
		}
		DeQueue(Q, e);
	}
	DestroyQueue(Q);
	return NULL;
}
//寻找父辈
int search_person_father(node* T, char* m)									
{
	node* p = T, * head;
	LNode* walker;
	LinkQueue Q;
	InitQueue(Q);
	EnQueue(Q, p);
	while (!QueEmp(Q))
	{												
		EnQueue(Q, NULL);
		walker = Q.front->next;
		while (walker->data != NULL)			
		{
			head = walker->data;
			if (head->chi != NULL)
			{
				EnQueue(Q, head->chi);			
				node* temp2 = head->chi;
				if (string(temp2->data.name) == string(m))
				{
					cout << "父辈信息如下：" << endl;
					cout << "姓名" << head->data.name << endl;
					cout << "年龄：" << head->data.age << endl;
					cout << "出生日期：" << head->data.birthdate << endl;
					cout << "婚姻状况：";
					if (head->data.engage == 1)
					{
						cout << "已婚；" << endl;
					}
					else
					{
						cout << "未婚；" << endl;
					}
					cout << "居住地址：" << head->data.location << endl;
					DestroyQueue(Q);
					return 1;
				}
				while (temp2->bro != NULL)
				{
					if (string(temp2->data.name) == string(m))
					{
						cout << "父辈信息如下：" << endl;
						cout << "姓名" << head->data.name << endl;
						cout << "年龄：" << head->data.age << endl;
						cout << "出生日期：" << head->data.birthdate << endl;
						cout << "婚姻状况：";
						if (head->data.engage == 1)
						{
							cout << "已婚；" << endl;
						}
						else
						{
							cout << "未婚；" << endl;
						}
						cout << "居住地址：" << head->data.location << endl;
						DestroyQueue(Q);
						return 1;
					}
					EnQueue(Q, temp2->bro);
					temp2 = temp2->bro;
				}
			}
			walker = walker->next;
		}														
		walker = Q.front->next;
		head = walker->data;
		while (head != NULL)
		{
			DeQueue(Q, head);						
		}
	}
	DestroyQueue(Q);
	return 0;
}
//计算代数
int depth(node* T)
{
	int temp = 1;
	node* p = T, * head;
	LNode* walker;
	LinkQueue Q;
	InitQueue(Q);
	EnQueue(Q, p);
	while (!QueEmp(Q))
	{
		temp++;
		EnQueue(Q, NULL);
		walker = Q.front->next;
		while (walker->data != NULL)			
		{
			head = walker->data;
			if (head->chi != NULL)
			{
				EnQueue(Q, head->chi);			
				node* temp2 = head->chi;
				while (temp2->bro != NULL)
				{
					EnQueue(Q, temp2->bro);
					temp2 = temp2->bro;
				}
			}
			walker = walker->next;
		}														
		walker = Q.front->next;
		head = walker->data;
		while (head != NULL)
		{
			DeQueue(Q, head);						
		}
	}
	DestroyQueue(Q);
	return temp;
}
//寻找要删除的子枝
node* contract=NULL;
node* visit(node* T, char* m)
{
	if (T != NULL)
	{
		if (string(T->data.name) == string(m))
		{
			contract = T;
			return contract;
		}
		visit(T->chi,m);
		visit(T->bro,m);
	}
	return contract;
}
//子枝删除寻找母枝
int zhi = -1;//判断孩子还是兄弟,1为孩子，0是兄弟，初始化为-1
node* visit_fa(node* T, char* m)
{
	LinkQueue Q;
	node* e;
	InitQueue(Q);
	EnQueue(Q, T);
	while (!QueEmp(Q))
	{
		if (Q.front->next->data->chi != NULL)
		{
			if (string(m) == string(Q.front->next->data->chi->data.name))
			{
				zhi = 1;
				return Q.front->next->data;
			}
			EnQueue(Q, Q.front->next->data->chi);
		}
		if (Q.front->next->data->bro != NULL)
		{
			if (string(m) == string(Q.front->next->data->bro->data.name))
			{
				zhi = 0;
				return Q.front->next->data;
			}
			EnQueue(Q, Q.front->next->data->bro);
		}
		DeQueue(Q,e);
	}
	DestroyQueue(Q);
	return NULL;
}
//删除子枝函数
int deletemember(node* T, char* m)
{
	node* p,*q;
	p = visit(T, m);
	q = visit_fa(T, m);
	if (zhi == 1)
	{
		q->chi = p->bro;
	}
	else
	{
		q->bro = p->bro;
	}
	p->bro = NULL;
	DestroyTree(p);
	zhi = -1;
	contract = NULL;
	return 0;
}
//寻找上一代
node* find_father(node* T, char* m)
{
	LinkQueue Q;
	node* e;
	LNode* walker;
	InitQueue(Q);
	EnQueue(Q, T);
	if (string(Q.front->next->data->data.name) ==string(m))
	{
		return Q.front->next->data;
	}
	while (!QueEmp(Q))
	{
		if (Q.front->next->data->chi != NULL)
		{
			if (string(m) == string(Q.front->next->data->chi->data.name))
			{
				return Q.front->next->data;
			}
			node* p=Q.front->next->data->chi;
			while (p ->bro!= NULL)
			{
				if (string(m) == string(p->bro->data.name))
				{
					return Q.front->next->data;
				}
				if (p->bro != NULL)
				{
					EnQueue(Q, p->bro);
				}
				p = p->bro;
			}
			if (Q.front->next->data->chi != NULL)
			{
				EnQueue(Q, Q.front->next->data->chi);
			}
		}
		DeQueue(Q, e);
	}
	DestroyQueue(Q);
	return NULL;
}
//寻找子孙
int find_chi(node* T, char* m, char* n)
{
	LinkQueue Q;
	node* e;
	InitQueue(Q);
	T = search_person(T, m);
	EnQueue(Q, T);
	while (!QueEmp(Q))
	{
		if (Q.front->next->data->chi != NULL)
		{
			if (string(Q.front->next->data->chi->data.name) == string(n))
			{
				return 1;
			}
			EnQueue(Q, Q.front->next->data->chi);
		}
		if (Q.front->next->data->bro != NULL&& Q.front->next->data!=T)
		{
			if (string(Q.front->next->data->bro->data.name) == string(n))
			{
				return 2;
			}
			EnQueue(Q, Q.front->next->data->bro);
		}
		DeQueue(Q, e);
	}
	DestroyQueue(Q);
	return 0;//n不是m的子孙
}
//寻找共同祖先
node* find_anst(node* T, char* m, char* n)
{
	string st1 = string(m);
	string st2 = string(n);
	while (1)
	{
		if (st1== st2)
		{
			return NULL;
		}
		node* con_one,*con_two;
		con_one = find_father(T, m);
		con_two = find_father(T, n);
		if ( con_one==con_two )
		{
			return con_one;
		}
		else
		{
			m = con_one->data.name;
			n = con_two->data.name;
			st1 = string(con_one->data.name);
			st2 = string(con_two->data.name);
		}
	}
	return NULL;
}
//寻找兄弟
int find_bro(node* T, char* m, char* n)
{
	node* p=search_person(T,m), *q=search_person(T,n);
	while (p->bro != NULL)
	{
		if (string(p->bro->data.name) == string(n))
		{
			return 1;
		}
		p = p->bro;
	}
	while (q->bro != NULL)
	{
		if (string(q->data.name) == string(m))
		{
			return 1;
		}
		q = q->bro;
	}
	return NULL;
}
int main()
{
	node *people=new node;
	fstream file;
	member person;
	int num = 0;
	file.open("data.dat", ios::in | ios::binary);
	file.read((char*)&person, sizeof(person));  
	while (!file.eof())//读取整个文件，将家族信息填入一个数组中
	{  
		for (int i = 0; i < 21; i++)
		{
			group[num].name[i] = person.name[i];
				
		}
		group[num].age = person.age;
		group[num].birthdate = person.birthdate;
		group[num].engage = person.engage;
		group[num].exist = person.exist;
		group[num].deathdate = person.deathdate;
		for (int i = 0; i < 100; i++)
		{
			group[num].location[i]= person.location[i];
		}
		group[num].flag = person.flag;
		file.read((char*)&person, sizeof(person));
		num++;
	}
	file.close();
	group[num].flag = 8;
	Create(people);
	int chioce=0;
	char chioce1[21];
	while (1)
	{
		cout << endl;
		cout << "-----------------------------------------------------" << endl;
		cout << "1.输出整个家谱；" << endl;
		cout << "2.查询家族成员；" << endl;
		cout << "3.显示某一代人的全部信息；"<<endl;
		cout << "4.查询两人关系；" << endl; 
		cout << "5.删除某个成员信息；" << endl; 
		cout << "6.添加某个成员信息；" << endl;
		cout << "7.结束；" << endl;
		cout << "输入以上操作之前的代号完成操作，你的操作是：";
		cin >> chioce1;
		chioce=atoi(chioce1);
		if (chioce < 1 || chioce>7)
		{
			cout << "看清楚再选，好吧？" << endl;
			continue;
		}
		else if(chioce==1)
		{
			for (int i =1; i <= depth(people); i++)
			{			
				Travse(people, i);
			}
			continue;
		}
		else if (chioce == 2)
		{
			char m[21] = {0};
			int flag = 0;
			node* this_man;
			cout << "请输入家族成员的姓名：";
			cin >> m;
			this_man=search_person(people, m);
			if (this_man==NULL)
			{
				cout << "没有这号人！" << endl;
			}
			else
			{
				cout << this_man->data.name << "信息如下:" << endl;
				if (this_man->data.deathdate != 0)
				{
					cout << " 年龄：" << this_man->data.age << endl;
					cout << " 出生日期：" << this_man->data.birthdate << endl;
					cout << " 婚姻状况：";
					if (this_man->data.engage == 1)
					{
						cout << " 已婚" << endl;
					}
					else
					{
						cout << " 未婚" << endl;
					}
					cout << " 居住地址：" << this_man->data.location << endl;
				}
				cout << m << "*孩子的信息：" << endl;
				if (this_man ->chi!= NULL)
				{
					cout << "   姓名:" << this_man->chi->data.name<<endl;
					cout << "   年龄：" << this_man->chi->data.age << endl;
					cout << "   出生日期：" << this_man->chi->data.birthdate << endl;
					cout << "   婚姻状况：";
					if (this_man->chi->data.engage == 1)
					{
						cout << "已婚" << endl;
					}
					else
					{
						cout << "未婚" << endl;
					}
					cout << "    居住地址：" << this_man->chi->data.location << endl;
					node* wk=this_man->chi->bro;
					while (wk != NULL)
					{
						cout << "   姓名:" <<wk->data.name << endl;
						cout << "   年龄：" << wk->data.age << endl;
						cout << "   出生日期：" << wk->data.birthdate << endl;
						cout << "   婚姻状况：";
						if (wk->data.engage == 1)
						{
							cout << "已婚" << endl;
						}
						else
						{
							cout << "未婚" << endl;
						}
						cout << "   居住地址：" << wk->data.location << endl;
						wk = wk->bro;
					}
				}
				else
				{
					cout << "没有孩子！"<<endl;
				}
				if (string(m)==string(people->data.name))
				{
					cout << "是老祖宗！"<<endl;
				}
				else
				{
					node* ptr;
					ptr=search_person(people,find_father(people, m)->data.name);
					cout << "*父亲信息：" << endl;
					cout << "   姓名:" << ptr->data.name << endl;
					cout << "   年龄：" << ptr->data.age << endl;
					cout << "   出生日期：" << ptr->data.birthdate << endl;
					cout << "   婚姻状况：";
					if (ptr->data.engage == 1)
					{
						cout << "已婚" << endl;
					}
					else
					{
						cout << "未婚" << endl;
					}
					cout << "   居住地址：" << ptr->data.location << endl;
				}
			}
			continue;
		}
		else if (chioce == 3)
		{
			int number;
			cout << "请输入想看第几代人:";
			cin >> number;
			cout << "下面是第" << number << "代全部成员" << endl;
			Travse(people, number);
			continue;
		}
		else if (chioce == 4)
		{
			char a[21] = { 0 }, b[21] = { 0 };
			cout << "请输入第一个人的姓名：";
			cin >> a;
			cout << "请输入第二个人的姓名：";
			cin >> b;
			if (search_person(people, a) == NULL)
			{
				cout << "没有这号人！";
				continue;
			}
			if (search_person(people, b) == NULL)
			{
				cout << "没有这号人！";
				continue;
			}
			
			if (string(a) == string(b))
			{
				cout << "他们是同一个人！"<< endl;
				continue;
			}
			cout << "他们的共同祖先为：";			
			cout << find_anst(people, a, b)->data.name<<endl;
			int temp_flag = find_bro(people, a, b);
			if(temp_flag ==1)
			{
				cout << "他们是兄弟" << endl;
				continue;
			}
			else
			{
				int link_two = find_chi(people, a, b);
				if ( link_two== 1)
				{
					cout << a << "是" << b << "父亲" << endl;
				}
				if (link_two == 2)
				{
					cout << a << "是" << b << "父辈" << endl;
				}
				if (link_two == 0)
				{
					int link_two2 = find_chi(people, b, a);
					if (link_two2 == 1)
					{
						cout << b << "是" << a << "父亲" << endl;
					}
					if (link_two2 == 2)
					{
						cout << b<< "是" << a << "父辈" << endl;
					}
				}
			}
			continue;
		}
		else if (chioce == 5)
		{
			char delname[21]={0};
			cout << "请输入想要删除的姓名：";
			cin >> delname;
			deletemember(people, delname);
			cout << "删除完成！" << endl;
			continue;
		}
		else if (chioce == 6)
		{
			char new_name[21],old_name[21];
			cout << "请输入你想添加的人：";
			cin >> new_name;
			cout << "请输入他是谁的孩子：";
			cin >> old_name;
			if (search_person(people, old_name) == NULL)
			{
				cout << "没有这号人！";
				continue;
			}
			cout << "请输入这个人的年龄：";
			node* old_per, * new_per;
			old_per = search_person(people, old_name);
			if (old_per->chi == NULL)
			{
				new_per = new node;
				for (int i = 0; i < 21; i++)
				{
					new_per->data.name[i]=new_name[i];
				}
				cin >> new_per->data.age;
				cin.ignore();
				cout << "请输入此人的生日：";
				cin >> new_per->data.birthdate;
				cin.ignore();
				cout << "婚否？";
				cin >> new_per->data.engage;
				cin.ignore();
				cout << "地址？";
				cin >> new_per->data.location;
				cin.ignore();
				cout << "是否健在？";
				cin >> new_per->data.exist;
				cin.ignore();
				if (new_per->data.exist != 0)
				{
					cout << "请输入死亡日期：";
					cin >> new_per->data.deathdate;
				}
				old_per->chi = new_per;
				cout << "添加成功！" << endl;
			}
			else
			{
				old_per = old_per->chi;
				while (old_per->bro != NULL)
				{
					old_per = old_per->bro;
				}
				new_per = new node;
				for (int i = 0; i < 21; i++)
				{
					new_per->data.name[i] = new_name[i];
				}
				cin >> new_per->data.age;
				cin.ignore();
				cout << "请输入此人的生日：";
				cin >> new_per->data.birthdate;
				cin.ignore();
				cout << "婚否？";
				cin >> new_per->data.engage;
				cin.ignore();
				cout << "地址？";
				cin >> new_per->data.location;
				cin.ignore();
				cout << "是否健在？";
				cin >> new_per->data.exist;
				cin.ignore();
				if (new_per->data.exist == 0)
				{
					cout << "请输入死亡日期：";
					cin >> new_per->data.deathdate;
				}
				old_per->bro= new_per;
				cout << "添加成功！" << endl;
			}
			continue;
		}
		else
		{
			break;
		}
	}
	DestroyTree(people);
	return 0;
}