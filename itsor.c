/** 
 * C stub code for Fortran functions generated by f2py (version:2.45.241_1926) 
 */

#ifdef  __cplusplus
extern "C" {
#endif

void __real_itsor_ (int *nn, int *ia, int *ja, double *a, double *rhs, double *u, double *wk);

void __wrap_itsor_ (int *nn, int *ia, int *ja, double *a, double *rhs, double *u, double *wk)
{
    return __real_itsor_(nn,ia,ja,a,rhs,u,wk);
}

#ifdef  __cplusplus
}
#endif
