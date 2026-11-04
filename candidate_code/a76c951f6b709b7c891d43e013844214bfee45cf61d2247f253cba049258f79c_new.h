// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.39489592;
  double density_weight = 0.46339115;
  double prefix_weight = 0.36998654;
  double neighborhood_weight = 0.03148811;
  double late_weight = 0.02227509;
  double critical_weight = 0.28301157;
  unsigned budget = 28;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
