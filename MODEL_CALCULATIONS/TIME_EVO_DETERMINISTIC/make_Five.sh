make clean
make JACOBIAN=ODE_RESTRICTED_JACOBIAN I=INITIAL_CONDITION
make clean
make JACOBIAN=ODE I=INITIAL_CONDITION
make clean
make JACOBIAN=ODE_RESTRICTED_JACOBIAN I=NON_INITIAL_CONDITION
make clean
make JACOBIAN=ODE I=NON_INITIAL_CONDITION
make clean
make JACOBIAN=ODE_RESTRICTED_JACOBIAN I=RANDOM_INITIAL_CONDITION
make clean
