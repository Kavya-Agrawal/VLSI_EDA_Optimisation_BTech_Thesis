// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.35485890;
  double density_weight = 0.30933466;
  double prefix_weight = 0.04385693;
  double neighborhood_weight = 0.07554022;
  double late_weight = 0.26330399;
  double critical_weight = 0.34481375;
  unsigned budget = 5;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
