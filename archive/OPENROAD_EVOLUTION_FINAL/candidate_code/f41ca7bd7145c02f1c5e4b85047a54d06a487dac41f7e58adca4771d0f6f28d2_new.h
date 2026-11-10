// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.09678066;
  double density_weight = 0.15208827;
  double prefix_weight = 0.04553478;
  double neighborhood_weight = 0.11848636;
  double late_weight = 0.16683891;
  double critical_weight = 0.29212926;
  unsigned budget = 18;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
