// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.17444518;
  double density_weight = 0.48134224;
  double prefix_weight = 0.38520136;
  double neighborhood_weight = 0.39417991;
  double late_weight = 0.04290360;
  double critical_weight = 0.17883183;
  unsigned budget = 17;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
