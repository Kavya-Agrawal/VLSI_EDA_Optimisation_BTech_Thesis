// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.74241303;
  double density_weight = 0.36101776;
  double prefix_weight = 0.01099247;
  double neighborhood_weight = 0.29591415;
  double late_weight = 0.06589865;
  double critical_weight = 0.23410965;
  unsigned budget = 28;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
