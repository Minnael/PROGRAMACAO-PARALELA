#!/bin/bash 
#SBATCH --partition=intel-128
#SBATCH --job-name=task13
#SBATCH --time=0-0:5
#SBATCH --cpus-per-task=8 
#SBATCH --hint=compute_bound

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK
export OMP_PROC_BIND=master
export OMP_PLACES=cores


./task13