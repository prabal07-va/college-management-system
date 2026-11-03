# College Schedule, Event & Teacher Management System

[![Live Demo](https://img.shields.io/badge/Live%20Demo-Online%20App-brightgreen?style=for-the-badge&logo=githubpages&logoColor=white)](https://prabal07-va.github.io/college-management-system/)
[![Language](https://img.shields.io/badge/Language-C%20(C99%2FC11)-00599C.svg?style=for-the-badge&logo=c)](college_mgmt.c)
[![License](https://img.shields.io/badge/License-MIT-purple.svg?style=for-the-badge)](LICENSE)

> A beginner-friendly Data Structures and Algorithms (DSA) project written in **Standard C (C99/C11)** accompanied by a **complete interactive Web Application frontend**.

---

## 🌐 Live Working Demo

Access the fully functional live application directly in your web browser:

👉 **[https://prabal07-va.github.io/college-management-system/](https://prabal07-va.github.io/college-management-system/)**

> **Note:** Zero setup or installation required! The web app runs client-side with interactive timetable scheduling, conflict warning simulations, a dynamic Linked List memory visualizer, and in-browser C source code export.

---

## 📌 Project Overview

This project provides an automated academic resource manager designed to solve scheduling, faculty assignment, and event management challenges in educational institutions.

It directly demonstrates three fundamental data structures:
1. **Singly Linked List**: Dynamic teacher directory management ($O(1)$ head insertion, dynamic memory allocation with `malloc`/`free`).
2. **2D Array Matrix Grid (5 &times; 5)**: Master weekly timetable with instant $O(1)$ random access for slot status verification.
3. **Priority Queue (Sorted Linked List)**: Chronological event ordering ensuring earliest upcoming college events always appear at the head ($O(1)$ peek).
4. **Conflict Detection Engine**: Algorithmic validation preventing slot collisions and faculty double-booking.
5. **File Persistence**: Automatic saving and loading of system state to `college_data.txt`.

---

## 🗂️ Repository Structure

```text
college-management-system/
├── college_mgmt.c          # Complete C Source Code (Compilable, self-contained)
├── index.html              # Main Web App Entry (GitHub Pages live app)
├── college_management.html # Standalone Web Application
├── README.md               # Full project documentation & Viva defense guide
├── .gitignore              # Ignores compiled binaries and persistent txt files
└── LICENSE                 # MIT License
```

---

## 🚀 How to Run the C Program

### Prerequisites
- Any standard C compiler: `gcc`, `clang`, or MSVC.

### Compilation
```bash
gcc -std=c99 -Wall -Wextra college_mgmt.c -o college_mgmt
```

### Execution
- **On Windows (PowerShell / Command Prompt):**
  ```powershell
  .\college_mgmt.exe
  ```
- **On Linux / macOS:**
  ```bash
  ./college_mgmt
  ```

---

## 💻 Web Application Features

1. **Dashboard Overview:** Real-time KPI counters (Total Faculty, Matrix Occupancy %, Live Schedule, Upcoming Events).
2. **Timetable Matrix:** Interactive 5-Day &times; 5-Period grid. Click on any slot to view, book, or cancel.
3. **Live Conflict Detection:** Immediate warning dialogs if a slot is already taken or if a faculty member is double-booked.
4. **Faculty Directory:** Visual faculty cards with a **Live Graphical Linked List Memory Visualizer** (`[HEAD] -> [Node] -> [NULL]`).
5. **College Events Timeline:** Chronological Priority Queue timeline with countdown badges.
6. **DSA & C Architecture Tab:** Preview and download `college_mgmt.c` directly with asymptotic complexity reference.

---

## 📊 Asymptotic Complexity Reference

| Module | Data Structure | Operation | Time Complexity | Space Complexity |
| :--- | :--- | :--- | :--- | :--- |
| **Faculty Records** | Singly Linked List | Insert at Head | $O(1)$ | $O(N)$ dynamic |
| **Faculty Search** | Singly Linked List | Find by ID | $O(N)$ | $O(1)$ auxiliary |
| **Timetable Slot** | 2D Array Matrix | Slot Lookup | $O(1)$ | $O(\text{Days} \times \text{Periods})$ |
| **Conflict Check** | Matrix Scan | Double-Booking Check | $O(D \times P)$ worst-case | $O(1)$ auxiliary |
| **College Events** | Sorted Linked List | Insert by Date | $O(K)$ | $O(K)$ dynamic |
| **Earliest Event** | Priority Queue Head | Peek Next Event | $O(1)$ | $O(1)$ |

---

## 🎓 Viva & Exam Defense Q&A

### Q1: Why use a 2D Array for class schedules instead of an array of linked lists?
> **Answer:** In colleges, the number of days (5 days: Mon–Fri) and periods per day (typically 4–6 periods) is fixed and predefined. A 2D array provides direct $O(1)$ coordinate-based random access (`timetable[day][period]`), making slot availability checks instant.

### Q2: How does the system prevent double-booking conflicts?
> **Answer:** Before assigning a class, the system performs two checks:
> 1. Verifies if `timetable[day][period].isBooked == true` (slot is occupied).
> 2. Verifies if the selected `teacherId` is already scheduled to teach in that exact day and time slot across the institution.

### Q3: Why is a Priority Queue used for College Events?
> **Answer:** Events are ordered by urgency/chronological order. By inserting events into a sorted linked list comparing timestamp keys ($Year \times 10000 + Month \times 100 + Day$), the head pointer always yields the earliest upcoming event in $O(1)$ time.

---

## 📄 License
This project is open-source and licensed under the [MIT License](LICENSE).
