rm Parameter_Trend.dat
../$1 -G8 1 -G9 4 -G11 5 -G5 0 -G6 0.0 -G7 1.0 -S0 19 -n 2 -v0 3 -v1 5 -v2 30 -G0 1 -G1 2 -G2 1 -G3 0.0 -G4 1240.0 -G5 1 -G6 0.0 -G7 1.0 -t0 2000 -t1 0.0 -t2 $2 \
 -H1 1.4E-4 -H2 1.4E-4 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.00001  -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M1 0.5 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05 \
 -TP 12 -TY -1 # -T0 0.0 -T1 1240.0 -Ti 800.0 -M0 0.15 -TI 0.15 -TM 0.45 -TF 0.15  

# ../$1 -S0 19 -n 2 -v0 3 -v1 21 -G0 1 -G1 3 -t0 200 -t1 0.0 -t2 32400.0  \
# -H2 1.4E-4 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.00001  -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M1 0.5 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05 
# Trend Argument Control Parameters:
# -TP 12 -TY 0 -T0 0.0 -T1 32400.0 -Ti 16200.0 -M0 0.15 -TI 0.15 -TM 0.45 -TF 0.15  

# -TP 25 -TY 0 -T0 1000.0 -T1 108000.0 -Ti 54000.0 -TI 4.0E4 -TM 7.0E4 -TF 4.1E4  

# Biting rate Trend:
# -TP 12 -TY 0 -T0 1000.0 -T1 10800.0 -Ti 5400.0 -M0 0.23 -TI 0.23 -TF 0.24 -TM 0.37 
# -TP 12 -TY 0 -T0 1000.0 -T1 108000.0 -Ti 54000.0 -M0 0.15 -TI 0.15 -TF 0.18 -TM 0.37 

# -n 20 -v0 2 -v1 3 -v2 4 -v3 8 -v4 9 -v5 12 -v6 15 -v7 16 -v8 17 -v9 20 -v10 21 -v11 22 -v12 23 -v13 24 -v14 26 -v15 27

## SOLUTION A:
# -H2 1.4E-4 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.00001  -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M0 0.3 -M1 0.5 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05 \

# Solution B: 
# -H2 1.4E-4 -H3 3.0E-3 -H4 9.0E-3 -H5 5 -H6 0.05 -H7 0.00001  -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.2  -M0 0.3 -M1 0.8 -M2 0.2 -M3 0.06 -L2 4.0E4 -P0 10 -P1 0.083 \ 
