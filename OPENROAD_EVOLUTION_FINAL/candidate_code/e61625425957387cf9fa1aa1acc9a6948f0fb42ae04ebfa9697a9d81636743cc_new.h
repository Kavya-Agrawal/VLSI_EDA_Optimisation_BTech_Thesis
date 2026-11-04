// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.36815993;
  double density_weight = 0.07493201;
  double prefix_weight = 0.32486693;
  double neighborhood_weight = 0.38467424;
  double late_weight = 0.17363734;
  double critical_weight = 0.15800096;
  unsigned budget = 20;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
