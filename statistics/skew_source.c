#include <math.h>


double 
FUNCTION(gsl_stats,skew) (const BASE data[], const size_t n)
{
  const double mean = FUNCTION(gsl_stats,mean)(data, n);
  const double est_sd = FUNCTION(gsl_stats,est_sd_with_mean)(data, n, mean);
  return FUNCTION(gsl_stats,skew_with_mean_and_sd)(data, n, mean, est_sd);
}
    
double 
FUNCTION(gsl_stats,skew_with_mean_and_sd) (const BASE data[], const size_t n,
					   const double mean, const double sd)
{
  /* takes a dataset and finds the skewness */

  double skew = 0;
  size_t i;

  /* find the sum of the cubed deviations, normalized by the sd. */

  /* we use a recurrence relation to stably update a running value so
     there aren't any large sums that can overflow */

  for (i = 0; i < n; i++)
    {
      const double x = (data[i] - mean) / sd;
      skew += (x * x * x - skew) / ((double)(i + 1));
    }

  return skew;
}

