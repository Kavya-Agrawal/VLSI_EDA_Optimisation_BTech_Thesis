// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.56875769;
  double density_weight = 0.48851783;
  double prefix_weight = 0.03474045;
  double neighborhood_weight = 0.25189317;
  double late_weight = 0.27739240;
  double critical_weight = 0.19434037;
  unsigned budget = 38;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
