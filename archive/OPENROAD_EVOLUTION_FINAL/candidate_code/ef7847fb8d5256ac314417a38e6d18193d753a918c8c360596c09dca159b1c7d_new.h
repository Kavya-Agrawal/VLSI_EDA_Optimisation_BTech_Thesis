// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.16568086;
  double density_weight = 0.50595008;
  double prefix_weight = 0.12242683;
  double neighborhood_weight = 0.26904650;
  double late_weight = 0.03614280;
  double critical_weight = 0.18160317;
  unsigned budget = 8;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
