// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.91629488;
  double density_weight = 0.24370185;
  double prefix_weight = 0.00424567;
  double neighborhood_weight = 0.34756591;
  double late_weight = 0.11730987;
  double critical_weight = 0.40529425;
  unsigned budget = 21;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
