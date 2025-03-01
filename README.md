# Academic Records Profiler

## Overview
**Academic Records Profiler** is a **C++ console-based application** that processes, organizes, and analyzes academic records of students from multiple campuses. The project profiles student registration details and generates summarized reports.

Originally, `main.cpp` was created as part of my **Object-Oriented Programming (OOP) project**, focusing on academic record processing. Later, I integrated a **Qt-based GUI (`app.cpp` and `app.py`)** to enhance usability and interaction.

## Features
### **Data Profiling:**
- Analyzes and processes students and courses records from **Peshawar** and **Lahore** campuses.
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
- Detects invalid dates.
- Flags missing degree information and addresses inconsistencies.

## Folder Structure
```plaintext
AcademicRecordsProfiler/
│── Peshawar/                # Contains all Peshawar-related records
│   ├── BS_P_94_Reg.txt      # For course records
│   ├── BS_P_94_Student.txt  # For student records
│   ├── ...
│
│── Lahore/                  # Contains all Lahore-related records
│   ├── Lhr_Student_94.txt   # For student records
│   ├── Lhr_Detail_94.txt    # For course records
│   ├── ...
│
│── main.cpp                 # Console-based C++ program (initial OOP project)
│── app.cpp                  # Qt-based GUI version (C++)
│── app.py                   # GUI controller (Python - PyQt5)
│── README.md                # Documentation
```

## Installation & Usage
### **Step 1: Clone the Repository**
```sh
git clone https://github.com/amueedk/AcademicRecordsProfiler.git
cd AcademicRecordsProfiler
```

### **Step 2: Compile the C++ Program**
#### **For Console Version (`main.cpp`)**
Use any C++ compiler (e.g., g++):
```sh
g++ main.cpp -o AcademicRecordsProfiler
```

#### **For GUI Version (`app.cpp`)**
```sh
g++ app.cpp -o app `pkg-config --cflags --libs Qt5Widgets`
```

### **Step 3: Run the Program**
#### **For Console Version**
```sh
./AcademicRecordsProfiler
```

#### **For GUI Version**
```sh
python app.py
```

## File Details
- **Peshawar Folder**: Contains all student details from Peshawar.
- **Lahore Folder**: Contains all student details from Lahore.
- **main.cpp**: The original C++ console application.
- **app.cpp**: The GUI version of the application using Qt.
- **app.py**: The Python controller for the GUI (PyQt5).
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

