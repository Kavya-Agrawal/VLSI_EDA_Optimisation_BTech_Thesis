// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.03005016;
  double density_weight = 0.24210820;
  double prefix_weight = 0.12664138;
  double neighborhood_weight = 0.02488715;
  double late_weight = 0.04059944;
  double critical_weight = 0.19538673;
  unsigned budget = 30;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
