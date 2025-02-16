import sys
import matplotlib.pyplot as plt

log_file_path = sys.argv[1] if len(sys.argv) > 1 else "score_log.txt"


def read_scores():
    generations = []
    scores = []
    with open(log_file_path, "r") as f:
        for line in f:
            parts = line.strip().split(": ")
            if len(parts) == 2 and parts[0].startswith("Gen"):
                gen_num = int(parts[0][3:])
                score = int(parts[1])
                generations.append(gen_num)
                scores.append(score)
    return generations, scores


plt.ion() # interactive stuff

while True:
    plt.clf()  # Clear

    # Read data
    generations, scores = read_scores()
    if generations:
        plt.plot(generations, scores, marker='o', linestyle='-', color='b', label="Highest Score")
        plt.xlabel("Generation")
        plt.ylabel("Highest Score")
        plt.title("Highest Score per Generation")
        plt.legend()
        plt.grid(True)

    plt.pause(1)
