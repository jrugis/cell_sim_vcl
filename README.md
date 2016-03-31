# cell_sim_vcl
1. install dependencies: eigen, boost, viennacl
2. git clone https://github.com/jrugis/cell_sim_vcl.git
3. build the simulation code
  1. cd cell_sim_vcl/src
  2. cp JWR_Makefile Makefile
  3. edit Makefile (if required) for your build
  4. load modules as shown in the makefile
  5. make
  6. cd ..
4. run the simulation
  1. cp JWR_run_sim.sl run_sim.sl
  2. sbatch run_sim.sl
5. check the results
  1. diff c.bin c_REF.bin
