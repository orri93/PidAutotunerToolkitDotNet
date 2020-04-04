#ifndef GOS_PID_TOOLKIT_STABILITY_H_
#define GOS_PID_TOOLKIT_STABILITY_H_

#include <memory>

#include <gos/pid/toolkit/types.h>

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/rolling_mean.hpp>
#include <boost/accumulators/statistics/rolling_variance.hpp>

namespace gos {
namespace pid {
namespace toolkit {
namespace stability {

template<typename T>
struct Parameters {
  ::gos::pid::toolkit::type::range<T> Range;
  int Size;
};

template<typename T>
struct Variables {
  typedef ::boost::accumulators::extractor<
    ::boost::accumulators::tag::rolling_mean> RollingMeanExtractor;
  RollingMeanExtractor MeanExtractor;
  typedef ::boost::accumulators::extractor<
    ::boost::accumulators::tag::rolling_variance> RollingVarianceExtractor;
  RollingVarianceExtractor VarianceExtractor;
  typedef ::boost::accumulators::accumulator_set <T,
    ::boost::accumulators::stats<::boost::accumulators::tag::rolling_variance>>
    VarianceSetType;
  typedef ::std::unique_ptr<VarianceSetType> VarianceSetPointer;
  VarianceSetPointer VarianceSet;
};

template<typename T>
struct Results {
  T Mean;
  T Variance;
};

template<typename T>
void initialize(
  const Parameters<T>& parameters,
  Variables<T>& variables) {
  variables.VarianceSet =
    ::std::make_unique<Variables<T>::VarianceSetType>(
      ::boost::accumulators::tag::rolling_window::window_size =
      parameters.Size);
}

template<typename T>
void evaluate(
  const Parameters<T>& parameters,
  Variables<T>& variables,
  Results<T>& results,
  const T& value) {
  if (variables.VarianceSet) {
    (*variables.VarianceSet)(value);
    results.Mean = variables.MeanExtractor(*variables.VarianceSet);
    results.Variance = variables.VarianceExtractor(*variables.VarianceSet);
  }
}

} // namespace stability
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
