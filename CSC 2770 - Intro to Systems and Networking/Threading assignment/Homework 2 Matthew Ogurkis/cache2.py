import subprocess

#incraments the threads
for threads in range(1,9):
    
    cmd = f"./sample2 {threads}"
    result = subprocess.run(cmd, shell=True, capture_output=True, text=True)
    time = result.stdout.strip().split()[-1]
    timing = float(time)
    print(f"{threads}, {timing}")

