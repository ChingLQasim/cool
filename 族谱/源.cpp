#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string>
using namespace std;
//---------------------------
int i = 0;//�����ȡλ��
//---------------------------

//�����Ա������Ϣ�ṹ��
struct member
{
	char name[21] = { 0 };             //�����Ա������
	int age = 0;                 //��Ա������
	bool  engage = 0;			//��Ա�Ƿ��ѻ飺0����δ�飬1�����ѻ�
	bool exist = 1;				//��Ա�Ƿ��ڣ�0�������ţ�1��������
	int birthdate = 0;			//��Ա�ĳ�������
	int deathdate = 0;			//��Ա���������ڣ�����ֵΪ0����ó�Աδ����
	char location[1000] = { 0 };		//��Ա�ļ�ͥסַ
	int flag = 1;				//�ó�Ա�Ƿ����
};

//�����ݽṹ__�����ֵ���__�������׹�ϵ
struct node
{
	member data;           //�洢�����Ա��Ϣ
	struct node* chi = NULL;      //�����֧
	struct node* bro = NULL;      //�ֵܷ�֧
};

//------------------------------------------
member group[100];//�洢������Ϣ����
//------------------------------------------

//��ʽ�������ݽṹ-----------------------
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
//�����йغ���
int InitQueue(LinkQueue& Q)					//��ʼ������
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

int DestroyQueue(LinkQueue& Q)			//���ٶ���
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

int EnQueue(LinkQueue& Q, node* e)			//����
{
	LNode* pNew = new LNode;
	pNew->data = e;
	Q.rear->next = pNew;
	Q.rear = pNew;
	Q.rear->next = NULL;
	return 0;
}

int DeQueue(LinkQueue& Q, node* &e)			//����
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

int QueEmp(LinkQueue Q)		//�ж������Ƿ�Ϊ��
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

void QueueTraverse(LinkQueue Q)//��������
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

//�����������봴�������ֵ���

int Create(node*& T)
{
	member person = group[i];//��������������׵���Ϣ������
	if (person.flag == 8)//���һ��ֹͣ��Ϣ
	{
		return 0;
	}
	if (person.flag == 0 || person.deathdate == 1)//��־Ϊ0������������Ϊ1���ʾ����ϢΪ��
	{
		T = NULL;
	}
	else
	{
		T = new node;
		for (int j = 0; j < 21; j++)									//����������Ϣ
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
		T->data.flag = person.flag;								//����������Ϣ
		i++;																	//ʹ��ȡ��Ϣ������һλ
		Create(T->chi);												//���ȴ���������֦
		i++;																	//ʹ��ȡ��Ϣ������һλ
		Create(T->bro);												//�����꺢����֦�󴴽��ֵ���֦
	}
	return 0;
}

//���ں���ɾ�������ֵ���
void DestroyTree(node*& T)
{
	if (T)
	{
		DestroyTree(T->chi);//ɾ������
		DestroyTree(T->bro);//ɾ���ֵ�
		delete T;//�ͷ�ָ����ָ��ռ�
		T = NULL;//��ָ��ָ���
	}
}

//���ÿһ���˵�����
int Travse(node* T, int i)
{
	int temp = 0;
	node* p = T, * head;
	LNode *walker;
	if (i == 0)
	{
		cout << "�����������������룡"<<endl;
		return 0;
	}
	if (i == 1)
	{
		cout << T->data.name << endl;
		return 0;
	}
	LinkQueue Q;
	InitQueue(Q);
	EnQueue(Q, p);//���������ڽ���
	while (!QueEmp(Q))
	{
		i--;													//���������ֱ��1��Ϊ�������
		EnQueue(Q, NULL);
		walker = Q.front->next;
		while (walker ->data!= NULL)			//����һ������
		{
			head = walker->data;
			if (head->chi!=NULL)
			{
				EnQueue(Q, head->chi);			//��һ�����ӽ��ӣ���ô�����ֵܾ���ͬһ����
				node* temp2=head->chi;
				while (temp2->bro != NULL)
				{
					EnQueue(Q, temp2->bro);
					temp2 = temp2->bro;
				}
			}
			walker = walker->next;
		}														//��һ��ȫ������
		walker = Q.front->next;
		head = walker->data;
		while (head != NULL)
		{
			DeQueue(Q,head);						//��һ������
		}
		if (i == 1)
		{
			QueueTraverse(Q);						//�������������һ����
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
//Ѱ���ض��ļ����Ա
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
//Ѱ�Ҹ���
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
					cout << "������Ϣ���£�" << endl;
					cout << "����" << head->data.name << endl;
					cout << "���䣺" << head->data.age << endl;
					cout << "�������ڣ�" << head->data.birthdate << endl;
					cout << "����״����";
					if (head->data.engage == 1)
					{
						cout << "�ѻ飻" << endl;
					}
					else
					{
						cout << "δ�飻" << endl;
					}
					cout << "��ס��ַ��" << head->data.location << endl;
					DestroyQueue(Q);
					return 1;
				}
				while (temp2->bro != NULL)
				{
					if (string(temp2->data.name) == string(m))
					{
						cout << "������Ϣ���£�" << endl;
						cout << "����" << head->data.name << endl;
						cout << "���䣺" << head->data.age << endl;
						cout << "�������ڣ�" << head->data.birthdate << endl;
						cout << "����״����";
						if (head->data.engage == 1)
						{
							cout << "�ѻ飻" << endl;
						}
						else
						{
							cout << "δ�飻" << endl;
						}
						cout << "��ס��ַ��" << head->data.location << endl;
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
//�������
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
//Ѱ��Ҫɾ������֦
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
//��֦ɾ��Ѱ��ĸ֦
int zhi = -1;//�жϺ��ӻ����ֵ�,1Ϊ���ӣ�0���ֵܣ���ʼ��Ϊ-1
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
//ɾ����֦����
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
//Ѱ����һ��
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
//Ѱ������
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
	return 0;//n����m������
}
//Ѱ�ҹ�ͬ����
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
//Ѱ���ֵ�
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
	while (!file.eof())//��ȡ�����ļ�����������Ϣ����һ��������
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
		cout << "1.����������ף�" << endl;
		cout << "2.��ѯ�����Ա��" << endl;
		cout << "3.��ʾĳһ���˵�ȫ����Ϣ��"<<endl;
		cout << "4.��ѯ���˹�ϵ��" << endl; 
		cout << "5.ɾ��ĳ����Ա��Ϣ��" << endl; 
		cout << "6.���ĳ����Ա��Ϣ��" << endl;
		cout << "7.������" << endl;
		cout << "�������ϲ���֮ǰ�Ĵ�����ɲ�������Ĳ����ǣ�";
		cin >> chioce1;
		chioce=atoi(chioce1);
		if (chioce < 1 || chioce>7)
		{
			cout << "�������ѡ���ðɣ�" << endl;
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
			cout << "����������Ա��������";
			cin >> m;
			this_man=search_person(people, m);
			if (this_man==NULL)
			{
				cout << "û������ˣ�" << endl;
			}
			else
			{
				cout << this_man->data.name << "��Ϣ����:" << endl;
				if (this_man->data.deathdate != 0)
				{
					cout << " ���䣺" << this_man->data.age << endl;
					cout << " �������ڣ�" << this_man->data.birthdate << endl;
					cout << " ����״����";
					if (this_man->data.engage == 1)
					{
						cout << " �ѻ�" << endl;
					}
					else
					{
						cout << " δ��" << endl;
					}
					cout << " ��ס��ַ��" << this_man->data.location << endl;
				}
				cout << m << "*���ӵ���Ϣ��" << endl;
				if (this_man ->chi!= NULL)
				{
					cout << "   ����:" << this_man->chi->data.name<<endl;
					cout << "   ���䣺" << this_man->chi->data.age << endl;
					cout << "   �������ڣ�" << this_man->chi->data.birthdate << endl;
					cout << "   ����״����";
					if (this_man->chi->data.engage == 1)
					{
						cout << "�ѻ�" << endl;
					}
					else
					{
						cout << "δ��" << endl;
					}
					cout << "    ��ס��ַ��" << this_man->chi->data.location << endl;
					node* wk=this_man->chi->bro;
					while (wk != NULL)
					{
						cout << "   ����:" <<wk->data.name << endl;
						cout << "   ���䣺" << wk->data.age << endl;
						cout << "   �������ڣ�" << wk->data.birthdate << endl;
						cout << "   ����״����";
						if (wk->data.engage == 1)
						{
							cout << "�ѻ�" << endl;
						}
						else
						{
							cout << "δ��" << endl;
						}
						cout << "   ��ס��ַ��" << wk->data.location << endl;
						wk = wk->bro;
					}
				}
				else
				{
					cout << "û�к��ӣ�"<<endl;
				}
				if (string(m)==string(people->data.name))
				{
					cout << "�������ڣ�"<<endl;
				}
				else
				{
					node* ptr;
					ptr=search_person(people,find_father(people, m)->data.name);
					cout << "*������Ϣ��" << endl;
					cout << "   ����:" << ptr->data.name << endl;
					cout << "   ���䣺" << ptr->data.age << endl;
					cout << "   �������ڣ�" << ptr->data.birthdate << endl;
					cout << "   ����״����";
					if (ptr->data.engage == 1)
					{
						cout << "�ѻ�" << endl;
					}
					else
					{
						cout << "δ��" << endl;
					}
					cout << "   ��ס��ַ��" << ptr->data.location << endl;
				}
			}
			continue;
		}
		else if (chioce == 3)
		{
			int number;
			cout << "�������뿴�ڼ�����:";
			cin >> number;
			cout << "�����ǵ�" << number << "��ȫ����Ա" << endl;
			Travse(people, number);
			continue;
		}
		else if (chioce == 4)
		{
			char a[21] = { 0 }, b[21] = { 0 };
			cout << "�������һ���˵�������";
			cin >> a;
			cout << "������ڶ����˵�������";
			cin >> b;
			if (search_person(people, a) == NULL)
			{
				cout << "û������ˣ�";
				continue;
			}
			if (search_person(people, b) == NULL)
			{
				cout << "û������ˣ�";
				continue;
			}
			
			if (string(a) == string(b))
			{
				cout << "������ͬһ���ˣ�"<< endl;
				continue;
			}
			cout << "���ǵĹ�ͬ����Ϊ��";			
			cout << find_anst(people, a, b)->data.name<<endl;
			int temp_flag = find_bro(people, a, b);
			if(temp_flag ==1)
			{
				cout << "�������ֵ�" << endl;
				continue;
			}
			else
			{
				int link_two = find_chi(people, a, b);
				if ( link_two== 1)
				{
					cout << a << "��" << b << "����" << endl;
				}
				if (link_two == 2)
				{
					cout << a << "��" << b << "����" << endl;
				}
				if (link_two == 0)
				{
					int link_two2 = find_chi(people, b, a);
					if (link_two2 == 1)
					{
						cout << b << "��" << a << "����" << endl;
					}
					if (link_two2 == 2)
					{
						cout << b<< "��" << a << "����" << endl;
					}
				}
			}
			continue;
		}
		else if (chioce == 5)
		{
			char delname[21]={0};
			cout << "��������Ҫɾ����������";
			cin >> delname;
			deletemember(people, delname);
			cout << "ɾ����ɣ�" << endl;
			continue;
		}
		else if (chioce == 6)
		{
			char new_name[21],old_name[21];
			cout << "������������ӵ��ˣ�";
			cin >> new_name;
			cout << "����������˭�ĺ��ӣ�";
			cin >> old_name;
			if (search_person(people, old_name) == NULL)
			{
				cout << "û������ˣ�";
				continue;
			}
			cout << "����������˵����䣺";
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
				cout << "��������˵����գ�";
				cin >> new_per->data.birthdate;
				cin.ignore();
				cout << "���";
				cin >> new_per->data.engage;
				cin.ignore();
				cout << "��ַ��";
				cin >> new_per->data.location;
				cin.ignore();
				cout << "�Ƿ��ڣ�";
				cin >> new_per->data.exist;
				cin.ignore();
				if (new_per->data.exist != 0)
				{
					cout << "�������������ڣ�";
					cin >> new_per->data.deathdate;
				}
				old_per->chi = new_per;
				cout << "��ӳɹ���" << endl;
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
				cout << "��������˵����գ�";
				cin >> new_per->data.birthdate;
				cin.ignore();
				cout << "���";
				cin >> new_per->data.engage;
				cin.ignore();
				cout << "��ַ��";
				cin >> new_per->data.location;
				cin.ignore();
				cout << "�Ƿ��ڣ�";
				cin >> new_per->data.exist;
				cin.ignore();
				if (new_per->data.exist == 0)
				{
					cout << "�������������ڣ�";
					cin >> new_per->data.deathdate;
				}
				old_per->bro= new_per;
				cout << "��ӳɹ���" << endl;
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