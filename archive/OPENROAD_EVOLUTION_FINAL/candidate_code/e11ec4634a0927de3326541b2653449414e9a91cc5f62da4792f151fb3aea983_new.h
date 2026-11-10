// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.97442178;
  double density_weight = 0.49797156;
  double prefix_weight = 0.03012404;
  double neighborhood_weight = 0.09521676;
  double late_weight = 0.01086312;
  double critical_weight = 0.01524781;
  unsigned budget = 16;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
