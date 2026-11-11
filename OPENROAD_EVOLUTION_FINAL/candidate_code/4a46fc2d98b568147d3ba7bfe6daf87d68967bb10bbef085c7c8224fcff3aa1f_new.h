// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.27789837;
  double density_weight = 0.26901121;
  double prefix_weight = 0.13463264;
  double neighborhood_weight = 0.10999631;
  double late_weight = 0.16052921;
  double critical_weight = 0.11764424;
  unsigned budget = 6;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
