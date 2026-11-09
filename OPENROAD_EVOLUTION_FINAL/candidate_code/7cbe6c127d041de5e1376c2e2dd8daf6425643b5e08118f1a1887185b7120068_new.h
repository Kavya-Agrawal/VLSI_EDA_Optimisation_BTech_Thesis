// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.59432568;
  double density_weight = 0.23840976;
  double prefix_weight = 0.46044279;
  double neighborhood_weight = 0.00430141;
  double late_weight = 0.21849986;
  double critical_weight = 0.11570057;
  unsigned budget = 32;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
