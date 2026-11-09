// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.25923457;
  double density_weight = 0.26883574;
  double prefix_weight = 0.29591188;
  double neighborhood_weight = 0.33109969;
  double late_weight = 0.26926693;
  double critical_weight = 0.40056664;
  unsigned budget = 26;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
