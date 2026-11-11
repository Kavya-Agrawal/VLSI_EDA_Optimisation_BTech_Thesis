// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.36417161;
  double density_weight = 0.14839211;
  double prefix_weight = 0.25598621;
  double neighborhood_weight = 0.20813650;
  double late_weight = 0.09844920;
  double critical_weight = 0.01958191;
  unsigned budget = 29;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
