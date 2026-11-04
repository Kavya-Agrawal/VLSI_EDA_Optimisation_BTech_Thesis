// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.74278839;
  double density_weight = 0.10470909;
  double prefix_weight = 0.00016786;
  double neighborhood_weight = 0.03525142;
  double late_weight = 0.16307401;
  double critical_weight = 0.40127679;
  unsigned budget = 24;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
