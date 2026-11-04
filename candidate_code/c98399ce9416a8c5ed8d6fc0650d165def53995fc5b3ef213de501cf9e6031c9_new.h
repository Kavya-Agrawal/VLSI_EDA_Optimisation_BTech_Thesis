// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.16820227;
  double density_weight = 0.27529587;
  double prefix_weight = 0.09061721;
  double neighborhood_weight = 0.29148354;
  double late_weight = 0.12082848;
  double critical_weight = 0.32172967;
  unsigned budget = 4;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
