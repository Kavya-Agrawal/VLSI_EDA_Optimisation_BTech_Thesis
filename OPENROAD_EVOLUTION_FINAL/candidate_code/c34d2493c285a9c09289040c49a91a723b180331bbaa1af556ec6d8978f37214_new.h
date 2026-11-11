// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.23919060;
  double density_weight = 0.30579760;
  double prefix_weight = 0.07387149;
  double neighborhood_weight = 0.23497394;
  double late_weight = 0.16517670;
  double critical_weight = 0.11452629;
  unsigned budget = 23;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
