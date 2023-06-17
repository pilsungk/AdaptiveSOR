# AdaptiveSOR
The code here is an examplary implementation of adaptive SOR (successive over-relaxation) via AspectC++, as described in the uploaded manuscript. 

## Build Env. Setup
The code has been tested and built on GNU/Linux, specifically on the Ubuntu 20.04 LTS distribution.

1. gfortran
  <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`sudo apt install gfortran`

2. AspectC++ compiler
  <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; `sudo apt install aspectc++`

3. ITPACK 2C source code
You can get the ITPACK 2C source (dsrc2c.f) and test code (dtst2c.f) at https://www.netlib.org/itpack/index.html. However, these are not directly compilable by gfortran since the codes too old for modern Fortran language syntax. For instance, a few subroutines such as `perror` need to be explicitly declared as external. In addition, the `ITSOR` subroutine needs to be separated into its own translation unit in order to apply the GCC compiler's link-time wrap functionality. Hence, there are three Fortran source files here.
  <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; `dsrc2c_wo_itsor.f, itsor.f, dtst2c.f`

4. Checking the original behavior
  <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Build: `gfortran -fno-automatic *.f -o dtst2c`
  <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Run: `./dtst2c`

  <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; The ITPACK test program will generate 'result_orig.out', as uploaded here, which shows how the original ITPACK SOR algorithm operates for the test problem.

5. Adjusting the SOR parameter of ITPACK
  1. Files needed
- C wrapper for the ITSOR Fortran subroutine: itsor.c
- Aspect C++ code for adjusting the SOR parameter at ITSOR calls: ControlSystems.ah (base aspect code), SORParamControl.ah (derived aspect code for ITPACK SOR parameter adjustment). 

  2. Aspect weaving via AspectC++ compiler
- `ac++ -c itsor.c -p. -a SORParamControl.ah -o itsor_weaved.cpp`

This will generate a standard C++ source code, itsor_weaved.cpp, where the `ITSOR` calls are weaved with the parameter adjusting aspect code. 

3) Compiling each source code
- itsor_weaved.cpp: `g++ -c itsor_weaved.cpp`
- all the Fortran code (itsor.f, dtst2c.f, and dsrc2c_wo_itsor.f): `gfortran -fno-automatic -c *.f`

4) Linking the object code with link-time wrap for the ITSOR calls
- `g++ *.o -Wl,--wrap=itsor_ -o dtst2c_ac -lgfortran`

This will build a ITPACK test program, 'dtst2c_ac', where the SOR parameter, omega, is adjusted at each `ITSOR` calls. For the illustration purposes, we adjust the omega value by 0.995 at each `ITSOR` iteration in our adaptive scenario.   

5) Running the adaptive ITPACK test program
- `./dtst2c_ac`

The adapted ITPACK test program will generate 'result.out', which shows how the adaptive version of ITPACK SOR operates. 
