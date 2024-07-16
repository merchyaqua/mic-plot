def schedule_jobs(jobs, num_machines):
    # Step 1: Sort jobs by start time, and by end time if start times are the same
    jobs.sort(key=lambda x: (x.start_time, x.end_time))
    
    # Step 2: Initialize machine availability and type tracking
    machines = [[] for _ in range(num_machines)]
    end_times = [0] * num_machines
    last_job_type = [None] * num_machines  # Assuming job types are identifiable
    swaps = 0

    # Step 3: Assign jobs to machines
    for job in jobs:
        # Find a suitable machine
        best_machine = -1
        best_time = float('inf')
        
        for i in range(num_machines):
            if end_times[i] <= job.start_time and (last_job_type[i] is None or last_job_type[i] == job.type):
                # This machine can take the job without switching types
                if end_times[i] < best_time:
                    best_machine = i
                    best_time = end_times[i]
        
        if best_machine == -1:
            swaps+=1

            # No machine can take this job without a switch, find the next available machine
            for i in range(num_machines):
                if end_times[i] <= job.start_time:
                    if end_times[i] < best_time:
                        best_machine = i
                        best_time = end_times[i]
        
        # Assign the job to the best machine found
        machines[best_machine].append(job)
        end_times[best_machine] = job.end_time
        last_job_type[best_machine] = job.type
    print(swaps)
    return machines

class Job:
    def __init__(self, start_time, end_time, type):
        self.start_time = start_time
        self.end_time = end_time
        self.type = type

# Reading input from 'odyssiad.in'
with open('odyssiad.in', 'r') as file:
    data = file.read().split()

# Parse input data
index = 0
num_scenes = int(data[index])
index += 1
num_actors = int(data[index])
index += 1

jobs = []
actor_to_id = {}
id_to_actor = {}
actor_count = 1

for scene in range(1, num_scenes + 1):
    num_actors_in_scene = int(data[index])
    index += 1
    for _ in range(num_actors_in_scene):
        actor_name = data[index]
        index += 1
        if actor_name not in actor_to_id:
            actor_to_id[actor_name] = actor_count
            id_to_actor[actor_count] = actor_name
            actor_count += 1
        actor_id = actor_to_id[actor_name]
        jobs.append(Job(scene, scene + 1, actor_id))  # Assuming each scene is 1 unit of time



num_machines = 30  # Assuming 30 available mics as in the C++ code
schedule = schedule_jobs(jobs, num_machines)

# Output the results
for i, machine in enumerate(schedule):
    print(f"Machine {i+1}:")
    for job in machine:
        print(f"  Job({job.start_time}, {job.end_time}, {id_to_actor[job.type]})")
