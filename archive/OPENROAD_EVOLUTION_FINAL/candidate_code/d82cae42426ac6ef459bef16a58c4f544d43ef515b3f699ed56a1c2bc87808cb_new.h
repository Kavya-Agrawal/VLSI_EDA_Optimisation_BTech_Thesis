// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.55875856;
  double density_weight = 0.50365964;
  double prefix_weight = 0.29132233;
  double neighborhood_weight = 0.23182620;
  double late_weight = 0.06540317;
  double critical_weight = 0.44638609;
  unsigned budget = 37;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
