#!/bin/bash
#SBATCH -n 2
#SBATCH -t 00:05:00
#SBATCH -o test.out
#SBATCH -e test.err
module load octave/4.0.0
mpirun -n 2 octave test.m
