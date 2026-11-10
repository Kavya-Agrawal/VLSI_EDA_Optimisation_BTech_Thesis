// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.03507426;
  double density_weight = 0.23281024;
  double prefix_weight = 0.33537986;
  double neighborhood_weight = 0.33344411;
  double late_weight = 0.28311152;
  double critical_weight = 0.02360625;
  unsigned budget = 8;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
