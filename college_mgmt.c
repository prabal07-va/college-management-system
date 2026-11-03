/**
 * ============================================================================
 * Project Name : College Schedule, Event & Teacher Management System
 * Language     : C (Standard C99 / C11)
 * Focus        : Data Structures & Algorithms (DSA)
 * Data Structures:
 *   1. Singly Linked List              -> Teacher Directory
 *   2. Priority Queue (Sorted List)   -> Chronological College Events
 *   3. 2D Array Matrix                -> Class Schedules (Days x Periods)
 *   4. Conflict Detection Algorithm   -> Teacher & Slot Collision Prevention
 *   5. File Persistence               -> Save & Load system data (I/O)
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DAYS 5              // Monday to Friday
#define PERIODS 5           // 5 Time slots per day
#define DATA_FILE "college_data.txt"

// Day names lookup
static const char* DAY_NAMES[DAYS] = {
    "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"
};

// Period timings lookup
static const char* TIME_SLOTS[PERIODS] = {
    "09:00 - 10:00 AM",
    "10:00 - 11:00 AM",
    "11:15 - 12:15 PM",
    "01:00 - 02:00 PM",
    "02:00 - 03:00 PM"
};

/* ============================================================================
 * DATA STRUCTURE DEFINITIONS
 * ============================================================================ */

/**
 * 1. TEACHER NODE (Singly Linked List)
 * Time Complexity:
 *   - Insertion : O(1) at head
 *   - Search    : O(N) by Teacher ID
 *   - Deletion  : O(N)
 */
typedef struct TeacherNode {
    int id;
    char name[60];
    char department[40];
    char email[60];
    char designation[40];
    struct TeacherNode* next;
} TeacherNode;

/**
 * 2. CLASS TIMETABLE SLOT (2D Array Grid Element)
 * Time Complexity:
 *   - Access / Lookup : O(1) direct indexing [day][period]
 *   - Conflict Check  : O(1) for slot, O(D*P) to verify teacher's other bookings
 */
typedef struct ClassSlot {
    bool isBooked;
    char subject[40];
    int teacherId;
    char room[20];
    char batch[20];
} ClassSlot;

/**
 * 3. COLLEGE EVENT NODE (Priority Queue implemented via Sorted Linked List)
 * Priority Key: Composite date timestamp (Year * 10000 + Month * 100 + Day)
 * Time Complexity:
 *   - Insert by Priority : O(K) where K is number of events
 *   - Peek Next Event   : O(1) head access
 *   - Traversal         : O(K)
 */
typedef struct EventNode {
    int eventId;
    char title[80];
    int year;
    int month;
    int day;
    char time[20];
    char venue[40];
    char category[30]; // Seminar, Workshop, Fest, Exam
    struct EventNode* next;
} EventNode;

/* ============================================================================
 * GLOBAL DATA REPOSITORIES
 * ============================================================================ */
TeacherNode* teacherHead = NULL;
EventNode* eventHead = NULL;
ClassSlot timetable[DAYS][PERIODS];

/* ============================================================================
 * FUNCTION DECLARATIONS
 * ============================================================================ */
void initTimetable(void);
void seedInitialData(void);

// Teacher operations
void addTeacher(int id, const char* name, const char* dept, const char* email, const char* desig);
void addTeacherInteractive(void);
TeacherNode* findTeacher(int id);
void displayTeachers(void);
void deleteTeacher(int id);

// Timetable operations
void scheduleClassInteractive(void);
bool checkTeacherConflict(int teacherId, int day, int period);
void displayTimetable(void);
void displayTeacherSchedule(int teacherId);
void cancelClass(int day, int period);

// Event operations
void addEvent(int id, const char* title, int y, int m, int d, const char* time, const char* venue, const char* cat);
void addEventInteractive(void);
void displayEvents(void);
void deleteEvent(int id);

// File I/O
void saveToFile(void);
void loadFromFile(void);

// Memory cleanup
void freeAll(void);

/* ============================================================================
 * TEACHER MODULE IMPLEMENTATION (Singly Linked List)
 * ============================================================================ */

void addTeacher(int id, const char* name, const char* dept, const char* email, const char* desig) {
    if (findTeacher(id) != NULL) {
        printf("\n[ERROR] Teacher with ID %d already exists!\n", id);
        return;
    }

    TeacherNode* newNode = (TeacherNode*)malloc(sizeof(TeacherNode));
    if (!newNode) {
        printf("\n[ERROR] Memory allocation failed!\n");
        return;
    }

    newNode->id = id;
    strncpy(newNode->name, name, sizeof(newNode->name) - 1);
    newNode->name[sizeof(newNode->name) - 1] = '\0';
    strncpy(newNode->department, dept, sizeof(newNode->department) - 1);
    newNode->department[sizeof(newNode->department) - 1] = '\0';
    strncpy(newNode->email, email, sizeof(newNode->email) - 1);
    newNode->email[sizeof(newNode->email) - 1] = '\0';
    strncpy(newNode->designation, desig, sizeof(newNode->designation) - 1);
    newNode->designation[sizeof(newNode->designation) - 1] = '\0';

    // Insert at head (O(1))
    newNode->next = teacherHead;
    teacherHead = newNode;
}

void addTeacherInteractive(void) {
    int id;
    char name[60], dept[40], email[60], desig[40];

    printf("\n--- Add New Faculty / Teacher ---");
    printf("\nEnter Teacher ID (e.g. 101): ");
    if (scanf("%d", &id) != 1) {
        while (getchar() != '\n');
        printf("[ERROR] Invalid numeric ID!\n");
        return;
    }
    while (getchar() != '\n'); // clear newline

    if (findTeacher(id) != NULL) {
        printf("[ERROR] Teacher ID %d already registered!\n", id);
        return;
    }

    printf("Enter Full Name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\r\n")] = 0;

    printf("Enter Department (e.g. CSE, IT, ECE): ");
    fgets(dept, sizeof(dept), stdin);
    dept[strcspn(dept, "\r\n")] = 0;

    printf("Enter Email Address: ");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\r\n")] = 0;

    printf("Enter Designation (e.g. Professor, Asst. Professor): ");
    fgets(desig, sizeof(desig), stdin);
    desig[strcspn(desig, "\r\n")] = 0;

    addTeacher(id, name, dept, email, desig);
    printf(">> SUCCESS: Faculty '%s' (ID %d) added to Linked List!\n", name, id);
}

TeacherNode* findTeacher(int id) {
    TeacherNode* curr = teacherHead;
    while (curr != NULL) {
        if (curr->id == id) return curr;
        curr = curr->next;
    }
    return NULL;
}

void displayTeachers(void) {
    printf("\n========================================================================================\n");
    printf("                            FACULTY DIRECTORY (LINKED LIST)                             \n");
    printf("========================================================================================\n");
    printf("%-6s | %-22s | %-12s | %-25s | %-15s\n", "ID", "Name", "Department", "Email", "Designation");
    printf("----------------------------------------------------------------------------------------\n");

    if (teacherHead == NULL) {
        printf("                 No faculty records found in the system.\n");
        printf("========================================================================================\n");
        return;
    }

    TeacherNode* curr = teacherHead;
    int count = 0;
    while (curr != NULL) {
        printf("%-6d | %-22s | %-12s | %-25s | %-15s\n",
               curr->id, curr->name, curr->department, curr->email, curr->designation);
        curr = curr->next;
        count++;
    }
    printf("----------------------------------------------------------------------------------------\n");
    printf("Total Faculty Count: %d\n", count);
    printf("========================================================================================\n");
}

void deleteTeacher(int id) {
    if (teacherHead == NULL) {
        printf("\n[ERROR] Teacher list is empty!\n");
        return;
    }

    TeacherNode* curr = teacherHead;
    TeacherNode* prev = NULL;

    while (curr != NULL && curr->id != id) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("\n[ERROR] Teacher with ID %d not found!\n", id);
        return;
    }

    if (prev == NULL) {
        teacherHead = curr->next;
    } else {
        prev->next = curr->next;
    }

    // Also unassign from any scheduled classes
    for (int d = 0; d < DAYS; d++) {
        for (int p = 0; p < PERIODS; p++) {
            if (timetable[d][p].isBooked && timetable[d][p].teacherId == id) {
                timetable[d][p].isBooked = false;
                strcpy(timetable[d][p].subject, "FREE");
                timetable[d][p].teacherId = -1;
                strcpy(timetable[d][p].room, "-");
            }
        }
    }

    printf(">> SUCCESS: Teacher '%s' (ID %d) deleted and unassigned from timetable.\n", curr->name, id);
    free(curr);
}

/* ============================================================================
 * TIMETABLE MODULE IMPLEMENTATION (2D Matrix & Conflict Checking)
 * ============================================================================ */

void initTimetable(void) {
    for (int d = 0; d < DAYS; d++) {
        for (int p = 0; p < PERIODS; p++) {
            timetable[d][p].isBooked = false;
            strcpy(timetable[d][p].subject, "FREE");
            timetable[d][p].teacherId = -1;
            strcpy(timetable[d][p].room, "-");
            strcpy(timetable[d][p].batch, "-");
        }
    }
}

/**
 * Checks if a teacher is already booked in another classroom at the same day & period
 */
bool checkTeacherConflict(int teacherId, int day, int period) {
    if (timetable[day][period].isBooked && timetable[day][period].teacherId == teacherId) {
        return true;
    }
    return false;
}

void scheduleClassInteractive(void) {
    int dayChoice, periodChoice, tId;
    char subject[40], room[20], batch[20];

    printf("\n--- Schedule a Class ---");
    printf("\nSelect Day:\n");
    for (int i = 0; i < DAYS; i++) {
        printf("  %d. %s\n", i + 1, DAY_NAMES[i]);
    }
    printf("Enter Day (1-%d): ", DAYS);
    if (scanf("%d", &dayChoice) != 1 || dayChoice < 1 || dayChoice > DAYS) {
        while (getchar() != '\n');
        printf("[ERROR] Invalid day selection!\n");
        return;
    }
    int day = dayChoice - 1;

    printf("\nSelect Time Slot:\n");
    for (int i = 0; i < PERIODS; i++) {
        printf("  %d. %s\n", i + 1, TIME_SLOTS[i]);
    }
    printf("Enter Slot (1-%d): ", PERIODS);
    if (scanf("%d", &periodChoice) != 1 || periodChoice < 1 || periodChoice > PERIODS) {
        while (getchar() != '\n');
        printf("[ERROR] Invalid slot selection!\n");
        return;
    }
    int period = periodChoice - 1;

    // 1. Check Slot Occupancy
    if (timetable[day][period].isBooked) {
        printf("\n[CONFLICT DETECTED] Slot '%s' on %s is ALREADY BOOKED for '%s'!\n",
               TIME_SLOTS[period], DAY_NAMES[day], timetable[day][period].subject);
        return;
    }

    // 2. Select Teacher
    printf("\nEnter Teacher ID: ");
    if (scanf("%d", &tId) != 1) {
        while (getchar() != '\n');
        printf("[ERROR] Invalid Teacher ID!\n");
        return;
    }
    while (getchar() != '\n');

    TeacherNode* teacher = findTeacher(tId);
    if (!teacher) {
        printf("[ERROR] Teacher ID %d does not exist! Please add the teacher first.\n", tId);
        return;
    }

    // 3. Check Teacher Conflict
    if (checkTeacherConflict(tId, day, period)) {
        printf("\n[CONFLICT DETECTED] Faculty '%s' is already scheduled in this slot!\n", teacher->name);
        return;
    }

    printf("Enter Course / Subject Name (e.g. Data Structures): ");
    fgets(subject, sizeof(subject), stdin);
    subject[strcspn(subject, "\r\n")] = 0;

    printf("Enter Room / Lab No (e.g. Lab-302): ");
    fgets(room, sizeof(room), stdin);
    room[strcspn(room, "\r\n")] = 0;

    printf("Enter Batch / Semester (e.g. CS-3A): ");
    fgets(batch, sizeof(batch), stdin);
    batch[strcspn(batch, "\r\n")] = 0;

    // Book the slot
    timetable[day][period].isBooked = true;
    timetable[day][period].teacherId = tId;
    strncpy(timetable[day][period].subject, subject, sizeof(timetable[day][period].subject) - 1);
    strncpy(timetable[day][period].room, room, sizeof(timetable[day][period].room) - 1);
    strncpy(timetable[day][period].batch, batch, sizeof(timetable[day][period].batch) - 1);

    printf(">> SUCCESS: Class for '%s' scheduled on %s at %s with %s (Room %s)\n",
           subject, DAY_NAMES[day], TIME_SLOTS[period], teacher->name, room);
}

void cancelClass(int day, int period) {
    if (day < 0 || day >= DAYS || period < 0 || period >= PERIODS) {
        printf("[ERROR] Invalid day or period indices!\n");
        return;
    }

    if (!timetable[day][period].isBooked) {
        printf(">> Slot is already FREE.\n");
        return;
    }

    printf(">> SUCCESS: Cancelled '%s' on %s at %s.\n",
           timetable[day][period].subject, DAY_NAMES[day], TIME_SLOTS[period]);

    timetable[day][period].isBooked = false;
    strcpy(timetable[day][period].subject, "FREE");
    timetable[day][period].teacherId = -1;
    strcpy(timetable[day][period].room, "-");
    strcpy(timetable[day][period].batch, "-");
}

void displayTimetable(void) {
    printf("\n====================================================================================================\n");
    printf("                                      WEEKLY CLASS TIMETABLE                                        \n");
    printf("====================================================================================================\n");

    for (int d = 0; d < DAYS; d++) {
        printf("\n>>> %s <<<\n", DAY_NAMES[d]);
        printf("%-18s | %-8s | %-22s | %-12s | %-10s | %-20s\n",
               "Time Slot", "Status", "Subject", "Batch", "Room", "Teacher");
        printf("----------------------------------------------------------------------------------------------------\n");

        for (int p = 0; p < PERIODS; p++) {
            if (timetable[d][p].isBooked) {
                TeacherNode* t = findTeacher(timetable[d][p].teacherId);
                printf("%-18s | %-8s | %-22s | %-12s | %-10s | %-20s\n",
                       TIME_SLOTS[p],
                       "BOOKED",
                       timetable[d][p].subject,
                       timetable[d][p].batch,
                       timetable[d][p].room,
                       (t ? t->name : "Unknown"));
            } else {
                printf("%-18s | %-8s | %-22s | %-12s | %-10s | %-20s\n",
                       TIME_SLOTS[p], "FREE", "-", "-", "-", "-");
            }
        }
    }
    printf("====================================================================================================\n");
}

void displayTeacherSchedule(int teacherId) {
    TeacherNode* t = findTeacher(teacherId);
    if (!t) {
        printf("\n[ERROR] Teacher with ID %d not found!\n", teacherId);
        return;
    }

    printf("\n========================================================================\n");
    printf("               SCHEDULE FOR: %s (ID: %d, Dept: %s)                      \n",
           t->name, t->id, t->department);
    printf("========================================================================\n");

    int count = 0;
    for (int d = 0; d < DAYS; d++) {
        for (int p = 0; p < PERIODS; p++) {
            if (timetable[d][p].isBooked && timetable[d][p].teacherId == teacherId) {
                printf("%-10s | %-18s | Subject: %-18s | Room: %-6s | Batch: %s\n",
                       DAY_NAMES[d], TIME_SLOTS[p],
                       timetable[d][p].subject,
                       timetable[d][p].room,
                       timetable[d][p].batch);
                count++;
            }
        }
    }

    if (count == 0) {
        printf("No classes currently scheduled for this teacher.\n");
    } else {
        printf("------------------------------------------------------------------------\n");
        printf("Total assigned periods: %d / %d\n", count, DAYS * PERIODS);
    }
    printf("========================================================================\n");
}

/* ============================================================================
 * COLLEGE EVENTS MODULE (Priority Queue via Sorted Linked List)
 * ============================================================================ */

static long getTimestamp(int y, int m, int d) {
    return (long)y * 10000L + (long)m * 100L + (long)d;
}

void addEvent(int id, const char* title, int y, int m, int d, const char* time, const char* venue, const char* cat) {
    EventNode* newNode = (EventNode*)malloc(sizeof(EventNode));
    if (!newNode) {
        printf("\n[ERROR] Memory allocation failed for event!\n");
        return;
    }

    newNode->eventId = id;
    strncpy(newNode->title, title, sizeof(newNode->title) - 1);
    newNode->title[sizeof(newNode->title) - 1] = '\0';
    newNode->year = y;
    newNode->month = m;
    newNode->day = d;
    strncpy(newNode->time, time, sizeof(newNode->time) - 1);
    newNode->time[sizeof(newNode->time) - 1] = '\0';
    strncpy(newNode->venue, venue, sizeof(newNode->venue) - 1);
    newNode->venue[sizeof(newNode->venue) - 1] = '\0';
    strncpy(newNode->category, cat, sizeof(newNode->category) - 1);
    newNode->category[sizeof(newNode->category) - 1] = '\0';
    newNode->next = NULL;

    long newStamp = getTimestamp(y, m, d);

    // Insert in Chronological Order (Priority Queue: Earliest timestamp first)
    if (eventHead == NULL || newStamp < getTimestamp(eventHead->year, eventHead->month, eventHead->day)) {
        newNode->next = eventHead;
        eventHead = newNode;
    } else {
        EventNode* curr = eventHead;
        while (curr->next != NULL && getTimestamp(curr->next->year, curr->next->month, curr->next->day) <= newStamp) {
            curr = curr->next;
        }
        newNode->next = curr->next;
        curr->next = newNode;
    }
}

void addEventInteractive(void) {
    int id, y, m, d;
    char title[80], time[20], venue[40], cat[30];

    printf("\n--- Schedule New College Event ---");
    printf("\nEnter Event ID (e.g. 501): ");
    if (scanf("%d", &id) != 1) {
        while (getchar() != '\n');
        printf("[ERROR] Invalid numeric ID!\n");
        return;
    }
    while (getchar() != '\n');

    printf("Enter Event Title: ");
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\r\n")] = 0;

    printf("Enter Date - Year (e.g. 2026): ");
    scanf("%d", &y);
    printf("Enter Date - Month (1-12): ");
    scanf("%d", &m);
    printf("Enter Date - Day (1-31): ");
    scanf("%d", &d);
    while (getchar() != '\n');

    printf("Enter Event Time (e.g. 10:00 AM): ");
    fgets(time, sizeof(time), stdin);
    time[strcspn(time, "\r\n")] = 0;

    printf("Enter Venue / Auditorium: ");
    fgets(venue, sizeof(venue), stdin);
    venue[strcspn(venue, "\r\n")] = 0;

    printf("Enter Category (e.g. Seminar, Workshop, Fest, Exam): ");
    fgets(cat, sizeof(cat), stdin);
    cat[strcspn(cat, "\r\n")] = 0;

    addEvent(id, title, y, m, d, time, venue, cat);
    printf(">> SUCCESS: Event '%s' queued in Chronological Order!\n", title);
}

void displayEvents(void) {
    printf("\n========================================================================================\n");
    printf("                  UPCOMING COLLEGE EVENTS (PRIORITY QUEUE - CHRONOLOGICAL)              \n");
    printf("========================================================================================\n");
    printf("%-5s | %-12s | %-10s | %-28s | %-16s | %-12s\n",
           "ID", "Date", "Time", "Event Title", "Venue", "Category");
    printf("----------------------------------------------------------------------------------------\n");

    if (eventHead == NULL) {
        printf("                     No upcoming events currently scheduled.\n");
        printf("========================================================================================\n");
        return;
    }

    EventNode* curr = eventHead;
    int count = 0;
    while (curr != NULL) {
        char dateStr[20];
        snprintf(dateStr, sizeof(dateStr), "%04d-%02d-%02d", curr->year, curr->month, curr->day);

        printf("%-5d | %-12s | %-10s | %-28s | %-16s | %-12s\n",
               curr->eventId, dateStr, curr->time, curr->title, curr->venue, curr->category);
        curr = curr->next;
        count++;
    }
    printf("----------------------------------------------------------------------------------------\n");
    printf("Total Events Listed: %d (Ordered by Date Priority)\n", count);
    printf("========================================================================================\n");
}

void deleteEvent(int id) {
    if (eventHead == NULL) {
        printf("\n[ERROR] Event list is empty!\n");
        return;
    }

    EventNode* curr = eventHead;
    EventNode* prev = NULL;

    while (curr != NULL && curr->eventId != id) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("\n[ERROR] Event ID %d not found!\n", id);
        return;
    }

    if (prev == NULL) {
        eventHead = curr->next;
    } else {
        prev->next = curr->next;
    }

    printf(">> SUCCESS: Event '%s' (ID %d) removed from queue.\n", curr->title, id);
    free(curr);
}

/* ============================================================================
 * FILE I/O PERSISTENCE MODULE
 * ============================================================================ */

void saveToFile(void) {
    FILE* fp = fopen(DATA_FILE, "w");
    if (!fp) {
        printf("\n[ERROR] Unable to open '%s' for saving!\n", DATA_FILE);
        return;
    }

    // 1. Save Teachers
    int teacherCount = 0;
    TeacherNode* t = teacherHead;
    while (t) { teacherCount++; t = t->next; }
    fprintf(fp, "[TEACHERS] %d\n", teacherCount);

    t = teacherHead;
    while (t) {
        fprintf(fp, "%d|%s|%s|%s|%s\n", t->id, t->name, t->department, t->email, t->designation);
        t = t->next;
    }

    // 2. Save Timetable
    fprintf(fp, "[TIMETABLE] %d %d\n", DAYS, PERIODS);
    for (int d = 0; d < DAYS; d++) {
        for (int p = 0; p < PERIODS; p++) {
            fprintf(fp, "%d|%d|%s|%d|%s|%s\n",
                    d, p,
                    timetable[d][p].isBooked ? "1" : "0",
                    timetable[d][p].teacherId,
                    timetable[d][p].subject,
                    timetable[d][p].room);
        }
    }

    // 3. Save Events
    int eventCount = 0;
    EventNode* e = eventHead;
    while (e) { eventCount++; e = e->next; }
    fprintf(fp, "[EVENTS] %d\n", eventCount);

    e = eventHead;
    while (e) {
        fprintf(fp, "%d|%s|%d|%d|%d|%s|%s|%s\n",
                e->eventId, e->title, e->year, e->month, e->day, e->time, e->venue, e->category);
        e = e->next;
    }

    fclose(fp);
    printf(">> SUCCESS: System state saved successfully to '%s'.\n", DATA_FILE);
}

void loadFromFile(void) {
    FILE* fp = fopen(DATA_FILE, "r");
    if (!fp) {
        // If file doesn't exist yet, seed initial demo data
        seedInitialData();
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "[TEACHERS]", 10) == 0) {
            int count;
            sscanf(line, "[TEACHERS] %d", &count);
            for (int i = 0; i < count; i++) {
                if (fgets(line, sizeof(line), fp)) {
                    int id;
                    char name[60], dept[40], email[60], desig[40];
                    char* token = strtok(line, "|\n");
                    if (token) id = atoi(token);
                    token = strtok(NULL, "|\n");
                    if (token) strncpy(name, token, sizeof(name));
                    token = strtok(NULL, "|\n");
                    if (token) strncpy(dept, token, sizeof(dept));
                    token = strtok(NULL, "|\n");
                    if (token) strncpy(email, token, sizeof(email));
                    token = strtok(NULL, "|\n");
                    if (token) strncpy(desig, token, sizeof(desig));
                    addTeacher(id, name, dept, email, desig);
                }
            }
        } else if (strncmp(line, "[TIMETABLE]", 11) == 0) {
            int dCount, pCount;
            sscanf(line, "[TIMETABLE] %d %d", &dCount, &pCount);
            for (int i = 0; i < dCount * pCount; i++) {
                if (fgets(line, sizeof(line), fp)) {
                    int d, p, booked, tId;
                    char subj[40], room[20];
                    char* token = strtok(line, "|\n");
                    if (token) d = atoi(token);
                    token = strtok(NULL, "|\n");
                    if (token) p = atoi(token);
                    token = strtok(NULL, "|\n");
                    if (token) booked = atoi(token);
                    token = strtok(NULL, "|\n");
                    if (token) tId = atoi(token);
                    token = strtok(NULL, "|\n");
                    if (token) strncpy(subj, token, sizeof(subj));
                    token = strtok(NULL, "|\n");
                    if (token) strncpy(room, token, sizeof(room));

                    if (d < DAYS && p < PERIODS) {
                        timetable[d][p].isBooked = (booked == 1);
                        timetable[d][p].teacherId = tId;
                        strncpy(timetable[d][p].subject, subj, sizeof(timetable[d][p].subject) - 1);
                        strncpy(timetable[d][p].room, room, sizeof(timetable[d][p].room) - 1);
                    }
                }
            }
        } else if (strncmp(line, "[EVENTS]", 8) == 0) {
            int count;
            sscanf(line, "[EVENTS] %d", &count);
            for (int i = 0; i < count; i++) {
                if (fgets(line, sizeof(line), fp)) {
                    int id, y, m, d;
                    char title[80], time[20], venue[40], cat[30];
                    char* token = strtok(line, "|\n");
                    if (token) id = atoi(token);
                    token = strtok(NULL, "|\n");
                    if (token) strncpy(title, token, sizeof(title));
                    token = strtok(NULL, "|\n");
                    if (token) y = atoi(token);
                    token = strtok(NULL, "|\n");
                    if (token) m = atoi(token);
                    token = strtok(NULL, "|\n");
                    if (token) d = atoi(token);
                    token = strtok(NULL, "|\n");
                    if (token) strncpy(time, token, sizeof(time));
                    token = strtok(NULL, "|\n");
                    if (token) strncpy(venue, token, sizeof(venue));
                    token = strtok(NULL, "|\n");
                    if (token) strncpy(cat, token, sizeof(cat));
                    addEvent(id, title, y, m, d, time, venue, cat);
                }
            }
        }
    }
    fclose(fp);
}

/* ============================================================================
 * SEED DEFAULT DATA
 * ============================================================================ */

void seedInitialData(void) {
    // Teachers
    addTeacher(101, "Dr. Robert Smith", "Computer Science", "rsmith@college.edu", "Professor & HOD");
    addTeacher(102, "Prof. Anita Sharma", "Information Tech", "asharma@college.edu", "Associate Professor");
    addTeacher(103, "Dr. Alan Turing", "Mathematics", "aturing@college.edu", "Visiting Professor");
    addTeacher(104, "Prof. David Miller", "Electronics", "dmiller@college.edu", "Assistant Professor");

    // Sample Timetable Entries
    timetable[0][0].isBooked = true;
    timetable[0][0].teacherId = 101;
    strcpy(timetable[0][0].subject, "Data Structures");
    strcpy(timetable[0][0].room, "Lab-101");
    strcpy(timetable[0][0].batch, "CS-3A");

    timetable[0][1].isBooked = true;
    timetable[0][1].teacherId = 103;
    strcpy(timetable[0][1].subject, "Discrete Math");
    strcpy(timetable[0][1].room, "LH-204");
    strcpy(timetable[0][1].batch, "CS-3A");

    timetable[1][2].isBooked = true;
    timetable[1][2].teacherId = 102;
    strcpy(timetable[1][2].subject, "Database Systems");
    strcpy(timetable[1][2].room, "Lab-102");
    strcpy(timetable[1][2].batch, "IT-3B");

    timetable[2][0].isBooked = true;
    timetable[2][0].teacherId = 104;
    strcpy(timetable[2][0].subject, "Digital Logic");
    strcpy(timetable[2][0].room, "LH-101");
    strcpy(timetable[2][0].batch, "EC-3A");

    // Events (Inserted with dates; Priority Queue orders automatically)
    addEvent(501, "National Tech Symposium", 2026, 11, 20, "09:30 AM", "Main Auditorium", "Symposium");
    addEvent(502, "AI & Machine Learning Workshop", 2026, 11, 10, "10:00 AM", "Seminar Hall B", "Workshop");
    addEvent(503, "Annual Coding Hackathon", 2026, 11, 15, "08:00 AM", "Innovation Lab", "Competition");
    addEvent(504, "End-Semester Practical Exams", 2026, 12, 5, "09:00 AM", "Exam Hall 1-4", "Examination");
}

/* ============================================================================
 * CLEANUP
 * ============================================================================ */

void freeAll(void) {
    TeacherNode* t = teacherHead;
    while (t) {
        TeacherNode* next = t->next;
        free(t);
        t = next;
    }
    teacherHead = NULL;

    EventNode* e = eventHead;
    while (e) {
        EventNode* next = e->next;
        free(e);
        e = next;
    }
    eventHead = NULL;
}

/* ============================================================================
 * MAIN INTERACTIVE CLI
 * ============================================================================ */

int main(void) {
    initTimetable();
    loadFromFile();

    int choice;
    while (1) {
        printf("\n");
        printf("========================================================================\n");
        printf("       COLLEGE SCHEDULE, EVENT & TEACHER MANAGEMENT SYSTEM              \n");
        printf("========================================================================\n");
        printf(" [FACULTY MANAGEMENT - LINKED LIST]\n");
        printf("  1. Add New Teacher\n");
        printf("  2. Display Faculty Directory\n");
        printf("  3. Delete Teacher Record\n");
        printf("\n [CLASS SCHEDULE - 2D MATRIX GRID]\n");
        printf("  4. Schedule a Class (with Conflict Checking)\n");
        printf("  5. View Weekly Master Timetable\n");
        printf("  6. View Specific Teacher's Weekly Schedule\n");
        printf("  7. Cancel a Scheduled Class\n");
        printf("\n [COLLEGE EVENTS - PRIORITY QUEUE]\n");
        printf("  8. Add College Event (Chronologically Sorted)\n");
        printf("  9. View Upcoming Events by Date Priority\n");
        printf(" 10. Delete / Cancel an Event\n");
        printf("\n [DATA PERSISTENCE & SYSTEM]\n");
        printf(" 11. Save System State to File\n");
        printf(" 12. Exit System\n");
        printf("------------------------------------------------------------------------\n");
        printf("Select an Option (1-12): ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf(">> Invalid option! Please enter a number.\n");
            continue;
        }

        switch (choice) {
            case 1:  addTeacherInteractive(); break;
            case 2:  displayTeachers(); break;
            case 3: {
                int id;
                printf("\nEnter Teacher ID to delete: ");
                scanf("%d", &id);
                deleteTeacher(id);
                break;
            }
            case 4:  scheduleClassInteractive(); break;
            case 5:  displayTimetable(); break;
            case 6: {
                int id;
                printf("\nEnter Teacher ID: ");
                scanf("%d", &id);
                displayTeacherSchedule(id);
                break;
            }
            case 7: {
                int d, p;
                printf("\nEnter Day (1-5): ");
                scanf("%d", &d);
                printf("Enter Slot (1-5): ");
                scanf("%d", &p);
                cancelClass(d - 1, p - 1);
                break;
            }
            case 8:  addEventInteractive(); break;
            case 9:  displayEvents(); break;
            case 10: {
                int id;
                printf("\nEnter Event ID to remove: ");
                scanf("%d", &id);
                deleteEvent(id);
                break;
            }
            case 11: saveToFile(); break;
            case 12:
                saveToFile();
                freeAll();
                printf("\n>> Thank you for using College Management System. Exiting...\n");
                return 0;
            default:
                printf(">> Invalid selection! Please enter a number between 1 and 12.\n");
        }
    }
    return 0;
}
