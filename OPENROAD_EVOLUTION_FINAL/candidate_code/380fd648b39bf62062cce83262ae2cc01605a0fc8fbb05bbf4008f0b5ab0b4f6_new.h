// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.95129161;
  double density_weight = 0.56069733;
  double prefix_weight = 0.38049038;
  double neighborhood_weight = 0.25456402;
  double late_weight = 0.28841202;
  double critical_weight = 0.26757147;
  unsigned budget = 37;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
