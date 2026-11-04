// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.78613021;
  double density_weight = 0.25787583;
  double prefix_weight = 0.40684706;
  double neighborhood_weight = 0.15327074;
  double late_weight = 0.28024366;
  double critical_weight = 0.22153727;
  unsigned budget = 34;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
