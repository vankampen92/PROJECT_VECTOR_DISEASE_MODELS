# iterate the program with different input conditions
for ((i = 1; i < $1; i+=1)) 
do

rm Parameter_Trend.dat
../ODE_RESTRICTED_JACOBIAN_NO_CASES-LXVnW_RANDOM_INITIAL_CONDITION -G8 1 -G9 4 -G11 5 -G5 0 -G6 0.0 -G7 1.0 -S0 19 -n 2 -v0 3 -v1 5 -v2 30 -G0 1 -G1 2 -G2 1 -G3 0.0 -G4 $2 -G5 1 -G6 0.0 -G7 1.0 -t0 2000 -t1 0.0 -t2 $2.0 \
 -H1 5.4E-4 -H2 5.4E-5 -H3 6.7E-4 -H4 6.3E-3 -H5 1 -H6 0.05 -H7 0.1  -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.1 -M0 0.3 -M1 0.1 -M2 0.2 -M3 0.04 -L2 3.0E4 -P0 1 -P1 0.05 \
 -TP 12 -TY -1

echo "Repetition  "$i

done
