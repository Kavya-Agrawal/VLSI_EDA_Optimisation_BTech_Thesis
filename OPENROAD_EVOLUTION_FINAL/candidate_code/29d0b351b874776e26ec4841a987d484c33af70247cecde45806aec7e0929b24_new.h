// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.32819848;
  double density_weight = 0.46188470;
  double prefix_weight = 0.34838206;
  double neighborhood_weight = 0.07009433;
  double late_weight = 0.24174510;
  double critical_weight = 0.33839210;
  unsigned budget = 15;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
