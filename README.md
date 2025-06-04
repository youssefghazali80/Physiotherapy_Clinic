# Physiotherapy_Clinic
Physiotherapy Center Simulation – Project Description
🎯 Objective
The goal is to develop a system that simulates a physiotherapy center, managing:

Patient appointments and arrivals,

Therapist treatment scheduling,

Treatment resource usage and availability.

This system must reflect real-world constraints using appropriate data structures and efficient algorithms to simulate the dynamic interaction between patients, treatments, and resources over discrete timesteps.

⏱ Simulation Time (Timestep-Based)
The simulation runs on discrete timesteps starting from 1. At each timestep, the system:

Processes patient arrivals,

Manages treatment assignments,

Updates statuses of patients and resources,

Tracks statistics.

🧑‍⚕️ Main Entities
👥 Patients
Each patient record includes:

ID (PID),

Type: Normal (N) or Recovering (R),

Appointment Time (PT),

Arrival Time (VT),

Required Treatments (max 3),

Status: IDLE, EARLY, LATE, WAIT, SERV, or FINISHED.

Patient Types:
Normal Patient (N): Must follow the treatment order as given.

Recovering Patient (R): Can undergo treatments in any order based on resource availability and queue latency.

💆 Treatments
Three treatment types:

Electrotherapy (E) → requires an electro device.

Ultrasound Therapy (U) → requires an ultrasound device.

Exercise Therapy (X) → requires a gym room with defined capacity.

🏗 System Components
📄 Lists
The system manages multiple patient lists:

ALL Patients (from input),

Early Arrivals, Late Arrivals,

Waiting Lists (E, U, X),

In-Treatment List,

Finished Patients.

And several Resource Lists:

Available E-Devices, U-Devices, X-Rooms.

📋 Rules
A patient cannot receive the same treatment type twice.

Early patients are moved to the waiting list when their appointment time arrives.

Late patients must wait a penalty time before joining waiting lists.

Waiting lists are sorted by appointment time.

Room capacity must be respected when assigning X-treatments.

Cancellations and rescheduling are probabilistic and based on input parameters.

🔄 Special Events
Cancellation: Patients in the X-waiting list (with X as last treatment) may cancel and leave based on a probability.

Rescheduling: Early patients may request a later PT with a random new value (must be > current PT), also based on a probability.

🛠 Core Simulation Functions
At each timestep:

Move patients from the ALL list to Early/Late/Waiting based on VT.

Assign patients to available resources when ready.

Move patients from treatment to the next required step or finish list.

Handle cancellation and rescheduling events randomly based on provided probabilities.

Print or save the status of the system (interactive or silent mode).

📥 Input File Format
Numbers of devices and rooms.

Room capacities.

Probabilities for cancellation and rescheduling.

Patient data lines (ID, type, PT, VT, treatments with durations).

📤 Output File Format
For each patient:

ID, Type, PT, VT, Finish Time (FT), Waiting Time (WT), Treatment Time (TT),

Whether they cancelled/rescheduled.

At the end, output system-wide statistics:

Total timesteps,

Average WT/TT,

Percentages for early/late patients, accepted cancels/reschedules.

🖥 Program Modes
Interactive Mode: User can view system status step-by-step.

Silent Mode: Simulation runs in the background and only generates output files.
