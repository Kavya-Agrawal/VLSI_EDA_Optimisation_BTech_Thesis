// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.16837371;
  double density_weight = 0.18;
  double prefix_weight = 0.12;
  double neighborhood_weight = 0.08;
  double late_weight = 0.06;
  double critical_weight = 0.10;
  unsigned budget = 12;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
