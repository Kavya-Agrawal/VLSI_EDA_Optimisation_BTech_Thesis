// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.14276054;
  double density_weight = 0.54523233;
  double prefix_weight = 0.21133792;
  double neighborhood_weight = 0.14242988;
  double late_weight = 0.08967294;
  double critical_weight = 0.43716721;
  unsigned budget = 20;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
