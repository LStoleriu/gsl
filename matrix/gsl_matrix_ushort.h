/* matrix/gsl_matrix_ushort.h
 * 
 * Copyright (C) 1996, 1997, 1998, 1999, 2000 Gerard Jungman, Brian Gough
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

#ifndef __GSL_MATRIX_USHORT_H__
#define __GSL_MATRIX_USHORT_H__

#include <stdlib.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_vector_ushort.h>

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

typedef struct gsl_matrix_ushort_struct gsl_matrix_ushort;

struct gsl_matrix_ushort_struct
{
  size_t size1;
  size_t size2;
  size_t tda;
  unsigned short * data;
  gsl_block_ushort * block;
  int owner;
} ;

gsl_matrix_ushort * 
gsl_matrix_ushort_alloc (const size_t n1, const size_t n2);

gsl_matrix_ushort * 
gsl_matrix_ushort_calloc (const size_t n1, const size_t n2);

gsl_matrix_ushort * 
gsl_matrix_ushort_alloc_from_block (gsl_block_ushort * b, 
                                   const size_t offset, 
                                   const size_t n1, 
                                   const size_t n2, 
                                   const size_t d2);

gsl_matrix_ushort * 
gsl_matrix_ushort_alloc_from_matrix (gsl_matrix_ushort * m,
                                    const size_t k1, 
                                    const size_t k2,
                                    const size_t n1, 
                                    const size_t n2);

gsl_vector_ushort * 
gsl_vector_ushort_alloc_row_from_matrix (gsl_matrix_ushort * m,
                                        const size_t i);

gsl_vector_ushort * 
gsl_vector_ushort_alloc_col_from_matrix (gsl_matrix_ushort * m,
                                        const size_t j);

void gsl_matrix_ushort_free (gsl_matrix_ushort * m);

int gsl_matrix_ushort_view_from_matrix (gsl_matrix_ushort * m, 
                                       gsl_matrix_ushort * mm,
                                       const size_t k1,
                                       const size_t k2,
                                       const size_t n1, 
                                       const size_t n2);

int gsl_matrix_ushort_view_from_vector (gsl_matrix_ushort * m, 
                                       gsl_vector_ushort * v,
                                       const size_t offset,
                                       const size_t n1, 
                                       const size_t n2);


int gsl_matrix_ushort_view_from_array (gsl_matrix_ushort * m, 
                                      unsigned short * base,
                                      const size_t offset,
                                      const size_t n1, 
                                      const size_t n2);

gsl_matrix_ushort gsl_matrix_ushort_view (unsigned short * m, 
                                        const size_t n1, 
                                        const size_t n2);

int gsl_vector_ushort_view_row_from_matrix (gsl_vector_ushort * v, gsl_matrix_ushort * m, const size_t i);
int gsl_vector_ushort_view_col_from_matrix (gsl_vector_ushort * v, gsl_matrix_ushort * m, const size_t j);

void gsl_matrix_ushort_set_zero (gsl_matrix_ushort * m);
void gsl_matrix_ushort_set_identity (gsl_matrix_ushort * m);
void gsl_matrix_ushort_set_all (gsl_matrix_ushort * m, unsigned short x);

unsigned short * gsl_matrix_ushort_ptr(const gsl_matrix_ushort * m, const size_t i, const size_t j);
unsigned short   gsl_matrix_ushort_get(const gsl_matrix_ushort * m, const size_t i, const size_t j);
void    gsl_matrix_ushort_set(gsl_matrix_ushort * m, const size_t i, const size_t j, const unsigned short x);

int gsl_matrix_ushort_fread (FILE * stream, gsl_matrix_ushort * m) ;
int gsl_matrix_ushort_fwrite (FILE * stream, const gsl_matrix_ushort * m) ;
int gsl_matrix_ushort_fscanf (FILE * stream, gsl_matrix_ushort * m);
int gsl_matrix_ushort_fprintf (FILE * stream, const gsl_matrix_ushort * m, const char * format);
 
int gsl_matrix_ushort_memcpy(gsl_matrix_ushort * dest, const gsl_matrix_ushort * src);
int gsl_matrix_ushort_swap(gsl_matrix_ushort * m1, const gsl_matrix_ushort * m2);

int gsl_matrix_ushort_swap_rows(gsl_matrix_ushort * m, const size_t i, const size_t j);
int gsl_matrix_ushort_swap_columns(gsl_matrix_ushort * m, const size_t i, const size_t j);
int gsl_matrix_ushort_swap_rowcol(gsl_matrix_ushort * m, const size_t i, const size_t j);
int gsl_matrix_ushort_transpose (gsl_matrix_ushort * m);
int gsl_matrix_ushort_transpose_memcpy (gsl_matrix_ushort * dest, const gsl_matrix_ushort * src);


gsl_matrix_ushort gsl_matrix_ushort_submatrix (gsl_matrix_ushort * m, size_t i, size_t j, size_t n1, size_t n2);
gsl_vector_ushort gsl_matrix_ushort_row (gsl_matrix_ushort * m, size_t i);
gsl_vector_ushort gsl_matrix_ushort_column (gsl_matrix_ushort * m, size_t j);
gsl_vector_ushort gsl_matrix_ushort_diagonal (gsl_matrix_ushort * m);

const gsl_matrix_ushort gsl_matrix_ushort_const_submatrix (const gsl_matrix_ushort * m, size_t i, size_t j, size_t n1, size_t n2);
const gsl_vector_ushort gsl_matrix_ushort_const_row (const gsl_matrix_ushort * m, size_t i);
const gsl_vector_ushort gsl_matrix_ushort_const_column (const gsl_matrix_ushort * m, size_t j);
const gsl_vector_ushort gsl_matrix_ushort_const_diagonal (const gsl_matrix_ushort * m);

unsigned short gsl_matrix_ushort_max (const gsl_matrix_ushort * m);
unsigned short gsl_matrix_ushort_min (const gsl_matrix_ushort * m);
void gsl_matrix_ushort_minmax (const gsl_matrix_ushort * m, unsigned short * min_out, unsigned short * max_out);

void gsl_matrix_ushort_max_index (const gsl_matrix_ushort * m, size_t * imax, size_t *jmax);
void gsl_matrix_ushort_min_index (const gsl_matrix_ushort * m, size_t * imin, size_t *jmin);
void gsl_matrix_ushort_minmax_index (const gsl_matrix_ushort * m, size_t * imin, size_t * jmin, size_t * imax, size_t * jmax);

int gsl_matrix_ushort_isnull (const gsl_matrix_ushort * m);

int gsl_matrix_ushort_add (gsl_matrix_ushort * a, const gsl_matrix_ushort * b);
int gsl_matrix_ushort_sub (gsl_matrix_ushort * a, const gsl_matrix_ushort * b);
int gsl_matrix_ushort_mul_elements (gsl_matrix_ushort * a, const gsl_matrix_ushort * b);
int gsl_matrix_ushort_div_elements (gsl_matrix_ushort * a, const gsl_matrix_ushort * b);
int gsl_matrix_ushort_scale (gsl_matrix_ushort * a, const double x);
int gsl_matrix_ushort_add_constant (gsl_matrix_ushort * a, const double x);

/***********************************************************************/
/* The functions below are obsolete                                    */
/***********************************************************************/
int gsl_matrix_ushort_get_row(gsl_vector_ushort * v, const gsl_matrix_ushort * m, const size_t i);
int gsl_matrix_ushort_get_col(gsl_vector_ushort * v, const gsl_matrix_ushort * m, const size_t j);
int gsl_matrix_ushort_set_row(gsl_matrix_ushort * m, const size_t i, const gsl_vector_ushort * v);
int gsl_matrix_ushort_set_col(gsl_matrix_ushort * m, const size_t j, const gsl_vector_ushort * v);

extern int gsl_check_range ;

/* inline functions if you are using GCC */

#ifdef HAVE_INLINE
extern inline 
unsigned short
gsl_matrix_ushort_get(const gsl_matrix_ushort * m, const size_t i, const size_t j)
{
#ifndef GSL_RANGE_CHECK_OFF
  if (i >= m->size1)
    {
      GSL_ERROR_VAL("first index out of range", GSL_EINVAL, 0) ;
    }
  else if (j >= m->size2)
    {
      GSL_ERROR_VAL("second index out of range", GSL_EINVAL, 0) ;
    }
#endif
  return m->data[i * m->tda + j] ;
} 

extern inline 
void
gsl_matrix_ushort_set(gsl_matrix_ushort * m, const size_t i, const size_t j, const unsigned short x)
{
#ifndef GSL_RANGE_CHECK_OFF
  if (i >= m->size1)
    {
      GSL_ERROR_VOID("first index out of range", GSL_EINVAL) ;
    }
  else if (j >= m->size2)
    {
      GSL_ERROR_VOID("second index out of range", GSL_EINVAL) ;
    }
#endif
  m->data[i * m->tda + j] = x ;
}
#endif

__END_DECLS

#endif /* __GSL_MATRIX_USHORT_H__ */
