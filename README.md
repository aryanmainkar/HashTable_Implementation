# Student Profile Hash Table
This is a simple implementation of a hash table for storing student profiles. The program uses a hash function to assign each student profile to a slot in the hash table. The student profiles are stored as a linked list in each slot of the hash table.

<h2 style = "font-size : 18px"; How to Use</h2>


  <li>Clone the repository to your local machine.</li>
  <li>Compile the program using the following command:</li> 

Copy code
  gcc -o hashtable hashtable.c
  Run the program using the following command:
  bash
 Copy code
./hashtable
Enter the first name of the student when prompted.
The program will display the hash value assigned to the student profile.

Code Overview
Data Structure
The program uses a linked list to store the student profiles in each slot of the hash table. Each student profile is represented by a STUDENTPROFILE struct. The struct contains the following fields:

first_name: a string representing the first name of the student.
last_name: a string representing the last name of the student.
initial: a character representing the middle initial of the student.
age: an integer representing the age of the student.
student_id: an integer representing the ID of the student.
graduation_year: an integer representing the year in which the student is expected to graduate.
current_gpa: a floating-point number representing the student's current GPA.
nextptr: a pointer to the next student profile in the linked list.
Hash Function
The hash function used in the program is a simple sum-of-ASCII-values function. The function calculates the sum of the ASCII values of the characters in the first name of the student and returns the result modulo the size of the hash table. This ensures that the hash value falls within the range of slot indices in the hash table.

Main Function
The main() function of the program prompts the user to enter the first name of the student. It then calculates the hash value for the student profile using the MyHashFunction() function and displays the result on the console.

Limitations
The hash function used in the program is very basic and may not produce a good distribution of hash values for all possible inputs. A more sophisticated hash function may be necessary for larger datasets or to ensure better collision avoidance.
The program does not provide any way to insert, update or delete student profiles in the hash table. This functionality could be added with additional code.


#Program overview

The Student Profile Management System is a program designed to manage the profiles of students enrolled in a university. The system uses hash tables to store student profiles, which include information such as the student's full name, age, student ID, graduation year, current GPA, and initial. The program provides various functionalities for managing student profiles, such as adding, deleting, and searching for student profiles.                                                 
