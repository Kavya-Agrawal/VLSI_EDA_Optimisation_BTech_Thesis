// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.73479861;
  double density_weight = 0.15257481;
  double prefix_weight = 0.36788301;
  double neighborhood_weight = 0.07122830;
  double late_weight = 0.29322614;
  double critical_weight = 0.01853448;
  unsigned budget = 13;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
