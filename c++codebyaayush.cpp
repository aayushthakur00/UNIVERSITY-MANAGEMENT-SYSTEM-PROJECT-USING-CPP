#include<iostream>
#include<conio.h>
#include<fstream>
#include<string.h>
#include<sstream>
using namespace std;
class student;
class admin{
		char fpass[10];
		int UID;
		string fpassword;
	public:
		void ainput();
		void forgot();//To be added inside input.
		void create_task();//declare task as protected using inherit.
		void assign_task();//(With date)1.To individual  2.To all
			void allstudents();
			void singlestudent();
		void update_task();//1.To individual  2.To all
		void delete_task();
		void display_submission();//create a file with task submissions of students.
};

class student{
	int regno;
	string spassword;
	char s[10];
	string name;
		public:
			void sinput();
			void forgot();//To be added inside input.
			void view_task();
			void submit_task();
			void check_date();//date in dd-mm-yy using date structure of c++.
};

void admin::ainput()
{
	cout<<"\n\n\t\tWelcome Dear Faculty"<<endl;
	cout<<"\n\t\tEnter the UID\n\n\t\t->";
	cin>>UID;
	cout<<"\n\t\tEnter the password\n\n\t\t->";
	char s[10];
	int i;
	for(i=0;i<10;i++)

	string Fpass(s);
	
	cin>>fpassword;
	fstream file;
	file.open("faculty.txt");
	if(!file)
	{
		cout<<"\n\t\t!Error "<<endl;
	}
	int id;
	char pass[20];
	file>>id;
	while(file.eof()==0)
	{
		file.getline(pass,20);
	}
	if( fpassword == pass)
	{
		if(UID == id)
		{
		cout<<"\n\t\t---------------Successfully LoggedIn---------------";
		cin.ignore();
		create_task();
		}
	}
	else
	{
		cout<<"\n\n\t\txx-!Wrong details-xx."<<endl;
		cout<<"\n\t\tForgot Password?(Y/N)\n\t\t->";
		char ch;
		cin>>ch;
		if(ch=='Y'||ch=='y')
		{
			forgot();
		}
		
	}
}

void admin::create_task()//create an infinite loop for giving task.
{
	y:
	static int m=0;
	m++;
	cout<<"\n\n\t\t\t\tCreating TASK\n";
	
	cout<<"\n\t\t\t--------Enter the task "<<m<<"--------\n\t\t\t->"; 
	char task[20];
	cin.getline(task,20);
	fstream fout;
	fout.open("Task.txt",ios::out|ios::in|ios::app);
	if(!fout)
	{
		cout<<"\n\t\t\tError Opening File Task";
		exit(1);
	}
	fout<<m<<" ";
	fout.write((char *)&task,sizeof(task));
	
	cout<<"\n\n\n\t\t\tTask "<<m<<" Created Successfully."<<endl;
	cout<<"\n\n\t\t\tDo you want to create Another task?(Y/N)"<<endl;
	char ch;
	cin>>ch;
	if(ch=='Y'||ch=='y')
	{
		cin.ignore();
		goto y;
	}
	else
	{
	fout.close();
	h:
	cout<<"\n\t\t1.Assign Task\n\t\t2.Update Task\n\t\t3.Delete Task"<<endl;
	int z;
	cin>>z;
	switch(z)
	{
		case 1:assign_task();break;
		case 2:update_task();break;
		case 3:delete_task();break;
		default:{
			cout<<"\n\t\tNo such Option"<<endl;
			goto h;
			break;
		}
	}
	}
}

void admin::assign_task()//File will be created against regno.
{
	cout<<"\n\n\t\t   ----------------Assigning Tasks---------------------   "<<endl;
	y:cout<<"\n\t\t1.Assign Task To All Students.\n\t\t2.Assign Task to a single student.\n\t\t->"<<endl;
	int n;
	cin>>n;
	switch(n)
	{
		case 1: allstudents();cin.ignore();break;
		case 2: singlestudent();break;
		default: 
		{
			cout<<"\n\t\tNo such Option.";
			goto y;
		}
	}
}

void admin::allstudents()
{
	cout<<"\n\t\tAssigning Task to All students";
	
	int regno;
	int i=70;
	char ch;
	char ques[02];
	ifstream fin;
	ofstream fnew;
	fin.open("Task.txt");
	fnew.open("TaskAll.txt",ios::out|ios::app);
	fin.read((char *)&ques,sizeof(ques));
	
	ch=fin.get();
	while(fin.eof()==0)
    {
    	fnew.put(ch);
    	ch=fin.get();
    }
	
	fnew.close();
	fin.close();
}

void admin::singlestudent()
{
	string reg;
	cout<<"\n\t\tEnter the Regestration number of the student.\n\t\t->"<<endl;
	cin>>reg;
	
	ifstream fin;
	fin.open("Regno.txt");
	
	ofstream fout;
	
	ifstream file;
	file.open("Task.txt");
	char ques[80];
	file.getline(ques,80);
	file.close();
	
	int oreg;
	while(fin.eof()==0)
	{
		fin>>oreg;
		ostringstream str;
		str<<oreg;
		string regno1 = str.str();
		
		if(regno1==reg)
		{
			cout<<"Hello";
			regno1.append(".txt");
			const char* filename = regno1.c_str();
			cout<<"\n\t\t\t<--Regno. Matched-->\n\t\t\t";
			fout.open(filename,ios::out);
			fout<<ques[80];
			fout.close();
		}
	}
	fin.close();
		
}

void admin::update_task()
{
	char uques[80];
	cout<<"\n\n\t\t----------UPDATE TASK------------\n";
	ifstream rfile;
	rfile.open("Task.txt",ios::in);
	ofstream ufile;
	ufile.open("Utask.txt",ios::out);
	int len=0;
	rfile.seekg(0,ios::end);
	len=rfile.tellg();
	rfile.seekg(0,ios::beg);
	int n;
	cout<<"\n\t\tEnter the task which you want to UPDATE"<<endl;
	cin>>n;
	int num;
	while(len>0)
	{
		len=len-sizeof(class admin);
		rfile>>num;
		if(num==n)
		{
			cout<<"\n\t\tEnter the task";
			cin.getline(uques,sizeof(uques));
			ufile.write((char *)&uques,sizeof(uques));
			cout<<"\n\t\tUpdating Task"<<n<<endl;
		}
	}
	rfile.close();
	ufile.close();
	remove("Task.txt");
	rename("Utask.txt","Task.txt");
	cout<<"\n\t\tAssigning the Updated Task"<<endl;
	assign_task();
	
}

void admin::delete_task()
{
	
	cout<<"\n\t\t------------Deleting Tasks-----------"<<endl;
	fstream file;
	file.open("Task.txt",ios::out);
	file.close();
	cout<<"\n\t\tTasks Deleted"<<endl;
}
void admin::forgot()
{
	//Yet to be written.
}

void student::sinput()
{
	cout<<"\n\t\t\t\t------Welcome student--------"<<endl;
	cout<<"\n\t\tEnter the REGESTRATION ID\n\n\t\t->";
	cin>>regno;
	cout<<"\n\t\tEnter the password\n\n\t\t->";
	


	string Spass(s);
	
	cin>>spassword;
	fstream fin;
	fin.open("students.txt");
	int reg;
	string pass;
	char name[25];
	fin>>reg;
	fin>>pass;
	while(fin.eof()==0)
	{
	fin.getline(name,25);
	}
	if(regno==reg)
	{
		if(pass==spassword)
		{
		cout<<"\n\t\t----------You Are successfully LoggedIn-----------\n\t\t"<<endl;
		cout<"\n\t\tYour Details:-\n";
		cout<<"\n\t\tName"<<"                      "<<"Regno.\n"<<endl;
		cout<<"\n\t\t"<<name<<"                 "<<regno<<endl;
		
		y:cout<<"\n\t\t1)View Task\n\n\t\t2)Submit Task";
		int n;
		cout<<"\n\t\t";
		cin>>n;
		switch(n)
		{
			case 1:view_task();break;
			//case 2:submit_task();break;
			default:{
				cout<<"\n\t\tNo such options";
				goto y;
				break;
			}
		}
		view_task(); 
		}
	}
	else
	{
		cout<<"\n\n\t\txx-!Wrong details-xx."<<endl;
		cout<<"\n\t\tForgot Password?(Y/N)\n\t\t->";
		char ch;
		cin>>ch;
		if(ch=='Y'||ch=='y')
		{
			forgot();
		}     
	}    
}

void student::forgot()
{
	//To be written
}

void student::view_task()
{
	cout<<"\n\t\t---------------Viewing Task------------";
	cout<<"\n\n\t\tYour regestration number is:"<<regno<<endl;
	ifstream fall;
	ifstream fsin;
	
	char ques[80];
	char ch;
	
	fall.open("D:\books\Projects\C++\Code\New folder\TaskAll.txt",ios::in);
	if(!fall)
	{
		
		cout<<"\n\t\tThe Task Assigned to you is:-"<<endl;
		fall.read((char *)ques,sizeof(ques));
		cout<<ques;
		cin.ignore();
	}
	else
	{
	int oreg;
	oreg=regno;
	ostringstream str;
	str<<oreg;
	string oreg1 = str.str();
	
	oreg1.append(".txt");
	
	const char* filename = oreg1.c_str();
	fsin.open(filename,ios::in);
	fsin.read((char *)ques,sizeof(ques));
	cout<<"\n\tThe task Assigned to you is:-\n\t";
	cout<<"\n\t"<<ques<<endl;
	}
	fall.close();
	fsin.close();
	exit(1);
}



int main()
{
	admin a;
	student s;
	cout<<"\t\t\t\t-------------------------";
	cout<<"\n\t\t\t\t|     Class Calendar    |";
	cout<<"\n\t\t\t\t-------------------------\n";
	int n;
	cout<<"--------------------------------------------------------------------------------\n"<<endl;
	cout<<"\n\n\t\tSelect\n\t\t1.Faculty\n\t\t2.Student\n\n\t\t";
	cin>>n;
	if(n==1)
	{
		a.ainput();
	}
	else if(n==2)
	{
		s.sinput();
	}
	else
	{
		cout<<"\n\n\t\tPlease Choose Correct Option.";
	}
}
