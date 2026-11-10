// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21469996;
  double density_weight = 0.53740009;
  double prefix_weight = 0.18784775;
  double neighborhood_weight = 0.25121952;
  double late_weight = 0.24125873;
  double critical_weight = 0.13823317;
  unsigned budget = 26;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
