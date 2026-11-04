// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.82282825;
  double density_weight = 0.44641659;
  double prefix_weight = 0.02283759;
  double neighborhood_weight = 0.28220037;
  double late_weight = 0.12770279;
  double critical_weight = 0.48284880;
  unsigned budget = 27;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
