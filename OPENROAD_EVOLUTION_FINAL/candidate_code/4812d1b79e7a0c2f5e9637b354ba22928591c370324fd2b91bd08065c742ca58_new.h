// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.44034920;
  double density_weight = 0.11236399;
  double prefix_weight = 0.28086292;
  double neighborhood_weight = 0.25258349;
  double late_weight = 0.09508055;
  double critical_weight = 0.20051682;
  unsigned budget = 12;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
