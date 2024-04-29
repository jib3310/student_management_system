#include	<iostream>
#include 	<fstream>
#include	<string>
#include	<cstdlib>
#include    <iomanip>
#include	<sstream>
#include	"List.h"
#include	"Student.h"

using namespace std;


bool CreateStuList(char*, List*);
bool DeleteStudent(List*, char*);
bool PrintList(List, int);
bool InsertExamResult(char*, List*);
bool PrintStatistic(List);
bool FilterStudent(List, List*, char*, int, int);
bool UpdateIDandPhone(List*);
bool FindPotentialFirstClass(List, List*, char*);
int menu();

using namespace std;


int main() {
	char stufile[12];
	char examfile[12];
	char course_filter[1], check_course[1], course_input[1];
	int year_filter, credit_filter;
	int menu_choice, menu_choice1;
	strcpy(examfile, "exam.txt");
	strcpy(stufile, "student.txt");
	List stulist;
	List displaylist;
	Student result;
	
	while (true)
	{

	cout << "1. Create student list" << endl;
	cout << "2. Delete Student" << endl;
	cout << "3. Print student list" << endl;
	cout << "4. Insert exam result" << endl;
	cout << "5. Print Exam Statistic" << endl;
	cout << "6. Filter Student" << endl;
	cout << "7. Update Student's ID and Phone" << endl;
	cout << "8. Find Potential First Class Student" << endl;
	cout << "9. Exit." << endl;
	cout << "Please enter your choice: ";
	int option = menu();
	system("cls");
	
		if (option == 1)
		{
			if (CreateStuList(stufile, &stulist)) cout << "create done!";
			else cout << "error";
			system("pause");
			system("cls");

		}

		else if (option == 2)
		{
			cout << "enter the student ID: ";
			char num[12];
			cin >> num;
			if (DeleteStudent(&stulist, num))cout << "done";
			else cout << "no record";
			system("pause");
			system("cls");

		}

		else if (option == 3) /// 
		{
			cout << "enter the output option (1.screen, 2. student result.txt) : ";
			int optionout;
			cin >> optionout;
			if (PrintList(stulist, optionout))cout<<"done";
			system("pause");
			system("cls");
		}

		else if (option == 4)
		{
			if (InsertExamResult(examfile, &stulist))cout << "Insert done";
			else cout << "error";
			system("pause");
			system("cls");

		}

		else if (option == 5)
		{
			if(!PrintStatistic(stulist))cout<<"error";
			system("pause");
			system("cls");
		}

		else if (option == 6)
		{
			cout << "Please enter the course(CS,IA,IB,CN,CT): ";
			cin >> course_filter;
			cout << "Please enter the year(if 2012 just enter 12): ";
			cin >> year_filter;
			cout << "Please enter the total credits: ";
			cin >> credit_filter;
			system("cls");
			if (FilterStudent(stulist, &displaylist, course_filter, year_filter, credit_filter))PrintList(displaylist,1);
			else cout << "No result matches!" << endl;
			system("pause");
			system("cls");
		}

		else if (option == 7)
		{
			if (!UpdateIDandPhone(&stulist))cout << "error";
			else
			{
				cout << "upadate completed";
				system("cls");
				PrintList(stulist, 1);
			}
			system("pause");
			system("cls");
		}

		else if (option == 8)
		{
			cout << "Please enter the course(CS,IA,IB,CN,CT): ";
			cin >> course_input;
			FindPotentialFirstClass(stulist, &displaylist, course_input);
			system("cls");
			if (displaylist.empty())
				cout << "There is no student in " << course_input << " that has potential to get first class" << endl;
			else
				PrintList(displaylist, 1);
			system("pause");
			system("cls");
		}

		else if (option == 9)
		{
		break;
		
		}

		else
		{
			cout << "Error!" << endl;
			system("pause");
			system("cls");
		}
	}
	exit(1);
	system("pause");
	return 0;
}

bool CreateStuList(char* filename, List* list)
{
	if (list->size() != 0) { cout << "the list already create!"; return false; }
	ifstream inFile;
	char in_id[12];
	char in_name[30];
	char in_course[3];
	char in_phoneNum[10];
	char name2[30];
	string temp;
	Student temp_stu;
	inFile.open(filename);
	if (!inFile.is_open()) { cout << "the file cant open";	return false;}
	else
	{
		while (!inFile.eof())
		{
			for (int i = 0; i < 3; i++)inFile >> temp;//use for ignore unrevelant word
			inFile >> in_id;						  //save student id
			for (int i = 0; i < 2; i++)inFile >> temp;//
			inFile >> in_name;						  //save student first name
			inFile.getline(name2,30);				  //save student second name
			strcat(in_name, name2);					  //combine student name
			for (int i = 0; i < 2; i++)inFile >> temp;//
			inFile >> in_course;					  //save student course
			for (int i = 0; i < 3; i++)inFile >> temp;//
			inFile >> in_phoneNum;						  //save student phone number
			strcpy(temp_stu.id, in_id);				  //save student detail in a temp struct
			strcpy(temp_stu.name, in_name);			  //
			strcpy(temp_stu.course, in_course);		  //
			strcpy(temp_stu.phone_no, in_phoneNum);	  //
			list->insert(temp_stu);					  //insert temp struct in the linked list
		}
		bool duplicate = false;
		for (int i = 1; i <= list->count ;i++)		 //here is to avoid duplicate record
		{											 //
			for (int j = 1;  j <= list->count; j++)	 //node j to compare with node i
			{
				if (j == i)continue;				//avoid j == i
				if (!strcmp(list->find(i)->item.name, list->find(j)->item.name)) { duplicate = true; break; }	//when i same as j
				if (!strcmp(list->find(i)->item.id , list->find(j)->item.id)) { duplicate = true; break; }			//
				if (!strcmp(list->find(i)->item.phone_no , list->find(j)->item.phone_no)) { duplicate = true; break; }	//
			}
		}
		if (duplicate == true) //if got dupliacte record
		{
			for (int i = list->size(); i > 0; i--)
			{
				list->remove(i); //reset list2 to empty list
			}
			cout << "There is a duplicate record in student.txt"<<endl;
			return false;
		}
		inFile.close();
		return true; // sucess true;
	} 

	
}

bool DeleteStudent(List* list, char* id)
{
	for (int i = 1; i <= list->count; i++)				//find every node
	{													//
		if (strcmp(list->find(i)->item.id, id) == 0)	//compare node's id with input'id
		{												//
			list->remove(i);							//same then remove the node
			return true;								//
		}												//
	}													//
	cout << "There is no such student in the list" << endl;
	return false;										//
}

bool PrintList(List list, int option)
{
	if (list.empty()) { cout << "the list is empty!" << endl; return false; }																		    //if list is empty then out
	if (option == 1) //screen																				    //
	{																										    //
		for (int i = 1; i <= list.count; i++)																    //
		{																									    //
			cout << "student " << i<<endl;																		//cout student detail
			cout << "Name : " << list.find(i)->item.name << endl;												//list->node->item->name
			cout << "ID : " << list.find(i)->item.id << endl;													//
			cout << "Course : " << list.find(i)->item.course << endl;											//
			cout << "Phone No : " << list.find(i)->item.phone_no << endl;										//
			cout << "Current CGPA : " << list.find(i)->item.current_cgpa << endl;								//
			cout << "Total Credit Earned : " << list.find(i)->item.totalCreditsEarned << endl;					//
			cout << "Past Exam Result\n" << endl;																//
			if (list.find(i)->item.exam_cnt == 0) {
				cout << " THIS STUDENT HAVEN’T TAKEN ANY EXAM YET. \n" << endl;	//if student have not taken exam
				cout << "--------------------------------------------------------------------------------------------" << endl;
				cout << "--------------------------------------------------------------------------------------------" << endl;
			}
			else
			{
				for (int j = 0; j < list.find(i)->item.exam_cnt; j++)
				{
					cout << list.find(i)->item.exam[j].printTrimester() << " ";
					cout << list.find(i)->item.exam[j].year;
					cout << " Exam Results:"<<endl;
					cout << "------------------" << endl;
					cout << list.find(i)->item.exam[j].numOfSubjects << "subject taken\n"<<endl;

					cout << "subject code\t subject name\t\t  \t\t\t\t\t Credit hours  Grade    Grade point  "<<endl;
					for (int z = 0; z < list.find(i)->item.exam[j].numOfSubjects;z++)
					{
						cout << fixed << setprecision(5)<<showpoint;
						cout << list.find(i)->item.exam[j].sub[z].subject_code << "\t";
						cout << left << setw(62) << list.find(i)->item.exam[j].sub[z].subject_name << "\t ";
						cout << left<<setw(14)<< list.find(i)->item.exam[j].sub[z].credit_hours ;
						cout << left<<setw(9)<<list.find(i)->item.exam[j].sub[z].getGrade();
						cout << list.find(i)->item.exam[j].sub[z].getGradePoint() ;
						cout << endl;
					}
					cout << "GPA : " << list.find(i)->item.exam[j].gpa<<endl;
					cout << endl;

				}
				
			}
			cout << "--------------------------------------------------------------------------------------------" << endl;
			cout << "--------------------------------------------------------------------------------------------" << endl;
		}
		
		return true;
	}
	else if (option == 2) //txt file
	{
		ofstream outFile;																						    //
		outFile.open("student_result.txt", ios::trunc);															    //open the student_result file by trunc

		for (int i = 1; i <= list.count; i++)
		{
			outFile << "student " << i << endl;
			outFile << "Name : " << list.find(i)->item.name << endl;
			outFile << "ID : " << list.find(i)->item.id << endl;
			outFile << "Course : " << list.find(i)->item.course << endl;
			outFile << "Phone No : " << list.find(i)->item.phone_no << endl;
			outFile << "Current CGPA : " << list.find(i)->item.current_cgpa << endl;
			outFile << "Total Credit Earned : " << list.find(i)->item.totalCreditsEarned << endl;
			outFile << "Past Exam Result" << endl;
			if (list.find(i)->item.exam_cnt == 0) {
				outFile << " THIS STUDENT HAVEN’T TAKEN ANY EXAM YET. \n" << endl;
				outFile << "--------------------------------------------------------------------------------------------" << endl;
				outFile << "--------------------------------------------------------------------------------------------" << endl;
			}
			else
			{

				for (int j = 0; j < list.find(i)->item.exam_cnt; j++)
				{
					outFile  << list.find(i)->item.exam[j].printTrimester() << " ";
					outFile  << list.find(i)->item.exam[j].year;
					outFile  << " Exam Results:" << endl;
					outFile << "------------------" << endl;
					outFile  << list.find(i)->item.exam[j].numOfSubjects << "subject taken\n" << endl;
					outFile  << "subject code\t subject name\t\t  \t\t\t\t\t Credit hours  Grade    Grade point  " << endl;
					for (int z = 0; z < list.find(i)->item.exam[j].numOfSubjects; z++)
					{
						outFile  << fixed << setprecision(5) << showpoint;
						outFile  << list.find(i)->item.exam[j].sub[z].subject_code << "\t";
						outFile  << left << setw(62) << list.find(i)->item.exam[j].sub[z].subject_name << "\t ";
						outFile  << left << setw(14) << list.find(i)->item.exam[j].sub[z].credit_hours;
						outFile  << left << setw(9) << list.find(i)->item.exam[j].sub[z].getGrade();
						outFile  << list.find(i)->item.exam[j].sub[z].getGradePoint();
						outFile  << endl;
					}
					outFile << "GPA : " << list.find(i)->item.exam[j].gpa<<endl;
					outFile << endl;

				}
			}
			outFile << "--------------------------------------------------------------------------------------------" << endl;
			outFile << "--------------------------------------------------------------------------------------------" << endl;
		}
		
		return true;
		
	}
	else return false;
}

bool InsertExamResult(char* filename, List* list)
{

	const int SIZE = 10; //only max 10 subject on one sem
	ifstream inFile;
	char in_stuid[12];
	int in_sem;
	int in_year;
	int in_subNum;
	char in_subCode[SIZE][10]; //create 2d list to store if student have taken more than one exam
	char in_subName[SIZE][256];
	double in_mark[SIZE];
	int in_credit[SIZE];
	inFile.open(filename);
	if (!inFile.is_open())return false;
	while (!inFile.eof())
	{
		int student_list = 1;					//start from first node
		inFile >> in_stuid;						//read in detail
		inFile >> in_sem;
		inFile >> in_year;
		inFile >> in_subNum;
		for (int i = 0; i < in_subNum; i++) //example( take 3 num of sub then loop 3 times)
		{
			inFile >> in_subCode[i];
			inFile >> in_subName[i];
			inFile >> in_credit[i];
			inFile >> in_mark[i];
		}
		Exam temp_exam;                     // create a temp exam struct to store the value just read in
		temp_exam.trimester = in_sem;
		temp_exam.year = in_year;
		temp_exam.numOfSubjects = in_subNum;
		for (int i = 0; i < in_subNum; i++)
		{
			strcpy(temp_exam.sub[i].subject_code , in_subCode[i]);
			strcpy(temp_exam.sub[i].subject_name, in_subName[i]);
			temp_exam.sub[i].credit_hours = in_credit[i];
			temp_exam.sub[i].marks = in_mark[i];
		}

		for (int i = 1; i <= list->size(); i++)       //example if student node have 4 , then loop 4 times
		{
			if (strcmp(list->find(i)->item.id, in_stuid) == 0) break; //if student id is same as id that just read in then break
			student_list++;											  // else go to next student node
			if (student_list ==( list->size() + 1))					////cant find the exam belong to who
			{
				cout << "There is a unknown exam in the exam txt file that not belong to anyone. Please correct it!\n";
				inFile.close();
				return false;
			}
		}
		list->find(student_list)->item.exam[list->find(student_list)->item.exam_cnt] = temp_exam;    //store exam struct that just store in the student exam 
		list->find(student_list)->item.exam[list->find(student_list)->item.exam_cnt].calculateGPA(); //calculate that one exam gpa
		list->find(student_list)->item.exam_cnt++;													// exam count plus one
		list->find(student_list)->item.calculateCurrentCGPA();										// calculate that one student cgpa (all exam gpa)
	}
	inFile.close();
	return true;
}

bool UpdateIDandPhone(List* list)
{
	if (list->empty())return false;						//if list is empty
	for (int i = 1; i <= list->count; i++)
	{
		char temp_id[14] = "";
		strcpy(temp_id, "B");                        //Bxxxxxxxxx
		strcat(temp_id, list->find(i)->item.course); //BCSxxxxxxx
		strcat(temp_id, list->find(i)->item.id);	 //BCS1234567
		strcpy(list->find(i)->item.id, temp_id);	 //update student id

	}
	for (int i = 1; i <= list->count; i++)
	{
		char temp_phone[10] = "";

		if ((list->find(i)->item.phone_no[0]- '0') % 2 == 0) //is even
		{
			strcpy(temp_phone, "02");
			for (int j = 2; j < 5; j++)temp_phone[j] = list->find(i)->item.phone_no[j-2];          //02123xxxx	
			for (int j = 5; j < 9; j++)temp_phone[j] = list->find(i)->item.phone_no[j-1];            //021234567
			strcpy(list->find(i)->item.phone_no, temp_phone);
		}
		else                                          // is odd
		{
			strcpy(temp_phone, "01");
			for (int j = 2; j < 5; j++)temp_phone[j] = list->find(i)->item.phone_no[j-2];           //01123xxxx	
			for (int j = 5; j < 9; j++)temp_phone[j] = list->find(i)->item.phone_no[j-1];            //011234567
			strcpy(list->find(i)->item.phone_no, temp_phone);
		}
	}
	return true;
}

bool PrintStatistic(List list)
{
	int  cs = 0, ia = 0, ib = 0, cn = 0, ct = 0, sem = 0;
	double gpa = 0, subject = 0, credit = 0;
		if (list.empty())return false;
		else
		{
			for (int i = 1; i <= list.count; i++)
			{
				{
					if (strcmp(list.find(i)->item.course, "CS") == 0)
						cs++;
					else if (strcmp(list.find(i)->item.course, "IA") == 0)
						ia++;
					else if (strcmp(list.find(i)->item.course, "IB") == 0)
						ib++;
					else if (strcmp(list.find(i)->item.course, "CN") == 0)
						cn++;
					else if (strcmp(list.find(i)->item.course, "CT") == 0)
						ct++;
				}
				list.find(i)->item.current_cgpa;
				if (list.find(i)->item.current_cgpa < 4.01000) //calculate number of sem
					sem++;
				gpa = gpa + list.find(i)->item.current_cgpa; //get total gpa
				for (int j = 0; j <= list.find(j)->item.exam_cnt;j++)subject = subject + list.find(i)->item.exam[j].numOfSubjects;
				credit = credit + list.find(i)->item.totalCreditsEarned; //get total credit
			}
				
		}
		cout << "Total students: " << list.count << endl;
		cout << "\tCS students: " << cs << endl;
		cout << "\tIA students: " << ia << endl;
		cout << "\tIB students: " << ib << endl;
		cout << "\tCN students: " << cn << endl;
		cout << "\tCT students: " << ct << endl;
		cout << "\nAverage CGPA: " << gpa / list.count << endl;
		cout << "Average Subjects Taken Per Semester: " << subject / sem << endl;
		cout << "Average Credits Earned Per Semester: " << credit / sem << endl;
		return true;
}

bool FilterStudent(List list1, List* list2, char* course, int year, int totalcredit)
{
	int credit_find = 0, year_find;
	string first_two;
	if (list1.empty())return false;
	if (!list2->empty())
	{
		for (int i = list2->size(); i > 0; i--)
		{
			list2->remove(i); //reset list2 to empty list
		}
	}
		for (int i = 1; i <= list1.count; i++)
		{
			first_two.push_back(list1.find(i)->item.id[0]); //extract first two digit of id from list
			first_two.push_back(list1.find(i)->item.id[1]);
			stringstream ss;
			ss << first_two;
			ss >> year_find;//convert string type to int
			credit_find =  list1.find(i)->item.totalCreditsEarned;//credit_find +
			if (strcmp(list1.find(i)->item.course, course) == 0 && (year_find == year) && (credit_find >= totalcredit))
			{
				list2->insert(list1.find(i)->item);
			}
			first_two = " ";//reset value to loop again
			credit_find = 0;
		}
		if (list2->empty())return false;
		return true;
	
}

bool FindPotentialFirstClass(List list1, List* list2, char* course)
{
	if (list1.empty())return false;
	for (int i = list2->size(); i >0; i--)
	{
		list2->remove(i);//reset list 2 to empty list
	}
	
		for (int i = 1; i <= list1.size(); i++)
		{
			int gpa_count = 0, subject_count = 0 ;
			bool next = false;
			if (!(strcmp(list1.find(i)->item.course, course) == 0))continue;//compare course input with course in list if not jump to next node
			if ((list1.find(i)->item.totalCreditsEarned) <= 12)continue;//if not over 12 chour go to next node
			for (int j = 0; j < list1.find(i)->item.exam_cnt; j++)subject_count = subject_count + list1.find(i)->item.exam[j].numOfSubjects;//total up all exam subject
			if (subject_count < 3)continue; //if less than 3 subject go to next node
			for (int j = 0; j < list1.find(i)->item.exam_cnt; j++)
				{
					if ((list1.find(i)->item.exam[j].gpa < 3.50000))
					{
						next = true;
					}//gpa less than 3.50000 break directly n go to next node
				}
			if (next == true)continue;
				for (int j = 0; j < list1.find(i)->item.exam_cnt; j++) // 
				{
					if ((list1.find(i)->item.exam[j].gpa >= 3.75000))
					{
						gpa_count++; // when gpa exceeds 3.75
					}
				}
				if (gpa_count >= 3) list2->insert(list1.find(i)->item);//ensure at least 3 sem gpa over 3.75
		}
}


int menu()
{
	int menu_choice;
	cin >> menu_choice;
	return menu_choice;
}