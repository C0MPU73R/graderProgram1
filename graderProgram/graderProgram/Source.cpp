/*
Purpose: Program asks user for student and answer key text files, computes final grades, highest grade, lowest grade, and average.
Prints student ID, name, and grade information to the screen as well as an output file called "classgrades.txt"
*/
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#define outFile "classgrades.txt"
const int SIZE = 100;
//structures
struct student
{
	int id;
	string firstName;
	string lastName;
	string answers;
	float totalGrade;
	char letterGrade;
};
//prototypes
string getStuFilename();
string getAnsFilename();
void fillArrayAndCalculate(ofstream&, ifstream&, student[], int&, float, string);
void readAnswerFile(ifstream&, float&, string&);
void gradeStuAnswers(student[], int, float, string);
void findTotalAndLetterGrade(student[], float, int, float);
char findLetterGrade(float);
float calculateMaxTotalGrade(student[], int);
float calculateMinTotalGrade(student[], int);
float calculateAvgTotalGrade(student[], int);
void convertToLower(string&);
void stuStatsToScreenAndFile(ofstream&, student[], int);
void gradeStatsToScreenAndFile(ofstream&, student[], int);
/*
Purpose: Creates, opens, and closes text files as well as calls the functions readAnswerFile, fillArrayAndCalculate,
and gradeStatsToScreenAndFile.
*/
int main()
{
	float numberOfQuestions;
	string keyAnswers;
	student studentArray[SIZE];
	ifstream ins;
	ifstream ins2;
	ofstream pds;
	string stuFileName = getStuFilename();
	string ansFileName = getAnsFilename();
	ins.open(stuFileName);
	ins2.open(ansFileName);
	pds.open(outFile);
	if (ins.fail())
	{
		cout << "***ERROR: Cannot open " << stuFileName << " for input.***" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	if (ins2.fail())
	{
		cout << "***ERROR: Cannot open " << ansFileName << " for input.***" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	int numberOfStudents = 0;
	readAnswerFile(ins2, numberOfQuestions, keyAnswers);
	fillArrayAndCalculate(pds, ins, studentArray, numberOfStudents, numberOfQuestions, keyAnswers);
	gradeStatsToScreenAndFile(pds, studentArray, numberOfStudents);
	ins.close();
	ins2.close();
	pds.close();
	system("pause");
	return 0;
}
/*
Purpose: Asks user for student file name and returns the student file name.
*/
string getStuFilename()
{
	string stuFilename;
	cout << "Enter student file name: ";
	cin >> stuFilename;
	return stuFilename;
}
/*
Purpose: Asks user for answer file name and returns the answer file name.
*/
string getAnsFilename()
{
	string ansFilename;
	cout << "Enter answer file name: ";
	cin >> ansFilename;
	return ansFilename;
}
/*
Purpose: Fills the array fo students and calls the functions gradeStuAnswers and stuStatsToScreenAndFile for each student until the
program reaches the end of the file.
*/
void fillArrayAndCalculate(ofstream& pds, ifstream& ins, student studentArray[], int& numberOfStudents, float numberOfQuestions, string keyAnswers)
{
	while (!ins.eof())
	{
		//importing all information about each student and converting their answers to lower case.
		ins >> studentArray[numberOfStudents].id;
		ins >> studentArray[numberOfStudents].firstName;
		ins >> studentArray[numberOfStudents].lastName;
		ins >> studentArray[numberOfStudents].answers;
		convertToLower(studentArray[numberOfStudents].answers);
		//pass student information into gradeStuAnswers to be graded.
		gradeStuAnswers(studentArray, numberOfStudents, numberOfQuestions, keyAnswers);
		//call stuStatsToScreenAndFile to display basic information about them to screen and file
		stuStatsToScreenAndFile(pds, studentArray, numberOfStudents);
		numberOfStudents++;
	}
}
/*
Purpose: Reads answers.txt file and calls string converter function.
*/
void readAnswerFile(ifstream& ins, float& question, string& keyAnswers)
{
	//import number of questions and answer key.
	//convert string of answer key to lower case.
	ins >> question;
	ins >> keyAnswers;
	convertToLower(keyAnswers);
}
/*
Purpose: Compares students' answers to answer key and keeps track of how many they got right and wrong through a counter.
Then calls findTotalAndLetter grade to convert the score to a score out of 100 and a letter grade.
*/

void gradeStuAnswers(student studentArray[], int numberOfStudents, float numberOfQuestions, string keyAnswers)
{
	//if the current character of the student is the sanem as the character in the answer key, score is incremented
	//by one. Other wise score stays the same.
	float score = 0.0;
	for (int i = 0; i < numberOfQuestions; i++) {
		if (studentArray[numberOfStudents].answers[i] == keyAnswers[i])
		{
			score++;

		}
		else if (studentArray[numberOfStudents].answers[i] != keyAnswers[i])
		{
			score = score;

		}
	}
	findTotalAndLetterGrade(studentArray, score, numberOfStudents, numberOfQuestions);
}
/*
Purpose: Converts student score to a score out of 100. Stores score in totalGrade struct for the student. Calls findLetterGrade
to compute the score to a letter grade, then stores that letter grade in the letterGrade struct for the student.
*/
void findTotalAndLetterGrade(student studentArray[], float score, int numberOfStudents, float numberOfQuestions)
{
	//converting score to a percent
	studentArray[numberOfStudents].totalGrade = (score / numberOfQuestions) * 100;
	float newScore = studentArray[numberOfStudents].totalGrade;
	//converting score to corresponding letter grade
	studentArray[numberOfStudents].letterGrade = findLetterGrade(newScore);
}
/*
Purpose:Converts score out of 100 to a corresponding letter grade.
*/
char findLetterGrade(float newScore)
{
	char result;
	if (newScore >= 90)
	{
		result = 'A';
	}
	else if (newScore < 90 && newScore >= 80)
	{
		result = 'B';
	}
	else if (newScore < 80 && newScore >= 70)
	{
		result = 'C';
	}

	else if (newScore < 70 && newScore >= 60)
	{
		result = 'D';
	}
	else if (newScore < 60 && newScore >= 50)
	{
		result = 'E';
	}
	else if (newScore < 50)
	{
		result = 'F';
	}
	return result;
}
/*
Purpose: Calculates the highest grade in the class.
*/
float calculateMaxTotalGrade(student studentArray[], int numberOfStudents)
{
	//starts max at 0. If the next value is greater than the previous one, we update the max value, then return.
	float max = 0;
	for (int i = 0; i < numberOfStudents; i++)
		if (studentArray[i].totalGrade > max)
		{
			max = studentArray[i].totalGrade;
		}
	return max;
}
/*
Purpose: Calculates the lowest grade in the class.
*/
float calculateMinTotalGrade(student studentArray[], int numberOfStudents)
{
	//start minimum at 100, if the next value is less than the previous one, we update the min value, then return.
	float min = 100;
	for (int i = 0; i < numberOfStudents; i++)
		if (studentArray[i].totalGrade < min)
		{
			min = studentArray[i].totalGrade;
		}
	return min;
}
/*
Purpose: Calculates the average grade of the class.
*/
float calculateAvgTotalGrade(student studentArray[], int numberOfStudents)
{
	//start average at 0. Update through addition, until we reach the end of the number of students. Then this sum of grades
	//is divided by the number of students, creating an average.
	float avg = 0;

	for (int i = 0; i < numberOfStudents; i++)
	{
		avg = avg + studentArray[i].totalGrade;
	}

	avg = avg / numberOfStudents;
	return avg;
}
/*
Purpose: Converts input string to all lowercase characters in the string.
*/
void convertToLower(string& input)
{
	//Using a for loop, we convert each character of the string to to lower case, using the function tolower.
	for (int i = 0; i < input.size(); i++)
	{
		input.at(i) = tolower(input.at(i));
	}
}
/*
Purpose: Presents the student statistics to the screen and to the output file for all students.
*/
void stuStatsToScreenAndFile(ofstream& pds, student studentArray[], int numberOfStudents)
{
	pds << studentArray[numberOfStudents].id;
	pds << " " << studentArray[numberOfStudents].firstName;
	pds << " " << studentArray[numberOfStudents].lastName;
	pds << " " << studentArray[numberOfStudents].totalGrade << "%";
	pds << " " << studentArray[numberOfStudents].letterGrade << endl;
	cout << studentArray[numberOfStudents].id;
	cout << " " << studentArray[numberOfStudents].firstName;
	cout << " " << studentArray[numberOfStudents].lastName;
	cout << " " << studentArray[numberOfStudents].totalGrade << "%";
	cout << " " << studentArray[numberOfStudents].letterGrade << endl;

}
/*
Purpose: Presents the grade statistics of the students to the screen and to the output file.
*/
void gradeStatsToScreenAndFile(ofstream& pds, student studentArray[], int numberOfStudents)
{
	pds << endl;
	pds << "***GRADE STATISTICS***" << endl;
	float average = calculateAvgTotalGrade(studentArray, numberOfStudents);
	float max = calculateMaxTotalGrade(studentArray, numberOfStudents);
	float min = calculateMinTotalGrade(studentArray, numberOfStudents);
	pds << "Highest grade: " << calculateMaxTotalGrade(studentArray, numberOfStudents) << "% ";
	pds << findLetterGrade(max) << endl;
	pds << "Lowest grade: " << calculateMinTotalGrade(studentArray, numberOfStudents) << "% ";
	pds << findLetterGrade(min) << endl;
	pds << "Average grade: " << calculateAvgTotalGrade(studentArray, numberOfStudents) << "%" << endl;
	pds << "Average letter grade: " << findLetterGrade(average) << endl;
	pds << "Number of processed students: " << numberOfStudents << endl;
	cout << endl;
	cout << "***GRADE STATISTICS***" << endl;
	cout << "Highest grade: " << calculateMaxTotalGrade(studentArray, numberOfStudents) << "% ";
	cout << findLetterGrade(max) << endl;
	cout << "Lowest grade: " << calculateMinTotalGrade(studentArray, numberOfStudents) << "% ";
	cout << findLetterGrade(min) << endl;
	cout << "Average grade: " << calculateAvgTotalGrade(studentArray, numberOfStudents) << "%" << endl;
	cout << "Average letter grade: " << findLetterGrade(average) << endl;
	cout << "Number of processed students: " << numberOfStudents << endl;
}