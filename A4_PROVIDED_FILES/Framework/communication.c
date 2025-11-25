/* 
   ####################################################
   IMPLEMENT FUNCTION 3:
    - add_communication() (20 points)
   ################################################### 
*/


#include "space_mission.h"

/**
 * FUNCTION 3: add_communication 
 * 
 * PURPOSE: Add a communication log entry to a specified mission
 * 
 * PARAMETERS:
 *   system - Pointer to mission control system
 *   mission_id - Target mission identifier
 *   timestamp - Communication timestamp in YYYY-MM-DD HH:MM format
 *   priority - Message priority (ROUTINE, URGENT, or EMERGENCY)
 *   message - Communication message content
 * 
 * RETURNS:
 *   0 on success, -1 on failure
 * 
 * REQUIREMENTS:
 *  - Validate all parameters: input parameters, enum values, NULL checks, timestamp format using `is_valid_timestamp_format()`
 *  - Validate MessagePriority enum values (ROUTINE, URGENT, EMERGENCY)
 *  - Find target mission by mission_id, return -1 if not found
 *  - Expand communications array using realloc when needed (double capacity)
 *  - Generate unique log_id and initialize communication structure
 */
int add_communication(MissionControl* system, int mission_id, const char* timestamp,
                     MessagePriority priority, const char* message) {
    
    // TODO: Implement add_communication with comprehensive validation
    //
    // 1. INPUT VALIDATION:
    //    - Check system, timestamp, and message for NULL
    //    - Verify message is not empty and within MAX_MESSAGE_LENGTH
    //    - Use/call is_valid_timestamp_format() in the driver to validate timestamp
    //    - Validate priority enum (ROUTINE, URGENT, EMERGENCY)
    //    - Return -1 if any validation fails
    //
    // 2. FIND TARGET MISSION:
    //    - Search through system->missions array for matching mission_id
    //    - Return -1 if mission not found
    //
    // 3. EXPAND COMMUNICATIONS ARRAY:
    //    - Check if communications array needs expansion (comm_count >= comm_capacity)
    //    - Use realloc() to double capacity if needed
    //    - Update mission's comm_capacity after successful realloc
    //
    // 4. ADD NEW COMMUNICATION:
    //    - Generate unique log_id (use comm_count + 1)
    //    - Copy timestamp and message to new communication entry
    //    - Set priority and acknowledged status (0 = not acknowledged)
    //    - Increment mission's comm_count
    //    - Return 0 for success
    
    // Your implementation here:


      // Basic pointer checks
      if (system == NULL || timestamp == NULL || message == NULL) {
         return -1;
      }

      // Ensure missions array exists and capacity is valid
      if (system->missions == NULL || system->capacity <= 0) {
         return -1;
      }

      // Validate mission_id
      if (mission_id <= 0) {
         return -1;
      }

      // Validate message 
      if (message[0] == '\0') {
         return -1;
      }
      size_t msg_len = strlen(message);
      if (msg_len >= MAX_MESSAGE_LENGTH) {
         // Would overflow CommLog.message
         return -1;
      }

      // Validate timestamp format using provided helper
      if (!is_valid_timestamp_format(timestamp)) {
         return -1;
      }

      // Validate priority enum
      if (priority != ROUTINE && priority != URGENT && priority != EMERGENCY) {
         return -1;
      }

      /* 2. FIND TARGET MISSION */

      Mission *target_mission = NULL;
      for (int i = 0; i < system->mission_count; i++) {
         if (system->missions[i].mission_id == mission_id) {
               target_mission = &system->missions[i];
               break;
         }
      }

      if (target_mission == NULL) {
         // Mission not found
         return -1;
      }

      //3. EXPAND COMMUNICATIONS ARRAY IF NEEDED 

      if (target_mission->comm_capacity <= 0 && target_mission->communications == NULL) {
         // Safety: initialize if somehow not set up
         target_mission->comm_capacity = INITIAL_COMM_CAPACITY;
         target_mission->communications = (CommLog*) calloc(
               target_mission->comm_capacity, sizeof(CommLog)
         );
         if (target_mission->communications == NULL) {
               return -1;
         }
      }

      if (target_mission->comm_count >= target_mission->comm_capacity) {
         int new_capacity = target_mission->comm_capacity * 2;
         if (new_capacity <= 0) {
               new_capacity = INITIAL_COMM_CAPACITY;
         }

         CommLog *new_array = (CommLog*) realloc(
               target_mission->communications,
               new_capacity * sizeof(CommLog)
         );
         if (new_array == NULL) {
               // Realloc failed; keep old pointer intact
               return -1;
         }

         target_mission->communications = new_array;
         target_mission->comm_capacity = new_capacity;
      }

      // 4. ADD NEW COMMUNICATION 

      int index = target_mission->comm_count;
      CommLog *log = &target_mission->communications[index];

      // Unique log_id within this mission
      log->log_id = index + 1;

      // Copy timestamp safely
      strncpy(log->timestamp, timestamp, MAX_TIMESTAMP_LENGTH - 1);
      log->timestamp[MAX_TIMESTAMP_LENGTH - 1] = '\0';

      // Copy message safely
      strncpy(log->message, message, MAX_MESSAGE_LENGTH - 1);
      log->message[MAX_MESSAGE_LENGTH - 1] = '\0';

      log->priority = priority;
      log->acknowledged = 0;   // Not acknowledged initially

      target_mission->comm_count++;

      return 0;
    
}