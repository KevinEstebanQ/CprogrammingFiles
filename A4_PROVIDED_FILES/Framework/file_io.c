/* 
   ####################################################
   IMPLEMENT FUNCTIONS 4 & 5:
    - load_missions_from_file() (15 points)
    - save_mission_report() (10 points)
   ################################################### 
*/


#include "space_mission.h"

/**
 * FUNCTION 4: load_missions_from_file()
 * 
 * PURPOSE: Load mission data from a text file using fscanf()
 * 
 * File format:
 * Line 1: number_of_missions
 * Following lines: mission_id mission_name launch_date
 * 
 * PARAMETERS:
 *   system - Pointer to mission control system
 *   filename - Path to input file
 * 
 * RETURNS:
 *   0 on success, -1 on failure
 * 
 * REQUIREMENTS:
 *  - Use fscanf() for file input parsing
 *  - Validate file operations and parsed data before creating missions
 *  - Create missions using existing create_mission_with_crew() function in mission_control.c
 *  - Handle file errors and invalid data gracefully
 *  - Support loading 0 missions (empty file case)
 */
int load_missions_from_file(MissionControl* system, const char* filename) {
    
    // TODO: Implement load_missions_from_file() with file I/O
    //
    // 1. INPUT VALIDATION:
    //    - Check system and filename for NULL
    //    - Return -1 if invalid
    //
    // 2. OPEN FILE:
    //    - Use fopen() to open file for reading ("r" mode)
    //    - Return -1 if file cannot be opened
    //
    // 3. READ MISSION COUNT:
    //    - Use fscanf() to read number of missions from first line
    //    - Validate mission count is non-negative
    //    - Handle case where mission count is 0 (empty file)
    //
    // 4. READ MISSION DATA:
    //    - Loop through each mission entry
    //    - Use fscanf() to read: mission_id, mission_name, launch_date
    //    - Validate each field (mission_id > 0, valid date format)
    //    - Call create_mission_with_crew() function in mission_control.cfor each valid mission
    //    - Return -1 if any mission creation fails
    //
    // 5. CLEANUP:
    //    - Close file using fclose()
    //    - Return 0 for success
    
    // Your implementation here:
     // 1. INPUT VALIDATION
    if (system == NULL || filename == NULL) {
        return -1;
    }

    // 2. OPEN FILE
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        return -1;
    }

    // 3. READ MISSION COUNT
    int mission_count = 0;
    if (fscanf(fp, "%d", &mission_count) != 1 || mission_count < 0) {
        fclose(fp);
        return -1;
    }

    // 4. READ MISSION DATA
    for (int i = 0; i < mission_count; i++) {
        int mission_id;
        char name[MAX_NAME_LENGTH];
        char launch_date[MAX_DATE_LENGTH];

        // Expect: mission_id mission_name launch_date
        if (fscanf(fp, "%d %49s %11s", &mission_id, name, launch_date) != 3) {
            fclose(fp);
            return -1;
        }

        // Basic validation
        if (mission_id <= 0) {
            fclose(fp);
            return -1;
        }

        if (!is_valid_date_format(launch_date)) {
            fclose(fp);
            return -1;
        }

        // Create mission using existing function
        if (create_mission_with_crew(system, mission_id, name, launch_date) != 0) {
            fclose(fp);
            return -1;
        }
    }

    // 5. CLEANUP
    fclose(fp);
    return 0;
    
}

/*
 * FUNCTION 5: save_mission_report()
 * 
 * PURPOSE: Generate a comprehensive mission status report using fprintf()
 * 
 * PARAMETERS:
 *   system - Pointer to mission control system
 *   filename - Path to output file
 * 
 * RETURNS:
 *   0 on success, -1 on failure
 * 
 * REQUIREMENTS:
 *  - Use fprintf() for formatted output
 *  - Write professional report header with system statistics - refer to the 'SAMPLE_report.txt' file provided
 *  - For each mission: display mission details, communication counts by priority
 *  - Calculate and display system totals (total missions, total communications)
 *  - Handle file operations with proper error checking
 */
int save_mission_report(const MissionControl* system, const char* filename) {
    
    // TODO: Implement save_mission_report with formatted output
    //
    // 1. INPUT VALIDATION:
    //    - Check system and filename for NULL
    //    - Return -1 if invalid
    //
    // 2. OPEN FILE:
    //    - Use fopen() to open file for writing ("w" mode)
    //    - Return -1 if file cannot be opened
    //
    // 3. WRITE REPORT HEADER: - refer to the 'SAMPLE_report.txt' file provided:
    //    - Use fprintf() to write professional header
    //    - Include total missions count
    //    - Add appropriate formatting and separators
    //
    // 4. WRITE MISSION DETAILS:
    //    - Loop through all missions in system
    //    - For each mission, write:
    //      * Mission ID, name, launch date, status
    //      * Communication count
    //      * Communication summary by priority (routine/urgent/emergency counts)
    //
    // 5. WRITE SYSTEM TOTALS: - refer to the 'SAMPLE_report.txt' file provided:
    //    - Calculate and write total communications across all missions
    //    - Add footer formatting
    //
    // 6. CLEANUP:
    //    - Close file using fclose()
    //    - Return 0 for success
    
    // Your implementation here:
    // 1. INPUT VALIDATION
    if (system == NULL || filename == NULL) {
        return -1;
    }

    // 2. OPEN FILE
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        return -1;
    }

    // 3. WRITE REPORT HEADER (simple, but structured)
    fprintf(fp, "================= Space Mission Control Report =================\n");
    fprintf(fp, "Total Missions: %d\n", system->mission_count);
    fprintf(fp, "===============================================================\n\n");

    int total_comm = 0;
    int total_routine = 0;
    int total_urgent = 0;
    int total_emergency = 0;

    // 4. WRITE MISSION DETAILS
    for (int i = 0; i < system->mission_count; i++) {
        const Mission* m = &system->missions[i];

        int routine = 0, urgent = 0, emergency = 0;

        for (int j = 0; j < m->comm_count; j++) {
            const CommLog* log = &m->communications[j];
            total_comm++;

            switch (log->priority) {
                case ROUTINE:
                    routine++;
                    total_routine++;
                    break;
                case URGENT:
                    urgent++;
                    total_urgent++;
                    break;
                case EMERGENCY:
                    emergency++;
                    total_emergency++;
                    break;
                default:
                    break;
            }
        }

        fprintf(fp, "Mission ID   : %d\n", m->mission_id);
        fprintf(fp, "Name         : %s\n", m->mission_name);
        fprintf(fp, "Launch Date  : %s\n", m->launch_date);
        fprintf(fp, "Status       : %s\n", status_to_string(m->status));
        fprintf(fp, "Communications: %d (Routine: %d, Urgent: %d, Emergency: %d)\n",
                m->comm_count, routine, urgent, emergency);
        fprintf(fp, "---------------------------------------------------------------\n");
    }

    // 5. WRITE SYSTEM TOTALS
    fprintf(fp, "\n===================== System Communication Totals ==============\n");
    fprintf(fp, "Total Communications: %d\n", total_comm);
    fprintf(fp, "  Routine : %d\n", total_routine);
    fprintf(fp, "  Urgent  : %d\n", total_urgent);
    fprintf(fp, "  Emergency: %d\n", total_emergency);
    fprintf(fp, "===============================================================\n");

    // 6. CLEANUP
    fclose(fp);
    return 0;
    
}