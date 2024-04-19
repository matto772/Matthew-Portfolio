import subprocess

numThreads = 2

#incraments by spaces
for spaces in range(1,21):
    cmd = f"./sample {numThreads}, {spaces}"
    result = subprocess.run(cmd, shell=True, capture_output=True, text=True)
    timeString = result.stdout.strip().split(': ')[-1] #chopping off the string again
    timing = float(timeString)
    print(f"{spaces}, {timing:.6f}")
