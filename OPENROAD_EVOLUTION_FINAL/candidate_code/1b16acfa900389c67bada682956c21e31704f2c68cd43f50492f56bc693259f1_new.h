// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.15931528;
  double density_weight = 0.46966167;
  double prefix_weight = 0.43326349;
  double neighborhood_weight = 0.02048680;
  double late_weight = 0.11179897;
  double critical_weight = 0.13731691;
  unsigned budget = 4;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
