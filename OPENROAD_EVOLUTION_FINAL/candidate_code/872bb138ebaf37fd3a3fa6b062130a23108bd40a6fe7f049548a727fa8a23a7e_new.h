// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.12989853;
  double density_weight = 0.36161748;
  double prefix_weight = 0.00419420;
  double neighborhood_weight = 0.04514385;
  double late_weight = 0.11856027;
  double critical_weight = 0.34671089;
  unsigned budget = 40;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
