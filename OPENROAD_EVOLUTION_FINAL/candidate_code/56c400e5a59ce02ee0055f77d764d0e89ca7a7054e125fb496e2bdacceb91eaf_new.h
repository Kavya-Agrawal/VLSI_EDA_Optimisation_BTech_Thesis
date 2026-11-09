// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.76477805;
  double density_weight = 0.30866889;
  double prefix_weight = 0.23543544;
  double neighborhood_weight = 0.37337729;
  double late_weight = 0.05587301;
  double critical_weight = 0.28840933;
  unsigned budget = 16;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
