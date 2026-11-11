// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.07729361;
  double density_weight = 0.55075920;
  double prefix_weight = 0.23548939;
  double neighborhood_weight = 0.17527060;
  double late_weight = 0.01112475;
  double critical_weight = 0.22447783;
  unsigned budget = 19;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
