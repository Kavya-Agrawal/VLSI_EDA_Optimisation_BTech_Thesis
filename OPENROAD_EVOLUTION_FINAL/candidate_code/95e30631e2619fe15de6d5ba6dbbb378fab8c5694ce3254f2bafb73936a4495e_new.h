// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.46920330;
  double density_weight = 0.12318938;
  double prefix_weight = 0.28533093;
  double neighborhood_weight = 0.15005009;
  double late_weight = 0.02828568;
  double critical_weight = 0.45928105;
  unsigned budget = 26;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
