// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.14086022;
  double density_weight = 0.28000791;
  double prefix_weight = 0.23628815;
  double neighborhood_weight = 0.02535504;
  double late_weight = 0.27202278;
  double critical_weight = 0.30554568;
  unsigned budget = 25;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
