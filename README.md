# AI-Assisted Student Record and Result Management System

**Student SAP ID:** 590032461  
**Course:** Programming in C (PRC1001)  
**Program:** B.Tech CSE, Semester I

## Project Overview

This is a menu-driven console application developed using C programming language. It manages student information and academic results while demonstrating fundamental C programming concepts.

## Features

- Add student details.
- Search and display student records using SAP ID.
- Calculate individual CGPA using available SGPA values.
- Calculate year-wise average CGPA.
- Display all student records.
- Delete individual student records.
- Sort student records by SAP ID and Name.
- Provide CGPA-based academic recommendations.

## Academic Advisor

The Academic Advisor uses conditional statements (`if-else`) to generate recommendations based on CGPA.

| CGPA | Recommendation |
|---|---|
| 9.00–10.00 | Excellent Performance |
| 7.50–8.99 | Good Performance |
| 6.00–7.49 | Needs Improvement |
| Below 6.00 | Requires Immediate Attention |

These are project-defined categories, not official university grading rules.

## Technologies Used

- C Programming Language
- GCC Compiler
- GitHub

## How to Run

Compile the program:

```bash
gcc -std=c11 -Wall -Wextra 590032461.c -o student_record
```

Run on Windows:

```powershell
.\student_record.exe
```

## Project Structure

```text
student-record-ai-c/
├── 590032461.c
├── README.md
├── AI_USAGE_LOG.md
└── tests/
    ├── sample_input.txt
    └── sample_output.txt
```

## Testing

The program includes sample test cases demonstrating different CGPA values, academic recommendations, searching, sorting and deletion.

## Note

Five fictional sample student records are loaded when the program starts. Records are currently stored in memory and are not permanently saved after exiting the application.

## AI Assistance

ChatGPT was used as a learning assistant to help design the academic advisor, suggest test cases and improve project documentation. The final logic was reviewed and implemented in C.
