#!/bin/bash
mkdir -p logs
for f in maps/fail_current/*; do
    name=$(basename "$f")
    echo "===== $name =====" | tee -a logs/full_report.txt
    timeout 5 valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
        ./cub3d "$f" 2>&1 | tee -a logs/full_report.txt
    echo | tee -a logs/full_report.txt
done