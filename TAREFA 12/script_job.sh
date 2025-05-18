#!/bin/bash 
#SBATCH --partition=intel-128
#SBATCH --job-name=task11.2
#SBATCH --time=0-0:5
#SBATCH --cpus-per-task=8 
#SBATCH --hint=compute_bound

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

./task11.2


