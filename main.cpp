/*
Medical Treatment Scheduler Simulation

This program simulates a hospital treatment scheduling system where patients
require different types of therapies (Electro, Ultrasound, Gym) with varying
priorities and schedules. The system manages resources and patient queues to
optimize treatment delivery.

Key components:
- Patient management with different types and priorities
- Resource management for three treatment types
- Scheduling algorithms for early, on-time, and late patients
- Simulation of treatment workflow over time

*/

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <memory>
#include <stdexcept>
#include "Scheduler.h"
#include "UI.h"
using namespace std;






// Helper function to create sample input file with 30 patients
/*
void createInputFile(const string& filename) {
    ofstream outfile(filename);
    if (!outfile.is_open()) {
        throw runtime_error("Cannot create file: " + filename);
    }

    // Format: ne nu ng gymCap cancelProb rescheduleProb numPatients
    outfile <<  "5 3 2"  << endl;      // 5 for E_Therapy, 3 U_Therapy, and 2 NG rooms
    outfile <<  "8 6"   << endl;      // Capacity of the  two X therapy Gym rooms
    outfile <<  "40 25"  << endl;      // Pcancel ,Presc (cancel and resedule property )
    outfile <<  "15"       << endl;      // Number of patients.
    
    // Write each patient's data directly
    outfile << "R 20 25 2 E 10 U 15" << endl;
    outfile << "N 30 25 3 E 5 U 12 X 10" << endl;
    outfile << "R 25 30 2 U 20 X 15" << endl;
    outfile << "R 30 35 3 U 6 E 5 X 10" << endl;
    outfile << "R 40 35 3 E 12 U 18 X 20" << endl;
    outfile << "R 50 40 1 X 5" << endl;
    outfile << "N 40 40 2 X 15 U 10" << endl;
    outfile << "R 40 45 2 E 15 X 20" << endl;
    outfile << "N 45 50 1 X 40" << endl;
    outfile << "R 50 55 1 E 30" << endl;
    outfile << "N 60 55 2 E 15 X 30" << endl;
    outfile << "N 55 60 3 E 20 U 25 X 30" << endl;
    outfile << "N 70 65 1 E 20" << endl;
    outfile << "R 65 70 3 E 15 U 20 X 35" << endl;
    outfile << "N 70 75 2 U 30 X 35" << endl;
    /*
    outfile << "N 60 55 2 E 15 X 30" << endl;
    
    outfile << "R 40 45 3 E 10 U 15 X 20" << endl;
    outfile << "N 35 40 2 U 25 X 15" << endl;

    outfile << "N 30 35 2 E 10 U 15" << endl;
    

    
    outfile << "N 55 60 2 E 20 X 25" << endl;
    outfile << "R 40 35 3 E 12 U 18 X 20" << endl;
    outfile << "N 25 30 1 U 15" << endl;
    outfile << "R 60 65 2 E 25 X 30" << endl;
    outfile << "N 35 40 1 E 15" << endl;
    outfile << "R 50 45 3 E 10 U 15 X 20" << endl;
    outfile << "N 70 75 2 U 30 X 35" << endl;
    outfile << "R 30 35 1 E 12" << endl;
    outfile << "N 45 50 2 E 15 U 20" << endl;
    outfile << "R 20 25 1 X 15" << endl;
    
    outfile << "R 40 45 2 E 15 X 20" << endl;
    outfile << "N 25 30 1 U 18" << endl;
    outfile << "R 65 70 2 E 30 U 35" << endl;
    outfile << "N 35 40 1 E 20" << endl;
    outfile << "R 50 55 3 E 12 U 18 X 25" << endl;
    */

  //  outfile.close();
   // cout << "Created input file '" << filename << "' with 4 patients" << endl;
// }


int main() {
    try {
        const string inputFile = "hospital_input_500_late_modified.txt";
        //createInputFile(inputFile);  // Create sample data
        
        Scheduler scheduler(inputFile,INTERACTIVE);
        scheduler.simulate();  // 
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    
    return 0;
}