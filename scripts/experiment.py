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

# Build command with named arguments
command = [exe_path]

for key, value in config.items():
    command.append(f"--{key}")
    command.append(value)

if "logFile" not in config:
    print("ERROR: logFile not specified in config! This field is required for data visualization!")
    sys.exit(1)

print(f"Starting C++ program: {' '.join(command)}")

cpp_process = subprocess.Popen(
    command,
    stdout=subprocess.PIPE,
    stderr=subprocess.PIPE,
    universal_newlines=True,
    text=True
)

# Start monitoring
visualize_process = subprocess.Popen(["python", "visualize.py", config["logFile"]])

# Read C++ output and print it
while True:
    output = cpp_process.stdout.readline()
    if output == "" and cpp_process.poll() is not None:
        break
    if output:
        print(output.strip())

return_code = cpp_process.poll()
if return_code is not None and return_code != 0:
    print(f"\n❌ ERROR: The executable crashed with exit code {return_code}.")

    # Capture and display stderr
    stderr_output = cpp_process.stderr.read().strip()
    if stderr_output:
        print("Crash details:\n" + stderr_output)

# Wait for both to be done
cpp_process.wait()
visualize_process.wait()

print("Experiment complete")
