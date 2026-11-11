// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.59049735;
  double density_weight = 0.42125545;
  double prefix_weight = 0.20047161;
  double neighborhood_weight = 0.09405089;
  double late_weight = 0.00071281;
  double critical_weight = 0.43496021;
  unsigned budget = 16;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
