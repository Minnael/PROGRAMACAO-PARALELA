#!/bin/bash 
#SBATCH --partition=amd-512
#SBATCH --job-name=OMP_hello 
#SBATCH --time=0-0:5
#SBATCH --cpus-per-task=8 
#SBATCH --hint=compute_bound

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

./hello_openmp


