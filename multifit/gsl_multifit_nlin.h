/* multifit_nlin/gsl_multifit_nlin.h
 * 
 * Copyright (C) 1996, 1997, 1998, 1999, 2000 Brian Gough
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef __GSL_MULTIFIT_NLIN_H__
#define __GSL_MULTIFIT_NLIN_H__

#include <stdlib.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>

#undef __BEGIN_DECLS
#undef __END_DECLS
#ifdef __cplusplus
# define __BEGIN_DECLS extern "C" {
# define __END_DECLS }
#else
# define __BEGIN_DECLS /* empty */
# define __END_DECLS /* empty */
#endif

__BEGIN_DECLS

/* Definition of vector-valued functions with parameters based on gsl_vector */

struct gsl_multifit_nlin_function_struct
{
  int (* f) (const gsl_vector * x, void * params, gsl_vector * f);
  size_t m;   /* number of functions */
  size_t n;   /* number of independent variables */
  void * params;
};

typedef struct gsl_multifit_nlin_function_struct gsl_multifit_nlin_function ;

#define GSL_MULTIFIT_NLIN_FN_EVAL(F,x,y) (*((F)->f))(x,(F)->params,(y))

int gsl_multifit_nlin_fdjacobian (gsl_multifit_nlin_function * F,
                              const gsl_vector * x, const gsl_vector * f,
                              double epsrel, gsl_matrix * jacobian);


typedef struct
  {
    const char *name;
    size_t size;
    int (*alloc) (void *state, size_t n);
    int (*set) (void *state, gsl_multifit_nlin_function * function, gsl_vector * x, gsl_vector * f, gsl_vector * dx);
    int (*iterate) (void *state, gsl_multifit_nlin_function * function, gsl_vector * x, gsl_vector * f, gsl_vector * dx);
    void (*free) (void *state);
  }
gsl_multifit_nlin_fsolver_type;

typedef struct
  {
    const gsl_multifit_nlin_fsolver_type * type;
    gsl_multifit_nlin_function * function ;
    gsl_vector * x ;
    gsl_vector * f ;
    gsl_vector * dx ;
    void *state;
  }
gsl_multifit_nlin_fsolver;

gsl_multifit_nlin_fsolver *
gsl_multifit_nlin_fsolver_alloc (const gsl_multifit_nlin_fsolver_type * T, 
                             gsl_multifit_nlin_function * f, gsl_vector * x);
void gsl_multifit_nlin_fsolver_free (gsl_multifit_nlin_fsolver * s);

int gsl_multifit_nlin_fsolver_set (gsl_multifit_nlin_fsolver * s, 
                               gsl_multifit_nlin_function * f, gsl_vector * x);

int gsl_multifit_nlin_fsolver_iterate (gsl_multifit_nlin_fsolver * s);

const char * gsl_multifit_nlin_fsolver_name (const gsl_multifit_nlin_fsolver * s);
gsl_vector * gsl_multifit_nlin_fsolver_root (const gsl_multifit_nlin_fsolver * s);

/* Definition of vector-valued functions and gradient with parameters
   based on gsl_vector */

struct gsl_multifit_nlin_function_fdf_struct
{
  int (* f) (const gsl_vector * x, void * params, gsl_vector * f);
  int (* df) (const gsl_vector * x, void * params, gsl_matrix * df);
  int (* fdf) (const gsl_vector * x, void * params, gsl_vector * f, gsl_matrix *df);
  size_t m;   /* number of functions */
  size_t n;   /* number of independent variables */
  void * params;
};

typedef struct gsl_multifit_nlin_function_fdf_struct gsl_multifit_nlin_function_fdf ;

#define GSL_MULTIFIT_NLIN_FN_EVAL_F(F,x,y) ((*((F)->f))(x,(F)->params,(y)))
#define GSL_MULTIFIT_NLIN_FN_EVAL_DF(F,x,dy) ((*((F)->df))(x,(F)->params,(dy)))
#define GSL_MULTIFIT_NLIN_FN_EVAL_F_DF(F,x,y,dy) ((*((F)->fdf))(x,(F)->params,(y),(dy)))

typedef struct
  {
    const char *name;
    size_t size;
    int (*alloc) (void *state, size_t n);
    int (*set) (void *state, gsl_multifit_nlin_function_fdf * fdf, gsl_vector * x, gsl_vector * f, gsl_matrix * J, gsl_vector * dx);
    int (*iterate) (void *state, gsl_multifit_nlin_function_fdf * fdf, gsl_vector * x, gsl_vector * f, gsl_matrix * J, gsl_vector * dx);
    void (*free) (void *state);
  }
gsl_multifit_nlin_fdfsolver_type;

typedef struct
  {
    const gsl_multifit_nlin_fdfsolver_type * type;
    gsl_multifit_nlin_function_fdf * fdf ;
    gsl_vector * x;
    gsl_vector * f;
    gsl_matrix * J;
    gsl_vector * dx;
    void *state;
  }
gsl_multifit_nlin_fdfsolver;


gsl_multifit_nlin_fdfsolver *
gsl_multifit_nlin_fdfsolver_alloc (const gsl_multifit_nlin_fdfsolver_type * T, 
                               gsl_multifit_nlin_function_fdf * fdf,
                               gsl_vector * x);

int
gsl_multifit_nlin_fdfsolver_set (gsl_multifit_nlin_fdfsolver * s, 
                             gsl_multifit_nlin_function_fdf * fdf,
                             gsl_vector * x);

int
gsl_multifit_nlin_fdfsolver_iterate (gsl_multifit_nlin_fdfsolver * s);

void
gsl_multifit_nlin_fdfsolver_free (gsl_multifit_nlin_fdfsolver * s);

const char * gsl_multifit_nlin_fdfsolver_name (const gsl_multifit_nlin_fdfsolver * s);
gsl_vector * gsl_multifit_nlin_fdfsolver_root (const gsl_multifit_nlin_fdfsolver * s);

int gsl_multifit_nlin_test_delta (const gsl_vector * dx, const gsl_vector * x, 
                              double epsabs, double epsrel);

int gsl_multifit_nlin_test_residual (const gsl_vector * f, double epsabs);

extern const gsl_multifit_nlin_fsolver_type * gsl_multifit_nlin_fsolver_dnewton;
extern const gsl_multifit_nlin_fsolver_type * gsl_multifit_nlin_fsolver_broyden;
extern const gsl_multifit_nlin_fsolver_type * gsl_multifit_nlin_fsolver_hybrid;
extern const gsl_multifit_nlin_fsolver_type * gsl_multifit_nlin_fsolver_hybrids;

extern const gsl_multifit_nlin_fdfsolver_type * gsl_multifit_nlin_fdfsolver_newton;
extern const gsl_multifit_nlin_fdfsolver_type * gsl_multifit_nlin_fdfsolver_gnewton;
extern const gsl_multifit_nlin_fdfsolver_type * gsl_multifit_nlin_fdfsolver_hybridj;
extern const gsl_multifit_nlin_fdfsolver_type * gsl_multifit_nlin_fdfsolver_hybridsj;


__END_DECLS

#endif /* __GSL_MULTIFIT_NLIN_H__ */
