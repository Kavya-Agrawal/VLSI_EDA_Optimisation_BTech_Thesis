// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.92674975;
  double density_weight = 0.29218219;
  double prefix_weight = 0.09378167;
  double neighborhood_weight = 0.10469512;
  double late_weight = 0.07872437;
  double critical_weight = 0.23351943;
  unsigned budget = 6;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
