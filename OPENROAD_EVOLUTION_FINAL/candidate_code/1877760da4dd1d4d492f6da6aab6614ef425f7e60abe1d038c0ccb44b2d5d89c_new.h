// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.92191584;
  double density_weight = 0.11956771;
  double prefix_weight = 0.03886370;
  double neighborhood_weight = 0.13240433;
  double late_weight = 0.00355445;
  double critical_weight = 0.00687718;
  unsigned budget = 6;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
