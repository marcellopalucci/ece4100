// -------------------------------------------------- //
// Implement all your code for this lab in this file. //
// This will be the only C++ file you will submit.    //
// -------------------------------------------------- //

// studentwork.cpp
// Analyzes a record in a CPU trace file.
// Author: Marcello Palucci

#include "trace.h"
#include <assert.h>
#include <vector>
#include <algorithm>
// You may include any other standard C or C++ headers you need here,
// e.g. #include <vector> or #include <algorithm>.
// Make sure this compiles on the reference machine!

// ----------------------------------------------------------------- //
// Do not modify the definitions of the four global variables below. //
// You may add more global variables if you need them.               //
// ----------------------------------------------------------------- //

/**
 * Total number of instructions executed.
 *
 * This variable is updated automatically by the code in sim.cpp.
 * You should not modify it, but you may find it useful for debugging,
 * e.g. as a unique identifier for a record in a trace file.
 */
uint64_t stat_num_inst = 0;

/**
 * Array of number of instructions executed by op type.
 *
 * For instance, stat_optype_dyn[OP_ALU] should be the number of times an ALU
 * instruction was executed in the trace.
 *
 * You must update this on every call to analyze_trace_record().
 */
uint64_t stat_optype_dyn[NUM_OP_TYPES] = {0};

/**
 * Total number of CPU cycles.
 *
 * You must update this on every call to analyze_trace_record().
 */
uint64_t stat_num_cycle = 0;

/**
 * Total number of unique instructions executed.
 *
 * Instructions with the same address should only be counted once.
 *
 * You must update this on every call to analyze_trace_record().
 */
uint64_t stat_unique_pc = 0;

/**
 * Vector that stores the unique pc's to check for copies before
 * incrementing stat_unique_pc
 */
std::vector<uint64_t> unique_pc_vector;

// ------------------------------------------------------------------------- //
// You must implement the body of the analyze_trace_record() function below. //
// Do not modify its return type or argument type.                           //
// You may add helper functions if you need them.                            //
// ------------------------------------------------------------------------- //

/**
 * Updates the global variables stat_num_cycle, stat_optype_dyn, and
 * stat_unique_pc according to the given trace record.
 *
 * You must write code to implement this function.
 * Make sure you DO NOT update stat_num_inst; it is updated by the code in
 * sim.cpp.
 *
 * @param t the trace record to process. Refer to the trace.h header file for
 * details on the TraceRec type.
 */
void analyze_trace_record(TraceRec *t) {
    assert(t);

    // TODO: Task 1: Quantify the mix of the dynamic instruction stream.
    // Update stat_optype_dyn according to the trace record t.
    
    //need to check if the optype is within the bounds
    if (t->optype >= 0 && t->optype < NUM_OP_TYPES){
        stat_optype_dyn[t->optype]++;
    }
        
    // TODO: Task 2: Estimate the overall CPI using a simple CPI model in which
    // the CPI for each category of instructions is provided.
    // Update stat_num_cycle according to the trace record t.
    switch (t->optype){
        case 0:
            stat_num_cycle += 1;
            break;
        case 1:
            stat_num_cycle += 2;
            break;
        case 2:
            stat_num_cycle += 2;
            break;
        case 3:
            stat_num_cycle += 3;
            break;
        case 4: 
            stat_num_cycle += 1;
            break;
        default:
            stat_num_cycle += 0;
            break;
    }

    // TODO: Task 3: Estimate the instruction footprint by counting the number
    // of unique PCs in the benchmark trace.
    // Update stat_unique_pc according to the trace record t.
    int count =  std::count(unique_pc_vector.begin(), unique_pc_vector.end(), t->inst_addr);
    if (count == 0) {
        stat_unique_pc++;
        unique_pc_vector.push_back(t->inst_addr);
    }
    // Make sure you DO NOT update stat_num_inst.
}
