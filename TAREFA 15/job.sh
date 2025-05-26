#!/bin/bash
#SBATCH --partition=intel-128 
#SBATCH --ntasks=32
#SBATCH --time=0-0:5

export OMPI_MCA_btl="^openib"
mpirun task15.1