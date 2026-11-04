// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.38466266;
  double density_weight = 0.41423018;
  double prefix_weight = 0.13519047;
  double neighborhood_weight = 0.07131035;
  double late_weight = 0.02429019;
  double critical_weight = 0.27750413;
  unsigned budget = 14;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
