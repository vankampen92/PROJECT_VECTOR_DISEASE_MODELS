# 0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M0 0.3 -M1 0.5 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05
#  PGPLOT_ENVOPT=I      ! Invert the tick marks
#  PGPLOT_ENVOPT=IV     ! Invert tick marks and label y Vertically
#  PGPLOT_ENVOPT=P
# -H7 0.0
### ../CASES_1 -S0 19 -n 1 -v0 3 -G0 1 -G1 1 
### ../CASES_1 -L2 1.0E5 -M2 0.01 -H5 5 -P0 10 -S0 19 -n 1 -v0 3 -G0 1 -G1 1 
### ../CASES_1_Hu_4p -L2 1.0E5 -M2 0.01 -H6 0.05 -H5 5 -C3 0.1 -P0 5 -P1 0.05 -S0 4 -n 1 -v0 3 -G0 2 -G1 2 
### ../CASES_1_Ca_4p -L2 1.0E5 -M2 0.01 -H6 0.05 -H5 5 -C3 0.1 -P0 5 -P1 0.05 -S0 4 -n 1 -v0 3 -G0 2 -G1 2 
### ../CASES_1_Mo_4p -L2 1.0E5 -M2 0.01 -H6 0.05 -H5 5 -C3 0.1 -P0 5 -P1 0.05 -S0 4 -n 1 -v0 3 -G0 2 -G1 2 
### ../CASES_1_Pa_4p -L2 1.0E5 -M2 0.01 -H6 0.05 -H5 5 -C3 0.1 -P0 5 -P1 0.05 -S0 4 -n 1 -v0 3 -G0 2 -G1 2

### Solution A:
 ../SUPERINFECTION_CASES_1_PR_19p -H2 1.4E-4 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.00001  -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M1 0.5 -M2 0.2 -M3 0.04 -L2 3.0E4   -P0 1 -P1 0.05 \
 -S0 19 -n 2 -v0 3 -G0 1 -G1 2 -G13 1 -G14 "\(2748)" 
# ../NON_SUPERINFECTION_CASES_1_PR_19p -H2 1.4E-4 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.00001  -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M1 0.5 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05 \
# -S0 19 -n 2 -v0 3 -G0 1 -G1 2 -G13 1 -G14 "\(2748)" 
###
### SOLUTION A:
# -                 -H2 1.4E-4 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.00001  -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M0 0.3 -M1 0.5 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05
### SOLUTION B:
# -                 -H2 1.4E-4 -H3 3.0E-3 -H4 9.0E-3 -H5 5 -H6 0.05 -H7 0.000001  -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.2  -M0 0.3 -M1 0.8 -M2 0.2 -M3 0.06 -L2 4.0E4  -P0 10 -P1 0.083
#
# ../$1 \
# -H2 1.4E-4 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.00001  -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M0 0.3 -M1 0.5 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05 \
# -S0 2 -n 2 -v0 3 -G0 1 -G1 1 -G13 1 -G14 "Parameter\(2748)space\(2748)exploration:\(2748)dynamical\(2748)regims"
#
# -H2 1.4E-4 -H3 6.7E-4 -H4 1.0E-2 -H5 1 -H6 0.05 -H7 0.0 -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M0 0.35 -M1 0.1 -M2 0.05 -M3 0.05 -L2 3.0E4 -P0 1 -P1 0.05 \
#
# -H2 1.4E-4 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.0  -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M0 0.3 -M1 0.5 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05 \
# -S0 2 -n 2 -v0 3 -G0 1 -G1 1 -G13 1 -G14 "\(2748)" 
# -S0 19 -n 2 -v0 3 -G0 1 -G1 2
### -S0 [Dim Parameter Space] This should the dimension of the subparameter space defined by index.Definition(...) index.Definitions_PR19p.c 
### -n [Output variables, in this case, number of subplots] Notice that we need the condition n = G0 x G1 for normal execution. 

### ../CASES_1_Hu_2p -H7 0.00001 -L2 3.0E4 -M1 0.5 -M2 0.1 -M3 0.06 -H4 3.0E-3 -H6 0.05 -H5 1 -P0 1 -P1 0.05 -S0 19 -n 2 -v0 3 -G0 1 -G1 1\
### -G13 1  -G14 "Parameter\(2748)space\(2748)exploration:\(2748)dynamical\(2748)regims" -G15 "Biting\(2748)rate" -G16 "r\d\fs0\u"

### No title:
### -G14 "\(2748)" -G15 "Biting\(2748)rate" -G16 "r\d\fs0\u"

  
 -H2 1.4E-4 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.00001  -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1  -M0 0.3 -M1 0.5 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05 \
 -S0 4 -n 4 -v0 3 -G0 2 -G1 2 -G13 1 -G14 "Parameter\(2748)space\(2748)exploration:\(2748)dynamical\(2748)regims"

