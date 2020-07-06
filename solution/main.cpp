// SELECT_COURSE SYSTEM
//
#include <conio.h>
#include <iomanip>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

long i;// i.txt فایل شمارنده تعداد دانشجو
int j; //  j.txt فایل شمارنده تعداد درس
int k; //  k.txt فایل شمارنده تعداد انتخاب واحد 


//
//کلاس درس 
class course
{
	int classNum, capacity, inCapacity, state, vahed, num, j;
	string name, teacherFirstName, teacherLastName, day, time;
public:
	void show();// تابع نمایش درس
	void add(); // تابع افزودن درس
	void Delete(); // تابع حذف درس
	void search(); // تابع جستجو
	void displayAll(); // تابع نمایش همه ی دروس
	friend class selectCourse; // افزودن دسترسی به کلاس انتخاب واحد  
	friend class student; // افزودن دسترسی به کلاس دانشجو
};

void course::show()
{
	cout<<"\n\n\n\n\tCOURSE INFORMATION\n";
	cout<<"\t------------------------------------\n";
	cout<<"\n\tCourse-number: "<<num<<"\n";
	cout<<"\n\tCourse-name: "<<name<<"\n";
	cout<<"\n\tVahed of course: "<<vahed<<"\n";
	cout<<"\n\tLast-name of course-teacher: "<<teacherLastName<<"\n";
	cout<<"\n\tFirst-name of course-teacher: "<<teacherFirstName<<"\n";
	cout<<"\n\tWeek day of course: "<<day<<"\n";
	cout<<"\n\tTime of course: "<<time<<"\n";
	cout<<"\n\tNumber of class: "<<classNum<<"\n";
	cout<<"\n\tCapacity of class: "<<capacity<<"\n";
	cout<<"\n\tNumber of students in class: "<<inCapacity<<"\n";
	cout<<"\n\t------------------------------------\n\t";
}

void course::add()
{
	course c;	

	fstream fp("courses.dat" , ios::out|ios::in|ios::binary);
	if(!fp) //create file if it's not created before
	{
		ofstream fp1("courses.dat" , ios::out|ios::binary);
		fp1.close();
	}

	ifstream inj("j.txt" , ios::in);
	if(!inj) //create file if it's not created before
	{
		ofstream outj("j.txt" , ios::out);
		int tempJ=0;
		outj<<tempJ;
		outj.close();
	}

	//----------add----------
	system("cls");
	cout<<"\n\n\n\n\tADD COURSE\n";
	cout<<"\t----------------------------------\n";
	cout<<"\n\tEnter course-number: ";
	cin>>c.num;
	cout<<"\n\tEnter course-name: ";
	cin>>c.name;
	cout<<"\n\tEnter vahed of course (1, 2, 3 Or 4?) : ";
	cin>>c.vahed;
	cout<<"\n\tEnter last-name of course-teacher: ";
	cin>>c.teacherLastName;
	cout<<"\n\tEnter first-name of course-teacher: ";
	cin>>c.teacherFirstName;
	cout<<"\n\tEnter week day of course (Sun, Mon, Tue, Wed, Thu, Fri or Sat?) : ";
	cin>>c.day;
	cout<<"\n\tEnter time of course (for example: 7.30-9.50) : ";
	cin>>c.time;
	cout<<"\n\tEnter number of class: ";
	cin>>c.classNum;
	cout<<"\n\tEnter capacity of class: ";
	cin>>c.capacity;
	c.state=1;
	c.inCapacity=0;

	//----------display----------
	system("cls");
	cout<<"\n\n\n\n\tRecord has been created successfully!";
	c.show();
	getch();

	ifstream inj1("j.txt" , ios::in); 
	inj1>>j;

	c.j=j;
	j++;

	ofstream outj1("j.txt" , ios::out);
	outj1<<j;

	//------------save------------
	fstream fp1("courses.dat" , ios::out|ios::in|ios::binary);
	fp1.seekp( sizeof(course)*(c.j) , ios::beg);
	fp1.write( (char *)&c , sizeof(course) );
	fp1.close();
} //end course::add()

void course::search()
{
	system("cls");
	int temp=0;
	course c;

	cout<<"\n\n\n\n\tEnter course-number to find: ";
	int tempCourseNum; cin>>tempCourseNum;

	fstream fp("courses.dat" , ios::out|ios::in|ios::binary);
	fp.read( (char *)&c , sizeof(course) );
	while( fp && !fp.eof() ) //while (fp is created) && (it's not end of fp)
	{
		if ( tempCourseNum == c.num )
		{
			if (c.state != 0)
			{
				//----------display----------
				c.show();

				temp++; 
			} //end if
		} //end if

		//read next from file
		fp.read( (char *)&c , sizeof(course) );
	} //end while

	if ( temp == 0 ) { cout<<"\n\tThere is no course with this number!\n\t"; }
	getch();
} //end course::search()

void course::displayAll()
{
	system("cls");
	cout<<"\nnumber  name      vahed teacher     day      time     remain-capacity  class-num";
	cout<<"================================================================================";
	
	course c;
	
	//read all records from file
	fstream fp("courses.dat" , ios::out|ios::in|ios::binary);
	fp.read( (char *)&c , sizeof(course) );
	while( fp && !fp.eof() ) //while (fp is created) && (it's not end of fp)
	{
		if(c.state != 0)
		{
			cout<<left<<setw(8)<<c.num;
			cout<<setw(10)<<c.name;
			cout<<setw(6)<<c.vahed;
			cout<<setw(12)<<c.teacherLastName;
			cout<<setw(6)<<c.day;
			cout<<setw(18)<<c.time;
			
			// remain capacity
			int a,b;
			a=c.capacity;
			b=c.inCapacity;
			cout<<setw(16)<<(a-b);
			
			cout<<c.classNum;
			cout<<"\n--------------------------------------------------------------------------------";
		} //end if

		fp.read( (char *)&c , sizeof(course) ); //read next from file
	} //end while

	getch();
} //end course::displayAll()
//---------------

//
// کلاس دانشجو
class student
{
	float average;
	long num,i;
	int state, courseLimit, courseTaken;
	string firstName, lastName;
public:
	void show();// تابع نمایش مشخصات دانشجو
	void add(); // تابع افزودن دانشجو
	void Delete(); // تابع حذف دانشجو
	void search(); // تابع جستجوی دانشجو
	void displayAll(); // تابع نمایش همه ی دانشجوها
	friend class selectCourse; // افزودن دسترسی به  کلاس انتخاب واحد
	friend class course;// افزودن دسترسی به کلاس درس
};

void student::show()
{
	cout<<"\n\n\n\n\tSTUDENT INFORMATION\n";
	cout<<"\t------------------------------------\n";
	cout<<"\n\tStudent-number: "<<num<<endl;
	cout<<"\n\tFirst-name: "<<firstName<<endl;
	cout<<"\n\tLast-name: "<<lastName<<endl;
	cout<<"\n\tLast term-average: "<<average<<endl;
	cout<<"\n\tTaken-courses: "<<courseTaken<<endl;
	cout<<"\n\tCourse-limit: "<<courseLimit<<endl;
	cout<<"\n\t------------------------------------\n\t";
}

void student::add()
{
	student s;
	
	fstream fp("students.dat" , ios::out|ios::in|ios::binary);
	if(!fp) //create file if it's not created before
	{
		ofstream fp1("students.dat" , ios::out|ios::binary);
		fp1.close();
	}

	ifstream ini("i.txt" , ios::in);
	if(!ini) //create file if it's not created before
	{
		ofstream outi("i.txt" , ios::out);
		long tempI=0;
		outi<<tempI;
		outi.close();
	}

	//----------add----------
	system("cls");
	cout<<"\n\n\n\n\tADD STUDENT\n";
	cout<<"\t----------------------------------\n";
	cout<<"\n\tEnter student-number: ";
	cin>>s.num;
	cout<<"\n\tEnter first-name: ";
	cin>>s.firstName;
	cout<<"\n\tEnter last-name: ";
	cin>>s.lastName;
	cout<<"\n\tEnter last term-average: ";
	cin>>s.average;

	s.state=1;
	s.courseTaken=0;
	
	if (s.average<12) s.courseLimit=14;
	else if (s.average>=17) s.courseLimit=24;
	else s.courseLimit=20;
	
	//----------display----------
	system("cls");
	cout<<"\n\n\n\n\tRecord has been created successfully!";
	s.show();
	getch();

	ifstream ini1("i.txt" , ios::in); 
	ini1>>i;

	s.i=i;
	i++;

	ofstream outi1("i.txt" , ios::out);
	outi1<<i;

	//------------save------------
	fstream fp1("students.dat" , ios::out|ios::in|ios::binary);
	fp1.seekp( sizeof(student)*(s.i) , ios::beg);
	fp1.write( (char *)&s , sizeof(student) );
	fp1.close();
} //end student::add()

void student::search()
{
	system("cls");
	int temp=0;
	student s;

	cout<<"\n\n\n\n\tEnter student-number to find: ";
	long tempStuNum; cin>>tempStuNum;

	fstream fp("students.dat" , ios::out|ios::in|ios::binary);
	fp.read( (char *)&s , sizeof(student) );
	while( fp && !fp.eof() ) //while (fp is created) && (it's not end of fp)
	{
		if ( tempStuNum == s.num )
		{
			if (s.state != 0)
			{
				//----------display----------
				s.show();

				temp++; 
			} //end if
		} //end if

		//read next from file
		fp.read( (char *)&s , sizeof(student) );
	} //end while

	if ( temp == 0 ) { cout<<"\n\tThere is no student with this number!\n\t"; }
	getch();
} //end student::search()

void student::displayAll()
{
	system("cls");
	cout<<"\n  number    first-name  last-name     last-average  taken-courses  course-limit\n";
	cout<<"  =============================================================================\n";
	
	student s;
	
	//read all records from file
	fstream fp("students.dat" , ios::out|ios::in|ios::binary);
	fp.read( (char *)&s , sizeof(student) );
	while( fp && !fp.eof() ) //while (fp is created) && (it's not end of fp)
	{
		if(s.state != 0)
		{
			cout<<"  "<<left<<setw(10)<<s.num;
			cout<<setw(12)<<s.firstName;
			cout<<setw(14)<<s.lastName;
			cout<<setw(14)<<s.average;
			cout<<setw(15)<<s.courseTaken;
			cout<<s.courseLimit;
			cout<<"\n  -----------------------------------------------------------------------------\n";
		} //end if

		fp.read( (char *)&s , sizeof(student) ); //read next from file
	} //end while

	cout<<"  ";
	getch();
} //end student::displayAll()
//---------------

//
// کلاس انتخاب واحد
class selectCourse
{
	student stu;
	course cour;
	int state, k; //select.k is address of each selectCourse
public:
	void add(); // تابع افزودن انتخاب واحد
	void Delete(); // تابع حذف انتخاب واحد
	void reportByStudentNum(); // تابع تمایش دانشجو هایی که انتخاب واحد انجام داده اند
	void reportByCourseNum(); // تابع نمایش درس هایی که در انتخاب واحد ثبت شده اند
	friend class course; // افزودن دسترسی به کلاس درس
	friend class student; // افزودن دسترسی به کلاس دانشجو
};

void selectCourse::add()
{
	system("cls");
	int sTemp=0;
	student s;

	cout<<"\n\n\n\n\tEnter student-number to add Select-Course: ";
	long tempStuNum; cin>>tempStuNum;

	fstream fp("students.dat" , ios::out|ios::in|ios::binary);
	fp.read( (char *)&s , sizeof(student) );
	while( fp && !fp.eof() ) //while (fp is created) && (it's not end of fp)
	{
		if ( tempStuNum == s.num )
		{
			if (s.state != 0)
			{
				if (s.courseTaken<=s.courseLimit) 
				{
                    //----------display student----------
					s.show();
					getch();
				
					// reset
					int cTemp=0;
					course c;

					cout<<"\n\n\n\n\tEnter course-number to select: ";
					int tempCourseNum; cin>>tempCourseNum;

					fstream fp1("courses.dat" , ios::out|ios::in|ios::binary);
					fp1.read( (char *)&c , sizeof(course) );
					while( fp1 && !fp1.eof() ) //while (fp1 is created) && (it's not end of fp1)
					{
						if ( tempCourseNum == c.num )
						{
							if (c.state != 0)
							{
								if( !(c.vahed + s.courseTaken > s.courseLimit) )
								{
									if(c.inCapacity < c.capacity)
									{
										//----------display course----------
										c.show();
							            getch();

							            ////////////////////////////////////////////////////////////////////
										s.courseTaken+=c.vahed;
							            //-----save student new informations-----
							            fstream fp5("students.dat" , ios::out|ios::in|ios::binary);
							            fp5.seekp( sizeof(student)*(s.i) , ios::beg);
							            fp5.write( (char *)&s , sizeof(student) );
							            fp5.close();

							            c.inCapacity++;
							            //-----save course new informations-----
							            fstream fp6("courses.dat" , ios::out|ios::in|ios::binary);
							            fp6.seekp( sizeof(course)*(c.j) , ios::beg);
							            fp6.write( (char *)&c , sizeof(course) );
							            fp6.close();

							            selectCourse select;
							            select.stu=s;  //step1
							            select.cour=c; //step2
							            select.state=1; //step3

							            ifstream ink("k.txt" , ios::in);
							            if(!ink) //create file if it's not created before
										{
											ofstream outk("k.txt" , ios::out);
								            int tempK=0;
								            outk<<tempK;
								            outk.close();
										}

										ifstream ink1("k.txt" , ios::in); 
							            ink1>>k;
				
							            select.k=k; //step4
							            k++;

							            ofstream outk1("k.txt" , ios::out);
							            outk1<<k;
							            outk1.close();
							
							            fstream fp3("selectCourses.dat" , ios::out|ios::in|ios::binary);
							            if(!fp3) //create file if it's not created before
							            {
											ofstream fp4("selectCourses.dat" , ios::out|ios::binary);
								            fp4.close();
										}

							            //--------save select--------
							            fstream fp2("selectCourses.dat" , ios::out|ios::in|ios::binary);
							            fp2.seekp( sizeof(selectCourse)*(select.k) , ios::beg);
							            fp2.write( (char *)&select , sizeof(selectCourse) );
							            fp2.close();
				
							            cout<<"\n\tSelect-Course is succsessfully done!\n\t";
							            getch();
							            //---
										
										cTemp++;

									} //end if (<)
									else { cout<<"\n\n\tThe capacity of class is full!\n\t"; cTemp=1; getch(); }
								
								} //end if ( !() )
								else { cout<<"\n\n\tThis student can't select this course!\n\t"; cTemp=1; getch(); }
							
							} //end if
						} //end if

						//read next from file
						fp1.read( (char *)&c , sizeof(course) );
					} //end while

					if ( cTemp == 0 ) { cout<<"\n\tThere is no course with this number!\n\t"; getch(); }
					//---

                } // end if(s.courseTaken<=s.courseLimit)
				else { cout<<"\n\n\tThis student can't select any more courses!\n\tTo add more courses, you must first delete some old courses!\n\t "; getch(); }

				sTemp++;

            } //end if
        } //end if
		
		//read next from file
		fp.read( (char *)&s , sizeof(student) );
    } //end while

	if ( sTemp == 0 ) { cout<<"\n\tThere is no student with this number!\n\t"; getch(); }
} //end selectCourse::add()

void selectCourse::reportByStudentNum()
{	
	system("cls");
	int sTemp=0;
	student s;

	cout<<"\n\n\n\n\tEnter student-number to report: ";
	long tempStuNum; cin>>tempStuNum;

	fstream fp("students.dat" , ios::out|ios::in|ios::binary);
	fp.read( (char *)&s , sizeof(student) );
	while( fp && !fp.eof() ) //while (fp is created) && (it's not end of fp)
	{
		if ( tempStuNum == s.num )
		{
			if (s.state != 0)
			{
				//----------display student----------
				cout<<"\n\n\n\n\tSTUDENT INFORMATION\n";
				cout<<"\t------------------------------------\n";
				cout<<"\n\tStudent-number: "<<s.num<<endl;
				cout<<"\n\tFirst-name: "<<s.firstName<<endl;
				cout<<"\n\tLast-name: "<<s.lastName<<endl;
				cout<<"\n\tLast term-average: "<<s.average<<endl;
				cout<<"\n\tTaken-courses: "<<s.courseTaken<<endl;
				cout<<"\n\tCourse-limit: "<<s.courseLimit<<endl;
				cout<<"\n\t------------------------------------\n\n\n";
				cout<<"\nnumber  name      vahed teacher     day      time     remain-capacity  class-num";
				cout<<"================================================================================";

				sTemp++; 
			} //end if
		} //end if
		
		//read next from file
		fp.read( (char *)&s , sizeof(student) );
	} //end while

	if ( sTemp == 0 ) { cout<<"\n\tThere is no student with this number!\n\t"; }

	//---
	int selectTemp=0;
	selectCourse select;

	fstream fp1("selectCourses.dat" , ios::out|ios::in|ios::binary);
	fp1.read( (char *)&select , sizeof(selectCourse) );
	while( fp1 && !fp1.eof() ) //while (fp1 is created) && (it's not end of fp1)
	{
		if ( tempStuNum == select.stu.num )
		{
			if (select.state != 0)
			{
				cout<<left<<setw(8)<<select.cour.num;
				cout<<setw(10)<<select.cour.name;
				cout<<setw(6)<<select.cour.vahed;
				cout<<setw(12)<<select.cour.teacherLastName;
				cout<<setw(6)<<select.cour.day;
				cout<<setw(18)<<select.cour.time;

				int a,b;
				a=select.cour.capacity;
				b=select.cour.inCapacity;
				cout<<setw(16)<<a-b;

				cout<<select.cour.classNum;
				cout<<"\n--------------------------------------------------------------------------------";

				selectTemp++;

			} //end if
		} //end if

		//read next from file
		fp1.read( (char *)&select , sizeof(selectCourse) );
	} //end while

	getch();	
	if ( selectTemp == 0 ) { cout<<"\n\tThere is no course for this student!\n\t"; getch(); }

} //end selectCourse::reportByStudentNum()

void selectCourse::reportByCourseNum()
{	
	system("cls");
	int cTemp=0;
	course c;

	cout<<"\n\n\n\n\tEnter course-number to report: ";
	long tempCourseNum; cin>>tempCourseNum;

	fstream fp("courses.dat" , ios::out|ios::in|ios::binary);
	fp.read( (char *)&c , sizeof(course) );
	while( fp && !fp.eof() ) //while (fp is created) && (it's not end of fp)
	{
		if ( tempCourseNum == c.num )
		{
			if (c.state != 0)
			{
				//----------display course----------
				cout<<"\n\n\n\n\tCOURSE INFORMATION\n";
				cout<<"\t------------------------------------\n";
				cout<<"\n\tCourse-number: "<<c.num<<"\n";
				cout<<"\n\tCourse-name: "<<c.name<<"\n";
				cout<<"\n\tVahed of course: "<<c.vahed<<"\n";
				cout<<"\n\tLast-name of course-teacher: "<<c.teacherLastName<<"\n";
				cout<<"\n\tFirst-name of course-teacher: "<<c.teacherFirstName<<"\n";
				cout<<"\n\tWeek day of course: "<<c.day<<"\n";
				cout<<"\n\tTime of course: "<<c.time<<"\n";
				cout<<"\n\tNumber of class: "<<c.classNum<<"\n";
				cout<<"\n\tCapacity of class: "<<c.capacity<<"\n";
				cout<<"\n\tNumber of students in class: "<<c.inCapacity<<"\n";
				cout<<"\n\t------------------------------------\n\n\n";
				cout<<"\n  number    first-name  last-name     last-average  course-limit\n";
				cout<<"  ==============================================================\n";

				cTemp++; 
			} //end if
		} //end if
		
		//read next from file
		fp.read( (char *)&c , sizeof(course) );
	} //end while

	if ( cTemp == 0 ) { cout<<"\n\tThere is no course with this number!\n\t"; }

	//---
	int selectTemp=0;
	selectCourse select;

	fstream fp1("selectCourses.dat" , ios::out|ios::in|ios::binary);
	fp1.read( (char *)&select , sizeof(selectCourse) );
	while( fp1 && !fp1.eof() ) //while (fp1 is created) && (it's not end of fp1)
	{
		if ( tempCourseNum == select.cour.num )
		{
			if (select.state != 0)
			{
				cout<<"  "<<left<<setw(10)<<select.stu.num;
			    cout<<setw(12)<<select.stu.firstName;
			    cout<<setw(14)<<select.stu.lastName;
			    cout<<setw(14)<<select.stu.average;
			    cout<<select.stu.courseLimit;
			    cout<<"\n  --------------------------------------------------------------\n";

				selectTemp++;

			} //end if
		} //end if

		//read next from file
		fp1.read( (char *)&select , sizeof(selectCourse) );
	} //end while

	getch();	
	if ( selectTemp == 0 ) { cout<<"\n\tThere is no student for this course!\n\t"; getch(); }

} //end selectCourse::reportByCourseNum()

void selectCourse::Delete()
{
	system("cls");
	cout<<"\n\n\n\n\tEnter student-number to delete its select-course: ";
	long tempStuNum; cin>>tempStuNum;
	cout<<"\n\n\tEnter number of select-course you want to delete: ";
	int tempCourseNum; cin>>tempCourseNum;

	//******step1: delete selectCourse
	int selectTemp=0;
	selectCourse select;

	fstream fp("selectCourses.dat" , ios::out|ios::in|ios::binary);
	fp.read( (char *)&select , sizeof(selectCourse) );
	while( fp && !fp.eof() ) //while (fp is created) && (it's not end of fp)
	{
		if ( tempStuNum == select.stu.num )
		{
			if ( tempCourseNum == select.cour.num )
			{
				if ( select.state != 0 )
				{
					select.state=0;
					
					//------save new informations-------
					fstream fp1("selectCourses.dat" , ios::out|ios::in|ios::binary);
					fp1.seekp( sizeof(selectCourse)*(select.k) , ios::beg);
					fp1.write( (char *)&select , sizeof(selectCourse) );
					fp1.close();

					cout<<"\n\n\n\tSelect-Course is succsessfully deleted!\n\t";
					getch();
					
					selectTemp++;

				} //end if
			} //end if
		} //end if

		//read next from file
		fp.read( (char *)&select , sizeof(selectCourse) );
	} //end while
	if ( selectTemp == 0 ) { cout<<"\n\n\n\tThere is no select-course for this student!\n\t"; getch(); }

	//******step2: decrease course inCapacity
	course c;

	fstream fp2("courses.dat" , ios::out|ios::in|ios::binary);
	fp2.read( (char *)&c , sizeof(course) );
	while( fp2 && !fp2.eof() ) //while (fp2 is created) && (it's not end of fp2)
	{
		if ( tempCourseNum == c.num )
		{
			if ( c.state!=0 )
			{ 
				if ( c.inCapacity != 0 )
				{
					c.inCapacity--;
					
					//------save new informations-------
				    fstream fp3("courses.dat" , ios::out|ios::in|ios::binary);
				    fp3.seekp( sizeof(course)*(c.j) , ios::beg);
				    fp3.write( (char *)&c , sizeof(course) );
				    fp3.close();

				} //end if
			} //end if
		} //end if

		//read next from file
		fp2.read( (char *)&c , sizeof(course) );
	} //end while
	
	//******step3: decrease student courseTaken
	student s;

	fstream fp4("students.dat" , ios::out|ios::in|ios::binary);
	fp4.read( (char *)&s , sizeof(student) );
	while( fp4 && !fp4.eof() ) //while (fp4 is created) && (it's not end of fp4)
	{
		if ( tempStuNum == s.num )
		{
			if ( s.state!=0 )
			{
				if ( s.courseTaken != 0)
				{
					//=============================
					course c1;

					fstream fp5("courses.dat" , ios::out|ios::in|ios::binary);
					fp5.read( (char *)&c1 , sizeof(course) );
					while( fp5 && !fp5.eof() ) //while (fp5 is created) && (it's not end of fp5)
					{
						if ( tempCourseNum == c1.num )
						{
							if ( c1.state!=0 )
							{
								s.courseTaken-=c1.vahed;
					
								//------save new informations-------
				                fstream fp6("students.dat" , ios::out|ios::in|ios::binary);
							    fp6.seekp( sizeof(student)*(s.i) , ios::beg);
				                fp6.write( (char *)&s , sizeof(student) );
				                fp6.close();

							} //end if
						} //end if

						//read next from file
						fp5.read( (char *)&c1 , sizeof(course) );
					} //end while
					//=============================

				} //end if
			} //end if
		} //end if

		//read next from file
		fp4.read( (char *)&s , sizeof(student) );
	} //end while

} //end selectCourse::Delete()

void course::Delete()
{
	system("cls");

	//******step1: delete course 
	int temp=0;
	course c;

	cout<<"\n\n\n\n\tEnter course-number to delete: ";
	int tempCourseNum; cin>>tempCourseNum;

	fstream fp("courses.dat" , ios::out|ios::in|ios::binary);
	fp.read( (char *)&c , sizeof(course) );
	while( fp && !fp.eof() ) //while (fp is created) && (it's not end of fp)
	{
		if ( tempCourseNum == c.num )
		{
			if (c.state != 0)
			{
				//----------display----------
				c.show();
		
				c.state=0;

				//-----------save-----------
				fstream fp1("courses.dat" , ios::out|ios::in|ios::binary);
				fp1.seekp( sizeof(course)*(c.j) , ios::beg);
				fp1.write( (char *)&c , sizeof(course) );
				fp1.close();

				temp++;
				cout<<"\n\tThe course has been successfully deleted!\n\t";
			} //end if
		} //end if

		//read next from file
		fp.read( (char *)&c , sizeof(course) );
	} //end while

	if ( temp == 0 ) { cout<<"\n\tThere is no course with this number!\n\t"; }
	getch();

	//******step2: delete selectCourse
	selectCourse select;

	fstream fp2("selectCourses.dat" , ios::out|ios::in|ios::binary);
	fp2.read( (char *)&select , sizeof(selectCourse) );
	while( fp2 && !fp2.eof() ) //while (fp2 is created) && (it's not end of fp2)
	{
		if ( tempCourseNum == select.cour.num )
		{
			if (select.cour.state != 0)
			{
				select.state=0; 

				//-----------save-----------
				fstream fp3("selectCourses.dat" , ios::out|ios::in|ios::binary);
				fp3.seekp( sizeof(selectCourse)*(select.k) , ios::beg);
				fp3.write( (char *)&select , sizeof(selectCourse) );
				fp3.close();

				//==========================================================================
				//******step3: decrease student courseTaken
				student s;
				fstream fp4("students.dat" , ios::out|ios::in|ios::binary);
				fp4.read( (char *)&s , sizeof(student) );
				while( fp4 && !fp4.eof() ) //while (fp4 is created) && (it's not end of fp4)
				{
					if ( select.stu.num == s.num )
					{
						if (s.courseTaken != 0)
						{
							s.courseTaken -= select.cour.vahed ; 

							//-----------save-----------
							fstream fp5("students.dat" , ios::out|ios::in|ios::binary);
							fp5.seekp( sizeof(student)*(s.i) , ios::beg);
				            fp5.write( (char *)&s , sizeof(student) );
				            fp5.close();

						} //end if
					} //end if

					//read next from file
					fp4.read( (char *)&s , sizeof(student) );
				} //end while

				//==========================================================================

			} //end if
		} //end if

		//read next from file
		fp2.read( (char *)&select , sizeof(selectCourse) );
	} //end while
	
} //end course::Delete()

void student::Delete()
{
	system("cls");

	//******step1: delete student
	int temp=0;
	student s;

	cout<<"\n\n\n\n\tEnter student-number to delete: ";
	long tempStuNum; cin>>tempStuNum;

	fstream fp("students.dat" , ios::out|ios::in|ios::binary);
	fp.read( (char *)&s , sizeof(student) );
	while( fp && !fp.eof() ) //while (fp is created) && (it's not end of fp)
	{
		if ( tempStuNum == s.num )
		{
			if (s.state != 0)
			{
				//----------display----------
				s.show();
			
				s.state=0;

				//-----------save-----------
				fstream fp1("students.dat" , ios::out|ios::in|ios::binary);
				fp1.seekp( sizeof(student)*(s.i) , ios::beg);
				fp1.write( (char *)&s , sizeof(student) );
				fp1.close();

				temp++;
				cout<<"\n\tThe student has been successfully deleted!\n\t";
			} //end if
		} //end if

		//read next from file
		fp.read( (char *)&s , sizeof(student) );
	} //end while

	if ( temp == 0 ) { cout<<"\n\tThere is no student with this number!\n\t"; }
	getch();
	
	//******step2: delete selectCourse
	selectCourse select;

	fstream fp2("selectCourses.dat" , ios::out|ios::in|ios::binary);
	fp2.read( (char *)&select , sizeof(selectCourse) );
	while( fp2 && !fp2.eof() ) //while (fp2 is created) && (it's not end of fp2)
	{
		if ( tempStuNum == select.stu.num )
		{
			if (select.stu.state != 0)
			{
				select.state=0;

				//-----------save-----------
				fstream fp3("selectCourses.dat" , ios::out|ios::in|ios::binary);
				fp3.seekp( sizeof(selectCourse)*(select.k) , ios::beg);
				fp3.write( (char *)&select , sizeof(selectCourse) );
				fp3.close();
				//==========================================================================
				//******step3: decrease course inCapacity
				course c;
				fstream fp4("courses.dat" , ios::out|ios::in|ios::binary);
				fp4.read( (char *)&c , sizeof(course) );
				while( fp4 && !fp4.eof() ) //while (fp4 is created) && (it's not end of fp4)
				{
					if ( select.cour.num == c.num )
					{
						if (c.inCapacity != 0)
						{
							c.inCapacity--; 

							//-----------save-----------
							fstream fp5("courses.dat" , ios::out|ios::in|ios::binary);
							fp5.seekp( sizeof(course)*(c.j) , ios::beg);
				            fp5.write( (char *)&c , sizeof(course) );
				            fp5.close();

						} //end if
					} //end if

					//read next from file
					fp4.read( (char *)&s , sizeof(student) );
				} //end while

				//==========================================================================

			} //end if
		} //end if

		//read next from file
		fp2.read( (char *)&select , sizeof(selectCourse) );
	} //end while

} //end student::Delete()

//
// بدنه اصلی
int main()
{
	system("cls");
	cout<<"\n\n\n\n\t                 WELCOME TO SELECT-COURSE SYSTEM!\n\n\t\n\t";
	getch();
	system("cls");
	student s;
	course c;
	selectCourse select;
	int back=1;
	while (back != 0)
	{
		system("cls");
		cout<<"\n\n\t                        MAIN MENU\n";
		cout<<"\t--------------------------------------------------------\n\n";
		cout<<"\t1.Add student                   5.Add course\n";
		cout<<"\t2.Delete student                6.Delete course\n";
		cout<<"\t3.Search student                7.Search course\n";
		cout<<"\t4.Display all students          8.Display all courses\n\n\n";
	
		cout<<"\t                 9.Add Select-Course\n";
		cout<<"\t                10.Delete Select-Course\n\n";

		cout<<"\t                11.Report students of a course\n";
		cout<<"\t                12.Report courses of a student\n";
		
		cout<<"\n\t                13.Exit\n\n";
		cout<<"\t---------------------------------------------------------\n";
		cout<<"\t                Enter a number (1-13) : ";
		int n; cin>>n;

		switch (n)
		{
		case 1: s.add(); break;
		case 2: s.Delete(); break;
		case 3: s.search(); break;
		case 4: s.displayAll(); break;

		case 5: c.add(); break;
		case 6: c.Delete(); break;
		case 7: c.search(); break;
		case 8: c.displayAll(); break;

		case 9: select.add(); break;
		case 10: select.Delete(); break;
		case 11: select.reportByCourseNum(); break;
		case 12: select.reportByStudentNum(); break;

		case 13: back=0; break;
		default: system("cls"); cout<<"\n\n\n\n\tError!\n\tEnter any key to back...\n\t"; getch();
		} //end switch
	} //end while
} //end main