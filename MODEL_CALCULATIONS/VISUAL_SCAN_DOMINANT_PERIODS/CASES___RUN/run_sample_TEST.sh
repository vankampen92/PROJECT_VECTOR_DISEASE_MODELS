##3 -m0 TYPE_of_MODEL
### -H7 0.0
###../CASES_1 -H7 0.0 -S0 19 -n 1 -v0 3 -G0 1 -G1 1 

### Parameter Values (Proc Roy Soc L Ser B, 2011) 
### ../CASES_1_Hu_4p -H7 0.00001 -C3 0.1 -L2 1.0E5 -M2 0.01 -M3 0.04 -H6 0.05 -H5 5 -P0 10 -P1 0.05 -S0 4 -n 1 -v0 3 -G0 2 -G1 2 
### ../CASES_1_Ca_4p -H7 0.00001 -C3 0.1 -L2 1.0E5 -M2 0.01 -M3 0.04 -H6 0.05 -H5 5 -P0 10 -P1 0.05 -S0 4 -n 1 -v0 3 -G0 2 -G1 2 
### ../CASES_1_Mo_4p -H7 0.00001 -C3 0.1 -L2 1.0E5 -M2 0.01 -M3 0.04 -H6 0.05 -H5 5 -P0 10 -P1 0.05 -S0 4 -n 1 -v0 3 -G0 2 -G1 2 
### ../CASES_1_Pa_4p -H7 0.00001 -C3 0.1 -L2 1.0E5 -M2 0.01 -M3 0.04 -H6 0.05 -H5 5 -P0 10 -P1 0.05 -S0 4 -n 1 -v0 3 -G0 2 -G1 2

### ../CASES_1_Hu_2p -H7 0.0 -L2 1.0E4 -M1 0.5 -M2 0.1 -M3 0.05 -H6 0.05 -H5 1 -C3 0.1 -P0 1 -P1 0.05 -S0 2 -n 1 -v0 3 -G0 2 -G1 1 

### Parameters that produce cycles around 3 to 4 years... (Notice -H2 H_Delta 4.5E-5 ---approx 60 anys; -H2 1.4E-4 ---> approx 20 anys) 
../CASES_1_Hu_4p -H7 0.00001 -L2 4.0E4 -C3 0.2 -M1 0.8 -M2 0.2 -M3 0.06 -H2 1.4E-4 -H3 3.0E-3 -H4 9.0E-3 -H6 0.05 -H5 5 -P0 10 -P1 0.05 -S0 4 -n 1 -v0 19 -G0 2 -G1 2
mv pgplot.ps Hu_4p.ps
../CASES_1_Ca_4p -H7 0.00001 -L2 4.0E4 -C3 0.2 -M1 0.8 -M2 0.2 -M3 0.06 -H2 1.4E-4 -H3 3.0E-3 -H4 9.0E-3 -H6 0.05 -H5 5 -P0 10 -P1 0.05 -S0 4 -n 1 -v0 19 -G0 2 -G1 2
mv pgplot.ps Ca_4p.ps
../CASES_1_Mo_4p -H7 0.00001 -L2 4.0E4 -C3 0.2 -M1 0.8 -M2 0.2 -M3 0.06 -H2 1.4E-4 -H3 3.6E-3 -H4 9.0E-3 -H6 0.05 -H5 5 -P0 10 -P1 0.05 -S0 4 -n 1 -v0 19 -G0 2 -G1 2
mv pgplot.ps Mo_4p.ps
../CASES_1_Pa_4p -H7 0.00001 -L2 4.0E4 -C3 0.2 -M1 0.8 -M2 0.2 -M3 0.06 -H2 1.4E-4 -H3 3.6E-3 -H4 9.0E-3 -H6 0.05 -H5 5 -P0 10 -P1 0.05 -S0 4 -n 1 -v0 19 -G0 2 -G1 2
mv pgplot.ps Pa_4p.ps
### Parameters that produce cycles around 3 to 4 years... 
### ../CASES_1_Hu_1p -H7 0.00001 -L2 4.0E4 -C3 0.2 -M1 0.8 -M2 0.2 -M3 0.06 -H2 4.5E-5 -H3 3.0E-3 -H4 9.0E-3 -H6 0.05 -H5 5 -P0 10 -P1 0.05 -S0 1 -n 1 -v0 19 -G0 1 -G1 1
