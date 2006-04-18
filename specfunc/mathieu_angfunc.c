/* specfunc/mathieu_angfunc.c
 * 
 * Copyright (C) 2002 Lowell Johnson
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

/* Author:  L. Johnson */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_sf_mathieu.h>

#include "mathieu.h"


int gsl_sf_mathieu_c(int order, double qq, double zz, gsl_sf_result *result)
{
  int even_odd, ii, status;
  double coeff[NUM_MATHIEU_COEFF], aa, norm, fn;


  norm = 0.0;
  even_odd = 0;
  if (order % 2 != 0)
      even_odd = 1;
  
  if (qq < 0.0)
  {
      GSL_ERROR("Negative q not allowed", GSL_EINVAL);
  }

  /* Handle the trivial case where q = 0. */
  if (qq == 0.0)
  {
      norm = 1.0;
      if (order == 0)
          norm = sqrt(2.0);

      fn = cos(order*zz)/norm;
      
      result->val = fn;
      result->err = GSL_DBL_EPSILON*fabs(fn);
      
      return GSL_SUCCESS;
  }
  
  /* Compute the characteristic value. */
  status = gsl_sf_mathieu_c_charv(order, qq, &aa);
  if (status != GSL_SUCCESS)
  {
      return status;
  }
  
  /* Compute the series coefficients. */
  status = gsl_sf_mathieu_c_coeff(order, qq, aa, coeff);
  if (status != GSL_SUCCESS)
  {
      return status;
  }
  
  if (even_odd == 0)
  {
      fn = 0.0;
      norm = coeff[0]*coeff[0];
      for (ii=0; ii<NUM_MATHIEU_COEFF; ii++)
      {
          fn += coeff[ii]*cos(2.0*ii*zz);
          norm += coeff[ii]*coeff[ii];
      }
  }
  else
  {
      fn = 0.0;
      for (ii=0; ii<NUM_MATHIEU_COEFF; ii++)
      {
          fn += coeff[ii]*cos((2.0*ii + 1.0)*zz);
          norm += coeff[ii]*coeff[ii];
      }
  }
  
  norm = sqrt(norm);
  fn /= norm;

  result->val = fn;
  result->err = GSL_DBL_EPSILON*fabs(fn);
  
  return GSL_SUCCESS;
}


int gsl_sf_mathieu_s(int order, double qq, double zz,gsl_sf_result *result)
{
  int even_odd, ii, status;
  double coeff[NUM_MATHIEU_COEFF], aa, norm, fn;


  norm = 0.0;
  even_odd = 0;
  if (order % 2 != 0)
      even_odd = 1;
  
  if (qq < 0.0)
  {
      GSL_ERROR("Negative q not allowed", GSL_EINVAL);
  }

  /* Handle the trivial case where q = 0. */
  if (qq == 0.0)
  {
      norm = 1.0;
      fn = sin(order*zz);
      
      result->val = fn;
      result->err = GSL_DBL_EPSILON*fabs(fn);
      
      return GSL_SUCCESS;
  }
  
  /* Compute the characteristic value. */
  status = gsl_sf_mathieu_s_charv(order, qq, &aa);
  if (status != GSL_SUCCESS)
  {
      return status;
  }
  
  /* Compute the series coefficients. */
  status = gsl_sf_mathieu_s_coeff(order, qq, aa, coeff);
  if (status != GSL_SUCCESS)
  {
      return status;
  }
  
  if (even_odd == 0)
  {
      fn = 0.0;
      for (ii=0; ii<NUM_MATHIEU_COEFF; ii++)
      {
          norm += coeff[ii]*coeff[ii];
          fn += coeff[ii]*sin(2.0*(ii + 1)*zz);
      }
  }
  else
  {
      fn = 0.0;
      for (ii=0; ii<NUM_MATHIEU_COEFF; ii++)
      {
          norm += coeff[ii]*coeff[ii];
          fn += coeff[ii]*sin((2.0*ii + 1)*zz);
      }
  }
  norm = sqrt(norm);
  fn /= norm;

  result->val = fn;
  result->err = GSL_DBL_EPSILON*fabs(fn);
  
  return GSL_SUCCESS;
}


int gsl_sf_mathieu_c_array(int nmin, int nmax, double qq, double zz,
                           gsl_sf_mathieu_workspace *work,
                           double result_array[])
{
  int even_odd, order, ii, jj, status;
  double coeff[NUM_MATHIEU_COEFF], *aa = work->char_value, norm;
  

  /* Initialize the result array to zeroes. */
  for (ii=0; ii<nmax-nmin+1; ii++)
      result_array[ii] = 0.0;
  
  /* Ensure that the workspace is large enough to accomodate. */
  if (work->size < (unsigned int)nmax)
  {
      GSL_ERROR("Work space not large enough", GSL_EINVAL);
  }
  
  if (qq < 0.0)
  {
      GSL_ERROR("Negative q not allowed", GSL_EINVAL);
  }
  if (nmin < 0 || nmax < nmin)
  {
      GSL_ERROR("domain error", GSL_EDOM);
  }

  /* Compute all of the eigenvalues up to nmax. */
  gsl_sf_mathieu_c_charv_array(qq, work);

  for (ii=0, order=nmin; order<=nmax; ii++, order++)
  {
      norm = 0.0;
      even_odd = 0;
      if (order % 2 != 0)
          even_odd = 1;
  
      /* Handle the trivial case where q = 0. */
      if (qq == 0.0)
      {
          norm = 1.0;
          if (order == 0)
              norm = sqrt(2.0);

          result_array[ii] = cos(order*zz)/norm;

          continue;
      }
  
      /* Compute the series coefficients. */
      status = gsl_sf_mathieu_c_coeff(order, qq, aa[order], coeff);
      if (status != GSL_SUCCESS)
          return status;
  
      if (even_odd == 0)
      {
          norm = coeff[0]*coeff[0];
          for (jj=0; jj<NUM_MATHIEU_COEFF; jj++)
          {
              result_array[ii] += coeff[jj]*cos(2.0*jj*zz);
              norm += coeff[jj]*coeff[jj];
          }
      }
      else
      {
          for (jj=0; jj<NUM_MATHIEU_COEFF; jj++)
          {
              result_array[ii] += coeff[jj]*cos((2.0*jj + 1.0)*zz);
              norm += coeff[jj]*coeff[jj];
          }
      }
  
      norm = sqrt(norm);
      result_array[ii] /= norm;
  }

  return GSL_SUCCESS;
}


int gsl_sf_mathieu_s_array(int nmin, int nmax, double qq, double zz,
                           gsl_sf_mathieu_workspace *work,
                           double result_array[])
{
  int even_odd, order, ii, jj, status;
  double coeff[NUM_MATHIEU_COEFF], *aa = work->char_value, norm;
  

  /* Initialize the result array to zeroes. */
  for (ii=0; ii<nmax-nmin+1; ii++)
      result_array[ii] = 0.0;
  
  /* Ensure that the workspace is large enough to accomodate. */
  if (work->size < (unsigned int)nmax)
  {
      GSL_ERROR("Work space not large enough", GSL_EINVAL);
  }
  
  if (qq < 0.0)
  {
      GSL_ERROR("Negative q not allowed", GSL_EINVAL);
  }
  if (nmin < 0 || nmax < nmin)
  {
      GSL_ERROR("domain error", GSL_EDOM);
  }

  /* Compute all of the eigenvalues up to nmax. */
  gsl_sf_mathieu_s_charv_array(qq, work);

  for (ii=0, order=nmin; order<=nmax; ii++, order++)
  {
      norm = 0.0;
      even_odd = 0;
      if (order % 2 != 0)
          even_odd = 1;
  
      /* Handle the trivial case where q = 0. */
      if (qq == 0.0)
      {
          norm = 1.0;
          result_array[ii] = sin(order*zz);

          continue;
      }
  
      /* Compute the series coefficients. */
      status = gsl_sf_mathieu_s_coeff(order, qq, aa[order], coeff);
      if (status != GSL_SUCCESS)
      {
          return status;
      }
  
      if (even_odd == 0)
      {
          for (jj=0; jj<NUM_MATHIEU_COEFF; jj++)
          {
              result_array[ii] += coeff[jj]*sin(2.0*(jj + 1)*zz);
              norm += coeff[jj]*coeff[jj];
          }
      }
      else
      {
          for (jj=0; jj<NUM_MATHIEU_COEFF; jj++)
          {
              result_array[ii] += coeff[jj]*sin((2.0*jj + 1.0)*zz);
              norm += coeff[jj]*coeff[jj];
          }
      }
  
      norm = sqrt(norm);
      result_array[ii] /= norm;
  }

  return GSL_SUCCESS;
}
