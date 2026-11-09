// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.18975146;
  double density_weight = 0.22367993;
  double prefix_weight = 0.05708029;
  double neighborhood_weight = 0.19998084;
  double late_weight = 0.24284100;
  double critical_weight = 0.11572767;
  unsigned budget = 17;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
