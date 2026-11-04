// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.94396308;
  double density_weight = 0.36430686;
  double prefix_weight = 0.13650154;
  double neighborhood_weight = 0.33173615;
  double late_weight = 0.27004607;
  double critical_weight = 0.45212687;
  unsigned budget = 26;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
