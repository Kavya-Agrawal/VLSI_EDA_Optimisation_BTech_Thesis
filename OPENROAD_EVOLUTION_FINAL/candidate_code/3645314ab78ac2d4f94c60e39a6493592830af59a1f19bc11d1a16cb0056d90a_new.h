// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.54703335;
  double density_weight = 0.07462837;
  double prefix_weight = 0.21551124;
  double neighborhood_weight = 0.03173219;
  double late_weight = 0.27615044;
  double critical_weight = 0.46762848;
  unsigned budget = 24;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
