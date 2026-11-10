// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.55584873;
  double density_weight = 0.33622268;
  double prefix_weight = 0.47479366;
  double neighborhood_weight = 0.00061273;
  double late_weight = 0.15680801;
  double critical_weight = 0.41001153;
  unsigned budget = 17;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
