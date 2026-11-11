// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.55116930;
  double density_weight = 0.10998542;
  double prefix_weight = 0.45402879;
  double neighborhood_weight = 0.31307288;
  double late_weight = 0.23862489;
  double critical_weight = 0.39494208;
  unsigned budget = 24;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
