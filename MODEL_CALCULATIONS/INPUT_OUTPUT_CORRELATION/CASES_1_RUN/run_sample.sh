### Annual Sampling: Annual accumulation of Cases (Variable 2)
### ../CASES_33_$1 -S0 19 -n 2 -v0 15 -v1 2 -G0 1 -G1 2 -t0 31 -t1 0.0 -t2 10950
### Monthly Sampling: Monthly accumulation of Cases (Variable 2)
### ../CASES_1_$1 -S0 19 -S3 100 -S4 12 -n 2 -v0 15 -v1 3 -G0 1 -G1 2 -t0 361 -t1 0.0 -t2 10800 -L2 4.0E+4 #-L2 2.0 

### 1D_SCAN
### ../CASES_1_$1 -G5 0 -G6 0.0 -G7 1.0 -S0 19 -S3 10 -S4 12 -S5 0.1 -S6 0.2 -n 3 -v0 15 -v1 3 -v2 21 -G0 1 -G1 3 -t0 1441 -t1 0.0 -t2 10800 \
### -H2 1.4E-4 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.00001  -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M0 0.3 -M1 0.5 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05

### 2D_SCAN
../CASES_1_$1 -G5 0 -G6 0.0 -G7 1.0 -S0 19 -S3 500 -S4 25 -n 2 -v0 15 -v1 3 -G0 1 -G1 2 -t0 1441 -t1 0.0 -t2 10800 \
 -H2 1.4E-4 -H3 3.0E-3 -H4 9.0E-3 -H5 5 -H6 0.05 -H7 0.00001   -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.2    -M0 0.3 -M1 0.8 -M2 0.2 -M3 0.06 -L2 4.0E4   -P0 10 -P1 0.083 

# SOLUTION A:
# -H2 1.4E-4 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.00001  -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M0 0.3 -M1 0.5 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05

# Solution B: 
# -H2 1.4E-4 -H3 3.0E-3 -H4 9.0E-3 -H5 5 -H6 0.05 -H7 0.00001   -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.2    -M0 0.3 -M1 0.8 -M2 0.2 -M3 0.06 -L2 4.0E4   -P0 10 -P1 0.083 

### Last parameter combination: -H7 0.00001 -L2 3.0E4 -M1 0.5 -M2 0.1 -M3 0.06 -H4 2.6E-3 -H6 0.05 -H5 20 -P0 20 -P1 0.05
### Dynamic regime parameters: -H7 0.00001 -L2 3.0E4 -M1 0.5 -M2 0.1 -M3 0.06 -H4 2.6E-3 -H6 0.05 -H5 1 -P0 1 -P1 0.05 (K_Seasonal_Intensity = 0.9)

### -L2 [K_0, average value] -v0 [ 15:K_0 ] -v1 [ 3:y[I] ]
### -S3 [No_of_POINTS] -S4 [Input_Parameter] -S5 [Value_0] -S6 [Value_1] -S6 0.35 / -S6 0.5
# -n 20 -v0 2 -v1 3 -v2 4 -v3 8 -v4 9 -v5 12 -v6 15 -v7 16 -v8 17 -v9 20 -v10 21 -v11 22 -v12 23 -v13 24 -v14 26 -v15 27


# Solution A: 
# -H2 1.4E-4 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.00001   -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1    -M0 0.3 -M1 0.5 -M2 0.2 -M3 0.04 -L2 3.0E4   -P0 1 -P1 0.05 

# /* Solution A */
# // -H2 1.4E-4 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.00001   -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1    -M0 0.3 -M1 0.5 -M2 0.2 -M3 0.04 -L2 3.0E4   -P0 1 -P1 0.05
# void Resetting_Parameter_Combination( Parameter_Table * Table, 
#                                      1.4E-4, 6.7E-4, 6.3E-3, 1, 0.00001,
#                                      0.2, 0.1, 
#                                      6.7E-2, 0.5, 3.0E4, 
#                                      0.3, 0.5, 0.2, 0.04, 
#                                      1, 0.05 )
# /* --------- */
# /* Solution B */
# // -H2 7.0E-5 -H3 3.0E-3 -H4 9.0E-3 -H5 5 -H6 0.05 -H7 0.00001   -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.2    -M0 0.3 -M1 0.8 -M2 0.2 -M3 0.06 -L2 4.0E4   -P0 10 -P1 0.083 
# void Resetting_Parameter_Combination( Parameter_Table * Table, 
#                                      1.4E-4, 3.0E-3, 9.0E-3, 5, 0.00001,
#                                      0.2, 0.2, 
#                                      6.7E-2, 0.5, 4.0E4, 
#                                      0.3, 0.8, 0.2, 0.06, 
#                                      10, 0.083 )
# /* --------- */

#  Solution B:
#  /* -H2 */ Table_H_Delta   = 1.0/40.0/360
#  /* -H3 */ Table.H_Sigma_0 = 3.0E-3
#  /* -H4 */ Table.H_Recov_0 = 9.0E-3;
#  /* -H5 */ Table.n_H       = 5;
#  /* -H7 */ Table.Imm       = 0.00


#  /* -C1 */ Table.H_Rho     = 0.2
#  /* -C3 */ Table.H_Nu      = 0.2;

#  /* -L0 */ Table.L_Devel     = 6.7E-2  /* Temperature Driven */
#  /* -L1 */ Table.L_Delta_0   = 0.5     /* Temperature Driven */
#  /* -L2 */ Table.K_0         = 4.0E4;

#  /* -M0 */ Table.M_a       = 0.3       /* Temperature Driven */
#  /* -M1 */ Table.M_b       = 0.8; 
#  /* -M2 */ Table.M_c       = 0.2;
#  /* -M3 */ Table.M_Delta   = 0.06;     /* Temperature driven */

#  /* -P0 */ Table.n_V       = 10;
#  /* -P1 */ Table.M_Gamma   = 0.05;     /* Temperature driven */
