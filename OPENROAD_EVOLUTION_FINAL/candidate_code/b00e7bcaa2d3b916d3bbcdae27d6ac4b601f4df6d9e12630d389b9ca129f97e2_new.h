// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.34448534;
  double density_weight = 0.11313789;
  double prefix_weight = 0.37832812;
  double neighborhood_weight = 0.07745643;
  double late_weight = 0.13689942;
  double critical_weight = 0.48570108;
  unsigned budget = 9;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
