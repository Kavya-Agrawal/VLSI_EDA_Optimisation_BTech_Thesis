// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.41893395;
  double density_weight = 0.03732164;
  double prefix_weight = 0.48263313;
  double neighborhood_weight = 0.32436776;
  double late_weight = 0.23470342;
  double critical_weight = 0.25587890;
  unsigned budget = 12;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
