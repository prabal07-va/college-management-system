# College Schedule, Event & Teacher Management System

[![Language](https://img.shields.io/badge/Language-C%20(C99%2FC11)-00599C.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Frontend](https://img.shields.io/badge/Frontend-HTML5%20%7C%20TailwindCSS%20%7C%20JS-38B2AC.svg)](index.html)
[![License](https://img.shields.io/badge/License-MIT-purple.svg)](LICENSE)
[![DSA](https://img.shields.io/badge/Focus-Data%20Structures%20%26%20Algorithms-success.svg)]()

> A beginner-friendly Data Structures and Algorithms (DSA) project written in **Standard C (C99/C11)** accompanied by a **complete interactive Web Application frontend (`index.html` / `college_management.html`)**.

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
├── index.html              # Main Web App Entry (GitHub Pages ready)
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
- **On Linux / macOS:**
  ```bash
  ./college_mgmt
  ```
- **On Windows (PowerShell / Command Prompt):**
  ```powershell
  .\college_mgmt.exe
  ```

---

## 🌐 How to Use the Web Application

1. Open [`index.html`](index.html) or [`college_management.html`](college_management.html) in any modern web browser.
2. **Dashboard**: View high-level metrics (Total Faculty, Matrix Occupancy %, Live Schedule).
3. **Timetable Matrix**: Visual 5-Day &times; 5-Period grid. Click on any slot to view, book, or cancel.
4. **Faculty Directory**: Shows cards with a live **Graphical Linked List Memory Visualizer** (`[HEAD] -> [Node] -> [NULL]`).
5. **College Events**: Displays events strictly ordered by date in a chronological Priority Queue timeline.
6. **DSA & C Architecture Tab**: Preview and download the C code directly from the browser, review time complexities, and study viva answers.

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
