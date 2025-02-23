# Academic Records Profiler

## Overview
**Academic Records Profiler** is a **C++ console-based application** that processes, organizes, and analyzes academic records of students from multiple campuses. The project profiles student registration details and generates summarized reports.

## Features
### **Data Profiling:**
- Analyzes and processes student records from **Peshawar** and **Lahore** campuses.
- Calculates the number of unique student IDs and verifies their consistency.
- Computes statistics such as total students, male vs. female students, and total courses.
- Determines the average number of students per semester and per batch.

### **Data Cleansing:**
- Standardizes names for students and their fathers.
- Extracts and standardizes city names from addresses.
- Adds missing gender information using name-based lookup.
- Ensures date validation for DOB and registration dates.
- Normalizes gender representation to **'M'** and **'F'**.

### **Anomalies Detection:**
- Identifies invalid marks (outside the range of 0 to 100).
- Detects invalid dates (e.g., 31st February, DOB greater than registration date).
- Flags missing degree information and addresses inconsistencies.

## Folder Structure
```plaintext
AcademicRecordsProfiler/
│── Peshawar/                # Contains all Peshawar-related records
│   ├── BS_P_94_Reg.txt
│   ├── BS_P_94_Student.txt
│   ├── ...
│
│── Lahore/                  # Contains all Lahore-related records
│   ├── Lhr_Student_94.txt
│   ├── Lhr_Detail_94.txt
│   ├── ...
│
│── main.cpp                 # The main C++ program
│── README.md                # Documentation
```

## Installation & Usage
### **Step 1: Clone the Repository**
```sh
git clone https://github.com/amueedk/AcademicRecordsProfiler.git
cd AcademicRecordsProfiler
```

### **Step 2: Compile the C++ Program**
Use any C++ compiler (e.g., g++):
```sh
g++ main.cpp -o AcademicRecordsProfiler
```

### **Step 3: Run the Program**
```sh
./AcademicRecordsProfiler
```
This will automatically generate `AllDetails.txt`, `AllStudents.txt`, `malenames.txt`, and `femalenames.txt` based on the data files.

## File Details
- **Peshawar Folder**: Contains all student details from Peshawar.
- **Lahore Folder**: Contains all student details from Lahore.
- **main.cpp**: The main C++ program that processes the records.
- **AllDetails.txt**: Created upon execution, stores combined course details.
- **AllStudents.txt**: Created upon execution, stores summarized student details.
- **malenames.txt & femalenames.txt**: Extracted from the provided data.

## Contributing
1. Fork the repository.
2. Create a new branch: `git checkout -b feature-branch`
3. Commit changes: `git commit -m "Added new feature"`
4. Push to the branch: `git push origin feature-branch`
5. Create a Pull Request.

## Author
**Abdul Mueed Khan**  
[GitHub Profile](https://github.com/amueedk)

