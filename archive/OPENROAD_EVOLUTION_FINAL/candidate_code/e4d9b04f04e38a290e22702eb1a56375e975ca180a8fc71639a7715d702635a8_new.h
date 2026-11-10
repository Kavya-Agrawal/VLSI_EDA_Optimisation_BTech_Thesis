// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.79136643;
  double density_weight = 0.41810847;
  double prefix_weight = 0.47905238;
  double neighborhood_weight = 0.28778482;
  double late_weight = 0.08408931;
  double critical_weight = 0.17433568;
  unsigned budget = 9;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
