// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.87756967;
  double density_weight = 0.49100492;
  double prefix_weight = 0.12718779;
  double neighborhood_weight = 0.22380654;
  double late_weight = 0.07701562;
  double critical_weight = 0.08437260;
  unsigned budget = 26;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
