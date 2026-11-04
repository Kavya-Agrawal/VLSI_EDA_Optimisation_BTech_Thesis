// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.08425153;
  double density_weight = 0.10130193;
  double prefix_weight = 0.40496775;
  double neighborhood_weight = 0.05347033;
  double late_weight = 0.04373027;
  double critical_weight = 0.40607644;
  unsigned budget = 11;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
