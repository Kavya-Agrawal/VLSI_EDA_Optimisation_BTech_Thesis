// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.36676781;
  double density_weight = 0.40137511;
  double prefix_weight = 0.12526415;
  double neighborhood_weight = 0.02243204;
  double late_weight = 0.13912235;
  double critical_weight = 0.39074789;
  unsigned budget = 16;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
