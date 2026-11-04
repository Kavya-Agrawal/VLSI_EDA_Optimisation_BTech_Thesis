// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.01527498;
  double density_weight = 0.04172320;
  double prefix_weight = 0.13591258;
  double neighborhood_weight = 0.20492546;
  double late_weight = 0.01896846;
  double critical_weight = 0.29257494;
  unsigned budget = 7;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
