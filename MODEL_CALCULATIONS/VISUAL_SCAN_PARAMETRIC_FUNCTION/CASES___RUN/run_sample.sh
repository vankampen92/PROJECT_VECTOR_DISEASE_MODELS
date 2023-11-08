# ../CASES_33 -S0 19 -n 1 -v0 19 -G0 1 -G1 1 
# Important note: only some out variables can be used here: 
#     18 ---> V_0 Vectorial capacity 
#     19 ---> R_0_Next_Generation_Matrix
#     20 ---> R_0_Next_Generation_Matrix * R_0_Next_Generation_Matrix
#     (-v0 18 or -v0 19 or -v0 20)
#
#
### ./CASES_1 -H7 0.0 -L2 1.0E3 -S0 4 -n 1 -v0 19 -G0 2 -G1 2

### ../CASES_1_K0_24p -H7 0.0 -L2 4.0E4 -S0 24 -n 1 -v0 19 -G0 2 -G1 2

../CASES_1_R0_2p -H7 0.0 -L2 4.0E4 -M1 0.8 -M2 0.2 -M3 0.06 -H3 3.0E-3 -H4 9.0E-3 -H6 0.05 -H5 5 -C3 0.2 -P0 10 -P1 0.083 -S0 2 -n 1 -v0 19 -G0 1 -G1 2 

### ../CASES_1_R0_2p -H7 0.0 -L2 4.0E4 -C3 0.2 -M1 0.8 -M2 0.2 -M3 0.06 -H3 3.0E-3 -H4 9.0E-3 -H6 0.05 -H5 5 -C3 0.1 -P0 10 -P1 0.05 -S0 2 -n 1 -v0 19 -G0 1 -G1 2 

### ../CASES_1_K0_24p -H7 0.0 -L2 4.0E4 -C3 0.2 -M1 0.8 -M2 0.2 -M3 0.06 -H3 3.0E-3 -H4 9.0E-3 -H6 0.05 -H5 5 -C3 0.1 -P0 10 -P1 0.05 -S0 24 -n 1 -v0 19 -G0 2 -G1 2 

## ../CASES_1_Hu_4p -H7 0.0 -L2 3.0E4 -M2 0.1 -M3 0.06 -H4 2.6E-3 -H6 0.05 -H5 5 -C3 0.1 -P0 5 -P1 0.05 -S0 4 -n 1 -v0 19 -G0 2 -G1 2 
## ../CASES_1_Ca_4p -H7 0.0 -L2 3.0E4 -M2 0.1 -M3 0.06 -H4 2.6E-3 -H6 0.05 -H5 5 -C3 0.1 -P0 5 -P1 0.05 -S0 4 -n 1 -v0 19 -G0 2 -G1 2 
## ../CASES_1_Mo_4p -H7 0.0 -L2 3.0E4 -M2 0.1 -M3 0.06 -H4 2.6E-3 -H6 0.05 -H5 5 -C3 0.1 -P0 5 -P1 0.05 -S0 4 -n 1 -v0 19 -G0 2 -G1 2 
## ../CASES_1_Pa_4p -H7 0.0 -L2 3.0E4 -M2 0.1 -M3 0.06 -H4 2.6E-3 -H6 0.05 -H5 5 -C3 0.1 -P0 5 -P1 0.05 -S0 4 -n 1 -v0 19 -G0 2 -G1 2 
