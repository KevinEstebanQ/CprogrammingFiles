/* 
   ####################################################
   IMPLEMENT FUNCTION 6:
    - free_mission_control() (10 points)
   ################################################### 
*/


#include "space_mission.h"

/**
 * FUNCTION 6: free_mission_control()
 
 * PURPOSE: Safely deallocate all memory associated with the mission control system
 * 
 * PARAMETERS:
 *   system - Pointer to mission control system (can be NULL)
 * 
 * RETURNS:
 *   void
 * 
 * REQUIREMENTS:
 *  - Handle NULL system pointer gracefully (return without error)
 *  - Free communications arrays for each mission (innermost level)
 *  - Free missions array (middle level)
 *  - Free main system structure (outermost level)
 *  - Follow proper deallocation order to prevent corruption
 *  - Prevent memory leaks and double-free errors
 * 
 * 💀 CRITICAL: Order of deallocation matters for nested structures
 * Must free from innermost to outermost allocations
 */
void free_mission_control(MissionControl* system) {
    
    // TODO: Implement free_mission_control with proper memory deallocation
    //
    // 1. NULL CHECK:
    //    - Check if system is NULL
    //    - Return gracefully if NULL (not an error)
    //
    // 2. FREE NESTED ARRAYS:
    //    - Check if missions array is not NULL
    //    - Loop through each mission in the system
    //    - For each mission:
    //      * Free communications array if not NULL
    //      * Set pointer to NULL (good practice)
    //
    // 3. FREE MISSIONS ARRAY:
    //    - Free the missions array itself
    //    - Set missions pointer to NULL
    //
    // 4. FREE MAIN STRUCTURE:
    //    - Free the main system structure
    //
    // MEMORY HIERARCHY (free in this order):
    //   1. mission->communications (innermost)
    //   2. system->missions (middle)
    //   3. system (outermost)
    
    // Your implementation here:
    // 1. NULL CHECK
    if (system == NULL) {
        return;  // nothing to free
    }

    // 2. FREE NESTED ARRAYS (per-mission communications)
    if (system->missions != NULL) {
        for (int i = 0; i < system->mission_count; i++) {
            Mission *m = &system->missions[i];

            if (m->communications != NULL) {
                free(m->communications);
                m->communications = NULL;
                m->comm_count = 0;
                m->comm_capacity = 0;
            }
        }

        // 3. FREE MISSIONS ARRAY
        free(system->missions);
        system->missions = NULL;
        system->mission_count = 0;
        system->capacity = 0;
    }

    // 4. FREE MAIN STRUCTURE
    free(system);
    
}