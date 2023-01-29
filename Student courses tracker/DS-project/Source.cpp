#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include<unordered_map>
#include<iterator>

using namespace std;

struct student
{
	string  password;
	int ID, Ac_year, Fsize, Psize;
	string* finishedCourses ;
	string* progressCourses ;

};
struct course
{
	int code, MaxNumStudents, hours, Pre_size;
	string *pre_Courses = new string[Pre_size];
};

string user_name;
unordered_map<string, student>Student_map;
unordered_map<string, student>::iterator StudentIT;
unordered_map<string, course>course_map;
unordered_map<string, course>::iterator courseIT;

ofstream myfile("student.txt", ios::app);
ofstream myfile2("course.txt", ios::app);
ifstream myfileread("student.txt");
ifstream myfile2read("course.txt");

int choise, login_choise,Avcourses=0, precount=0;
char ch;
string userName, userPass, adminName, adminPass;
string *available = new string[20];
student NewOne;
course NewCourse;
string CourseName , getName , wantedCourse , StudentName;


void show_courses_tree()
{


}

void Available_Course(unordered_map<string, student>Student_map, unordered_map<string, student>::iterator StudentIT, unordered_map<string, course>course_map, unordered_map<string, course>::iterator courseIT)
{
	int studentCount=0 ,k=0  ;

	for (courseIT = course_map.begin(); courseIT != course_map.end(); courseIT++)
	{
		studentCount = 0;
		for (StudentIT = Student_map.begin(); StudentIT != Student_map.end(); StudentIT++)
		{
			for (int i=0 ; i< StudentIT->second.Psize ; i++)
			{
				if (courseIT->first == StudentIT->second.progressCourses[i])
				{
					studentCount++;
					break;
				}
			}

		}
		if (studentCount < courseIT->second.MaxNumStudents)
		{
			available[k] = courseIT->first;
			k++;
		}
	}
	Avcourses = k;

}

void View_my_courses(unordered_map<string, student>Student_map, unordered_map<string, student>::iterator StudentIT)
{
	for (StudentIT = Student_map.begin(); StudentIT != Student_map.end(); StudentIT++)
	{
		if (userName == StudentIT->first)
		{
			cout << " here are the courses you finished : " << endl;
			for (int i = 0; i < StudentIT->second.Fsize; i++)
			{
				cout << StudentIT->second.finishedCourses[i] << endl;
			}
			cout <<endl << " here are the courses you are taking now : " << endl;
			for (int i = 0; i < StudentIT->second.Psize; i++)
			{
				cout << StudentIT->second.progressCourses[i] << endl;
			}
			break;
		}

	}
}

void Edit_my_data(unordered_map<string, student>Student_map, unordered_map<string, student>::iterator StudentIT)
{
	int NEWpass , NEWacademic;
	for (StudentIT = Student_map.begin(); StudentIT != Student_map.end(); StudentIT++)
	{
		if (userName == StudentIT->first)
		{
			cout << "choose the info you want to edit : " << endl;
			cout << "1)Edit my password ." << endl;
			cout << "2)Edit my academic year ." << endl;
			cin >> choise;
			if (choise == 1)
			{
				cout << "Enter your new password : ";
				cin >> NEWpass;
				StudentIT->second.password = NEWpass;
				break;

			}
			else if (choise == 2)
			{
				cout << "Enter your academic year : ";
				cin >> NEWacademic;
				StudentIT->second.Ac_year = NEWacademic;
				break;
			}


		}

	}
	choise = 0;
}

void Register(unordered_map<string, student>Student_map, unordered_map<string, student>::iterator StudentIT, unordered_map<string, course>course_map, unordered_map<string, course>::iterator courseIT)
{
	if (Avcourses == 0)
		cout << " there is no available course now ." << endl;
	else 
		for (int i = 0; i < Avcourses; i++)
		{
			cout << i + 1 << ')' << available[i] << endl;
		}
	cin >> choise;
	for (int i = 0; i < Avcourses; i++)
	{
		if (choise == i + 1)
		{
			for (courseIT = course_map.begin(); courseIT != course_map.end(); courseIT++)
			{
				if (available[i] == courseIT->first)
				{
					for (StudentIT = Student_map.begin(); StudentIT != Student_map.end(); StudentIT)
					{
						if(userName==StudentIT->first)
						{
							for (int m = 0; m < courseIT->second.Pre_size; m++)
							{
								for (int j = 0; j <StudentIT->second.Fsize; j++)
								{
									if (courseIT->second.pre_Courses[m] == StudentIT->second.finishedCourses[j])
										precount++;
								}
							}
							if (precount == courseIT->second.Pre_size)
							{
								StudentIT->second.Psize = StudentIT->second.Psize + 1;
								StudentIT->second.progressCourses[StudentIT->second.Psize] = courseIT->first;
							}
						}
					}

				}
			}
		}
	}

}

void view_details_ofCourse(unordered_map<string, course>course_map, unordered_map<string, course>::iterator courseIT)
{
	int i = 1;
	cout << " Choose the course you want to view its details : " << endl;
	for (courseIT = course_map.begin(); courseIT != course_map.end(); courseIT++)
	{
		cout << i << ') ' << courseIT->first << endl;
		i++;
	}
	i = 1;
	cin >> choise;
	for (courseIT = course_map.begin(); courseIT != course_map.end(); courseIT++)
	{
		if (choise == i)
		{
			cout << "course name : " << courseIT->first << endl;
			cout << " course code : " << courseIT->second.code << endl;
			cout << " course hours : " << courseIT->second.hours << endl;
			cout << " course maximum number of students : " << courseIT->second.MaxNumStudents << endl;
			cout << " course pre-courses : " << endl;
			for (int k = 0; k < courseIT->second.Pre_size; k++)
			{
				cout << courseIT->second.pre_Courses[k] << endl;
			}
			break;
		}
		i++;
	}
	choise = 0;
}

void Student_form(unordered_map<string, student>Student_map, unordered_map<string, student>::iterator StudentIT, unordered_map<string, course>course_map, unordered_map<string, course>::iterator courseIT)
{
	cout << " choose the action you want to do :" << endl;
	cout << "1)View details of a specific course." << endl;
	cout << "2)Register for a course." << endl;
	cout << "3)View all your courses ." << endl;
	cout << "4)Edit your data ." << endl;

	cin >> choise;

	if (choise == 1)
	{
		view_details_ofCourse(course_map, courseIT);
	}
	else if (choise == 2)
	{
		Register(Student_map, StudentIT, course_map, courseIT);
	}
	else if (choise == 3)
	{
		View_my_courses(Student_map, StudentIT);
	}
	else if (choise == 4)
	{
		Edit_my_data(Student_map,StudentIT);
	}
	else
		cout << " you didn't choose a number from the list .";
	choise = 0;
}

// admin form start here 


void Add_new_student(unordered_map<string, student>Student_map)
{
	cout << " Enter the student name : ";
	cin >> StudentName;
	cout << endl;

	cout << "Enter the student password : ";
	cin >> NewOne.password;
	cout << endl;

	cout << "Enter the student ID: ";
	cin >> NewOne.ID;
	cout << endl;

	cout << "Enter the student academic year : ";
	cin >> NewOne.Ac_year;
	cout << endl;

	cout << "Enter the number of finished courses : ";
	cin >> NewOne.Fsize;
	cout << endl;
	NewOne.finishedCourses = new string[NewOne.Fsize];

	cout << "Enter the student's finished courses : ";
	for (int i = 0; i < NewOne.Fsize; i++)
	{
		cin >> NewOne.finishedCourses[i];
	}
	cout << endl;

	cout << "Enter the number of courses in progress: ";
	cin >> NewOne.Psize;
	cout << endl;
	NewOne.progressCourses = new string[NewOne.Psize];

	cout << "Enter the student's courses in progress: ";
	for (int i = 0; i < NewOne.Psize; i++)
	{
		cin >> NewOne.progressCourses[i];
	}
	cout << endl;
	//Student_map[StudentName] = NewOne;

	Student_map.insert(make_pair(StudentName, NewOne));

	for (StudentIT = Student_map.begin(); StudentIT != Student_map.end(); StudentIT++)
	{
		cout << StudentIT->first << endl << StudentIT->second.Ac_year << endl << StudentIT->second.ID;
	}


	return;
}

void Add_new_course(unordered_map<string, course>course_map)
{
	cout << "Enter the course name : ";
	cin >> CourseName;
	cout << endl;

	cout << "Enter the course code : ";
	cin >> NewCourse.code;
	cout << endl;

	cout << "Enter the course maximum number of students : ";
	cin >> NewCourse.MaxNumStudents;
	cout << endl;

	cout << "Enter the course hours : ";
	cin >> NewCourse.hours;
	cout << endl;

	cout << "Enter the number of pre-courses : ";
	cin >> NewCourse.Pre_size;
	cout << endl;
	NewCourse.pre_Courses = new string[NewCourse.Pre_size];

	cout << "Enter the pre-courses : ";
	for (int i = 0; i < NewCourse.Pre_size; i++)
	{
		cin >> NewCourse.pre_Courses[i];
	}
	cout << endl;

	//course_map[CourseName] = NewCourse ;
	course_map.insert(pair<string, course>(CourseName, NewCourse));
}

void View_list_of_allStudents(unordered_map<string, student>Student_map, unordered_map<string, student>::iterator StudentIT, unordered_map<string, course>course_map, unordered_map<string, course>::iterator courseIT)
{
	int i = 1;
	cout << " Choose the course you want its students : " << endl;
	courseIT = course_map.begin();
		while (courseIT != course_map.end())
		{
			cout << i << ') ' << courseIT->first << endl;
			courseIT++;
			i++;
		}

	i = 1;
	cin >> choise;
	for (courseIT = course_map.begin(); courseIT != course_map.end(); courseIT++)
	{
		if (choise == i)
		{
			wantedCourse = courseIT->first;
			break;
		}
		i++;
	}
	choise = 0;

	for (StudentIT = Student_map.begin(); StudentIT != Student_map.end(); StudentIT++)
	{ for( int i=0 ; i< StudentIT->second.Psize ; i++)
		if (wantedCourse == StudentIT->second.progressCourses[i])
		{
			cout << StudentIT->first << endl;
			break;
		}
	}
}

void View_list_of_allCourses(unordered_map<string, student>Student_map, unordered_map<string, student>::iterator StudentIT)
{

	cout << "Enter the name of the student you want : ";
	cin >> getName;

	for ( StudentIT=Student_map.begin(); StudentIT!=Student_map.end() ; StudentIT++)
	{
		if (getName == StudentIT->first)
		{
			cout << "The finished courses are : "; 
			 for (int i=0 ; i < StudentIT->second.Fsize ; i++)
			{
				 cout << StudentIT->second.finishedCourses[i] << endl;
			}
			 cout << "The courses in progress are : ";
			 for (int i = 0; i < StudentIT->second.Psize; i++)
			 {
				 cout << StudentIT->second.progressCourses[i] << endl;
			 }
		}
	}

}

void Edit_data(unordered_map<string, course>course_map, unordered_map<string, course>::iterator courseIT)
{
	int i = 1 ,newHour ,newMaxNum;

	cout << " Choose the course you want to edit : " << endl;
	for (courseIT = course_map.begin(); courseIT != course_map.end(); courseIT++)
	{
		cout << i << ') ' << courseIT->first << endl;
		i++;
	}
	i = 1;
	cin >> choise;
	for (courseIT = course_map.begin(); courseIT != course_map.end(); courseIT++)
	{
		if (choise == i)
		{
			choise = 0;
			cout << "Select the info you want to change : " << endl;
			cout << "1) the course hours" << endl;
			cout << "2) the course maximuam number of students " << endl;
			cout << "3) the course pre-requiered courses list " << endl;
			cin >> choise;
			if (choise == 1)
			{
				cout << " enter the new hours number :";
				cin >> newHour;
				courseIT->second.hours = newHour;
			}
			else if (choise == 2)
			{
				cout << " enter the new maximum number of students :";
				cin >> newMaxNum;
				courseIT->second.MaxNumStudents = newMaxNum;
			}
			else if (choise == 3)
			{
				string addPreCourse;
				choise = 0;
				cout << "choose the action you want to do :" << endl;
				cout << "1)add another pre-course ." << endl;
				cout << "2)delete a pre-course ." << endl;
				cin >> choise;
				if (choise == 1)
				{
					courseIT->second.Pre_size = courseIT->second.Pre_size + 1;
					cout << " enter the new pre course name : ";
					cin >> addPreCourse;
					courseIT->second.pre_Courses[courseIT->second.Pre_size] = addPreCourse;
				}
				else if (choise == 2)
				{
					choise = 0;
					int k = 1;
					for (int i = 0; i < courseIT->second.Pre_size; i++)
					{
						cout << k << ')' << courseIT->second.pre_Courses[i];
							k++;
					}
					k = 1;
					cin >> choise;
					for (int i = 0; i < courseIT->second.Pre_size; i++)
					{
						if (choise == k)
						{
							for (int m = choise - 1; m < courseIT->second.Pre_size; m++)
							{
								courseIT->second.pre_Courses[m] = courseIT->second.pre_Courses[m + 1];
							}
							courseIT->second.Pre_size--;
						}
					}

				}
			}

		}
		i++;
	}
	choise = 0;

}

void From_Pre_to_Finished()
{

}

void Admin_form(unordered_map<string, student>Student_map, unordered_map<string, student>::iterator StudentIT, unordered_map<string, course>course_map, unordered_map<string, course>::iterator courseIT)
{
	do
	{
		cout << " choose the action you want to do :" << endl;
		cout << "1)Add new student." << endl;
		cout << "2)Add new course." << endl;
		cout << "3)View list of all students in a specific course." << endl;
		cout << "4)View list of all courses ( finished - progressed ) of a specific student ." << endl;
		cout << "5)Edit a course data ." << endl;
		cout << "6)Mark a course as finished ." << endl;
		cout << "7)to log out ." << endl;

		cin >> choise;
		if (choise == 1)
		{
			Add_new_student(Student_map);
		}
		else if (choise == 2)
		{
			Add_new_course(course_map);
		}
		else if (choise == 3)
		{
			View_list_of_allStudents(Student_map, StudentIT, course_map, courseIT);
		}
		else if (choise == 4)
		{
			View_list_of_allCourses(Student_map, StudentIT);
		}
		else if (choise == 5)
		{
			Edit_data(course_map, courseIT);
		}
		else if (choise == 6)
		{
			From_Pre_to_Finished();
		}
		else if (choise == 7) 
			break;
		else
			cout << " you didn't choose a number from the list .";
		
	} while (true);
	Admin_form(Student_map, StudentIT, course_map, courseIT);
	choise = 0;
}

void check_student(unordered_map<string, student> Student_map, unordered_map<string, student>::iterator StudentIT)
{
	cout << " please enter your user name :";
	cin >> userName;
	cout << endl;
	cout << " please enter your password :";
	ch = _getch();
	while (ch != 13)
	{
		userPass.push_back(ch);
		cout << '*';
		ch = _getch();
	}
	for (StudentIT = Student_map.begin(); StudentIT != Student_map.end(); StudentIT++)
	{
		if (userName == StudentIT->first)
		{
			if (userPass == StudentIT->second.password)
			{
				Student_form(Student_map, StudentIT, course_map, courseIT);
			}
			else
			{
				cout << " The entered password is wrong. ";
				
			}
		}

	}
	cout << " The entered user name is wrorg .";
}

void login(unordered_map<string, student>Student_map , unordered_map<string, student>::iterator StudentIT)
{
	cout << " Login as : " << endl;
	cout << "1)Admin " << endl << "2)student " << endl;
	cin >> login_choise;
	if (login_choise == 1)
	{
		cout << " please enter your user name :";
		cin >> adminName;
		cout << endl;
		cout << " please enter your password :";
		ch = _getch();
		while (ch != 13)
		{
			adminPass.push_back(ch);
			cout << '*';
			ch = _getch();
		}
		if (adminName == "admin" && adminPass == "0000")
		{
			Admin_form(Student_map,StudentIT, course_map , courseIT);
		}
		else
			cout << "you entered a wrong user name or password ." ;
	}
	else if (login_choise == 2)
	{

		check_student(Student_map, StudentIT);

	}
}

int main()
{

	login(Student_map, StudentIT);

	system("pause");
	return 0;
 }