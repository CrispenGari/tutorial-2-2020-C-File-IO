// #include <algorithm>
#include <cmath>
// #include <cstdlib>
// #include <ctime>
// #include <afxres.h>
// #include <fstream>
// #include <sstream>
// #include <map>
// #include <vector>
// #include <string>
// //#include <Crispen.h>
// // #include <sqlite3.h/sqlite3>
// #include <utility>
// #define TRUE "true"
// #define FALSE "false"
// #include <time.h>
// #include <stdio.h>
// #include<stdlib.h>
// #include <optional>
// #include <cstdlib>
// #include <vector>
// #define PI 3.1429
// #include <iostream>

// #include <string>
// #include <iomanip>
// #include  <iterator>

// /*
// Printing hello world without writting
// anything in the main function
// */

using namespace std;
#include <iostream>
#include <string>
// int _actual_number = 19;
// int game()
// {
//     int scores = 0;
//     for (int i = 0; i < 5; i++)
//     {
//         int guessed_num;
//         cout << "Gues a number that is less than 20:    ";
//         cin >> guessed_num;
//         if (guessed_num == _actual_number)
//         {
//             cout << "You are correct!!" << endl;
//             scores++;
//         }
//         else
//         {
//             cout << "Try again" << endl;
//             scores += 0;
//         }
//     }
//     return scores;
// }
// int main()
// {
//     cout << "PLAYER 1'S TURN" << endl;
//     int player_1 = game();
//     cout << "PLAYER 2'S TURN" << endl;
//     int player_2 = game();
//     cout << "THE FINAL RESULT" << endl;
//     cout << "PLAYER 1: " << player_1 << " vrs PLAYER 2:  " << player_2 << endl;
//     return 0;
// }

#include <cstdlib>
using namespace std;
#include <iostream>
#include <string>
#include <cmath> // you can include algorithm #include <algorithm>
#include <algorithm>
#include <fstream>

/*
A file contains a record list of the following students
Name Surname StudentNo Test1 Test2 Prac1 Prac2
(populate the file with candidates of your choice)
1. Computer the average for each test and prac and display the results in an external file
2. Find the average mark for each student
3. Determine the students with pass mark and display the results on the screen (pass mark is
determined by average of both test and prac to be more or equal to 55)
4. How many students have distinctions?
*/
// An average function
int average(int total_marks, int number_of_test_or_assignment);
// The function that detemines if the student has a distinction or not
bool countDistinctions(int mark);
// a function that detemines passing or failing of student
bool passOrFail(int average_test_mark, int average_prac_mark);
// a function that writes data to files
void writtingToAFile(ofstream *filewriteObject, string name,
                     string surname, int stud_no, int test1, int test2, int prac1,
                     int prac2, int average_test, int average_prac);
int main(void)
{
    // passing a file path to the string variable path as a constructor
    string name, surname;
    int student_no, test1, test2, prac1, prac2, avg_test, avg_pract;
    string path("students.txt"); // same as string path = "students.txt"
    string path1("average.txt");
    string path3("marks.txt");
    ifstream fileObjectRead(path);
    ofstream fileObjectWrite(path1);
    ofstream fileObjectWriteAverageMarks(path3);

    if (fileObjectWrite.is_open())
    {
        fileObjectWrite << "STUDENTS AVERAGE MARKS\n";
        fileObjectWrite << "name surname studentNo test1 test2 prac1 prac2 averageTest averagePrac\n";
    }
    else
    {
        cout << "Can not write to a closed file!!\a" << endl;
    }

    /*CHECK IF THE FILE IS OPEN*/
    if (fileObjectRead.is_open())
    {
        int test = 0, practicals = 0;
        // Qn 1 writting average marks to a file average from a file students
        while (fileObjectRead >> name >> surname >> student_no >> test1 >> test2 >> prac1 >> prac2)
        {
            test = test1 + test2;
            practicals = prac1 + prac2;

            if (fileObjectWrite.is_open() && fileObjectWriteAverageMarks.is_open())
            {
                // write to the average file qn1
                writtingToAFile(&fileObjectWrite, name, surname,
                                student_no, test1, test2, prac1, prac2, average(test, 2), average(practicals, 2));
                // Qn2  write to the marks file
                writtingToAFile(&fileObjectWriteAverageMarks, name, surname,
                                student_no, test1, test2, prac1, prac2, average(test, 2), average(practicals, 2));
            }

            // restore the marks
            test = 0;
            practicals = 0;
        }
        cout << "Qn1. THE AVERAGE MARKS OF TEST AND PRACTICAL IS NOW IN A FILE NAMED: " << path1 << endl
             << endl;
        cout << "Qn2. THE AVERAGE MARKS OF TEST AND PRACTICAL FOR EACH STUDENT IS WRITTEN IN A FILE NAMED: " << path3 << endl
             << endl;
        /*
        while (!fileObjectRead.eof()){
        // do something with the file data
        }
        */
    }
    else
    {
        cout << "Can not read a closed file" << endl;
    }

    // Qn3 I can read the students average marks from a created file average
    cout << "Qn3. THE STUDENTS WHO HAVE PASSED!!" << endl;
    cout << "name surname studentNo avgTest avgPrac PASS/FAIL\n";
    //  We must close the stream we want to read before reading it
    fileObjectWriteAverageMarks.close();
    ifstream fileObjectReadPassed(path3);
    int count_passed_with_Distictions = 0;
    if (fileObjectReadPassed.is_open())
    {
        while (fileObjectReadPassed >> name >> surname >> student_no >>
               test1 >> test2 >> prac1 >> prac2 >> avg_test >> avg_pract)
        {
            string passed_or_fail = "FAIL";
            // call the function pass or fail to detemine for us
            passed_or_fail = passOrFail(avg_test, avg_pract) ? "PASS" : "FAIL";

            // Qn4. conting the number of people with distinctions based on a condition mark >=75
            int mark = .6 * avg_test + .4 * avg_pract; // ceil() round up the number
            countDistinctions(mark) && count_passed_with_Distictions++;
            cout << name << "\t" << surname << "\t" << student_no << "\t"
                 << avg_test << "\t" << avg_pract << "\t" << passed_or_fail << "\n";
        }
    }
    else
    {
        cout << "CAN NOT READ AVERAGE MARKS TO A CLOSED FILE!!" << endl;
    }
    cout << "\nQn4. THE STUDENTS WHO HAVE PASSED WITH DISTINCTIONS (mark>=75) ARE: " << count_passed_with_Distictions << endl;
    // Free up memory
    fileObjectRead.close();
    fileObjectWrite.close();
    fileObjectReadPassed.close();
    return 0;
}
int average(int total_marks, int number_of_test_or_assignment)
{
    return total_marks / number_of_test_or_assignment;
}
bool countDistinctions(int mark)
{
    // a positive mark by abs() function from the <cmath> or <algorithm>
    return abs(mark) >= 75;
}
bool passOrFail(int average_test_mark, int average_prac_mark)
{
    // for a student to pass these av_prac and av_test should be nore or equal to 55,
    return average_test_mark >= 55 && average_prac_mark >= 55;
}
void writtingToAFile(ofstream *filewriteObject, string name,
                     string surname, int stud_no, int test1, int test2, int prac1,
                     int prac2, int average_test, int average_prac)
{
    *filewriteObject << name << "\t" << surname << "\t" << stud_no << "\t" << test1 << "\t" << test2 << "\t" << prac1 << "\t" << prac2 << "\t"
                     << average_test << "\t" << average_prac << "\n";
}