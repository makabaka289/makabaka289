#include <bits/stdc++.h>
using namespace std;

# define Max 1000

void show()
{
	cout<<"****************"<<endl;
	cout<<"*****1.添加*****"<<endl;
	cout<<"*****2.显示*****"<<endl;
	cout<<"*****3.删除*****"<<endl;
	cout<<"*****4.查找*****"<<endl;
	cout<<"*****5.修改*****"<<endl; 
	cout<<"*****6.清空*****"<<endl;
	cout<<"*****0.退出*****"<<endl;
	cout<<"****************"<<endl;
}

struct person{
	string name;
	int age;
	int sex;//1man 2woman
	string phone;
	string address;
};

struct books{
	struct person a[Max];
	int m_size;
};
 
 
 void addPerson(books * abs)
 {
 	if(abs->m_size==Max)
 	{
 		cout<<"满了，憋加了"<<endl;
 		system("pause");
 		return ;
	 }
 	else
 	{
 		string name;
 		cout<<"name?"<<endl;
 		cin>>name;
 		abs->a[abs->m_size].name=name;

 		
 		int age;
 		cout<<"age?"<<endl;
 		cin>>age;
        abs->a[abs->m_size].age=age; 		


 		int Sex;
 		cout<<"sex?"<<endl;
 		cout<<"1--man"<<endl;
 		cout<<"2--woman"<<endl;
 		while(true)
 	    {
 	    	cin>>Sex;
 		if(Sex==1)
 		 {
 			abs->a[abs->m_size].sex=Sex;
 			break; 
		 }
 		else if(Sex==2)
 	      {
 			abs->a[abs->m_size].sex=Sex;
 			break;
		  }
		 else
		   {
		 	cout<<"nmd，选1或者2"<<endl;
		 	
		   }
		   
 	    }
	    
            string phone;
            cout<<"phone?"<<endl;
            cin>>phone;
 	        abs->a[abs->m_size].phone=phone;
 	  
 		   string address;
 		   cout<<"家庭住址（不会上门找你哒）"<<endl; 
 		   cin>>address;
 		   abs->a[abs->m_size].address=address;
 		   
 		   
 		  abs->m_size++;
 		  
 		 
		   cout<<"恭喜啊，生死簿又添一位"<<endl; 
 		 
		  system("pause");
 		 
 		 
 	  	  system("cls");//清屏 
	 }
	 
 	
 }
 
//检测 
   void showperson(books * abs)
{
   	   if(abs->m_size==0)
   	   {
   	   	cout<<"快看，没人爱的家伙。hhhhc"<<endl; 
   		system("pause");
   		system("cls");
   	   	
		  }
   	else
   	{
   		for(int i=0;i<abs->m_size;i++)
   		{
   			cout<<"name: "<<abs->a[i].name<<"\t"; 
   			cout<<" age: "<<abs->a[i].age<<"\t";
   			cout<<" sex: "<<(abs->a[i].sex==1?"男":"女" )<<"\t";
   			cout<<" phone: "<<abs->a[i].phone<<"\t";
   			cout<<" address: "<<abs->a[i].address <<endl;
		   }
   		system("pause");
   		system("cls");
	   }
   }

int  isExsit(books * abs,string name)
{
	for(int i=0;i<=(abs->m_size);i++)
	{
		if(abs->a[i].name==name)
		{ 		
			return i;
		}
		else if (abs->a[i].name!=name)
		{
			return -1;
		}
	}
}

void delectperson(books * abs,string name)
{
	
    int ret = isExsit(abs,name);
	if(ret!=-1)
	{
		for(int i=ret;i<abs->m_size-1;i++)
		{
			abs->a[i]=abs->a[i+1];
		}
		abs->m_size--;
		cout<<"删完啦"<<endl; 
	}
	else
	{
		cout<<"阴兵"<<endl; 
	}
		system("pause");
		system("cls");
 } 

void findperson(books * abs,string name)
{
	 int ret=isExsit(abs,name);
	 if(ret!=-1)
	 {
		cout<<"name: "<<abs->a[ret].name<<"\t"; 
   			cout<<" age: "<<abs->a[ret].age<<"\t";
   			cout<<" sex: "<<(abs->a[ret].sex)<<"\t";
   			cout<<" phone: "<<abs->a[ret].phone<<"\t";
   			cout<<" address: "<<abs->a[ret].address <<endl;
   			system("pause");
   			system("cls");
	 }
	 else
	 {
	 	cout<<"阴兵！"<<endl;
	 		system("pause");
   			system("cls");
	 }
}

void modifyperson(books * abs)
{
	cout<<"想改谁？"<<"名字 ："<<endl; 
	string name;
	cin>>name;
	int ret=isExsit(abs,name);
	if(ret!=-1)
	{
		cout<<"new name:"<<endl;
		cin>>abs->a[ret].name;
		
		cout<<"new age:"<<endl;
		cin>>abs->a[ret].age;
		
		cout<<"new sex:"<<endl;
		cout<<"1-man,2-woman"<<endl;
		cin>>abs->a[ret].sex;
		
		cout<<"new phone"<<endl;
		cin>>abs->a[ret].phone;
		
		cout<<"new address"<<endl;
		cin>>abs->a[ret].address;
		
	}
	else
	{
		cout<<"未找到,你记错了吧？"<<endl;
	}
		system("pause");
		system("cls");
	
 } 

void clear(books * abs)
{
	abs->m_size=0;
	cout<<"全没啦"<<endl;
		system("pause");
		system("cls");
}

int main()
{
	 books abs;
	 abs.m_size=0;
	 int select=0;
	//菜单 
	while(true)
{ 
    show();
	cin>>select; 
	switch (select)
    {
    	case 1://添加 
    	 addPerson(&abs);
    	//地址传递 
    		break;
    	
    	case 2://显示 
            showperson(&abs);
    		break;
    	
    	
    	case 3://删除 
            {
			string name;
         	cout<<"输入惹你的联系人名儿！"<<endl; 
    	    cin>>name;
             delectperson(&abs,name);
  
//    	    if(isExsit(&abs,name)==-1)
//    	    {
//    	    	cout<<"你小子，给我整阴兵？"<<endl; 
//    	     	system("pause");
//		   	    system("cls");
//			}
//		   else if(isExsit(&abs,name)!=-1)
//		   {
//		   	cout<<"找到这b了"<<endl;
//		   	system("pause");
//		   	system("cls");
//		   }
    	    
    		break;
    } 
    	
     	case 4://查找 
     	{
     		string name;
     		cout<<"相查的名字： "<<endl; 
     		cin>>name;
          findperson(&abs,name);  	
    		break;
    }
    	
    	case 5://修改 
    	{
    		modifyperson(&abs);
    		break;
   }
    	case 6:
		{
	        clear(&abs);
    		break;
    		
}
    	case 0://退出 
    	    cout<<"欢迎你回来捏~"<<endl;
    	    system("pause");
    	    return 0;
    		break;
    		
    	default:
    		break;
	}
}
	
	system("pause");
	return 0;
}
