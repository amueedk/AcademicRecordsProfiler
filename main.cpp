#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <unordered_map>
using namespace std;

class Student
{
public:
    string SID;
    string St_Name;
    string Father_Name;
    string Gender;
    string Address;
    string city_name;
    string DOB;
    string Reg_Date;
    string Reg_Status;
    string Degree_Status;
    string Last_Degree;
};

class Course
{
public:
    string SID;
    string Degree;
    string Semester;
    string Course_Code;
    string Marks;
    string discipline;
};

string ConvertDate(string date)
{
    vector<string> dateParts;
    string part;
    for (char c : date)
    {
        if (c == '-')
        {
            dateParts.push_back(part); // feeds part before - say 01-02-94 i.e 01 and then 02
            part = "";
        }
        else
        {
            part += c;
        }
    }
    dateParts.push_back(part); // 94 part
    string monthAbbreviation;
    if (dateParts[1] == "01" || dateParts[1] == "1")
    {
        monthAbbreviation = "Jan";
    }
    else if (dateParts[1] == "02" || dateParts[1] == "2")
    {
        monthAbbreviation = "Feb";
    }
    else if (dateParts[1] == "03" || dateParts[1] == "3")
    {
        monthAbbreviation = "Mar";
    }
    else if (dateParts[1] == "04" || dateParts[1] == "4")
    {
        monthAbbreviation = "Apr";
    }
    else if (dateParts[1] == "05" || dateParts[1] == "5")
    {
        monthAbbreviation = "May";
    }
    else if (dateParts[1] == "06" || dateParts[1] == "6")
    {
        monthAbbreviation = "Jun";
    }
    else if (dateParts[1] == "07" || dateParts[1] == "7")
    {
        monthAbbreviation = "Jul";
    }
    else if (dateParts[1] == "08" || dateParts[1] == "8")
    {
        monthAbbreviation = "Aug";
    }
    else if (dateParts[1] == "09" || dateParts[1] == "9")
    {
        monthAbbreviation = "Sep";
    }
    else if (dateParts[1] == "10")
    {
        monthAbbreviation = "Oct";
    }
    else if (dateParts[1] == "11")
    {
        monthAbbreviation = "Nov";
    }
    else if (dateParts[1] == "12")
    {
        monthAbbreviation = "Dec";
    }
    return dateParts[0] + "-" + monthAbbreviation + "-" + dateParts[2];
}

bool IsNameInFile(string name, string fileName)
{
    ifstream openfile(fileName);
    string line;
    while (getline(openfile, line))
    {
        if (line == name)
        {
            return true;
        }
    }
    return false;
}

bool isNameAlreadyExists(const string filename, const string name)
{
    ifstream file(filename);
    string line;

    while (getline(file, line))
    {
        if (line == name)
        {
            return true;
        }
    }

    return false;
}

void writeToGenderFile(const Student student)
{
    ofstream outfile2;
    string f;
    if (student.Gender == "M")
    {
        f = "malenames.txt";
        outfile2.open("malenames.txt", ios_base::app);
    }
    else if (student.Gender == "F")
    {
        f = "femalenames.txt";
        outfile2.open("femalenames.txt", ios_base::app);
    }

    string firstname;

    for (char x : student.St_Name)
    {
        if (x == ' ' || x == '.')
        {
            break; // Stop extracting after encountering a space or period
        }
        else
        {
            firstname += x;
        }
    }

    if (firstname.length() < 3)
    {
        string secondname;
        bool foundSpace = false;

        for (char x : student.St_Name)
        {
            if (x == ' ')
            {
                foundSpace = true;
            }
            else if (foundSpace)
            {
                secondname += x;
            }
        }

        if (!secondname.empty())
        {
            firstname = secondname;
        }
    }

    if (!isNameAlreadyExists(f, firstname))
    {
        outfile2 << firstname << endl;
    }

    outfile2.close();
}

string standardizeCityName(const string &city)
{
    string standardizedCity = city;
    transform(standardizedCity.begin(), standardizedCity.end(), standardizedCity.begin(), ::tolower);

    // Handle specific city mappings
    unordered_map<string, string> cityMappings = {
        {"dg khan", "Dera Ghazi Khan"},
        {"di khan", "Dera Ismail Khan"},
        {"lhr", "Lahore"},
        {"shekhopura", "Sheikhupura"},
        {"isb", "Islamabad"},
        {"khan", "Dera Ghazi Khan"},
        {"rwp", "Rawalpindi"},
        {"dgk", "Dera Ghazi Khan"},
        {"mul", "Multan"},
        {"mux", "Multan"},
        {"fsb", "Faislabad"},
        {"kar", "Karachi"},
        {"sheikhapura", "Sheikhupura"},
        {"psh", "Peshawar"},
        {"bhv", "Bahawalpur"},
        {"lhe", "Lahore"},
        {"noshera", "Nowshera"},
        {"fsd", "Faislabad"},
        {"khi", "Karachi"}
      
    };

    // Check if the city has a specific mapping
    auto it = cityMappings.find(standardizedCity);
    if (it != cityMappings.end())
    {
        return it->second;
    }

    // Capitalize the first letter of each word
    bool capitalizeNext = true;
    for (size_t i = 0; i < standardizedCity.length(); ++i)
    {
        if (capitalizeNext && isalpha(standardizedCity[i]))
        {
            standardizedCity[i] = toupper(standardizedCity[i]);
            capitalizeNext = false;
        }
        else if (standardizedCity[i] == ' ')
        {
            capitalizeNext = true;
        }
    }

    return standardizedCity;
}



int countStudentsWithMoreThanFiveCourses(const vector<Course>& ACdata) {
    set<string> uniqueStudents;
    int moreThanFive = 0;
    int coursesCounter = 0;
    string currentSID = "";

    for (int i = 0; i < ACdata.size(); i++) {
        if (ACdata[i].SID == currentSID) {
            coursesCounter++;
        } else {
            currentSID = ACdata[i].SID;
            coursesCounter = 1;
        }

        if (coursesCounter > 5 && uniqueStudents.find(currentSID) == uniqueStudents.end()) {
            moreThanFive++;
            uniqueStudents.insert(currentSID);
        }
    }

    return moreThanFive;
}

void loadStudents(const string fileNames[], int fileCount, vector<Student>& Sdata, bool isPeshawar) {
    ifstream in;
    string line;

    for (int i = 0; i < fileCount; i++) {
        in.open(fileNames[i]);
        if (!in) continue;
        getline(in, line); // Discard first line

        while (getline(in, line)) {
            string field;
            vector<string> fields;

            // ✅ Manually split line by commas
            for (char b : line) {
                if (b == ',') {
                    fields.push_back(field);
                    field = "";
                } else {
                    field += b;
                }
            }
            fields.push_back(field); // Add last field

            Student student;
            student.SID = fields[0];
            student.St_Name = fields[1];
            student.Father_Name = fields[2];

            // Gender Handling (Different for Lahore and Peshawar)
            if (isPeshawar) {
                string name, nametobeadded;
                vector<string> firstname;
                for (char a : student.St_Name) {
                    if (a == ' ') {
                        firstname.push_back(name);
                        name = "";
                    } else {
                        name += a;
                    }
                }
                if (firstname.size() > 1 && firstname[0].length() < 3) {
                    nametobeadded = firstname[1];
                } else if (!firstname.empty() && firstname[0].length() >= 3) {
                    nametobeadded = firstname[0];
                } else {
                    nametobeadded = "";
                }

                string malenames = "malenames.txt";
                string femalenames = "femalenames.txt";
                if (IsNameInFile(nametobeadded, malenames)) {
                    student.Gender = "M";
                } else if (IsNameInFile(nametobeadded, femalenames)) {
                    student.Gender = "F";
                } else {
                    student.Gender = "";
                }
            } else {
                student.Gender = (fields[3] == "0") ? "M" : (fields[3] == "1") ? "F" : fields[3];
            }

            student.Address = fields[isPeshawar ? 3 : 4];
            size_t pos = student.Address.rfind(" ");
            student.city_name = (pos != string::npos) ? standardizeCityName(student.Address.substr(pos + 1)) : "";

            student.DOB = isPeshawar ? ConvertDate(fields[4]) : fields[5];
            student.Reg_Date = isPeshawar ? ConvertDate(fields[6]) : fields[6];

            student.Reg_Status = fields[7];
            student.Degree_Status = fields[8];
            student.Last_Degree = fields[isPeshawar ? 5 : 9];

            Sdata.push_back(student);

            if (!isPeshawar) {
                writeToGenderFile(student);
            }
        }
        in.close();
    }
}

// Load students from a single file (Unified `AllStudents.txt`)
void loadStudents(const string& fileName, vector<Student>& Sdata) {
    ifstream in(fileName);
    if (!in) return;

    string line;
    getline(in, line); 

    while (getline(in, line)) {
        string field;
        vector<string> fields;

        
        for (char b : line) {
            if (b == ',') {
                fields.push_back(field);
                field = "";
            } else {
                field += b;
            }
        }
        fields.push_back(field); // Add last field

        Student student;
        student.SID = fields[0];
        student.St_Name = fields[1];
        student.Father_Name = fields[2];
        student.Gender = fields[3];
        student.Address = fields[4];
        student.city_name = fields[5];
        student.DOB = fields[6];
        student.Reg_Date = fields[7];
        student.Reg_Status = fields[8];
        student.Degree_Status = fields[9];
        student.Last_Degree = fields[10];

        Sdata.push_back(student);
    }
    in.close();
}

void loadCourses(const string fileNames[], int fileCount, vector<Course>& Cdata, bool isPeshawar) {
    ifstream in;
    string line;

    for (int i = 0; i < fileCount; i++) {
        in.open(fileNames[i]);
        if (!in) continue;
        getline(in, line); 
        while (getline(in, line)) {
            string field;
            vector<string> fields;

            for (char b : line) {
                if (b == ',') {
                    fields.push_back(field);
                    field = "";
                } else {
                    field += b;
                }
            }
            fields.push_back(field); 

            Course course;
            course.SID = fields[0];

            if (isPeshawar) {
                course.Degree = (i < 11) ? "BS" : "MS";
                course.discipline = (i < 11) ? fields[3] : fields[3].substr(3);
                string semesterYear = fields[5];
                if (semesterYear.size() == 4) {
                    semesterYear = semesterYear.substr(2);
                }
                course.Semester = fields[4] + semesterYear;
                course.Course_Code = fields[1];
                course.Marks = fields[2];
            } else {
                course.Degree = fields[1];
                course.Semester = fields[2];
                course.Course_Code = fields[3];
                course.Marks = fields[4];
                course.discipline = fields[5];
            }

            Cdata.push_back(course);
        }
        in.close();
    }
}

// Load courses from a single file (Unified `AllDetails.txt`)
void loadCourses(const string& fileName, vector<Course>& Cdata) {
    ifstream in(fileName);
    if (!in) return;

    string line;
    getline(in, line); 

    while (getline(in, line)) {
        string field;
        vector<string> fields;

       
        for (char b : line) {
            if (b == ',') {
                fields.push_back(field);
                field = "";
            } else {
                field += b;
            }
        }
        fields.push_back(field); // Add last field

        Course course;
        course.SID = fields[0];
        course.Degree = fields[1];
        course.Semester = fields[2];
        course.Course_Code = fields[3];
        course.Marks = fields[4];
        course.discipline = fields[5];

        Cdata.push_back(course);
    }
    in.close();
}



// Function to write all student data (Lahore + Peshawar) into a single file
void writeUnifiedStudentFile(const vector<Student>& Sdata, const vector<Student>& PSdata, const string& filename) {
    ofstream out(filename);
    if (!out) return;

    out << "SID,St_Name,Father_Name,Gender,Address,City,DOB,Reg_Date,Reg_Status,Degree_Status,Last_Degree\n";

    // Write Lahore student data
    for (const auto& student : Sdata) {
        out << student.SID << "," << student.St_Name << "," << student.Father_Name << ","
            << student.Gender << "," << student.Address << "," << student.city_name << ","
            << student.DOB << "," << student.Reg_Date << "," << student.Reg_Status << ","
            << student.Degree_Status << "," << student.Last_Degree << "\n";
    }

    // Write Peshawar student data
    for (const auto& student : PSdata) {
        out << student.SID << "," << student.St_Name << "," << student.Father_Name << ","
            << student.Gender << "," << student.Address << "," << student.city_name << ","
            << student.DOB << "," << student.Reg_Date << "," << student.Reg_Status << ","
            << student.Degree_Status << "," << student.Last_Degree << "\n";
    }

    out.close();
}

// Function to write all course data (Lahore + Peshawar) into a single file
void writeUnifiedCourseFile(const vector<Course>& Cdata, const vector<Course>& PCdata, const string& filename) {
    ofstream out(filename);
    if (!out) return;

    out << "SID,Degree,Semester,Course_Code,Marks,Discipline\n";

    for (const auto& course : Cdata) {
        out << course.SID << "," << course.Degree << "," << course.Semester << ","
            << course.Course_Code << "," << course.Marks << "," << course.discipline << "\n";
    }

    for (const auto& course : PCdata) {
        out << course.SID << "," << course.Degree << "," << course.Semester << ","
            << course.Course_Code << "," << course.Marks << "," << course.discipline << "\n";
    }

    out.close();
}
void calculateCampusStatistics(const vector<Student>& Sdata, const vector<Course>& Cdata) {
    set<string> uSID, uDegree, uSemester, uCourse_Code, uMarks, uDiscipline;
    int idnull = 0, degreenull = 0, codenull = 0, marksnull = 0, disciplinenull = 0, semnull = 0;
    
    for (const auto& course : Cdata) {
    uSID.insert(course.SID);
    uDegree.insert(course.Degree);
    uCourse_Code.insert(course.Course_Code);
    uMarks.insert(course.Marks);
    uDiscipline.insert(course.discipline);
    uSemester.insert(course.Semester);
    
    if (course.SID.empty()) idnull++;
    if (course.Degree.empty()) degreenull++;
    if (course.Semester.empty()) semnull++;
    if (course.Course_Code.empty()) codenull++;
    if (course.Marks.empty()) marksnull++;
    if (course.discipline.empty()) disciplinenull++;
    }
    
    int male = 0, female = 0;
    for (const auto& student : Sdata) {
    if (student.Gender == "M") male++;
    else if (student.Gender == "F") female++;
    }
    
    int moreThanFiveCourses = countStudentsWithMoreThanFiveCourses(Cdata);
    
    cout << "Number of unique values in Course data:" << endl;
    cout << "Student ID: " << uSID.size() << endl;
    cout << "Degree: " << uDegree.size() << endl;
    cout << "Semester: " << uSemester.size() << endl;
    cout << "Course Code: " << uCourse_Code.size() << endl;
    cout << "Marks: " << uMarks.size() << endl;
    cout << "Discipline: " << uDiscipline.size() << endl << endl;
    
    cout << "Number of null values in Course data:" << endl;
    cout << "Student ID: " << idnull << endl;
    cout << "Degree: " << degreenull << endl;
    cout << "Semester: " << semnull << endl;
    cout << "Course Code: " << codenull << endl;
    cout << "Marks: " << marksnull << endl;
    cout << "Discipline: " << disciplinenull << endl << endl;
    
    cout << "Total Courses: " << uCourse_Code.size() << endl;
    cout << "Total no. of female students Vs male students: " << female << ":" << male << endl;
    cout << "Students with more than 5 courses: " << moreThanFiveCourses << endl;
    cout << "Total no. of unique student IDs Vs total students: " << uSID.size() << ":" << Sdata.size() << endl;
    }
    
// Function to calculate combined statistics for both campuses
void calculateCombinedStatistics(const vector<Student>& ASdata, const vector<Course>& ACdata) {
    set<string> uSID, uDegree, uSemester, uCourse_Code, uMarks, uDiscipline;
    int idnull = 0, degreenull = 0, codenull = 0, marksnull = 0, disciplinenull = 0, semnull = 0;

    for (const auto& course : ACdata) {
        uSID.insert(course.SID);
        uDegree.insert(course.Degree);
        uCourse_Code.insert(course.Course_Code);
        uMarks.insert(course.Marks);
        uDiscipline.insert(course.discipline);
        uSemester.insert(course.Semester);

        if (course.SID.empty()) idnull++;
        if (course.Degree.empty()) degreenull++;
        if (course.Semester.empty()) semnull++;
        if (course.Course_Code.empty()) codenull++;
        if (course.Marks.empty()) marksnull++;
        if (course.discipline.empty()) disciplinenull++;
    }

    // Process all students (Combined Data)
    int sid = 0, add = 0, city = 0, deg = 0, fath = 0, gend = 0, lastd = 0, regd = 0, regs = 0, stname = 0, dob = 0;
    for (const auto& student : ASdata) {
        if (student.SID.empty()) sid++;
        if (student.Address.empty()) add++;
        if (student.city_name.empty()) city++;
        if (student.Degree_Status.empty()) deg++;
        if (student.DOB.empty()) dob++;
        if (student.Father_Name.empty()) fath++;
        if (student.Gender.empty()) gend++;
        if (student.Last_Degree.empty()) lastd++;
        if (student.Reg_Date.empty()) regd++;
        if (student.Reg_Status.empty()) regs++;
        if (student.St_Name.empty()) stname++;
    }

    int male = 0, female = 0;
    for (const auto& student : ASdata) {
        if (student.Gender == "M") male++;
        else if (student.Gender == "F") female++;
    }

    // Students with more than 5 courses
    int moreThanFiveCourses = countStudentsWithMoreThanFiveCourses(ACdata);

    // Print statistics
    cout << "Total Courses: " << uCourse_Code.size() << endl;
    cout << "Total no. of female students Vs male students: " << female << ":" << male << endl;
    cout << "Students with more than 5 courses: " << moreThanFiveCourses << endl;
    cout << "Total no. of unique student IDs Vs total students: " << uSID.size() << ":" << ASdata.size() << endl << endl;

    cout << "Number of null values in All Student Data: " << endl;
    cout << "Student ID: " << sid << endl;
    cout << "Student Name: " << stname << endl;
    cout << "Address: " << add << endl;
    cout << "City: " << city << endl;
    cout << "Degree Status: " << deg << endl;
    cout << "Date of Birth: " << dob << endl;
    cout << "Father's Name: " << fath << endl;
    cout << "Gender: " << gend << endl;
    cout << "Last Degree: " << lastd << endl;
    cout << "Registration Date: " << regd << endl;
    cout << "Registration Status: " << regs << endl;
}

    
void displayStatistics(const vector<Student>& Sdata, const vector<Course>& Cdata,
    const vector<Student>& PSdata, const vector<Course>& PCdata,
    const vector<Student>& ASdata, const vector<Course>& ACdata) {
int i0;
cout << "1. Statistics for Lahore" << endl;
cout << "2. Statistics for Peshawar" << endl;
cout << "3. Statistics for Lahore and Peshawar combined" << endl;
cout << "Enter 1 or 2 or 3" << endl << endl;
cin >> i0;

switch (i0) {
case 1:
cout << "Statistics for Lahore:" << endl;
calculateCampusStatistics(Sdata, Cdata);
break;

case 2:
cout << "Statistics for Peshawar:" << endl;
calculateCampusStatistics(PSdata, PCdata);
break;

case 3:
cout << "Statistics for Lahore and Peshawar Combined:" << endl;
calculateCombinedStatistics(ASdata, ACdata); 
break;

default:
cout << "Invalid entry..." << endl;
return;
}
}



int main() {
    // Lahore Student Data
    string Studentfile_names[] = {
        "Lahore/Lhr_Student_94.txt", "Lahore/Lhr_Student_95.txt", "Lahore/Lhr_Student_96.txt",
        "Lahore/Lhr_Student_97.txt", "Lahore/Lhr_Student_98.txt",
        "Lahore/Lhr_Student_99.txt", "Lahore/Lhr_Student_100.txt", "Lahore/Lhr_Student_101.txt",
        "Lahore/Lhr_Student_102.txt", "Lahore/Lhr_Student_103.txt",
        "Lahore/Lhr_Student_104.txt", "Lahore/Lhr_Student_MS_101.txt",
        "Lahore/Lhr_Student_MS_102.txt", "Lahore/Lhr_Student_MS_103.txt", "Lahore/Lhr_Student_MS_104.txt",
        "Lahore/Transfer.txt"
    };

    vector<Student> LSdata;
    loadStudents(Studentfile_names, 16, LSdata, false); // Load Lahore students

    // Lahore Course Data
    string Detailfile_names[] = {
        "Lahore/Lhr_Detail_94.txt", "Lahore/Lhr_Detail_95.txt", "Lahore/Lhr_Detail_96.txt",
        "Lahore/Lhr_Detail_97.txt", "Lahore/Lhr_Detail_98.txt",
        "Lahore/Lhr_Detail_99.txt", "Lahore/Lhr_Detail_100.txt", "Lahore/Lhr_Detail_101.txt",
        "Lahore/Lhr_Detail_102.txt", "Lahore/Lhr_Detail_103.txt",
        "Lahore/Lhr_Detail_104.txt", "Lahore/Lhr_Detail_MS_101.txt",
        "Lahore/Lhr_Detail_MS_102.txt", "Lahore/Lhr_Detail_MS_103.txt", "Lahore/Lhr_Detail_MS_104.txt"
    };

    vector<Course> LCdata;
    loadCourses(Detailfile_names, 15, LCdata, false); // Load Lahore courses

    /////////////////////////////////////////////////////////////////////////////////////////////////////

    // Peshawar Student Data
    string PStudentfile_names[] = {
        "Peshawar/BS_P_94_Student.txt", "Peshawar/BS_P_95_Student.txt", "Peshawar/BS_P_96_Student.txt",
        "Peshawar/BS_P_97_Student.txt", "Peshawar/BS_P_98_Student.txt",
        "Peshawar/BS_P_99_Student.txt", "Peshawar/BS_P_100_Student.txt",
        "Peshawar/BS_P_101_Student.txt", "Peshawar/BS_P_102_Student.txt", "Peshawar/BS_P_103_Student.txt",
        "Peshawar/BS_P_104_Student.txt", "Peshawar/MS_P_101_Student.txt", "Peshawar/MS_P_102_Student.txt",
        "Peshawar/MS_P_103_Student.txt", "Peshawar/MS_P_104_Student.txt"
    };

    vector<Student> PSdata;
    loadStudents(PStudentfile_names, 15, PSdata, true); // Load Peshawar students

    // Peshawar Course Data
    string PDetailfile_names[] = {
        "Peshawar/BS_P_94_Reg.txt", "Peshawar/BS_P_95_Reg.txt", "Peshawar/BS_P_96_Reg.txt",
        "Peshawar/BS_P_97_Reg.txt", "Peshawar/BS_P_98_Reg.txt",
        "Peshawar/BS_P_99_Reg.txt", "Peshawar/BS_P_100_Reg.txt", "Peshawar/BS_P_101_Reg.txt", "Peshawar/BS_P_102_Reg.txt",
        "Peshawar/BS_P_103_Reg.txt","Peshawar/BS_P_104_Reg.txt",
        "Peshawar/MS_P_101_Reg.txt", "Peshawar/MS_P_102_Reg.txt", "Peshawar/MS_P_103_Reg.txt", "MS_P_104_Reg.txt"
    };

    vector<Course> PCdata;
    loadCourses(PDetailfile_names, 15, PCdata, true); // Load Peshawar courses

    /////////////////////////////////////////////////////////////////////////////////////////////////////

    // Write unified student & course data into files
    string allStudentFile = "AllStudents.txt";
    string allCourseFile = "AllDetails.txt";
    writeUnifiedStudentFile(LSdata, PSdata, allStudentFile);
    writeUnifiedCourseFile(LCdata, PCdata, allCourseFile);

    // Load unified (combined) student & course data from files
    vector<Student> ASdata;
    vector<Course> ACdata;
    loadStudents(allStudentFile, ASdata);  // Load combined student data
    loadCourses(allCourseFile, ACdata);    // Load combined course data

    /////////////////////////////////////////////////////////////////////////////////////////////////////

    // Call function to display statistics with proper parameters
    displayStatistics(LSdata, LCdata, PSdata, PCdata, ASdata, ACdata);

    return 0;
}

