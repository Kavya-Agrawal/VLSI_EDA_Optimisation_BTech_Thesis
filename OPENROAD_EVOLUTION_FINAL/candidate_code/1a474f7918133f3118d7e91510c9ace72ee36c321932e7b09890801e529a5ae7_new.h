// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.58787868;
  double density_weight = 0.01539050;
  double prefix_weight = 0.11361987;
  double neighborhood_weight = 0.16449137;
  double late_weight = 0.14192646;
  double critical_weight = 0.28817202;
  unsigned budget = 14;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
