import subprocess

#incraments in 1000s
for size in range(20000, 40001, 1000):
    total_time = 0.0
    num_runs = 20
    #ensures that it runs 20 times and gets the time
    for i in range(num_runs):
        cmd = f"./sample {size}"
        result = subprocess.run(cmd, shell=True, capture_output=True, text=True)
        timeString = result.stdout.strip().split(': ')[-1]
        #checks to make sure the string is empty so the time can be swiped up
        if timeString:
            total_time += float(timeString)
    avg_time = total_time / num_runs
    print(f"{size}, {avg_time:.6f}")