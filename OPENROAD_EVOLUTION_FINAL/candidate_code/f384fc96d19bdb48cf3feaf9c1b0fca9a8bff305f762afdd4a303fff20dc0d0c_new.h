// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.58616371;
  double density_weight = 0.53461386;
  double prefix_weight = 0.05859555;
  double neighborhood_weight = 0.28630297;
  double late_weight = 0.28300745;
  double critical_weight = 0.18906566;
  unsigned budget = 10;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
