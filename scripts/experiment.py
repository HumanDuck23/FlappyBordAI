import subprocess
import sys

if len(sys.argv) != 3:
    print("Usage: python experiment.py <path_to_exe> <config_file>")
    sys.exit(1)

exe_path = sys.argv[1]  # C++ executable
config_path = sys.argv[2]  # Config file

config = {}
with open(config_path, "r") as f:
    for line in f:
        key, value = line.strip().split("=")
        config[key] = value

brain_shape = config["brainShape"]
log_file = config["logFile"]
mutation_rate = config["mutationRate"]
mutation_chance = config["mutationChance"]

# Run FlappyBord
command = [exe_path, brain_shape, log_file, mutation_rate, mutation_chance]
print(f"Starting C++ program: {' '.join(command)}")

cpp_process = subprocess.Popen(
    command,
    stdout=subprocess.PIPE,
    stderr=subprocess.PIPE,
    universal_newlines=True,
    bufsize=1
)

# Start monitoring
visualize_process = subprocess.Popen(["python", "visualize.py", log_file])

# Read C++ output and print it
while True:
    output = cpp_process.stdout.readline()
    if output == "" and cpp_process.poll() is not None:
        break
    if output:
        print(output.strip())

# Wait for both to be done
cpp_process.wait()
visualize_process.wait()

print("Experiment complete")
