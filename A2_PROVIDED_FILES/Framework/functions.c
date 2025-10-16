/*
 * ============================================================================
 * Description: Student implementation template for Grade Management System
 * 
 * INSTRUCTIONS FOR STUDENTS:
 * 1. Rename this file to "functions.c" before compilation
 * 2. Implement all 8 TODO functions below
 * 3. Do NOT modify function signatures (names, parameters, return types)
 *
 * GRADING: 90 points total distributed among these 8 functions * 
 * ============================================================================
 */

#include "grade_system.h"

/* ============================================================================
 *TODO 1: Validates if a grade is within acceptable range (5 points)
 * ============================================================================
 * Parameter: grade - grade value to validate
 * Returns: OPERATION_SUCCESS (1) if valid, OPERATION_INVALID_INPUT (-1) if invalid
 * Logic: Check if grade is between MIN_GRADE and MAX_GRADE inclusive
*/

int isValidGrade(float grade) {
    // TODO: Implement grade validation logic
    // 🕵️‍♀️HINT: Use MIN_GRADE and MAX_GRADE constants

    //check if grade is between correct range
    if(grade > MAX_GRADE || grade < MIN_GRADE){

        return OPERATION_INVALID_INPUT;
    }
    //grade is in correct range, sucess
    return OPERATION_SUCCESS;
    
}

/* ============================================================================
 * TODO 2: Converts numerical grade to letter grade (5 points)
 * ============================================================================ 
 * Parameter: average - numerical average to convert
 * Returns: letter grade character (A, B, C, D, F, N for no grades)
 * 
 * GRADING SCALE:
 * A: 90.0 and above
 * B: 80.0 to 89.9
 * C: 70.0 to 79.9
 * D: 60.0 to 69.9
 * F: Below 60.0
 * N: Negative input (no grades) 
 */

char getLetterGrade(float average) {
    // TODO: Implement letter grade conversion
    // 🕵️‍♀️HINT: Use if-else ladder with the grading scale above

    //if scale checking range of grades, return matching letter grade
    if(average < 0.0f) return 'N';
    if(average >= 90.0f) return 'A';
    if(average >= 80.0f) return 'B';
    if(average >= 70.0f) return 'C';
    if(average >= 60.0f) return 'D';

    //grade was found to be below 60.0
    return 'F'; // Replace with your implementation
}

/* ============================================================================
 * TODO 3: Searches for a student by ID using linear search (10 points)
 * ============================================================================ 
 * Parameter: id - student ID to search for
 * Returns: array index if found, OPERATION_NOT_FOUND (0) if not found
 */

int findStudentByID(int id) {
    // TODO: Implement linear search algorithm
    // 🕵️‍♀️HINT: Use for loop and comparison
    
    //early return if id is not in permitted range
    if (id <= 0) return OPERATION_NOT_FOUND;  
    for (int i = 0; i < studentCount; i++) {
         if (studentIDs[i] == id) {
             return i;
         }
     }
     return OPERATION_NOT_FOUND;
 }

/* ============================================================================
 * TODO 4: Calculates average grade for a specific student (10 points)
 * ============================================================================ 
 * Calculates average grade for a specific student
 * Parameter: studentIndex - index in the global arrays
 * Returns: average grade or -1.0 if no grades entered or invalid index
 */

float calculateStudentAverage(int studentIndex) {
    // TODO: Implement average calculation
    // 🕵️‍♀️HINT: Count valid grades (>= 0), sum them, return average

    //early return if id is not in correct range
    if(studentIndex < 0 || studentIndex > studentCount){return -1.0f;}
    
    //initialize variable to calculate average 
    int count = 0;
    float sum = 0.0f;
    
    //perform various checks, only sum the grades if the grade is positive, update count if so
    if(quizGrades[studentIndex] >= 0.0f){sum += quizGrades[studentIndex]; count++;}
    if(assignmentGrades[studentIndex] >= 0.0f){sum += assignmentGrades[studentIndex]; count++;}
    if(midtermGrades[studentIndex] >= 0.0f){sum += midtermGrades[studentIndex]; count++;}
    if(finalGrades[studentIndex] >= 0.0f){sum += finalGrades[studentIndex]; count++;}
    
    //return if count was not updated
    if(count == 0) return -1.0f;


    //perfom basic average calculation, cas count to a float to maintain precision
    return sum/(float)count;
}

/* ============================================================================
 *  TODO 5: Adds a new student to the system (10 points)
 * ============================================================================ 
 * Parameter: studentID - ID of student to add
 * Returns: Success/error codes based on validation results 
 * 
 * 🕵️‍♀️IMPLEMENTATION HINT:
 * 1. if studentCount >= MAX_STUDENTS, return OPERATION_CAPACITY_ERROR
 * 2. Validate studentID (> 0 and <= MAX_STUDENT_ID), return OPERATION_INVALID_INPUT if invalid
 * 3. Check for duplicate using findStudentByID(), return OPERATION_DUPLICATE_ERROR if found
 * 4. Add student to arrays and initialize grades to GRADE_NOT_ENTERED
 * 5. Increment studentCount
 * 6. Return OPERATION_SUCCESS
 */

int addStudent(int studentID) {
    // TODO: Implement student addition with full validation 
    // 🕵️‍♀️HINT: Validate ID, check duplicates, check capacity, add to arrays 


    if(studentCount >= MAX_STUDENTS) return OPERATION_CAPACITY_ERROR; //the array full? if so capacity error
    if(studentID <=0 || studentID > MAX_STUDENT_ID) return OPERATION_INVALID_INPUT; //is the id between the correct range? 
    if(findStudentByID(studentID) != OPERATION_NOT_FOUND) return OPERATION_DUPLICATE_ERROR;// is the ID a duplicate?

    //if checks are passed, add student to array
    //initialize all necessary arrays to default values
    int idx = studentCount;
    studentIDs[idx]       = studentID;
    quizGrades[idx]       = GRADE_NOT_ENTERED;
    assignmentGrades[idx] = GRADE_NOT_ENTERED;
    midtermGrades[idx]    = GRADE_NOT_ENTERED;
    finalGrades[idx]      = GRADE_NOT_ENTERED;
    studentCount++;

    //sucess
    return OPERATION_SUCCESS;
}

/* ============================================================================
 *  TODO 6: Enters a grade for a specific student and assessment (10 points)
 * ============================================================================ 
 * Parameters: studentID - ID of student
 *            assessmentType - type of assessment (1-4)
 *            grade - grade value to enter
 * Returns: Success/error codes based on validation
 * 
 * 🕵️‍♀️IMPLEMENTATION HINTS:
 * 1. Find student using findStudentByID(), return OPERATION_NOT_FOUND if not found
 * 2. Validate grade using isValidGrade(), return OPERATION_INVALID_INPUT if invalid
 * 3. Validate assessmentType (1-4), return OPERATION_INVALID_INPUT if invalid
 * 4. Use switch statement to assign grade to correct array based on assessmentType
 * 5. Return OPERATION_SUCCESS
 */

int enterGrade(int studentID, int assessmentType, float grade) {
    // TODO: Implement grade entry with validation
    // 🕵️‍♀️HINT: Find student, validate inputs, update appropriate grade array
    // 🕵️‍♀️HINT: Use switch statement for assessmentType (1=quiz, 2=assignment, 3=midterm, 4=final)

    //find the student and return error if not found
    int studentIdx = findStudentByID(studentID);
    if(studentIdx == OPERATION_NOT_FOUND) return OPERATION_NOT_FOUND;

    //make sure that the assesment type is between the correct range of assesments (1-4)
    if(assessmentType < 1 || assessmentType > 4) return OPERATION_INVALID_INPUT;

    //Check the validity of the output and return error
    if(isValidGrade(grade) != OPERATION_SUCCESS) return OPERATION_INVALID_INPUT;

    

    //switch case to update correct assesment type with validated grades and studentID
    switch(assessmentType){
        case 1:
            quizGrades[studentIdx] = grade;
            break;
        case 2:
            assignmentGrades[studentIdx] = grade;
            break;
        case 3:
            midtermGrades[studentIdx] = grade;
            break;
        case 4:
            finalGrades[studentIdx] = grade;
            break;
    }

    return OPERATION_SUCCESS;

}

/* ============================================================================
 TODO 7: Retrieves and formats student grade information (10 points)
 * ============================================================================ 
 * Parameter: studentID - ID of student to display
 * Returns: OPERATION_SUCCESS if found, OPERATION_NOT_FOUND if not found
 * 
 * 🕵️‍♀️IMPLEMENTATION HINT:
 * 1. Use findStudentByID() to locate student
 * 2. Return OPERATION_NOT_FOUND if student not found
 * 3. Driver will handle formatting and display
 * 4. Return OPERATION_SUCCESS if student found
 * 
 * NOTE: This function works with the driver to display formatted output
 */

int displayStudentGrades(int studentID) {
    // TODO: Implement student lookup for display
    // 🕵️‍♀️HINT: Find student, get all grades, calculate average and letter grade
    // 🕵️‍♀️HINT: Use findStudentByID() to check if student exists

    //search iterably for the student and return error if not found
    int studentIdx = findStudentByID(studentID);
    if(studentIdx == OPERATION_NOT_FOUND) return OPERATION_NOT_FOUND;
    
    //found
    return OPERATION_SUCCESS;
}

/* ====================================================================================
 * TODO 8: Calculates comprehensive class statistics (30 points) - MAJOR IMPLEMENTATION
 * ===================================================================================== 
 * Parameters: None (uses global arrays)
 * Returns: OPERATION_SUCCESS if calculated, OPERATION_NOT_FOUND if no students
 * 
 * REQUIREMENT: Students must calculate ALL statistics and populate global arrays
 * - assessmentStats[16]: average, count, min, max for each assessment type
 * - gradeDistributionCounts[5]: count of A, B, C, D, F grades
 * 
 * IMPLEMENTATION HINTS:
 * 1. Initialize both global arrays to default values
 * 2. Check if studentCount > 0, return OPERATION_NOT_FOUND if no students
 * 3. For each assessment type (Quiz, Assignment, Midterm, Final): *   
 *    a. Count valid grades
 *    b. Calculate sum, find min and max
 *    c. Calculate average
 *    d. Store results in assessmentStats[i] array
 * 4. Calculate grade distribution: *    
 *    a. Calculate each student's average using calculateStudentAverage()
 *    b. Convert to letter grade using getLetterGrade()
 *    c. Count occurrences of each letter grade
 *    d. Store the letter grade counts in gradeDistributionCounts array
 * 5. Return OPERATION_SUCCESS
 * 
 * ARRAY LAYOUTS:
 * assessmentStats[16]:
 * [0-3] = Quiz: average, count, min, max
 * [4-7] = Assignment: average, count, min, max  
 * [8-11] = Midterm: average, count, min, max
 * [12-15] = Final: average, count, min, max
 * 
 * gradeDistributionCounts[5]:
 * [0] = A count, [1] = B count, [2] = C count, [3] = D count, [4] = F count
 */

int calculateStatistics(void) {
    // Step 1: Initialize global arrays to default values
    for(int i = 0; i < 16; i++) {
        assessmentStats[i] = -1.0f;  // -1 indicates no data available
    }
    for(int i = 0; i < 5; i++) {
        gradeDistributionCounts[i] = 0;
    }
    
    // Step 2: Check if students exist
    if(studentCount <= 0) {
        return OPERATION_NOT_FOUND;
    }
    
    // TODO: STUDENTS MUST IMPLEMENT THE ASSESSMENT STATISTICS CALCULATIONS    
    // Step 3: Calculate statistics for each assessment type

    //loop 4 times, once for every assesment type we have to fill
    for (int i = 0; i < 4; i++)
    {
        //initialize the varaibles we are going to use 
        float sum = 0.0f;
        int count = 0;
        float min = MAX_GRADE +1.0f;
        float max = MIN_GRADE-1.0f;

        //find the minimun and maximum grade for every assignment type
        for(int j = 0; j < studentCount; j++)
        {
            float grades = -1.0f; 
            if(i == 0){
                grades = quizGrades[j];
            }
            if(i == 1){
                grades = assignmentGrades[j];
            }
            if(i == 2){
                grades = midtermGrades[j];
            }
            if(i == 3){
                grades = finalGrades[j];
            }
            
            
            if(grades >= 0.0f){
                sum+=grades;
                count++;
                if(grades<min) min = grades;    
                if(grades>max) max = grades;    
            }
        }

        //populate the assesment stats the base value specifies when wer are moving to the next assessment (0-3, 4-7,....etc)
        int base = 4 * i;

        //update counts for the respective assesment type, starting with 0-3 
        //idx(base + 0) = avg, idx(base + 1) = count, idx(base + 2) = min, idx(base + 3) = max )
        //base modifies where in the array we are located, on the firs loop we populate ranges from base +0 to base +3
        //which are the ranges for the quiz
        //on the second loop base jumps to 4, moving us to the next assesment area and so on.
        if(count > 0){
            assessmentStats[base + 0] = sum/(float)count;
            assessmentStats[base + 1] = (float)count;
            assessmentStats[base + 2] = min;
            assessmentStats[base + 3] = max;
        } else {
            assessmentStats[base + 0] = -1.0f;
            assessmentStats[base + 1] = -1.0f;
            assessmentStats[base + 2] = -1.0f;
            assessmentStats[base + 3] = -1.0f;
        }
    }
    

    // TODO: STUDENTS MUST IMPLEMENT GRADE DISTRIBUTION CALCULATION:
    // Step 4: Calculate grade distribution    

    //for every student we calculate their average score and update counts
    for (int i = 0; i < studentCount; i++)
    {
        float average = calculateStudentAverage(i);
        if(average<0.0f){
            continue;
        }
        char letter = getLetterGrade(average);
        //simple switch to decide what count to update
        switch(letter){
            case 'A':
                gradeDistributionCounts[0]++;
                break;
            case 'B':
                gradeDistributionCounts[1]++;
                break;
            case 'C':
                gradeDistributionCounts[2]++;
                break;
            case 'D':
                gradeDistributionCounts[3]++;
                break;
            case 'F':
                gradeDistributionCounts[4]++;
                break;
            default:
                break;
        }
    }
    
    return OPERATION_SUCCESS; // Only return this after implementing all calculations above
}

