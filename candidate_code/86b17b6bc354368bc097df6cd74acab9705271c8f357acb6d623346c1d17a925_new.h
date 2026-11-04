// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.44277306;
  double density_weight = 0.48178395;
  double prefix_weight = 0.44537959;
  double neighborhood_weight = 0.28147290;
  double late_weight = 0.04476649;
  double critical_weight = 0.29924552;
  unsigned budget = 5;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
