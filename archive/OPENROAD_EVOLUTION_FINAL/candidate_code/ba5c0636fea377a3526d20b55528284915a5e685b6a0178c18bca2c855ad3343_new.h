// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.80195015;
  double density_weight = 0.09869066;
  double prefix_weight = 0.19238356;
  double neighborhood_weight = 0.22536744;
  double late_weight = 0.13162920;
  double critical_weight = 0.10496107;
  unsigned budget = 30;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
