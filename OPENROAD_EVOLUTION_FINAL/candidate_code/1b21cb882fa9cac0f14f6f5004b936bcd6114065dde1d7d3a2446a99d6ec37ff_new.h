// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.97532755;
  double density_weight = 0.15294297;
  double prefix_weight = 0.29119482;
  double neighborhood_weight = 0.25062590;
  double late_weight = 0.23582602;
  double critical_weight = 0.29655855;
  unsigned budget = 33;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
