// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.20503277;
  double density_weight = 0.04966105;
  double prefix_weight = 0.21099028;
  double neighborhood_weight = 0.01379108;
  double late_weight = 0.18607507;
  double critical_weight = 0.49933826;
  unsigned budget = 12;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
