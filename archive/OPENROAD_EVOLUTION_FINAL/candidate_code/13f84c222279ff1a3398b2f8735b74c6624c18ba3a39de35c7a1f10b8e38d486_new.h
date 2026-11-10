// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.12789200;
  double density_weight = 0.34925635;
  double prefix_weight = 0.27752196;
  double neighborhood_weight = 0.14437377;
  double late_weight = 0.25990325;
  double critical_weight = 0.15984498;
  unsigned budget = 27;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
