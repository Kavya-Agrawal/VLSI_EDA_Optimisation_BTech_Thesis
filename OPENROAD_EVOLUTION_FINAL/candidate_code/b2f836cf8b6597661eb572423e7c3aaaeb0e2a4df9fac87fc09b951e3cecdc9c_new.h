// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.62128219;
  double density_weight = 0.22280536;
  double prefix_weight = 0.48558615;
  double neighborhood_weight = 0.33878887;
  double late_weight = 0.03565075;
  double critical_weight = 0.22618044;
  unsigned budget = 31;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
