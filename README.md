# README #

This project runs on linux machines out of the box. To run in other platforms makefiles should be modified accordingly. 
The follwing dependencies are required:

## GNU Scientific Library (GSL)
This is a numerical library for C and C++ programmers. It is free software under the GNU General Public License.
## CPGPLOT Graphix Library. 
This is a set of functions written in C relying on cpgplot primitives from pgplot, and plplot. You can git clone the CPGPLOT library from my repository upon request (dalonso@ceab.csic.es). the CPGPLOT Graphix library, in turns, depends on: 
### [pgplot](/http://www.astro.caltech.edu/~tjp/pgplot/)
### [plplot](http://plplot.sourceforge.net/)

### What is this repository for? ###

* This repository sets up a number of coupled mosquito-human ODE models of increasing complexity to study vector-transmitted diseases such as malaria. One of these models was first published in Alonso, D., Bouma, M. J., & Pascual, M. (2011). [Epidemic malaria and warmer temperatures in recent decades in an East African highland](https://doi.org/10.1098/rspb.2010.2020). Proceedings. Biological Sciences / The Royal Society, 278(1712), 1661-1669. Different model explorations allow for the study of the impact of model parameter on model dynamic regimes.  
* Version: 0.0.0.999
* [Learn Markdown](https://bitbucket.org/tutorials/markdowndemo)

### How do I get set up? ###

First you should install the libraries to meet the dependencies mentioned above. Look for GSL, pgplot and libplplot12 in your usual package handler.
Notice that the linking command from most makefiles contains, at least, the following libraries:

* -lgsl -lgslcblas 
* -lX11 -lpng -lplplotd -lpgplot -lcpgplot 
* -lda_cpgplot_XY_GRID_FILE -lda_cpgplot_BASIC

The first two ones are basic GSL libraries. The following 5 are required to use primitive plotting functions from the graphic libraries cpplot and plplot. The final two are mandatory when using higher-level plotting functions from the CPGPLOT Graphix library. All of them are usually required to produce a graphical output. However, the control variable (see 
any makefile) 'CPG" can also be set up to 'NON_CPG_REPRESENTATION' and, then, through conditional compilation, the same program is built
to just run the numerical computations. In all cases, the output may be saved in files. 

When you git clone the repository on your machine, you should do it from your home direcotry. Then the directory 'vtd_human-mosquito_models' will be expanded on ~/vtd_human-mosquito_models, as usual. Then, do:

~$ ln -s vtd_human-mosquito_models VECTOR_DISEASE_MODELS. 

If graphic libraries have been correctly installed, this symbolic link should be enough to make all makefiles work out of the box.  

* Summary of set up:
	+ #### 1. Install GSL library
	+ #### 2. Install plplot library
	+ #### 3. Install pgplot library
	+ #### 4. Install CPGPLOT Graphix library
	+ #### 5. git clone https://p252205@bitbucket.org/p252205/project_std_aids_models.git
	+ #### 6. ln -s vtd_human-mosquito_models VECTOR_DISEASE_MODELS
	+ #### 7. Tests: 
	In order to test if pgplot, plplot and CPGPLOT are correctly installed in your machine, you can expand the tar file PROJECT_CPGPLOT_EXAMPLES.tar, which is in the project root directory on your home directory. Then you will get the directory ~/PROJECT_CPGPLOT_EXAMPLES. In that directory, there is a simple example of how to use the CPGPLOT library. You build it by typing:
		
		+ ~/PROJECT_CPGPLOT_EXAMPLES/make
		
		and you will get the exectutable file PLOT. You may run the example with some command arguments (see main.c). You should get a graph with four different subplots. You may also type:
		
		+ ~/PROJECT_CPGPLOT_EXAMPLES/PLOT -h
		
		and see other available command line arguments. You may also type: 
		
		+ ~/PROJECT_CPGPLOT_EXAMPLES/PLOT -G29 ?
		
	and see the different avaiable graphic formats in which plots can be saved. Notice that sometimes the value for these input arguments is overriden by the internal program code. When this happens, it is for a good reason. Please check the code to understand why and make moodgodfications at your own risk. Be creative.   
	
	+ #### 8. Examples:
	See, for instance, ./MODEL_CALCULATIONS//MODEL_CALCULATIONS/INPUT_OUTPUT_CORRELATION/main_2D_SCAN.c and follow the directions to compile and run the code: 
		
		+ ~$ make TYPE_of_MAIN=_2D_SCAN CPG=CPGPLOT_REPRESENTATION 
		
		+ ~$ ./CASES_1-LXVnW__2D_SCAN -h  (for help on input arguments)
		
		+ ~$ ./CASES_1-LXVnW__2D_SCAN -G5 0 -G6 0.0 -G7 1.0 -S0 19 -S3 200 -S4 25 -n 2 -v0 30 -v1 3 -G0 1 -G1 2 -t0 1441 -t1 0.0 -t2 10800    -H2 1.4E-4 -H3 3.0E-3 -H4 9.0E-3 -H5 1 -H6 0.05 -H7 0.00001   -C0 0.2 -C1 0.2 -C2 0.01 -C3 0.2    -M0 0.3 -M1 0.8 -M2 0.2 -M3 0.06 -L2 4.0E4   -P0 1 -P1 0.083 -TY 0 -TP 51 -t4 4 -Xn 2 -L5 0.3

### Contribution guidelines ###

* Writing tests
* Code review
* Other guidelines

### Who do I talk to? ###

* Repo owner or admin
Drop an email to David Alonso (<dalonso@ceab.csic.es>) or Ruby An (<rubyan@uchicago.edu>)
* Other community or team contact