// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.05848920;
  double density_weight = 0.08770751;
  double prefix_weight = 0.18304906;
  double neighborhood_weight = 0.21425880;
  double late_weight = 0.04724509;
  double critical_weight = 0.35625848;
  unsigned budget = 26;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
