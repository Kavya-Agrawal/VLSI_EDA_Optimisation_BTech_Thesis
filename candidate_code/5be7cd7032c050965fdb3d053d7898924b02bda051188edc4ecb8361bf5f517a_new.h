// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.59957979;
  double density_weight = 0.42177686;
  double prefix_weight = 0.44189578;
  double neighborhood_weight = 0.10732766;
  double late_weight = 0.23179443;
  double critical_weight = 0.35891120;
  unsigned budget = 35;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
