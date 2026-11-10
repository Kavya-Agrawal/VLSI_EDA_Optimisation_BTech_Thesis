// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.78204581;
  double density_weight = 0.18729602;
  double prefix_weight = 0.19686768;
  double neighborhood_weight = 0.01345810;
  double late_weight = 0.23329375;
  double critical_weight = 0.22238270;
  unsigned budget = 19;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
