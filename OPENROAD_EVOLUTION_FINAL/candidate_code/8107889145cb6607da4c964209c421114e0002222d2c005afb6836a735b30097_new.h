// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.01229418;
  double density_weight = 0.22460339;
  double prefix_weight = 0.41716225;
  double neighborhood_weight = 0.32020897;
  double late_weight = 0.22401278;
  double critical_weight = 0.45651545;
  unsigned budget = 40;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
