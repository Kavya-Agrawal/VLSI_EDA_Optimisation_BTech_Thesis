// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.35662985;
  double density_weight = 0.07690931;
  double prefix_weight = 0.43691274;
  double neighborhood_weight = 0.07140226;
  double late_weight = 0.02092062;
  double critical_weight = 0.46798449;
  unsigned budget = 12;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
