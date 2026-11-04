// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.82560968;
  double density_weight = 0.23514615;
  double prefix_weight = 0.12833297;
  double neighborhood_weight = 0.30719118;
  double late_weight = 0.15321296;
  double critical_weight = 0.45497786;
  unsigned budget = 32;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
