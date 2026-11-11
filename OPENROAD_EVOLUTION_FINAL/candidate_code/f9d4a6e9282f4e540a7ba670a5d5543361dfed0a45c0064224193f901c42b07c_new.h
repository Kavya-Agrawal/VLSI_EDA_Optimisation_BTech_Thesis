// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.04089319;
  double density_weight = 0.12450115;
  double prefix_weight = 0.20422119;
  double neighborhood_weight = 0.07167543;
  double late_weight = 0.24738106;
  double critical_weight = 0.31037481;
  unsigned budget = 21;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
