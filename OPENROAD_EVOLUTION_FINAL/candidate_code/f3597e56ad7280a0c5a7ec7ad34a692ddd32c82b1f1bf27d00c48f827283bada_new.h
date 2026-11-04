// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.47885822;
  double density_weight = 0.22068732;
  double prefix_weight = 0.38069545;
  double neighborhood_weight = 0.31806917;
  double late_weight = 0.22045754;
  double critical_weight = 0.28550128;
  unsigned budget = 6;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
