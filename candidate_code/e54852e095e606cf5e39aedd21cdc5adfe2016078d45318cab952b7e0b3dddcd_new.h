// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.00401748;
  double density_weight = 0.24605002;
  double prefix_weight = 0.26604237;
  double neighborhood_weight = 0.15669754;
  double late_weight = 0.03725029;
  double critical_weight = 0.49333993;
  unsigned budget = 13;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
