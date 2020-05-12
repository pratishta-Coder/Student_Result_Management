#include<iostream.h>   //header files
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<fstream.h>
#include<iomanip.h>
class Student          //class in project
{
   public:
   int rollno;
   char name[50];
   int p_marks,c_marks,m_marks,e_marks,cs_marks;
   float per;
   char grade;
   int std;
   public:
   void calculate();
   void getdata();
   void showdata();
   void show_tabular();
   int retrollno();
 };
 void Student::calculate()
 {
   per=(p_marks+c_marks+m_marks+e_marks+cs_marks)/5.0;
   if(per>=60)
   grade='A';
   else if(per>=50 && per<60)
   grade='B';
   else if(per>=33 && per<50)
   grade='C';
   else
   grade='F';
  }
  void Student::getdata()
  {
    textcolor(CYAN);
    cout<<"*****Enter the student details*****"<<endl;
    cout<<"Enter the rollno of the student:";
    cin>>rollno;
    cout<<"\nEnter the name of the student:";
    gets(name);
    cout<<"\nEnter the marks in physics out of 100:";
    cin>>p_marks;
    cout<<"\nEnter the marks in chemistry out of 100:";
    cin>>c_marks;
    cout<<"\nEnter the marks in maths out of 100:";
    cin>>m_marks;
    cout<<"\nEnter the marks in english out of 100:";
    cin>>e_marks;
    cout<<"\nEnter the marks in computer science out of 100:";
    cin>>cs_marks;
    calculate();
  }
  void Student::showdata()
  {
    textcolor(CYAN);
    cout<<"\nRoll number of student:"<<rollno;
    cout<<"\nName of student:"<<name;
    cout<<"\nMraks in Physics:"<<p_marks;
    cout<<"\nMarks in Chemistry:"<<c_marks;
    cout<<"\nMarks in Maths:"<<m_marks;
    cout<<"\nMarks in English:"<<e_marks;
    cout<<"\nMarks in Computer Science:"<<cs_marks;
    cout<<"\nPercentage of student is:"<<setprecision(2)<<per;
    cout<<"\nGrade of student is:"<<grade;
  }
  void Student::show_tabular()  //memberv function of Student
  {
    cout<<rollno<<setw(12)<<name<<setw(10)<<p_marks<<setw(3)<<c_marks<<setw(3)<<m_marks<<setw(3)<<e_marks<<setw(3)<<cs_marks<<setw(6)<<setprecision(3)<<per<<" "<<grade<<endl;
  }
  int Student::retrollno()   //member function of class Student
  {
    return rollno;
  }
  fstream fp;//global declaration for filestream object
  Student st;
  void write_student()     //function to write data in file
  {
    fp.open("student.dat",ios::out|ios::app);
    st.getdata();            //member function of Student
    fp.write((char*)&st,sizeof(Student));
    fp.close();
    cout<<"\n\nstudent record has been created successfully!!!";
    getch();
  }
  void display_all()      //function to read all records from file
  {
    clrscr();
    cout<<"\n\n\n\t\tDisplay All Record!!!\n\n";
    fp.open("student.dat",ios::in);
    while(fp.read((char*)&st,sizeof(Student)))
    {
     textcolor(CYAN);
     st.showdata();     //member function of Student
     cout<<"\n\n==============================\n";
     getch();
    }
    fp.close();
    getch();
  }
  void display_sp(int n)     //function to read specific record from file
  {
    int flag=0;
    textcolor(CYAN);
    fp.open("student.dat",ios::in);
    while(fp.read((char*)&st,sizeof(Student)))
    {
       if(st.retrollno()==n)
       {
	 clrscr();
	 st.showdata();
	 flag=1;
	 break;
       }
    }
    fp.close();
    if(flag==0)
    {
       cout<<"\n\nRecord not exist...";
    }
    getch();
  }

  void modify_student()       //function to modify record of file
  {
     int no,found=0;
     clrscr();
     cout<<"\n\n\tTo Modify Record:-";
     cout<<"\n\n\tPlease enter the roll number of student:";
     cin>>no;
     fp.open("student.dat",ios::in|ios::out);
     while(fp.read((char*)&st,sizeof(Student))&& found==0)
     {
	if(st.retrollno()==no)
	{
	   st.showdata();
	   cout<<"\nPlease enter the new details of student:"<<endl;
	   st.getdata();
	   int pos=-1*sizeof(st);
	   fp.seekp(pos,ios::cur);
	   fp.write((char*)&st,sizeof(Student));
	   cout<<"\n\n\tRecord Updated Successfully!!!";
	   found=1;
	   break;
	}
     }
     fp.close();
     if(found==0)
     {
	cout<<"\n\nRecord not found...";
     }
     getch();
    }
    char validate(int no)
    {
       fp.open("student.dat",ios::in|ios::out);
       while(fp.read((char*)&st,sizeof(Student)))
       {
	  if(st.retrollno()==no)
	  {
	     return 'Y';
	  }
       }
	     return 'N';
    }

    void delete_student()      //function to delete the record of file
    {
      int no;
      clrscr();
      cout<<"\n\n\n\tDelete Record";
      cout<<"\n\nPlease enter the roll number of student you want to delete:";
      cin>>no;
      char c=validate(no);
      if(c=='Y')
     {
      fp.open("student.dat",ios::in|ios::out);
      fstream fp2;
      fp2.open("Temp.dat",ios::out);
      fp.open(0,ios::beg);
      while(fp.read((char*)&st,sizeof(Student)))
      {
	 if(st.retrollno()!=no)
	 {
	    fp2.write((char*)&st,sizeof(Student));
	 }
      }
      fp2.close();
      fp.close();
      remove("student.dat");
      rename("Temp.dat","student.dat");
      cout<<"\n\n\tRecord deleted successfully!!!";
     }
     else
     {
	cout<<"Record not exist..."<<endl;
      }
      getch();
    }
    void class_result()          //function to display all students grade report
    {
      clrscr();
      fp.open("student.dat",ios::in);
      if(!fp)
      {
	cout<<"Error!!!File could not be open\n\n\nGo to entry Menu to create file";
	cout<<"\n\n\nProgram is closing";
	getch();
	exit(0);
      }

      cout<<"\n\n\t\tAll students result\n\n";
      cout<<"=====================================================================\n";
      cout<<"Rollno\tName\t\tP C M E  CS %age Grade\n";
      cout<<"=====================================================================\n";
      while(fp.read((char*)&st,sizeof(Student)))
      {
	st.show_tabular();
      }
      fp.close();
      getch();

    }

    void result()            //function to display result menu
    {
       int ans,rno;
       char ch;
       clrscr();
       cout<<"\n\n\n********Result Menu*********";
       cout<<"\n\n\n1.Class Result\n\n2.Student Report Card\n\n3.Back to main menu";
       cout<<"\n\nEnter choice(1/2)?";
       cin>>ans;
       switch(ans)
       {
	 case 1:class_result();
		break;
	 case 2:{
		    clrscr();
		    char ans;
		   // do{
		    cout<<"\n\nEnter roll number of student:";
		    cin>>rno;
		    display_sp(rno);
		   // cout<<"\n\nDo you want to see more result(y/n)?";
		   // cin>>ans;
		  // }while(ans=='y'||ans=='Y');
		   break;
		}
	 case 3:break;
	 default:cout<<"\a";
       }
    }
    void intro()          //Introduction function
    {
       clrscr();
       cout<<"\n\n\n\n\n\n\n\n\t===========================================================";
       cout<<"\n\n\t\tWELCOME TO STUDENT RESULT MANAGEMENT SYSTEM";
       cout<<"\n\n\t===========================================================";
       gotoxy(35,17);
       cout<<"\n\nMade By:-Pratishta Shelke,Vaishnavi Salunke,Gourangni Bhola,Sumira Srivastava";
       cout<<"\n\nCollege:-K K Wagh Engineering College";
       getch();
    }
    void entry_menu()
    {
      clrscr();
      char ch2;
      cout<<"\n\n\n\t*****Entry Menu*****";
      cout<<"\n\n\t1.Create Student Record";
      cout<<"\n\n\t2.Display All Student Records";
      cout<<"\n\n\t3.Search Student Record";
      cout<<"\n\n\t4.Modify Student Record";
      cout<<"\n\n\t5.Delete Student Record";
      cout<<"\n\n\t6.Back to main menu";
      cout<<"\n\n\tPlease enter your choice(1-6)";
      ch2=getche();
      switch(ch2)
      {
	case '1':clrscr();
		 write_student();
		 break;
	case '2':display_all();
		 break;
	case '3':int num;
		 clrscr();
		 cout<<"\n\n\tPlease enter the roll number:";
		 cin>>num;
		 display_sp(num);
		 break;
	case '4':modify_student();
		 break;
	case '5':delete_student();
		 break;
	case '6':break;
	default:cout<<"\a";
		entry_menu();
       }
     }
     void main()               //main function
     {
	char ch;
	textcolor(CYAN);
	intro();
	do{
	    clrscr();
	    cout<<"\n\n\n\t\t\t*************Main Menu*************";
	    cout<<"\n\n\t\t\t1.Insert/Edit Student Marks Menu ";
	    cout<<"\n\n\t\t\t2.Result Menu";
	    cout<<"\n\n\t\t\t3.Exit";
	    cout<<"\n\n\t\t\tPlease select your option:";
	    ch=getche();
	    switch(ch)
	    {
	      case '1'://clrscr();
		       entry_menu();
		       break;
	      case '2':
		       result();
		       break;
	      case '3':exit(0);
	      default:cout<<"\a";
	    }
	 }while(ch!=3);
     }
     //End of project

