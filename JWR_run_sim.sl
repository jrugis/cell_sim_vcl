#!/bin/bash
#SBATCH -J Serial_JOB
#SBATCH -A nesi00119          # Project Account
#SBATCH --time=0:59:00       # Walltime HH:MM:SS
#SBATCH --mem-per-cpu=32G     # Memory
#SBATCH --ntasks=1            # number of tasks
#SBATCH --cpus-per-task=1     # number of threads
##SBATCH --nodes=1             # number nodes
#SBATCH -C sb                 # sb=Sandybridge wm=Westmere

# output some information
echo $HOSTNAME

# load module(s)
module load intel/2015a
module load Python/2.7.9-intel-2015a

# run the job
srun -o sim.log ./src/cell_3d
