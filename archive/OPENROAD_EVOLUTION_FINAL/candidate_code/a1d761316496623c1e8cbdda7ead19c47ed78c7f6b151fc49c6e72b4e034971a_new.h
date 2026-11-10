// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.14650173;
  double density_weight = 0.46826924;
  double prefix_weight = 0.11698534;
  double neighborhood_weight = 0.29972859;
  double late_weight = 0.20252793;
  double critical_weight = 0.32496529;
  unsigned budget = 23;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
