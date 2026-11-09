// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.49802297;
  double density_weight = 0.27381302;
  double prefix_weight = 0.27501486;
  double neighborhood_weight = 0.12688275;
  double late_weight = 0.24435464;
  double critical_weight = 0.26672205;
  unsigned budget = 6;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
